# Copyright (C) 2003-2024 GraphicsMagick Group
# Copyright (C) 2002 ImageMagick Studio
# Copyright (C) 1999 E. I. du Pont de Nemours and Company
#
# This program is covered by multiple licenses, which are described in
# Copyright.txt. You should have received a copy of Copyright.txt with this
# package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
#
# Common subroutines to support tests
#
# Contributed by Bob Friesenhahn <bfriesen@simple.dallas.tx.us>
#

require 't/features.pl';

# Function which returns true if named feature is supported.
sub featureSupported {
    my ($feature) = @_;

    #return ($feature ~~ @MAGICK_FEATURES);
    #return (any {$_ eq $feature} @MAGICK_FEATURES)
    return (grep {$_ eq $feature} @MAGICK_FEATURES)
}

#
# Retrieve quantum depth
#
sub quantumDepth ( ) {
  my($depth,$image);
  $image=Graphics::Magick->new;
  $depth=$image->Get('depth');
  undef $image;
  return $depth;
}

#
# Establish some global constants (MaxRGB, OpaqueOpacity, & QuantumDepth)
#
$QuantumDepth=quantumDepth();
$OpaqueOpacity=0;
if ($QuantumDepth == 8)
  {
    $MaxRGB=255;
  }
elsif ($QuantumDepth == 16)
  {
    $MaxRGB=65535;
  }
elsif ($QuantumDepth == 32)
  {
    $MaxRGB=4294967295;
  }

#
# Test composite method using comparison with a reference image
#
# Usage: testFilterCompare( background image name, background read options,
#                           composite image name, composite read options,
#                           composite options,reference image
#                           normalized_mean_error,
#                           normalized_maximum_error );
sub testCompositeCompare {
  my ($background_name,
      $background_read_options,
      $composite_name,
      $composite_read_options,
      $composite_options,
      $refimage_name,
      $normalized_mean_error_max,
      $normalized_maximum_error_max) = @_;
  my ($background,
      $composite,
      $errorinfo,
      $normalized_maximum_error,
      $normalized_mean_error,
      $refimage,
      $status);

  $errorinfo='';
  $status='';

  # Create images
  $background=Graphics::Magick->new;
  $composite=Graphics::Magick->new;
  $refimage=Graphics::Magick->new;

  # Read background image
  if ( "$background_read_options" ne "" ) {
    print("Set($background_read_options) ...\n");
    eval "\$status=\$background->Set($background_read_options);";
    if ("$status")
      {
        $errorinfo = "Set($background_read_options): $status";
        goto COMPARE_RUNTIME_ERROR;
      }
  }
  $status=$background->ReadImage($background_name);
  if ("$status")
    {
      $errorinfo = "Readimage ($background_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  # Read composite image
  if ( "$composite_read_options" ne "" ) {
    print("Set($composite_read_options) ...\n");
    eval "\$status=\$composite->Set($composite_read_options);";
    if ("$status")
      {
        $errorinfo = "Set($composite_read_options): $status";
        goto COMPARE_RUNTIME_ERROR;
      }
  }
  $status=$composite->ReadImage($composite_name);
  if ("$status")
    {
      $errorinfo = "Readimage ($composite_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  # Do composition
  print("Composite\($composite_options\) ...\n");
  eval "\$status=\$background->Composite(image=>\$composite, $composite_options);";
  if ("$status")
    {
      $errorinfo = "Composite ($composite_options): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  $background->set(depth=>8);
#  if ("$composite_options" =~ /Multiply/) {
#    $background->write(filename=>"$refimage_name", compression=>'None');
#    $background->Display();
#  }

  $status=$refimage->ReadImage("$refimage_name");
  if ("$status")
    {
      $errorinfo = "Readimage ($refimage_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  $status=$background->Compare($refimage);
  if ("$status")
    {
      $errorinfo = "Compare($refimage_name): $status";
      print("  Computed:  ", $background->Get('columns'), "x", $background->Get('rows'), "\n");
      print("  Reference: ", $refimage->Get('columns'), "x", $refimage->Get('rows'), "\n");
      goto COMPARE_RUNTIME_ERROR;
    }

  $normalized_mean_error=0;
  $normalized_mean_error=$background->GetAttribute('mean-error');
  if ( !defined($normalized_mean_error) )
    {
      $errorinfo = "GetAttribute('mean-error') returned undefined value!";
      goto COMPARE_RUNTIME_ERROR;
    }
  $normalized_maximum_error=0;
  $normalized_maximum_error=$background->GetAttribute('maximum-error');
  if ( ! defined($normalized_maximum_error) )
    {
      $errorinfo = "GetAttribute('maximum-error') returned undefined value!";
      goto COMPARE_RUNTIME_ERROR;
    }
  if ( ($normalized_mean_error > $normalized_mean_error_max) ||
       ($normalized_maximum_error > $normalized_maximum_error_max) )
    {
      print("  mean-error=$normalized_mean_error, maximum-error=$normalized_maximum_error\n");
      print "not ok $test\n";
      defined $ENV{'PERL_DEBUG'} && $background->Display();
      undef $background;
      undef $composite;
      undef $refimage;
      return 1
    }

  undef $background;
  undef $composite;
  undef $refimage;
  print "ok $test\n";
  return 0;

 COMPARE_RUNTIME_ERROR:
  defined $ENV{'PERL_DEBUG'} && $composite->Display();
  undef $background;
  undef $composite;
  undef $refimage;
  print("  $errorinfo\n");
  print "not ok $test\n";
  return 1
}

#
# Test reading a file (and blob) in which several signatures are
# possible, depending on available image depth.
#
# Usage: testRead( read filename, read options, expected ref_8 [, expected ref_16] [, expected ref_32] );
#
sub testRead {
  my( $infile, $read_options, $ref_8, $ref_16, $ref_32 ) =  @_;

  my($image,$magick,$success,$depth,$ref_signature,$errorinfo,$failure,$status);

  $errorinfo='';
  $failure=0;

  if ( !defined( $ref_16 ) )
    {
      $ref_16 = $ref_8;
    }
  if ( !defined( $ref_32 ) )
    {
      $ref_32 = $ref_16;
    }

  $depth=quantumDepth();
  if ($depth == 32)
    {
      $ref_signature=$ref_32;
    }
  elsif ($depth == 16)
    {
      $ref_signature=$ref_16;
    }
  else
    {
      $ref_signature=$ref_8;
    }

  $magick='';

  #
  # Test reading from file
  #
  {
    my($image, $signature, $status);

    print( "  testing reading from file \"", $infile, "\" ...\n");
    $image=Graphics::Magick->new;
    #$image->Set(size=>'512x512');

    if ( "$read_options" ne "" ) {
        eval "\$status=\$image->Set($read_options);";
        if ("$status")
        {
            $errorinfo = "Set($read_options): $status";
            warn("$errorinfo");
            goto READ_RUNTIME_ERROR;
        }
    }

    $status=$image->ReadImage("$infile");
    if( "$status" && !($status =~ /Exception ((315)|(350))/)) {
      print "ReadImage $infile: $status\n";
      ++$failure;
    } else {
      if( "$status" ) {
        print "ReadImage $infile: $status\n";
      }
      undef $status;
      $magick=$image->Get('magick');
      $signature=$image->Get('signature');

      if ( $signature ne $ref_signature ) {
        print "ReadImage()\n";
        print "Image: $infile, signatures do not match.\n";
        print "     Computed: $signature\n";
        print "     Expected: $ref_signature\n";
        print "     Depth:    $depth\n";
        ++$failure;
        defined $ENV{'PERL_DEBUG'} && $image->Display();
      }
    }
    undef $image;
  }

  #
  # Test reading from blob
  #
  if (!($infile =~ /\.bz2$/) && !($infile =~ /\.gz$/) && !($infile =~ /\.Z$/))
  {
    my(@blob, $blob_length, $image, $signature, $status);

    if( open( FILE, "< $infile"))
      {
        print( "  testing reading from BLOB with magick \"", $magick, "\"...\n");
        binmode( FILE );
        $blob_length = read( FILE, $blob, 10000000 );
        close( FILE );
        if( defined( $blob ) ) {
          $image=Graphics::Magick->new(magick=>$magick);
          #$image->Set(size=>'512x512');

          if ( defined( $read_options ) && "$read_options" ne "" ) {
              eval "\$status=\$image->Set($read_options);";
              if ("$status")
              {
                  $errorinfo = "Set($read_options): $status";
                  warn("$errorinfo");
                  goto READ_RUNTIME_ERROR;
              }
          }
          $status=$image->BlobToImage( $blob );
          undef $blob;
          if( "$status" && !($status =~ /Exception ((315)|(350))/)) {
            print "BlobToImage $infile: $status\n";
            ++$failure;
          } else {
            if( "$status" ) {
              print "ReadImage $infile: $status\n";
            }
            $signature=$image->Get('signature');
            if ( $signature ne $ref_signature ) {
              print "BlobToImage()\n";
              print "Image: $infile, signatures do not match.\n";
              print "     Computed: $signature\n";
              print "     Expected: $ref_signature\n";
              print "     Depth:    $depth\n";
              defined $ENV{'PERL_DEBUG'} && $image->Display();
              ++$failure;
            }
          }
        }
      }
    undef $image;
  }

 READ_RUNTIME_ERROR:

  #
  # Display test status
  #
  if ( $failure != 0 ) {
    print "not ok $test\n";
  } else {
    print "ok $test\n";
  }
}


#
# Test reading a file, and compare with a reference file
# This one does not test reading from an in-memory blob
#
sub testReadCompare {
  my( $srcimage_name,$refimage_name, $read_options,
      $normalized_mean_error_max, $normalized_maximum_error_max) = @_;
  my($srcimage, $refimage, $normalized_mean_error, $normalized_maximum_error);

  $errorinfo='';

  # Create images
  $srcimage=Graphics::Magick->new;
  $refimage=Graphics::Magick->new;

  if ( "$read_options" ne "" ) {
    eval "\$status=\$srcimage->Set($read_options);";
    if ("$status")
      {
        $errorinfo = "Set($read_options): $status";
        warn("$errorinfo");
        goto COMPARE_RUNTIME_ERROR;
      }
  }

  $status=$srcimage->ReadImage("$srcimage_name");
  if ("$status")
    {
      $errorinfo = "Readimage ($srcimage_name): $status";
      warn("$errorinfo");
      goto COMPARE_RUNTIME_ERROR;
    }

# if ("$srcimage_name" eq "CGM:input.cgm") {
#    $srcimage->write(filename=>"$refimage_name", compression=>'None');
#  }

  #print("writing file $refimage_name\n");
  #$srcimage->Quantize(colors=>256);
  #$status=$srcimage->write(filename=>"$refimage_name", compression=>'rle');
  #warn "$status" if $status;

  $status=$refimage->ReadImage("$refimage_name");
  if ("$status")
    {
      $errorinfo = "Readimage ($refimage_name): $status";
       warn("$errorinfo");
      goto COMPARE_RUNTIME_ERROR;
    }

  $srcimage->set(depth=>8);

  # FIXME: The following statement should not be needed.
#  $status=$refimage->Set(type=>'TrueColor');
#  if ("$status")
#    {
#      $errorinfo = "Set(type=>'TrueColor'): $status";
#      goto COMPARE_RUNTIME_ERROR;
#    }

  # Verify that $srcimage and $refimage contain the same number of frames.
  if ( $#srcimage != $#refimage )
    {
      $errorinfo = "Source and reference images contain different number of frames ($#srcimage != $#refimage)";
      warn("$errorinfo");
      goto COMPARE_RUNTIME_ERROR;
    }

  # Compare each frame in the sequence.
  for ($index = 0; $srcimage->[$index] && $refimage->[$index]; $index++)
    {
      $status=$srcimage->[$index]->Compare($refimage->[$index]);
      if ("$status")
        {
          $errorinfo = "Compare($refimage_name)->[$index]: $status";
          warn("$errorinfo");
          goto COMPARE_RUNTIME_ERROR;
        }
    }

  $normalized_mean_error=0;
  $normalized_mean_error=$srcimage->GetAttribute('mean-error');
  if ( !defined($normalized_mean_error) )
    {
      $errorinfo = "GetAttribute('mean-error') returned undefined value!";
      warn("$errorinfo");
      goto COMPARE_RUNTIME_ERROR;
    }
  $normalized_maximum_error=0;
  $normalized_maximum_error=$srcimage->GetAttribute('maximum-error');
  if ( ! defined($normalized_maximum_error) )
    {
      $errorinfo = "GetAttribute('maximum-error') returned undefined value!";
      warn("$errorinfo");
      goto COMPARE_RUNTIME_ERROR;
    }
  if ( ($normalized_mean_error > $normalized_mean_error_max) ||
       ($normalized_maximum_error > $normalized_maximum_error_max) )
    {
      print("mean-error=$normalized_mean_error, maximum-error=$normalized_maximum_error\n");
      defined $ENV{'PERL_DEBUG'} && $srcimage->Display();
      print "not ok $test\n";
      return 1
    }

  undef $srcimage;
  undef $refimage;
  print "ok $test\n";
  return 0;

 COMPARE_RUNTIME_ERROR:
  $srcimage->Display();
  $refimage->Display();
  undef $srcimage;
  undef $refimage;
  print "not ok $test\n";
  return 1
}

#
# Test reading a file which requires a file size to read (GRAY, RGB, CMYK)
# or supports multiple resolutions (JBIG, JPEG, PCD)
#
# Usage: testReadSized( read filename, size, depth, expected ref_8 [, expected ref_16] );
#
sub testReadSized {
  my( $infile, $size, $depth, $ref_8, $ref_16, $ref_32 ) =  @_;

  my($image,$ref_signature);

  if ( !defined( $ref_16 ) )
    {
      $ref_16 = $ref_8;
    }
  if ( !defined( $ref_32 ) )
    {
      $ref_32 = $ref_16;
    }

  $depth=quantumDepth();
  if ($depth == 32)
    {
      $ref_signature=$ref_32;
    }
  elsif ($depth == 16)
    {
      $ref_signature=$ref_16;
    }
  else
    {
      $ref_signature=$ref_8;
    }

  $image=Graphics::Magick->new;

  # Set size attribute
  $status=$image->SetAttribute(size=>"$size");
  warn "$status" if "$status";

  # If depth is not zero, then set it
  if ( $depth != 0 ) {
    $status=$image->SetAttribute(depth=>"$depth");
    warn "$status" if "$status";
  }

  $status=$image->ReadImage("$infile");
  if( "$status" ) {
    print "ReadImage $infile: $status";
    print "not ok $test\n";
  } else {
    $signature=$image->Get('signature');
      if ( $signature ne $ref_signature ) {
        print "ReadImage()\n";
        print "Image: $infile, signatures do not match.\n";
        print "     Computed: $signature\n";
        print "     Expected: $ref_signature\n";
        print "     Depth:    $depth\n";
        print "not ok $test\n";
        defined $ENV{'PERL_DEBUG'} && $image->Display();
      } else {
        print "ok $test\n";
    }
  }
}

#
# Test writing a file by first reading a source image, writing to a new image,
# reading the written image, and comparing with expected REF_8.
#
# Usage: testReadWrite( read filename, write filename, write options,
#    expected ref_8 [, expected ref_16] );
#
# .e.g
#
# testReadWrite( 'input.jpg', 'output.jpg', q/quality=>80, interlace=>'None'/,
#                'dc0a144a0b9480cd1e93757a30f01ae3' );
#
# If the REF_8 of the written image is not what is expected, the written
# image is preserved.  Otherwise, the written image is removed.
#
sub testReadWrite {
  my( $infile, $outfile, $writeoptions, $ref_8, $ref_16, $ref_32 ) = @_;

  my($image);

  if ( !defined( $ref_16 ) )
    {
      $ref_16 = $ref_8;
    }
  if ( !defined( $ref_32 ) )
    {
      $ref_32 = $ref_16;
    }

  $depth=quantumDepth();
  if ($depth == 32)
    {
      $ref_signature=$ref_32;
    }
  elsif ($depth == 16)
    {
      $ref_signature=$ref_16;
    }
  else
    {
      $ref_signature=$ref_8;
    }

  $image=Graphics::Magick->new;
  $status=$image->ReadImage("$infile");
  $signature=$image->Get('signature');
  if( "$status" ) {
    print "ReadImage $infile: $status\n";
    print "not ok $test\n";
  } else {
    # Write image to file
    my $options = 'filename=>"$outfile", ' . "$writeoptions";
    #print "Using options: $options\n";
    eval "\$status=\$image->WriteImage( $options ) ;";
    if( $@ ) {
      print "$@\n";
      print "not ok $test\n";
      exit 1;
    }
    if( "$status" ) {
      print "WriteImage $outfile: $status\n";
      print "not ok $test\n";
    } else {
      my($image);

      # Read image just written
      $image=Graphics::Magick->new;
      $status=$image->ReadImage("$outfile");
      if( "$status" ) {
        print "ReadImage $outfile: $status\n";
        print "not ok $test\n";
      } else {
        # Check signature
        $signature=$image->Get('signature');
        if ( $signature ne $ref_signature ) {
          print "ReadImage()\n";
          print "Image: $infile, signatures do not match.\n";
          print "     Computed: $signature\n";
          print "     Expected: $ref_signature\n";
          print "     Depth:    $depth\n";
          print "not ok $test\n";
          defined $ENV{'PERL_DEBUG'} && $image->Display();
        } else {
          print "ok $test\n";
          ($file = $outfile) =~ s/.*://g;
          #unlink "$file";
        }
      }
    }
  }
}

#
# Test reading a file, and compare with a reference file
#
sub testReadWriteCompare {
  my( $srcimage_name, $outimage_name, $refimage_name,
      $read_options, $write_options,
      $normalized_mean_error_max, $normalized_maximum_error_max) = @_;
  my($srcimage, $refimage, $normalized_mean_error,
    $normalized_maximum_error);

  $errorinfo='';

  $image=Graphics::Magick->new;
  $refimage=Graphics::Magick->new;

  #
  # Read the initial image
  #
  $status=$image->ReadImage($srcimage_name);
  if ("$status")
    {
      $errorinfo = "Readimage ($srcimage_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  #
  # Write image to output file
  #
  if ( "$write_options" ne "" ) {
    eval "\$status=\$image->Set($write_options);";
    if ("$status")
      {
        $errorinfo = "Set($write_options): $status";
        goto COMPARE_RUNTIME_ERROR;
      }
  }
  $image->Set(filename=>"$outimage_name");

  $status=$image->WriteImage( );
  if ("$status")
    {
      $errorinfo = "WriteImage ($outimage_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  undef $image;
  $image=Graphics::Magick->new;

  #
  # Read image from output file
  #
  if ( "$read_options" ne "" ) {
    eval "\$status=\$image->Set($read_options);";
    if ("$status")
      {
        $errorinfo = "Set($read_options): $status";
        goto COMPARE_RUNTIME_ERROR;
      }
  }

  $image->ReadImage("$outimage_name");
  if ("$status")
    {
      $errorinfo = "WriteImage ($outimage_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

# eval "\$status=\$image->Set($write_options);";
#  if ("$outimage_name" eq "P7:output_p7.p7")
#    {
#      $status=$image->write(filename=>"$refimage_name", compression=>'None');
#      warn "$status" if $status;
#    }

  #
  # Read reference image
  #
  $status=$refimage->ReadImage("$refimage_name");
  if ("$status")
    {
      $errorinfo = "Readimage ($refimage_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  #
  # Compare output file with reference image
  #

  $image->set(depth=>8);

  # FIXME: The following statement should not be needed.
#  $status=$refimage->Set(type=>'TrueColor');
#  if ("$status")
#    {
#      $errorinfo = "Set(type=>'TrueColor'): $status";
#      goto COMPARE_RUNTIME_ERROR;
#    }

  $status=$image->Compare($refimage);
  if ("$status")
    {
      $errorinfo = "Compare($refimage_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  $normalized_mean_error=0;
  $normalized_mean_error=$image->GetAttribute('mean-error');
  if ( !defined($normalized_mean_error) )
    {
      $errorinfo = "GetAttribute('mean-error') returned undefined value!";
      goto COMPARE_RUNTIME_ERROR;
    }
  $normalized_maximum_error=0;
  $normalized_maximum_error=$image->GetAttribute('maximum-error');
  if ( ! defined($normalized_maximum_error) )
    {
      $errorinfo = "GetAttribute('maximum-error') returned undefined value!";
      goto COMPARE_RUNTIME_ERROR;
    }

  if ( ($normalized_mean_error > $normalized_mean_error_max) ||
       ($normalized_maximum_error > $normalized_maximum_error_max) )
    {
      print("mean-error=$normalized_mean_error, maximum-error=$normalized_maximum_error\n");
      print "not ok $test\n";
      defined $ENV{'PERL_DEBUG'} && $image->Display();
      return 1
    }

  print "ok $test\n";
  undef $image;
  undef $refimage;
  return 0;

 COMPARE_RUNTIME_ERROR:
  warn("$errorinfo");
  print "not ok $test\n";
  undef $image;
  undef $refimage;
  return 1
}

#
# Test writing a file by first reading a source image, writing to a
# new image, and reading the written image.  Depends on detecting
# reported errors by GraphicsMagick
#
# Usage: testReadWrite( read filename, write filename, write options);
#
# .e.g
#
# testReadWrite( 'input.jpg', 'output.jpg', q/quality=>80, 'interlace'=>'None'/ );
#
# If the read of the written image is not what is expected, the
# written image is preserved.  Otherwise, the written image is
# removed.
#
sub testReadWriteNoVerify {
  my( $infile, $outfile, $writeoptions) = @_;

  my($image, $images);

  $image=Graphics::Magick->new;
  $status=$image->ReadImage("$infile");
  if( "$status" ) {
    print "$status\n";
    print "ReadImage $infile: not ok $test\n";
  } else {
    # Write image to file
    my $options = 'filename=>"$outfile", ' . $writeoptions;
    #print "Using options: $options\n";
    eval "\$status=\$image->WriteImage( $options ) ;";
    if( $@ ) {
      print "$@";
      print "not ok $test\n";
      exit 1;
    }
    if( "$status" ) {
      print "WriteImage $outfile: $status\n";
      print "not ok $test\n";
    } else {
      my($image);

      # Read image just written
      $image=Graphics::Magick->new;
      $status=$image->ReadImage("$outfile");
      if( "$status" ) {
        print "ReadImage $outfile: $status\n";
        print "not ok $test\n";
      } else {
        print "ok $test\n";
        unlink $outfile;
      }
    }
  }
}

#
# Test writing a file by first reading a source image, writing to a new image,
# reading the written image, and comparing with expected REF_8.
#
# Usage: testReadWriteSized( read filename,
#                            write filename,
#                            read filename size,
#                            read filename depth,
#                            write options,
#                            expected ref_8 [,expected ref_16] );
#
# .e.g
#
# testReadWriteSized( 'input.jpg', 'output.jpg', '70x46', 8, q/quality=>80,
#                     'interlace'=>'None'/, 'dc0a144a0b9480cd1e93757a30f01ae3' );
#
# If the REF_8 of the written image is not what is expected, the written
# image is preserved.  Otherwise, the written image is removed.  A depth of 0 is
# ignored.
#
sub testReadWriteSized {
  my( $infile, $outfile, $size, $readdepth, $writeoptions, $ref_8, $ref_16,
      $ref_32 ) = @_;

  my($image,$depth,$ref_signature);

  if ( !defined( $ref_16 ) )
    {
      $ref_16 = $ref_8;
    }
  if ( !defined( $ref_32 ) )
    {
      $ref_32 = $ref_16;
    }

  $depth=quantumDepth();
  if ($depth == 32)
    {
      $ref_signature=$ref_32;
    }
  elsif ($depth == 16)
    {
      $ref_signature=$ref_16;
    }
  else
    {
      $ref_signature=$ref_8;
    }

  $image=Graphics::Magick->new;

  #$image->SetAttribute(debug=>'transform');

  # Set size attribute
  $status=$image->SetAttribute(size=>"$size");
  warn "$status" if "$status";

  # If read depth is not zero, then set it
  if ( $readdepth != 0 ) {
    $status=$image->SetAttribute(depth=>$readdepth);
    warn "$status" if "$status";
  }

  $status=$image->ReadImage("$infile");
  if( "$status" ) {
    print "ReadImage $infile: $status\n";
    print "not ok $test\n";
  } else {
    # Write image to file
    my $options = 'filename=>"$outfile", ' . "$writeoptions";
    #print "Using options: $options\n";
    eval "\$status=\$image->WriteImage( $options ) ;";
    if( $@ ) {
      print "$@\n";
      print "not ok $test\n";
      exit 1;
    }
    if( "$status" ) {
      print "WriteImage $outfile: $status\n";
      print "not ok $test\n";
    } else {
      my($image);

      $image=Graphics::Magick->new;

      if ( $readdepth != 0 ) {
        $status=$image->SetAttribute(depth=>$readdepth);
        warn "$status" if "$status";
      }
      # Set image size attribute
      $status=$image->SetAttribute(size=>"$size");
      warn "$status" if "$status";

      # Read image just written
      $status=$image->ReadImage("$outfile");
      if( "$status" ) {
        print "ReadImage $outfile: $status\n";
        print "not ok $test\n";
      } else {
        # Check signature
        $signature=$image->Get('signature');

        if ( $signature ne $ref_signature ) {
          print "ReadImage()\n";
          print "Image: $infile, signatures do not match.\n";
          print "     Computed: $signature\n";
          print "     Expected: $ref_signature\n";
          print "     Depth:    $depth\n";
          print "not ok $test\n";
          defined $ENV{'PERL_DEBUG'} && $image->Display();
        } else {
          print "ok $test\n";
          #$image->Display();
          ($file = $outfile) =~ s/.*://g;
          unlink "$file";
        }
      }
    }
  }
}

#
# Test SetAttribute method
#
# Usage: testSetAttribute( name, attribute);
#
sub testSetAttribute {
  my( $srcimage, $name, $attribute ) = @_;

  my($image);

  # Create temporary image
  $image=Graphics::Magick->new;

  $status=$image->ReadImage("$srcimage");
  warn "Readimage: $status" if "$status";

  # Set image option
  print "Image Option  : $name=>$attribute\n";
  eval "\$status = \$image->Set('$name'=>'$attribute') ;";
  warn "SetImage: $status" if "$status";

  # Convert input values to expected output values
  $expected=$attribute;
  if ($attribute eq 'True' || $attribute eq 'true') {
    $expected = 1;
  } elsif ($attribute eq 'False' || $attribute eq 'false') {
    $expected = 0;
  }


  $value=$image->GetAttribute($name);

  if( defined( $value ) ) {
    if ("$expected" eq "$value") {
      print "ok $test\n";
    } else {
      print "Expected ($expected), Got ($value)\n";
      print "not ok $test\n";
    }
  } else {
    print "GetAttribute returned undefined value!\n";
    print "not ok $test\n";
  }
}

#
# Test GetAttribute method
#
# Usage: testGetAttribute( name, expected);
#
sub testGetAttribute {
  my( $srcimage, $name, $expected ) = @_;

  my($image);

  # Create temporary image
  $image=Graphics::Magick->new;

  $status=$image->ReadImage("$srcimage");
  warn "Readimage: $status" if "$status";

  $value=$image->GetAttribute($name);

  if( !defined( $expected ) && !defined( $value ) ) {
    # Undefined value is expected
    print "ok $test\n";
  } elsif ( !defined( $value ) ) {
    print "Expected ($expected), Got (undefined)\n";
    print "not ok $test\n";
  } else {
    if ("$expected" eq "$value") {
      print "ok $test\n";
    } else {
      print "Expected ($expected), Got ($value)\n";
      print "not ok $test\n";
    }
  }
}

#
# Test MontageImage method
#
# Usage: testMontage( input image attributes, montage options, expected REF_8
#       [, expected REF_16] );
#
sub testMontage {
  my( $imageOptions, $montageOptions, $ref_8, $ref_16, $ref_32 ) = @_;

  my($image,$depth,$ref_signature);

  if ( !defined( $ref_16 ) )
    {
      $ref_16 = $ref_8;
    }
  if ( !defined( $ref_32 ) )
    {
      $ref_32 = $ref_16;
    }

  $depth=quantumDepth();
  if ($depth == 32)
    {
      $ref_signature=$ref_32;
    }
  elsif ($depth == 16)
    {
      $ref_signature=$ref_16;
    }
  else
    {
      $ref_signature=$ref_8;
    }

  # Create image for image list
  $images=Graphics::Magick->new;

  # Create temporary image
  $image=Graphics::Magick->new;

  my @colors = ( '#000000', '#008000', '#C0C0C0', '#00FF00',
                 '#808080', '#808000', '#FFFFFF', '#FFFF00',
                 '#800000', '#000080', '#FF0000', '#0000FF',
                 '#800080', '#008080', '#FF00FF', '#00FFFF' );

  my $color;
  foreach $color ( @colors ) {

    # Generate image
    $image->Set(size=>'50x50');
    #print("\$image->ReadImage(xc:$color);\n");
    $status=$image->ReadImage("xc:$color");
    if ("$status") {
      warn "Readimage: $status" if "$status";
    } else {
      # Add image to list
      push( @$images, @$image);
    }
    undef @$image;
  }

  # Set image options
  if ("$imageOptions" ne "") {
    print("\$images->Set($imageOptions)\n");
    eval "\$status = \$images->Set($imageOptions) ;";
    warn "SetImage: $status" if "$status";
  }

  #print "Border color : ", $images->Get('bordercolor'), "\n";
  #print "Matte color  : ", $images->Get('mattecolor'), "\n";
  #print "Pen color    : ", $images->Get('pen'), "\n";

  # Do montage
  #print "Montage Options: $montageOptions\n";
  print("\$montage=\$images->Montage( $montageOptions )\n");
  eval "\$montage=\$images->Montage( $montageOptions ) ;";
  if( $@ ) {
    print "$@";
    print "not ok $test\n";
    return 1;
  }

  if( ! ref($montage) ) {
    print "not ok $test\n";
  } else {
    # Check REF_8 signature
    # $montage->Display();
    $signature=$montage->GetAttribute('signature');
    if ( defined( $signature ) ) {
      if ( $signature ne $ref_signature ) {
        print "ReadImage()\n";
        print "Test $test, signatures do not match.\n";
        print "     Computed: $signature\n";
        print "     Expected: $ref_signature\n";
        print "     Depth:    $depth\n";
        $status = $montage->Write("test_${test}_out.miff");
        warn "Write: $status" if "$status";

        print "not ok $test\n";
      } else {
        # Check montage directory
        my $directory = $montage->Get('directory');
        my $expected = join( "\n", @colors ) . "\n";
        if ( !defined($directory) ) {
          print "ok $test\n";
        } elsif ( $directory  ne $expected) {
          print("Invalid montage directory:\n\"$directory\"\n");
          print("Expected:\n\"$expected\"\n");
          print "not ok $test\n";
        } else {
          # Check montage geometry
          $montage_geom=$montage->Get('montage');
          if( !defined($montage_geom) ) {
            print("Montage geometry not defined!\n");
            print "not ok $test\n";
          } elsif ( $montage_geom !~ /^\d+x\d+\+\d+\+\d+$/ ) {
            print("Montage geometry not in correct format: \"$montage_geom\"\n");
            print "not ok $test\n";
          } else {
            print "ok $test\n";
          }
        }
      }
    } else {
      warn "GetAttribute returned undefined value!";
      print "not ok $test\n";
    }
  }
}

#
# Test filter method using signature compare
#
# Usage: testFilterSignature( input image attributes, filter, options, expected REF_8
#      [, expected REF_16] );
#
sub testFilterSignature {
  my( $srcimage, $filter, $filter_options, $ref_8, $ref_16, $ref_32 ) = @_;

  my($image,$depth,$ref_signature);

#  print( $filter, " ...\n" );

  if ( !defined( $ref_16 ) )
    {
      $ref_16 = $ref_8;
    }
  if ( !defined( $ref_32 ) )
    {
      $ref_32 = $ref_16;
    }

  $depth=quantumDepth();
  if ($depth == 32)
    {
      $ref_signature=$ref_32;
    }
  elsif ($depth == 16)
    {
      $ref_signature=$ref_16;
    }
  else
    {
      $ref_signature=$ref_8;
    }

  # Create temporary image
  $image=Graphics::Magick->new;

  $status=$image->ReadImage("$srcimage");
  warn "Readimage: $status" if "$status";

  print("$filter\($filter_options\) ...\n");
  $image->$filter($filter_options);
#$image->write(filename=>"reference/filter/$filter.miff", compression=>'None');

  $signature=$image->GetAttribute('signature');
  if ( defined( $signature ) ) {
    if ( $signature ne $ref_signature ) {
      print "Test $test, signatures do not match.\n";
      print "     Computed: $signature\n";
      print "     Expected: $ref_signature\n";
      print "     Depth:    $depth\n";
      defined $ENV{'PERL_DEBUG'} && $image->Display();
      print "not ok $test\n";
    } else {
      print "ok $test\n";
    }
  } else {
    warn "GetAttribute returned undefined value!";
    print "not ok $test\n";
  }
}

#
# Test filter method using comparison with reference image
#
# Usage: testFilterCompare( input image, input image options, reference image, filter, filter options,
#                           normalized_mean_error,
#                           normalized_maximum_error );
sub testFilterCompare {
  my ($srcimage_name, $src_read_options, $refimage_name, $filter,
      $filter_options, $normalized_mean_error_max,
      $normalized_maximum_error_max) = @_;
  my($srcimage, $refimage, $normalized_mean_error,
    $normalized_maximum_error);
  my($status,$errorinfo);

  $errorinfo='';
  $status='';

  #print( $filter, " ...\n" );

  # Create images
  $srcimage=Graphics::Magick->new;
  $refimage=Graphics::Magick->new;

  if ( "$src_read_options" ne "" ) {
    print("Set($src_read_options) ...\n");
    eval "\$status=\$srcimage->Set($src_read_options);";
    if ("$status")
      {
        $errorinfo = "Set($src_read_options): $status";
        goto COMPARE_RUNTIME_ERROR;
      }
  }

  $status=$srcimage->ReadImage($srcimage_name);
  #eval "\$status=\$srcimage->ReadImage($srcimage_name);";
  if ("$status")
    {
      $errorinfo = "Readimage ($srcimage_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  print("$filter\($filter_options\) ...\n");
  eval "\$status=\$srcimage->$filter($filter_options);";
  if ("$status")
    {
      $errorinfo = "$filter ($filter_options): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  $srcimage->set(depth=>8);
#  if ("$filter" eq "Shear") {
#    $srcimage->Display();
#    $srcimage->write(filename=>"$refimage_name", compression=>'None');
#  }

  $status=$refimage->ReadImage("$refimage_name");
  if ("$status")
    {
      $errorinfo = "Readimage ($refimage_name): $status";
      goto COMPARE_RUNTIME_ERROR;
    }

  # FIXME: The following statement should not be needed.
#  $status=$refimage->Set(type=>'TrueColor');
#  if ("$status")
#    {
#      $errorinfo = "Set(type=>'TrueColor'): $status";
#      goto COMPARE_RUNTIME_ERROR;
#    }

  $status=$srcimage->Compare($refimage);
  if ("$status")
    {
      $errorinfo = "Compare($refimage_name): $status";
      print("  Computed:  ", $srcimage->Get('columns'), "x", $srcimage->Get('rows'), "\n");
      print("  Reference: ", $refimage->Get('columns'), "x", $refimage->Get('rows'), "\n");
      goto COMPARE_RUNTIME_ERROR;
    }

  $normalized_mean_error=0;
  $normalized_mean_error=$srcimage->GetAttribute('mean-error');
  if ( !defined($normalized_mean_error) )
    {
      $errorinfo = "GetAttribute('mean-error') returned undefined value!";
      goto COMPARE_RUNTIME_ERROR;
    }
  $normalized_maximum_error=0;
  $normalized_maximum_error=$srcimage->GetAttribute('maximum-error');
  if ( ! defined($normalized_maximum_error) )
    {
      $errorinfo = "GetAttribute('maximum-error') returned undefined value!";
      goto COMPARE_RUNTIME_ERROR;
    }
  if ( ($normalized_mean_error > $normalized_mean_error_max) ||
       ($normalized_maximum_error > $normalized_maximum_error_max) )
    {
      print("  mean-error=$normalized_mean_error, maximum-error=$normalized_maximum_error\n");
      print "not ok $test\n";
      defined $ENV{'PERL_DEBUG'} && $srcimage->Display();
      undef $srcimage;
      undef $refimage;
      return 1
    }

  undef $srcimage;
  undef $refimage;
  print "ok $test\n";
  return 0;

 COMPARE_RUNTIME_ERROR:
  undef $srcimage;
  undef $refimage;
  print("  $errorinfo\n");
  print "not ok $test\n";
  return 1
}

#
# Test AccessDefinition method
#
# Usage: testAccessDefinition( image, magick, key, expected );
#
sub testAccessDefinition {
  my( $image, $magick, $key, $expected ) = @_;

        my $got = $image->AccessDefinition($magick, $key);

  if( !defined( $got ) && !defined( $expected ) ) {
    # Undefined value is expected
    print "ok $test\n";
  } elsif ( !defined( $got ) ) {
    print "Expected ($expected), Got (undefined)\n";
    print "not ok $test\n";
  } else {
    if ("$expected" eq "$got") {
      print "ok $test\n";
    } else {
      print "Expected ($expected), Got ($got)\n";
      print "not ok $test\n";
    }
  }
}

#
# Test AddDefinition method
#
# Usage: testAddDefinition( image, magick, key, value, expected );
#
sub testAddDefinition {
  my( $image, $magick, $key, $value, $expected ) = @_;

        # returns 1 on success, 0 on failure
  my $result = $image->AddDefinition($magick, $key, $value);

  if ( $result == $expected) {
    print "ok $test\n";
  } else {
    print "Expected ($expected), Got ($result)\n";
    print "not ok $test\n";
  }
}

#
# Test AddDefinitions method
#
# Usage: testAddDefinitions( image, values, expected );
#
sub testAddDefinitions {
  my( $image, $values, $expected ) = @_;

        # returns 1 on success, 0 on failure
  my $result = $image->AddDefinitions($values);

  if ( $result == $expected) {
    print "ok $test\n";
  } else {
    print "Expected ($expected), Got ($result)\n";
    print "not ok $test\n";
  }
}

#
# Test RemoveDefinitions method
#
# Usage: testRemoveDefinitions( image, values, expected );
#
sub testRemoveDefinitions {
  my( $image, $values, $expected ) = @_;

        # returns 1 on success, 0 on failure
  my $result = $image->RemoveDefinitions($values);

  if ( $result == $expected) {
    print "ok $test\n";
  } else {
    print "Expected ($expected), Got ($result)\n";
    print "not ok $test\n";
  }
}
1;

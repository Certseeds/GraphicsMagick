#!/usr/local/bin/perl
# Copyright (C) 2003-2022 GraphicsMagick Group
# Copyright (C) 2002 ImageMagick Studio
# Copyright (C) 1991-1999 E. I. du Pont de Nemours and Company
#
# This program is covered by multiple licenses, which are described in
# Copyright.txt. You should have received a copy of Copyright.txt with this
# package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
#
#
# Test reading formats supported directly by GraphicsMagick
#
# Whenever a new test is added/removed, be sure to update the
# 1..n ouput.
#
BEGIN { $| = 1; $test=1; print "TAP version 13\n1..88\n"; }
END {print "not ok $test\n" unless $loaded;}
use Graphics::Magick;
$loaded=1;

require 't/subroutines.pl';

chdir 't' || die 'Cd failed';

print("AVS X image file ...\n");
testRead('input.avs', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Microsoft Windows bitmap image file ...\n");
++$test;
testRead('input.bmp', q//,
         '5083e062c7e4d3d462944bc1e89c4f491bf1f0241352e0a93988c8854c261fdb');

print("Microsoft Windows 24-bit bitmap image file ...\n");
++$test;
testRead('input.bmp24', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Cineon Gray image file ...\n");
++$test;
testRead('input_gray.cin', q//,
         'ccaf790142036ff44357a3feaf254027416d4fcc1925f2aa9f33adcea5fa3640',
         '4e747c49104cd520c3c1f3211d0ae67ac8bddbbe1f69983da3fabc24e19ffc27');

print("Cineon RGB image file ...\n");
++$test;
testRead('input_rgb.cin', q//,
         'eca74b0f19caa54629a57f77c9d513897185db1c751aff7a1cc593b998fefd09',
         '21ce8408f9e97cd955da38b68e1ec70622a04bec07344fbac22657e4cf06fc9c');

print("ZSoft IBM PC multi-page Paintbrush file ...\n");
++$test;
testRead('input.dcx', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Microsoft Windows bitmap image file ...\n");
++$test;
testRead('input.dib', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Flexible Image Transport System 8-bit ...\n");
++$test;
testReadCompare('input_gray_08bit.fits', 'reference/read/input_gray_08bit_fits.miff', q//, 0, 0);
# This one produces a different signature each time!
#testRead('input_gray_08bit.fits', q//,, ,'863a70f43cb481512e805babd7e09360ef6e5c7fe75725712242b367f0d0ef28');

print("Flexible Image Transport System LSB 16-bit ...\n");
++$test;
testRead('input_gray_16bit.fits',  q//,
         'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855');

print("Flexible Image Transport System LSB 32-bit ...\n");
++$test;
testRead('input_gray_32bit.fits', q//,
         'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855');

print("Flexible Image Transport System LSB double ...\n");
++$test;
testReadCompare('input_gray_lsb_double.fits', 'reference/read/input_gray_lsb_double_fits.miff', q//, 0.002, 0.004);

print("Flexible Image Transport System MSB 16-bit ...\n");
++$test;
testRead('input_gray_msb_16bit.fits', q//,
         'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855');

print("Flexible Image Transport System MSB 32-bit ...\n");
++$test;
testRead('input_gray_msb_32bit.fits', q//,
         'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855');

print("Flexible Image Transport System MSB 64-bit ...\n");
++$test;
testRead('input_gray_msb_64bit.fits', q//,
         'e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855');

print("Flexible Image Transport System MSB float ...\n");
++$test;
testReadCompare('input_gray_msb_float.fits', 'reference/read/input_gray_msb_float_fits.miff', q//, 0.002, 0.004);

print("Flexible Image Transport System MSB double ...\n");
++$test;
testReadCompare('input_gray_msb_double.fits', 'reference/read/input_gray_msb_double_fits.miff', q//, 0.002, 0.004);

print("CompuServe graphics interchange format ...\n");
++$test;
testRead('input.gif', q//,
         'f84cb6b5817ea2f6f313c2bdd90c94af0d0e7fb144528994050b355f8d5e6a94');

print("CompuServe graphics interchange format (1987) ...\n");
++$test;
testRead('input.gif87', q//,
         'f84cb6b5817ea2f6f313c2bdd90c94af0d0e7fb144528994050b355f8d5e6a94');

print("Gradient (gradual passing from one shade to another) ...\n");
++$test;
testRead('gradient:red-blue', q/size=>"256x256", depth=>8/,
         'c84d22f40f69a5055baf5148629bd37a175d768c924b46580303953026df2d26');

print("GRANITE (granite texture) ...\n");
++$test;
testRead('granite:', q/size=>"70x46", depth=>8/ ,'6e7317a9cb3abb1fe090d2d43c7645be455b6116ef8e93ca193d1df421447602');

print("HRZ Slow scan TV ...\n");
++$test;
testRead('input.hrz', q//,
         'cf3aed87b1364c93509e15b2519c26dd0302dcef024ac92d0c870aeacf472524');

print("MacPaint ...\n");
++$test;
testRead('input.mac', q//,
         '9efba89e075921201e837583e3439968b1569e2608994cf89673ecc3024b2ea3');

print("MAT (MatLab logical 8-bit LSB integer) ...\n");
++$test;
testRead('input_logical_lsb_08bit.mat', q//,
         '864fb782fc20acd3428f90a1a373a6dec27d1dfe84a42f8462f303a812653878');

print("MAT (MatLab gray 8-bit LSB integer) ...\n");
++$test;
testRead('input_gray_lsb_08bit.mat', q//,
         '863a70f43cb481512e805babd7e09360ef6e5c7fe75725712242b367f0d0ef28');

print("MAT (MatLab gray 8-bit MSB integer) ...\n");
++$test;
testRead('input_gray_msb_08bit.mat', q//,
         'cd0e75dd75bce03537c17bf067e19e97d1e28feb18a5ba54dddaf3309097c255');

print("MAT (MatLab gray 16-bit LSB integer) ...\n");
++$test;
testRead('input_gray_lsb_16bit.mat', q//,
         'acfbc25e7afd4b80db3e961fe4432cc9acab0d8f599728593ee950cb9099b10e',
         'ee9617706ce2af8c4f40536d6e0f17626c5b080f5af4ed7a05f72445fb9dd3ca',);

print("MAT (MatLab gray 32-bit LSB integer) ...\n");
++$test;
testRead('input_gray_lsb_32bit.mat', q//,
         'fb49d38988edb04b20bfa89c5e16378c3e18c559716194f2c9c712f8f232b11f',
         '33fe0fb5e1dc38f8b74dce16a854a54bd2ea33052bf73ced9736ee86f3e6d0a8',
         'b46acb2a1e91421d06f3c2a094f3e31eaa304721dba57890472c822b14da4abc');

print("MAT (MatLab gray 32-bit LSB float) ...\n");
++$test;
testReadCompare('input_gray_lsb_float.mat', 'reference/read/input_gray_lsb_float_mat.miff', q//, 0.002, 0.004);

print("MAT (MatLab gray 64-bit LSB double) ...\n");
++$test;
testReadCompare('input_gray_lsb_double.mat', 'reference/read/input_gray_lsb_double_mat.miff', q//, 0.002, 0.004);

print("MAT (MatLab RGB 8-bit LSB integer) ...\n");
++$test;
testRead('input_rgb_lsb_08bit.mat', q//,
         'b21cb1b0ea0d446adfccf3552a66e39e8d46c2c0e7b5af1429f942b83336d83e');

print("MAT (MatLab V4 gray 64-bit LSB double) ...\n");
++$test;
testReadCompare('input_gray_lsb_double_V4.mat', 'reference/read/input_gray_lsb_double_V4_mat.miff', q//, 0.002, 0.004);

print("Microsoft icon ...\n");
++$test;
testRead('input.ico', q//,
         'a8b1aae465606b8273caf1035f95b7c1262bcb1f72fcb73bfe2d3640ff6b45ef');

print("Magick image file format ...\n");
++$test;
testRead('input.miff', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("MTV Raytracing image format ...\n");
++$test;
testRead('input.mtv', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Xv's visual schnauzer format. ...\n");
++$test;
testRead('input_p7.p7', q//,
         'dd9c40cefab0af4261bc9fe774c60323f32fe28359fc7a941b7545eb4989dd1c',
         'e737f462f4f806207d5bf9453fe1ce3b16057ab4d740b7614c111312a87f1df3',
         '54dd757ae221326ec39372293eee90fd29f586d8371e4a4925a246f17c2f838e');

print("NULL (white image) ...\n");
++$test;
testRead('NULL:white', q/size=>"70x46", depth=>8/,
         ,'40db28af0162a4abd3ee8a1094591cd7eb07463464d7c235e4c2f2ae40aa3686');

print("NULL (black image) ...\n");
++$test;
testRead('NULL:black', q/size=>"70x46", depth=>8/,
         'd7e8478261a01c7f4c4f6bbb172976d1bd585c1b43195cdb65bafb008f71b5c6');

print("NULL (DarkOrange image) ...\n");
++$test;
testRead('NULL:DarkOrange', q/size=>"70x46", depth=>8/,
         '316efde44dfeba05dc384fcfcaf72df768811ec4132190484b9f64d43a6fc784');

print("Portable bitmap format (black and white), ASCII format ...\n");
++$test;
testRead('input_p1.pbm', q//,
         '2b48bcf7d93cc31a8deb3026d872f1bb0a300b0f4e177423e5301adc638179e4');

print("Portable bitmap format (black and white), binary format ...\n");
++$test;
testRead('input_p4.pbm', q//,
         '2b48bcf7d93cc31a8deb3026d872f1bb0a300b0f4e177423e5301adc638179e4');

print("ZSoft IBM PC Paintbrush file ...\n");
++$test;
testRead('input.pcx', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Portable graymap format (gray scale), ASCII format ...\n");
++$test;
testRead('input_p2.pgm', q//,
         '04c5604964838e47aba7a355efee266a4d0f1b90f672ff56863440e5e5a29761');

print("Portable graymap format (gray scale), binary format ...\n");
++$test;
testRead('input_p5.pgm', q//,
         '04c5604964838e47aba7a355efee266a4d0f1b90f672ff56863440e5e5a29761');

print("Apple Macintosh QuickDraw/PICT file ...\n");
++$test;
testRead('input.pict', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Alias/Wavefront RLA image format (gray scale) ...\n");
++$test;
testRead('input_gray.rla', q//,
         '04c5604964838e47aba7a355efee266a4d0f1b90f672ff56863440e5e5a29761');

print("Alias/Wavefront RLA image format (RGB) ...\n");
++$test;
testRead('input_rgb.rla', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Utah Raster Toolkit (URT) RLE image format (gray scale) ...\n");
++$test;
testRead('input_gray.rle', q//,
         '04c5604964838e47aba7a355efee266a4d0f1b90f672ff56863440e5e5a29761');

print("Utah Raster Toolkit (URT) RLE image format (RGB) ...\n");
++$test;
testRead('input.rle', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Portable pixmap format (color), ASCII format ...\n");
++$test;
testRead('input_p3.ppm', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Portable pixmap format (color), binary format ...\n");
++$test;
testRead('input_p6.ppm', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Adobe Photoshop bitmap file ...\n");
++$test;
if (featureSupported("PSD")) {
    testReadCompare('input.psd', 'reference/read/input_psd.miff', q//, 0, 0);
} else {
    print "ok $test # skip PSD not supported\n";
}

print("Irix RGB image file ...\n");
++$test;
testRead('input.sgi', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("SUN 1-bit Rasterfile ...\n");
++$test;
testRead('input.im1', q//,
         '86cf46ab9d620aa85eba722d777cc97e30df51916b2380df3cbc2685614d1222');

print("SUN 8-bit Rasterfile ...\n");
++$test;
testRead('input.im8', q//,
         'f84cb6b5817ea2f6f313c2bdd90c94af0d0e7fb144528994050b355f8d5e6a94');

print("SUN TrueColor Rasterfile ...\n");
++$test;
testRead('sun:input.im24', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Topol Type 1 ...\n");
++$test;
testRead('topol:topol_1.ras', q//,
         'e2536d9d7c2e0c165d0a6df496bae51c1504d97a33710d3f45f2d52b9e0b8fa9');

print("Topol Type 2 ...\n");
++$test;
testRead('topol:topol_2.ras', q//,
         '8ae260ecdb635805d1c8229d1449aed23ee80bb39418afd9a1eba7851f1a0c24');

print("Topol Type 3 ...\n");
++$test;
testRead('topol:topol_3.ras', q//,
         '4ed70370bb01f4254998850ca534baea9d87636f86b72d1da0e8058ca235ee19');

print("Topol Type 4 ...\n");
++$test;
testRead('topol:topol_4.ras', q//,
         '469b1bd65fe6ada689f9929527d6dc5629e4f1a581f55c00a2efc8341ed71603');

print("Topol Type 5 ...\n");
++$test;
testRead('topol:topol_5.ras', q//,
         '984eca4cc8f863c60c3981b75d6d3212c6700a95bc6651094e69d64768d51958');

print("Topol Type 7 ...\n");
++$test;
testRead('topol:topol_7.ras', q//,
         'e54d28e80d0ed61dd7010c3bfc542897b2f9218062cfc19a509b7ff955025f53');

print("Truevision Targa image file (true color) ...\n");
++$test;
testRead('input_24.tga', q//,
         'ee9a91e1f87a45484a65350b1079fdc3dd0c6d72b9443068c7751cd621189122');

print("Truevision Targa image file (true color - RLE compressed) ...\n");
++$test;
testRead('input_24rle.tga', q//,
         'ee9a91e1f87a45484a65350b1079fdc3dd0c6d72b9443068c7751cd621189122');

print("Truevision Targa image file (true color 16) ...\n");
++$test;
testRead('input_16.tga', q//,
         'cfcd894d32c55b9335ceeb52f4048bc1901720a6c49bbb9d722763cdd0b46689');

print("Truevision Targa image file (true color 16 - RLE compressed) ...\n");
++$test;
testRead('input_16rle.tga', q//,
         'cfcd894d32c55b9335ceeb52f4048bc1901720a6c49bbb9d722763cdd0b46689');

print("Truevision Targa image file (palette color) ...\n");
++$test;
testRead('input_8_CC.tga', q//,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("Truevision Targa image file (gray) ...\n");
++$test;
testRead('input_8_BW.tga', q//,
         'eb6fc4bbf01284d9e8a9e065435ba79507bcbbafb8823293ea99ea9ee6f407bc');

print("Truevision Targa image file (bilevel) ...\n");
++$test;
testRead('input_mono.tga', q//,
         '34c6d81d5dd096d4f2ec80ce0e2b089131870527c54a1c6837809ff67173c413');

print("PSX TIM file ...\n");
++$test;
testRead('input.tim', q//,
         'c344efd8deda6507e2ea960bf31bff8e22fc3688a1721e8b8ef932c0d98c3979');

print("Khoros Visualization image file ...\n");
++$test;
testRead('input.viff', q//,
         '9c01e510e4aa7c369895db51389ae917a0d4f9004ffb4edf81e5e2302cab98a3');

print("WBMP (Wireless Bitmap (level 0) image) ...\n");
++$test;
testRead('input.wbmp', q//,
         'ccde39dba836a36bbc076e7e6f20f06b034dab0eb2613b350b17c2759533b2ca');

print("WPG (Word Perfect Graphics image, bilevel WPG level 1) ...\n");
++$test;
testRead('input1_1.wpg', q//,
         '24f136b95afc7c11b9d5e1a22c4b53030b7aced49bf83eebaa5985128e0600f3');

print("WPG (Word Perfect Graphics image, 4 bit depth WPG level 1) ...\n");
++$test;
testRead('input1_4.wpg', q//,
         '27b4d537ef0fac232f1f9cb8bc1b3e1378d6804a43d4b813770119cd6146e225');

print("WPG (Word Perfect Graphics image, 8 bit depth WPG level 1) ...\n");
++$test;
testRead('input1_8_1.wpg', q//,
         '6c8a6e6e237e03a636e976b3a04fcab56470854d6051b8959bd968b526843c48');

print("WPG (Word Perfect Graphics image, 1 bit depth + 24 bit depth WPG level 2) ...\n");
++$test;
testRead('input2_TC1.wpg', q//,
         '6c8a6e6e237e03a636e976b3a04fcab56470854d6051b8959bd968b526843c48');

print("WPG (Word Perfect Graphics image, 8 bit depth WPG level 2) ...\n");
++$test;
testRead('input2_8.wpg', q//,
         '1cfa3408a18d263034abf11862d6c5e2a92c0cb0b7a067479709013ae0df9af6');

print("X Windows system bitmap (black and white only) ...\n");
++$test;
testRead('input.xbm', q//,
         '86cf46ab9d620aa85eba722d777cc97e30df51916b2380df3cbc2685614d1222');

print("XC: Constant image of X server color ...\n");
++$test;
testRead('xc:black', q/size=>"70x46", depth=>8/, ,'d7e8478261a01c7f4c4f6bbb172976d1bd585c1b43195cdb65bafb008f71b5c6');

print("X Windows system pixmap file (bilevel) ...\n");
++$test;
testRead('input_bilevel.xpm', q//,
         'c100134c37f7d48c2908747f40f4f18e63a00ebf2b6124cdbe63f078bc74cc5f');

print("X Windows system pixmap file (color) ...\n");
++$test;
testRead('input.xpm', q//,
         'f84cb6b5817ea2f6f313c2bdd90c94af0d0e7fb144528994050b355f8d5e6a94');

print("X Windows system pixmap file (color, 16bit palette) ...\n");
++$test;
testRead('input_pal16.xpm', q//,
         '45f0083676dcd95255f24b897df490a310a28f8f180c86ba2450e1624656f1f8');

print("X Windows system pixmap file (color, 3 chars per pixel) ...\n");
++$test;
testRead('input_3chars.xpm', q//,
         '3716883efcd24e9ea3500febb299b77a86484574a6b81e11707e6b06d3c208f7');

#print("X Windows system window dump file (color) ...\n");
#++$test;
#testReadCompare('input.xwd', 'reference/read/input_xwd.miff', q//, 0, 0);

print("TILE (Tile image with a texture) ...\n");
# This is an internal generated format
# We will tile using the default image and a MIFF file
#
++$test;
testRead('TILE:input.miff', q/size=>"140x92", depth=>8/,
         'e1384a6f9f75d4a86f6291c47171a9039972718d9e5092294746cca57fd7b02e');

print("CMYK format ...\n");
++$test;
testRead('input_70x46.cmyk', q/size=>"70x46", depth=>8/,
         '1a1b99a35b962941e2a1cfc01e34907539f6d6ddc4a8df09fc024ef58e16d4e2');

print("GRAY format ...\n");
++$test;
testRead('input_70x46.gray', q/size=>"70x46", depth=>8/,
         '0e54b24352da9f7d0966c9b882988b9124b6b7fd7493ff266f4c03382b94a42a');

print("RGB format ...\n");
++$test;
testRead('input_70x46.rgb',  q/size=>"70x46", depth=>8/,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("RGBA format ...\n");
++$test;
testRead('input_70x46.rgba',  q/size=>"70x46", depth=>8/,
         '8b19185a62241bd7b79ecf3f619711f4ebbedd73eaeca0366f05778762b6614f');

print("UYVY format ...\n");
++$test;
testReadCompare('input_70x46.uyvy', 'reference/read/input_uyvy.miff',
                q/size=>"70x46", depth=>8/,
                #0.006, 0.008
                0.022, 0.817 # FIXME: Messed up somehow!
    );

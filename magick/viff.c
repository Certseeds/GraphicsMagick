/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                        V   V  IIIII  FFFFF  FFFFF                           %
%                        V   V    I    F      F                               %
%                        V   V    I    FFF    FFF                             %
%                         V V     I    F      F                               %
%                          V    IIIII  F      F                               %
%                                                                             %
%                                                                             %
%                    Read/Write ImageMagick Image Format.                     %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1992                                   %
%                                                                             %
%                                                                             %
%  Copyright 1999 E. I. du Pont de Nemours and Company                        %
%                                                                             %
%  Permission is hereby granted, free of charge, to any person obtaining a    %
%  copy of this software and associated documentation files ("ImageMagick"),  %
%  to deal in ImageMagick without restriction, including without limitation   %
%  the rights to use, copy, modify, merge, publish, distribute, sublicense,   %
%  and/or sell copies of ImageMagick, and to permit persons to whom the       %
%  ImageMagick is furnished to do so, subject to the following conditions:    %
%                                                                             %
%  The above copyright notice and this permission notice shall be included in %
%  all copies or substantial portions of ImageMagick.                         %
%                                                                             %
%  The software is provided "as is", without warranty of any kind, express or %
%  implied, including but not limited to the warranties of merchantability,   %
%  fitness for a particular purpose and noninfringement.  In no event shall   %
%  E. I. du Pont de Nemours and Company be liable for any claim, damages or   %
%  other liability, whether in an action of contract, tort or otherwise,      %
%  arising from, out of or in connection with ImageMagick or the use or other %
%  dealings in ImageMagick.                                                   %
%                                                                             %
%  Except as contained in this notice, the name of the E. I. du Pont de       %
%  Nemours and Company shall not be used in advertising or otherwise to       %
%  promote the sale, use or other dealings in ImageMagick without prior       %
%  written authorization from the E. I. du Pont de Nemours and Company.       %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/

/*
  Include declarations.
*/
#include "magick.h"
#include "defines.h"
#include "proxy.h"

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d V I F F I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadVIFFImage reads a Khoros Visualization image file and returns
%  it.  It allocates the memory necessary for the new Image structure and
%  returns a pointer to the new image.
%
%  The format of the ReadVIFFImage routine is:
%
%      image=ReadVIFFImage(image_info)
%
%  A description of each parameter follows:
%
%    o image: Method ReadVIFFImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or if
%      the image cannot be read.
%
%    o filename: Specifies the name of the image to read.
%
%
*/
Export Image *ReadVIFFImage(const ImageInfo *image_info)
{
#define VFF_CM_genericRGB  15
#define VFF_CM_ntscRGB  1
#define VFF_CM_NONE  0
#define VFF_DEP_DECORDER  0x4
#define VFF_DEP_NSORDER  0x8
#define VFF_DES_RAW  0
#define VFF_LOC_IMPLICIT  1
#define VFF_MAPTYP_NONE  0
#define VFF_MAPTYP_1_BYTE  1
#define VFF_MS_NONE  0
#define VFF_MS_ONEPERBAND  1
#define VFF_MS_SHARED  3
#define VFF_TYP_BIT  0
#define VFF_TYP_1_BYTE  1
#define VFF_TYP_2_BYTE  2
#define VFF_TYP_4_BYTE  4

  typedef struct _ViffHeader
  {
    unsigned char
      identifier,
      file_type,
      release,
      version,
      machine_dependency,
      reserve[3];

    char
      comment[512];

    unsigned long
      rows,
      columns,
      subrows;

    long
      x_offset,
      y_offset;

    float
      x_bits_per_pixel,
      y_bits_per_pixel;

    unsigned long
      location_type,
      location_dimension,
      number_of_images,
      number_data_bands,
      data_storage_type,
      data_encode_scheme,
      map_scheme,
      map_storage_type,
      map_rows,
      map_columns,
      map_subrows,
      map_enable,
      maps_per_cycle,
      color_space_model;
  } ViffHeader;

  Image
    *image;

  register int
    bit,
    i,
    x,
    y;

  register Quantum
    *p;

  register RunlengthPacket
    *q;

  unsigned char
    buffer[7],
    *viff_pixels;

  unsigned int
    bytes_per_pixel,
    status;

  unsigned long
    max_packets;

  ViffHeader
    viff_header;

  /*
    Allocate image structure.
  */
  image=AllocateImage(image_info);
  if (image == (Image *) NULL)
    return((Image *) NULL);
  /*
    Open image file.
  */
  OpenImage(image_info,image,ReadBinaryType);
  if (image->file == (FILE *) NULL)
    ReaderExit(FileOpenWarning,"Unable to open file",image);
  /*
    Read VIFF header (1024 bytes).
  */
  status=ReadData((char *) &viff_header.identifier,1,1,image->file);
  do
  {
    /*
      Verify VIFF identifier.
    */
    if ((status == False) || ((unsigned char) viff_header.identifier != 0xab))
      ReaderExit(CorruptImageWarning,"Not a VIFF raster",image);
    /*
      Initialize VIFF image.
    */
    (void) ReadData((char *) buffer,1,7,image->file);
    viff_header.file_type=buffer[0];
    viff_header.release=buffer[1];
    viff_header.version=buffer[2];
    viff_header.machine_dependency=buffer[3];
    (void) ReadData((char *) viff_header.comment,1,512,image->file);
    viff_header.comment[511]='\0';
    if (Extent(viff_header.comment) > 4)
      (void) CloneString(&image->comments,viff_header.comment);
    if ((viff_header.machine_dependency == VFF_DEP_DECORDER) ||
        (viff_header.machine_dependency == VFF_DEP_NSORDER))
      {
        viff_header.rows=LSBFirstReadLong(image->file);
        viff_header.columns=LSBFirstReadLong(image->file);
        viff_header.subrows=LSBFirstReadLong(image->file);
        viff_header.x_offset=(long) LSBFirstReadLong(image->file);
        viff_header.y_offset=(long) LSBFirstReadLong(image->file);
        viff_header.x_bits_per_pixel=(float) LSBFirstReadLong(image->file);
        viff_header.y_bits_per_pixel=(float) LSBFirstReadLong(image->file);
        viff_header.location_type=LSBFirstReadLong(image->file);
        viff_header.location_dimension=LSBFirstReadLong(image->file);
        viff_header.number_of_images=LSBFirstReadLong(image->file);
        viff_header.number_data_bands=LSBFirstReadLong(image->file);
        viff_header.data_storage_type=LSBFirstReadLong(image->file);
        viff_header.data_encode_scheme=LSBFirstReadLong(image->file);
        viff_header.map_scheme=LSBFirstReadLong(image->file);
        viff_header.map_storage_type=LSBFirstReadLong(image->file);
        viff_header.map_rows=LSBFirstReadLong(image->file);
        viff_header.map_columns=LSBFirstReadLong(image->file);
        viff_header.map_subrows=LSBFirstReadLong(image->file);
        viff_header.map_enable=LSBFirstReadLong(image->file);
        viff_header.maps_per_cycle=LSBFirstReadLong(image->file);
        viff_header.color_space_model=LSBFirstReadLong(image->file);
      }
    else
      {
        viff_header.rows=MSBFirstReadLong(image->file);
        viff_header.columns=MSBFirstReadLong(image->file);
        viff_header.subrows=MSBFirstReadLong(image->file);
        viff_header.x_offset=(long) MSBFirstReadLong(image->file);
        viff_header.y_offset=(long) MSBFirstReadLong(image->file);
        viff_header.x_bits_per_pixel=(float) MSBFirstReadLong(image->file);
        viff_header.y_bits_per_pixel=(float) MSBFirstReadLong(image->file);
        viff_header.location_type=MSBFirstReadLong(image->file);
        viff_header.location_dimension=MSBFirstReadLong(image->file);
        viff_header.number_of_images=MSBFirstReadLong(image->file);
        viff_header.number_data_bands=MSBFirstReadLong(image->file);
        viff_header.data_storage_type=MSBFirstReadLong(image->file);
        viff_header.data_encode_scheme=MSBFirstReadLong(image->file);
        viff_header.map_scheme=MSBFirstReadLong(image->file);
        viff_header.map_storage_type=MSBFirstReadLong(image->file);
        viff_header.map_rows=MSBFirstReadLong(image->file);
        viff_header.map_columns=MSBFirstReadLong(image->file);
        viff_header.map_subrows=MSBFirstReadLong(image->file);
        viff_header.map_enable=MSBFirstReadLong(image->file);
        viff_header.maps_per_cycle=MSBFirstReadLong(image->file);
        viff_header.color_space_model=MSBFirstReadLong(image->file);
      }
    for (i=0; i < 420; i++)
      (void) fgetc(image->file);
    image->columns=(unsigned int) viff_header.rows;
    image->rows=(unsigned int) viff_header.columns;
    /*
      Verify that we can read this VIFF image.
    */
    if ((viff_header.columns*viff_header.rows) == 0)
      ReaderExit(CorruptImageWarning,
        "Image column or row size is not supported",image);
    if ((viff_header.data_storage_type != VFF_TYP_BIT) &&
        (viff_header.data_storage_type != VFF_TYP_1_BYTE) &&
        (viff_header.data_storage_type != VFF_TYP_2_BYTE) &&
        (viff_header.data_storage_type != VFF_TYP_4_BYTE))
      ReaderExit(CorruptImageWarning,
        "Data storage type is not supported",image);
    if (viff_header.data_encode_scheme != VFF_DES_RAW)
      ReaderExit(CorruptImageWarning,
        "Data encoding scheme is not supported",image);
    if ((viff_header.map_storage_type != VFF_MAPTYP_NONE) &&
        (viff_header.map_storage_type != VFF_MAPTYP_1_BYTE))
      ReaderExit(CorruptImageWarning,
        "Map storage type is not supported",image);
    if ((viff_header.color_space_model != VFF_CM_NONE) &&
        (viff_header.color_space_model != VFF_CM_ntscRGB) &&
        (viff_header.color_space_model != VFF_CM_genericRGB))
      ReaderExit(CorruptImageWarning,
        "Colorspace model is not supported",image);
    if (viff_header.location_type != VFF_LOC_IMPLICIT)
      {
        MagickWarning(CorruptImageWarning,
          "Location type is not supported",image->filename);
        DestroyImages(image);
        return((Image *) NULL);
      }
    if (viff_header.number_of_images != 1)
      ReaderExit(CorruptImageWarning,
        "Number of images is not supported",image);
    switch (viff_header.map_scheme)
    {
      case VFF_MS_NONE:
      {
        if (viff_header.number_data_bands < 3)
          {
            /*
              Create linear color ramp.
            */
            if (viff_header.data_storage_type == VFF_TYP_BIT)
              image->colors=2;
            else
              image->colors=1 << (viff_header.number_data_bands*QuantumDepth);
            image->colormap=(ColorPacket *)
              AllocateMemory(image->colors*sizeof(ColorPacket));
            if (image->colormap == (ColorPacket *) NULL)
              ReaderExit(ResourceLimitWarning,"Memory allocation failed",
                image);
            for (i=0; i < (int) image->colors; i++)
            {
              image->colormap[i].red=(MaxRGB*i)/(image->colors-1);
              image->colormap[i].green=(MaxRGB*i)/(image->colors-1);
              image->colormap[i].blue=(MaxRGB*i)/(image->colors-1);
            }
          }
        break;
      }
      case VFF_MS_ONEPERBAND:
      case VFF_MS_SHARED:
      {
        unsigned char
          *viff_colormap;

        /*
          Read VIFF raster colormap.
        */
        image->colors=(unsigned int) viff_header.map_columns;
        image->colormap=(ColorPacket *)
          AllocateMemory(image->colors*sizeof(ColorPacket));
        viff_colormap=(unsigned char *)
          AllocateMemory(image->colors*sizeof(unsigned char));
        if ((image->colormap == (ColorPacket *) NULL) ||
            (viff_colormap == (unsigned char *) NULL))
          ReaderExit(ResourceLimitWarning,"Memory allocation failed",image);
        (void) ReadData((char *) viff_colormap,1,image->colors,image->file);
        for (i=0; i < (int) image->colors; i++)
        {
          image->colormap[i].red=UpScale(viff_colormap[i]);
          image->colormap[i].green=UpScale(viff_colormap[i]);
          image->colormap[i].blue=UpScale(viff_colormap[i]);
        }
        if (viff_header.map_rows > 1)
          {
            (void) ReadData((char *) viff_colormap,1,image->colors,image->file);
            for (i=0; i < (int) image->colors; i++)
              image->colormap[i].green=UpScale(viff_colormap[i]);
          }
        if (viff_header.map_rows > 2)
          {
            (void) ReadData((char *) viff_colormap,1,image->colors,image->file);
            for (i=0; i < (int) image->colors; i++)
              image->colormap[i].blue=UpScale(viff_colormap[i]);
          }
        FreeMemory((char *) viff_colormap);
        break;
      }
      default:
        ReaderExit(CorruptImageWarning,"Colormap type is not supported",
          image);
    }
    /*
      Allocate VIFF pixels.
    */
    bytes_per_pixel=1;
    if (viff_header.data_storage_type == VFF_TYP_2_BYTE)
      bytes_per_pixel=2;
    if (viff_header.data_storage_type == VFF_TYP_4_BYTE)
      bytes_per_pixel=4;
    if (viff_header.data_storage_type == VFF_TYP_BIT)
      max_packets=((viff_header.columns+7) >> 3)*viff_header.rows;
    else
      max_packets=
        viff_header.columns*viff_header.rows*viff_header.number_data_bands;
    viff_pixels=(unsigned char *)
      AllocateMemory(bytes_per_pixel*max_packets*sizeof(Quantum));
    if (viff_pixels == (unsigned char *) NULL)
      ReaderExit(ResourceLimitWarning,"Memory allocation failed",image);
    (void) ReadData((char *) viff_pixels,bytes_per_pixel,(unsigned int)
      max_packets,image->file);
    switch (viff_header.data_storage_type)
    {
      int
        max_value,
        min_value,
        value;

      register Quantum
        *q;

      unsigned long
        scale_factor;

      case VFF_TYP_1_BYTE:
      {
        register unsigned char
          *p;

        if (QuantumDepth == 8)
          break;
        /*
          Scale integer pixels to [0..MaxRGB].
        */
        p=viff_pixels;
        q=(Quantum *) viff_pixels;
        p+=max_packets-1;
        q+=max_packets-1;
        for (i=0; i < (int) max_packets; i++)
        {
          value=UpScale(*p);
          *q=(Quantum) value;
          p--;
          q--;
        }
        break;
      }
      case VFF_TYP_2_BYTE:
      {
        register short int
          *p;

        /*
          Ensure the header byte-order is most-significant byte first.
        */
        if ((viff_header.machine_dependency == VFF_DEP_DECORDER) ||
            (viff_header.machine_dependency == VFF_DEP_NSORDER))
          MSBFirstOrderShort((char *) &viff_header,
            (unsigned int) (bytes_per_pixel*max_packets));
        /*
          Determine scale factor.
        */
        p=(short int *) viff_pixels;
        max_value=(*p);
        min_value=(*p);
        for (i=0; i < (int) max_packets; i++)
        {
          if (*p > max_value)
            max_value=(*p);
          else
            if (*p < min_value)
              min_value=(*p);
          p++;
        }
        if ((min_value == 0) && (max_value == 0))
          scale_factor=0;
        else
          if (min_value == max_value)
            {
              scale_factor=UpShift(MaxRGB)/min_value;
              min_value=0;
            }
          else
            scale_factor=UpShift(MaxRGB)/(max_value-min_value);
        /*
          Scale integer pixels to [0..MaxRGB].
        */
        p=(short int *) viff_pixels;
        q=(Quantum *) viff_pixels;
        for (i=0; i < (int) max_packets; i++)
        {
          value=DownShift((*p-min_value)*scale_factor);
          if (value > MaxRGB)
            value=MaxRGB;
          else
            if (value < 0)
              value=0;
          *q=(Quantum) value;
          p++;
          q++;
        }
        break;
      }
      case VFF_TYP_4_BYTE:
      {
        register int
          *p;

        /*
          Ensure the header byte-order is most-significant byte first.
        */
        if ((viff_header.machine_dependency == VFF_DEP_DECORDER) ||
            (viff_header.machine_dependency == VFF_DEP_NSORDER))
          MSBFirstOrderLong((char *) &viff_header,
            (unsigned int) (bytes_per_pixel*max_packets));
        /*
          Determine scale factor.
        */
        p=(int *) viff_pixels;
        max_value=(*p);
        min_value=(*p);
        for (i=0; i < (int) max_packets; i++)
        {
          if (*p > max_value)
            max_value=(*p);
          else
            if (*p < min_value)
              min_value=(*p);
          p++;
        }
        if ((min_value == 0) && (max_value == 0))
          scale_factor=0;
        else
          if (min_value == max_value)
            {
              scale_factor=UpShift(MaxRGB)/min_value;
              min_value=0;
            }
          else
            scale_factor=UpShift(MaxRGB)/(max_value-min_value);
        /*
          Scale integer pixels to [0..MaxRGB].
        */
        p=(int *) viff_pixels;
        q=(Quantum *) viff_pixels;
        for (i=0; i < (int) max_packets; i++)
        {
          value=DownShift((*p-min_value)*scale_factor);
          if (value > MaxRGB)
            value=MaxRGB;
          else
            if (value < 0)
              value=0;
          *q=(unsigned char) value;
          p++;
          q++;
        }
        break;
      }
    }
    /*
      Initialize image structure.
    */
    image->matte=(viff_header.number_data_bands == 4);
    image->class=
      (viff_header.number_data_bands < 3 ? PseudoClass : DirectClass);
    image->columns=(unsigned int) viff_header.rows;
    image->rows=(unsigned int) viff_header.columns;
    if (image_info->ping)
      {
        CloseImage(image);
        return(image);
      }
    image->packets=image->columns*image->rows;
    image->pixels=(RunlengthPacket *)
      AllocateMemory(image->packets*sizeof(RunlengthPacket));
    if (image->pixels == (RunlengthPacket *) NULL)
      ReaderExit(ResourceLimitWarning,"Memory allocation failed",image);
    SetImage(image);
    /*
      Convert VIFF raster image to runlength-encoded packets.
    */
    p=(Quantum *) viff_pixels;
    q=image->pixels;
    if (viff_header.data_storage_type == VFF_TYP_BIT)
      {
        unsigned int
          polarity;

        /*
          Convert bitmap scanline to runlength-encoded color packets.
        */
        polarity=(viff_header.machine_dependency == VFF_DEP_DECORDER) ||
          (viff_header.machine_dependency == VFF_DEP_NSORDER);
        for (y=0; y < (int) image->rows; y++)
        {
          /*
            Convert bitmap scanline to runlength-encoded color packets.
          */
          for (x=0; x < (int) (image->columns >> 3); x++)
          {
            for (bit=0; bit < 8; bit++)
            {
              q->index=
                ((*p) & (0x01 << bit) ? (int) polarity : (int) !polarity);
              q->length=0;
              q++;
            }
            p++;
          }
          if ((image->columns % 8) != 0)
            {
              for (bit=0; bit < (int) (image->columns % 8); bit++)
              {
                q->index=
                  ((*p) & (0x01 << bit) ? (int) polarity : (int) !polarity);
                q->length=0;
                q++;
              }
              p++;
            }
          if (image->previous == (Image *) NULL)
            if (QuantumTick(y,image->rows))
              ProgressMonitor(LoadImageText,y,image->rows);
        }
      }
    else
      if (image->class == PseudoClass)
        for (y=0; y < (int) image->rows; y++)
        {
          /*
            Convert PseudoColor scanline to runlength-encoded color packets.
          */
          for (x=0; x < (int) image->columns; x++)
          {
            q->index=(*p++);
            q->length=0;
            q++;
          }
          if (image->previous == (Image *) NULL)
            if (QuantumTick(y,image->rows))
              ProgressMonitor(LoadImageText,y,image->rows);
        }
      else
        {
          unsigned long
            offset;

          /*
            Convert DirectColor scanline to runlength-encoded color packets.
          */
          offset=image->columns*image->rows;
          for (y=0; y < (int) image->rows; y++)
          {
            for (x=0; x < (int) image->columns; x++)
            {
              q->red=(*p);
              q->green=(*(p+offset));
              q->blue=(*(p+offset*2));
              if (image->colors != 0)
                {
                  q->red=image->colormap[q->red].red;
                  q->green=image->colormap[q->green].green;
                  q->blue=image->colormap[q->blue].blue;
                }
              q->index=(unsigned short) (image->matte ? (*(p+offset*3)) : 0);
              q->length=0;
              p++;
              q++;
            }
            if (image->previous == (Image *) NULL)
              if (QuantumTick(y,image->rows))
                ProgressMonitor(LoadImageText,y,image->rows);
          }
        }
    FreeMemory((char *) viff_pixels);
    if (image->class == PseudoClass)
      SyncImage(image);
    CondenseImage(image);
    /*
      Proceed to next image.
    */
    if (image_info->subrange != 0)
      if (image->scene >= (image_info->subimage+image_info->subrange-1))
        break;
    status=ReadData((char *) &viff_header.identifier,1,1,image->file);
    if ((status == True) && (viff_header.identifier == 0xab))
      {
        /*
          Allocate next image structure.
        */
        AllocateNextImage(image_info,image);
        if (image->next == (Image *) NULL)
          {
            DestroyImages(image);
            return((Image *) NULL);
          }
        image=image->next;
        ProgressMonitor(LoadImagesText,(unsigned int) ftell(image->file),
          (unsigned int) image->filesize);
      }
  } while ((status == True) && (viff_header.identifier == 0xab));
  while (image->previous != (Image *) NULL)
    image=image->previous;
  CloseImage(image);
  return(image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e V I F F I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WriteVIFFImage writes an image to a file in the VIFF image format.
%
%  The format of the WriteVIFFImage routine is:
%
%      status=WriteVIFFImage(image_info,image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteVIFFImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to an ImageInfo structure.
%
%    o image:  A pointer to a Image structure.
%
%
*/
Export unsigned int WriteVIFFImage(const ImageInfo *image_info,Image *image)
{
#define VFF_CM_genericRGB  15
#define VFF_CM_NONE  0
#define VFF_DEP_IEEEORDER  0x2
#define VFF_DES_RAW  0
#define VFF_LOC_IMPLICIT  1
#define VFF_MAPTYP_NONE  0
#define VFF_MAPTYP_1_BYTE  1
#define VFF_MS_NONE  0
#define VFF_MS_ONEPERBAND  1
#define VFF_TYP_BIT  0
#define VFF_TYP_1_BYTE  1

  typedef struct _ViffHeader
  {
    char
      identifier,
      file_type,
      release,
      version,
      machine_dependency,
      reserve[3],
      comment[512];

    unsigned long
      rows,
      columns,
      subrows;

    long
      x_offset,
      y_offset;

    unsigned int
      x_bits_per_pixel,
      y_bits_per_pixel;

    unsigned long
      location_type,
      location_dimension,
      number_of_images,
      number_data_bands,
      data_storage_type,
      data_encode_scheme,
      map_scheme,
      map_storage_type,
      map_rows,
      map_columns,
      map_subrows,
      map_enable,
      maps_per_cycle,
      color_space_model;
  } ViffHeader;

  register int
    i,
    j;

  register RunlengthPacket
    *p;

  register unsigned char
    *q;

  unsigned char
    buffer[8],
    *viff_pixels;

  unsigned int
    scene;

  unsigned long
    packets;

  ViffHeader
    viff_header;

  /*
    Open output image file.
  */
  OpenImage(image_info,image,WriteBinaryType);
  if (image->file == (FILE *) NULL)
    WriterExit(FileOpenWarning,"Unable to open file",image);
  scene=0;
  do
  {
    /*
      Initialize VIFF image structure.
    */
    TransformRGBImage(image,RGBColorspace);
    viff_header.identifier=(char) 0xab;
    viff_header.file_type=1;
    viff_header.release=1;
    viff_header.version=3;
    viff_header.machine_dependency=VFF_DEP_IEEEORDER;  /* IEEE byte ordering */
    *viff_header.comment='\0';
    if (image->comments != (char *) NULL)
      {
        (void) strncpy(viff_header.comment,image->comments,
          Min(Extent(image->comments),511));
        viff_header.comment[Min(Extent(image->comments),511)]='\0';
      }
    viff_header.rows=image->columns;
    viff_header.columns=image->rows;
    viff_header.subrows=0;
    viff_header.x_offset=(~0);
    viff_header.y_offset=(~0);
    viff_header.x_bits_per_pixel=0;
    viff_header.y_bits_per_pixel=0;
    viff_header.location_type=VFF_LOC_IMPLICIT;
    viff_header.location_dimension=0;
    viff_header.number_of_images=1;
    viff_header.data_encode_scheme=VFF_DES_RAW;
    viff_header.map_scheme=VFF_MS_NONE;
    viff_header.map_storage_type=VFF_MAPTYP_NONE;
    viff_header.map_rows=0;
    viff_header.map_columns=0;
    viff_header.map_subrows=0;
    viff_header.map_enable=1;  /* no colormap */
    viff_header.maps_per_cycle=0;
    if (!IsPseudoClass(image) && !IsGrayImage(image))
      {
        /*
          Full color VIFF raster.
        */
        viff_header.number_data_bands=image->matte ? 4 : 3;
        viff_header.color_space_model=VFF_CM_genericRGB;
        viff_header.data_storage_type=VFF_TYP_1_BYTE;
        packets=image->columns*image->rows*viff_header.number_data_bands;
      }
    else
      {
        viff_header.number_data_bands=1;
        viff_header.color_space_model=VFF_CM_NONE;
        viff_header.data_storage_type=VFF_TYP_1_BYTE;
        packets=image->columns*image->rows;
        if (!IsGrayImage(image))
          {
            /*
              Colormapped VIFF raster.
            */
            viff_header.map_scheme=VFF_MS_ONEPERBAND;
            viff_header.map_storage_type=VFF_MAPTYP_1_BYTE;
            viff_header.map_rows=3;
            viff_header.map_columns=image->colors;
          }
        else
          if (image->colors == 2)
            {
              /*
                Monochrome VIFF raster.
              */
              viff_header.data_storage_type=VFF_TYP_BIT;
              packets=((image->columns+7) >> 3)*image->rows;
            }
      }
    /*
      Write VIFF image header (pad to 1024 bytes).
    */
    buffer[0]=viff_header.identifier;
    buffer[1]=viff_header.file_type;
    buffer[2]=viff_header.release;
    buffer[3]=viff_header.version;
    buffer[4]=viff_header.machine_dependency;
    buffer[5]=viff_header.reserve[0];
    buffer[6]=viff_header.reserve[1];
    buffer[7]=viff_header.reserve[2];
    (void) fwrite((char *) buffer,1,8,image->file);
    (void) fwrite((char *) viff_header.comment,1,512,image->file);
    MSBFirstWriteLong(viff_header.rows,image->file);
    MSBFirstWriteLong(viff_header.columns,image->file);
    MSBFirstWriteLong(viff_header.subrows,image->file);
    MSBFirstWriteLong((unsigned long) viff_header.x_offset,image->file);
    MSBFirstWriteLong((unsigned long) viff_header.y_offset,image->file);
    viff_header.x_bits_per_pixel=(63 << 24) | (128 << 16);
    MSBFirstWriteLong((unsigned long) viff_header.x_bits_per_pixel,image->file);
    viff_header.y_bits_per_pixel=(63 << 24) | (128 << 16);
    MSBFirstWriteLong((unsigned long) viff_header.y_bits_per_pixel,image->file);
    MSBFirstWriteLong(viff_header.location_type,image->file);
    MSBFirstWriteLong(viff_header.location_dimension,image->file);
    MSBFirstWriteLong(viff_header.number_of_images,image->file);
    MSBFirstWriteLong(viff_header.number_data_bands,image->file);
    MSBFirstWriteLong(viff_header.data_storage_type,image->file);
    MSBFirstWriteLong(viff_header.data_encode_scheme,image->file);
    MSBFirstWriteLong(viff_header.map_scheme,image->file);
    MSBFirstWriteLong(viff_header.map_storage_type,image->file);
    MSBFirstWriteLong(viff_header.map_rows,image->file);
    MSBFirstWriteLong(viff_header.map_columns,image->file);
    MSBFirstWriteLong(viff_header.map_subrows,image->file);
    MSBFirstWriteLong(viff_header.map_enable,image->file);
    MSBFirstWriteLong(viff_header.maps_per_cycle,image->file);
    MSBFirstWriteLong(viff_header.color_space_model,image->file);
    for (i=0; i < 420; i++)
      (void) fputc('\0',image->file);
    /*
      Convert MIFF to VIFF raster pixels.
    */
    viff_pixels=(unsigned char *) AllocateMemory(packets*sizeof(unsigned char));
    if (viff_pixels == (unsigned char *) NULL)
      WriterExit(ResourceLimitWarning,"Memory allocation failed",image);
    p=image->pixels;
    q=viff_pixels;
    if (!IsPseudoClass(image) && !IsGrayImage(image))
      {
        unsigned long
          offset;

        /*
          Convert DirectClass packet to VIFF RGB pixel.
        */
        offset=image->columns*image->rows;
        for (i=0; i < (int) image->packets; i++)
        {
          for (j=0; j <= ((int) p->length); j++)
          {
            *q=DownScale(p->red);
            *(q+offset)=DownScale(p->green);
            *(q+offset*2)=DownScale(p->blue);
            if (image->matte)
              *(q+offset*3)=DownScale(p->index);
            q++;
          }
          p++;
          if (image->previous == (Image *) NULL)
            if (QuantumTick(i,image->packets))
              ProgressMonitor(SaveImageText,i,image->packets);
        }
      }
    else
      if (!IsGrayImage(image))
        {
          unsigned char
            *viff_colormap;

          /*
            Dump colormap to file.
          */
          viff_colormap=(unsigned char *)
            AllocateMemory(image->colors*3*sizeof(unsigned char));
          if (viff_colormap == (unsigned char *) NULL)
            WriterExit(ResourceLimitWarning,"Memory allocation failed",
              image);
          q=viff_colormap;
          for (i=0; i < (int) image->colors; i++)
            *q++=DownScale(image->colormap[i].red);
          for (i=0; i < (int) image->colors; i++)
            *q++=DownScale(image->colormap[i].green);
          for (i=0; i < (int) image->colors; i++)
            *q++=DownScale(image->colormap[i].blue);
          (void) fwrite((char *) viff_colormap,1,(int) image->colors*3,
            image->file);
          FreeMemory((char *) viff_colormap);
          /*
            Convert PseudoClass packet to VIFF colormapped pixels.
          */
          q=viff_pixels;
          for (i=0; i < (int) image->packets; i++)
          {
            for (j=0; j <= ((int) p->length); j++)
              *q++=p->index;
            p++;
            if (image->previous == (Image *) NULL)
              if (QuantumTick(i,image->packets))
                ProgressMonitor(SaveImageText,i,image->packets);
          }
        }
      else
        if (image->colors == 2)
          {
            int
              x,
              y;

            register unsigned char
              bit,
              byte,
              polarity;

            /*
              Convert PseudoClass image to a VIFF monochrome image.
            */
            polarity=Intensity(image->colormap[0]) > (MaxRGB >> 1);
            if (image->colors == 2)
              polarity=
                Intensity(image->colormap[0]) > Intensity(image->colormap[1]);
            x=0;
            y=0;
            bit=0;
            byte=0;
            for (i=0; i < (int) image->packets; i++)
            {
              for (j=0; j <= ((int) p->length); j++)
              {
                byte>>=1;
                if (p->index == polarity)
                  byte|=0x80;
                bit++;
                if (bit == 8)
                  {
                    *q++=byte;
                    bit=0;
                    byte=0;
                  }
                x++;
                if (x == (int) image->columns)
                  {
                    /*
                      Advance to the next scanline.
                    */
                    if (bit != 0)
                      *q++=byte >> (8-bit);
                    if (image->previous == (Image *) NULL)
                      if (QuantumTick(y,image->rows))
                        ProgressMonitor(SaveImageText,y,image->rows);
                    bit=0;
                    byte=0;
                    x=0;
                    y++;
                 }
              }
              p++;
            }
          }
        else
          {
            /*
              Convert PseudoClass packet to VIFF grayscale pixel.
            */
            for (i=0; i < (int) image->packets; i++)
            {
              for (j=0; j <= ((int) p->length); j++)
                *q++=p->red;
              p++;
              if (image->previous == (Image *) NULL)
                if (QuantumTick(i,image->packets))
                  ProgressMonitor(SaveImageText,i,image->packets);
            }
          }
    (void) fwrite((char *) viff_pixels,1,(int) packets,image->file);
    FreeMemory((char *) viff_pixels);
    if (image->next == (Image *) NULL)
      break;
    image->next->file=image->file;
    image=image->next;
    ProgressMonitor(SaveImagesText,scene++,GetNumberScenes(image));
  } while (image_info->adjoin);
  if (image_info->adjoin)
    while (image->previous != (Image *) NULL)
      image=image->previous;
  CloseImage(image);
  return(True);
}

/*
% Copyright (C) 2003 - 2019 GraphicsMagick Group
% Copyright (C) 2003 ImageMagick Studio
% Copyright 1991-1999 E. I. du Pont de Nemours and Company
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
% GraphicsMagick Gradient Image Methods.
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/alpha_composite.h"
#include "magick/color.h"
#include "magick/gradient.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
+     G r a d i e n t I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GradientImage() applies a continuously smooth color transitions along a
%  vector from one color to another.
%
%  Note, the interface of this method will change in the future to support
%  more than one transistion.
%
%  The format of the GradientImage method is:
%
%      MagickPassFail GradientImage(Image *image,
%        const PixelPacket *start_color,
%        const PixelPacket *stop_color)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o start_color: The start color.
%
%    o stop_color: The stop color.
%
%
*/

#define GradientImageText "[%s] Gradient..."
MagickExport MagickPassFail GradientImage(Image *restrict image,
                                          const PixelPacket *start_color,
                                          const PixelPacket *stop_color)
{
  PixelPacket
    *pixel_packets;

  double
    alpha_scale;

  unsigned long
    i,
    span,
    y;

  unsigned long
    row_count=0;

  MagickBool
    monitor_active;

  MagickPassFail
    status=MagickPass;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(start_color != (const PixelPacket *) NULL);
  assert(stop_color != (const PixelPacket *) NULL);

  monitor_active=MagickMonitorActive();

  span = image->rows;

  pixel_packets=MagickAllocateArray(PixelPacket *,span,sizeof(PixelPacket));
  if (pixel_packets == (PixelPacket *) NULL)
    ThrowBinaryException(ResourceLimitError,MemoryAllocationFailed,
                         image->filename);

  /*
    Generate gradient pixels using alpha blending
    OpenMP is not demonstrated to help here.
  */
  alpha_scale = span > 1 ? ((MaxRGBDouble)/(span-1)) : MaxRGBDouble/2.0;

  for (i=0; i < span; i++)
    {
      double alpha = (double)i*alpha_scale;
      BlendCompositePixel(&pixel_packets[i],start_color,stop_color,alpha);
#if 0
      fprintf(stdout, "%lu: %g (r=%u, g=%u, b=%u)\n", i, alpha,
              (unsigned) pixel_packets[i].red,
              (unsigned) pixel_packets[i].green,
              (unsigned) pixel_packets[i].blue);
#endif
    }

  /*
    Copy gradient pixels to image rows
  */
  for (y=0; y < image->rows; y++)
    {
      register unsigned long
        x;

      register PixelPacket
        *q;

      q=SetImagePixelsEx(image,0,y,image->columns,1,&image->exception);
      if (q == (PixelPacket *) NULL)
        {
          status=MagickFail;
          break;
        }

      for (x=0; x < image->columns; x++)
        q[x] = pixel_packets[y];

      if (!SyncImagePixelsEx(image,&image->exception))
        {
          status=MagickFail;
          break;
        }

      if (monitor_active)
        {
          row_count++;
          if (QuantumTick(row_count,image->rows))
            if (!MagickMonitorFormatted(row_count,image->rows,&image->exception,
                                        GradientImageText,image->filename))
              {
                status=MagickFail;
                break;
              }
        }
    }
  if (IsGray(*start_color) && IsGray(*stop_color))
    image->is_grayscale=MagickTrue;
  if (IsMonochrome(*start_color) && ColorMatch(start_color,stop_color))
    image->is_monochrome=MagickTrue;
  MagickFreeMemory(pixel_packets);
  return(status);
}

/*
% Copyright (C) 2003-2021 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                               A N A L I Z E                                 %
%                                                                             %
%               Methods to Compute a Information about an Image               %
%                                                                             %
%                                                                             %
%                             Software Design                                 %
%                               Bill Corbis                                   %
%                              December 1998                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/attribute.h"
#include "magick/gem.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/utility.h"

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A n a l y z e I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method AnalyzeImage computes the brightness and saturation mean and
%  standard deviation and stores these values as attributes of the image.
%
%  The format of the AnalyzeImage method is:
%
%      MagickPassFail AnalyzeImage(Image *image)
%
%  A description of each parameter follows:
%
%    o image: The address of a structure of type Image.
%
*/
#define PRECISION "%.0f"
ModuleExport MagickPassFail AnalyzeImage(Image **image_ref,
                                         const int argc,char **argv)
{
#define AnalyzeImageText "[%s] Analyze Filter..."

  Image
    * restrict image;

  double
    bsumX = 0.0,
    bsumX2 = 0.0,
    ssumX = 0.0,
    ssumX2 = 0.0;

  long
    y;

  unsigned long
    row_count=0;

  MagickBool
    monitor_active;

  MagickPassFail
    status = MagickPass;

  ARG_NOT_USED(argc);
  ARG_NOT_USED(argv);

  assert(image_ref != (Image **) NULL);
  assert(*image_ref != (Image *) NULL);
  image = *image_ref;

  monitor_active=MagickMonitorActive();

#if defined(HAVE_OPENMP)
#  if defined(TUNE_OPENMP)
#    pragma omp parallel for schedule(runtime) shared(row_count, status, bsumX, bsumX2, ssumX, ssumX2)
#  else
#    if defined(USE_STATIC_SCHEDULING_ONLY)
#      pragma omp parallel for schedule(static) shared(row_count, status, bsumX, bsumX2, ssumX, ssumX2)
#    else
#      pragma omp parallel for schedule(dynamic) shared(row_count, status, bsumX, bsumX2, ssumX, ssumX2)
#    endif
#  endif
#endif
  for (y=0; y < (long) image->rows; y++)
    {
      double
        brightness,
        hue,
        saturation;

      double
        l_bsumX = 0.0,
        l_bsumX2 = 0.0,
        l_ssumX = 0.0,
        l_ssumX2 = 0.0;

      register PixelPacket
        *p;

      register unsigned long
        x = 0;

      MagickPassFail
        thread_status;

      char
        text[MaxTextExtent];

      thread_status=status;
      if (thread_status == MagickFail)
        continue;

      p=GetImagePixels(image,0,y,image->columns,1);
      if (p == (PixelPacket *) NULL)
        {
          thread_status = MagickFail;
          goto bail;
        }
      if (y == 0)
        {
          FormatString(text,"#%02x%02x%02x",p->red,p->green,p->blue);
          (void) SetImageAttribute(image,"TopLeftColor",text);
        }
      if (y == ((long) image->rows-1))
        {
          FormatString(text,"#%02x%02x%02x",p->red,p->green,p->blue);
          (void) SetImageAttribute(image,"BottomLeftColor",text);
        }
      for (x=0; x < image->columns; x++)
        {
          TransformHSL(p->red,p->green,p->blue,&hue,&saturation,&brightness);
          brightness *= MaxRGBDouble;
          l_bsumX += brightness;
          l_bsumX2 += brightness * brightness;
          saturation *= MaxRGBDouble;
          l_ssumX += saturation;
          l_ssumX2 += saturation * saturation;
          p++;
        }
      p--; /* backup one pixel to allow us to sample */
      if (y == 0)
        {
          FormatString(text,"#%02x%02x%02x",p->red,p->green,p->blue);
          (void) SetImageAttribute(image,"TopRightColor",text);
        }
      if (y == ((long) image->rows-1))
        {
          FormatString(text,"#%02x%02x%02x",p->red,p->green,p->blue);
          (void) SetImageAttribute(image,"BottomRightColor",text);
        }

#if defined(HAVE_OPENMP)
#  pragma omp critical (GM_Analyze_Filter_Summation)
#endif
      {
        bsumX += l_bsumX;
        bsumX2 += l_bsumX2;
        ssumX += l_ssumX;
        ssumX2 += l_ssumX2;

#if defined(HAVE_OPENMP)
#  pragma omp flush (bsumX, bsumX2, ssumX, ssumX2)
#endif
      }

    bail:;

      if (monitor_active)
        {
          unsigned long
            thread_row_count;

#if defined(HAVE_OPENMP)
#  pragma omp atomic
#endif
          row_count++;
#if defined(HAVE_OPENMP)
#  pragma omp flush (row_count)
#endif
          thread_row_count=row_count;
          if (QuantumTick(thread_row_count,image->rows))
            if (!MagickMonitorFormatted(thread_row_count,image->rows,&image->exception,
                                        AnalyzeImageText,image->filename))
              thread_status=MagickFail;
        }

      if (thread_status == MagickFail)
        {
          status=MagickFail;
#if defined(HAVE_OPENMP)
#  pragma omp flush (status)
#endif
        }
    }
  if (status == MagickPass)
    {
      double
        brightness_mean,
        brightness_stdev,
        saturation_mean,
        saturation_stdev,
        total_pixels;

      char
        text[MaxTextExtent];

      total_pixels = (double) image->columns * (double) image->rows;
      brightness_mean = bsumX/total_pixels;
      FormatString(text,PRECISION,brightness_mean);
      (void) SetImageAttribute(image,"BrightnessMean",text);
      /*  This formula gives a slightly biased result */
      brightness_stdev =
        sqrt(bsumX2/total_pixels - (bsumX/total_pixels*bsumX/total_pixels));
      FormatString(text,PRECISION,brightness_stdev);
      (void) SetImageAttribute(image,"BrightnessStddev",text);
      /* Now the correction for bias. */
      /*  stdev = stdev*sqrt((double)total_pixels/(double)(total_pixels-1)); */
      /* Now calculate the standard deviation of the mean */
      /*  brightness_stdevmean = bstdev/sqrt((double)total_pixels); */

      saturation_mean = ssumX/total_pixels;
      FormatString(text,PRECISION,saturation_mean);
      (void) SetImageAttribute(image,"SaturationMean",text);
      /* This formula gives a slightly biased result */
      saturation_stdev =
        sqrt(ssumX2/total_pixels - (ssumX/total_pixels*ssumX/total_pixels));
      FormatString(text,PRECISION,saturation_stdev);
      (void) SetImageAttribute(image,"SaturationStddev",text);
      /* Now the correction for bias. */
      /*  stdev = stdev*sqrt((double)total_pixels/(double)(total_pixels-1)); */
      /* Now calculate the standard deviation of the mean */
      /*  saturation_stdevmean = sstdev/sqrt((double)total_pixels); */
    }
  return status;
}

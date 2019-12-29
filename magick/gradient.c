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
#include "magick/colormap.h"
#include "magick/gradient.h"
#include "magick/log.h"
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
%  GradientImage() applies continuously smooth color transitions along a
%  distance vector from one color to another.
%
%  The default is to apply a gradient from the top of the image to the bottom.
%  Since GraphicsMagick 1.3.35, this function responds to the image gravity
%  attribute as follows:
%
%    SouthGravity - Top to Bottom (Default)
%    NorthGravity - Bottom to Top
%    WestGravity  - Right to Left
%    EastGravity  - Left to Right
%    NorthWestGravity - Bottom-Right to Top-Left
%    NorthEastGravity - Bottom-Left to Top-Right
%    SouthWestGravity - Top-Right Bottom-Left
%    SouthEastGravity - Top-Left to Bottom-Right
%
%  Also, since GraphicsMagick 1.3.35, an effort is made to produce a
%  PseudoClass image representation by default.  If the gradient distance
%  vector produces a number of points less than or equal to the maximum
%  colormap size (MaxColormapSize), then a colormap is produced according
%  to the order indicated by the start and stop colors.  Otherwise a
%  DirectClass image is created (as it always was prior to 1.3.35).  The
%  PseudoClass representation is suitably initialized so that changing
%  the image storage class will lead to an immediately usable DirectClass
%  image.
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
    alpha_scale,
    x_origin = 0.0,
    y_origin = 0.0;

  size_t
    span;

  unsigned long
    i,
    y;

  unsigned long
    row_count=0;

#if defined(HAVE_OPENMP)
  int num_threads = omp_get_max_threads();
#endif

  MagickBool
    monitor_active;

  MagickPassFail
    status=MagickPass;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(start_color != (const PixelPacket *) NULL);
  assert(stop_color != (const PixelPacket *) NULL);

  monitor_active=MagickMonitorActive();

  /*
    -define gradient:direction={NorthWest, North, Northeast, West, East, SouthWest, South, SouthEast}

    South is the default

    image->gravity
  */

  /*
    Computed required gradient span
  */
  switch(image->gravity)
    {
    case SouthGravity:
    case NorthGravity:
    default:
      span = image->rows;
      break;
    case WestGravity:
    case EastGravity:
      span = image->columns;
      break;
    case NorthWestGravity:
    case NorthEastGravity:
    case SouthWestGravity:
    case SouthEastGravity:
      span = (size_t) (sqrt(((double)image->columns-1)*((double)image->columns-1)+
                            ((double)image->rows-1)*((double)image->rows-1))+0.5)+1;
      break;
    }

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Gradient span %"MAGICK_SIZE_T_F"u", (MAGICK_SIZE_T) span);

  /*
    Determine origin pixel for diagonal gradients
  */
  switch(image->gravity)
    {
    default:
      break;
    case NorthWestGravity:
      /* Origin bottom-right */
      x_origin = (double)image->columns-1;
      y_origin = (double)image->rows-1;
      break;
    case NorthEastGravity:
      /* Origin bottom-left */
      x_origin = 0.0;
      y_origin = (double)image->rows-1;
      break;
    case SouthWestGravity:
      /* Origin top-right */
      x_origin = (double)image->columns-1;
      y_origin = 0.0;
      break;
    case SouthEastGravity:
      /* Origin top-left */
      x_origin = 0.0;
      y_origin = 0.0;
      break;
    }

  pixel_packets=MagickAllocateArray(PixelPacket *,span,sizeof(PixelPacket));
  if (pixel_packets == (PixelPacket *) NULL)
    ThrowBinaryException(ResourceLimitError,MemoryAllocationFailed,
                         image->filename);
  if (span <= MaxColormapSize)
    AllocateImageColormap(image,span);

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

  if (image->storage_class == PseudoClass)
    (void) memcpy(image->colormap,pixel_packets,span*sizeof(PixelPacket));

  /*
    Copy gradient pixels to image rows
  */
#if defined(HAVE_OPENMP)
  if (num_threads > 3)
    num_threads = 3;
#  if defined(TUNE_OPENMP)
#    pragma omp parallel for if(num_threads > 1) num_threads(num_threads) schedule(runtime) shared(row_count, status)
#  else
#    pragma omp parallel for if(num_threads > 1) num_threads(num_threads) schedule(guided) shared(row_count, status)
#  endif
#endif
  for (y=0; y < image->rows; y++)
    {
      MagickPassFail
        thread_status;

      register unsigned long
        x;

      register PixelPacket
        *q;

      register IndexPacket
        *indexes = (IndexPacket *) NULL;

      thread_status=status;
      if (thread_status == MagickFail)
        continue;

      do
        {
          q=SetImagePixelsEx(image,0,y,image->columns,1,&image->exception);
          if (q == (PixelPacket *) NULL)
            {
              thread_status=MagickFail;
              break;
            }
          if (image->storage_class == PseudoClass)
            {
              indexes=AccessMutableIndexes(image);
              if (indexes == (IndexPacket *) NULL)
                {
                  thread_status=MagickFail;
                  break;
                }
            }

          switch(image->gravity)
            {
            case SouthGravity:
            default:
              {
                for (x=0; x < image->columns; x++)
                  q[x] = pixel_packets[y];
                if (indexes)
                  for (x=0; x < image->columns; x++)
                    indexes[x]=(IndexPacket) y;
                break;
              }
            case NorthGravity:
              {
                for (x=0; x < image->columns; x++)
                  q[x] = pixel_packets[image->columns-y];
                if (indexes)
                  for (x=0; x < image->columns; x++)
                    indexes[x]=(IndexPacket) image->columns-y;
                break;
              }
            case WestGravity:
              {
                for (x=0; x < image->columns; x++)
                  q[x] = pixel_packets[image->columns-x];
                if (indexes)
                  for (x=0; x < image->columns; x++)
                    indexes[x]=(IndexPacket) image->columns-x;
                break;
              }
            case EastGravity:
              {
                for (x=0; x < image->columns; x++)
                  q[x] = pixel_packets[x];
                if (indexes)
                  for (x=0; x < image->columns; x++)
                    indexes[x]=(IndexPacket) x;
                break;
              }
            case NorthWestGravity:
            case NorthEastGravity:
            case SouthWestGravity:
            case SouthEastGravity:
              {
                double ydf = (y_origin-(double)y)*(y_origin-(double)y);
                for (x=0; x < image->columns; x++)
                  {
                    i = (size_t) (sqrt((x_origin-x)*(x_origin-x)+ydf)+0.5);
                    /* fprintf(stderr,"NW %lux%lu: %lu\n", x, y, (unsigned long) i); */
                    q[x] = pixel_packets[i];
                    if (indexes)
                      indexes[x]=(IndexPacket) i;
                  }

                break;
              }
            }

          if (!SyncImagePixelsEx(image,&image->exception))
            {
              thread_status=MagickFail;
              break;
            }

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
                                            GradientImageText,image->filename))
                  {
                    thread_status=MagickFail;
                    break;
                  }
            }
        } while(0);

      if (thread_status == MagickFail)
        {
          status=MagickFail;
#if defined(HAVE_OPENMP)
#  pragma omp flush (status)
#endif
        }
    }
  if (IsGray(*start_color) && IsGray(*stop_color))
    image->is_grayscale=MagickTrue;
  if (IsMonochrome(*start_color) && ColorMatch(start_color,stop_color))
    image->is_monochrome=MagickTrue;
  MagickFreeMemory(pixel_packets);
  return(status);
}

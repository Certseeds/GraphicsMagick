/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                              OOO   RRRR    AAA                              %
%                             O   O  R   R  A   A                             %
%                             O   O  RRRR   AAAAA                             %
%                             O   O  R  R   A   A                             %
%                              OOO   R   R  A   A                             %
%                                                                             %
%                                                                             %
%                       Read OpenRaster (.ora) files                          %
%                                                                             %
%                             OpenRaster spec:                                %
%         https://www.freedesktop.org/wiki/Specifications/OpenRaster/         %
%                                                                             %
%                              Software Design                                %
%                              Jaroslav Fojtik                                %
%                                   2024                                      %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/


/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/blob.h"
#include "magick/colormap.h"
#include "magick/constitute.h"
#include "magick/image.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/tempfile.h"
#include "magick/utility.h"
#include "contrib/minizip/unzip.h"

#if defined(HasPNG) && defined(HasUNZIP)


static const char MERGED_IMAGE_PATH[] = "mergedimage.png";
#define BUFFER_SIZE 8196


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d O R A I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReadORAImage reads an ORA file in the most basic way possible: by
%  reading it as a ZIP File and extracting the mergedimage.png file from it,
%  which is then passed to ReadPNGImage.
%  https://www.freedesktop.org/wiki/Specifications/OpenRaster/Draft/FileLayout/
%
%  The format of the ReadORAImage method is:
%
%      Image *ReadORAImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadORAImage returns a pointer to the image after
%      reading. A null image is returned if there is a memory shortage or if
%      the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
*/
static Image *ReadORAImage(const ImageInfo *image_info, ExceptionInfo *exception)
{
  unzFile zip_archive;
  Image *image;
  int res;
  void *buf;
  FILE *PngFile;
  ImageInfo *clone_info;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);

  image = AllocateImage(image_info);

  buf = MagickAllocateResourceLimitedArray(void*,BUFFER_SIZE,1);
  if(buf == NULL)
        ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  zip_archive = unzOpen(image_info->filename);
  if(zip_archive == NULL)
  {
    MagickFreeResourceLimitedMemory(buf);
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);
  }

  if(UNZ_OK != unzLocateFile(zip_archive,MERGED_IMAGE_PATH,0))
  {
    unzClose(zip_archive);
    MagickFreeResourceLimitedMemory(buf);
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);
  }

  clone_info = CloneImageInfo(image_info);
  memcpy(clone_info->filename,"PNG:",4);
  PngFile = AcquireTemporaryFileStream(clone_info->filename+4,BinaryFileIOMode);
  if(!PngFile)
  {
    DestroyImageInfo(clone_info);
    clone_info = (ImageInfo *) NULL;
    unzClose(zip_archive);
    MagickFreeResourceLimitedMemory(buf);
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);
  }

  unzOpenCurrentFile(zip_archive);
  while((res=unzReadCurrentFile(zip_archive,buf,BUFFER_SIZE)) > 0)
  {
    fwrite(buf,res,1,PngFile);
  }
  unzCloseCurrentFile(zip_archive);
  fclose(PngFile);

  MagickFreeResourceLimitedMemory(buf);
  unzClose(zip_archive);

  DestroyImage(image);

  (void)strlcpy(clone_info->magick, "PNG", sizeof(clone_info->magick));
  image = ReadImage(clone_info,exception);

  DestroyImageInfo(clone_info);
  clone_info = (ImageInfo*)NULL;

  return(image);
}



/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r O R A I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterORAImage adds attributes for the ORA image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterORAImage method is:
%
%      RegisterORAImage(void)
%
*/
ModuleExport void RegisterORAImage(void)
{
  MagickInfo *entry;

  entry=SetMagickInfo("ORA");
  entry->decoder = (DecoderHandler)ReadORAImage;
  entry->description="Open Raster";
  entry->module="ORA";
  entry->adjoin=False;
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r O R A I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterORAImage removes format registrations made by the
%  ORA module from the list of supported formats.
%
%  The format of the UnregisterORAImage method is:
%
%      UnregisterORAImage(void)
%
*/
ModuleExport void UnregisterORAImage(void)
{
  (void) UnregisterMagickInfo("ORA");
}

#endif

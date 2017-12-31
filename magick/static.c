/*
% Copyright (C) 2003-2017 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                  SSSSS  TTTTT   AAA   TTTTT  IIIII   CCCC                   %
%                  SS       T    A   A    T      I    C                       %
%                   SSS     T    AAAAA    T      I    C                       %
%                     SS    T    A   A    T      I    C                       %
%                  SSSSS    T    A   A    T    IIIII   CCCC                   %
%                                                                             %
%                                                                             %
%                        GraphicsMagick Static Methods                        %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 March 2000                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/module.h"
#include "magick/static.h"
#include "magick/utility.h"

#if !defined(BuildMagickModules)
static const struct
{
  char* name;
  void (*register_fn)(void);
  void (*unregister_fn)(void);

} StaticModules[] =
{
#define STATICM(name,register_fn,unregister_fn) {name,register_fn,unregister_fn}
  STATICM("ART",RegisterARTImage,UnregisterARTImage),
  STATICM("AVS",RegisterAVSImage,UnregisterAVSImage),
  STATICM("BMP",RegisterBMPImage,UnregisterBMPImage),
  STATICM("CALS",RegisterCALSImage,UnregisterCALSImage),
  STATICM("CAPTION",RegisterCAPTIONImage,UnregisterCAPTIONImage),
  STATICM("CINEON",RegisterCINEONImage,UnregisterCINEONImage),
#if defined(HasWINGDI32)
  STATICM("CLIPBOARD",RegisterCLIPBOARDImage,UnregisterCLIPBOARDImage),
#endif
  STATICM("CMYK",RegisterCMYKImage,UnregisterCMYKImage),
  STATICM("CUT",RegisterCUTImage,UnregisterCUTImage),
  STATICM("DCM",RegisterDCMImage,UnregisterDCMImage),
  STATICM("DCRAW",RegisterDCRAWImage,UnregisterDCRAWImage),
  STATICM("DIB",RegisterDIBImage,UnregisterDIBImage),
#if defined(HasDPS)
  STATICM("DPS",RegisterDPSImage,UnregisterDPSImage),
#endif
  STATICM("DPX",RegisterDPXImage,UnregisterDPXImage),
#if defined(HasWINGDI32)
  STATICM("EMF",RegisterEMFImage,UnregisterEMFImage),
#endif
#if defined(HasTIFF)
  STATICM("EPT",RegisterEPTImage,UnregisterEPTImage),
#endif
  STATICM("FAX",RegisterFAXImage,UnregisterFAXImage),
  STATICM("FITS",RegisterFITSImage,UnregisterFITSImage),
#if defined(HasFPX)
  STATICM("FPX",RegisterFPXImage,UnregisterFPXImage),
#endif
  STATICM("GIF",RegisterGIFImage,UnregisterGIFImage),
  STATICM("GRAY",RegisterGRAYImage,UnregisterGRAYImage),
  STATICM("GRADIENT",RegisterGRADIENTImage,UnregisterGRADIENTImage),
  STATICM("HISTOGRAM",RegisterHISTOGRAMImage,UnregisterHISTOGRAMImage),
  STATICM("HRZ",RegisterHRZImage,UnregisterHRZImage),
  STATICM("HTML",RegisterHTMLImage,UnregisterHTMLImage),
  STATICM("ICON",RegisterICONImage,UnregisterICONImage),
  STATICM("IDENTITY",RegisterIDENTITYImage,UnregisterIDENTITYImage),
  STATICM("INFO",RegisterINFOImage,UnregisterINFOImage),
#if defined(HasJBIG)
  STATICM("JBIG",RegisterJBIGImage,UnregisterJBIGImage),
#endif
#if defined(HasJPEG)
  STATICM("JNX",RegisterJNXImage,UnregisterJNXImage),
#endif
#if defined(HasJPEG)
  STATICM("JPEG",RegisterJPEGImage,UnregisterJPEGImage),
#endif
#if defined(HasJP2)
  STATICM("JP2",RegisterJP2Image,UnregisterJP2Image),
#endif
  STATICM("LABEL",RegisterLABELImage,UnregisterLABELImage),
  STATICM("LOCALE",RegisterLOCALEImage,UnregisterLOCALEImage),
  STATICM("LOGO",RegisterLOGOImage,UnregisterLOGOImage),
  STATICM("MAC",RegisterMACImage,UnregisterMACImage),
  STATICM("MAP",RegisterMAPImage,UnregisterMAPImage),
  STATICM("MAT",RegisterMATImage,UnregisterMATImage),
  STATICM("MATTE",RegisterMATTEImage,UnregisterMATTEImage),
  STATICM("META",RegisterMETAImage,UnregisterMETAImage),
  STATICM("MIFF",RegisterMIFFImage,UnregisterMIFFImage),
  STATICM("MONO",RegisterMONOImage,UnregisterMONOImage),
  STATICM("MPC",RegisterMPCImage,UnregisterMPCImage),
  STATICM("MPEG",RegisterMPEGImage,UnregisterMPEGImage),
  STATICM("MPR",RegisterMPRImage,UnregisterMPRImage),
  STATICM("MSL",RegisterMSLImage,UnregisterMSLImage),
  STATICM("MTV",RegisterMTVImage,UnregisterMTVImage),
  STATICM("MVG",RegisterMVGImage,UnregisterMVGImage),
  STATICM("NULL",RegisterNULLImage,UnregisterNULLImage),
  STATICM("OTB",RegisterOTBImage,UnregisterOTBImage),
  STATICM("PALM",RegisterPALMImage,UnregisterPALMImage),
  STATICM("PCD",RegisterPCDImage,UnregisterPCDImage),
  STATICM("PCL",RegisterPCLImage,UnregisterPCLImage),
  STATICM("PCX",RegisterPCXImage,UnregisterPCXImage),
  STATICM("PDB",RegisterPDBImage,UnregisterPDBImage),
  STATICM("PDF",RegisterPDFImage,UnregisterPDFImage),
  STATICM("PICT",RegisterPICTImage,UnregisterPICTImage),
  STATICM("PIX",RegisterPIXImage,UnregisterPIXImage),
  STATICM("PLASMA",RegisterPLASMAImage,UnregisterPLASMAImage),
#if defined(HasPNG)
  STATICM("PNG",RegisterPNGImage,UnregisterPNGImage),
#endif
  STATICM("PNM",RegisterPNMImage,UnregisterPNMImage),
  STATICM("PREVIEW",RegisterPREVIEWImage,UnregisterPREVIEWImage),
  STATICM("PS",RegisterPSImage,UnregisterPSImage),
  STATICM("PS2",RegisterPS2Image,UnregisterPS2Image),
  STATICM("PS3",RegisterPS3Image,UnregisterPS3Image),
#if defined(EnableBrokenCoders) && EnableBrokenCoders
  STATICM("PSD",RegisterPSDImage,UnregisterPSDImage),
#endif /* defined(EnableBrokenCoders) && EnableBrokenCoders */
  STATICM("PWP",RegisterPWPImage,UnregisterPWPImage),
  STATICM("RGB",RegisterRGBImage,UnregisterRGBImage),
  STATICM("RLA",RegisterRLAImage,UnregisterRLAImage),
  STATICM("RLE",RegisterRLEImage,UnregisterRLEImage),
  STATICM("SCT",RegisterSCTImage,UnregisterSCTImage),
  STATICM("SFW",RegisterSFWImage,UnregisterSFWImage),
  STATICM("SGI",RegisterSGIImage,UnregisterSGIImage),
  STATICM("STEGANO",RegisterSTEGANOImage,UnregisterSTEGANOImage),
  STATICM("SUN",RegisterSUNImage,UnregisterSUNImage),
  STATICM("SVG",RegisterSVGImage,UnregisterSVGImage),
  STATICM("TGA",RegisterTGAImage,UnregisterTGAImage),
#if defined(HasTIFF)
  STATICM("TIFF",RegisterTIFFImage,UnregisterTIFFImage),
#endif
  STATICM("TILE",RegisterTILEImage,UnregisterTILEImage),
  STATICM("TIM",RegisterTIMImage,UnregisterTIMImage),
  STATICM("TOPOL",RegisterTOPOLImage,UnregisterTOPOLImage),
  STATICM("TTF",RegisterTTFImage,UnregisterTTFImage),
  STATICM("TXT",RegisterTXTImage,UnregisterTXTImage),
  STATICM("UIL",RegisterUILImage,UnregisterUILImage),
  STATICM("URL",RegisterURLImage,UnregisterURLImage),
  STATICM("UYVY",RegisterUYVYImage,UnregisterUYVYImage),
  STATICM("VICAR",RegisterVICARImage,UnregisterVICARImage),
  STATICM("VID",RegisterVIDImage,UnregisterVIDImage),
  STATICM("VIFF",RegisterVIFFImage,UnregisterVIFFImage),
  STATICM("WBMP",RegisterWBMPImage,UnregisterWBMPImage),
#if defined(HasWEBP)
  STATICM("WEBP",RegisterWEBPImage,UnregisterWEBPImage),
#endif
  STATICM("WMF",RegisterWMFImage,UnregisterWMFImage),
  STATICM("WPG",RegisterWPGImage,UnregisterWPGImage),
#if defined(HasX11)
  STATICM("X",RegisterXImage,UnregisterXImage),
#endif /* defined(HasX11) */
  STATICM("XBM",RegisterXBMImage,UnregisterXBMImage),
  STATICM("XC",RegisterXCImage,UnregisterXCImage),
  STATICM("XCF",RegisterXCFImage,UnregisterXCFImage),
  STATICM("XPM",RegisterXPMImage,UnregisterXPMImage),
#if defined(_VISUALC_)
  STATICM("XTRN",RegisterXTRNImage,UnregisterXTRNImage),
#endif /* defined(_VISUALC_) */
#if defined(HasX11)
  STATICM("XWD",RegisterXWDImage,UnregisterXWDImage),
#endif /* defined(HasX11) */
  STATICM("YUV",RegisterYUVImage,UnregisterYUVImage)
};
#endif /* !defined(BuildMagickModules) */

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   E x e c u t e S t a t i c M o d u l e P r o c e s s                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ExecuteStaticModuleProcess() is just a template method. This version is
%  only used for static and moby builds.  See the version in module.c for
%  module-only builds. This function takes the place of ExecuteModuleProcess
%  for builds which do not support loading modules.
%
%  The format of the ExecuteStaticModuleProcess method is:
%
%      unsigned int ExecuteStaticModuleProcess(const char *tag,
%        Image **image,const int argc,char **argv)
%
%  A description of each parameter follows:
%
%    o tag: The module tag.
%
%    o image: The image.
%
%    o argc: The number of elements in the argument vector.
%
%    o argv: A text array containing the command line arguments.
%
*/
#if defined(SupportMagickModules)
MagickExport unsigned int ExecuteStaticModuleProcess(const char *tag,
  Image **image,const int argc,char **argv)
#else
MagickExport unsigned int ExecuteModuleProcess(const char *tag,
  Image **image,const int argc,char **argv)
#endif /* defined(SupportMagickModules) */
{
  unsigned int
    status = False;

#if !defined(BuildMagickModules)
  unsigned int
    (*method)(Image **,const int,char **) = 0;

  if (LocaleCompare("analyze",tag) == 0)
    method=AnalyzeImage;

  if (method)
    {
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Invoking \"%.1024s\" filter module",tag);

      status=(*method)(image,argc,argv);

      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "Returned from \"%.1024s\" filter module",tag);
    }
#else
  ARG_NOT_USED(tag);
  ARG_NOT_USED(image);
  ARG_NOT_USED(argc);
  ARG_NOT_USED(argv);
#endif /* !defined(BuildMagickModules) */
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r S t a t i c M o d u l e s                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
RegisterStaticModules() statically registers all the available module
%  handlers.
%
%  The format of the RegisterStaticModules method is:
%
%      RegisterStaticModules(void)
%
%
*/
MagickExport void RegisterStaticModules(void)
{
#if !defined(BuildMagickModules)
  unsigned int index;

  for (index=0; index < sizeof(StaticModules)/sizeof(StaticModules[0]);index++)
    {
      (StaticModules[index].register_fn)();
    }
#endif /* !defined(BuildMagickModules) */
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r S t a t i c M o d u l e s                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  UnregisterStaticModules() statically unregisters all the available module
%  handlers. This allows allocated resources to be freed.
%
%  The format of the UnRegisterStaticModules method is:
%
%      UnRegisterStaticModules(void)
%
%
*/
MagickExport void UnregisterStaticModules(void)
{
#if !defined(BuildMagickModules)
  unsigned int index;

  for (index=0; index < sizeof(StaticModules)/sizeof(StaticModules[0]);index++)
    {
      (StaticModules[index].unregister_fn)();
    }
#endif /* !defined(BuildMagickModules) */
}

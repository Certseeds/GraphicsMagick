@echo off
set exedir=..\bin\
set srcdir=..\..\tests\
set events="exception"
set bilevel_file=%srcdir%input_bilevel.miff
set gray_file=%srcdir%input_gray.miff
set palette_file=%srcdir%input_palette.miff
set truecolor_file=%srcdir%input_truecolor.miff
@echo Running rwblob tests...
@echo on
%exedir%rwblob.exe -debug %events% %bilevel_file% AVS 
%exedir%rwblob.exe -debug %events% %gray_file% AVS 
%exedir%rwblob.exe -debug %events% %palette_file% AVS 
%exedir%rwblob.exe -debug %events% %truecolor_file% AVS 
%exedir%rwblob.exe -debug %events% %bilevel_file% BMP 
%exedir%rwblob.exe -debug %events% %gray_file% BMP 
%exedir%rwblob.exe -debug %events% %palette_file% BMP 
%exedir%rwblob.exe -debug %events% %truecolor_file% BMP 
%exedir%rwblob.exe -debug %events% %bilevel_file% DIB 
%exedir%rwblob.exe -debug %events% %gray_file% DIB 
%exedir%rwblob.exe -debug %events% %palette_file% DIB 
%exedir%rwblob.exe -debug %events% %truecolor_file% DIB 
%exedir%rwblob.exe -debug %events% %bilevel_file% DPX 
%exedir%rwblob.exe -debug %events% %gray_file% DPX 
%exedir%rwblob.exe -debug %events% %palette_file% DPX 
%exedir%rwblob.exe -debug %events% %truecolor_file% DPX 
%exedir%rwblob.exe -debug %events% %bilevel_file% EPDF 
%exedir%rwblob.exe -debug %events% %gray_file% EPDF 
%exedir%rwblob.exe -debug %events% %palette_file% EPDF 
%exedir%rwblob.exe -debug %events% %truecolor_file% EPDF 
%exedir%rwblob.exe -debug %events% %bilevel_file% EPSF 
%exedir%rwblob.exe -debug %events% %gray_file% EPSF 
%exedir%rwblob.exe -debug %events% %palette_file% EPSF 
%exedir%rwblob.exe -debug %events% %truecolor_file% EPSF 
%exedir%rwblob.exe -debug %events% %bilevel_file% EPSI 
%exedir%rwblob.exe -debug %events% %gray_file% EPSI 
%exedir%rwblob.exe -debug %events% %palette_file% EPSI 
%exedir%rwblob.exe -debug %events% %truecolor_file% EPSI 
%exedir%rwblob.exe -debug %events% %bilevel_file% EPI 
%exedir%rwblob.exe -debug %events% %gray_file% EPI 
%exedir%rwblob.exe -debug %events% %palette_file% EPI 
%exedir%rwblob.exe -debug %events% %truecolor_file% EPI 
%exedir%rwblob.exe -debug %events% %bilevel_file% EPS 
%exedir%rwblob.exe -debug %events% %gray_file% EPS 
%exedir%rwblob.exe -debug %events% %palette_file% EPS 
%exedir%rwblob.exe -debug %events% %truecolor_file% EPS 
%exedir%rwblob.exe -debug %events% %bilevel_file% EPT 
%exedir%rwblob.exe -debug %events% %gray_file% EPT 
%exedir%rwblob.exe -debug %events% %palette_file% EPT 
%exedir%rwblob.exe -debug %events% %truecolor_file% EPT 
%exedir%rwblob.exe -debug %events% %bilevel_file% FAX 
%exedir%rwblob.exe -debug %events% %gray_file% FAX 
%exedir%rwblob.exe -debug %events% %palette_file% FAX 
%exedir%rwblob.exe -debug %events% %truecolor_file% FAX 
%exedir%rwblob.exe -debug %events% %bilevel_file% FITS 
%exedir%rwblob.exe -debug %events% %gray_file% FITS 
%exedir%rwblob.exe -debug %events% %palette_file% FITS 
%exedir%rwblob.exe -debug %events% %truecolor_file% FITS 
%exedir%rwblob.exe -debug %events% %bilevel_file% GIF 
%exedir%rwblob.exe -debug %events% %gray_file% GIF 
%exedir%rwblob.exe -debug %events% %palette_file% GIF 
%exedir%rwblob.exe -debug %events% %truecolor_file% GIF 
%exedir%rwblob.exe -debug %events% %bilevel_file% GRAY 
%exedir%rwblob.exe -debug %events% %gray_file% GRAY 
%exedir%rwblob.exe -debug %events% %palette_file% GRAY 
%exedir%rwblob.exe -debug %events% %truecolor_file% GRAY 
%exedir%rwblob.exe -debug %events% %bilevel_file% ICB 
%exedir%rwblob.exe -debug %events% %gray_file% ICB 
%exedir%rwblob.exe -debug %events% %palette_file% ICB 
%exedir%rwblob.exe -debug %events% %truecolor_file% ICB 
%exedir%rwblob.exe -debug %events% %bilevel_file% JBIG 
%exedir%rwblob.exe -debug %events% %gray_file% JBIG 
%exedir%rwblob.exe -debug %events% %palette_file% JBIG 
%exedir%rwblob.exe -debug %events% %truecolor_file% JBIG 
%exedir%rwblob.exe -debug %events% %bilevel_file% JPEG 
%exedir%rwblob.exe -debug %events% %gray_file% JPEG 
%exedir%rwblob.exe -debug %events% %palette_file% JPEG 
%exedir%rwblob.exe -debug %events% %truecolor_file% JPEG 
%exedir%rwblob.exe -debug %events% %bilevel_file% JP2 
%exedir%rwblob.exe -debug %events% %gray_file% JP2 
%exedir%rwblob.exe -debug %events% %palette_file% JP2 
%exedir%rwblob.exe -debug %events% %truecolor_file% JP2 
%exedir%rwblob.exe -debug %events% %bilevel_file% MIFF 
%exedir%rwblob.exe -debug %events% %gray_file% MIFF 
%exedir%rwblob.exe -debug %events% %palette_file% MIFF 
%exedir%rwblob.exe -debug %events% %truecolor_file% MIFF 
%exedir%rwblob.exe -debug %events% %bilevel_file% MNG 
%exedir%rwblob.exe -debug %events% %gray_file% MNG 
%exedir%rwblob.exe -debug %events% %palette_file% MNG 
%exedir%rwblob.exe -debug %events% %truecolor_file% MNG 
%exedir%rwblob.exe -debug %events% %bilevel_file% MTV 
%exedir%rwblob.exe -debug %events% %gray_file% MTV 
%exedir%rwblob.exe -debug %events% %palette_file% MTV 
%exedir%rwblob.exe -debug %events% %truecolor_file% MTV 
%exedir%rwblob.exe -debug %events% %bilevel_file% P7 
%exedir%rwblob.exe -debug %events% %gray_file% P7 
%exedir%rwblob.exe -debug %events% %palette_file% P7 
%exedir%rwblob.exe -debug %events% %truecolor_file% P7 
%exedir%rwblob.exe -debug %events% %bilevel_file% PBM 
%exedir%rwblob.exe -debug %events% %gray_file% PBM 
%exedir%rwblob.exe -debug %events% %palette_file% PBM 
%exedir%rwblob.exe -debug %events% %truecolor_file% PBM 
%exedir%rwblob.exe -debug %events% %bilevel_file% PCD 
%exedir%rwblob.exe -debug %events% %gray_file% PCD 
%exedir%rwblob.exe -debug %events% %palette_file% PCD 
%exedir%rwblob.exe -debug %events% %truecolor_file% PCD 
%exedir%rwblob.exe -debug %events% %bilevel_file% PCDS 
%exedir%rwblob.exe -debug %events% %gray_file% PCDS 
%exedir%rwblob.exe -debug %events% %palette_file% PCDS 
%exedir%rwblob.exe -debug %events% %truecolor_file% PCDS 
%exedir%rwblob.exe -debug %events% %bilevel_file% PCX 
%exedir%rwblob.exe -debug %events% %gray_file% PCX 
%exedir%rwblob.exe -debug %events% %palette_file% PCX 
%exedir%rwblob.exe -debug %events% %truecolor_file% PCX 
%exedir%rwblob.exe -debug %events% %bilevel_file% PGM 
%exedir%rwblob.exe -debug %events% %gray_file% PGM 
%exedir%rwblob.exe -debug %events% %palette_file% PGM 
%exedir%rwblob.exe -debug %events% %truecolor_file% PGM 
%exedir%rwblob.exe -debug %events% %bilevel_file% PICON 
%exedir%rwblob.exe -debug %events% %gray_file% PICON 
%exedir%rwblob.exe -debug %events% %palette_file% PICON 
%exedir%rwblob.exe -debug %events% %truecolor_file% PICON 
%exedir%rwblob.exe -debug %events% %bilevel_file% PICT 
%exedir%rwblob.exe -debug %events% %gray_file% PICT 
%exedir%rwblob.exe -debug %events% %palette_file% PICT 
%exedir%rwblob.exe -debug %events% %truecolor_file% PICT 
%exedir%rwblob.exe -debug %events% %bilevel_file% PNG 
%exedir%rwblob.exe -debug %events% %gray_file% PNG 
%exedir%rwblob.exe -debug %events% %palette_file% PNG 
%exedir%rwblob.exe -debug %events% %truecolor_file% PNG 
%exedir%rwblob.exe -debug %events% %bilevel_file% PNM 
%exedir%rwblob.exe -debug %events% %gray_file% PNM 
%exedir%rwblob.exe -debug %events% %palette_file% PNM 
%exedir%rwblob.exe -debug %events% %truecolor_file% PNM 
%exedir%rwblob.exe -debug %events% %bilevel_file% PPM 
%exedir%rwblob.exe -debug %events% %gray_file% PPM 
%exedir%rwblob.exe -debug %events% %palette_file% PPM 
%exedir%rwblob.exe -debug %events% %truecolor_file% PPM 
%exedir%rwblob.exe -debug %events% %bilevel_file% PS 
%exedir%rwblob.exe -debug %events% %gray_file% PS 
%exedir%rwblob.exe -debug %events% %palette_file% PS 
%exedir%rwblob.exe -debug %events% %truecolor_file% PS 
: %exedir%rwblob.exe -debug %events% %bilevel_file% PSD 
: %exedir%rwblob.exe -debug %events% %gray_file% PSD 
: %exedir%rwblob.exe -debug %events% %palette_file% PSD 
: %exedir%rwblob.exe -debug %events% %truecolor_file% PSD 
%exedir%rwblob.exe -debug %events% %bilevel_file% RAS 
%exedir%rwblob.exe -debug %events% %gray_file% RAS 
%exedir%rwblob.exe -debug %events% %palette_file% RAS 
%exedir%rwblob.exe -debug %events% %truecolor_file% RAS 
%exedir%rwblob.exe -debug %events% %bilevel_file% SGI 
%exedir%rwblob.exe -debug %events% %gray_file% SGI 
%exedir%rwblob.exe -debug %events% %palette_file% SGI 
%exedir%rwblob.exe -debug %events% %truecolor_file% SGI 
%exedir%rwblob.exe -debug %events% %bilevel_file% SUN 
%exedir%rwblob.exe -debug %events% %gray_file% SUN 
%exedir%rwblob.exe -debug %events% %palette_file% SUN 
%exedir%rwblob.exe -debug %events% %truecolor_file% SUN 
%exedir%rwblob.exe -debug %events% %bilevel_file% TGA 
%exedir%rwblob.exe -debug %events% %gray_file% TGA 
%exedir%rwblob.exe -debug %events% %palette_file% TGA 
%exedir%rwblob.exe -debug %events% %truecolor_file% TGA 
%exedir%rwblob.exe -debug %events% %bilevel_file% TIFF 
%exedir%rwblob.exe -debug %events% %gray_file% TIFF 
%exedir%rwblob.exe -debug %events% %palette_file% TIFF 
%exedir%rwblob.exe -debug %events% %truecolor_file% TIFF 
%exedir%rwblob.exe -debug %events% %bilevel_file% VDA 
%exedir%rwblob.exe -debug %events% %gray_file% VDA 
%exedir%rwblob.exe -debug %events% %palette_file% VDA 
%exedir%rwblob.exe -debug %events% %truecolor_file% VDA 
%exedir%rwblob.exe -debug %events% %bilevel_file% VICAR 
%exedir%rwblob.exe -debug %events% %gray_file% VICAR 
%exedir%rwblob.exe -debug %events% %palette_file% VICAR 
%exedir%rwblob.exe -debug %events% %truecolor_file% VICAR 
%exedir%rwblob.exe -debug %events% %bilevel_file% VIFF 
%exedir%rwblob.exe -debug %events% %gray_file% VIFF 
%exedir%rwblob.exe -debug %events% %palette_file% VIFF 
%exedir%rwblob.exe -debug %events% %truecolor_file% VIFF 
%exedir%rwblob.exe -debug %events% %bilevel_file% VST 
%exedir%rwblob.exe -debug %events% %gray_file% VST 
%exedir%rwblob.exe -debug %events% %palette_file% VST 
%exedir%rwblob.exe -debug %events% %truecolor_file% VST 
%exedir%rwblob.exe -debug %events% %bilevel_file% WBMP 
%exedir%rwblob.exe -debug %events% %gray_file% WBMP 
%exedir%rwblob.exe -debug %events% %palette_file% WBMP 
%exedir%rwblob.exe -debug %events% %truecolor_file% WBMP 
%exedir%rwblob.exe -debug %events% %bilevel_file% XBM 
%exedir%rwblob.exe -debug %events% %gray_file% XBM 
%exedir%rwblob.exe -debug %events% %palette_file% XBM 
%exedir%rwblob.exe -debug %events% %truecolor_file% XBM 
%exedir%rwblob.exe -debug %events% %bilevel_file% XPM 
%exedir%rwblob.exe -debug %events% %gray_file% XPM 
%exedir%rwblob.exe -debug %events% %palette_file% XPM 
%exedir%rwblob.exe -debug %events% %truecolor_file% XPM 
: %exedir%rwblob.exe -debug %events% %bilevel_file% XWD
: %exedir%rwblob.exe -debug %events% %gray_file% XWD 
: %exedir%rwblob.exe -debug %events% %palette_file% XWD 
: %exedir%rwblob.exe -debug %events% %truecolor_file% XWD
%exedir%rwblob.exe -debug %events% -size 70x46 %bilevel_file% CMYK 
%exedir%rwblob.exe -debug %events% -size 70x46 %gray_file% CMYK 
%exedir%rwblob.exe -debug %events% -size 70x46 %palette_file% CMYK 
%exedir%rwblob.exe -debug %events% -size 70x46 %truecolor_file% CMYK 
%exedir%rwblob.exe -debug %events% -size 70x46 %bilevel_file% GRAY 
%exedir%rwblob.exe -debug %events% -size 70x46 %gray_file% GRAY 
%exedir%rwblob.exe -debug %events% -size 70x46 %palette_file% GRAY 
%exedir%rwblob.exe -debug %events% -size 70x46 %truecolor_file% GRAY 
%exedir%rwblob.exe -debug %events% -size 70x46 %bilevel_file% MONO 
%exedir%rwblob.exe -debug %events% -size 70x46 %gray_file% MONO 
%exedir%rwblob.exe -debug %events% -size 70x46 %palette_file% MONO 
%exedir%rwblob.exe -debug %events% -size 70x46 %truecolor_file% MONO 
%exedir%rwblob.exe -debug %events% -size 70x46 %bilevel_file% PAL 
%exedir%rwblob.exe -debug %events% -size 70x46 %gray_file% PAL 
%exedir%rwblob.exe -debug %events% -size 70x46 %palette_file% PAL 
%exedir%rwblob.exe -debug %events% -size 70x46 %truecolor_file% PAL 
%exedir%rwblob.exe -debug %events% -size 70x46 %bilevel_file% RGB 
%exedir%rwblob.exe -debug %events% -size 70x46 %gray_file% RGB 
%exedir%rwblob.exe -debug %events% -size 70x46 %palette_file% RGB 
%exedir%rwblob.exe -debug %events% -size 70x46 %truecolor_file% RGB 
%exedir%rwblob.exe -debug %events% -size 70x46 %bilevel_file% RGBA 
%exedir%rwblob.exe -debug %events% -size 70x46 %gray_file% RGBA 
%exedir%rwblob.exe -debug %events% -size 70x46 %palette_file% RGBA 
%exedir%rwblob.exe -debug %events% -size 70x46 %truecolor_file% RGBA 
%exedir%rwblob.exe -debug %events% -size 70x46 %bilevel_file% UYVY 
%exedir%rwblob.exe -debug %events% -size 70x46 %gray_file% UYVY 
%exedir%rwblob.exe -debug %events% -size 70x46 %palette_file% UYVY 
%exedir%rwblob.exe -debug %events% -size 70x46 %truecolor_file% UYVY 
%exedir%rwblob.exe -debug %events% -size 70x46 %bilevel_file% YUV 
%exedir%rwblob.exe -debug %events% -size 70x46 %gray_file% YUV 
%exedir%rwblob.exe -debug %events% -size 70x46 %palette_file% YUV 
%exedir%rwblob.exe -debug %events% -size 70x46 %truecolor_file% YUV 


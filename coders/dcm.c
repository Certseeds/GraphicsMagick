/*
% Copyright (C) 2003-2019 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
% Copyright 1991-1999 E. I. du Pont de Nemours and Company
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                            DDDD    CCCC  M   M                              %
%                            D   D  C      MM MM                              %
%                            D   D  C      M M M                              %
%                            D   D  C      M   M                              %
%                            DDDD    CCCC  M   M                              %
%                                                                             %
%                                                                             %
%                          Read DICOM Image Format.                           %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1992                                   %
%                                                                             %
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
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/colormap.h"
#include "magick/constitute.h"
#include "magick/enhance.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/tempfile.h"
#include "magick/utility.h"

/*
#define USE_GRAYMAP
#define GRAYSCALE_USES_PALETTE
*/

/* Defines for "best guess" fixes */
#define NEW_IMPLICIT_LOGIC
#define IGNORE_WINDOW_FOR_UNSPECIFIED_SCALE_TYPE

/*
  Function types for reading MSB/LSB shorts/longs
*/
typedef magick_uint16_t (DicomReadShortFunc)(Image *);
typedef magick_uint32_t (DicomReadLongFunc)(Image *);

/*
   DCM enums
*/
typedef enum
{
  DCM_TS_IMPL_LITTLE,
  DCM_TS_EXPL_LITTLE,
  DCM_TS_EXPL_BIG,
  DCM_TS_JPEG,
  DCM_TS_JPEG_LS,
  DCM_TS_JPEG_2000,
  DCM_TS_RLE
} Dicom_TS;

typedef enum
{
  DCM_MSB_LITTLE,
  DCM_MSB_BIG_PENDING,
  DCM_MSB_BIG
} Dicom_MSB;

typedef enum
{
  DCM_PI_MONOCHROME1,
  DCM_PI_MONOCHROME2,
  DCM_PI_PALETTE_COLOR,
  DCM_PI_RGB,
  DCM_PI_OTHER
} Dicom_PI;

typedef enum
{
  DCM_RT_OPTICAL_DENSITY,
  DCM_RT_HOUNSFIELD,
  DCM_RT_UNSPECIFIED,
  DCM_RT_UNKNOWN
} Dicom_RT;

typedef enum
{
  DCM_RS_NONE,
  DCM_RS_PRE,
  DCM_RS_POST
} Dicom_RS;

/*
  Dicom medical image declarations.
*/
typedef struct _DicomStream
{
  /*
    Values representing nature of image
  */
  unsigned long
    rows,
    columns;

  unsigned int
    number_scenes,
    samples_per_pixel,
    bits_allocated,
    significant_bits,
    bytes_per_pixel,
    max_value_in,
    max_value_out,
    high_bit,
    pixel_representation,
    interlace;

  Dicom_MSB
    msb_state;

  Dicom_PI
    phot_interp;

  double
    window_center,
    window_width,
    rescale_intercept,
    rescale_slope;

  Dicom_TS
    transfer_syntax;

  Dicom_RT
    rescale_type;

  Dicom_RS
    rescaling;

  /*
    Array to store offset table for fragments within image
  */
  magick_uint32_t
    offset_ct;
  magick_uint32_t *
    offset_arr;

  /*
    Variables used to handle fragments and RLE compression
  */
  magick_uint32_t
    frag_bytes;

  magick_uint32_t
    rle_seg_ct,
    rle_seg_offsets[15];

  int
    rle_rep_ct,
    rle_rep_char;

  /*
    Max and minimum sample values within image used for post rescale mapping
  */
  int
    upper_lim,
    lower_lim;

  Quantum
    *rescale_map; /* Allocated with dcm->max_value_in+1 entries */

#if defined(USE_GRAYMAP)
  unsigned short
    *graymap;
#endif

  /*
    Values representing last read element
  */
  unsigned short
    group,
    element;

  int
    index,
    datum;

  size_t
    quantum,
    length;

  unsigned char *
    data;

  /*
    Remaining fields for internal use by DCM_ReadElement and to read data
  */
  DicomReadShortFunc *
    funcReadShort;

  DicomReadLongFunc *
    funcReadLong;

  int
    explicit_file;

  unsigned int
    verbose;
} DicomStream;

/*
  Function type for parsing DICOM elements
*/
typedef MagickPassFail (DicomElemParseFunc)(Image *Image,DicomStream *dcm,ExceptionInfo *exception);

/*
  Forward declaration for parser functions
*/
static DicomElemParseFunc funcDCM_TransferSyntax;
static DicomElemParseFunc funcDCM_StudyDate;
static DicomElemParseFunc funcDCM_PatientName;
static DicomElemParseFunc funcDCM_TriggerTime;
static DicomElemParseFunc funcDCM_FieldOfView;
static DicomElemParseFunc funcDCM_SeriesNumber;
static DicomElemParseFunc funcDCM_ImagePosition;
static DicomElemParseFunc funcDCM_ImageOrientation;
static DicomElemParseFunc funcDCM_SliceLocation;
static DicomElemParseFunc funcDCM_SamplesPerPixel;
static DicomElemParseFunc funcDCM_PhotometricInterpretation;
static DicomElemParseFunc funcDCM_PlanarConfiguration;
static DicomElemParseFunc funcDCM_NumberOfFrames;
static DicomElemParseFunc funcDCM_Rows;
static DicomElemParseFunc funcDCM_Columns;
static DicomElemParseFunc funcDCM_BitsAllocated;
static DicomElemParseFunc funcDCM_BitsStored;
static DicomElemParseFunc funcDCM_HighBit;
static DicomElemParseFunc funcDCM_PixelRepresentation;
static DicomElemParseFunc funcDCM_WindowCenter;
static DicomElemParseFunc funcDCM_WindowWidth;
static DicomElemParseFunc funcDCM_RescaleIntercept;
static DicomElemParseFunc funcDCM_RescaleSlope;
static DicomElemParseFunc funcDCM_RescaleType;
static DicomElemParseFunc funcDCM_PaletteDescriptor;
static DicomElemParseFunc funcDCM_LUT;
static DicomElemParseFunc funcDCM_Palette;

/*
  Type for holding information on DICOM elements
*/
#define DESCRIPION_STR 1 /* Description text elements in one big string */
typedef struct _DicomInfo
{
  const unsigned short
    group,
    element;

  const char
    vr[3];

#if !DESCRIPION_STR
  const char
    *description;
#endif /* DESCRIPION_STR */

  DicomElemParseFunc
    * const pfunc;
} DicomInfo;

/*
  Array holding information on DICOM elements
*/
static const DicomInfo
  dicom_info[]=
  {
#if DESCRIPION_STR
#define ENTRY(group, element, vr, description, pfunc) {group, element, vr, pfunc}
#else
#define ENTRY(group, element, vr, description, pfunc) {group, element, vr, description, pfunc}
#endif
    ENTRY( 0x0000, 0x0000, "UL", "Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0001, "UL", "Command Length to End", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0002, "UI", "Affected SOP Class UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0003, "UI", "Requested SOP Class UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0010, "LO", "Command Recognition Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0100, "US", "Command Field", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0110, "US", "Message ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0120, "US", "Message ID Being Responded To", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0200, "AE", "Initiator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0300, "AE", "Receiver", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0400, "AE", "Find Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0600, "AE", "Move Destination", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0700, "US", "Priority", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0800, "US", "Data Set Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0850, "US", "Number of Matches", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0860, "US", "Response Sequence Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0900, "US", "Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0901, "AT", "Offending Element", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0902, "LO", "Exception Comment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x0903, "US", "Exception ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1000, "UI", "Affected SOP Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1001, "UI", "Requested SOP Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1002, "US", "Event Type ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1005, "AT", "Attribute Identifier List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1008, "US", "Action Type ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1020, "US", "Number of Remaining Suboperations", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1021, "US", "Number of Completed Suboperations", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1022, "US", "Number of Failed Suboperations", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1023, "US", "Number of Warning Suboperations", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1030, "AE", "Move Originator Application Entity Title", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x1031, "US", "Move Originator Message ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x4000, "LO", "Dialog Receiver", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x4010, "LO", "Terminal Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5010, "SH", "Message Set ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5020, "SH", "End Message Set", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5110, "LO", "Display Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5120, "LO", "Page Position ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5130, "LO", "Text Format ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5140, "LO", "Normal Reverse", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5150, "LO", "Add Gray Scale", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5160, "LO", "Borders", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5170, "IS", "Copies", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5180, "LO", "OldMagnificationType", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x5190, "LO", "Erase", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x51a0, "LO", "Print", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0000, 0x51b0, "US", "Overlays", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0000, "UL", "Meta Element Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0001, "OB", "File Meta Information Version", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0002, "UI", "Media Storage SOP Class UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0003, "UI", "Media Storage SOP Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0010, "UI", "Transfer Syntax UID", (DicomElemParseFunc *) funcDCM_TransferSyntax ),
    ENTRY( 0x0002, 0x0012, "UI", "Implementation Class UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0013, "SH", "Implementation Version Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0016, "AE", "Source Application Entity Title", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0100, "UI", "Private Information Creator UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0002, 0x0102, "OB", "Private Information", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0000, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0008, "US", "ISI Command Field", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0011, "US", "Attach ID Application Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0012, "UL", "Attach ID Message Count", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0013, "DA", "Attach ID Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0014, "TM", "Attach ID Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0020, "US", "Message Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0030, "DA", "Max Waiting Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0003, 0x0031, "TM", "Max Waiting Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x0000, "UL", "File Set Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1130, "CS", "File Set ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1141, "CS", "File Set Descriptor File ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1142, "CS", "File Set Descriptor File Specific Character Set", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1200, "UL", "Root Directory Entity First Directory Record Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1202, "UL", "Root Directory Entity Last Directory Record Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1212, "US", "File Set Consistency Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1220, "SQ", "Directory Record Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1400, "UL", "Next Directory Record Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1410, "US", "Record In Use Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1420, "UL", "Referenced Lower Level Directory Entity Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1430, "CS", "Directory Record Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1432, "UI", "Private Record UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1500, "CS", "Referenced File ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1504, "UL", "MRDR Directory Record Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1510, "UI", "Referenced SOP Class UID In File", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1511, "UI", "Referenced SOP Instance UID In File", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1512, "UI", "Referenced Transfer Syntax UID In File", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0004, 0x1600, "UL", "Number of References", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0005, 0x0000, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0006, 0x0000, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0000, "UL", "Identifying Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0001, "UL", "Length to End", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0005, "CS", "Specific Character Set", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0008, "CS", "Image Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0010, "LO", "Recognition Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0012, "DA", "Instance Creation Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0013, "TM", "Instance Creation Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0014, "UI", "Instance Creator UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0016, "UI", "SOP Class UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0018, "UI", "SOP Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0020, "DA", "Study Date", (DicomElemParseFunc *) funcDCM_StudyDate ),
    ENTRY( 0x0008, 0x0021, "DA", "Series Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0022, "DA", "Acquisition Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0023, "DA", "Image Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0024, "DA", "Overlay Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0025, "DA", "Curve Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0030, "TM", "Study Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0031, "TM", "Series Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0032, "TM", "Acquisition Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0033, "TM", "Image Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0034, "TM", "Overlay Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0035, "TM", "Curve Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0040, "xs", "Old Data Set Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0041, "xs", "Old Data Set Subtype", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0042, "CS", "Nuclear Medicine Series Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0050, "SH", "Accession Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0052, "CS", "Query/Retrieve Level", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0054, "AE", "Retrieve AE Title", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0058, "UI", "Failed SOP Instance UID List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0060, "CS", "Modality", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0062, "SQ", "Modality Subtype", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0064, "CS", "Conversion Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0068, "CS", "Presentation Intent Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0070, "LO", "Manufacturer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0080, "LO", "Institution Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0081, "ST", "Institution Address", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0082, "SQ", "Institution Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0090, "PN", "Referring Physician's Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0092, "ST", "Referring Physician's Address", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0094, "SH", "Referring Physician's Telephone Numbers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0100, "SH", "Code Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0102, "SH", "Coding Scheme Designator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0103, "SH", "Coding Scheme Version", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0104, "LO", "Code Meaning", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0105, "CS", "Mapping Resource", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x0106, "DT", "Context Group Version", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x010b, "CS", "Code Set Extension Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x010c, "UI", "Private Coding Scheme Creator UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x010d, "UI", "Code Set Extension Creator UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x010f, "CS", "Context Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1000, "LT", "Network ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1010, "SH", "Station Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1030, "LO", "Study Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1032, "SQ", "Procedure Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x103e, "LO", "Series Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1040, "LO", "Institutional Department Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1048, "PN", "Physician of Record", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1050, "PN", "Performing Physician's Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1060, "PN", "Name of Physician(s) Reading Study", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1070, "PN", "Operator's Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1080, "LO", "Admitting Diagnosis Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1084, "SQ", "Admitting Diagnosis Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1090, "LO", "Manufacturer's Model Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1100, "SQ", "Referenced Results Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1110, "SQ", "Referenced Study Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1111, "SQ", "Referenced Study Component Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1115, "SQ", "Referenced Series Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1120, "SQ", "Referenced Patient Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1125, "SQ", "Referenced Visit Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1130, "SQ", "Referenced Overlay Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1140, "SQ", "Referenced Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1145, "SQ", "Referenced Curve Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1148, "SQ", "Referenced Previous Waveform", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x114a, "SQ", "Referenced Simultaneous Waveforms", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x114c, "SQ", "Referenced Subsequent Waveform", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1150, "UI", "Referenced SOP Class UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1155, "UI", "Referenced SOP Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1160, "IS", "Referenced Frame Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1195, "UI", "Transaction UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1197, "US", "Failure Reason", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1198, "SQ", "Failed SOP Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x1199, "SQ", "Referenced SOP Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2110, "CS", "Old Lossy Image Compression", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2111, "ST", "Derivation Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2112, "SQ", "Source Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2120, "SH", "Stage Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2122, "IS", "Stage Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2124, "IS", "Number of Stages", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2128, "IS", "View Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2129, "IS", "Number of Event Timers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x212a, "IS", "Number of Views in Stage", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2130, "DS", "Event Elapsed Time(s)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2132, "LO", "Event Timer Name(s)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2142, "IS", "Start Trim", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2143, "IS", "Stop Trim", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2144, "IS", "Recommended Display Frame Rate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2200, "CS", "Transducer Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2204, "CS", "Transducer Orientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2208, "CS", "Anatomic Structure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2218, "SQ", "Anatomic Region Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2220, "SQ", "Anatomic Region Modifier Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2228, "SQ", "Primary Anatomic Structure Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2230, "SQ", "Primary Anatomic Structure Modifier Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2240, "SQ", "Transducer Position Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2242, "SQ", "Transducer Position Modifier Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2244, "SQ", "Transducer Orientation Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2246, "SQ", "Transducer Orientation Modifier Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2251, "SQ", "Anatomic Structure Space Or Region Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2253, "SQ", "Anatomic Portal Of Entrance Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2255, "SQ", "Anatomic Approach Direction Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2256, "ST", "Anatomic Perspective Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2257, "SQ", "Anatomic Perspective Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2258, "ST", "Anatomic Location Of Examining Instrument Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x2259, "SQ", "Anatomic Location Of Examining Instrument Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x225a, "SQ", "Anatomic Structure Space Or Region Modifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x225c, "SQ", "OnAxis Background Anatomic Structure Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0008, 0x4000, "LT", "Identifying Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0000, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0001, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0002, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0003, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0004, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0005, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0006, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0007, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0008, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0009, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x000a, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x000b, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x000c, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x000d, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x000e, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x000f, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0011, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0012, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0013, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0014, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0015, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0016, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0017, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0018, "LT", "Data Set Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x001a, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x001e, "UI", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0020, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0021, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0022, "SH", "User Orientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0023, "SL", "Initiation Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0024, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0025, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0026, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0027, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0029, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x002a, "SL", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x002c, "LO", "Series Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x002d, "SL", "Track Beat Average", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x002e, "FD", "Distance Prescribed", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x002f, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0030, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0031, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0032, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0034, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0035, "SL", "Gantry Locus Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0037, "SL", "Starting Heart Rate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0038, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0039, "SL", "RR Window Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x003a, "SL", "Percent Cycle Imaged", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x003e, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x003f, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0040, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0041, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0042, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0043, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0050, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0051, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0060, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0061, "LT", "Series Unique Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0070, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0080, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x0091, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00e2, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00e3, "UI", "Equipment UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00e6, "SH", "Genesis Version Now", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00e7, "UL", "Exam Record Checksum", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00e8, "UL", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00e9, "SL", "Actual Series Data Time Stamp", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00f2, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00f3, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00f4, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00f5, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00f6, "LT", "PDM Data Object Type Extension", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00f8, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x00fb, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x1002, "OB", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x1003, "OB", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0009, 0x1010, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x0000, "UL", "Patient Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x0010, "PN", "Patient's Name", (DicomElemParseFunc *) funcDCM_PatientName ),
    ENTRY( 0x0010, 0x0020, "LO", "Patient's ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x0021, "LO", "Issuer of Patient's ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x0030, "DA", "Patient's Birth Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x0032, "TM", "Patient's Birth Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x0040, "CS", "Patient's Sex", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x0050, "SQ", "Patient's Insurance Plan Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1000, "LO", "Other Patient's ID's", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1001, "PN", "Other Patient's Names", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1005, "PN", "Patient's Birth Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1010, "AS", "Patient's Age", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1020, "DS", "Patient's Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1030, "DS", "Patient's Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1040, "LO", "Patient's Address", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1050, "LT", "Insurance Plan Identification", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1060, "PN", "Patient's Mother's Birth Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1080, "LO", "Military Rank", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1081, "LO", "Branch of Service", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x1090, "LO", "Medical Record Locator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x2000, "LO", "Medical Alerts", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x2110, "LO", "Contrast Allergies", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x2150, "LO", "Country of Residence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x2152, "LO", "Region of Residence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x2154, "SH", "Patients Telephone Numbers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x2160, "SH", "Ethnic Group", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x2180, "SH", "Occupation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x21a0, "CS", "Smoking Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x21b0, "LT", "Additional Patient History", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x21c0, "US", "Pregnancy Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x21d0, "DA", "Last Menstrual Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x21f0, "LO", "Patients Religious Preference", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0010, 0x4000, "LT", "Patient Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0001, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0002, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0003, "LT", "Patient UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0004, "LT", "Patient ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x000a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x000b, "SL", "Effective Series Duration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x000c, "SL", "Num Beats", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x000d, "LO", "Radio Nuclide Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0011, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0012, "LO", "Dataset Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0013, "LO", "Dataset Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0015, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0016, "SL", "Energy Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0017, "SL", "RR Interval Window Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0018, "SL", "MG Bin Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0019, "FD", "Radius Of Rotation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x001a, "SL", "Detector Count Zone", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x001b, "SL", "Num Energy Windows", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x001c, "SL", "Energy Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x001d, "SL", "Energy Range", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x001f, "SL", "Image Orientation", (DicomElemParseFunc *) funcDCM_ImageOrientation ),
    ENTRY( 0x0011, 0x0020, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0021, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0022, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0023, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0024, "SL", "FOV Mask Y Cutoff Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0025, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0026, "SL", "Table Orientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0027, "SL", "ROI Top Left", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0028, "SL", "ROI Bottom Right", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0030, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0031, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0032, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0033, "LO", "Energy Correct Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0034, "LO", "Spatial Correct Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0035, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0036, "LO", "Uniformity Correct Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0037, "LO", "Acquisition Specific Correct Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0038, "SL", "Byte Order", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x003a, "SL", "Picture Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x003b, "FD", "Pixel Scale", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x003c, "FD", "Pixel Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x003e, "SL", "FOV Shape", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x003f, "SL", "Dataset Flags", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0040, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0041, "LT", "Medical Alerts", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0042, "LT", "Contrast Allergies", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0044, "FD", "Threshold Center", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0045, "FD", "Threshold Width", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0046, "SL", "Interpolation Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0055, "FD", "Period", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x0056, "FD", "ElapsedTime", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00a1, "DA", "Patient Registration Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00a2, "TM", "Patient Registration Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00b0, "LT", "Patient Last Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00b2, "LT", "Patient First Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00b4, "LT", "Patient Hospital Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00bc, "TM", "Current Location Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00c0, "LT", "Patient Insurance Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00d0, "LT", "Patient Billing Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0011, 0x00d2, "LT", "Patient Billing Address", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0000, "LT", "Modifying Physician", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0011, "SL", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0012, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0016, "SL", "AutoTrack Peak", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0017, "SL", "AutoTrack Width", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0018, "FD", "Transmission Scan Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0019, "FD", "Transmission Mask Width", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x001a, "FD", "Copper Attenuator Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x001c, "FD", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x001d, "FD", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x001e, "FD", "Tomo View Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0020, "LT", "Patient Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0022, "LT", "Patient Id", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0026, "LT", "Study Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0030, "DA", "Patient Birthdate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0031, "DS", "Patient Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0032, "LT", "Patients Maiden Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0033, "LT", "Referring Physician", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0034, "LT", "Admitting Diagnosis", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0035, "LT", "Patient Sex", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0040, "LT", "Procedure Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0042, "LT", "Patient Rest Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0044, "LT", "Patient Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0013, 0x0046, "LT", "View Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0015, 0x0001, "DS", "Stenosis Calibration Ratio", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0015, 0x0002, "DS", "Stenosis Magnification", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0015, 0x0003, "DS", "Cardiac Calibration Ratio", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0000, "UL", "Acquisition Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0010, "LO", "Contrast/Bolus Agent", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0012, "SQ", "Contrast/Bolus Agent Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0014, "SQ", "Contrast/Bolus Administration Route Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0015, "CS", "Body Part Examined", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0020, "CS", "Scanning Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0021, "CS", "Sequence Variant", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0022, "CS", "Scan Options", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0023, "CS", "MR Acquisition Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0024, "SH", "Sequence Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0025, "CS", "Angio Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0026, "SQ", "Intervention Drug Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0027, "TM", "Intervention Drug Stop Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0028, "DS", "Intervention Drug Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0029, "SQ", "Intervention Drug Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x002a, "SQ", "Additional Drug Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0030, "LO", "Radionuclide", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0031, "LO", "Radiopharmaceutical", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0032, "DS", "Energy Window Centerline", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0033, "DS", "Energy Window Total Width", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0034, "LO", "Intervention Drug Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0035, "TM", "Intervention Drug Start Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0036, "SQ", "Intervention Therapy Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0037, "CS", "Therapy Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0038, "CS", "Intervention Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0039, "CS", "Therapy Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0040, "IS", "Cine Rate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0050, "DS", "Slice Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0060, "DS", "KVP", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0070, "IS", "Counts Accumulated", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0071, "CS", "Acquisition Termination Condition", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0072, "DS", "Effective Series Duration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0073, "CS", "Acquisition Start Condition", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0074, "IS", "Acquisition Start Condition Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0075, "IS", "Acquisition Termination Condition Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0080, "DS", "Repetition Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0081, "DS", "Echo Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0082, "DS", "Inversion Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0083, "DS", "Number of Averages", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0084, "DS", "Imaging Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0085, "SH", "Imaged Nucleus", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0086, "IS", "Echo Number(s)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0087, "DS", "Magnetic Field Strength", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0088, "DS", "Spacing Between Slices", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0089, "IS", "Number of Phase Encoding Steps", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0090, "DS", "Data Collection Diameter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0091, "IS", "Echo Train Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0093, "DS", "Percent Sampling", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0094, "DS", "Percent Phase Field of View", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x0095, "DS", "Pixel Bandwidth", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1000, "LO", "Device Serial Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1004, "LO", "Plate ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1010, "LO", "Secondary Capture Device ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1012, "DA", "Date of Secondary Capture", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1014, "TM", "Time of Secondary Capture", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1016, "LO", "Secondary Capture Device Manufacturer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1018, "LO", "Secondary Capture Device Manufacturer Model Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1019, "LO", "Secondary Capture Device Software Version(s)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1020, "LO", "Software Version(s)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1022, "SH", "Video Image Format Acquired", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1023, "LO", "Digital Image Format Acquired", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1030, "LO", "Protocol Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1040, "LO", "Contrast/Bolus Route", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1041, "DS", "Contrast/Bolus Volume", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1042, "TM", "Contrast/Bolus Start Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1043, "TM", "Contrast/Bolus Stop Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1044, "DS", "Contrast/Bolus Total Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1045, "IS", "Syringe Counts", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1046, "DS", "Contrast Flow Rate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1047, "DS", "Contrast Flow Duration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1048, "CS", "Contrast/Bolus Ingredient", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1049, "DS", "Contrast/Bolus Ingredient Concentration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1050, "DS", "Spatial Resolution", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1060, "DS", "Trigger Time", (DicomElemParseFunc *) funcDCM_TriggerTime ),
    ENTRY( 0x0018, 0x1061, "LO", "Trigger Source or Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1062, "IS", "Nominal Interval", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1063, "DS", "Frame Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1064, "LO", "Framing Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1065, "DS", "Frame Time Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1066, "DS", "Frame Delay", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1067, "DS", "Image Trigger Delay", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1068, "DS", "Group Time Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1069, "DS", "Trigger Time Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x106a, "CS", "Synchronization Trigger", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x106b, "UI", "Synchronization Frame of Reference", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x106e, "UL", "Trigger Sample Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1070, "LO", "Radiopharmaceutical Route", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1071, "DS", "Radiopharmaceutical Volume", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1072, "TM", "Radiopharmaceutical Start Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1073, "TM", "Radiopharmaceutical Stop Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1074, "DS", "Radionuclide Total Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1075, "DS", "Radionuclide Half Life", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1076, "DS", "Radionuclide Positron Fraction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1077, "DS", "Radiopharmaceutical Specific Activity", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1080, "CS", "Beat Rejection Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1081, "IS", "Low R-R Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1082, "IS", "High R-R Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1083, "IS", "Intervals Acquired", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1084, "IS", "Intervals Rejected", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1085, "LO", "PVC Rejection", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1086, "IS", "Skip Beats", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1088, "IS", "Heart Rate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1090, "IS", "Cardiac Number of Images", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1094, "IS", "Trigger Window", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1100, "DS", "Reconstruction Diameter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1110, "DS", "Distance Source to Detector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1111, "DS", "Distance Source to Patient", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1114, "DS", "Estimated Radiographic Magnification Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1120, "DS", "Gantry/Detector Tilt", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1121, "DS", "Gantry/Detector Slew", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1130, "DS", "Table Height", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1131, "DS", "Table Traverse", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1134, "CS", "Table Motion", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1135, "DS", "Table Vertical Increment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1136, "DS", "Table Lateral Increment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1137, "DS", "Table Longitudinal Increment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1138, "DS", "Table Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x113a, "CS", "Table Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1140, "CS", "Rotation Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1141, "DS", "Angular Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1142, "DS", "Radial Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1143, "DS", "Scan Arc", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1144, "DS", "Angular Step", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1145, "DS", "Center of Rotation Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1146, "DS", "Rotation Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1147, "CS", "Field of View Shape", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1149, "IS", "Field of View Dimension(s)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1150, "IS", "Exposure Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1151, "IS", "X-ray Tube Current", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1152, "IS", "Exposure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1153, "IS", "Exposure in uAs", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1154, "DS", "AveragePulseWidth", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1155, "CS", "RadiationSetting", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1156, "CS", "Rectification Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x115a, "CS", "RadiationMode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x115e, "DS", "ImageAreaDoseProduct", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1160, "SH", "Filter Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1161, "LO", "TypeOfFilters", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1162, "DS", "IntensifierSize", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1164, "DS", "ImagerPixelSpacing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1166, "CS", "Grid", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1170, "IS", "Generator Power", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1180, "SH", "Collimator/Grid Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1181, "CS", "Collimator Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1182, "IS", "Focal Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1183, "DS", "X Focus Center", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1184, "DS", "Y Focus Center", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1190, "DS", "Focal Spot(s)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1191, "CS", "Anode Target Material", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x11a0, "DS", "Body Part Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x11a2, "DS", "Compression Force", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1200, "DA", "Date of Last Calibration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1201, "TM", "Time of Last Calibration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1210, "SH", "Convolution Kernel", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1240, "IS", "Upper/Lower Pixel Values", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1242, "IS", "Actual Frame Duration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1243, "IS", "Count Rate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1244, "US", "Preferred Playback Sequencing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1250, "SH", "Receiving Coil", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1251, "SH", "Transmitting Coil", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1260, "SH", "Plate Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1261, "LO", "Phosphor Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1300, "DS", "Scan Velocity", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1301, "CS", "Whole Body Technique", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1302, "IS", "Scan Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1310, "US", "Acquisition Matrix", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1312, "CS", "Phase Encoding Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1314, "DS", "Flip Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1315, "CS", "Variable Flip Angle Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1316, "DS", "SAR", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1318, "DS", "dB/dt", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1400, "LO", "Acquisition Device Processing Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1401, "LO", "Acquisition Device Processing Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1402, "CS", "Cassette Orientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1403, "CS", "Cassette Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1404, "US", "Exposures on Plate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1405, "IS", "Relative X-ray Exposure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1450, "DS", "Column Angulation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1460, "DS", "Tomo Layer Height", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1470, "DS", "Tomo Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1480, "DS", "Tomo Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1490, "CS", "Tomo Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1491, "CS", "Tomo Class", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1495, "IS", "Number of Tomosynthesis Source Images", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1500, "CS", "PositionerMotion", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1508, "CS", "Positioner Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1510, "DS", "PositionerPrimaryAngle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1511, "DS", "PositionerSecondaryAngle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1520, "DS", "PositionerPrimaryAngleIncrement", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1521, "DS", "PositionerSecondaryAngleIncrement", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1530, "DS", "DetectorPrimaryAngle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1531, "DS", "DetectorSecondaryAngle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1600, "CS", "Shutter Shape", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1602, "IS", "Shutter Left Vertical Edge", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1604, "IS", "Shutter Right Vertical Edge", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1606, "IS", "Shutter Upper Horizontal Edge", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1608, "IS", "Shutter Lower Horizonta lEdge", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1610, "IS", "Center of Circular Shutter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1612, "IS", "Radius of Circular Shutter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1620, "IS", "Vertices of Polygonal Shutter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1622, "US", "Shutter Presentation Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1623, "US", "Shutter Overlay Group", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1700, "CS", "Collimator Shape", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1702, "IS", "Collimator Left Vertical Edge", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1704, "IS", "Collimator Right Vertical Edge", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1706, "IS", "Collimator Upper Horizontal Edge", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1708, "IS", "Collimator Lower Horizontal Edge", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1710, "IS", "Center of Circular Collimator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1712, "IS", "Radius of Circular Collimator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1720, "IS", "Vertices of Polygonal Collimator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1800, "CS", "Acquisition Time Synchronized", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1801, "SH", "Time Source", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x1802, "CS", "Time Distribution Protocol", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x4000, "LT", "Acquisition Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5000, "SH", "Output Power", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5010, "LO", "Transducer Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5012, "DS", "Focus Depth", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5020, "LO", "Processing Function", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5021, "LO", "Postprocessing Function", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5022, "DS", "Mechanical Index", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5024, "DS", "Thermal Index", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5026, "DS", "Cranial Thermal Index", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5027, "DS", "Soft Tissue Thermal Index", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5028, "DS", "Soft Tissue-Focus Thermal Index", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5029, "DS", "Soft Tissue-Surface Thermal Index", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5030, "DS", "Dynamic Range", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5040, "DS", "Total Gain", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5050, "IS", "Depth of Scan Field", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5100, "CS", "Patient Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5101, "CS", "View Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5104, "SQ", "Projection Eponymous Name Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5210, "DS", "Image Transformation Matrix", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x5212, "DS", "Image Translation Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6000, "DS", "Sensitivity", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6011, "IS", "Sequence of Ultrasound Regions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6012, "US", "Region Spatial Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6014, "US", "Region Data Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6016, "UL", "Region Flags", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6018, "UL", "Region Location Min X0", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x601a, "UL", "Region Location Min Y0", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x601c, "UL", "Region Location Max X1", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x601e, "UL", "Region Location Max Y1", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6020, "SL", "Reference Pixel X0", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6022, "SL", "Reference Pixel Y0", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6024, "US", "Physical Units X Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6026, "US", "Physical Units Y Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6028, "FD", "Reference Pixel Physical Value X", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x602a, "US", "Reference Pixel Physical Value Y", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x602c, "US", "Physical Delta X", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x602e, "US", "Physical Delta Y", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6030, "UL", "Transducer Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6031, "CS", "Transducer Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6032, "UL", "Pulse Repetition Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6034, "FD", "Doppler Correction Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6036, "FD", "Steering Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6038, "UL", "Doppler Sample Volume X Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x603a, "UL", "Doppler Sample Volume Y Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x603c, "UL", "TM-Line Position X0", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x603e, "UL", "TM-Line Position Y0", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6040, "UL", "TM-Line Position X1", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6042, "UL", "TM-Line Position Y1", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6044, "US", "Pixel Component Organization", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6046, "UL", "Pixel Component Mask", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6048, "UL", "Pixel Component Range Start", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x604a, "UL", "Pixel Component Range Stop", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x604c, "US", "Pixel Component Physical Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x604e, "US", "Pixel Component Data Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6050, "UL", "Number of Table Break Points", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6052, "UL", "Table of X Break Points", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6054, "FD", "Table of Y Break Points", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6056, "UL", "Number of Table Entries", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x6058, "UL", "Table of Pixel Values", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x605a, "FL", "Table of Parameter Values", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7000, "CS", "Detector Conditions Nominal Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7001, "DS", "Detector Temperature", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7004, "CS", "Detector Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7005, "CS", "Detector Configuration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7006, "LT", "Detector Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7008, "LT", "Detector Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x700a, "SH", "Detector ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x700c, "DA", "Date of Last Detector Calibration ", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x700e, "TM", "Time of Last Detector Calibration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7010, "IS", "Exposures on Detector Since Last Calibration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7011, "IS", "Exposures on Detector Since Manufactured", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7012, "DS", "Detector Time Since Last Exposure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7014, "DS", "Detector Active Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7016, "DS", "Detector Activation Offset From Exposure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x701a, "DS", "Detector Binning", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7020, "DS", "Detector Element Physical Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7022, "DS", "Detector Element Spacing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7024, "CS", "Detector Active Shape", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7026, "DS", "Detector Active Dimensions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7028, "DS", "Detector Active Origin", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7030, "DS", "Field of View Origin", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7032, "DS", "Field of View Rotation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7034, "CS", "Field of View Horizontal Flip", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7040, "LT", "Grid Absorbing Material", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7041, "LT", "Grid Spacing Material", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7042, "DS", "Grid Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7044, "DS", "Grid Pitch", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7046, "IS", "Grid Aspect Ratio", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7048, "DS", "Grid Period", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x704c, "DS", "Grid Focal Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7050, "LT", "Filter Material", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7052, "DS", "Filter Thickness Minimum", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7054, "DS", "Filter Thickness Maximum", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7060, "CS", "Exposure Control Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7062, "LT", "Exposure Control Mode Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7064, "CS", "Exposure Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0018, 0x7065, "DS", "Phototimer Setting", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0000, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0001, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0002, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0003, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0004, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0005, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0006, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0007, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0008, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0009, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x000a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x000b, "DS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x000c, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x000d, "TM", "Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x000e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x000f, "DS", "Horizontal Frame Of Reference", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0011, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0012, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0013, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0014, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0015, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0016, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0017, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0018, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0019, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x001a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x001b, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x001c, "CS", "Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x001d, "IS", "Side Mark", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x001e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x001f, "DS", "Exposure Duration", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0020, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0021, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0022, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0023, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0024, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0025, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0026, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0027, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0028, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0029, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x002a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x002b, "DS", "Xray Off Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x002c, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x002d, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x002e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x002f, "DS", "Trigger Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0030, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0031, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0032, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0033, "UN", "ECG 2 Offset 2", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0034, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0036, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0038, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0039, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x003a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x003b, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x003c, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x003e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x003f, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0040, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0041, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0042, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0043, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0044, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0045, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0046, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0047, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0048, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0049, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x004a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x004b, "SL", "Data Size For Scan Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x004c, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x004e, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0050, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0051, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0052, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0053, "LT", "Barcode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0054, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0055, "DS", "Receiver Reference Gain", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0056, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0057, "SS", "CT Water Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0058, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x005a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x005c, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x005d, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x005e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x005f, "SL", "Increment Between Channels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0060, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0061, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0062, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0063, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0064, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0065, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0066, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0067, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0068, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0069, "UL", "Convolution Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x006a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x006b, "SS", "Field Of View In Detector Cells", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x006c, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x006e, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0070, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0071, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0072, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0073, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0074, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0075, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0076, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0077, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0078, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x007a, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x007c, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x007d, "DS", "Second Echo", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x007e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x007f, "DS", "Table Delta", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0080, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0081, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0082, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0083, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0084, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0085, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0086, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0087, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0088, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x008a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x008b, "SS", "Actual Receive Gain Digital", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x008c, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x008d, "DS", "Delay After Trigger", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x008e, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x008f, "SS", "Swap Phase Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0090, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0091, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0092, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0093, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0094, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0095, "SS", "Analog Receiver Gain", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0096, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0097, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0098, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x0099, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x009a, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x009b, "SS", "Pulse Sequence Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x009c, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x009d, "DT", "Pulse Sequence Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x009e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x009f, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a0, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a1, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a2, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a3, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a4, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a5, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a6, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a7, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a8, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00a9, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00aa, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00ab, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00ac, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00ad, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00ae, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00af, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b0, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b1, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b2, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b3, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b4, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b5, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b6, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b7, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b8, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00b9, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00ba, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00bb, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00bc, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00bd, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00be, "DS", "Projection Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c0, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c1, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c2, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c3, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c4, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c5, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c6, "SS", "SAT Location H", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c7, "SS", "SAT Location F", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c8, "SS", "SAT Thickness R L", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00c9, "SS", "SAT Thickness A P", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00ca, "SS", "SAT Thickness H F", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00cb, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00cc, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00cd, "SS", "Thickness Disclaimer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00ce, "SS", "Prescan Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00cf, "SS", "Prescan Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d0, "SH", "Raw Data Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d1, "DS", "Flow Sensitivity", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d2, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d3, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d4, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d5, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d6, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d7, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d8, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00d9, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00da, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00db, "DS", "Back Projector Coefficient", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00dc, "SS", "Primary Speed Correction Used", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00dd, "SS", "Overrange Correction Used", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00de, "DS", "Dynamic Z Alpha Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00df, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e0, "DS", "User Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e1, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e2, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e3, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e4, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e5, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e6, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e8, "DS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00e9, "DS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00eb, "DS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00ec, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00f0, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00f1, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00f2, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00f3, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00f4, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x00f9, "DS", "Transmission Gain", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0019, 0x1015, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0000, "UL", "Relationship Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x000d, "UI", "Study Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x000e, "UI", "Series Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0010, "SH", "Study ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0011, "IS", "Series Number", (DicomElemParseFunc *) funcDCM_SeriesNumber ),
    ENTRY( 0x0020, 0x0012, "IS", "Acquisition Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0013, "IS", "Instance (formerly Image) Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0014, "IS", "Isotope Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0015, "IS", "Phase Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0016, "IS", "Interval Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0017, "IS", "Time Slot Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0018, "IS", "Angle Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0020, "CS", "Patient Orientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0022, "IS", "Overlay Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0024, "IS", "Curve Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0026, "IS", "LUT Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0030, "DS", "Image Position", (DicomElemParseFunc *) funcDCM_ImagePosition ),
    ENTRY( 0x0020, 0x0032, "DS", "Image Position (Patient)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0035, "DS", "Image Orientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0037, "DS", "Image Orientation (Patient)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0050, "DS", "Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0052, "UI", "Frame of Reference UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0060, "CS", "Laterality", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0062, "CS", "Image Laterality", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0070, "LT", "Image Geometry Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0080, "LO", "Masking Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0100, "IS", "Temporal Position Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0105, "IS", "Number of Temporal Positions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x0110, "DS", "Temporal Resolution", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1000, "IS", "Series in Study", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1001, "DS", "Acquisitions in Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1002, "IS", "Images in Acquisition", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1003, "IS", "Images in Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1004, "IS", "Acquisitions in Study", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1005, "IS", "Images in Study", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1020, "LO", "Reference", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1040, "LO", "Position Reference Indicator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1041, "DS", "Slice Location", (DicomElemParseFunc *) funcDCM_SliceLocation ),
    ENTRY( 0x0020, 0x1070, "IS", "Other Study Numbers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1200, "IS", "Number of Patient Related Studies", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1202, "IS", "Number of Patient Related Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1204, "IS", "Number of Patient Related Images", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1206, "IS", "Number of Study Related Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x1208, "IS", "Number of Study Related Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x3100, "LO", "Source Image IDs", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x3401, "LO", "Modifying Device ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x3402, "LO", "Modified Image ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x3403, "xs", "Modified Image Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x3404, "LO", "Modifying Device Manufacturer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x3405, "xs", "Modified Image Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x3406, "xs", "Modified Image Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x4000, "LT", "Image Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x5000, "AT", "Original Image Identification", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0020, 0x5002, "LO", "Original Image Identification Nomenclature", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0000, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0001, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0002, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0003, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0004, "DS", "VOI Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0005, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0006, "IS", "CSI Matrix Size Original", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0007, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0008, "DS", "Spatial Grid Shift", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0009, "DS", "Signal Limits Minimum", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0011, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0012, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0013, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0014, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0015, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0016, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0017, "DS", "EPI Operation Mode Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0018, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0019, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0020, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0021, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0022, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0024, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0025, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0026, "IS", "Image Pixel Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0030, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0031, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0032, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0034, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0035, "SS", "Series From Which Prescribed", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0036, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0037, "SS", "Screen Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0039, "DS", "Slab Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0040, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0041, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0042, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0043, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0044, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0045, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0046, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0047, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0048, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0049, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x004a, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x004e, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x004f, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0050, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0051, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0052, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0053, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0054, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0055, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0056, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0057, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0058, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0059, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x005a, "SL", "Integer Slop", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x005b, "DS", "Float Slop", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x005c, "DS", "Float Slop", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x005d, "DS", "Float Slop", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x005e, "DS", "Float Slop", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x005f, "DS", "Float Slop", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0060, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0061, "DS", "Image Normal", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0062, "IS", "Reference Type Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0063, "DS", "Image Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0065, "US", "Image Positioning History Mask", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x006a, "DS", "Image Row", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x006b, "DS", "Image Column", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0070, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0071, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0072, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0073, "DS", "Second Repetition Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0075, "DS", "Light Brightness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0076, "DS", "Light Contrast", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x007a, "IS", "Overlay Threshold", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x007b, "IS", "Surface Threshold", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x007c, "IS", "Grey Scale Threshold", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0080, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0081, "DS", "Auto Window Level Alpha", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0082, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0083, "DS", "Auto Window Level Window", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0084, "DS", "Auto Window Level Level", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0090, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0091, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0092, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0093, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0094, "DS", "EPI Change Value of X Component", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0095, "DS", "EPI Change Value of Y Component", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x0096, "DS", "EPI Change Value of Z Component", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x00a0, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x00a1, "DS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x00a2, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x00a3, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x00a4, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x00a7, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x00b0, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0021, 0x00c0, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0000, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0001, "SL", "Number Of Series In Study", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0002, "SL", "Number Of Unarchived Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0020, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0030, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0040, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0050, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0060, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0070, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0074, "SL", "Number Of Updates To Info", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x007d, "SS", "Indicates If Study Has Complete Info", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0080, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x0090, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0023, 0x00ff, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0000, "UL", "Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0006, "SS", "Last Pulse Sequence Used", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0007, "SL", "Images In Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0010, "SS", "Landmark Counter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0011, "SS", "Number Of Acquisitions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0014, "SL", "Indicates Number Of Updates To Info", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0017, "SL", "Series Complete Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0018, "SL", "Number Of Images Archived", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x0019, "SL", "Last Image Number Used", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0025, 0x001a, "SH", "Primary Receiver Suite And Host", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0000, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0006, "SL", "Image Archive Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0010, "SS", "Scout Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0011, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0012, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0013, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0014, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0015, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0016, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x001c, "SL", "Vma Mamp", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x001d, "SS", "Vma Phase", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x001e, "SL", "Vma Mod", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x001f, "SL", "Vma Clip", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0020, "SS", "Smart Scan On Off Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0030, "SH", "Foreign Image Revision", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0031, "SS", "Imaging Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0032, "SS", "Pulse Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0033, "SL", "Imaging Options", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0035, "SS", "Plane Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0036, "SL", "Oblique Plane", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0040, "SH", "RAS Letter Of Image Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0041, "FL", "Image Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0042, "FL", "Center R Coord Of Plane Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0043, "FL", "Center A Coord Of Plane Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0044, "FL", "Center S Coord Of Plane Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0045, "FL", "Normal R Coord", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0046, "FL", "Normal A Coord", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0047, "FL", "Normal S Coord", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0048, "FL", "R Coord Of Top Right Corner", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0049, "FL", "A Coord Of Top Right Corner", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x004a, "FL", "S Coord Of Top Right Corner", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x004b, "FL", "R Coord Of Bottom Right Corner", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x004c, "FL", "A Coord Of Bottom Right Corner", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x004d, "FL", "S Coord Of Bottom Right Corner", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0050, "FL", "Table Start Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0051, "FL", "Table End Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0052, "SH", "RAS Letter For Side Of Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0053, "SH", "RAS Letter For Anterior Posterior", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0054, "SH", "RAS Letter For Scout Start Loc", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0055, "SH", "RAS Letter For Scout End Loc", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0060, "FL", "Image Dimension X", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0061, "FL", "Image Dimension Y", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0027, 0x0062, "FL", "Number Of Excitations", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0000, "UL", "Image Presentation Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0002, "US", "Samples per Pixel", (DicomElemParseFunc *) funcDCM_SamplesPerPixel ),
    ENTRY( 0x0028, 0x0004, "CS", "Photometric Interpretation", (DicomElemParseFunc *) funcDCM_PhotometricInterpretation ),
    ENTRY( 0x0028, 0x0005, "US", "Image Dimensions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0006, "US", "Planar Configuration", (DicomElemParseFunc *) funcDCM_PlanarConfiguration ),
    ENTRY( 0x0028, 0x0008, "IS", "Number of Frames", (DicomElemParseFunc *) funcDCM_NumberOfFrames ),
    ENTRY( 0x0028, 0x0009, "AT", "Frame Increment Pointer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0010, "US", "Rows", (DicomElemParseFunc *) funcDCM_Rows ),
    ENTRY( 0x0028, 0x0011, "US", "Columns", (DicomElemParseFunc *) funcDCM_Columns ),
    ENTRY( 0x0028, 0x0012, "US", "Planes", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0014, "US", "Ultrasound Color Data Present", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0030, "DS", "Pixel Spacing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0031, "DS", "Zoom Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0032, "DS", "Zoom Center", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0034, "IS", "Pixel Aspect Ratio", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0040, "LO", "Image Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0050, "LT", "Manipulated Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0051, "CS", "Corrected Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x005f, "LO", "Compression Recognition Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0060, "LO", "Compression Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0061, "SH", "Compression Originator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0062, "SH", "Compression Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0063, "SH", "Compression Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0065, "LO", "Compression Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0066, "AT", "Compression Step Pointers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0068, "US", "Repeat Interval", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0069, "US", "Bits Grouped", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0070, "US", "Perimeter Table", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0071, "xs", "Perimeter Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0080, "US", "Predictor Rows", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0081, "US", "Predictor Columns", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0082, "US", "Predictor Constants", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0090, "LO", "Blocked Pixels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0091, "US", "Block Rows", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0092, "US", "Block Columns", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0093, "US", "Row Overlap", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0094, "US", "Column Overlap", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0100, "US", "Bits Allocated", (DicomElemParseFunc *) funcDCM_BitsAllocated ),
    ENTRY( 0x0028, 0x0101, "US", "Bits Stored", (DicomElemParseFunc *) funcDCM_BitsStored ),
    ENTRY( 0x0028, 0x0102, "US", "High Bit", (DicomElemParseFunc *) funcDCM_HighBit ),
    ENTRY( 0x0028, 0x0103, "US", "Pixel Representation", (DicomElemParseFunc *) funcDCM_PixelRepresentation ),
    ENTRY( 0x0028, 0x0104, "xs", "Smallest Valid Pixel Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0105, "xs", "Largest Valid Pixel Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0106, "xs", "Smallest Image Pixel Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0107, "xs", "Largest Image Pixel Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0108, "xs", "Smallest Pixel Value in Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0109, "xs", "Largest Pixel Value in Series", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0110, "xs", "Smallest Pixel Value in Plane", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0111, "xs", "Largest Pixel Value in Plane", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0120, "xs", "Pixel Padding Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0121, "xs", "Pixel Padding Range Limit", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0200, "xs", "Image Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0300, "CS", "Quality Control Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0301, "CS", "Burned In Annotation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0400, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0401, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0402, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0403, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0404, "AT", "Details of Coefficients", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0700, "LO", "DCT Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0701, "LO", "Data Block Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0702, "AT", "Data Block", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0710, "US", "Normalization Factor Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0720, "US", "Zonal Map Number Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0721, "AT", "Zonal Map Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0722, "US", "Zonal Map Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0730, "US", "Adaptive Map Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0740, "US", "Code Number Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0800, "LO", "Code Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0802, "US", "Number of Tables", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0803, "AT", "Code Table Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0804, "US", "Bits For Code Word", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x0808, "AT", "Image Data Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1040, "CS", "Pixel Intensity Relationship", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1041, "SS", "Pixel Intensity Relationship Sign", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1050, "DS", "Window Center", (DicomElemParseFunc *) funcDCM_WindowCenter ),
    ENTRY( 0x0028, 0x1051, "DS", "Window Width", (DicomElemParseFunc *) funcDCM_WindowWidth ),
    ENTRY( 0x0028, 0x1052, "DS", "Rescale Intercept", (DicomElemParseFunc *) funcDCM_RescaleIntercept ),
    ENTRY( 0x0028, 0x1053, "DS", "Rescale Slope", (DicomElemParseFunc *) funcDCM_RescaleSlope ),
    ENTRY( 0x0028, 0x1054, "LO", "Rescale Type", (DicomElemParseFunc *) funcDCM_RescaleType ),
    ENTRY( 0x0028, 0x1055, "LO", "Window Center & Width Explanation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1080, "LO", "Gray Scale", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1090, "CS", "Recommended Viewing Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1100, "xs", "Gray Lookup Table Descriptor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1101, "xs", "Red Palette Color Lookup Table Descriptor", (DicomElemParseFunc *) funcDCM_PaletteDescriptor ),
    ENTRY( 0x0028, 0x1102, "xs", "Green Palette Color Lookup Table Descriptor", (DicomElemParseFunc *) funcDCM_PaletteDescriptor ),
    ENTRY( 0x0028, 0x1103, "xs", "Blue Palette Color Lookup Table Descriptor", (DicomElemParseFunc *) funcDCM_PaletteDescriptor ),
    ENTRY( 0x0028, 0x1111, "OW", "Large Red Palette Color Lookup Table Descriptor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1112, "OW", "Large Green Palette Color Lookup Table Descriptor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1113, "OW", "Large Blue Palette Color Lookup Table Descriptor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1199, "UI", "Palette Color Lookup Table UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1200, "xs", "Gray Lookup Table Data", (DicomElemParseFunc *) funcDCM_LUT ),
    ENTRY( 0x0028, 0x1201, "OW", "Red Palette Color Lookup Table Data", (DicomElemParseFunc *) funcDCM_Palette ),
    ENTRY( 0x0028, 0x1202, "OW", "Green Palette Color Lookup Table Data", (DicomElemParseFunc *) funcDCM_Palette ),
    ENTRY( 0x0028, 0x1203, "OW", "Blue Palette Color Lookup Table Data", (DicomElemParseFunc *) funcDCM_Palette ),
    ENTRY( 0x0028, 0x1211, "OW", "Large Red Palette Color Lookup Table Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1212, "OW", "Large Green Palette Color Lookup Table Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1213, "OW", "Large Blue Palette Color Lookup Table Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1214, "UI", "Large Palette Color Lookup Table UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1221, "OW", "Segmented Red Palette Color Lookup Table Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1222, "OW", "Segmented Green Palette Color Lookup Table Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1223, "OW", "Segmented Blue Palette Color Lookup Table Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x1300, "CS", "Implant Present", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x2110, "CS", "Lossy Image Compression", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x2112, "DS", "Lossy Image Compression Ratio", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x3000, "SQ", "Modality LUT Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x3002, "US", "LUT Descriptor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x3003, "LO", "LUT Explanation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x3004, "LO", "Modality LUT Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x3006, "US", "LUT Data", (DicomElemParseFunc *) funcDCM_LUT ),
    ENTRY( 0x0028, 0x3010, "xs", "VOI LUT Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x4000, "LT", "Image Presentation Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x5000, "SQ", "Biplane Acquisition Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6010, "US", "Representative Frame Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6020, "US", "Frame Numbers of Interest", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6022, "LO", "Frame of Interest Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6030, "US", "Mask Pointer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6040, "US", "R Wave Pointer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6100, "SQ", "Mask Subtraction Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6101, "CS", "Mask Operation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6102, "US", "Applicable Frame Range", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6110, "US", "Mask Frame Numbers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6112, "US", "Contrast Frame Averaging", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6114, "FL", "Mask Sub-Pixel Shift", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6120, "SS", "TID Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0028, 0x6190, "ST", "Mask Operation Explanation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0000, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0001, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0002, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0003, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0004, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0005, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0006, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0007, "SL", "Lower Range Of Pixels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0008, "SH", "Lower Range Of Pixels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0009, "SH", "Lower Range Of Pixels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x000a, "SS", "Lower Range Of Pixels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x000c, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x000e, "CS", "Zoom Enable Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x000f, "CS", "Zoom Select Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0011, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0013, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0015, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0016, "SL", "Lower Range Of Pixels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0017, "SL", "Lower Range Of Pixels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0018, "SL", "Upper Range Of Pixels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x001a, "SL", "Length Of Total Info In Bytes", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x001e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x001f, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0020, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0022, "IS", "Pixel Quality Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0025, "LT", "Processed Pixel Data Quality", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0026, "SS", "Version Of Info Structure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0030, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0031, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0032, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0033, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0034, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0035, "SL", "Advantage Comp Underflow", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0038, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0040, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0041, "DS", "Magnifying Glass Rectangle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0043, "DS", "Magnifying Glass Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0044, "US", "Magnifying Glass Function", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x004e, "CS", "Magnifying Glass Enable Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x004f, "CS", "Magnifying Glass Select Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0050, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0051, "LT", "Exposure Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0052, "LT", "Sort Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0053, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0060, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0061, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0067, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0070, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0071, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0072, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0077, "CS", "Window Select Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0078, "LT", "ECG Display Printing ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0079, "CS", "ECG Display Printing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x007e, "CS", "ECG Display Printing Enable Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x007f, "CS", "ECG Display Printing Select Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0080, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0081, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0082, "IS", "View Zoom", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0083, "IS", "View Transform", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x008e, "CS", "Physiological Display Enable Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x008f, "CS", "Physiological Display Select Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0090, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x0099, "LT", "Shutter Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00a0, "US", "Rows of Rectangular Shutter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00a1, "US", "Columns of Rectangular Shutter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00a2, "US", "Origin of Rectangular Shutter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00b0, "US", "Radius of Circular Shutter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00b2, "US", "Origin of Circular Shutter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00c0, "LT", "Functional Shutter ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00c1, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00c3, "IS", "Scan Resolution", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00c4, "IS", "Field of View", (DicomElemParseFunc *) funcDCM_FieldOfView ),
    ENTRY( 0x0029, 0x00c5, "LT", "Field Of Shutter Rectangle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00ce, "CS", "Shutter Enable Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00cf, "CS", "Shutter Select Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00d0, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00d1, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0029, 0x00d5, "LT", "Slice Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x0010, "LT", "Request UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x0012, "LT", "Examination Reason", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x0030, "DA", "Requested Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x0032, "TM", "Worklist Request Start Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x0033, "TM", "Worklist Request End Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x0045, "LT", "Requesting Physician", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x004a, "TM", "Requested Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x0050, "LT", "Requested Physician", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0031, 0x0080, "LT", "Requested Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x0000, "UL", "Study Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x000a, "CS", "Study Status ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x000c, "CS", "Study Priority ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x0012, "LO", "Study ID Issuer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x0032, "DA", "Study Verified Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x0033, "TM", "Study Verified Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x0034, "DA", "Study Read Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x0035, "TM", "Study Read Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1000, "DA", "Scheduled Study Start Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1001, "TM", "Scheduled Study Start Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1010, "DA", "Scheduled Study Stop Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1011, "TM", "Scheduled Study Stop Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1020, "LO", "Scheduled Study Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1021, "AE", "Scheduled Study Location AE Title(s)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1030, "LO", "Reason for Study", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1032, "PN", "Requesting Physician", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1033, "LO", "Requesting Service", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1040, "DA", "Study Arrival Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1041, "TM", "Study Arrival Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1050, "DA", "Study Completion Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1051, "TM", "Study Completion Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1055, "CS", "Study Component Status ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1060, "LO", "Requested Procedure Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1064, "SQ", "Requested Procedure Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x1070, "LO", "Requested Contrast Agent", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0032, 0x4000, "LT", "Study Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0033, 0x0001, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0033, 0x0002, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0033, 0x0005, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0033, 0x0006, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0033, 0x0010, "LT", "Patient Study UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0037, 0x0010, "LO", "ReferringDepartment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0037, 0x0020, "US", "ScreenNumber", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0037, 0x0040, "SH", "LeftOrientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0037, 0x0042, "SH", "RightOrientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0037, 0x0050, "CS", "Inversion", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0037, 0x0060, "US", "DSA", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0000, "UL", "Visit Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0004, "SQ", "Referenced Patient Alias Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0008, "CS", "Visit Status ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0010, "LO", "Admission ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0011, "LO", "Issuer of Admission ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0016, "LO", "Route of Admissions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x001a, "DA", "Scheduled Admission Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x001b, "TM", "Scheduled Admission Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x001c, "DA", "Scheduled Discharge Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x001d, "TM", "Scheduled Discharge Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x001e, "LO", "Scheduled Patient Institution Residence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0020, "DA", "Admitting Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0021, "TM", "Admitting Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0030, "DA", "Discharge Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0032, "TM", "Discharge Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0040, "LO", "Discharge Diagnosis Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0044, "SQ", "Discharge Diagnosis Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0050, "LO", "Special Needs", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0300, "LO", "Current Patient Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0400, "LO", "Patient's Institution Residence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x0500, "LO", "Patient State", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0038, 0x4000, "LT", "Visit Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0039, 0x0080, "IS", "Private Entity Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0039, 0x0085, "DA", "Private Entity Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0039, 0x0090, "TM", "Private Entity Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0039, 0x0095, "LO", "Private Entity Launch Command", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0039, 0x00aa, "CS", "Private Entity Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0002, "SQ", "Waveform Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0005, "US", "Waveform Number of Channels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0010, "UL", "Waveform Number of Samples", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x001a, "DS", "Sampling Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0020, "SH", "Group Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0103, "CS", "Waveform Sample Value Representation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0122, "OB", "Waveform Padding Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0200, "SQ", "Channel Definition", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0202, "IS", "Waveform Channel Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0203, "SH", "Channel Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0205, "CS", "Channel Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0208, "SQ", "Channel Source", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0209, "SQ", "Channel Source Modifiers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x020a, "SQ", "Differential Channel Source", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x020b, "SQ", "Differential Channel Source Modifiers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0210, "DS", "Channel Sensitivity", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0211, "SQ", "Channel Sensitivity Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0212, "DS", "Channel Sensitivity Correction Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0213, "DS", "Channel Baseline", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0214, "DS", "Channel Time Skew", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0215, "DS", "Channel Sample Skew", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0216, "OB", "Channel Minimum Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0217, "OB", "Channel Maximum Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0218, "DS", "Channel Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x021a, "US", "Bits Per Sample", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0220, "DS", "Filter Low Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0221, "DS", "Filter High Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0222, "DS", "Notch Filter Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x0223, "DS", "Notch Filter Bandwidth", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x003a, 0x1000, "OB", "Waveform Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0001, "AE", "Scheduled Station AE Title", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0002, "DA", "Scheduled Procedure Step Start Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0003, "TM", "Scheduled Procedure Step Start Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0004, "DA", "Scheduled Procedure Step End Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0005, "TM", "Scheduled Procedure Step End Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0006, "PN", "Scheduled Performing Physician Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0007, "LO", "Scheduled Procedure Step Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0008, "SQ", "Scheduled Action Item Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0009, "SH", "Scheduled Procedure Step ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0010, "SH", "Scheduled Station Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0011, "SH", "Scheduled Procedure Step Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0012, "LO", "Pre-Medication", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0020, "CS", "Scheduled Procedure Step Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0100, "SQ", "Scheduled Procedure Step Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0302, "US", "Entrance Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0303, "US", "Exposed Area", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0306, "DS", "Distance Source to Entrance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0307, "DS", "Distance Source to Support", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0310, "ST", "Comments On Radiation Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0312, "DS", "X-Ray Output", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0314, "DS", "Half Value Layer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0316, "DS", "Organ Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0318, "CS", "Organ Exposed", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0400, "LT", "Comments On Scheduled Procedure Step", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x050a, "LO", "Specimen Accession Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0550, "SQ", "Specimen Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0551, "LO", "Specimen Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0552, "SQ", "Specimen Description Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0553, "ST", "Specimen Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0555, "SQ", "Acquisition Context Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x0556, "ST", "Acquisition Context Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x059a, "SQ", "Specimen Type Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x06fa, "LO", "Slide Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x071a, "SQ", "Image Center Point Coordinates Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x072a, "DS", "X Offset In Slide Coordinate System", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x073a, "DS", "Y Offset In Slide Coordinate System", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x074a, "DS", "Z Offset In Slide Coordinate System", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x08d8, "SQ", "Pixel Spacing Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x08da, "SQ", "Coordinate System Axis Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x08ea, "SQ", "Measurement Units Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x09f8, "SQ", "Vital Stain Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1001, "SH", "Requested Procedure ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1002, "LO", "Reason For Requested Procedure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1003, "SH", "Requested Procedure Priority", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1004, "LO", "Patient Transport Arrangements", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1005, "LO", "Requested Procedure Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1006, "SH", "Placer Order Number of Procedure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1007, "SH", "Filler Order Number of Procedure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1008, "LO", "Confidentiality Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1009, "SH", "Reporting Priority", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1010, "PN", "Names of Intended Recipients of Results", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x1400, "LT", "Requested Procedure Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2001, "LO", "Reason For Imaging Service Request", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2004, "DA", "Issue Date of Imaging Service Request", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2005, "TM", "Issue Time of Imaging Service Request", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2006, "SH", "Placer Order Number of Imaging Service Request", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2007, "SH", "Filler Order Number of Imaging Service Request", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2008, "PN", "Order Entered By", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2009, "SH", "Order Enterer Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2010, "SH", "Order Callback Phone Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x2400, "LT", "Imaging Service Request Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0x3001, "LO", "Confidentiality Constraint On Patient Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa007, "CS", "Findings Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa020, "SQ", "Findings Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa021, "UI", "Findings Group UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa022, "UI", "Referenced Findings Group UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa023, "DA", "Findings Group Recording Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa024, "TM", "Findings Group Recording Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa026, "SQ", "Findings Source Category Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa027, "LO", "Documenting Organization", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa028, "SQ", "Documenting Organization Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa032, "LO", "History Reliability Qualifier Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa043, "SQ", "Concept Name Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa047, "LO", "Measurement Precision Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa057, "CS", "Urgency or Priority Alerts", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa060, "LO", "Sequencing Indicator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa066, "SQ", "Document Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa067, "PN", "Document Author", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa068, "SQ", "Document Author Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa070, "SQ", "Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa073, "LO", "Object String Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa074, "OB", "Object Binary Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa075, "PN", "Documenting Observer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa076, "SQ", "Documenting Observer Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa078, "SQ", "Observation Subject Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa080, "SQ", "Person Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa085, "SQ", "Procedure Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa088, "LO", "Object Directory String Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa089, "OB", "Object Directory Binary Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa090, "CS", "History Reliability Qualifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa0a0, "CS", "Referenced Type of Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa0b0, "US", "Referenced Waveform Channels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa110, "DA", "Date of Document or Verbal Transaction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa112, "TM", "Time of Document Creation or Verbal Transaction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa121, "DA", "Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa122, "TM", "Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa123, "PN", "Person Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa124, "SQ", "Referenced Person Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa125, "CS", "Report Status ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa130, "CS", "Temporal Range Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa132, "UL", "Referenced Sample Offsets", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa136, "US", "Referenced Frame Numbers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa138, "DS", "Referenced Time Offsets", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa13a, "DT", "Referenced Datetime", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa160, "UT", "Text Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa167, "SQ", "Observation Category Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa168, "SQ", "Concept Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa16a, "ST", "Bibliographic Citation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa170, "CS", "Observation Class", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa171, "UI", "Observation UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa172, "UI", "Referenced Observation UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa173, "CS", "Referenced Observation Class", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa174, "CS", "Referenced Object Observation Class", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa180, "US", "Annotation Group Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa192, "DA", "Observation Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa193, "TM", "Observation Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa194, "CS", "Measurement Automation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa195, "SQ", "Concept Name Code Sequence Modifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa224, "ST", "Identification Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa290, "CS", "Coordinates Set Geometric Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa296, "SQ", "Algorithm Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa297, "ST", "Algorithm Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa29a, "SL", "Pixel Coordinates Set", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa300, "SQ", "Measured Value Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa307, "PN", "Current Observer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa30a, "DS", "Numeric Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa313, "SQ", "Referenced Accession Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa33a, "ST", "Report Status Comment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa340, "SQ", "Procedure Context Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa352, "PN", "Verbal Source", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa353, "ST", "Address", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa354, "LO", "Telephone Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa358, "SQ", "Verbal Source Identifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa380, "SQ", "Report Detail Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa402, "UI", "Observation Subject UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa403, "CS", "Observation Subject Class", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa404, "SQ", "Observation Subject Type Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa600, "CS", "Observation Subject Context Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa601, "CS", "Observer Context Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa603, "CS", "Procedure Context Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa730, "SQ", "Observations Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa731, "SQ", "Relationship Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa732, "SQ", "Relationship Type Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa744, "SQ", "Language Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xa992, "ST", "Uniform Resource Locator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xb020, "SQ", "Annotation Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0040, 0xdb73, "SQ", "Relationship Type Code Sequence Modifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0000, "LT", "Papyrus Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0011, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0012, "UL", "Pixel Offset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0013, "SQ", "Image Identifier Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0014, "SQ", "External File Reference Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0015, "US", "Number of Images", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0020, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0021, "UI", "Referenced SOP Class UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0022, "UI", "Referenced SOP Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0030, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0031, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0032, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0034, "DA", "Modified Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0036, "TM", "Modified Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0040, "LT", "Owner Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0041, "UI", "Referenced Image SOP Class UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0042, "UI", "Referenced Image SOP Instance UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0050, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0060, "UL", "Number of Images", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x0062, "UL", "Number of Other", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x00a0, "LT", "External Folder Element DSID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x00a1, "US", "External Folder Element Data Set Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x00a2, "LT", "External Folder Element File Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x00a3, "UL", "External Folder Element Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x00b0, "LT", "Internal Folder Element DSID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x00b1, "US", "Internal Folder Element Data Set Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x00b2, "UL", "Internal Offset To Data Set", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0041, 0x00b3, "UL", "Internal Offset To Image", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0001, "SS", "Bitmap Of Prescan Options", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0002, "SS", "Gradient Offset In X", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0003, "SS", "Gradient Offset In Y", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0004, "SS", "Gradient Offset In Z", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0005, "SS", "Image Is Original Or Unoriginal", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0006, "SS", "Number Of EPI Shots", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0007, "SS", "Views Per Segment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0008, "SS", "Respiratory Rate In BPM", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0009, "SS", "Respiratory Trigger Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x000a, "SS", "Type Of Receiver Used", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x000b, "DS", "Peak Rate Of Change Of Gradient Field", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x000c, "DS", "Limits In Units Of Percent", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x000d, "DS", "PSD Estimated Limit", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x000e, "DS", "PSD Estimated Limit In Tesla Per Second", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x000f, "DS", "SAR Avg Head", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0010, "US", "Window Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0011, "US", "Total Input Views", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0012, "SS", "Xray Chain", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0013, "SS", "Recon Kernel Parameters", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0014, "SS", "Calibration Parameters", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0015, "SS", "Total Output Views", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0016, "SS", "Number Of Overranges", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0017, "DS", "IBH Image Scale Factors", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0018, "DS", "BBH Coefficients", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0019, "SS", "Number Of BBH Chains To Blend", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x001a, "SL", "Starting Channel Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x001b, "SS", "PPScan Parameters", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x001c, "SS", "GE Image Integrity", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x001d, "SS", "Level Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x001e, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x001f, "SL", "Max Overranges In A View", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0020, "DS", "Avg Overranges All Views", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0021, "SS", "Corrected Afterglow Terms", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0025, "SS", "Reference Channels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0026, "US", "No Views Ref Channels Blocked", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0027, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0028, "OB", "Unique Image Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0029, "OB", "Histogram Tables", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x002a, "OB", "User Defined Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x002b, "SS", "Private Scan Options", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x002c, "SS", "Effective Echo Spacing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x002d, "SH", "String Slop Field 1", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x002e, "SH", "String Slop Field 2", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x002f, "SS", "Raw Data Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0030, "SS", "Raw Data Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0031, "DS", "RA Coord Of Target Recon Centre", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0032, "SS", "Raw Data Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0033, "FL", "Neg Scan Spacing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0034, "IS", "Offset Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0035, "UL", "User Usage Tag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0036, "UL", "User Fill Map MSW", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0037, "UL", "User Fill Map LSW", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0038, "FL", "User 25 To User 48", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0039, "IS", "Slop Integer 6 To Slop Integer 9", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0040, "FL", "Trigger On Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0041, "FL", "Degree Of Rotation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0042, "SL", "DAS Trigger Source", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0043, "SL", "DAS Fpa Gain", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0044, "SL", "DAS Output Source", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0045, "SL", "DAS Ad Input", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0046, "SL", "DAS Cal Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0047, "SL", "DAS Cal Frequency", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0048, "SL", "DAS Reg Xm", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x0049, "SL", "DAS Auto Zero", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x004a, "SS", "Starting Channel Of View", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x004b, "SL", "DAS Xm Pattern", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x004c, "SS", "TGGC Trigger Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x004d, "FL", "Start Scan To Xray On Delay", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0043, 0x004e, "FL", "Duration Of Xray On", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0044, 0x0000, "UI", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0004, "CS", "AES", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0006, "DS", "Angulation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0009, "DS", "Real Magnification Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x000b, "CS", "Senograph Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x000c, "DS", "Integration Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x000d, "DS", "ROI Origin X and Y", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0011, "DS", "Receptor Size cm X and Y", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0012, "IS", "Receptor Size Pixels X and Y", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0013, "ST", "Screen", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0014, "DS", "Pixel Pitch Microns", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0015, "IS", "Pixel Depth Bits", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0016, "IS", "Binning Factor X and Y", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x001b, "CS", "Clinical View", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x001d, "DS", "Mean Of Raw Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x001e, "DS", "Mean Of Offset Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x001f, "DS", "Mean Of Corrected Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0020, "DS", "Mean Of Region Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0021, "DS", "Mean Of Log Region Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0022, "DS", "Standard Deviation Of Raw Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0023, "DS", "Standard Deviation Of Corrected Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0024, "DS", "Standard Deviation Of Region Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0025, "DS", "Standard Deviation Of Log Region Gray Levels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0026, "OB", "MAO Buffer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0027, "IS", "Set Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0028, "CS", "WindowingType (LINEAR or GAMMA)", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0029, "DS", "WindowingParameters", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x002a, "IS", "Crosshair Cursor X Coordinates", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x002b, "IS", "Crosshair Cursor Y Coordinates", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x0039, "US", "Vignette Rows", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x003a, "US", "Vignette Columns", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x003b, "US", "Vignette Bits Allocated", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x003c, "US", "Vignette Bits Stored", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x003d, "US", "Vignette High Bit", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x003e, "US", "Vignette Pixel Representation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0045, 0x003f, "OB", "Vignette Pixel Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0001, "SQ", "Reconstruction Parameters Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0050, "UL", "Volume Voxel Count", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0051, "UL", "Volume Segment Count", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0053, "US", "Volume Slice Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0054, "US", "Volume Slice Count", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0055, "SL", "Volume Threshold Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0057, "DS", "Volume Voxel Ratio", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0058, "DS", "Volume Voxel Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0059, "US", "Volume Z Position Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0060, "DS", "Volume Base Line", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0061, "DS", "Volume Center Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0063, "SL", "Volume Skew Base", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0064, "DS", "Volume Registration Transform Rotation Matrix", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0065, "DS", "Volume Registration Transform Translation Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0070, "DS", "KVP List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0071, "IS", "XRay Tube Current List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0072, "IS", "Exposure List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0080, "LO", "Acquisition DLX Identifier", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0085, "SQ", "Acquisition DLX 2D Series Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0089, "DS", "Contrast Agent Volume List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x008a, "US", "Number Of Injections", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x008b, "US", "Frame Count", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0096, "IS", "Used Frames", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0091, "LO", "XA 3D Reconstruction Algorithm Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0092, "CS", "XA 3D Reconstruction Algorithm Version", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0093, "DA", "DLX Calibration Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0094, "TM", "DLX Calibration Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0095, "CS", "DLX Calibration Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0098, "US", "Transform Count", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x0099, "SQ", "Transform Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x009a, "DS", "Transform Rotation Matrix", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x009b, "DS", "Transform Translation Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x009c, "LO", "Transform Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00b1, "US", "Wireframe Count", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00b2, "US", "Location System", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00b0, "SQ", "Wireframe List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00b5, "LO", "Wireframe Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00b6, "LO", "Wireframe Group Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00b7, "LO", "Wireframe Color", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00b8, "SL", "Wireframe Attributes", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00b9, "SL", "Wireframe Point Count", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00ba, "SL", "Wireframe Timestamp", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00bb, "SQ", "Wireframe Point List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00bc, "DS", "Wireframe Points Coordinates", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00c0, "DS", "Volume Upper Left High Corner RAS", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00c1, "DS", "Volume Slice To RAS Rotation Matrix", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00c2, "DS", "Volume Upper Left High Corner TLOC", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00d1, "OB", "Volume Segment List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00d2, "OB", "Volume Gradient List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00d3, "OB", "Volume Density List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00d4, "OB", "Volume Z Position List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0047, 0x00d5, "OB", "Volume Original Index List", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0000, "UL", "Calibration Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0004, "CS", "Calibration Object", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0010, "SQ", "DeviceSequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0014, "DS", "DeviceLength", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0016, "DS", "DeviceDiameter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0017, "CS", "DeviceDiameterUnits", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0018, "DS", "DeviceVolume", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0019, "DS", "InterMarkerDistance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0020, "LO", "DeviceDescription", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0050, 0x0030, "SQ", "CodedInterventionDeviceSequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0051, 0x0010, "xs", "Image Text", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0000, "UL", "Nuclear Acquisition Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0010, "US", "Energy Window Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0011, "US", "Number of Energy Windows", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0012, "SQ", "Energy Window Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0013, "SQ", "Energy Window Range Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0014, "DS", "Energy Window Lower Limit", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0015, "DS", "Energy Window Upper Limit", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0016, "SQ", "Radiopharmaceutical Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0017, "IS", "Residual Syringe Counts", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0018, "SH", "Energy Window Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0020, "US", "Detector Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0021, "US", "Number of Detectors", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0022, "SQ", "Detector Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0030, "US", "Phase Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0031, "US", "Number of Phases", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0032, "SQ", "Phase Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0033, "US", "Number of Frames In Phase", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0036, "IS", "Phase Delay", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0038, "IS", "Pause Between Frames", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0050, "US", "Rotation Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0051, "US", "Number of Rotations", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0052, "SQ", "Rotation Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0053, "US", "Number of Frames In Rotation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0060, "US", "R-R Interval Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0061, "US", "Number of R-R Intervals", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0062, "SQ", "Gated Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0063, "SQ", "Data Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0070, "US", "Time Slot Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0071, "US", "Number of Time Slots", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0072, "SQ", "Time Slot Information Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0073, "DS", "Time Slot Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0080, "US", "Slice Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0081, "US", "Number of Slices", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0090, "US", "Angular View Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0100, "US", "Time Slice Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0101, "US", "Number Of Time Slices", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0200, "DS", "Start Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0202, "CS", "Type of Detector Motion", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0210, "IS", "Trigger Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0211, "US", "Number of Triggers in Phase", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0220, "SQ", "View Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0222, "SQ", "View Modifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0300, "SQ", "Radionuclide Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0302, "SQ", "Radiopharmaceutical Route Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0304, "SQ", "Radiopharmaceutical Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0306, "SQ", "Calibration Data Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0308, "US", "Energy Window Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0400, "SH", "Image ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0410, "SQ", "Patient Orientation Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0412, "SQ", "Patient Orientation Modifier Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x0414, "SQ", "Patient Gantry Relationship Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1000, "CS", "Positron Emission Tomography Series Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1001, "CS", "Positron Emission Tomography Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1002, "CS", "Counts Source", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1004, "CS", "Reprojection Method", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1100, "CS", "Randoms Correction Method", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1101, "LO", "Attenuation Correction Method", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1102, "CS", "Decay Correction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1103, "LO", "Reconstruction Method", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1104, "LO", "Detector Lines of Response Used", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1105, "LO", "Scatter Correction Method", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1200, "DS", "Axial Acceptance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1201, "IS", "Axial Mash", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1202, "IS", "Transverse Mash", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1203, "DS", "Detector Element Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1210, "DS", "Coincidence Window Width", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1220, "CS", "Secondary Counts Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1300, "DS", "Frame Reference Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1310, "IS", "Primary Prompts Counts Accumulated", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1311, "IS", "Secondary Counts Accumulated", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1320, "DS", "Slice Sensitivity Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1321, "DS", "Decay Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1322, "DS", "Dose Calibration Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1323, "DS", "Scatter Fraction Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1324, "DS", "Dead Time Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1330, "US", "Image Index", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1400, "CS", "Counts Included", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0054, 0x1401, "CS", "Dead Time Correction Flag", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0055, 0x0046, "LT", "Current Ward", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0058, 0x0000, "SQ", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0060, 0x3000, "SQ", "Histogram Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0060, 0x3002, "US", "Histogram Number of Bins", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0060, 0x3004, "xs", "Histogram First Bin Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0060, 0x3006, "xs", "Histogram Last Bin Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0060, 0x3008, "US", "Histogram Bin Width", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0060, 0x3010, "LO", "Histogram Explanation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0060, 0x3020, "UL", "Histogram Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0001, "SQ", "Graphic Annotation Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0002, "CS", "Graphic Layer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0003, "CS", "Bounding Box Annotation Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0004, "CS", "Anchor Point Annotation Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0005, "CS", "Graphic Annotation Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0006, "ST", "Unformatted Text Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0008, "SQ", "Text Object Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0009, "SQ", "Graphic Object Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0010, "FL", "Bounding Box TLHC", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0011, "FL", "Bounding Box BRHC", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0014, "FL", "Anchor Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0015, "CS", "Anchor Point Visibility", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0020, "US", "Graphic Dimensions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0021, "US", "Number Of Graphic Points", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0022, "FL", "Graphic Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0023, "CS", "Graphic Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0024, "CS", "Graphic Filled", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0040, "IS", "Image Rotation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0041, "CS", "Image Horizontal Flip", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0050, "US", "Displayed Area TLHC", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0051, "US", "Displayed Area BRHC", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0060, "SQ", "Graphic Layer Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0062, "IS", "Graphic Layer Order", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0066, "US", "Graphic Layer Recommended Display Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0068, "LO", "Graphic Layer Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0080, "CS", "Presentation Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0081, "LO", "Presentation Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0082, "DA", "Presentation Creation Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0083, "TM", "Presentation Creation Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0070, 0x0084, "PN", "Presentation Creator's Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0087, 0x0010, "CS", "Media Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0087, 0x0020, "CS", "Media Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0087, 0x0050, "IS", "Estimated Retrieve Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0088, 0x0000, "UL", "Storage Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0088, 0x0130, "SH", "Storage Media FileSet ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0088, 0x0140, "UI", "Storage Media FileSet UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0088, 0x0200, "SQ", "Icon Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0088, 0x0904, "LO", "Topic Title", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0088, 0x0906, "ST", "Topic Subject", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0088, 0x0910, "LO", "Topic Author", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0088, 0x0912, "LO", "Topic Key Words", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0095, 0x0001, "LT", "Examination Folder ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0095, 0x0004, "UL", "Folder Reported Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0095, 0x0005, "LT", "Folder Reporting Radiologist", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0095, 0x0007, "LT", "SIENET ISA PLA", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0099, 0x0002, "UL", "Data Object Attributes", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x00e1, 0x0001, "US", "Data Dictionary Version", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x00e1, 0x0014, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x00e1, 0x0022, "DS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x00e1, 0x0023, "DS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x00e1, 0x0024, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x00e1, 0x0025, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x00e1, 0x0040, "SH", "Offset From CT MR Images", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0193, 0x0002, "DS", "RIS Key", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0307, 0x0001, "UN", "RIS Worklist IMGEF", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0309, 0x0001, "UN", "RIS Report IMGEF", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0000, "SH", "Implementation Version", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0020, "DS", "Relative Table Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0021, "DS", "Relative Table Height", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0030, "SH", "Surview Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0031, "DS", "Surview Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0050, "SH", "Image View Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0070, "DS", "Batch Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0071, "DS", "Batch Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x0601, 0x0072, "DS", "Batch Slice Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x1000, 0x0000, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x1000, 0x0001, "US", "Run Length Triplet", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x1000, 0x0002, "US", "Huffman Table Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x1000, 0x0003, "US", "Huffman Table Triplet", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x1000, 0x0004, "US", "Shift Table Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x1000, 0x0005, "US", "Shift Table Triplet", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x1010, 0x0000, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x1369, 0x0000, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2000, 0x0000, "UL", "Film Session Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2000, 0x0010, "IS", "Number of Copies", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2000, 0x0020, "CS", "Print Priority", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2000, 0x0030, "CS", "Medium Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2000, 0x0040, "CS", "Film Destination", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2000, 0x0050, "LO", "Film Session Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2000, 0x0060, "IS", "Memory Allocation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2000, 0x0500, "SQ", "Referenced Film Box Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0000, "UL", "Film Box Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0010, "ST", "Image Display Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0030, "CS", "Annotation Display Format ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0040, "CS", "Film Orientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0050, "CS", "Film Size ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0060, "CS", "Magnification Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0080, "CS", "Smoothing Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0100, "CS", "Border Density", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0110, "CS", "Empty Image Density", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0120, "US", "Min Density", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0130, "US", "Max Density", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0140, "CS", "Trim", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0150, "ST", "Configuration Information", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0500, "SQ", "Referenced Film Session Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0510, "SQ", "Referenced Image Box Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2010, 0x0520, "SQ", "Referenced Basic Annotation Box Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2020, 0x0000, "UL", "Image Box Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2020, 0x0010, "US", "Image Box Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2020, 0x0020, "CS", "Polarity", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2020, 0x0030, "DS", "Requested Image Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2020, 0x0110, "SQ", "Preformatted Grayscale Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2020, 0x0111, "SQ", "Preformatted Color Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2020, 0x0130, "SQ", "Referenced Image Overlay Box Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2020, 0x0140, "SQ", "Referenced VOI LUT Box Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2030, 0x0000, "UL", "Annotation Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2030, 0x0010, "US", "Annotation Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2030, 0x0020, "LO", "Text String", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0000, "UL", "Overlay Box Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0010, "SQ", "Referenced Overlay Plane Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0011, "US", "Referenced Overlay Plane Groups", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0060, "CS", "Overlay Magnification Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0070, "CS", "Overlay Smoothing Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0080, "CS", "Overlay Foreground Density", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0090, "CS", "Overlay Mode", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0100, "CS", "Threshold Density", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2040, 0x0500, "SQ", "Referenced Overlay Image Box Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2050, 0x0010, "SQ", "Presentation LUT Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2050, 0x0020, "CS", "Presentation LUT Shape", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2100, 0x0000, "UL", "Print Job Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2100, 0x0020, "CS", "Execution Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2100, 0x0030, "CS", "Execution Status Info", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2100, 0x0040, "DA", "Creation Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2100, 0x0050, "TM", "Creation Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2100, 0x0070, "AE", "Originator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2100, 0x0500, "SQ", "Referenced Print Job Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2110, 0x0000, "UL", "Printer Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2110, 0x0010, "CS", "Printer Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2110, 0x0020, "CS", "Printer Status Info", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2110, 0x0030, "LO", "Printer Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x2110, 0x0099, "SH", "Print Queue ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0002, "SH", "RT Image Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0003, "LO", "RT Image Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0004, "ST", "RT Image Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x000a, "CS", "Reported Values Origin", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x000c, "CS", "RT Image Plane", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x000e, "DS", "X-Ray Image Receptor Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0010, "DS", "RTImageOrientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0011, "DS", "Image Plane Pixel Spacing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0012, "DS", "RT Image Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0020, "SH", "Radiation Machine Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0022, "DS", "Radiation Machine SAD", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0024, "DS", "Radiation Machine SSD", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0026, "DS", "RT Image SID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0028, "DS", "Source to Reference Object Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0029, "IS", "Fraction Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0030, "SQ", "Exposure Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3002, 0x0032, "DS", "Meterset Exposure", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0001, "CS", "DVH Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0002, "CS", "Dose Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0004, "CS", "Dose Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0006, "LO", "Dose Comment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0008, "DS", "Normalization Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x000a, "CS", "Dose Summation Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x000c, "DS", "GridFrame Offset Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x000e, "DS", "Dose Grid Scaling", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0010, "SQ", "RT Dose ROI Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0012, "DS", "Dose Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0040, "DS", "DVH Normalization Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0042, "DS", "DVH Normalization Dose Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0050, "SQ", "DVH Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0052, "DS", "DVH Dose Scaling", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0054, "CS", "DVH Volume Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0056, "IS", "DVH Number of Bins", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0058, "DS", "DVH Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0060, "SQ", "DVH Referenced ROI Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0062, "CS", "DVH ROI Contribution Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0070, "DS", "DVH Minimum Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0072, "DS", "DVH Maximum Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3004, 0x0074, "DS", "DVH Mean Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0002, "SH", "Structure Set Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0004, "LO", "Structure Set Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0006, "ST", "Structure Set Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0008, "DA", "Structure Set Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0009, "TM", "Structure Set Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0010, "SQ", "Referenced Frame of Reference Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0012, "SQ", "RT Referenced Study Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0014, "SQ", "RT Referenced Series Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0016, "SQ", "Contour Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0020, "SQ", "Structure Set ROI Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0022, "IS", "ROI Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0024, "UI", "Referenced Frame of Reference UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0026, "LO", "ROI Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0028, "ST", "ROI Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x002a, "IS", "ROI Display Color", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x002c, "DS", "ROI Volume", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0030, "SQ", "RT Related ROI Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0033, "CS", "RT ROI Relationship", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0036, "CS", "ROI Generation Algorithm", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0038, "LO", "ROI Generation Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0039, "SQ", "ROI Contour Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0040, "SQ", "Contour Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0042, "CS", "Contour Geometric Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0044, "DS", "Contour SlabT hickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0045, "DS", "Contour Offset Vector", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0046, "IS", "Number of Contour Points", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0050, "DS", "Contour Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0080, "SQ", "RT ROI Observations Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0082, "IS", "Observation Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0084, "IS", "Referenced ROI Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0085, "SH", "ROI Observation Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0086, "SQ", "RT ROI Identification Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x0088, "ST", "ROI Observation Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00a0, "SQ", "Related RT ROI Observations Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00a4, "CS", "RT ROI Interpreted Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00a6, "PN", "ROI Interpreter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00b0, "SQ", "ROI Physical Properties Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00b2, "CS", "ROI Physical Property", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00b4, "DS", "ROI Physical Property Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00c0, "SQ", "Frame of Reference Relationship Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00c2, "UI", "Related Frame of Reference UID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00c4, "CS", "Frame of Reference Transformation Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00c6, "DS", "Frame of Reference Transformation Matrix", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x3006, 0x00c8, "LO", "Frame of Reference Transformation Comment", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0002, "SH", "RT Plan Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0003, "LO", "RT Plan Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0004, "ST", "RT Plan Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0006, "DA", "RT Plan Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0007, "TM", "RT Plan Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0009, "LO", "Treatment Protocols", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x000a, "CS", "Treatment Intent", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x000b, "LO", "Treatment Sites", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x000c, "CS", "RT Plan Geometry", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x000e, "ST", "Prescription Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0010, "SQ", "Dose ReferenceSequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0012, "IS", "Dose ReferenceNumber", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0014, "CS", "Dose Reference Structure Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0016, "LO", "Dose ReferenceDescription", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0018, "DS", "Dose Reference Point Coordinates", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x001a, "DS", "Nominal Prior Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0020, "CS", "Dose Reference Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0021, "DS", "Constraint Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0022, "DS", "Delivery Warning Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0023, "DS", "Delivery Maximum Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0025, "DS", "Target Minimum Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0026, "DS", "Target Prescription Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0027, "DS", "Target Maximum Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0028, "DS", "Target Underdose Volume Fraction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x002a, "DS", "Organ at Risk Full-volume Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x002b, "DS", "Organ at Risk Limit Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x002c, "DS", "Organ at Risk Maximum Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x002d, "DS", "Organ at Risk Overdose Volume Fraction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0040, "SQ", "Tolerance Table Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0042, "IS", "Tolerance Table Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0043, "SH", "Tolerance Table Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0044, "DS", "Gantry Angle Tolerance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0046, "DS", "Beam Limiting Device Angle Tolerance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0048, "SQ", "Beam Limiting Device Tolerance Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x004a, "DS", "Beam Limiting Device Position Tolerance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x004c, "DS", "Patient Support Angle Tolerance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x004e, "DS", "Table Top Eccentric Angle Tolerance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0051, "DS", "Table Top Vertical Position Tolerance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0052, "DS", "Table Top Longitudinal Position Tolerance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0053, "DS", "Table Top Lateral Position Tolerance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0055, "CS", "RT Plan Relationship", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0070, "SQ", "Fraction Group Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0071, "IS", "Fraction Group Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0078, "IS", "Number of Fractions Planned", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0079, "IS", "Number of Fractions Per Day", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x007a, "IS", "Repeat Fraction Cycle Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x007b, "LT", "Fraction Pattern", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0080, "IS", "Number of Beams", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0082, "DS", "Beam Dose Specification Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0084, "DS", "Beam Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0086, "DS", "Beam Meterset", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00a0, "IS", "Number of Brachy Application Setups", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00a2, "DS", "Brachy Application Setup Dose Specification Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00a4, "DS", "Brachy Application Setup Dose", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00b0, "SQ", "Beam Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00b2, "SH", "Treatment Machine Name ", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00b3, "CS", "Primary Dosimeter Unit", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00b4, "DS", "Source-Axis Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00b6, "SQ", "Beam Limiting Device Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00b8, "CS", "RT Beam Limiting Device Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00ba, "DS", "Source to Beam Limiting Device Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00bc, "IS", "Number of Leaf/Jaw Pairs", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00be, "DS", "Leaf Position Boundaries", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00c0, "IS", "Beam Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00c2, "LO", "Beam Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00c3, "ST", "Beam Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00c4, "CS", "Beam Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00c6, "CS", "Radiation Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00c8, "IS", "Reference Image Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00ca, "SQ", "Planned Verification Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00cc, "LO", "Imaging Device Specific Acquisition Parameters", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00ce, "CS", "Treatment Delivery Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00d0, "IS", "Number of Wedges", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00d1, "SQ", "Wedge Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00d2, "IS", "Wedge Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00d3, "CS", "Wedge Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00d4, "SH", "Wedge ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00d5, "IS", "Wedge Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00d6, "DS", "Wedge Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00d8, "DS", "Wedge Orientation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00da, "DS", "Source to Wedge Tray Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e0, "IS", "Number of Compensators", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e1, "SH", "Material ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e2, "DS", "Total Compensator Tray Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e3, "SQ", "Compensator Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e4, "IS", "Compensator Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e5, "SH", "Compensator ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e6, "DS", "Source to Compensator Tray Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e7, "IS", "Compensator Rows", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e8, "IS", "Compensator Columns", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00e9, "DS", "Compensator Pixel Spacing", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00ea, "DS", "Compensator Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00eb, "DS", "Compensator Transmission Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00ec, "DS", "Compensator Thickness Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00ed, "IS", "Number of Boli", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00f0, "IS", "Number of Blocks", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00f2, "DS", "Total Block Tray Factor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00f4, "SQ", "Block Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00f5, "SH", "Block Tray ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00f6, "DS", "Source to Block Tray Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00f8, "CS", "Block Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00fa, "CS", "Block Divergence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00fc, "IS", "Block Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x00fe, "LO", "Block Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0100, "DS", "Block Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0102, "DS", "Block Transmission", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0104, "IS", "Block Number of Points", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0106, "DS", "Block Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0107, "SQ", "Applicator Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0108, "SH", "Applicator ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0109, "CS", "Applicator Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x010a, "LO", "Applicator Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x010c, "DS", "Cumulative Dose Reference Coefficient", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x010e, "DS", "Final Cumulative Meterset Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0110, "IS", "Number of Control Points", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0111, "SQ", "Control Point Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0112, "IS", "Control Point Index", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0114, "DS", "Nominal Beam Energy", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0115, "DS", "Dose Rate Set", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0116, "SQ", "Wedge Position Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0118, "CS", "Wedge Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x011a, "SQ", "Beam Limiting Device Position Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x011c, "DS", "Leaf Jaw Positions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x011e, "DS", "Gantry Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x011f, "CS", "Gantry Rotation Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0120, "DS", "Beam Limiting Device Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0121, "CS", "Beam Limiting Device Rotation Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0122, "DS", "Patient Support Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0123, "CS", "Patient Support Rotation Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0124, "DS", "Table Top Eccentric Axis Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0125, "DS", "Table Top Eccentric Angle", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0126, "CS", "Table Top Eccentric Rotation Direction", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0128, "DS", "Table Top Vertical Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0129, "DS", "Table Top Longitudinal Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x012a, "DS", "Table Top Lateral Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x012c, "DS", "Isocenter Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x012e, "DS", "Surface Entry Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0130, "DS", "Source to Surface Distance", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0134, "DS", "Cumulative Meterset Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0180, "SQ", "Patient Setup Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0182, "IS", "Patient Setup Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0184, "LO", "Patient Additional Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0190, "SQ", "Fixation Device Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0192, "CS", "Fixation Device Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0194, "SH", "Fixation Device Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0196, "ST", "Fixation Device Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0198, "SH", "Fixation Device Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01a0, "SQ", "Shielding Device Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01a2, "CS", "Shielding Device Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01a4, "SH", "Shielding Device Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01a6, "ST", "Shielding Device Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01a8, "SH", "Shielding Device Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01b0, "CS", "Setup Technique", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01b2, "ST", "Setup TechniqueDescription", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01b4, "SQ", "Setup Device Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01b6, "CS", "Setup Device Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01b8, "SH", "Setup Device Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01ba, "ST", "Setup Device Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01bc, "DS", "Setup Device Parameter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01d0, "ST", "Setup ReferenceDescription", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01d2, "DS", "Table Top Vertical Setup Displacement", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01d4, "DS", "Table Top Longitudinal Setup Displacement", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x01d6, "DS", "Table Top Lateral Setup Displacement", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0200, "CS", "Brachy Treatment Technique", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0202, "CS", "Brachy Treatment Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0206, "SQ", "Treatment Machine Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0210, "SQ", "Source Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0212, "IS", "Source Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0214, "CS", "Source Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0216, "LO", "Source Manufacturer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0218, "DS", "Active Source Diameter", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x021a, "DS", "Active Source Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0222, "DS", "Source Encapsulation Nominal Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0224, "DS", "Source Encapsulation Nominal Transmission", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0226, "LO", "Source IsotopeName", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0228, "DS", "Source Isotope Half Life", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x022a, "DS", "Reference Air Kerma Rate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x022c, "DA", "Air Kerma Rate Reference Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x022e, "TM", "Air Kerma Rate Reference Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0230, "SQ", "Application Setup Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0232, "CS", "Application Setup Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0234, "IS", "Application Setup Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0236, "LO", "Application Setup Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0238, "LO", "Application Setup Manufacturer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0240, "IS", "Template Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0242, "SH", "Template Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0244, "LO", "Template Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0250, "DS", "Total Reference Air Kerma", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0260, "SQ", "Brachy Accessory Device Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0262, "IS", "Brachy Accessory Device Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0263, "SH", "Brachy Accessory Device ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0264, "CS", "Brachy Accessory Device Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0266, "LO", "Brachy Accessory Device Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x026a, "DS", "Brachy Accessory Device Nominal Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x026c, "DS", "Brachy Accessory Device Nominal Transmission", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0280, "SQ", "Channel Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0282, "IS", "Channel Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0284, "DS", "Channel Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0286, "DS", "Channel Total Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0288, "CS", "Source Movement Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x028a, "IS", "Number of Pulses", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x028c, "DS", "Pulse Repetition Interval", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0290, "IS", "Source Applicator Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0291, "SH", "Source Applicator ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0292, "CS", "Source Applicator Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0294, "LO", "Source Applicator Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0296, "DS", "Source Applicator Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x0298, "LO", "Source Applicator Manufacturer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x029c, "DS", "Source Applicator Wall Nominal Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x029e, "DS", "Source Applicator Wall Nominal Transmission", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02a0, "DS", "Source Applicator Step Size", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02a2, "IS", "Transfer Tube Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02a4, "DS", "Transfer Tube Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02b0, "SQ", "Channel Shield Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02b2, "IS", "Channel Shield Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02b3, "SH", "Channel Shield ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02b4, "LO", "Channel Shield Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02b8, "DS", "Channel Shield Nominal Thickness", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02ba, "DS", "Channel Shield Nominal Transmission", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02c8, "DS", "Final Cumulative Time Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02d0, "SQ", "Brachy Control Point Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02d2, "DS", "Control Point Relative Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02d4, "DS", "Control Point 3D Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300a, 0x02d6, "DS", "Cumulative Time Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0002, "SQ", "Referenced RT Plan Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0004, "SQ", "Referenced Beam Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0006, "IS", "Referenced Beam Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0007, "IS", "Referenced Reference Image Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0008, "DS", "Start Cumulative Meterset Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0009, "DS", "End Cumulative Meterset Weight", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x000a, "SQ", "Referenced Brachy Application Setup Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x000c, "IS", "Referenced Brachy Application Setup Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x000e, "IS", "Referenced Source Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0020, "SQ", "Referenced Fraction Group Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0022, "IS", "Referenced Fraction Group Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0040, "SQ", "Referenced Verification Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0042, "SQ", "Referenced Reference Image Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0050, "SQ", "Referenced Dose Reference Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0051, "IS", "Referenced Dose Reference Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0055, "SQ", "Brachy Referenced Dose Reference Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0060, "SQ", "Referenced Structure Set Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x006a, "IS", "Referenced Patient Setup Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x0080, "SQ", "Referenced Dose Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x00a0, "IS", "Referenced Tolerance Table Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x00b0, "SQ", "Referenced Bolus Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x00c0, "IS", "Referenced Wedge Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x00d0, "IS", "Referenced Compensato rNumber", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x00e0, "IS", "Referenced Block Number", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300c, 0x00f0, "IS", "Referenced Control Point", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300e, 0x0002, "CS", "Approval Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300e, 0x0004, "DA", "Review Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300e, 0x0005, "TM", "Review Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x300e, 0x0008, "PN", "Reviewer Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4000, 0x0000, "UL", "Text Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4000, 0x0010, "LT", "Text Arbitrary", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4000, 0x4000, "LT", "Text Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0000, "UL", "Results Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0040, "SH", "Results ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0042, "LO", "Results ID Issuer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0050, "SQ", "Referenced Interpretation Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x00ff, "CS", "Report Production Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0100, "DA", "Interpretation Recorded Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0101, "TM", "Interpretation Recorded Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0102, "PN", "Interpretation Recorder", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0103, "LO", "Reference to Recorded Sound", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0108, "DA", "Interpretation Transcription Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0109, "TM", "Interpretation Transcription Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x010a, "PN", "Interpretation Transcriber", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x010b, "ST", "Interpretation Text", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x010c, "PN", "Interpretation Author", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0111, "SQ", "Interpretation Approver Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0112, "DA", "Interpretation Approval Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0113, "TM", "Interpretation Approval Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0114, "PN", "Physician Approving Interpretation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0115, "LT", "Interpretation Diagnosis Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0117, "SQ", "InterpretationDiagnosis Code Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0118, "SQ", "Results Distribution List Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0119, "PN", "Distribution Name", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x011a, "LO", "Distribution Address", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0200, "SH", "Interpretation ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0202, "LO", "Interpretation ID Issuer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0210, "CS", "Interpretation Type ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0212, "CS", "Interpretation Status ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x0300, "ST", "Impressions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4008, 0x4000, "ST", "Results Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4009, 0x0001, "LT", "Report ID", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4009, 0x0020, "LT", "Report Status", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4009, 0x0030, "DA", "Report Creation Date", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4009, 0x0070, "LT", "Report Approving Physician", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4009, 0x00e0, "LT", "Report Text", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4009, 0x00e1, "LT", "Report Author", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x4009, 0x00e3, "LT", "Reporting Radiologist", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0000, "UL", "Curve Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0005, "US", "Curve Dimensions", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0010, "US", "Number of Points", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0020, "CS", "Type of Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0022, "LO", "Curve Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0030, "SH", "Axis Units", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0040, "SH", "Axis Labels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0103, "US", "Data Value Representation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0104, "US", "Minimum Coordinate Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0105, "US", "Maximum Coordinate Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0106, "SH", "Curve Range", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0110, "US", "Curve Data Descriptor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0112, "US", "Coordinate Start Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x0114, "US", "Coordinate Step Value", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x1001, "CS", "Curve Activation Layer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x2000, "US", "Audio Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x2002, "US", "Audio Sample Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x2004, "US", "Number of Channels", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x2006, "UL", "Number of Samples", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x2008, "UL", "Sample Rate", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x200a, "UL", "Total Time", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x200c, "xs", "Audio Sample Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x200e, "LT", "Audio Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x2500, "LO", "Curve Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x2600, "SQ", "CurveReferenced Overlay Sequence", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x2610, "US", "CurveReferenced Overlay Group", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x5000, 0x3000, "OW", "Curve Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0000, "UL", "Overlay Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0001, "US", "Gray Palette Color Lookup Table Descriptor", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0002, "US", "Gray Palette Color Lookup Table Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0010, "US", "Overlay Rows", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0011, "US", "Overlay Columns", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0012, "US", "Overlay Planes", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0015, "IS", "Number of Frames in Overlay", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0022, "LO", "Overlay Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0040, "CS", "Overlay Type", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0045, "CS", "Overlay Subtype", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0050, "SS", "Overlay Origin", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0051, "US", "Image Frame Origin", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0052, "US", "Plane Origin", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0060, "LO", "Overlay Compression Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0061, "SH", "Overlay Compression Originator", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0062, "SH", "Overlay Compression Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0063, "SH", "Overlay Compression Description", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0066, "AT", "Overlay Compression Step Pointers", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0068, "US", "Overlay Repeat Interval", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0069, "US", "Overlay Bits Grouped", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0100, "US", "Overlay Bits Allocated", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0102, "US", "Overlay Bit Position", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0110, "LO", "Overlay Format", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0200, "xs", "Overlay Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0800, "LO", "Overlay Code Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0802, "US", "Overlay Number of Tables", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0803, "AT", "Overlay Code Table Location", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x0804, "US", "Overlay Bits For Code Word", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1001, "CS", "Overlay Activation Layer", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1100, "US", "Overlay Descriptor - Gray", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1101, "US", "Overlay Descriptor - Red", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1102, "US", "Overlay Descriptor - Green", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1103, "US", "Overlay Descriptor - Blue", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1200, "US", "Overlays - Gray", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1201, "US", "Overlays - Red", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1202, "US", "Overlays - Green", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1203, "US", "Overlays - Blue", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1301, "IS", "ROI Area", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1302, "DS", "ROI Mean", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1303, "DS", "ROI Standard Deviation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x1500, "LO", "Overlay Label", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x3000, "OW", "Overlay Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6000, 0x4000, "LT", "Overlay Comments", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6001, 0x0000, "UN", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6001, 0x0010, "LO", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6001, 0x1010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6001, 0x1030, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6021, 0x0000, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x6021, 0x0010, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7001, 0x0010, "LT", "Dummy", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7003, 0x0010, "LT", "Info", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7005, 0x0010, "LT", "Dummy", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7000, 0x0004, "ST", "TextAnnotation", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7000, 0x0005, "IS", "Box", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7000, 0x0007, "IS", "ArrowEnd", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe0, 0x0000, "UL", "Pixel Data Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe0, 0x0010, "xs", "Pixel Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe0, 0x0020, "OW", "Coefficients SDVN", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe0, 0x0030, "OW", "Coefficients SDHN", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe0, 0x0040, "OW", "Coefficients SDDN", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe1, 0x0010, "xs", "Pixel Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7f00, 0x0000, "UL", "Variable Pixel Data Group Length", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7f00, 0x0010, "xs", "Variable Pixel Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7f00, 0x0011, "US", "Variable Next Data Group", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7f00, 0x0020, "OW", "Variable Coefficients SDVN", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7f00, 0x0030, "OW", "Variable Coefficients SDHN", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7f00, 0x0040, "OW", "Variable Coefficients SDDN", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe1, 0x0000, "OB", "Binary Data", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe3, 0x0000, "LT", "Image Graphics Format Code", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe3, 0x0010, "OB", "Image Graphics", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7fe3, 0x0020, "OB", "Image Graphics Dummy", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0001, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0002, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0003, "xs", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0004, "IS", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0005, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0007, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0008, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0009, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x000a, "LT", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x000b, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x000c, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x000d, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0x7ff1, 0x0010, "US", "?", (DicomElemParseFunc *) NULL ),
    ENTRY( 0xfffc, 0xfffc, "OB", "Data Set Trailing Padding", (DicomElemParseFunc *) NULL ),
    ENTRY( 0xfffe, 0xe000, "!!", "Item", (DicomElemParseFunc *) NULL ),
    ENTRY( 0xfffe, 0xe00d, "!!", "Item Delimitation Item", (DicomElemParseFunc *) NULL ),
    ENTRY( 0xfffe, 0xe0dd, "!!", "Sequence Delimitation Item", (DicomElemParseFunc *) NULL ),
    ENTRY( 0xffff, 0xffff, "xs", "", (DicomElemParseFunc *) NULL )
  };

#if DESCRIPION_STR
static const char dicom_descriptions[] =
    "Group Length\0" /* 0, 0x0000, 0x0000 */
    "Command Length to End\0" /* 1, 0x0000, 0x0001 */
    "Affected SOP Class UID\0" /* 2, 0x0000, 0x0002 */
    "Requested SOP Class UID\0" /* 3, 0x0000, 0x0003 */
    "Command Recognition Code\0" /* 4, 0x0000, 0x0010 */
    "Command Field\0" /* 5, 0x0000, 0x0100 */
    "Message ID\0" /* 6, 0x0000, 0x0110 */
    "Message ID Being Responded To\0" /* 7, 0x0000, 0x0120 */
    "Initiator\0" /* 8, 0x0000, 0x0200 */
    "Receiver\0" /* 9, 0x0000, 0x0300 */
    "Find Location\0" /* 10, 0x0000, 0x0400 */
    "Move Destination\0" /* 11, 0x0000, 0x0600 */
    "Priority\0" /* 12, 0x0000, 0x0700 */
    "Data Set Type\0" /* 13, 0x0000, 0x0800 */
    "Number of Matches\0" /* 14, 0x0000, 0x0850 */
    "Response Sequence Number\0" /* 15, 0x0000, 0x0860 */
    "Status\0" /* 16, 0x0000, 0x0900 */
    "Offending Element\0" /* 17, 0x0000, 0x0901 */
    "Exception Comment\0" /* 18, 0x0000, 0x0902 */
    "Exception ID\0" /* 19, 0x0000, 0x0903 */
    "Affected SOP Instance UID\0" /* 20, 0x0000, 0x1000 */
    "Requested SOP Instance UID\0" /* 21, 0x0000, 0x1001 */
    "Event Type ID\0" /* 22, 0x0000, 0x1002 */
    "Attribute Identifier List\0" /* 23, 0x0000, 0x1005 */
    "Action Type ID\0" /* 24, 0x0000, 0x1008 */
    "Number of Remaining Suboperations\0" /* 25, 0x0000, 0x1020 */
    "Number of Completed Suboperations\0" /* 26, 0x0000, 0x1021 */
    "Number of Failed Suboperations\0" /* 27, 0x0000, 0x1022 */
    "Number of Warning Suboperations\0" /* 28, 0x0000, 0x1023 */
    "Move Originator Application Entity Title\0" /* 29, 0x0000, 0x1030 */
    "Move Originator Message ID\0" /* 30, 0x0000, 0x1031 */
    "Dialog Receiver\0" /* 31, 0x0000, 0x4000 */
    "Terminal Type\0" /* 32, 0x0000, 0x4010 */
    "Message Set ID\0" /* 33, 0x0000, 0x5010 */
    "End Message Set\0" /* 34, 0x0000, 0x5020 */
    "Display Format\0" /* 35, 0x0000, 0x5110 */
    "Page Position ID\0" /* 36, 0x0000, 0x5120 */
    "Text Format ID\0" /* 37, 0x0000, 0x5130 */
    "Normal Reverse\0" /* 38, 0x0000, 0x5140 */
    "Add Gray Scale\0" /* 39, 0x0000, 0x5150 */
    "Borders\0" /* 40, 0x0000, 0x5160 */
    "Copies\0" /* 41, 0x0000, 0x5170 */
    "OldMagnificationType\0" /* 42, 0x0000, 0x5180 */
    "Erase\0" /* 43, 0x0000, 0x5190 */
    "Print\0" /* 44, 0x0000, 0x51a0 */
    "Overlays\0" /* 45, 0x0000, 0x51b0 */
    "Meta Element Group Length\0" /* 46, 0x0002, 0x0000 */
    "File Meta Information Version\0" /* 47, 0x0002, 0x0001 */
    "Media Storage SOP Class UID\0" /* 48, 0x0002, 0x0002 */
    "Media Storage SOP Instance UID\0" /* 49, 0x0002, 0x0003 */
    "Transfer Syntax UID\0" /* 50, 0x0002, 0x0010 */
    "Implementation Class UID\0" /* 51, 0x0002, 0x0012 */
    "Implementation Version Name\0" /* 52, 0x0002, 0x0013 */
    "Source Application Entity Title\0" /* 53, 0x0002, 0x0016 */
    "Private Information Creator UID\0" /* 54, 0x0002, 0x0100 */
    "Private Information\0" /* 55, 0x0002, 0x0102 */
    "?\0" /* 56, 0x0003, 0x0000 */
    "ISI Command Field\0" /* 57, 0x0003, 0x0008 */
    "Attach ID Application Code\0" /* 58, 0x0003, 0x0011 */
    "Attach ID Message Count\0" /* 59, 0x0003, 0x0012 */
    "Attach ID Date\0" /* 60, 0x0003, 0x0013 */
    "Attach ID Time\0" /* 61, 0x0003, 0x0014 */
    "Message Type\0" /* 62, 0x0003, 0x0020 */
    "Max Waiting Date\0" /* 63, 0x0003, 0x0030 */
    "Max Waiting Time\0" /* 64, 0x0003, 0x0031 */
    "File Set Group Length\0" /* 65, 0x0004, 0x0000 */
    "File Set ID\0" /* 66, 0x0004, 0x1130 */
    "File Set Descriptor File ID\0" /* 67, 0x0004, 0x1141 */
    "File Set Descriptor File Specific Character Set\0" /* 68, 0x0004, 0x1142 */
    "Root Directory Entity First Directory Record Offset\0" /* 69, 0x0004, 0x1200 */
    "Root Directory Entity Last Directory Record Offset\0" /* 70, 0x0004, 0x1202 */
    "File Set Consistency Flag\0" /* 71, 0x0004, 0x1212 */
    "Directory Record Sequence\0" /* 72, 0x0004, 0x1220 */
    "Next Directory Record Offset\0" /* 73, 0x0004, 0x1400 */
    "Record In Use Flag\0" /* 74, 0x0004, 0x1410 */
    "Referenced Lower Level Directory Entity Offset\0" /* 75, 0x0004, 0x1420 */
    "Directory Record Type\0" /* 76, 0x0004, 0x1430 */
    "Private Record UID\0" /* 77, 0x0004, 0x1432 */
    "Referenced File ID\0" /* 78, 0x0004, 0x1500 */
    "MRDR Directory Record Offset\0" /* 79, 0x0004, 0x1504 */
    "Referenced SOP Class UID In File\0" /* 80, 0x0004, 0x1510 */
    "Referenced SOP Instance UID In File\0" /* 81, 0x0004, 0x1511 */
    "Referenced Transfer Syntax UID In File\0" /* 82, 0x0004, 0x1512 */
    "Number of References\0" /* 83, 0x0004, 0x1600 */
    "?\0" /* 84, 0x0005, 0x0000 */
    "?\0" /* 85, 0x0006, 0x0000 */
    "Identifying Group Length\0" /* 86, 0x0008, 0x0000 */
    "Length to End\0" /* 87, 0x0008, 0x0001 */
    "Specific Character Set\0" /* 88, 0x0008, 0x0005 */
    "Image Type\0" /* 89, 0x0008, 0x0008 */
    "Recognition Code\0" /* 90, 0x0008, 0x0010 */
    "Instance Creation Date\0" /* 91, 0x0008, 0x0012 */
    "Instance Creation Time\0" /* 92, 0x0008, 0x0013 */
    "Instance Creator UID\0" /* 93, 0x0008, 0x0014 */
    "SOP Class UID\0" /* 94, 0x0008, 0x0016 */
    "SOP Instance UID\0" /* 95, 0x0008, 0x0018 */
    "Study Date\0" /* 96, 0x0008, 0x0020 */
    "Series Date\0" /* 97, 0x0008, 0x0021 */
    "Acquisition Date\0" /* 98, 0x0008, 0x0022 */
    "Image Date\0" /* 99, 0x0008, 0x0023 */
    "Overlay Date\0" /* 100, 0x0008, 0x0024 */
    "Curve Date\0" /* 101, 0x0008, 0x0025 */
    "Study Time\0" /* 102, 0x0008, 0x0030 */
    "Series Time\0" /* 103, 0x0008, 0x0031 */
    "Acquisition Time\0" /* 104, 0x0008, 0x0032 */
    "Image Time\0" /* 105, 0x0008, 0x0033 */
    "Overlay Time\0" /* 106, 0x0008, 0x0034 */
    "Curve Time\0" /* 107, 0x0008, 0x0035 */
    "Old Data Set Type\0" /* 108, 0x0008, 0x0040 */
    "Old Data Set Subtype\0" /* 109, 0x0008, 0x0041 */
    "Nuclear Medicine Series Type\0" /* 110, 0x0008, 0x0042 */
    "Accession Number\0" /* 111, 0x0008, 0x0050 */
    "Query/Retrieve Level\0" /* 112, 0x0008, 0x0052 */
    "Retrieve AE Title\0" /* 113, 0x0008, 0x0054 */
    "Failed SOP Instance UID List\0" /* 114, 0x0008, 0x0058 */
    "Modality\0" /* 115, 0x0008, 0x0060 */
    "Modality Subtype\0" /* 116, 0x0008, 0x0062 */
    "Conversion Type\0" /* 117, 0x0008, 0x0064 */
    "Presentation Intent Type\0" /* 118, 0x0008, 0x0068 */
    "Manufacturer\0" /* 119, 0x0008, 0x0070 */
    "Institution Name\0" /* 120, 0x0008, 0x0080 */
    "Institution Address\0" /* 121, 0x0008, 0x0081 */
    "Institution Code Sequence\0" /* 122, 0x0008, 0x0082 */
    "Referring Physician's Name\0" /* 123, 0x0008, 0x0090 */
    "Referring Physician's Address\0" /* 124, 0x0008, 0x0092 */
    "Referring Physician's Telephone Numbers\0" /* 125, 0x0008, 0x0094 */
    "Code Value\0" /* 126, 0x0008, 0x0100 */
    "Coding Scheme Designator\0" /* 127, 0x0008, 0x0102 */
    "Coding Scheme Version\0" /* 128, 0x0008, 0x0103 */
    "Code Meaning\0" /* 129, 0x0008, 0x0104 */
    "Mapping Resource\0" /* 130, 0x0008, 0x0105 */
    "Context Group Version\0" /* 131, 0x0008, 0x0106 */
    "Code Set Extension Flag\0" /* 132, 0x0008, 0x010b */
    "Private Coding Scheme Creator UID\0" /* 133, 0x0008, 0x010c */
    "Code Set Extension Creator UID\0" /* 134, 0x0008, 0x010d */
    "Context Identifier\0" /* 135, 0x0008, 0x010f */
    "Network ID\0" /* 136, 0x0008, 0x1000 */
    "Station Name\0" /* 137, 0x0008, 0x1010 */
    "Study Description\0" /* 138, 0x0008, 0x1030 */
    "Procedure Code Sequence\0" /* 139, 0x0008, 0x1032 */
    "Series Description\0" /* 140, 0x0008, 0x103e */
    "Institutional Department Name\0" /* 141, 0x0008, 0x1040 */
    "Physician of Record\0" /* 142, 0x0008, 0x1048 */
    "Performing Physician's Name\0" /* 143, 0x0008, 0x1050 */
    "Name of Physician(s) Reading Study\0" /* 144, 0x0008, 0x1060 */
    "Operator's Name\0" /* 145, 0x0008, 0x1070 */
    "Admitting Diagnosis Description\0" /* 146, 0x0008, 0x1080 */
    "Admitting Diagnosis Code Sequence\0" /* 147, 0x0008, 0x1084 */
    "Manufacturer's Model Name\0" /* 148, 0x0008, 0x1090 */
    "Referenced Results Sequence\0" /* 149, 0x0008, 0x1100 */
    "Referenced Study Sequence\0" /* 150, 0x0008, 0x1110 */
    "Referenced Study Component Sequence\0" /* 151, 0x0008, 0x1111 */
    "Referenced Series Sequence\0" /* 152, 0x0008, 0x1115 */
    "Referenced Patient Sequence\0" /* 153, 0x0008, 0x1120 */
    "Referenced Visit Sequence\0" /* 154, 0x0008, 0x1125 */
    "Referenced Overlay Sequence\0" /* 155, 0x0008, 0x1130 */
    "Referenced Image Sequence\0" /* 156, 0x0008, 0x1140 */
    "Referenced Curve Sequence\0" /* 157, 0x0008, 0x1145 */
    "Referenced Previous Waveform\0" /* 158, 0x0008, 0x1148 */
    "Referenced Simultaneous Waveforms\0" /* 159, 0x0008, 0x114a */
    "Referenced Subsequent Waveform\0" /* 160, 0x0008, 0x114c */
    "Referenced SOP Class UID\0" /* 161, 0x0008, 0x1150 */
    "Referenced SOP Instance UID\0" /* 162, 0x0008, 0x1155 */
    "Referenced Frame Number\0" /* 163, 0x0008, 0x1160 */
    "Transaction UID\0" /* 164, 0x0008, 0x1195 */
    "Failure Reason\0" /* 165, 0x0008, 0x1197 */
    "Failed SOP Sequence\0" /* 166, 0x0008, 0x1198 */
    "Referenced SOP Sequence\0" /* 167, 0x0008, 0x1199 */
    "Old Lossy Image Compression\0" /* 168, 0x0008, 0x2110 */
    "Derivation Description\0" /* 169, 0x0008, 0x2111 */
    "Source Image Sequence\0" /* 170, 0x0008, 0x2112 */
    "Stage Name\0" /* 171, 0x0008, 0x2120 */
    "Stage Number\0" /* 172, 0x0008, 0x2122 */
    "Number of Stages\0" /* 173, 0x0008, 0x2124 */
    "View Number\0" /* 174, 0x0008, 0x2128 */
    "Number of Event Timers\0" /* 175, 0x0008, 0x2129 */
    "Number of Views in Stage\0" /* 176, 0x0008, 0x212a */
    "Event Elapsed Time(s)\0" /* 177, 0x0008, 0x2130 */
    "Event Timer Name(s)\0" /* 178, 0x0008, 0x2132 */
    "Start Trim\0" /* 179, 0x0008, 0x2142 */
    "Stop Trim\0" /* 180, 0x0008, 0x2143 */
    "Recommended Display Frame Rate\0" /* 181, 0x0008, 0x2144 */
    "Transducer Position\0" /* 182, 0x0008, 0x2200 */
    "Transducer Orientation\0" /* 183, 0x0008, 0x2204 */
    "Anatomic Structure\0" /* 184, 0x0008, 0x2208 */
    "Anatomic Region Sequence\0" /* 185, 0x0008, 0x2218 */
    "Anatomic Region Modifier Sequence\0" /* 186, 0x0008, 0x2220 */
    "Primary Anatomic Structure Sequence\0" /* 187, 0x0008, 0x2228 */
    "Primary Anatomic Structure Modifier Sequence\0" /* 188, 0x0008, 0x2230 */
    "Transducer Position Sequence\0" /* 189, 0x0008, 0x2240 */
    "Transducer Position Modifier Sequence\0" /* 190, 0x0008, 0x2242 */
    "Transducer Orientation Sequence\0" /* 191, 0x0008, 0x2244 */
    "Transducer Orientation Modifier Sequence\0" /* 192, 0x0008, 0x2246 */
    "Anatomic Structure Space Or Region Code Sequence\0" /* 193, 0x0008, 0x2251 */
    "Anatomic Portal Of Entrance Code Sequence\0" /* 194, 0x0008, 0x2253 */
    "Anatomic Approach Direction Code Sequence\0" /* 195, 0x0008, 0x2255 */
    "Anatomic Perspective Description\0" /* 196, 0x0008, 0x2256 */
    "Anatomic Perspective Code Sequence\0" /* 197, 0x0008, 0x2257 */
    "Anatomic Location Of Examining Instrument Description\0" /* 198, 0x0008, 0x2258 */
    "Anatomic Location Of Examining Instrument Code Sequence\0" /* 199, 0x0008, 0x2259 */
    "Anatomic Structure Space Or Region Modifier Code Sequence\0" /* 200, 0x0008, 0x225a */
    "OnAxis Background Anatomic Structure Code Sequence\0" /* 201, 0x0008, 0x225c */
    "Identifying Comments\0" /* 202, 0x0008, 0x4000 */
    "?\0" /* 203, 0x0009, 0x0000 */
    "?\0" /* 204, 0x0009, 0x0001 */
    "?\0" /* 205, 0x0009, 0x0002 */
    "?\0" /* 206, 0x0009, 0x0003 */
    "?\0" /* 207, 0x0009, 0x0004 */
    "?\0" /* 208, 0x0009, 0x0005 */
    "?\0" /* 209, 0x0009, 0x0006 */
    "?\0" /* 210, 0x0009, 0x0007 */
    "?\0" /* 211, 0x0009, 0x0008 */
    "?\0" /* 212, 0x0009, 0x0009 */
    "?\0" /* 213, 0x0009, 0x000a */
    "?\0" /* 214, 0x0009, 0x000b */
    "?\0" /* 215, 0x0009, 0x000c */
    "?\0" /* 216, 0x0009, 0x000d */
    "?\0" /* 217, 0x0009, 0x000e */
    "?\0" /* 218, 0x0009, 0x000f */
    "?\0" /* 219, 0x0009, 0x0010 */
    "?\0" /* 220, 0x0009, 0x0011 */
    "?\0" /* 221, 0x0009, 0x0012 */
    "?\0" /* 222, 0x0009, 0x0013 */
    "?\0" /* 223, 0x0009, 0x0014 */
    "?\0" /* 224, 0x0009, 0x0015 */
    "?\0" /* 225, 0x0009, 0x0016 */
    "?\0" /* 226, 0x0009, 0x0017 */
    "Data Set Identifier\0" /* 227, 0x0009, 0x0018 */
    "?\0" /* 228, 0x0009, 0x001a */
    "?\0" /* 229, 0x0009, 0x001e */
    "?\0" /* 230, 0x0009, 0x0020 */
    "?\0" /* 231, 0x0009, 0x0021 */
    "User Orientation\0" /* 232, 0x0009, 0x0022 */
    "Initiation Type\0" /* 233, 0x0009, 0x0023 */
    "?\0" /* 234, 0x0009, 0x0024 */
    "?\0" /* 235, 0x0009, 0x0025 */
    "?\0" /* 236, 0x0009, 0x0026 */
    "?\0" /* 237, 0x0009, 0x0027 */
    "?\0" /* 238, 0x0009, 0x0029 */
    "?\0" /* 239, 0x0009, 0x002a */
    "Series Comments\0" /* 240, 0x0009, 0x002c */
    "Track Beat Average\0" /* 241, 0x0009, 0x002d */
    "Distance Prescribed\0" /* 242, 0x0009, 0x002e */
    "?\0" /* 243, 0x0009, 0x002f */
    "?\0" /* 244, 0x0009, 0x0030 */
    "?\0" /* 245, 0x0009, 0x0031 */
    "?\0" /* 246, 0x0009, 0x0032 */
    "?\0" /* 247, 0x0009, 0x0034 */
    "Gantry Locus Type\0" /* 248, 0x0009, 0x0035 */
    "Starting Heart Rate\0" /* 249, 0x0009, 0x0037 */
    "?\0" /* 250, 0x0009, 0x0038 */
    "RR Window Offset\0" /* 251, 0x0009, 0x0039 */
    "Percent Cycle Imaged\0" /* 252, 0x0009, 0x003a */
    "?\0" /* 253, 0x0009, 0x003e */
    "?\0" /* 254, 0x0009, 0x003f */
    "?\0" /* 255, 0x0009, 0x0040 */
    "?\0" /* 256, 0x0009, 0x0041 */
    "?\0" /* 257, 0x0009, 0x0042 */
    "?\0" /* 258, 0x0009, 0x0043 */
    "?\0" /* 259, 0x0009, 0x0050 */
    "?\0" /* 260, 0x0009, 0x0051 */
    "?\0" /* 261, 0x0009, 0x0060 */
    "Series Unique Identifier\0" /* 262, 0x0009, 0x0061 */
    "?\0" /* 263, 0x0009, 0x0070 */
    "?\0" /* 264, 0x0009, 0x0080 */
    "?\0" /* 265, 0x0009, 0x0091 */
    "?\0" /* 266, 0x0009, 0x00e2 */
    "Equipment UID\0" /* 267, 0x0009, 0x00e3 */
    "Genesis Version Now\0" /* 268, 0x0009, 0x00e6 */
    "Exam Record Checksum\0" /* 269, 0x0009, 0x00e7 */
    "?\0" /* 270, 0x0009, 0x00e8 */
    "Actual Series Data Time Stamp\0" /* 271, 0x0009, 0x00e9 */
    "?\0" /* 272, 0x0009, 0x00f2 */
    "?\0" /* 273, 0x0009, 0x00f3 */
    "?\0" /* 274, 0x0009, 0x00f4 */
    "?\0" /* 275, 0x0009, 0x00f5 */
    "PDM Data Object Type Extension\0" /* 276, 0x0009, 0x00f6 */
    "?\0" /* 277, 0x0009, 0x00f8 */
    "?\0" /* 278, 0x0009, 0x00fb */
    "?\0" /* 279, 0x0009, 0x1002 */
    "?\0" /* 280, 0x0009, 0x1003 */
    "?\0" /* 281, 0x0009, 0x1010 */
    "Patient Group Length\0" /* 282, 0x0010, 0x0000 */
    "Patient's Name\0" /* 283, 0x0010, 0x0010 */
    "Patient's ID\0" /* 284, 0x0010, 0x0020 */
    "Issuer of Patient's ID\0" /* 285, 0x0010, 0x0021 */
    "Patient's Birth Date\0" /* 286, 0x0010, 0x0030 */
    "Patient's Birth Time\0" /* 287, 0x0010, 0x0032 */
    "Patient's Sex\0" /* 288, 0x0010, 0x0040 */
    "Patient's Insurance Plan Code Sequence\0" /* 289, 0x0010, 0x0050 */
    "Other Patient's ID's\0" /* 290, 0x0010, 0x1000 */
    "Other Patient's Names\0" /* 291, 0x0010, 0x1001 */
    "Patient's Birth Name\0" /* 292, 0x0010, 0x1005 */
    "Patient's Age\0" /* 293, 0x0010, 0x1010 */
    "Patient's Size\0" /* 294, 0x0010, 0x1020 */
    "Patient's Weight\0" /* 295, 0x0010, 0x1030 */
    "Patient's Address\0" /* 296, 0x0010, 0x1040 */
    "Insurance Plan Identification\0" /* 297, 0x0010, 0x1050 */
    "Patient's Mother's Birth Name\0" /* 298, 0x0010, 0x1060 */
    "Military Rank\0" /* 299, 0x0010, 0x1080 */
    "Branch of Service\0" /* 300, 0x0010, 0x1081 */
    "Medical Record Locator\0" /* 301, 0x0010, 0x1090 */
    "Medical Alerts\0" /* 302, 0x0010, 0x2000 */
    "Contrast Allergies\0" /* 303, 0x0010, 0x2110 */
    "Country of Residence\0" /* 304, 0x0010, 0x2150 */
    "Region of Residence\0" /* 305, 0x0010, 0x2152 */
    "Patients Telephone Numbers\0" /* 306, 0x0010, 0x2154 */
    "Ethnic Group\0" /* 307, 0x0010, 0x2160 */
    "Occupation\0" /* 308, 0x0010, 0x2180 */
    "Smoking Status\0" /* 309, 0x0010, 0x21a0 */
    "Additional Patient History\0" /* 310, 0x0010, 0x21b0 */
    "Pregnancy Status\0" /* 311, 0x0010, 0x21c0 */
    "Last Menstrual Date\0" /* 312, 0x0010, 0x21d0 */
    "Patients Religious Preference\0" /* 313, 0x0010, 0x21f0 */
    "Patient Comments\0" /* 314, 0x0010, 0x4000 */
    "?\0" /* 315, 0x0011, 0x0001 */
    "?\0" /* 316, 0x0011, 0x0002 */
    "Patient UID\0" /* 317, 0x0011, 0x0003 */
    "Patient ID\0" /* 318, 0x0011, 0x0004 */
    "?\0" /* 319, 0x0011, 0x000a */
    "Effective Series Duration\0" /* 320, 0x0011, 0x000b */
    "Num Beats\0" /* 321, 0x0011, 0x000c */
    "Radio Nuclide Name\0" /* 322, 0x0011, 0x000d */
    "?\0" /* 323, 0x0011, 0x0010 */
    "?\0" /* 324, 0x0011, 0x0011 */
    "Dataset Name\0" /* 325, 0x0011, 0x0012 */
    "Dataset Type\0" /* 326, 0x0011, 0x0013 */
    "?\0" /* 327, 0x0011, 0x0015 */
    "Energy Number\0" /* 328, 0x0011, 0x0016 */
    "RR Interval Window Number\0" /* 329, 0x0011, 0x0017 */
    "MG Bin Number\0" /* 330, 0x0011, 0x0018 */
    "Radius Of Rotation\0" /* 331, 0x0011, 0x0019 */
    "Detector Count Zone\0" /* 332, 0x0011, 0x001a */
    "Num Energy Windows\0" /* 333, 0x0011, 0x001b */
    "Energy Offset\0" /* 334, 0x0011, 0x001c */
    "Energy Range\0" /* 335, 0x0011, 0x001d */
    "Image Orientation\0" /* 336, 0x0011, 0x001f */
    "?\0" /* 337, 0x0011, 0x0020 */
    "?\0" /* 338, 0x0011, 0x0021 */
    "?\0" /* 339, 0x0011, 0x0022 */
    "?\0" /* 340, 0x0011, 0x0023 */
    "FOV Mask Y Cutoff Angle\0" /* 341, 0x0011, 0x0024 */
    "?\0" /* 342, 0x0011, 0x0025 */
    "Table Orientation\0" /* 343, 0x0011, 0x0026 */
    "ROI Top Left\0" /* 344, 0x0011, 0x0027 */
    "ROI Bottom Right\0" /* 345, 0x0011, 0x0028 */
    "?\0" /* 346, 0x0011, 0x0030 */
    "?\0" /* 347, 0x0011, 0x0031 */
    "?\0" /* 348, 0x0011, 0x0032 */
    "Energy Correct Name\0" /* 349, 0x0011, 0x0033 */
    "Spatial Correct Name\0" /* 350, 0x0011, 0x0034 */
    "?\0" /* 351, 0x0011, 0x0035 */
    "Uniformity Correct Name\0" /* 352, 0x0011, 0x0036 */
    "Acquisition Specific Correct Name\0" /* 353, 0x0011, 0x0037 */
    "Byte Order\0" /* 354, 0x0011, 0x0038 */
    "Picture Format\0" /* 355, 0x0011, 0x003a */
    "Pixel Scale\0" /* 356, 0x0011, 0x003b */
    "Pixel Offset\0" /* 357, 0x0011, 0x003c */
    "FOV Shape\0" /* 358, 0x0011, 0x003e */
    "Dataset Flags\0" /* 359, 0x0011, 0x003f */
    "?\0" /* 360, 0x0011, 0x0040 */
    "Medical Alerts\0" /* 361, 0x0011, 0x0041 */
    "Contrast Allergies\0" /* 362, 0x0011, 0x0042 */
    "Threshold Center\0" /* 363, 0x0011, 0x0044 */
    "Threshold Width\0" /* 364, 0x0011, 0x0045 */
    "Interpolation Type\0" /* 365, 0x0011, 0x0046 */
    "Period\0" /* 366, 0x0011, 0x0055 */
    "ElapsedTime\0" /* 367, 0x0011, 0x0056 */
    "Patient Registration Date\0" /* 368, 0x0011, 0x00a1 */
    "Patient Registration Time\0" /* 369, 0x0011, 0x00a2 */
    "Patient Last Name\0" /* 370, 0x0011, 0x00b0 */
    "Patient First Name\0" /* 371, 0x0011, 0x00b2 */
    "Patient Hospital Status\0" /* 372, 0x0011, 0x00b4 */
    "Current Location Time\0" /* 373, 0x0011, 0x00bc */
    "Patient Insurance Status\0" /* 374, 0x0011, 0x00c0 */
    "Patient Billing Type\0" /* 375, 0x0011, 0x00d0 */
    "Patient Billing Address\0" /* 376, 0x0011, 0x00d2 */
    "Modifying Physician\0" /* 377, 0x0013, 0x0000 */
    "?\0" /* 378, 0x0013, 0x0010 */
    "?\0" /* 379, 0x0013, 0x0011 */
    "?\0" /* 380, 0x0013, 0x0012 */
    "AutoTrack Peak\0" /* 381, 0x0013, 0x0016 */
    "AutoTrack Width\0" /* 382, 0x0013, 0x0017 */
    "Transmission Scan Time\0" /* 383, 0x0013, 0x0018 */
    "Transmission Mask Width\0" /* 384, 0x0013, 0x0019 */
    "Copper Attenuator Thickness\0" /* 385, 0x0013, 0x001a */
    "?\0" /* 386, 0x0013, 0x001c */
    "?\0" /* 387, 0x0013, 0x001d */
    "Tomo View Offset\0" /* 388, 0x0013, 0x001e */
    "Patient Name\0" /* 389, 0x0013, 0x0020 */
    "Patient Id\0" /* 390, 0x0013, 0x0022 */
    "Study Comments\0" /* 391, 0x0013, 0x0026 */
    "Patient Birthdate\0" /* 392, 0x0013, 0x0030 */
    "Patient Weight\0" /* 393, 0x0013, 0x0031 */
    "Patients Maiden Name\0" /* 394, 0x0013, 0x0032 */
    "Referring Physician\0" /* 395, 0x0013, 0x0033 */
    "Admitting Diagnosis\0" /* 396, 0x0013, 0x0034 */
    "Patient Sex\0" /* 397, 0x0013, 0x0035 */
    "Procedure Description\0" /* 398, 0x0013, 0x0040 */
    "Patient Rest Direction\0" /* 399, 0x0013, 0x0042 */
    "Patient Position\0" /* 400, 0x0013, 0x0044 */
    "View Direction\0" /* 401, 0x0013, 0x0046 */
    "Stenosis Calibration Ratio\0" /* 402, 0x0015, 0x0001 */
    "Stenosis Magnification\0" /* 403, 0x0015, 0x0002 */
    "Cardiac Calibration Ratio\0" /* 404, 0x0015, 0x0003 */
    "Acquisition Group Length\0" /* 405, 0x0018, 0x0000 */
    "Contrast/Bolus Agent\0" /* 406, 0x0018, 0x0010 */
    "Contrast/Bolus Agent Sequence\0" /* 407, 0x0018, 0x0012 */
    "Contrast/Bolus Administration Route Sequence\0" /* 408, 0x0018, 0x0014 */
    "Body Part Examined\0" /* 409, 0x0018, 0x0015 */
    "Scanning Sequence\0" /* 410, 0x0018, 0x0020 */
    "Sequence Variant\0" /* 411, 0x0018, 0x0021 */
    "Scan Options\0" /* 412, 0x0018, 0x0022 */
    "MR Acquisition Type\0" /* 413, 0x0018, 0x0023 */
    "Sequence Name\0" /* 414, 0x0018, 0x0024 */
    "Angio Flag\0" /* 415, 0x0018, 0x0025 */
    "Intervention Drug Information Sequence\0" /* 416, 0x0018, 0x0026 */
    "Intervention Drug Stop Time\0" /* 417, 0x0018, 0x0027 */
    "Intervention Drug Dose\0" /* 418, 0x0018, 0x0028 */
    "Intervention Drug Code Sequence\0" /* 419, 0x0018, 0x0029 */
    "Additional Drug Sequence\0" /* 420, 0x0018, 0x002a */
    "Radionuclide\0" /* 421, 0x0018, 0x0030 */
    "Radiopharmaceutical\0" /* 422, 0x0018, 0x0031 */
    "Energy Window Centerline\0" /* 423, 0x0018, 0x0032 */
    "Energy Window Total Width\0" /* 424, 0x0018, 0x0033 */
    "Intervention Drug Name\0" /* 425, 0x0018, 0x0034 */
    "Intervention Drug Start Time\0" /* 426, 0x0018, 0x0035 */
    "Intervention Therapy Sequence\0" /* 427, 0x0018, 0x0036 */
    "Therapy Type\0" /* 428, 0x0018, 0x0037 */
    "Intervention Status\0" /* 429, 0x0018, 0x0038 */
    "Therapy Description\0" /* 430, 0x0018, 0x0039 */
    "Cine Rate\0" /* 431, 0x0018, 0x0040 */
    "Slice Thickness\0" /* 432, 0x0018, 0x0050 */
    "KVP\0" /* 433, 0x0018, 0x0060 */
    "Counts Accumulated\0" /* 434, 0x0018, 0x0070 */
    "Acquisition Termination Condition\0" /* 435, 0x0018, 0x0071 */
    "Effective Series Duration\0" /* 436, 0x0018, 0x0072 */
    "Acquisition Start Condition\0" /* 437, 0x0018, 0x0073 */
    "Acquisition Start Condition Data\0" /* 438, 0x0018, 0x0074 */
    "Acquisition Termination Condition Data\0" /* 439, 0x0018, 0x0075 */
    "Repetition Time\0" /* 440, 0x0018, 0x0080 */
    "Echo Time\0" /* 441, 0x0018, 0x0081 */
    "Inversion Time\0" /* 442, 0x0018, 0x0082 */
    "Number of Averages\0" /* 443, 0x0018, 0x0083 */
    "Imaging Frequency\0" /* 444, 0x0018, 0x0084 */
    "Imaged Nucleus\0" /* 445, 0x0018, 0x0085 */
    "Echo Number(s)\0" /* 446, 0x0018, 0x0086 */
    "Magnetic Field Strength\0" /* 447, 0x0018, 0x0087 */
    "Spacing Between Slices\0" /* 448, 0x0018, 0x0088 */
    "Number of Phase Encoding Steps\0" /* 449, 0x0018, 0x0089 */
    "Data Collection Diameter\0" /* 450, 0x0018, 0x0090 */
    "Echo Train Length\0" /* 451, 0x0018, 0x0091 */
    "Percent Sampling\0" /* 452, 0x0018, 0x0093 */
    "Percent Phase Field of View\0" /* 453, 0x0018, 0x0094 */
    "Pixel Bandwidth\0" /* 454, 0x0018, 0x0095 */
    "Device Serial Number\0" /* 455, 0x0018, 0x1000 */
    "Plate ID\0" /* 456, 0x0018, 0x1004 */
    "Secondary Capture Device ID\0" /* 457, 0x0018, 0x1010 */
    "Date of Secondary Capture\0" /* 458, 0x0018, 0x1012 */
    "Time of Secondary Capture\0" /* 459, 0x0018, 0x1014 */
    "Secondary Capture Device Manufacturer\0" /* 460, 0x0018, 0x1016 */
    "Secondary Capture Device Manufacturer Model Name\0" /* 461, 0x0018, 0x1018 */
    "Secondary Capture Device Software Version(s)\0" /* 462, 0x0018, 0x1019 */
    "Software Version(s)\0" /* 463, 0x0018, 0x1020 */
    "Video Image Format Acquired\0" /* 464, 0x0018, 0x1022 */
    "Digital Image Format Acquired\0" /* 465, 0x0018, 0x1023 */
    "Protocol Name\0" /* 466, 0x0018, 0x1030 */
    "Contrast/Bolus Route\0" /* 467, 0x0018, 0x1040 */
    "Contrast/Bolus Volume\0" /* 468, 0x0018, 0x1041 */
    "Contrast/Bolus Start Time\0" /* 469, 0x0018, 0x1042 */
    "Contrast/Bolus Stop Time\0" /* 470, 0x0018, 0x1043 */
    "Contrast/Bolus Total Dose\0" /* 471, 0x0018, 0x1044 */
    "Syringe Counts\0" /* 472, 0x0018, 0x1045 */
    "Contrast Flow Rate\0" /* 473, 0x0018, 0x1046 */
    "Contrast Flow Duration\0" /* 474, 0x0018, 0x1047 */
    "Contrast/Bolus Ingredient\0" /* 475, 0x0018, 0x1048 */
    "Contrast/Bolus Ingredient Concentration\0" /* 476, 0x0018, 0x1049 */
    "Spatial Resolution\0" /* 477, 0x0018, 0x1050 */
    "Trigger Time\0" /* 478, 0x0018, 0x1060 */
    "Trigger Source or Type\0" /* 479, 0x0018, 0x1061 */
    "Nominal Interval\0" /* 480, 0x0018, 0x1062 */
    "Frame Time\0" /* 481, 0x0018, 0x1063 */
    "Framing Type\0" /* 482, 0x0018, 0x1064 */
    "Frame Time Vector\0" /* 483, 0x0018, 0x1065 */
    "Frame Delay\0" /* 484, 0x0018, 0x1066 */
    "Image Trigger Delay\0" /* 485, 0x0018, 0x1067 */
    "Group Time Offset\0" /* 486, 0x0018, 0x1068 */
    "Trigger Time Offset\0" /* 487, 0x0018, 0x1069 */
    "Synchronization Trigger\0" /* 488, 0x0018, 0x106a */
    "Synchronization Frame of Reference\0" /* 489, 0x0018, 0x106b */
    "Trigger Sample Position\0" /* 490, 0x0018, 0x106e */
    "Radiopharmaceutical Route\0" /* 491, 0x0018, 0x1070 */
    "Radiopharmaceutical Volume\0" /* 492, 0x0018, 0x1071 */
    "Radiopharmaceutical Start Time\0" /* 493, 0x0018, 0x1072 */
    "Radiopharmaceutical Stop Time\0" /* 494, 0x0018, 0x1073 */
    "Radionuclide Total Dose\0" /* 495, 0x0018, 0x1074 */
    "Radionuclide Half Life\0" /* 496, 0x0018, 0x1075 */
    "Radionuclide Positron Fraction\0" /* 497, 0x0018, 0x1076 */
    "Radiopharmaceutical Specific Activity\0" /* 498, 0x0018, 0x1077 */
    "Beat Rejection Flag\0" /* 499, 0x0018, 0x1080 */
    "Low R-R Value\0" /* 500, 0x0018, 0x1081 */
    "High R-R Value\0" /* 501, 0x0018, 0x1082 */
    "Intervals Acquired\0" /* 502, 0x0018, 0x1083 */
    "Intervals Rejected\0" /* 503, 0x0018, 0x1084 */
    "PVC Rejection\0" /* 504, 0x0018, 0x1085 */
    "Skip Beats\0" /* 505, 0x0018, 0x1086 */
    "Heart Rate\0" /* 506, 0x0018, 0x1088 */
    "Cardiac Number of Images\0" /* 507, 0x0018, 0x1090 */
    "Trigger Window\0" /* 508, 0x0018, 0x1094 */
    "Reconstruction Diameter\0" /* 509, 0x0018, 0x1100 */
    "Distance Source to Detector\0" /* 510, 0x0018, 0x1110 */
    "Distance Source to Patient\0" /* 511, 0x0018, 0x1111 */
    "Estimated Radiographic Magnification Factor\0" /* 512, 0x0018, 0x1114 */
    "Gantry/Detector Tilt\0" /* 513, 0x0018, 0x1120 */
    "Gantry/Detector Slew\0" /* 514, 0x0018, 0x1121 */
    "Table Height\0" /* 515, 0x0018, 0x1130 */
    "Table Traverse\0" /* 516, 0x0018, 0x1131 */
    "Table Motion\0" /* 517, 0x0018, 0x1134 */
    "Table Vertical Increment\0" /* 518, 0x0018, 0x1135 */
    "Table Lateral Increment\0" /* 519, 0x0018, 0x1136 */
    "Table Longitudinal Increment\0" /* 520, 0x0018, 0x1137 */
    "Table Angle\0" /* 521, 0x0018, 0x1138 */
    "Table Type\0" /* 522, 0x0018, 0x113a */
    "Rotation Direction\0" /* 523, 0x0018, 0x1140 */
    "Angular Position\0" /* 524, 0x0018, 0x1141 */
    "Radial Position\0" /* 525, 0x0018, 0x1142 */
    "Scan Arc\0" /* 526, 0x0018, 0x1143 */
    "Angular Step\0" /* 527, 0x0018, 0x1144 */
    "Center of Rotation Offset\0" /* 528, 0x0018, 0x1145 */
    "Rotation Offset\0" /* 529, 0x0018, 0x1146 */
    "Field of View Shape\0" /* 530, 0x0018, 0x1147 */
    "Field of View Dimension(s)\0" /* 531, 0x0018, 0x1149 */
    "Exposure Time\0" /* 532, 0x0018, 0x1150 */
    "X-ray Tube Current\0" /* 533, 0x0018, 0x1151 */
    "Exposure\0" /* 534, 0x0018, 0x1152 */
    "Exposure in uAs\0" /* 535, 0x0018, 0x1153 */
    "AveragePulseWidth\0" /* 536, 0x0018, 0x1154 */
    "RadiationSetting\0" /* 537, 0x0018, 0x1155 */
    "Rectification Type\0" /* 538, 0x0018, 0x1156 */
    "RadiationMode\0" /* 539, 0x0018, 0x115a */
    "ImageAreaDoseProduct\0" /* 540, 0x0018, 0x115e */
    "Filter Type\0" /* 541, 0x0018, 0x1160 */
    "TypeOfFilters\0" /* 542, 0x0018, 0x1161 */
    "IntensifierSize\0" /* 543, 0x0018, 0x1162 */
    "ImagerPixelSpacing\0" /* 544, 0x0018, 0x1164 */
    "Grid\0" /* 545, 0x0018, 0x1166 */
    "Generator Power\0" /* 546, 0x0018, 0x1170 */
    "Collimator/Grid Name\0" /* 547, 0x0018, 0x1180 */
    "Collimator Type\0" /* 548, 0x0018, 0x1181 */
    "Focal Distance\0" /* 549, 0x0018, 0x1182 */
    "X Focus Center\0" /* 550, 0x0018, 0x1183 */
    "Y Focus Center\0" /* 551, 0x0018, 0x1184 */
    "Focal Spot(s)\0" /* 552, 0x0018, 0x1190 */
    "Anode Target Material\0" /* 553, 0x0018, 0x1191 */
    "Body Part Thickness\0" /* 554, 0x0018, 0x11a0 */
    "Compression Force\0" /* 555, 0x0018, 0x11a2 */
    "Date of Last Calibration\0" /* 556, 0x0018, 0x1200 */
    "Time of Last Calibration\0" /* 557, 0x0018, 0x1201 */
    "Convolution Kernel\0" /* 558, 0x0018, 0x1210 */
    "Upper/Lower Pixel Values\0" /* 559, 0x0018, 0x1240 */
    "Actual Frame Duration\0" /* 560, 0x0018, 0x1242 */
    "Count Rate\0" /* 561, 0x0018, 0x1243 */
    "Preferred Playback Sequencing\0" /* 562, 0x0018, 0x1244 */
    "Receiving Coil\0" /* 563, 0x0018, 0x1250 */
    "Transmitting Coil\0" /* 564, 0x0018, 0x1251 */
    "Plate Type\0" /* 565, 0x0018, 0x1260 */
    "Phosphor Type\0" /* 566, 0x0018, 0x1261 */
    "Scan Velocity\0" /* 567, 0x0018, 0x1300 */
    "Whole Body Technique\0" /* 568, 0x0018, 0x1301 */
    "Scan Length\0" /* 569, 0x0018, 0x1302 */
    "Acquisition Matrix\0" /* 570, 0x0018, 0x1310 */
    "Phase Encoding Direction\0" /* 571, 0x0018, 0x1312 */
    "Flip Angle\0" /* 572, 0x0018, 0x1314 */
    "Variable Flip Angle Flag\0" /* 573, 0x0018, 0x1315 */
    "SAR\0" /* 574, 0x0018, 0x1316 */
    "dB/dt\0" /* 575, 0x0018, 0x1318 */
    "Acquisition Device Processing Description\0" /* 576, 0x0018, 0x1400 */
    "Acquisition Device Processing Code\0" /* 577, 0x0018, 0x1401 */
    "Cassette Orientation\0" /* 578, 0x0018, 0x1402 */
    "Cassette Size\0" /* 579, 0x0018, 0x1403 */
    "Exposures on Plate\0" /* 580, 0x0018, 0x1404 */
    "Relative X-ray Exposure\0" /* 581, 0x0018, 0x1405 */
    "Column Angulation\0" /* 582, 0x0018, 0x1450 */
    "Tomo Layer Height\0" /* 583, 0x0018, 0x1460 */
    "Tomo Angle\0" /* 584, 0x0018, 0x1470 */
    "Tomo Time\0" /* 585, 0x0018, 0x1480 */
    "Tomo Type\0" /* 586, 0x0018, 0x1490 */
    "Tomo Class\0" /* 587, 0x0018, 0x1491 */
    "Number of Tomosynthesis Source Images\0" /* 588, 0x0018, 0x1495 */
    "PositionerMotion\0" /* 589, 0x0018, 0x1500 */
    "Positioner Type\0" /* 590, 0x0018, 0x1508 */
    "PositionerPrimaryAngle\0" /* 591, 0x0018, 0x1510 */
    "PositionerSecondaryAngle\0" /* 592, 0x0018, 0x1511 */
    "PositionerPrimaryAngleIncrement\0" /* 593, 0x0018, 0x1520 */
    "PositionerSecondaryAngleIncrement\0" /* 594, 0x0018, 0x1521 */
    "DetectorPrimaryAngle\0" /* 595, 0x0018, 0x1530 */
    "DetectorSecondaryAngle\0" /* 596, 0x0018, 0x1531 */
    "Shutter Shape\0" /* 597, 0x0018, 0x1600 */
    "Shutter Left Vertical Edge\0" /* 598, 0x0018, 0x1602 */
    "Shutter Right Vertical Edge\0" /* 599, 0x0018, 0x1604 */
    "Shutter Upper Horizontal Edge\0" /* 600, 0x0018, 0x1606 */
    "Shutter Lower Horizonta lEdge\0" /* 601, 0x0018, 0x1608 */
    "Center of Circular Shutter\0" /* 602, 0x0018, 0x1610 */
    "Radius of Circular Shutter\0" /* 603, 0x0018, 0x1612 */
    "Vertices of Polygonal Shutter\0" /* 604, 0x0018, 0x1620 */
    "Shutter Presentation Value\0" /* 605, 0x0018, 0x1622 */
    "Shutter Overlay Group\0" /* 606, 0x0018, 0x1623 */
    "Collimator Shape\0" /* 607, 0x0018, 0x1700 */
    "Collimator Left Vertical Edge\0" /* 608, 0x0018, 0x1702 */
    "Collimator Right Vertical Edge\0" /* 609, 0x0018, 0x1704 */
    "Collimator Upper Horizontal Edge\0" /* 610, 0x0018, 0x1706 */
    "Collimator Lower Horizontal Edge\0" /* 611, 0x0018, 0x1708 */
    "Center of Circular Collimator\0" /* 612, 0x0018, 0x1710 */
    "Radius of Circular Collimator\0" /* 613, 0x0018, 0x1712 */
    "Vertices of Polygonal Collimator\0" /* 614, 0x0018, 0x1720 */
    "Acquisition Time Synchronized\0" /* 615, 0x0018, 0x1800 */
    "Time Source\0" /* 616, 0x0018, 0x1801 */
    "Time Distribution Protocol\0" /* 617, 0x0018, 0x1802 */
    "Acquisition Comments\0" /* 618, 0x0018, 0x4000 */
    "Output Power\0" /* 619, 0x0018, 0x5000 */
    "Transducer Data\0" /* 620, 0x0018, 0x5010 */
    "Focus Depth\0" /* 621, 0x0018, 0x5012 */
    "Processing Function\0" /* 622, 0x0018, 0x5020 */
    "Postprocessing Function\0" /* 623, 0x0018, 0x5021 */
    "Mechanical Index\0" /* 624, 0x0018, 0x5022 */
    "Thermal Index\0" /* 625, 0x0018, 0x5024 */
    "Cranial Thermal Index\0" /* 626, 0x0018, 0x5026 */
    "Soft Tissue Thermal Index\0" /* 627, 0x0018, 0x5027 */
    "Soft Tissue-Focus Thermal Index\0" /* 628, 0x0018, 0x5028 */
    "Soft Tissue-Surface Thermal Index\0" /* 629, 0x0018, 0x5029 */
    "Dynamic Range\0" /* 630, 0x0018, 0x5030 */
    "Total Gain\0" /* 631, 0x0018, 0x5040 */
    "Depth of Scan Field\0" /* 632, 0x0018, 0x5050 */
    "Patient Position\0" /* 633, 0x0018, 0x5100 */
    "View Position\0" /* 634, 0x0018, 0x5101 */
    "Projection Eponymous Name Code Sequence\0" /* 635, 0x0018, 0x5104 */
    "Image Transformation Matrix\0" /* 636, 0x0018, 0x5210 */
    "Image Translation Vector\0" /* 637, 0x0018, 0x5212 */
    "Sensitivity\0" /* 638, 0x0018, 0x6000 */
    "Sequence of Ultrasound Regions\0" /* 639, 0x0018, 0x6011 */
    "Region Spatial Format\0" /* 640, 0x0018, 0x6012 */
    "Region Data Type\0" /* 641, 0x0018, 0x6014 */
    "Region Flags\0" /* 642, 0x0018, 0x6016 */
    "Region Location Min X0\0" /* 643, 0x0018, 0x6018 */
    "Region Location Min Y0\0" /* 644, 0x0018, 0x601a */
    "Region Location Max X1\0" /* 645, 0x0018, 0x601c */
    "Region Location Max Y1\0" /* 646, 0x0018, 0x601e */
    "Reference Pixel X0\0" /* 647, 0x0018, 0x6020 */
    "Reference Pixel Y0\0" /* 648, 0x0018, 0x6022 */
    "Physical Units X Direction\0" /* 649, 0x0018, 0x6024 */
    "Physical Units Y Direction\0" /* 650, 0x0018, 0x6026 */
    "Reference Pixel Physical Value X\0" /* 651, 0x0018, 0x6028 */
    "Reference Pixel Physical Value Y\0" /* 652, 0x0018, 0x602a */
    "Physical Delta X\0" /* 653, 0x0018, 0x602c */
    "Physical Delta Y\0" /* 654, 0x0018, 0x602e */
    "Transducer Frequency\0" /* 655, 0x0018, 0x6030 */
    "Transducer Type\0" /* 656, 0x0018, 0x6031 */
    "Pulse Repetition Frequency\0" /* 657, 0x0018, 0x6032 */
    "Doppler Correction Angle\0" /* 658, 0x0018, 0x6034 */
    "Steering Angle\0" /* 659, 0x0018, 0x6036 */
    "Doppler Sample Volume X Position\0" /* 660, 0x0018, 0x6038 */
    "Doppler Sample Volume Y Position\0" /* 661, 0x0018, 0x603a */
    "TM-Line Position X0\0" /* 662, 0x0018, 0x603c */
    "TM-Line Position Y0\0" /* 663, 0x0018, 0x603e */
    "TM-Line Position X1\0" /* 664, 0x0018, 0x6040 */
    "TM-Line Position Y1\0" /* 665, 0x0018, 0x6042 */
    "Pixel Component Organization\0" /* 666, 0x0018, 0x6044 */
    "Pixel Component Mask\0" /* 667, 0x0018, 0x6046 */
    "Pixel Component Range Start\0" /* 668, 0x0018, 0x6048 */
    "Pixel Component Range Stop\0" /* 669, 0x0018, 0x604a */
    "Pixel Component Physical Units\0" /* 670, 0x0018, 0x604c */
    "Pixel Component Data Type\0" /* 671, 0x0018, 0x604e */
    "Number of Table Break Points\0" /* 672, 0x0018, 0x6050 */
    "Table of X Break Points\0" /* 673, 0x0018, 0x6052 */
    "Table of Y Break Points\0" /* 674, 0x0018, 0x6054 */
    "Number of Table Entries\0" /* 675, 0x0018, 0x6056 */
    "Table of Pixel Values\0" /* 676, 0x0018, 0x6058 */
    "Table of Parameter Values\0" /* 677, 0x0018, 0x605a */
    "Detector Conditions Nominal Flag\0" /* 678, 0x0018, 0x7000 */
    "Detector Temperature\0" /* 679, 0x0018, 0x7001 */
    "Detector Type\0" /* 680, 0x0018, 0x7004 */
    "Detector Configuration\0" /* 681, 0x0018, 0x7005 */
    "Detector Description\0" /* 682, 0x0018, 0x7006 */
    "Detector Mode\0" /* 683, 0x0018, 0x7008 */
    "Detector ID\0" /* 684, 0x0018, 0x700a */
    "Date of Last Detector Calibration \0" /* 685, 0x0018, 0x700c */
    "Time of Last Detector Calibration\0" /* 686, 0x0018, 0x700e */
    "Exposures on Detector Since Last Calibration\0" /* 687, 0x0018, 0x7010 */
    "Exposures on Detector Since Manufactured\0" /* 688, 0x0018, 0x7011 */
    "Detector Time Since Last Exposure\0" /* 689, 0x0018, 0x7012 */
    "Detector Active Time\0" /* 690, 0x0018, 0x7014 */
    "Detector Activation Offset From Exposure\0" /* 691, 0x0018, 0x7016 */
    "Detector Binning\0" /* 692, 0x0018, 0x701a */
    "Detector Element Physical Size\0" /* 693, 0x0018, 0x7020 */
    "Detector Element Spacing\0" /* 694, 0x0018, 0x7022 */
    "Detector Active Shape\0" /* 695, 0x0018, 0x7024 */
    "Detector Active Dimensions\0" /* 696, 0x0018, 0x7026 */
    "Detector Active Origin\0" /* 697, 0x0018, 0x7028 */
    "Field of View Origin\0" /* 698, 0x0018, 0x7030 */
    "Field of View Rotation\0" /* 699, 0x0018, 0x7032 */
    "Field of View Horizontal Flip\0" /* 700, 0x0018, 0x7034 */
    "Grid Absorbing Material\0" /* 701, 0x0018, 0x7040 */
    "Grid Spacing Material\0" /* 702, 0x0018, 0x7041 */
    "Grid Thickness\0" /* 703, 0x0018, 0x7042 */
    "Grid Pitch\0" /* 704, 0x0018, 0x7044 */
    "Grid Aspect Ratio\0" /* 705, 0x0018, 0x7046 */
    "Grid Period\0" /* 706, 0x0018, 0x7048 */
    "Grid Focal Distance\0" /* 707, 0x0018, 0x704c */
    "Filter Material\0" /* 708, 0x0018, 0x7050 */
    "Filter Thickness Minimum\0" /* 709, 0x0018, 0x7052 */
    "Filter Thickness Maximum\0" /* 710, 0x0018, 0x7054 */
    "Exposure Control Mode\0" /* 711, 0x0018, 0x7060 */
    "Exposure Control Mode Description\0" /* 712, 0x0018, 0x7062 */
    "Exposure Status\0" /* 713, 0x0018, 0x7064 */
    "Phototimer Setting\0" /* 714, 0x0018, 0x7065 */
    "?\0" /* 715, 0x0019, 0x0000 */
    "?\0" /* 716, 0x0019, 0x0001 */
    "?\0" /* 717, 0x0019, 0x0002 */
    "?\0" /* 718, 0x0019, 0x0003 */
    "?\0" /* 719, 0x0019, 0x0004 */
    "?\0" /* 720, 0x0019, 0x0005 */
    "?\0" /* 721, 0x0019, 0x0006 */
    "?\0" /* 722, 0x0019, 0x0007 */
    "?\0" /* 723, 0x0019, 0x0008 */
    "?\0" /* 724, 0x0019, 0x0009 */
    "?\0" /* 725, 0x0019, 0x000a */
    "?\0" /* 726, 0x0019, 0x000b */
    "?\0" /* 727, 0x0019, 0x000c */
    "Time\0" /* 728, 0x0019, 0x000d */
    "?\0" /* 729, 0x0019, 0x000e */
    "Horizontal Frame Of Reference\0" /* 730, 0x0019, 0x000f */
    "?\0" /* 731, 0x0019, 0x0010 */
    "?\0" /* 732, 0x0019, 0x0011 */
    "?\0" /* 733, 0x0019, 0x0012 */
    "?\0" /* 734, 0x0019, 0x0013 */
    "?\0" /* 735, 0x0019, 0x0014 */
    "?\0" /* 736, 0x0019, 0x0015 */
    "?\0" /* 737, 0x0019, 0x0016 */
    "?\0" /* 738, 0x0019, 0x0017 */
    "?\0" /* 739, 0x0019, 0x0018 */
    "?\0" /* 740, 0x0019, 0x0019 */
    "?\0" /* 741, 0x0019, 0x001a */
    "?\0" /* 742, 0x0019, 0x001b */
    "Dose\0" /* 743, 0x0019, 0x001c */
    "Side Mark\0" /* 744, 0x0019, 0x001d */
    "?\0" /* 745, 0x0019, 0x001e */
    "Exposure Duration\0" /* 746, 0x0019, 0x001f */
    "?\0" /* 747, 0x0019, 0x0020 */
    "?\0" /* 748, 0x0019, 0x0021 */
    "?\0" /* 749, 0x0019, 0x0022 */
    "?\0" /* 750, 0x0019, 0x0023 */
    "?\0" /* 751, 0x0019, 0x0024 */
    "?\0" /* 752, 0x0019, 0x0025 */
    "?\0" /* 753, 0x0019, 0x0026 */
    "?\0" /* 754, 0x0019, 0x0027 */
    "?\0" /* 755, 0x0019, 0x0028 */
    "?\0" /* 756, 0x0019, 0x0029 */
    "?\0" /* 757, 0x0019, 0x002a */
    "Xray Off Position\0" /* 758, 0x0019, 0x002b */
    "?\0" /* 759, 0x0019, 0x002c */
    "?\0" /* 760, 0x0019, 0x002d */
    "?\0" /* 761, 0x0019, 0x002e */
    "Trigger Frequency\0" /* 762, 0x0019, 0x002f */
    "?\0" /* 763, 0x0019, 0x0030 */
    "?\0" /* 764, 0x0019, 0x0031 */
    "?\0" /* 765, 0x0019, 0x0032 */
    "ECG 2 Offset 2\0" /* 766, 0x0019, 0x0033 */
    "?\0" /* 767, 0x0019, 0x0034 */
    "?\0" /* 768, 0x0019, 0x0036 */
    "?\0" /* 769, 0x0019, 0x0038 */
    "?\0" /* 770, 0x0019, 0x0039 */
    "?\0" /* 771, 0x0019, 0x003a */
    "?\0" /* 772, 0x0019, 0x003b */
    "?\0" /* 773, 0x0019, 0x003c */
    "?\0" /* 774, 0x0019, 0x003e */
    "?\0" /* 775, 0x0019, 0x003f */
    "?\0" /* 776, 0x0019, 0x0040 */
    "?\0" /* 777, 0x0019, 0x0041 */
    "?\0" /* 778, 0x0019, 0x0042 */
    "?\0" /* 779, 0x0019, 0x0043 */
    "?\0" /* 780, 0x0019, 0x0044 */
    "?\0" /* 781, 0x0019, 0x0045 */
    "?\0" /* 782, 0x0019, 0x0046 */
    "?\0" /* 783, 0x0019, 0x0047 */
    "?\0" /* 784, 0x0019, 0x0048 */
    "?\0" /* 785, 0x0019, 0x0049 */
    "?\0" /* 786, 0x0019, 0x004a */
    "Data Size For Scan Data\0" /* 787, 0x0019, 0x004b */
    "?\0" /* 788, 0x0019, 0x004c */
    "?\0" /* 789, 0x0019, 0x004e */
    "?\0" /* 790, 0x0019, 0x0050 */
    "?\0" /* 791, 0x0019, 0x0051 */
    "?\0" /* 792, 0x0019, 0x0052 */
    "Barcode\0" /* 793, 0x0019, 0x0053 */
    "?\0" /* 794, 0x0019, 0x0054 */
    "Receiver Reference Gain\0" /* 795, 0x0019, 0x0055 */
    "?\0" /* 796, 0x0019, 0x0056 */
    "CT Water Number\0" /* 797, 0x0019, 0x0057 */
    "?\0" /* 798, 0x0019, 0x0058 */
    "?\0" /* 799, 0x0019, 0x005a */
    "?\0" /* 800, 0x0019, 0x005c */
    "?\0" /* 801, 0x0019, 0x005d */
    "?\0" /* 802, 0x0019, 0x005e */
    "Increment Between Channels\0" /* 803, 0x0019, 0x005f */
    "?\0" /* 804, 0x0019, 0x0060 */
    "?\0" /* 805, 0x0019, 0x0061 */
    "?\0" /* 806, 0x0019, 0x0062 */
    "?\0" /* 807, 0x0019, 0x0063 */
    "?\0" /* 808, 0x0019, 0x0064 */
    "?\0" /* 809, 0x0019, 0x0065 */
    "?\0" /* 810, 0x0019, 0x0066 */
    "?\0" /* 811, 0x0019, 0x0067 */
    "?\0" /* 812, 0x0019, 0x0068 */
    "Convolution Mode\0" /* 813, 0x0019, 0x0069 */
    "?\0" /* 814, 0x0019, 0x006a */
    "Field Of View In Detector Cells\0" /* 815, 0x0019, 0x006b */
    "?\0" /* 816, 0x0019, 0x006c */
    "?\0" /* 817, 0x0019, 0x006e */
    "?\0" /* 818, 0x0019, 0x0070 */
    "?\0" /* 819, 0x0019, 0x0071 */
    "?\0" /* 820, 0x0019, 0x0072 */
    "?\0" /* 821, 0x0019, 0x0073 */
    "?\0" /* 822, 0x0019, 0x0074 */
    "?\0" /* 823, 0x0019, 0x0075 */
    "?\0" /* 824, 0x0019, 0x0076 */
    "?\0" /* 825, 0x0019, 0x0077 */
    "?\0" /* 826, 0x0019, 0x0078 */
    "?\0" /* 827, 0x0019, 0x007a */
    "?\0" /* 828, 0x0019, 0x007c */
    "Second Echo\0" /* 829, 0x0019, 0x007d */
    "?\0" /* 830, 0x0019, 0x007e */
    "Table Delta\0" /* 831, 0x0019, 0x007f */
    "?\0" /* 832, 0x0019, 0x0080 */
    "?\0" /* 833, 0x0019, 0x0081 */
    "?\0" /* 834, 0x0019, 0x0082 */
    "?\0" /* 835, 0x0019, 0x0083 */
    "?\0" /* 836, 0x0019, 0x0084 */
    "?\0" /* 837, 0x0019, 0x0085 */
    "?\0" /* 838, 0x0019, 0x0086 */
    "?\0" /* 839, 0x0019, 0x0087 */
    "?\0" /* 840, 0x0019, 0x0088 */
    "?\0" /* 841, 0x0019, 0x008a */
    "Actual Receive Gain Digital\0" /* 842, 0x0019, 0x008b */
    "?\0" /* 843, 0x0019, 0x008c */
    "Delay After Trigger\0" /* 844, 0x0019, 0x008d */
    "?\0" /* 845, 0x0019, 0x008e */
    "Swap Phase Frequency\0" /* 846, 0x0019, 0x008f */
    "?\0" /* 847, 0x0019, 0x0090 */
    "?\0" /* 848, 0x0019, 0x0091 */
    "?\0" /* 849, 0x0019, 0x0092 */
    "?\0" /* 850, 0x0019, 0x0093 */
    "?\0" /* 851, 0x0019, 0x0094 */
    "Analog Receiver Gain\0" /* 852, 0x0019, 0x0095 */
    "?\0" /* 853, 0x0019, 0x0096 */
    "?\0" /* 854, 0x0019, 0x0097 */
    "?\0" /* 855, 0x0019, 0x0098 */
    "?\0" /* 856, 0x0019, 0x0099 */
    "?\0" /* 857, 0x0019, 0x009a */
    "Pulse Sequence Mode\0" /* 858, 0x0019, 0x009b */
    "?\0" /* 859, 0x0019, 0x009c */
    "Pulse Sequence Date\0" /* 860, 0x0019, 0x009d */
    "?\0" /* 861, 0x0019, 0x009e */
    "?\0" /* 862, 0x0019, 0x009f */
    "?\0" /* 863, 0x0019, 0x00a0 */
    "?\0" /* 864, 0x0019, 0x00a1 */
    "?\0" /* 865, 0x0019, 0x00a2 */
    "?\0" /* 866, 0x0019, 0x00a3 */
    "?\0" /* 867, 0x0019, 0x00a4 */
    "?\0" /* 868, 0x0019, 0x00a5 */
    "?\0" /* 869, 0x0019, 0x00a6 */
    "?\0" /* 870, 0x0019, 0x00a7 */
    "?\0" /* 871, 0x0019, 0x00a8 */
    "?\0" /* 872, 0x0019, 0x00a9 */
    "?\0" /* 873, 0x0019, 0x00aa */
    "?\0" /* 874, 0x0019, 0x00ab */
    "?\0" /* 875, 0x0019, 0x00ac */
    "?\0" /* 876, 0x0019, 0x00ad */
    "?\0" /* 877, 0x0019, 0x00ae */
    "?\0" /* 878, 0x0019, 0x00af */
    "?\0" /* 879, 0x0019, 0x00b0 */
    "?\0" /* 880, 0x0019, 0x00b1 */
    "?\0" /* 881, 0x0019, 0x00b2 */
    "?\0" /* 882, 0x0019, 0x00b3 */
    "?\0" /* 883, 0x0019, 0x00b4 */
    "?\0" /* 884, 0x0019, 0x00b5 */
    "User Data\0" /* 885, 0x0019, 0x00b6 */
    "User Data\0" /* 886, 0x0019, 0x00b7 */
    "User Data\0" /* 887, 0x0019, 0x00b8 */
    "User Data\0" /* 888, 0x0019, 0x00b9 */
    "User Data\0" /* 889, 0x0019, 0x00ba */
    "User Data\0" /* 890, 0x0019, 0x00bb */
    "User Data\0" /* 891, 0x0019, 0x00bc */
    "User Data\0" /* 892, 0x0019, 0x00bd */
    "Projection Angle\0" /* 893, 0x0019, 0x00be */
    "?\0" /* 894, 0x0019, 0x00c0 */
    "?\0" /* 895, 0x0019, 0x00c1 */
    "?\0" /* 896, 0x0019, 0x00c2 */
    "?\0" /* 897, 0x0019, 0x00c3 */
    "?\0" /* 898, 0x0019, 0x00c4 */
    "?\0" /* 899, 0x0019, 0x00c5 */
    "SAT Location H\0" /* 900, 0x0019, 0x00c6 */
    "SAT Location F\0" /* 901, 0x0019, 0x00c7 */
    "SAT Thickness R L\0" /* 902, 0x0019, 0x00c8 */
    "SAT Thickness A P\0" /* 903, 0x0019, 0x00c9 */
    "SAT Thickness H F\0" /* 904, 0x0019, 0x00ca */
    "?\0" /* 905, 0x0019, 0x00cb */
    "?\0" /* 906, 0x0019, 0x00cc */
    "Thickness Disclaimer\0" /* 907, 0x0019, 0x00cd */
    "Prescan Type\0" /* 908, 0x0019, 0x00ce */
    "Prescan Status\0" /* 909, 0x0019, 0x00cf */
    "Raw Data Type\0" /* 910, 0x0019, 0x00d0 */
    "Flow Sensitivity\0" /* 911, 0x0019, 0x00d1 */
    "?\0" /* 912, 0x0019, 0x00d2 */
    "?\0" /* 913, 0x0019, 0x00d3 */
    "?\0" /* 914, 0x0019, 0x00d4 */
    "?\0" /* 915, 0x0019, 0x00d5 */
    "?\0" /* 916, 0x0019, 0x00d6 */
    "?\0" /* 917, 0x0019, 0x00d7 */
    "?\0" /* 918, 0x0019, 0x00d8 */
    "?\0" /* 919, 0x0019, 0x00d9 */
    "?\0" /* 920, 0x0019, 0x00da */
    "Back Projector Coefficient\0" /* 921, 0x0019, 0x00db */
    "Primary Speed Correction Used\0" /* 922, 0x0019, 0x00dc */
    "Overrange Correction Used\0" /* 923, 0x0019, 0x00dd */
    "Dynamic Z Alpha Value\0" /* 924, 0x0019, 0x00de */
    "User Data\0" /* 925, 0x0019, 0x00df */
    "User Data\0" /* 926, 0x0019, 0x00e0 */
    "?\0" /* 927, 0x0019, 0x00e1 */
    "?\0" /* 928, 0x0019, 0x00e2 */
    "?\0" /* 929, 0x0019, 0x00e3 */
    "?\0" /* 930, 0x0019, 0x00e4 */
    "?\0" /* 931, 0x0019, 0x00e5 */
    "?\0" /* 932, 0x0019, 0x00e6 */
    "?\0" /* 933, 0x0019, 0x00e8 */
    "?\0" /* 934, 0x0019, 0x00e9 */
    "?\0" /* 935, 0x0019, 0x00eb */
    "?\0" /* 936, 0x0019, 0x00ec */
    "?\0" /* 937, 0x0019, 0x00f0 */
    "?\0" /* 938, 0x0019, 0x00f1 */
    "?\0" /* 939, 0x0019, 0x00f2 */
    "?\0" /* 940, 0x0019, 0x00f3 */
    "?\0" /* 941, 0x0019, 0x00f4 */
    "Transmission Gain\0" /* 942, 0x0019, 0x00f9 */
    "?\0" /* 943, 0x0019, 0x1015 */
    "Relationship Group Length\0" /* 944, 0x0020, 0x0000 */
    "Study Instance UID\0" /* 945, 0x0020, 0x000d */
    "Series Instance UID\0" /* 946, 0x0020, 0x000e */
    "Study ID\0" /* 947, 0x0020, 0x0010 */
    "Series Number\0" /* 948, 0x0020, 0x0011 */
    "Acquisition Number\0" /* 949, 0x0020, 0x0012 */
    "Instance (formerly Image) Number\0" /* 950, 0x0020, 0x0013 */
    "Isotope Number\0" /* 951, 0x0020, 0x0014 */
    "Phase Number\0" /* 952, 0x0020, 0x0015 */
    "Interval Number\0" /* 953, 0x0020, 0x0016 */
    "Time Slot Number\0" /* 954, 0x0020, 0x0017 */
    "Angle Number\0" /* 955, 0x0020, 0x0018 */
    "Patient Orientation\0" /* 956, 0x0020, 0x0020 */
    "Overlay Number\0" /* 957, 0x0020, 0x0022 */
    "Curve Number\0" /* 958, 0x0020, 0x0024 */
    "LUT Number\0" /* 959, 0x0020, 0x0026 */
    "Image Position\0" /* 960, 0x0020, 0x0030 */
    "Image Position (Patient)\0" /* 961, 0x0020, 0x0032 */
    "Image Orientation\0" /* 962, 0x0020, 0x0035 */
    "Image Orientation (Patient)\0" /* 963, 0x0020, 0x0037 */
    "Location\0" /* 964, 0x0020, 0x0050 */
    "Frame of Reference UID\0" /* 965, 0x0020, 0x0052 */
    "Laterality\0" /* 966, 0x0020, 0x0060 */
    "Image Laterality\0" /* 967, 0x0020, 0x0062 */
    "Image Geometry Type\0" /* 968, 0x0020, 0x0070 */
    "Masking Image\0" /* 969, 0x0020, 0x0080 */
    "Temporal Position Identifier\0" /* 970, 0x0020, 0x0100 */
    "Number of Temporal Positions\0" /* 971, 0x0020, 0x0105 */
    "Temporal Resolution\0" /* 972, 0x0020, 0x0110 */
    "Series in Study\0" /* 973, 0x0020, 0x1000 */
    "Acquisitions in Series\0" /* 974, 0x0020, 0x1001 */
    "Images in Acquisition\0" /* 975, 0x0020, 0x1002 */
    "Images in Series\0" /* 976, 0x0020, 0x1003 */
    "Acquisitions in Study\0" /* 977, 0x0020, 0x1004 */
    "Images in Study\0" /* 978, 0x0020, 0x1005 */
    "Reference\0" /* 979, 0x0020, 0x1020 */
    "Position Reference Indicator\0" /* 980, 0x0020, 0x1040 */
    "Slice Location\0" /* 981, 0x0020, 0x1041 */
    "Other Study Numbers\0" /* 982, 0x0020, 0x1070 */
    "Number of Patient Related Studies\0" /* 983, 0x0020, 0x1200 */
    "Number of Patient Related Series\0" /* 984, 0x0020, 0x1202 */
    "Number of Patient Related Images\0" /* 985, 0x0020, 0x1204 */
    "Number of Study Related Series\0" /* 986, 0x0020, 0x1206 */
    "Number of Study Related Series\0" /* 987, 0x0020, 0x1208 */
    "Source Image IDs\0" /* 988, 0x0020, 0x3100 */
    "Modifying Device ID\0" /* 989, 0x0020, 0x3401 */
    "Modified Image ID\0" /* 990, 0x0020, 0x3402 */
    "Modified Image Date\0" /* 991, 0x0020, 0x3403 */
    "Modifying Device Manufacturer\0" /* 992, 0x0020, 0x3404 */
    "Modified Image Time\0" /* 993, 0x0020, 0x3405 */
    "Modified Image Description\0" /* 994, 0x0020, 0x3406 */
    "Image Comments\0" /* 995, 0x0020, 0x4000 */
    "Original Image Identification\0" /* 996, 0x0020, 0x5000 */
    "Original Image Identification Nomenclature\0" /* 997, 0x0020, 0x5002 */
    "?\0" /* 998, 0x0021, 0x0000 */
    "?\0" /* 999, 0x0021, 0x0001 */
    "?\0" /* 1000, 0x0021, 0x0002 */
    "?\0" /* 1001, 0x0021, 0x0003 */
    "VOI Position\0" /* 1002, 0x0021, 0x0004 */
    "?\0" /* 1003, 0x0021, 0x0005 */
    "CSI Matrix Size Original\0" /* 1004, 0x0021, 0x0006 */
    "?\0" /* 1005, 0x0021, 0x0007 */
    "Spatial Grid Shift\0" /* 1006, 0x0021, 0x0008 */
    "Signal Limits Minimum\0" /* 1007, 0x0021, 0x0009 */
    "?\0" /* 1008, 0x0021, 0x0010 */
    "?\0" /* 1009, 0x0021, 0x0011 */
    "?\0" /* 1010, 0x0021, 0x0012 */
    "?\0" /* 1011, 0x0021, 0x0013 */
    "?\0" /* 1012, 0x0021, 0x0014 */
    "?\0" /* 1013, 0x0021, 0x0015 */
    "?\0" /* 1014, 0x0021, 0x0016 */
    "EPI Operation Mode Flag\0" /* 1015, 0x0021, 0x0017 */
    "?\0" /* 1016, 0x0021, 0x0018 */
    "?\0" /* 1017, 0x0021, 0x0019 */
    "?\0" /* 1018, 0x0021, 0x0020 */
    "?\0" /* 1019, 0x0021, 0x0021 */
    "?\0" /* 1020, 0x0021, 0x0022 */
    "?\0" /* 1021, 0x0021, 0x0024 */
    "?\0" /* 1022, 0x0021, 0x0025 */
    "Image Pixel Offset\0" /* 1023, 0x0021, 0x0026 */
    "?\0" /* 1024, 0x0021, 0x0030 */
    "?\0" /* 1025, 0x0021, 0x0031 */
    "?\0" /* 1026, 0x0021, 0x0032 */
    "?\0" /* 1027, 0x0021, 0x0034 */
    "Series From Which Prescribed\0" /* 1028, 0x0021, 0x0035 */
    "?\0" /* 1029, 0x0021, 0x0036 */
    "Screen Format\0" /* 1030, 0x0021, 0x0037 */
    "Slab Thickness\0" /* 1031, 0x0021, 0x0039 */
    "?\0" /* 1032, 0x0021, 0x0040 */
    "?\0" /* 1033, 0x0021, 0x0041 */
    "?\0" /* 1034, 0x0021, 0x0042 */
    "?\0" /* 1035, 0x0021, 0x0043 */
    "?\0" /* 1036, 0x0021, 0x0044 */
    "?\0" /* 1037, 0x0021, 0x0045 */
    "?\0" /* 1038, 0x0021, 0x0046 */
    "?\0" /* 1039, 0x0021, 0x0047 */
    "?\0" /* 1040, 0x0021, 0x0048 */
    "?\0" /* 1041, 0x0021, 0x0049 */
    "?\0" /* 1042, 0x0021, 0x004a */
    "?\0" /* 1043, 0x0021, 0x004e */
    "?\0" /* 1044, 0x0021, 0x004f */
    "?\0" /* 1045, 0x0021, 0x0050 */
    "?\0" /* 1046, 0x0021, 0x0051 */
    "?\0" /* 1047, 0x0021, 0x0052 */
    "?\0" /* 1048, 0x0021, 0x0053 */
    "?\0" /* 1049, 0x0021, 0x0054 */
    "?\0" /* 1050, 0x0021, 0x0055 */
    "?\0" /* 1051, 0x0021, 0x0056 */
    "?\0" /* 1052, 0x0021, 0x0057 */
    "?\0" /* 1053, 0x0021, 0x0058 */
    "?\0" /* 1054, 0x0021, 0x0059 */
    "Integer Slop\0" /* 1055, 0x0021, 0x005a */
    "Float Slop\0" /* 1056, 0x0021, 0x005b */
    "Float Slop\0" /* 1057, 0x0021, 0x005c */
    "Float Slop\0" /* 1058, 0x0021, 0x005d */
    "Float Slop\0" /* 1059, 0x0021, 0x005e */
    "Float Slop\0" /* 1060, 0x0021, 0x005f */
    "?\0" /* 1061, 0x0021, 0x0060 */
    "Image Normal\0" /* 1062, 0x0021, 0x0061 */
    "Reference Type Code\0" /* 1063, 0x0021, 0x0062 */
    "Image Distance\0" /* 1064, 0x0021, 0x0063 */
    "Image Positioning History Mask\0" /* 1065, 0x0021, 0x0065 */
    "Image Row\0" /* 1066, 0x0021, 0x006a */
    "Image Column\0" /* 1067, 0x0021, 0x006b */
    "?\0" /* 1068, 0x0021, 0x0070 */
    "?\0" /* 1069, 0x0021, 0x0071 */
    "?\0" /* 1070, 0x0021, 0x0072 */
    "Second Repetition Time\0" /* 1071, 0x0021, 0x0073 */
    "Light Brightness\0" /* 1072, 0x0021, 0x0075 */
    "Light Contrast\0" /* 1073, 0x0021, 0x0076 */
    "Overlay Threshold\0" /* 1074, 0x0021, 0x007a */
    "Surface Threshold\0" /* 1075, 0x0021, 0x007b */
    "Grey Scale Threshold\0" /* 1076, 0x0021, 0x007c */
    "?\0" /* 1077, 0x0021, 0x0080 */
    "Auto Window Level Alpha\0" /* 1078, 0x0021, 0x0081 */
    "?\0" /* 1079, 0x0021, 0x0082 */
    "Auto Window Level Window\0" /* 1080, 0x0021, 0x0083 */
    "Auto Window Level Level\0" /* 1081, 0x0021, 0x0084 */
    "?\0" /* 1082, 0x0021, 0x0090 */
    "?\0" /* 1083, 0x0021, 0x0091 */
    "?\0" /* 1084, 0x0021, 0x0092 */
    "?\0" /* 1085, 0x0021, 0x0093 */
    "EPI Change Value of X Component\0" /* 1086, 0x0021, 0x0094 */
    "EPI Change Value of Y Component\0" /* 1087, 0x0021, 0x0095 */
    "EPI Change Value of Z Component\0" /* 1088, 0x0021, 0x0096 */
    "?\0" /* 1089, 0x0021, 0x00a0 */
    "?\0" /* 1090, 0x0021, 0x00a1 */
    "?\0" /* 1091, 0x0021, 0x00a2 */
    "?\0" /* 1092, 0x0021, 0x00a3 */
    "?\0" /* 1093, 0x0021, 0x00a4 */
    "?\0" /* 1094, 0x0021, 0x00a7 */
    "?\0" /* 1095, 0x0021, 0x00b0 */
    "?\0" /* 1096, 0x0021, 0x00c0 */
    "?\0" /* 1097, 0x0023, 0x0000 */
    "Number Of Series In Study\0" /* 1098, 0x0023, 0x0001 */
    "Number Of Unarchived Series\0" /* 1099, 0x0023, 0x0002 */
    "?\0" /* 1100, 0x0023, 0x0010 */
    "?\0" /* 1101, 0x0023, 0x0020 */
    "?\0" /* 1102, 0x0023, 0x0030 */
    "?\0" /* 1103, 0x0023, 0x0040 */
    "?\0" /* 1104, 0x0023, 0x0050 */
    "?\0" /* 1105, 0x0023, 0x0060 */
    "?\0" /* 1106, 0x0023, 0x0070 */
    "Number Of Updates To Info\0" /* 1107, 0x0023, 0x0074 */
    "Indicates If Study Has Complete Info\0" /* 1108, 0x0023, 0x007d */
    "?\0" /* 1109, 0x0023, 0x0080 */
    "?\0" /* 1110, 0x0023, 0x0090 */
    "?\0" /* 1111, 0x0023, 0x00ff */
    "Group Length\0" /* 1112, 0x0025, 0x0000 */
    "Last Pulse Sequence Used\0" /* 1113, 0x0025, 0x0006 */
    "Images In Series\0" /* 1114, 0x0025, 0x0007 */
    "Landmark Counter\0" /* 1115, 0x0025, 0x0010 */
    "Number Of Acquisitions\0" /* 1116, 0x0025, 0x0011 */
    "Indicates Number Of Updates To Info\0" /* 1117, 0x0025, 0x0014 */
    "Series Complete Flag\0" /* 1118, 0x0025, 0x0017 */
    "Number Of Images Archived\0" /* 1119, 0x0025, 0x0018 */
    "Last Image Number Used\0" /* 1120, 0x0025, 0x0019 */
    "Primary Receiver Suite And Host\0" /* 1121, 0x0025, 0x001a */
    "?\0" /* 1122, 0x0027, 0x0000 */
    "Image Archive Flag\0" /* 1123, 0x0027, 0x0006 */
    "Scout Type\0" /* 1124, 0x0027, 0x0010 */
    "?\0" /* 1125, 0x0027, 0x0011 */
    "?\0" /* 1126, 0x0027, 0x0012 */
    "?\0" /* 1127, 0x0027, 0x0013 */
    "?\0" /* 1128, 0x0027, 0x0014 */
    "?\0" /* 1129, 0x0027, 0x0015 */
    "?\0" /* 1130, 0x0027, 0x0016 */
    "Vma Mamp\0" /* 1131, 0x0027, 0x001c */
    "Vma Phase\0" /* 1132, 0x0027, 0x001d */
    "Vma Mod\0" /* 1133, 0x0027, 0x001e */
    "Vma Clip\0" /* 1134, 0x0027, 0x001f */
    "Smart Scan On Off Flag\0" /* 1135, 0x0027, 0x0020 */
    "Foreign Image Revision\0" /* 1136, 0x0027, 0x0030 */
    "Imaging Mode\0" /* 1137, 0x0027, 0x0031 */
    "Pulse Sequence\0" /* 1138, 0x0027, 0x0032 */
    "Imaging Options\0" /* 1139, 0x0027, 0x0033 */
    "Plane Type\0" /* 1140, 0x0027, 0x0035 */
    "Oblique Plane\0" /* 1141, 0x0027, 0x0036 */
    "RAS Letter Of Image Location\0" /* 1142, 0x0027, 0x0040 */
    "Image Location\0" /* 1143, 0x0027, 0x0041 */
    "Center R Coord Of Plane Image\0" /* 1144, 0x0027, 0x0042 */
    "Center A Coord Of Plane Image\0" /* 1145, 0x0027, 0x0043 */
    "Center S Coord Of Plane Image\0" /* 1146, 0x0027, 0x0044 */
    "Normal R Coord\0" /* 1147, 0x0027, 0x0045 */
    "Normal A Coord\0" /* 1148, 0x0027, 0x0046 */
    "Normal S Coord\0" /* 1149, 0x0027, 0x0047 */
    "R Coord Of Top Right Corner\0" /* 1150, 0x0027, 0x0048 */
    "A Coord Of Top Right Corner\0" /* 1151, 0x0027, 0x0049 */
    "S Coord Of Top Right Corner\0" /* 1152, 0x0027, 0x004a */
    "R Coord Of Bottom Right Corner\0" /* 1153, 0x0027, 0x004b */
    "A Coord Of Bottom Right Corner\0" /* 1154, 0x0027, 0x004c */
    "S Coord Of Bottom Right Corner\0" /* 1155, 0x0027, 0x004d */
    "Table Start Location\0" /* 1156, 0x0027, 0x0050 */
    "Table End Location\0" /* 1157, 0x0027, 0x0051 */
    "RAS Letter For Side Of Image\0" /* 1158, 0x0027, 0x0052 */
    "RAS Letter For Anterior Posterior\0" /* 1159, 0x0027, 0x0053 */
    "RAS Letter For Scout Start Loc\0" /* 1160, 0x0027, 0x0054 */
    "RAS Letter For Scout End Loc\0" /* 1161, 0x0027, 0x0055 */
    "Image Dimension X\0" /* 1162, 0x0027, 0x0060 */
    "Image Dimension Y\0" /* 1163, 0x0027, 0x0061 */
    "Number Of Excitations\0" /* 1164, 0x0027, 0x0062 */
    "Image Presentation Group Length\0" /* 1165, 0x0028, 0x0000 */
    "Samples per Pixel\0" /* 1166, 0x0028, 0x0002 */
    "Photometric Interpretation\0" /* 1167, 0x0028, 0x0004 */
    "Image Dimensions\0" /* 1168, 0x0028, 0x0005 */
    "Planar Configuration\0" /* 1169, 0x0028, 0x0006 */
    "Number of Frames\0" /* 1170, 0x0028, 0x0008 */
    "Frame Increment Pointer\0" /* 1171, 0x0028, 0x0009 */
    "Rows\0" /* 1172, 0x0028, 0x0010 */
    "Columns\0" /* 1173, 0x0028, 0x0011 */
    "Planes\0" /* 1174, 0x0028, 0x0012 */
    "Ultrasound Color Data Present\0" /* 1175, 0x0028, 0x0014 */
    "Pixel Spacing\0" /* 1176, 0x0028, 0x0030 */
    "Zoom Factor\0" /* 1177, 0x0028, 0x0031 */
    "Zoom Center\0" /* 1178, 0x0028, 0x0032 */
    "Pixel Aspect Ratio\0" /* 1179, 0x0028, 0x0034 */
    "Image Format\0" /* 1180, 0x0028, 0x0040 */
    "Manipulated Image\0" /* 1181, 0x0028, 0x0050 */
    "Corrected Image\0" /* 1182, 0x0028, 0x0051 */
    "Compression Recognition Code\0" /* 1183, 0x0028, 0x005f */
    "Compression Code\0" /* 1184, 0x0028, 0x0060 */
    "Compression Originator\0" /* 1185, 0x0028, 0x0061 */
    "Compression Label\0" /* 1186, 0x0028, 0x0062 */
    "Compression Description\0" /* 1187, 0x0028, 0x0063 */
    "Compression Sequence\0" /* 1188, 0x0028, 0x0065 */
    "Compression Step Pointers\0" /* 1189, 0x0028, 0x0066 */
    "Repeat Interval\0" /* 1190, 0x0028, 0x0068 */
    "Bits Grouped\0" /* 1191, 0x0028, 0x0069 */
    "Perimeter Table\0" /* 1192, 0x0028, 0x0070 */
    "Perimeter Value\0" /* 1193, 0x0028, 0x0071 */
    "Predictor Rows\0" /* 1194, 0x0028, 0x0080 */
    "Predictor Columns\0" /* 1195, 0x0028, 0x0081 */
    "Predictor Constants\0" /* 1196, 0x0028, 0x0082 */
    "Blocked Pixels\0" /* 1197, 0x0028, 0x0090 */
    "Block Rows\0" /* 1198, 0x0028, 0x0091 */
    "Block Columns\0" /* 1199, 0x0028, 0x0092 */
    "Row Overlap\0" /* 1200, 0x0028, 0x0093 */
    "Column Overlap\0" /* 1201, 0x0028, 0x0094 */
    "Bits Allocated\0" /* 1202, 0x0028, 0x0100 */
    "Bits Stored\0" /* 1203, 0x0028, 0x0101 */
    "High Bit\0" /* 1204, 0x0028, 0x0102 */
    "Pixel Representation\0" /* 1205, 0x0028, 0x0103 */
    "Smallest Valid Pixel Value\0" /* 1206, 0x0028, 0x0104 */
    "Largest Valid Pixel Value\0" /* 1207, 0x0028, 0x0105 */
    "Smallest Image Pixel Value\0" /* 1208, 0x0028, 0x0106 */
    "Largest Image Pixel Value\0" /* 1209, 0x0028, 0x0107 */
    "Smallest Pixel Value in Series\0" /* 1210, 0x0028, 0x0108 */
    "Largest Pixel Value in Series\0" /* 1211, 0x0028, 0x0109 */
    "Smallest Pixel Value in Plane\0" /* 1212, 0x0028, 0x0110 */
    "Largest Pixel Value in Plane\0" /* 1213, 0x0028, 0x0111 */
    "Pixel Padding Value\0" /* 1214, 0x0028, 0x0120 */
    "Pixel Padding Range Limit\0" /* 1215, 0x0028, 0x0121 */
    "Image Location\0" /* 1216, 0x0028, 0x0200 */
    "Quality Control Image\0" /* 1217, 0x0028, 0x0300 */
    "Burned In Annotation\0" /* 1218, 0x0028, 0x0301 */
    "?\0" /* 1219, 0x0028, 0x0400 */
    "?\0" /* 1220, 0x0028, 0x0401 */
    "?\0" /* 1221, 0x0028, 0x0402 */
    "?\0" /* 1222, 0x0028, 0x0403 */
    "Details of Coefficients\0" /* 1223, 0x0028, 0x0404 */
    "DCT Label\0" /* 1224, 0x0028, 0x0700 */
    "Data Block Description\0" /* 1225, 0x0028, 0x0701 */
    "Data Block\0" /* 1226, 0x0028, 0x0702 */
    "Normalization Factor Format\0" /* 1227, 0x0028, 0x0710 */
    "Zonal Map Number Format\0" /* 1228, 0x0028, 0x0720 */
    "Zonal Map Location\0" /* 1229, 0x0028, 0x0721 */
    "Zonal Map Format\0" /* 1230, 0x0028, 0x0722 */
    "Adaptive Map Format\0" /* 1231, 0x0028, 0x0730 */
    "Code Number Format\0" /* 1232, 0x0028, 0x0740 */
    "Code Label\0" /* 1233, 0x0028, 0x0800 */
    "Number of Tables\0" /* 1234, 0x0028, 0x0802 */
    "Code Table Location\0" /* 1235, 0x0028, 0x0803 */
    "Bits For Code Word\0" /* 1236, 0x0028, 0x0804 */
    "Image Data Location\0" /* 1237, 0x0028, 0x0808 */
    "Pixel Intensity Relationship\0" /* 1238, 0x0028, 0x1040 */
    "Pixel Intensity Relationship Sign\0" /* 1239, 0x0028, 0x1041 */
    "Window Center\0" /* 1240, 0x0028, 0x1050 */
    "Window Width\0" /* 1241, 0x0028, 0x1051 */
    "Rescale Intercept\0" /* 1242, 0x0028, 0x1052 */
    "Rescale Slope\0" /* 1243, 0x0028, 0x1053 */
    "Rescale Type\0" /* 1244, 0x0028, 0x1054 */
    "Window Center & Width Explanation\0" /* 1245, 0x0028, 0x1055 */
    "Gray Scale\0" /* 1246, 0x0028, 0x1080 */
    "Recommended Viewing Mode\0" /* 1247, 0x0028, 0x1090 */
    "Gray Lookup Table Descriptor\0" /* 1248, 0x0028, 0x1100 */
    "Red Palette Color Lookup Table Descriptor\0" /* 1249, 0x0028, 0x1101 */
    "Green Palette Color Lookup Table Descriptor\0" /* 1250, 0x0028, 0x1102 */
    "Blue Palette Color Lookup Table Descriptor\0" /* 1251, 0x0028, 0x1103 */
    "Large Red Palette Color Lookup Table Descriptor\0" /* 1252, 0x0028, 0x1111 */
    "Large Green Palette Color Lookup Table Descriptor\0" /* 1253, 0x0028, 0x1112 */
    "Large Blue Palette Color Lookup Table Descriptor\0" /* 1254, 0x0028, 0x1113 */
    "Palette Color Lookup Table UID\0" /* 1255, 0x0028, 0x1199 */
    "Gray Lookup Table Data\0" /* 1256, 0x0028, 0x1200 */
    "Red Palette Color Lookup Table Data\0" /* 1257, 0x0028, 0x1201 */
    "Green Palette Color Lookup Table Data\0" /* 1258, 0x0028, 0x1202 */
    "Blue Palette Color Lookup Table Data\0" /* 1259, 0x0028, 0x1203 */
    "Large Red Palette Color Lookup Table Data\0" /* 1260, 0x0028, 0x1211 */
    "Large Green Palette Color Lookup Table Data\0" /* 1261, 0x0028, 0x1212 */
    "Large Blue Palette Color Lookup Table Data\0" /* 1262, 0x0028, 0x1213 */
    "Large Palette Color Lookup Table UID\0" /* 1263, 0x0028, 0x1214 */
    "Segmented Red Palette Color Lookup Table Data\0" /* 1264, 0x0028, 0x1221 */
    "Segmented Green Palette Color Lookup Table Data\0" /* 1265, 0x0028, 0x1222 */
    "Segmented Blue Palette Color Lookup Table Data\0" /* 1266, 0x0028, 0x1223 */
    "Implant Present\0" /* 1267, 0x0028, 0x1300 */
    "Lossy Image Compression\0" /* 1268, 0x0028, 0x2110 */
    "Lossy Image Compression Ratio\0" /* 1269, 0x0028, 0x2112 */
    "Modality LUT Sequence\0" /* 1270, 0x0028, 0x3000 */
    "LUT Descriptor\0" /* 1271, 0x0028, 0x3002 */
    "LUT Explanation\0" /* 1272, 0x0028, 0x3003 */
    "Modality LUT Type\0" /* 1273, 0x0028, 0x3004 */
    "LUT Data\0" /* 1274, 0x0028, 0x3006 */
    "VOI LUT Sequence\0" /* 1275, 0x0028, 0x3010 */
    "Image Presentation Comments\0" /* 1276, 0x0028, 0x4000 */
    "Biplane Acquisition Sequence\0" /* 1277, 0x0028, 0x5000 */
    "Representative Frame Number\0" /* 1278, 0x0028, 0x6010 */
    "Frame Numbers of Interest\0" /* 1279, 0x0028, 0x6020 */
    "Frame of Interest Description\0" /* 1280, 0x0028, 0x6022 */
    "Mask Pointer\0" /* 1281, 0x0028, 0x6030 */
    "R Wave Pointer\0" /* 1282, 0x0028, 0x6040 */
    "Mask Subtraction Sequence\0" /* 1283, 0x0028, 0x6100 */
    "Mask Operation\0" /* 1284, 0x0028, 0x6101 */
    "Applicable Frame Range\0" /* 1285, 0x0028, 0x6102 */
    "Mask Frame Numbers\0" /* 1286, 0x0028, 0x6110 */
    "Contrast Frame Averaging\0" /* 1287, 0x0028, 0x6112 */
    "Mask Sub-Pixel Shift\0" /* 1288, 0x0028, 0x6114 */
    "TID Offset\0" /* 1289, 0x0028, 0x6120 */
    "Mask Operation Explanation\0" /* 1290, 0x0028, 0x6190 */
    "?\0" /* 1291, 0x0029, 0x0000 */
    "?\0" /* 1292, 0x0029, 0x0001 */
    "?\0" /* 1293, 0x0029, 0x0002 */
    "?\0" /* 1294, 0x0029, 0x0003 */
    "?\0" /* 1295, 0x0029, 0x0004 */
    "?\0" /* 1296, 0x0029, 0x0005 */
    "?\0" /* 1297, 0x0029, 0x0006 */
    "Lower Range Of Pixels\0" /* 1298, 0x0029, 0x0007 */
    "Lower Range Of Pixels\0" /* 1299, 0x0029, 0x0008 */
    "Lower Range Of Pixels\0" /* 1300, 0x0029, 0x0009 */
    "Lower Range Of Pixels\0" /* 1301, 0x0029, 0x000a */
    "?\0" /* 1302, 0x0029, 0x000c */
    "Zoom Enable Status\0" /* 1303, 0x0029, 0x000e */
    "Zoom Select Status\0" /* 1304, 0x0029, 0x000f */
    "?\0" /* 1305, 0x0029, 0x0010 */
    "?\0" /* 1306, 0x0029, 0x0011 */
    "?\0" /* 1307, 0x0029, 0x0013 */
    "?\0" /* 1308, 0x0029, 0x0015 */
    "Lower Range Of Pixels\0" /* 1309, 0x0029, 0x0016 */
    "Lower Range Of Pixels\0" /* 1310, 0x0029, 0x0017 */
    "Upper Range Of Pixels\0" /* 1311, 0x0029, 0x0018 */
    "Length Of Total Info In Bytes\0" /* 1312, 0x0029, 0x001a */
    "?\0" /* 1313, 0x0029, 0x001e */
    "?\0" /* 1314, 0x0029, 0x001f */
    "?\0" /* 1315, 0x0029, 0x0020 */
    "Pixel Quality Value\0" /* 1316, 0x0029, 0x0022 */
    "Processed Pixel Data Quality\0" /* 1317, 0x0029, 0x0025 */
    "Version Of Info Structure\0" /* 1318, 0x0029, 0x0026 */
    "?\0" /* 1319, 0x0029, 0x0030 */
    "?\0" /* 1320, 0x0029, 0x0031 */
    "?\0" /* 1321, 0x0029, 0x0032 */
    "?\0" /* 1322, 0x0029, 0x0033 */
    "?\0" /* 1323, 0x0029, 0x0034 */
    "Advantage Comp Underflow\0" /* 1324, 0x0029, 0x0035 */
    "?\0" /* 1325, 0x0029, 0x0038 */
    "?\0" /* 1326, 0x0029, 0x0040 */
    "Magnifying Glass Rectangle\0" /* 1327, 0x0029, 0x0041 */
    "Magnifying Glass Factor\0" /* 1328, 0x0029, 0x0043 */
    "Magnifying Glass Function\0" /* 1329, 0x0029, 0x0044 */
    "Magnifying Glass Enable Status\0" /* 1330, 0x0029, 0x004e */
    "Magnifying Glass Select Status\0" /* 1331, 0x0029, 0x004f */
    "?\0" /* 1332, 0x0029, 0x0050 */
    "Exposure Code\0" /* 1333, 0x0029, 0x0051 */
    "Sort Code\0" /* 1334, 0x0029, 0x0052 */
    "?\0" /* 1335, 0x0029, 0x0053 */
    "?\0" /* 1336, 0x0029, 0x0060 */
    "?\0" /* 1337, 0x0029, 0x0061 */
    "?\0" /* 1338, 0x0029, 0x0067 */
    "?\0" /* 1339, 0x0029, 0x0070 */
    "?\0" /* 1340, 0x0029, 0x0071 */
    "?\0" /* 1341, 0x0029, 0x0072 */
    "Window Select Status\0" /* 1342, 0x0029, 0x0077 */
    "ECG Display Printing ID\0" /* 1343, 0x0029, 0x0078 */
    "ECG Display Printing\0" /* 1344, 0x0029, 0x0079 */
    "ECG Display Printing Enable Status\0" /* 1345, 0x0029, 0x007e */
    "ECG Display Printing Select Status\0" /* 1346, 0x0029, 0x007f */
    "?\0" /* 1347, 0x0029, 0x0080 */
    "?\0" /* 1348, 0x0029, 0x0081 */
    "View Zoom\0" /* 1349, 0x0029, 0x0082 */
    "View Transform\0" /* 1350, 0x0029, 0x0083 */
    "Physiological Display Enable Status\0" /* 1351, 0x0029, 0x008e */
    "Physiological Display Select Status\0" /* 1352, 0x0029, 0x008f */
    "?\0" /* 1353, 0x0029, 0x0090 */
    "Shutter Type\0" /* 1354, 0x0029, 0x0099 */
    "Rows of Rectangular Shutter\0" /* 1355, 0x0029, 0x00a0 */
    "Columns of Rectangular Shutter\0" /* 1356, 0x0029, 0x00a1 */
    "Origin of Rectangular Shutter\0" /* 1357, 0x0029, 0x00a2 */
    "Radius of Circular Shutter\0" /* 1358, 0x0029, 0x00b0 */
    "Origin of Circular Shutter\0" /* 1359, 0x0029, 0x00b2 */
    "Functional Shutter ID\0" /* 1360, 0x0029, 0x00c0 */
    "?\0" /* 1361, 0x0029, 0x00c1 */
    "Scan Resolution\0" /* 1362, 0x0029, 0x00c3 */
    "Field of View\0" /* 1363, 0x0029, 0x00c4 */
    "Field Of Shutter Rectangle\0" /* 1364, 0x0029, 0x00c5 */
    "Shutter Enable Status\0" /* 1365, 0x0029, 0x00ce */
    "Shutter Select Status\0" /* 1366, 0x0029, 0x00cf */
    "?\0" /* 1367, 0x0029, 0x00d0 */
    "?\0" /* 1368, 0x0029, 0x00d1 */
    "Slice Thickness\0" /* 1369, 0x0029, 0x00d5 */
    "Request UID\0" /* 1370, 0x0031, 0x0010 */
    "Examination Reason\0" /* 1371, 0x0031, 0x0012 */
    "Requested Date\0" /* 1372, 0x0031, 0x0030 */
    "Worklist Request Start Time\0" /* 1373, 0x0031, 0x0032 */
    "Worklist Request End Time\0" /* 1374, 0x0031, 0x0033 */
    "Requesting Physician\0" /* 1375, 0x0031, 0x0045 */
    "Requested Time\0" /* 1376, 0x0031, 0x004a */
    "Requested Physician\0" /* 1377, 0x0031, 0x0050 */
    "Requested Location\0" /* 1378, 0x0031, 0x0080 */
    "Study Group Length\0" /* 1379, 0x0032, 0x0000 */
    "Study Status ID\0" /* 1380, 0x0032, 0x000a */
    "Study Priority ID\0" /* 1381, 0x0032, 0x000c */
    "Study ID Issuer\0" /* 1382, 0x0032, 0x0012 */
    "Study Verified Date\0" /* 1383, 0x0032, 0x0032 */
    "Study Verified Time\0" /* 1384, 0x0032, 0x0033 */
    "Study Read Date\0" /* 1385, 0x0032, 0x0034 */
    "Study Read Time\0" /* 1386, 0x0032, 0x0035 */
    "Scheduled Study Start Date\0" /* 1387, 0x0032, 0x1000 */
    "Scheduled Study Start Time\0" /* 1388, 0x0032, 0x1001 */
    "Scheduled Study Stop Date\0" /* 1389, 0x0032, 0x1010 */
    "Scheduled Study Stop Time\0" /* 1390, 0x0032, 0x1011 */
    "Scheduled Study Location\0" /* 1391, 0x0032, 0x1020 */
    "Scheduled Study Location AE Title(s)\0" /* 1392, 0x0032, 0x1021 */
    "Reason for Study\0" /* 1393, 0x0032, 0x1030 */
    "Requesting Physician\0" /* 1394, 0x0032, 0x1032 */
    "Requesting Service\0" /* 1395, 0x0032, 0x1033 */
    "Study Arrival Date\0" /* 1396, 0x0032, 0x1040 */
    "Study Arrival Time\0" /* 1397, 0x0032, 0x1041 */
    "Study Completion Date\0" /* 1398, 0x0032, 0x1050 */
    "Study Completion Time\0" /* 1399, 0x0032, 0x1051 */
    "Study Component Status ID\0" /* 1400, 0x0032, 0x1055 */
    "Requested Procedure Description\0" /* 1401, 0x0032, 0x1060 */
    "Requested Procedure Code Sequence\0" /* 1402, 0x0032, 0x1064 */
    "Requested Contrast Agent\0" /* 1403, 0x0032, 0x1070 */
    "Study Comments\0" /* 1404, 0x0032, 0x4000 */
    "?\0" /* 1405, 0x0033, 0x0001 */
    "?\0" /* 1406, 0x0033, 0x0002 */
    "?\0" /* 1407, 0x0033, 0x0005 */
    "?\0" /* 1408, 0x0033, 0x0006 */
    "Patient Study UID\0" /* 1409, 0x0033, 0x0010 */
    "ReferringDepartment\0" /* 1410, 0x0037, 0x0010 */
    "ScreenNumber\0" /* 1411, 0x0037, 0x0020 */
    "LeftOrientation\0" /* 1412, 0x0037, 0x0040 */
    "RightOrientation\0" /* 1413, 0x0037, 0x0042 */
    "Inversion\0" /* 1414, 0x0037, 0x0050 */
    "DSA\0" /* 1415, 0x0037, 0x0060 */
    "Visit Group Length\0" /* 1416, 0x0038, 0x0000 */
    "Referenced Patient Alias Sequence\0" /* 1417, 0x0038, 0x0004 */
    "Visit Status ID\0" /* 1418, 0x0038, 0x0008 */
    "Admission ID\0" /* 1419, 0x0038, 0x0010 */
    "Issuer of Admission ID\0" /* 1420, 0x0038, 0x0011 */
    "Route of Admissions\0" /* 1421, 0x0038, 0x0016 */
    "Scheduled Admission Date\0" /* 1422, 0x0038, 0x001a */
    "Scheduled Admission Time\0" /* 1423, 0x0038, 0x001b */
    "Scheduled Discharge Date\0" /* 1424, 0x0038, 0x001c */
    "Scheduled Discharge Time\0" /* 1425, 0x0038, 0x001d */
    "Scheduled Patient Institution Residence\0" /* 1426, 0x0038, 0x001e */
    "Admitting Date\0" /* 1427, 0x0038, 0x0020 */
    "Admitting Time\0" /* 1428, 0x0038, 0x0021 */
    "Discharge Date\0" /* 1429, 0x0038, 0x0030 */
    "Discharge Time\0" /* 1430, 0x0038, 0x0032 */
    "Discharge Diagnosis Description\0" /* 1431, 0x0038, 0x0040 */
    "Discharge Diagnosis Code Sequence\0" /* 1432, 0x0038, 0x0044 */
    "Special Needs\0" /* 1433, 0x0038, 0x0050 */
    "Current Patient Location\0" /* 1434, 0x0038, 0x0300 */
    "Patient's Institution Residence\0" /* 1435, 0x0038, 0x0400 */
    "Patient State\0" /* 1436, 0x0038, 0x0500 */
    "Visit Comments\0" /* 1437, 0x0038, 0x4000 */
    "Private Entity Number\0" /* 1438, 0x0039, 0x0080 */
    "Private Entity Date\0" /* 1439, 0x0039, 0x0085 */
    "Private Entity Time\0" /* 1440, 0x0039, 0x0090 */
    "Private Entity Launch Command\0" /* 1441, 0x0039, 0x0095 */
    "Private Entity Type\0" /* 1442, 0x0039, 0x00aa */
    "Waveform Sequence\0" /* 1443, 0x003a, 0x0002 */
    "Waveform Number of Channels\0" /* 1444, 0x003a, 0x0005 */
    "Waveform Number of Samples\0" /* 1445, 0x003a, 0x0010 */
    "Sampling Frequency\0" /* 1446, 0x003a, 0x001a */
    "Group Label\0" /* 1447, 0x003a, 0x0020 */
    "Waveform Sample Value Representation\0" /* 1448, 0x003a, 0x0103 */
    "Waveform Padding Value\0" /* 1449, 0x003a, 0x0122 */
    "Channel Definition\0" /* 1450, 0x003a, 0x0200 */
    "Waveform Channel Number\0" /* 1451, 0x003a, 0x0202 */
    "Channel Label\0" /* 1452, 0x003a, 0x0203 */
    "Channel Status\0" /* 1453, 0x003a, 0x0205 */
    "Channel Source\0" /* 1454, 0x003a, 0x0208 */
    "Channel Source Modifiers\0" /* 1455, 0x003a, 0x0209 */
    "Differential Channel Source\0" /* 1456, 0x003a, 0x020a */
    "Differential Channel Source Modifiers\0" /* 1457, 0x003a, 0x020b */
    "Channel Sensitivity\0" /* 1458, 0x003a, 0x0210 */
    "Channel Sensitivity Units\0" /* 1459, 0x003a, 0x0211 */
    "Channel Sensitivity Correction Factor\0" /* 1460, 0x003a, 0x0212 */
    "Channel Baseline\0" /* 1461, 0x003a, 0x0213 */
    "Channel Time Skew\0" /* 1462, 0x003a, 0x0214 */
    "Channel Sample Skew\0" /* 1463, 0x003a, 0x0215 */
    "Channel Minimum Value\0" /* 1464, 0x003a, 0x0216 */
    "Channel Maximum Value\0" /* 1465, 0x003a, 0x0217 */
    "Channel Offset\0" /* 1466, 0x003a, 0x0218 */
    "Bits Per Sample\0" /* 1467, 0x003a, 0x021a */
    "Filter Low Frequency\0" /* 1468, 0x003a, 0x0220 */
    "Filter High Frequency\0" /* 1469, 0x003a, 0x0221 */
    "Notch Filter Frequency\0" /* 1470, 0x003a, 0x0222 */
    "Notch Filter Bandwidth\0" /* 1471, 0x003a, 0x0223 */
    "Waveform Data\0" /* 1472, 0x003a, 0x1000 */
    "Scheduled Station AE Title\0" /* 1473, 0x0040, 0x0001 */
    "Scheduled Procedure Step Start Date\0" /* 1474, 0x0040, 0x0002 */
    "Scheduled Procedure Step Start Time\0" /* 1475, 0x0040, 0x0003 */
    "Scheduled Procedure Step End Date\0" /* 1476, 0x0040, 0x0004 */
    "Scheduled Procedure Step End Time\0" /* 1477, 0x0040, 0x0005 */
    "Scheduled Performing Physician Name\0" /* 1478, 0x0040, 0x0006 */
    "Scheduled Procedure Step Description\0" /* 1479, 0x0040, 0x0007 */
    "Scheduled Action Item Code Sequence\0" /* 1480, 0x0040, 0x0008 */
    "Scheduled Procedure Step ID\0" /* 1481, 0x0040, 0x0009 */
    "Scheduled Station Name\0" /* 1482, 0x0040, 0x0010 */
    "Scheduled Procedure Step Location\0" /* 1483, 0x0040, 0x0011 */
    "Pre-Medication\0" /* 1484, 0x0040, 0x0012 */
    "Scheduled Procedure Step Status\0" /* 1485, 0x0040, 0x0020 */
    "Scheduled Procedure Step Sequence\0" /* 1486, 0x0040, 0x0100 */
    "Entrance Dose\0" /* 1487, 0x0040, 0x0302 */
    "Exposed Area\0" /* 1488, 0x0040, 0x0303 */
    "Distance Source to Entrance\0" /* 1489, 0x0040, 0x0306 */
    "Distance Source to Support\0" /* 1490, 0x0040, 0x0307 */
    "Comments On Radiation Dose\0" /* 1491, 0x0040, 0x0310 */
    "X-Ray Output\0" /* 1492, 0x0040, 0x0312 */
    "Half Value Layer\0" /* 1493, 0x0040, 0x0314 */
    "Organ Dose\0" /* 1494, 0x0040, 0x0316 */
    "Organ Exposed\0" /* 1495, 0x0040, 0x0318 */
    "Comments On Scheduled Procedure Step\0" /* 1496, 0x0040, 0x0400 */
    "Specimen Accession Number\0" /* 1497, 0x0040, 0x050a */
    "Specimen Sequence\0" /* 1498, 0x0040, 0x0550 */
    "Specimen Identifier\0" /* 1499, 0x0040, 0x0551 */
    "Specimen Description Sequence\0" /* 1500, 0x0040, 0x0552 */
    "Specimen Description\0" /* 1501, 0x0040, 0x0553 */
    "Acquisition Context Sequence\0" /* 1502, 0x0040, 0x0555 */
    "Acquisition Context Description\0" /* 1503, 0x0040, 0x0556 */
    "Specimen Type Code Sequence\0" /* 1504, 0x0040, 0x059a */
    "Slide Identifier\0" /* 1505, 0x0040, 0x06fa */
    "Image Center Point Coordinates Sequence\0" /* 1506, 0x0040, 0x071a */
    "X Offset In Slide Coordinate System\0" /* 1507, 0x0040, 0x072a */
    "Y Offset In Slide Coordinate System\0" /* 1508, 0x0040, 0x073a */
    "Z Offset In Slide Coordinate System\0" /* 1509, 0x0040, 0x074a */
    "Pixel Spacing Sequence\0" /* 1510, 0x0040, 0x08d8 */
    "Coordinate System Axis Code Sequence\0" /* 1511, 0x0040, 0x08da */
    "Measurement Units Code Sequence\0" /* 1512, 0x0040, 0x08ea */
    "Vital Stain Code Sequence\0" /* 1513, 0x0040, 0x09f8 */
    "Requested Procedure ID\0" /* 1514, 0x0040, 0x1001 */
    "Reason For Requested Procedure\0" /* 1515, 0x0040, 0x1002 */
    "Requested Procedure Priority\0" /* 1516, 0x0040, 0x1003 */
    "Patient Transport Arrangements\0" /* 1517, 0x0040, 0x1004 */
    "Requested Procedure Location\0" /* 1518, 0x0040, 0x1005 */
    "Placer Order Number of Procedure\0" /* 1519, 0x0040, 0x1006 */
    "Filler Order Number of Procedure\0" /* 1520, 0x0040, 0x1007 */
    "Confidentiality Code\0" /* 1521, 0x0040, 0x1008 */
    "Reporting Priority\0" /* 1522, 0x0040, 0x1009 */
    "Names of Intended Recipients of Results\0" /* 1523, 0x0040, 0x1010 */
    "Requested Procedure Comments\0" /* 1524, 0x0040, 0x1400 */
    "Reason For Imaging Service Request\0" /* 1525, 0x0040, 0x2001 */
    "Issue Date of Imaging Service Request\0" /* 1526, 0x0040, 0x2004 */
    "Issue Time of Imaging Service Request\0" /* 1527, 0x0040, 0x2005 */
    "Placer Order Number of Imaging Service Request\0" /* 1528, 0x0040, 0x2006 */
    "Filler Order Number of Imaging Service Request\0" /* 1529, 0x0040, 0x2007 */
    "Order Entered By\0" /* 1530, 0x0040, 0x2008 */
    "Order Enterer Location\0" /* 1531, 0x0040, 0x2009 */
    "Order Callback Phone Number\0" /* 1532, 0x0040, 0x2010 */
    "Imaging Service Request Comments\0" /* 1533, 0x0040, 0x2400 */
    "Confidentiality Constraint On Patient Data\0" /* 1534, 0x0040, 0x3001 */
    "Findings Flag\0" /* 1535, 0x0040, 0xa007 */
    "Findings Sequence\0" /* 1536, 0x0040, 0xa020 */
    "Findings Group UID\0" /* 1537, 0x0040, 0xa021 */
    "Referenced Findings Group UID\0" /* 1538, 0x0040, 0xa022 */
    "Findings Group Recording Date\0" /* 1539, 0x0040, 0xa023 */
    "Findings Group Recording Time\0" /* 1540, 0x0040, 0xa024 */
    "Findings Source Category Code Sequence\0" /* 1541, 0x0040, 0xa026 */
    "Documenting Organization\0" /* 1542, 0x0040, 0xa027 */
    "Documenting Organization Identifier Code Sequence\0" /* 1543, 0x0040, 0xa028 */
    "History Reliability Qualifier Description\0" /* 1544, 0x0040, 0xa032 */
    "Concept Name Code Sequence\0" /* 1545, 0x0040, 0xa043 */
    "Measurement Precision Description\0" /* 1546, 0x0040, 0xa047 */
    "Urgency or Priority Alerts\0" /* 1547, 0x0040, 0xa057 */
    "Sequencing Indicator\0" /* 1548, 0x0040, 0xa060 */
    "Document Identifier Code Sequence\0" /* 1549, 0x0040, 0xa066 */
    "Document Author\0" /* 1550, 0x0040, 0xa067 */
    "Document Author Identifier Code Sequence\0" /* 1551, 0x0040, 0xa068 */
    "Identifier Code Sequence\0" /* 1552, 0x0040, 0xa070 */
    "Object String Identifier\0" /* 1553, 0x0040, 0xa073 */
    "Object Binary Identifier\0" /* 1554, 0x0040, 0xa074 */
    "Documenting Observer\0" /* 1555, 0x0040, 0xa075 */
    "Documenting Observer Identifier Code Sequence\0" /* 1556, 0x0040, 0xa076 */
    "Observation Subject Identifier Code Sequence\0" /* 1557, 0x0040, 0xa078 */
    "Person Identifier Code Sequence\0" /* 1558, 0x0040, 0xa080 */
    "Procedure Identifier Code Sequence\0" /* 1559, 0x0040, 0xa085 */
    "Object Directory String Identifier\0" /* 1560, 0x0040, 0xa088 */
    "Object Directory Binary Identifier\0" /* 1561, 0x0040, 0xa089 */
    "History Reliability Qualifier\0" /* 1562, 0x0040, 0xa090 */
    "Referenced Type of Data\0" /* 1563, 0x0040, 0xa0a0 */
    "Referenced Waveform Channels\0" /* 1564, 0x0040, 0xa0b0 */
    "Date of Document or Verbal Transaction\0" /* 1565, 0x0040, 0xa110 */
    "Time of Document Creation or Verbal Transaction\0" /* 1566, 0x0040, 0xa112 */
    "Date\0" /* 1567, 0x0040, 0xa121 */
    "Time\0" /* 1568, 0x0040, 0xa122 */
    "Person Name\0" /* 1569, 0x0040, 0xa123 */
    "Referenced Person Sequence\0" /* 1570, 0x0040, 0xa124 */
    "Report Status ID\0" /* 1571, 0x0040, 0xa125 */
    "Temporal Range Type\0" /* 1572, 0x0040, 0xa130 */
    "Referenced Sample Offsets\0" /* 1573, 0x0040, 0xa132 */
    "Referenced Frame Numbers\0" /* 1574, 0x0040, 0xa136 */
    "Referenced Time Offsets\0" /* 1575, 0x0040, 0xa138 */
    "Referenced Datetime\0" /* 1576, 0x0040, 0xa13a */
    "Text Value\0" /* 1577, 0x0040, 0xa160 */
    "Observation Category Code Sequence\0" /* 1578, 0x0040, 0xa167 */
    "Concept Code Sequence\0" /* 1579, 0x0040, 0xa168 */
    "Bibliographic Citation\0" /* 1580, 0x0040, 0xa16a */
    "Observation Class\0" /* 1581, 0x0040, 0xa170 */
    "Observation UID\0" /* 1582, 0x0040, 0xa171 */
    "Referenced Observation UID\0" /* 1583, 0x0040, 0xa172 */
    "Referenced Observation Class\0" /* 1584, 0x0040, 0xa173 */
    "Referenced Object Observation Class\0" /* 1585, 0x0040, 0xa174 */
    "Annotation Group Number\0" /* 1586, 0x0040, 0xa180 */
    "Observation Date\0" /* 1587, 0x0040, 0xa192 */
    "Observation Time\0" /* 1588, 0x0040, 0xa193 */
    "Measurement Automation\0" /* 1589, 0x0040, 0xa194 */
    "Concept Name Code Sequence Modifier\0" /* 1590, 0x0040, 0xa195 */
    "Identification Description\0" /* 1591, 0x0040, 0xa224 */
    "Coordinates Set Geometric Type\0" /* 1592, 0x0040, 0xa290 */
    "Algorithm Code Sequence\0" /* 1593, 0x0040, 0xa296 */
    "Algorithm Description\0" /* 1594, 0x0040, 0xa297 */
    "Pixel Coordinates Set\0" /* 1595, 0x0040, 0xa29a */
    "Measured Value Sequence\0" /* 1596, 0x0040, 0xa300 */
    "Current Observer\0" /* 1597, 0x0040, 0xa307 */
    "Numeric Value\0" /* 1598, 0x0040, 0xa30a */
    "Referenced Accession Sequence\0" /* 1599, 0x0040, 0xa313 */
    "Report Status Comment\0" /* 1600, 0x0040, 0xa33a */
    "Procedure Context Sequence\0" /* 1601, 0x0040, 0xa340 */
    "Verbal Source\0" /* 1602, 0x0040, 0xa352 */
    "Address\0" /* 1603, 0x0040, 0xa353 */
    "Telephone Number\0" /* 1604, 0x0040, 0xa354 */
    "Verbal Source Identifier Code Sequence\0" /* 1605, 0x0040, 0xa358 */
    "Report Detail Sequence\0" /* 1606, 0x0040, 0xa380 */
    "Observation Subject UID\0" /* 1607, 0x0040, 0xa402 */
    "Observation Subject Class\0" /* 1608, 0x0040, 0xa403 */
    "Observation Subject Type Code Sequence\0" /* 1609, 0x0040, 0xa404 */
    "Observation Subject Context Flag\0" /* 1610, 0x0040, 0xa600 */
    "Observer Context Flag\0" /* 1611, 0x0040, 0xa601 */
    "Procedure Context Flag\0" /* 1612, 0x0040, 0xa603 */
    "Observations Sequence\0" /* 1613, 0x0040, 0xa730 */
    "Relationship Sequence\0" /* 1614, 0x0040, 0xa731 */
    "Relationship Type Code Sequence\0" /* 1615, 0x0040, 0xa732 */
    "Language Code Sequence\0" /* 1616, 0x0040, 0xa744 */
    "Uniform Resource Locator\0" /* 1617, 0x0040, 0xa992 */
    "Annotation Sequence\0" /* 1618, 0x0040, 0xb020 */
    "Relationship Type Code Sequence Modifier\0" /* 1619, 0x0040, 0xdb73 */
    "Papyrus Comments\0" /* 1620, 0x0041, 0x0000 */
    "?\0" /* 1621, 0x0041, 0x0010 */
    "?\0" /* 1622, 0x0041, 0x0011 */
    "Pixel Offset\0" /* 1623, 0x0041, 0x0012 */
    "Image Identifier Sequence\0" /* 1624, 0x0041, 0x0013 */
    "External File Reference Sequence\0" /* 1625, 0x0041, 0x0014 */
    "Number of Images\0" /* 1626, 0x0041, 0x0015 */
    "?\0" /* 1627, 0x0041, 0x0020 */
    "Referenced SOP Class UID\0" /* 1628, 0x0041, 0x0021 */
    "Referenced SOP Instance UID\0" /* 1629, 0x0041, 0x0022 */
    "?\0" /* 1630, 0x0041, 0x0030 */
    "?\0" /* 1631, 0x0041, 0x0031 */
    "?\0" /* 1632, 0x0041, 0x0032 */
    "Modified Date\0" /* 1633, 0x0041, 0x0034 */
    "Modified Time\0" /* 1634, 0x0041, 0x0036 */
    "Owner Name\0" /* 1635, 0x0041, 0x0040 */
    "Referenced Image SOP Class UID\0" /* 1636, 0x0041, 0x0041 */
    "Referenced Image SOP Instance UID\0" /* 1637, 0x0041, 0x0042 */
    "?\0" /* 1638, 0x0041, 0x0050 */
    "Number of Images\0" /* 1639, 0x0041, 0x0060 */
    "Number of Other\0" /* 1640, 0x0041, 0x0062 */
    "External Folder Element DSID\0" /* 1641, 0x0041, 0x00a0 */
    "External Folder Element Data Set Type\0" /* 1642, 0x0041, 0x00a1 */
    "External Folder Element File Location\0" /* 1643, 0x0041, 0x00a2 */
    "External Folder Element Length\0" /* 1644, 0x0041, 0x00a3 */
    "Internal Folder Element DSID\0" /* 1645, 0x0041, 0x00b0 */
    "Internal Folder Element Data Set Type\0" /* 1646, 0x0041, 0x00b1 */
    "Internal Offset To Data Set\0" /* 1647, 0x0041, 0x00b2 */
    "Internal Offset To Image\0" /* 1648, 0x0041, 0x00b3 */
    "Bitmap Of Prescan Options\0" /* 1649, 0x0043, 0x0001 */
    "Gradient Offset In X\0" /* 1650, 0x0043, 0x0002 */
    "Gradient Offset In Y\0" /* 1651, 0x0043, 0x0003 */
    "Gradient Offset In Z\0" /* 1652, 0x0043, 0x0004 */
    "Image Is Original Or Unoriginal\0" /* 1653, 0x0043, 0x0005 */
    "Number Of EPI Shots\0" /* 1654, 0x0043, 0x0006 */
    "Views Per Segment\0" /* 1655, 0x0043, 0x0007 */
    "Respiratory Rate In BPM\0" /* 1656, 0x0043, 0x0008 */
    "Respiratory Trigger Point\0" /* 1657, 0x0043, 0x0009 */
    "Type Of Receiver Used\0" /* 1658, 0x0043, 0x000a */
    "Peak Rate Of Change Of Gradient Field\0" /* 1659, 0x0043, 0x000b */
    "Limits In Units Of Percent\0" /* 1660, 0x0043, 0x000c */
    "PSD Estimated Limit\0" /* 1661, 0x0043, 0x000d */
    "PSD Estimated Limit In Tesla Per Second\0" /* 1662, 0x0043, 0x000e */
    "SAR Avg Head\0" /* 1663, 0x0043, 0x000f */
    "Window Value\0" /* 1664, 0x0043, 0x0010 */
    "Total Input Views\0" /* 1665, 0x0043, 0x0011 */
    "Xray Chain\0" /* 1666, 0x0043, 0x0012 */
    "Recon Kernel Parameters\0" /* 1667, 0x0043, 0x0013 */
    "Calibration Parameters\0" /* 1668, 0x0043, 0x0014 */
    "Total Output Views\0" /* 1669, 0x0043, 0x0015 */
    "Number Of Overranges\0" /* 1670, 0x0043, 0x0016 */
    "IBH Image Scale Factors\0" /* 1671, 0x0043, 0x0017 */
    "BBH Coefficients\0" /* 1672, 0x0043, 0x0018 */
    "Number Of BBH Chains To Blend\0" /* 1673, 0x0043, 0x0019 */
    "Starting Channel Number\0" /* 1674, 0x0043, 0x001a */
    "PPScan Parameters\0" /* 1675, 0x0043, 0x001b */
    "GE Image Integrity\0" /* 1676, 0x0043, 0x001c */
    "Level Value\0" /* 1677, 0x0043, 0x001d */
    "?\0" /* 1678, 0x0043, 0x001e */
    "Max Overranges In A View\0" /* 1679, 0x0043, 0x001f */
    "Avg Overranges All Views\0" /* 1680, 0x0043, 0x0020 */
    "Corrected Afterglow Terms\0" /* 1681, 0x0043, 0x0021 */
    "Reference Channels\0" /* 1682, 0x0043, 0x0025 */
    "No Views Ref Channels Blocked\0" /* 1683, 0x0043, 0x0026 */
    "?\0" /* 1684, 0x0043, 0x0027 */
    "Unique Image Identifier\0" /* 1685, 0x0043, 0x0028 */
    "Histogram Tables\0" /* 1686, 0x0043, 0x0029 */
    "User Defined Data\0" /* 1687, 0x0043, 0x002a */
    "Private Scan Options\0" /* 1688, 0x0043, 0x002b */
    "Effective Echo Spacing\0" /* 1689, 0x0043, 0x002c */
    "String Slop Field 1\0" /* 1690, 0x0043, 0x002d */
    "String Slop Field 2\0" /* 1691, 0x0043, 0x002e */
    "Raw Data Type\0" /* 1692, 0x0043, 0x002f */
    "Raw Data Type\0" /* 1693, 0x0043, 0x0030 */
    "RA Coord Of Target Recon Centre\0" /* 1694, 0x0043, 0x0031 */
    "Raw Data Type\0" /* 1695, 0x0043, 0x0032 */
    "Neg Scan Spacing\0" /* 1696, 0x0043, 0x0033 */
    "Offset Frequency\0" /* 1697, 0x0043, 0x0034 */
    "User Usage Tag\0" /* 1698, 0x0043, 0x0035 */
    "User Fill Map MSW\0" /* 1699, 0x0043, 0x0036 */
    "User Fill Map LSW\0" /* 1700, 0x0043, 0x0037 */
    "User 25 To User 48\0" /* 1701, 0x0043, 0x0038 */
    "Slop Integer 6 To Slop Integer 9\0" /* 1702, 0x0043, 0x0039 */
    "Trigger On Position\0" /* 1703, 0x0043, 0x0040 */
    "Degree Of Rotation\0" /* 1704, 0x0043, 0x0041 */
    "DAS Trigger Source\0" /* 1705, 0x0043, 0x0042 */
    "DAS Fpa Gain\0" /* 1706, 0x0043, 0x0043 */
    "DAS Output Source\0" /* 1707, 0x0043, 0x0044 */
    "DAS Ad Input\0" /* 1708, 0x0043, 0x0045 */
    "DAS Cal Mode\0" /* 1709, 0x0043, 0x0046 */
    "DAS Cal Frequency\0" /* 1710, 0x0043, 0x0047 */
    "DAS Reg Xm\0" /* 1711, 0x0043, 0x0048 */
    "DAS Auto Zero\0" /* 1712, 0x0043, 0x0049 */
    "Starting Channel Of View\0" /* 1713, 0x0043, 0x004a */
    "DAS Xm Pattern\0" /* 1714, 0x0043, 0x004b */
    "TGGC Trigger Mode\0" /* 1715, 0x0043, 0x004c */
    "Start Scan To Xray On Delay\0" /* 1716, 0x0043, 0x004d */
    "Duration Of Xray On\0" /* 1717, 0x0043, 0x004e */
    "?\0" /* 1718, 0x0044, 0x0000 */
    "AES\0" /* 1719, 0x0045, 0x0004 */
    "Angulation\0" /* 1720, 0x0045, 0x0006 */
    "Real Magnification Factor\0" /* 1721, 0x0045, 0x0009 */
    "Senograph Type\0" /* 1722, 0x0045, 0x000b */
    "Integration Time\0" /* 1723, 0x0045, 0x000c */
    "ROI Origin X and Y\0" /* 1724, 0x0045, 0x000d */
    "Receptor Size cm X and Y\0" /* 1725, 0x0045, 0x0011 */
    "Receptor Size Pixels X and Y\0" /* 1726, 0x0045, 0x0012 */
    "Screen\0" /* 1727, 0x0045, 0x0013 */
    "Pixel Pitch Microns\0" /* 1728, 0x0045, 0x0014 */
    "Pixel Depth Bits\0" /* 1729, 0x0045, 0x0015 */
    "Binning Factor X and Y\0" /* 1730, 0x0045, 0x0016 */
    "Clinical View\0" /* 1731, 0x0045, 0x001b */
    "Mean Of Raw Gray Levels\0" /* 1732, 0x0045, 0x001d */
    "Mean Of Offset Gray Levels\0" /* 1733, 0x0045, 0x001e */
    "Mean Of Corrected Gray Levels\0" /* 1734, 0x0045, 0x001f */
    "Mean Of Region Gray Levels\0" /* 1735, 0x0045, 0x0020 */
    "Mean Of Log Region Gray Levels\0" /* 1736, 0x0045, 0x0021 */
    "Standard Deviation Of Raw Gray Levels\0" /* 1737, 0x0045, 0x0022 */
    "Standard Deviation Of Corrected Gray Levels\0" /* 1738, 0x0045, 0x0023 */
    "Standard Deviation Of Region Gray Levels\0" /* 1739, 0x0045, 0x0024 */
    "Standard Deviation Of Log Region Gray Levels\0" /* 1740, 0x0045, 0x0025 */
    "MAO Buffer\0" /* 1741, 0x0045, 0x0026 */
    "Set Number\0" /* 1742, 0x0045, 0x0027 */
    "WindowingType (LINEAR or GAMMA)\0" /* 1743, 0x0045, 0x0028 */
    "WindowingParameters\0" /* 1744, 0x0045, 0x0029 */
    "Crosshair Cursor X Coordinates\0" /* 1745, 0x0045, 0x002a */
    "Crosshair Cursor Y Coordinates\0" /* 1746, 0x0045, 0x002b */
    "Vignette Rows\0" /* 1747, 0x0045, 0x0039 */
    "Vignette Columns\0" /* 1748, 0x0045, 0x003a */
    "Vignette Bits Allocated\0" /* 1749, 0x0045, 0x003b */
    "Vignette Bits Stored\0" /* 1750, 0x0045, 0x003c */
    "Vignette High Bit\0" /* 1751, 0x0045, 0x003d */
    "Vignette Pixel Representation\0" /* 1752, 0x0045, 0x003e */
    "Vignette Pixel Data\0" /* 1753, 0x0045, 0x003f */
    "Reconstruction Parameters Sequence\0" /* 1754, 0x0047, 0x0001 */
    "Volume Voxel Count\0" /* 1755, 0x0047, 0x0050 */
    "Volume Segment Count\0" /* 1756, 0x0047, 0x0051 */
    "Volume Slice Size\0" /* 1757, 0x0047, 0x0053 */
    "Volume Slice Count\0" /* 1758, 0x0047, 0x0054 */
    "Volume Threshold Value\0" /* 1759, 0x0047, 0x0055 */
    "Volume Voxel Ratio\0" /* 1760, 0x0047, 0x0057 */
    "Volume Voxel Size\0" /* 1761, 0x0047, 0x0058 */
    "Volume Z Position Size\0" /* 1762, 0x0047, 0x0059 */
    "Volume Base Line\0" /* 1763, 0x0047, 0x0060 */
    "Volume Center Point\0" /* 1764, 0x0047, 0x0061 */
    "Volume Skew Base\0" /* 1765, 0x0047, 0x0063 */
    "Volume Registration Transform Rotation Matrix\0" /* 1766, 0x0047, 0x0064 */
    "Volume Registration Transform Translation Vector\0" /* 1767, 0x0047, 0x0065 */
    "KVP List\0" /* 1768, 0x0047, 0x0070 */
    "XRay Tube Current List\0" /* 1769, 0x0047, 0x0071 */
    "Exposure List\0" /* 1770, 0x0047, 0x0072 */
    "Acquisition DLX Identifier\0" /* 1771, 0x0047, 0x0080 */
    "Acquisition DLX 2D Series Sequence\0" /* 1772, 0x0047, 0x0085 */
    "Contrast Agent Volume List\0" /* 1773, 0x0047, 0x0089 */
    "Number Of Injections\0" /* 1774, 0x0047, 0x008a */
    "Frame Count\0" /* 1775, 0x0047, 0x008b */
    "Used Frames\0" /* 1776, 0x0047, 0x0096 */
    "XA 3D Reconstruction Algorithm Name\0" /* 1777, 0x0047, 0x0091 */
    "XA 3D Reconstruction Algorithm Version\0" /* 1778, 0x0047, 0x0092 */
    "DLX Calibration Date\0" /* 1779, 0x0047, 0x0093 */
    "DLX Calibration Time\0" /* 1780, 0x0047, 0x0094 */
    "DLX Calibration Status\0" /* 1781, 0x0047, 0x0095 */
    "Transform Count\0" /* 1782, 0x0047, 0x0098 */
    "Transform Sequence\0" /* 1783, 0x0047, 0x0099 */
    "Transform Rotation Matrix\0" /* 1784, 0x0047, 0x009a */
    "Transform Translation Vector\0" /* 1785, 0x0047, 0x009b */
    "Transform Label\0" /* 1786, 0x0047, 0x009c */
    "Wireframe Count\0" /* 1787, 0x0047, 0x00b1 */
    "Location System\0" /* 1788, 0x0047, 0x00b2 */
    "Wireframe List\0" /* 1789, 0x0047, 0x00b0 */
    "Wireframe Name\0" /* 1790, 0x0047, 0x00b5 */
    "Wireframe Group Name\0" /* 1791, 0x0047, 0x00b6 */
    "Wireframe Color\0" /* 1792, 0x0047, 0x00b7 */
    "Wireframe Attributes\0" /* 1793, 0x0047, 0x00b8 */
    "Wireframe Point Count\0" /* 1794, 0x0047, 0x00b9 */
    "Wireframe Timestamp\0" /* 1795, 0x0047, 0x00ba */
    "Wireframe Point List\0" /* 1796, 0x0047, 0x00bb */
    "Wireframe Points Coordinates\0" /* 1797, 0x0047, 0x00bc */
    "Volume Upper Left High Corner RAS\0" /* 1798, 0x0047, 0x00c0 */
    "Volume Slice To RAS Rotation Matrix\0" /* 1799, 0x0047, 0x00c1 */
    "Volume Upper Left High Corner TLOC\0" /* 1800, 0x0047, 0x00c2 */
    "Volume Segment List\0" /* 1801, 0x0047, 0x00d1 */
    "Volume Gradient List\0" /* 1802, 0x0047, 0x00d2 */
    "Volume Density List\0" /* 1803, 0x0047, 0x00d3 */
    "Volume Z Position List\0" /* 1804, 0x0047, 0x00d4 */
    "Volume Original Index List\0" /* 1805, 0x0047, 0x00d5 */
    "Calibration Group Length\0" /* 1806, 0x0050, 0x0000 */
    "Calibration Object\0" /* 1807, 0x0050, 0x0004 */
    "DeviceSequence\0" /* 1808, 0x0050, 0x0010 */
    "DeviceLength\0" /* 1809, 0x0050, 0x0014 */
    "DeviceDiameter\0" /* 1810, 0x0050, 0x0016 */
    "DeviceDiameterUnits\0" /* 1811, 0x0050, 0x0017 */
    "DeviceVolume\0" /* 1812, 0x0050, 0x0018 */
    "InterMarkerDistance\0" /* 1813, 0x0050, 0x0019 */
    "DeviceDescription\0" /* 1814, 0x0050, 0x0020 */
    "CodedInterventionDeviceSequence\0" /* 1815, 0x0050, 0x0030 */
    "Image Text\0" /* 1816, 0x0051, 0x0010 */
    "Nuclear Acquisition Group Length\0" /* 1817, 0x0054, 0x0000 */
    "Energy Window Vector\0" /* 1818, 0x0054, 0x0010 */
    "Number of Energy Windows\0" /* 1819, 0x0054, 0x0011 */
    "Energy Window Information Sequence\0" /* 1820, 0x0054, 0x0012 */
    "Energy Window Range Sequence\0" /* 1821, 0x0054, 0x0013 */
    "Energy Window Lower Limit\0" /* 1822, 0x0054, 0x0014 */
    "Energy Window Upper Limit\0" /* 1823, 0x0054, 0x0015 */
    "Radiopharmaceutical Information Sequence\0" /* 1824, 0x0054, 0x0016 */
    "Residual Syringe Counts\0" /* 1825, 0x0054, 0x0017 */
    "Energy Window Name\0" /* 1826, 0x0054, 0x0018 */
    "Detector Vector\0" /* 1827, 0x0054, 0x0020 */
    "Number of Detectors\0" /* 1828, 0x0054, 0x0021 */
    "Detector Information Sequence\0" /* 1829, 0x0054, 0x0022 */
    "Phase Vector\0" /* 1830, 0x0054, 0x0030 */
    "Number of Phases\0" /* 1831, 0x0054, 0x0031 */
    "Phase Information Sequence\0" /* 1832, 0x0054, 0x0032 */
    "Number of Frames In Phase\0" /* 1833, 0x0054, 0x0033 */
    "Phase Delay\0" /* 1834, 0x0054, 0x0036 */
    "Pause Between Frames\0" /* 1835, 0x0054, 0x0038 */
    "Rotation Vector\0" /* 1836, 0x0054, 0x0050 */
    "Number of Rotations\0" /* 1837, 0x0054, 0x0051 */
    "Rotation Information Sequence\0" /* 1838, 0x0054, 0x0052 */
    "Number of Frames In Rotation\0" /* 1839, 0x0054, 0x0053 */
    "R-R Interval Vector\0" /* 1840, 0x0054, 0x0060 */
    "Number of R-R Intervals\0" /* 1841, 0x0054, 0x0061 */
    "Gated Information Sequence\0" /* 1842, 0x0054, 0x0062 */
    "Data Information Sequence\0" /* 1843, 0x0054, 0x0063 */
    "Time Slot Vector\0" /* 1844, 0x0054, 0x0070 */
    "Number of Time Slots\0" /* 1845, 0x0054, 0x0071 */
    "Time Slot Information Sequence\0" /* 1846, 0x0054, 0x0072 */
    "Time Slot Time\0" /* 1847, 0x0054, 0x0073 */
    "Slice Vector\0" /* 1848, 0x0054, 0x0080 */
    "Number of Slices\0" /* 1849, 0x0054, 0x0081 */
    "Angular View Vector\0" /* 1850, 0x0054, 0x0090 */
    "Time Slice Vector\0" /* 1851, 0x0054, 0x0100 */
    "Number Of Time Slices\0" /* 1852, 0x0054, 0x0101 */
    "Start Angle\0" /* 1853, 0x0054, 0x0200 */
    "Type of Detector Motion\0" /* 1854, 0x0054, 0x0202 */
    "Trigger Vector\0" /* 1855, 0x0054, 0x0210 */
    "Number of Triggers in Phase\0" /* 1856, 0x0054, 0x0211 */
    "View Code Sequence\0" /* 1857, 0x0054, 0x0220 */
    "View Modifier Code Sequence\0" /* 1858, 0x0054, 0x0222 */
    "Radionuclide Code Sequence\0" /* 1859, 0x0054, 0x0300 */
    "Radiopharmaceutical Route Code Sequence\0" /* 1860, 0x0054, 0x0302 */
    "Radiopharmaceutical Code Sequence\0" /* 1861, 0x0054, 0x0304 */
    "Calibration Data Sequence\0" /* 1862, 0x0054, 0x0306 */
    "Energy Window Number\0" /* 1863, 0x0054, 0x0308 */
    "Image ID\0" /* 1864, 0x0054, 0x0400 */
    "Patient Orientation Code Sequence\0" /* 1865, 0x0054, 0x0410 */
    "Patient Orientation Modifier Code Sequence\0" /* 1866, 0x0054, 0x0412 */
    "Patient Gantry Relationship Code Sequence\0" /* 1867, 0x0054, 0x0414 */
    "Positron Emission Tomography Series Type\0" /* 1868, 0x0054, 0x1000 */
    "Positron Emission Tomography Units\0" /* 1869, 0x0054, 0x1001 */
    "Counts Source\0" /* 1870, 0x0054, 0x1002 */
    "Reprojection Method\0" /* 1871, 0x0054, 0x1004 */
    "Randoms Correction Method\0" /* 1872, 0x0054, 0x1100 */
    "Attenuation Correction Method\0" /* 1873, 0x0054, 0x1101 */
    "Decay Correction\0" /* 1874, 0x0054, 0x1102 */
    "Reconstruction Method\0" /* 1875, 0x0054, 0x1103 */
    "Detector Lines of Response Used\0" /* 1876, 0x0054, 0x1104 */
    "Scatter Correction Method\0" /* 1877, 0x0054, 0x1105 */
    "Axial Acceptance\0" /* 1878, 0x0054, 0x1200 */
    "Axial Mash\0" /* 1879, 0x0054, 0x1201 */
    "Transverse Mash\0" /* 1880, 0x0054, 0x1202 */
    "Detector Element Size\0" /* 1881, 0x0054, 0x1203 */
    "Coincidence Window Width\0" /* 1882, 0x0054, 0x1210 */
    "Secondary Counts Type\0" /* 1883, 0x0054, 0x1220 */
    "Frame Reference Time\0" /* 1884, 0x0054, 0x1300 */
    "Primary Prompts Counts Accumulated\0" /* 1885, 0x0054, 0x1310 */
    "Secondary Counts Accumulated\0" /* 1886, 0x0054, 0x1311 */
    "Slice Sensitivity Factor\0" /* 1887, 0x0054, 0x1320 */
    "Decay Factor\0" /* 1888, 0x0054, 0x1321 */
    "Dose Calibration Factor\0" /* 1889, 0x0054, 0x1322 */
    "Scatter Fraction Factor\0" /* 1890, 0x0054, 0x1323 */
    "Dead Time Factor\0" /* 1891, 0x0054, 0x1324 */
    "Image Index\0" /* 1892, 0x0054, 0x1330 */
    "Counts Included\0" /* 1893, 0x0054, 0x1400 */
    "Dead Time Correction Flag\0" /* 1894, 0x0054, 0x1401 */
    "Current Ward\0" /* 1895, 0x0055, 0x0046 */
    "?\0" /* 1896, 0x0058, 0x0000 */
    "Histogram Sequence\0" /* 1897, 0x0060, 0x3000 */
    "Histogram Number of Bins\0" /* 1898, 0x0060, 0x3002 */
    "Histogram First Bin Value\0" /* 1899, 0x0060, 0x3004 */
    "Histogram Last Bin Value\0" /* 1900, 0x0060, 0x3006 */
    "Histogram Bin Width\0" /* 1901, 0x0060, 0x3008 */
    "Histogram Explanation\0" /* 1902, 0x0060, 0x3010 */
    "Histogram Data\0" /* 1903, 0x0060, 0x3020 */
    "Graphic Annotation Sequence\0" /* 1904, 0x0070, 0x0001 */
    "Graphic Layer\0" /* 1905, 0x0070, 0x0002 */
    "Bounding Box Annotation Units\0" /* 1906, 0x0070, 0x0003 */
    "Anchor Point Annotation Units\0" /* 1907, 0x0070, 0x0004 */
    "Graphic Annotation Units\0" /* 1908, 0x0070, 0x0005 */
    "Unformatted Text Value\0" /* 1909, 0x0070, 0x0006 */
    "Text Object Sequence\0" /* 1910, 0x0070, 0x0008 */
    "Graphic Object Sequence\0" /* 1911, 0x0070, 0x0009 */
    "Bounding Box TLHC\0" /* 1912, 0x0070, 0x0010 */
    "Bounding Box BRHC\0" /* 1913, 0x0070, 0x0011 */
    "Anchor Point\0" /* 1914, 0x0070, 0x0014 */
    "Anchor Point Visibility\0" /* 1915, 0x0070, 0x0015 */
    "Graphic Dimensions\0" /* 1916, 0x0070, 0x0020 */
    "Number Of Graphic Points\0" /* 1917, 0x0070, 0x0021 */
    "Graphic Data\0" /* 1918, 0x0070, 0x0022 */
    "Graphic Type\0" /* 1919, 0x0070, 0x0023 */
    "Graphic Filled\0" /* 1920, 0x0070, 0x0024 */
    "Image Rotation\0" /* 1921, 0x0070, 0x0040 */
    "Image Horizontal Flip\0" /* 1922, 0x0070, 0x0041 */
    "Displayed Area TLHC\0" /* 1923, 0x0070, 0x0050 */
    "Displayed Area BRHC\0" /* 1924, 0x0070, 0x0051 */
    "Graphic Layer Sequence\0" /* 1925, 0x0070, 0x0060 */
    "Graphic Layer Order\0" /* 1926, 0x0070, 0x0062 */
    "Graphic Layer Recommended Display Value\0" /* 1927, 0x0070, 0x0066 */
    "Graphic Layer Description\0" /* 1928, 0x0070, 0x0068 */
    "Presentation Label\0" /* 1929, 0x0070, 0x0080 */
    "Presentation Description\0" /* 1930, 0x0070, 0x0081 */
    "Presentation Creation Date\0" /* 1931, 0x0070, 0x0082 */
    "Presentation Creation Time\0" /* 1932, 0x0070, 0x0083 */
    "Presentation Creator's Name\0" /* 1933, 0x0070, 0x0084 */
    "Media Type\0" /* 1934, 0x0087, 0x0010 */
    "Media Location\0" /* 1935, 0x0087, 0x0020 */
    "Estimated Retrieve Time\0" /* 1936, 0x0087, 0x0050 */
    "Storage Group Length\0" /* 1937, 0x0088, 0x0000 */
    "Storage Media FileSet ID\0" /* 1938, 0x0088, 0x0130 */
    "Storage Media FileSet UID\0" /* 1939, 0x0088, 0x0140 */
    "Icon Image Sequence\0" /* 1940, 0x0088, 0x0200 */
    "Topic Title\0" /* 1941, 0x0088, 0x0904 */
    "Topic Subject\0" /* 1942, 0x0088, 0x0906 */
    "Topic Author\0" /* 1943, 0x0088, 0x0910 */
    "Topic Key Words\0" /* 1944, 0x0088, 0x0912 */
    "Examination Folder ID\0" /* 1945, 0x0095, 0x0001 */
    "Folder Reported Status\0" /* 1946, 0x0095, 0x0004 */
    "Folder Reporting Radiologist\0" /* 1947, 0x0095, 0x0005 */
    "SIENET ISA PLA\0" /* 1948, 0x0095, 0x0007 */
    "Data Object Attributes\0" /* 1949, 0x0099, 0x0002 */
    "Data Dictionary Version\0" /* 1950, 0x00e1, 0x0001 */
    "?\0" /* 1951, 0x00e1, 0x0014 */
    "?\0" /* 1952, 0x00e1, 0x0022 */
    "?\0" /* 1953, 0x00e1, 0x0023 */
    "?\0" /* 1954, 0x00e1, 0x0024 */
    "?\0" /* 1955, 0x00e1, 0x0025 */
    "Offset From CT MR Images\0" /* 1956, 0x00e1, 0x0040 */
    "RIS Key\0" /* 1957, 0x0193, 0x0002 */
    "RIS Worklist IMGEF\0" /* 1958, 0x0307, 0x0001 */
    "RIS Report IMGEF\0" /* 1959, 0x0309, 0x0001 */
    "Implementation Version\0" /* 1960, 0x0601, 0x0000 */
    "Relative Table Position\0" /* 1961, 0x0601, 0x0020 */
    "Relative Table Height\0" /* 1962, 0x0601, 0x0021 */
    "Surview Direction\0" /* 1963, 0x0601, 0x0030 */
    "Surview Length\0" /* 1964, 0x0601, 0x0031 */
    "Image View Type\0" /* 1965, 0x0601, 0x0050 */
    "Batch Number\0" /* 1966, 0x0601, 0x0070 */
    "Batch Size\0" /* 1967, 0x0601, 0x0071 */
    "Batch Slice Number\0" /* 1968, 0x0601, 0x0072 */
    "?\0" /* 1969, 0x1000, 0x0000 */
    "Run Length Triplet\0" /* 1970, 0x1000, 0x0001 */
    "Huffman Table Size\0" /* 1971, 0x1000, 0x0002 */
    "Huffman Table Triplet\0" /* 1972, 0x1000, 0x0003 */
    "Shift Table Size\0" /* 1973, 0x1000, 0x0004 */
    "Shift Table Triplet\0" /* 1974, 0x1000, 0x0005 */
    "?\0" /* 1975, 0x1010, 0x0000 */
    "?\0" /* 1976, 0x1369, 0x0000 */
    "Film Session Group Length\0" /* 1977, 0x2000, 0x0000 */
    "Number of Copies\0" /* 1978, 0x2000, 0x0010 */
    "Print Priority\0" /* 1979, 0x2000, 0x0020 */
    "Medium Type\0" /* 1980, 0x2000, 0x0030 */
    "Film Destination\0" /* 1981, 0x2000, 0x0040 */
    "Film Session Label\0" /* 1982, 0x2000, 0x0050 */
    "Memory Allocation\0" /* 1983, 0x2000, 0x0060 */
    "Referenced Film Box Sequence\0" /* 1984, 0x2000, 0x0500 */
    "Film Box Group Length\0" /* 1985, 0x2010, 0x0000 */
    "Image Display Format\0" /* 1986, 0x2010, 0x0010 */
    "Annotation Display Format ID\0" /* 1987, 0x2010, 0x0030 */
    "Film Orientation\0" /* 1988, 0x2010, 0x0040 */
    "Film Size ID\0" /* 1989, 0x2010, 0x0050 */
    "Magnification Type\0" /* 1990, 0x2010, 0x0060 */
    "Smoothing Type\0" /* 1991, 0x2010, 0x0080 */
    "Border Density\0" /* 1992, 0x2010, 0x0100 */
    "Empty Image Density\0" /* 1993, 0x2010, 0x0110 */
    "Min Density\0" /* 1994, 0x2010, 0x0120 */
    "Max Density\0" /* 1995, 0x2010, 0x0130 */
    "Trim\0" /* 1996, 0x2010, 0x0140 */
    "Configuration Information\0" /* 1997, 0x2010, 0x0150 */
    "Referenced Film Session Sequence\0" /* 1998, 0x2010, 0x0500 */
    "Referenced Image Box Sequence\0" /* 1999, 0x2010, 0x0510 */
    "Referenced Basic Annotation Box Sequence\0" /* 2000, 0x2010, 0x0520 */
    "Image Box Group Length\0" /* 2001, 0x2020, 0x0000 */
    "Image Box Position\0" /* 2002, 0x2020, 0x0010 */
    "Polarity\0" /* 2003, 0x2020, 0x0020 */
    "Requested Image Size\0" /* 2004, 0x2020, 0x0030 */
    "Preformatted Grayscale Image Sequence\0" /* 2005, 0x2020, 0x0110 */
    "Preformatted Color Image Sequence\0" /* 2006, 0x2020, 0x0111 */
    "Referenced Image Overlay Box Sequence\0" /* 2007, 0x2020, 0x0130 */
    "Referenced VOI LUT Box Sequence\0" /* 2008, 0x2020, 0x0140 */
    "Annotation Group Length\0" /* 2009, 0x2030, 0x0000 */
    "Annotation Position\0" /* 2010, 0x2030, 0x0010 */
    "Text String\0" /* 2011, 0x2030, 0x0020 */
    "Overlay Box Group Length\0" /* 2012, 0x2040, 0x0000 */
    "Referenced Overlay Plane Sequence\0" /* 2013, 0x2040, 0x0010 */
    "Referenced Overlay Plane Groups\0" /* 2014, 0x2040, 0x0011 */
    "Overlay Magnification Type\0" /* 2015, 0x2040, 0x0060 */
    "Overlay Smoothing Type\0" /* 2016, 0x2040, 0x0070 */
    "Overlay Foreground Density\0" /* 2017, 0x2040, 0x0080 */
    "Overlay Mode\0" /* 2018, 0x2040, 0x0090 */
    "Threshold Density\0" /* 2019, 0x2040, 0x0100 */
    "Referenced Overlay Image Box Sequence\0" /* 2020, 0x2040, 0x0500 */
    "Presentation LUT Sequence\0" /* 2021, 0x2050, 0x0010 */
    "Presentation LUT Shape\0" /* 2022, 0x2050, 0x0020 */
    "Print Job Group Length\0" /* 2023, 0x2100, 0x0000 */
    "Execution Status\0" /* 2024, 0x2100, 0x0020 */
    "Execution Status Info\0" /* 2025, 0x2100, 0x0030 */
    "Creation Date\0" /* 2026, 0x2100, 0x0040 */
    "Creation Time\0" /* 2027, 0x2100, 0x0050 */
    "Originator\0" /* 2028, 0x2100, 0x0070 */
    "Referenced Print Job Sequence\0" /* 2029, 0x2100, 0x0500 */
    "Printer Group Length\0" /* 2030, 0x2110, 0x0000 */
    "Printer Status\0" /* 2031, 0x2110, 0x0010 */
    "Printer Status Info\0" /* 2032, 0x2110, 0x0020 */
    "Printer Name\0" /* 2033, 0x2110, 0x0030 */
    "Print Queue ID\0" /* 2034, 0x2110, 0x0099 */
    "RT Image Label\0" /* 2035, 0x3002, 0x0002 */
    "RT Image Name\0" /* 2036, 0x3002, 0x0003 */
    "RT Image Description\0" /* 2037, 0x3002, 0x0004 */
    "Reported Values Origin\0" /* 2038, 0x3002, 0x000a */
    "RT Image Plane\0" /* 2039, 0x3002, 0x000c */
    "X-Ray Image Receptor Angle\0" /* 2040, 0x3002, 0x000e */
    "RTImageOrientation\0" /* 2041, 0x3002, 0x0010 */
    "Image Plane Pixel Spacing\0" /* 2042, 0x3002, 0x0011 */
    "RT Image Position\0" /* 2043, 0x3002, 0x0012 */
    "Radiation Machine Name\0" /* 2044, 0x3002, 0x0020 */
    "Radiation Machine SAD\0" /* 2045, 0x3002, 0x0022 */
    "Radiation Machine SSD\0" /* 2046, 0x3002, 0x0024 */
    "RT Image SID\0" /* 2047, 0x3002, 0x0026 */
    "Source to Reference Object Distance\0" /* 2048, 0x3002, 0x0028 */
    "Fraction Number\0" /* 2049, 0x3002, 0x0029 */
    "Exposure Sequence\0" /* 2050, 0x3002, 0x0030 */
    "Meterset Exposure\0" /* 2051, 0x3002, 0x0032 */
    "DVH Type\0" /* 2052, 0x3004, 0x0001 */
    "Dose Units\0" /* 2053, 0x3004, 0x0002 */
    "Dose Type\0" /* 2054, 0x3004, 0x0004 */
    "Dose Comment\0" /* 2055, 0x3004, 0x0006 */
    "Normalization Point\0" /* 2056, 0x3004, 0x0008 */
    "Dose Summation Type\0" /* 2057, 0x3004, 0x000a */
    "GridFrame Offset Vector\0" /* 2058, 0x3004, 0x000c */
    "Dose Grid Scaling\0" /* 2059, 0x3004, 0x000e */
    "RT Dose ROI Sequence\0" /* 2060, 0x3004, 0x0010 */
    "Dose Value\0" /* 2061, 0x3004, 0x0012 */
    "DVH Normalization Point\0" /* 2062, 0x3004, 0x0040 */
    "DVH Normalization Dose Value\0" /* 2063, 0x3004, 0x0042 */
    "DVH Sequence\0" /* 2064, 0x3004, 0x0050 */
    "DVH Dose Scaling\0" /* 2065, 0x3004, 0x0052 */
    "DVH Volume Units\0" /* 2066, 0x3004, 0x0054 */
    "DVH Number of Bins\0" /* 2067, 0x3004, 0x0056 */
    "DVH Data\0" /* 2068, 0x3004, 0x0058 */
    "DVH Referenced ROI Sequence\0" /* 2069, 0x3004, 0x0060 */
    "DVH ROI Contribution Type\0" /* 2070, 0x3004, 0x0062 */
    "DVH Minimum Dose\0" /* 2071, 0x3004, 0x0070 */
    "DVH Maximum Dose\0" /* 2072, 0x3004, 0x0072 */
    "DVH Mean Dose\0" /* 2073, 0x3004, 0x0074 */
    "Structure Set Label\0" /* 2074, 0x3006, 0x0002 */
    "Structure Set Name\0" /* 2075, 0x3006, 0x0004 */
    "Structure Set Description\0" /* 2076, 0x3006, 0x0006 */
    "Structure Set Date\0" /* 2077, 0x3006, 0x0008 */
    "Structure Set Time\0" /* 2078, 0x3006, 0x0009 */
    "Referenced Frame of Reference Sequence\0" /* 2079, 0x3006, 0x0010 */
    "RT Referenced Study Sequence\0" /* 2080, 0x3006, 0x0012 */
    "RT Referenced Series Sequence\0" /* 2081, 0x3006, 0x0014 */
    "Contour Image Sequence\0" /* 2082, 0x3006, 0x0016 */
    "Structure Set ROI Sequence\0" /* 2083, 0x3006, 0x0020 */
    "ROI Number\0" /* 2084, 0x3006, 0x0022 */
    "Referenced Frame of Reference UID\0" /* 2085, 0x3006, 0x0024 */
    "ROI Name\0" /* 2086, 0x3006, 0x0026 */
    "ROI Description\0" /* 2087, 0x3006, 0x0028 */
    "ROI Display Color\0" /* 2088, 0x3006, 0x002a */
    "ROI Volume\0" /* 2089, 0x3006, 0x002c */
    "RT Related ROI Sequence\0" /* 2090, 0x3006, 0x0030 */
    "RT ROI Relationship\0" /* 2091, 0x3006, 0x0033 */
    "ROI Generation Algorithm\0" /* 2092, 0x3006, 0x0036 */
    "ROI Generation Description\0" /* 2093, 0x3006, 0x0038 */
    "ROI Contour Sequence\0" /* 2094, 0x3006, 0x0039 */
    "Contour Sequence\0" /* 2095, 0x3006, 0x0040 */
    "Contour Geometric Type\0" /* 2096, 0x3006, 0x0042 */
    "Contour SlabT hickness\0" /* 2097, 0x3006, 0x0044 */
    "Contour Offset Vector\0" /* 2098, 0x3006, 0x0045 */
    "Number of Contour Points\0" /* 2099, 0x3006, 0x0046 */
    "Contour Data\0" /* 2100, 0x3006, 0x0050 */
    "RT ROI Observations Sequence\0" /* 2101, 0x3006, 0x0080 */
    "Observation Number\0" /* 2102, 0x3006, 0x0082 */
    "Referenced ROI Number\0" /* 2103, 0x3006, 0x0084 */
    "ROI Observation Label\0" /* 2104, 0x3006, 0x0085 */
    "RT ROI Identification Code Sequence\0" /* 2105, 0x3006, 0x0086 */
    "ROI Observation Description\0" /* 2106, 0x3006, 0x0088 */
    "Related RT ROI Observations Sequence\0" /* 2107, 0x3006, 0x00a0 */
    "RT ROI Interpreted Type\0" /* 2108, 0x3006, 0x00a4 */
    "ROI Interpreter\0" /* 2109, 0x3006, 0x00a6 */
    "ROI Physical Properties Sequence\0" /* 2110, 0x3006, 0x00b0 */
    "ROI Physical Property\0" /* 2111, 0x3006, 0x00b2 */
    "ROI Physical Property Value\0" /* 2112, 0x3006, 0x00b4 */
    "Frame of Reference Relationship Sequence\0" /* 2113, 0x3006, 0x00c0 */
    "Related Frame of Reference UID\0" /* 2114, 0x3006, 0x00c2 */
    "Frame of Reference Transformation Type\0" /* 2115, 0x3006, 0x00c4 */
    "Frame of Reference Transformation Matrix\0" /* 2116, 0x3006, 0x00c6 */
    "Frame of Reference Transformation Comment\0" /* 2117, 0x3006, 0x00c8 */
    "RT Plan Label\0" /* 2118, 0x300a, 0x0002 */
    "RT Plan Name\0" /* 2119, 0x300a, 0x0003 */
    "RT Plan Description\0" /* 2120, 0x300a, 0x0004 */
    "RT Plan Date\0" /* 2121, 0x300a, 0x0006 */
    "RT Plan Time\0" /* 2122, 0x300a, 0x0007 */
    "Treatment Protocols\0" /* 2123, 0x300a, 0x0009 */
    "Treatment Intent\0" /* 2124, 0x300a, 0x000a */
    "Treatment Sites\0" /* 2125, 0x300a, 0x000b */
    "RT Plan Geometry\0" /* 2126, 0x300a, 0x000c */
    "Prescription Description\0" /* 2127, 0x300a, 0x000e */
    "Dose ReferenceSequence\0" /* 2128, 0x300a, 0x0010 */
    "Dose ReferenceNumber\0" /* 2129, 0x300a, 0x0012 */
    "Dose Reference Structure Type\0" /* 2130, 0x300a, 0x0014 */
    "Dose ReferenceDescription\0" /* 2131, 0x300a, 0x0016 */
    "Dose Reference Point Coordinates\0" /* 2132, 0x300a, 0x0018 */
    "Nominal Prior Dose\0" /* 2133, 0x300a, 0x001a */
    "Dose Reference Type\0" /* 2134, 0x300a, 0x0020 */
    "Constraint Weight\0" /* 2135, 0x300a, 0x0021 */
    "Delivery Warning Dose\0" /* 2136, 0x300a, 0x0022 */
    "Delivery Maximum Dose\0" /* 2137, 0x300a, 0x0023 */
    "Target Minimum Dose\0" /* 2138, 0x300a, 0x0025 */
    "Target Prescription Dose\0" /* 2139, 0x300a, 0x0026 */
    "Target Maximum Dose\0" /* 2140, 0x300a, 0x0027 */
    "Target Underdose Volume Fraction\0" /* 2141, 0x300a, 0x0028 */
    "Organ at Risk Full-volume Dose\0" /* 2142, 0x300a, 0x002a */
    "Organ at Risk Limit Dose\0" /* 2143, 0x300a, 0x002b */
    "Organ at Risk Maximum Dose\0" /* 2144, 0x300a, 0x002c */
    "Organ at Risk Overdose Volume Fraction\0" /* 2145, 0x300a, 0x002d */
    "Tolerance Table Sequence\0" /* 2146, 0x300a, 0x0040 */
    "Tolerance Table Number\0" /* 2147, 0x300a, 0x0042 */
    "Tolerance Table Label\0" /* 2148, 0x300a, 0x0043 */
    "Gantry Angle Tolerance\0" /* 2149, 0x300a, 0x0044 */
    "Beam Limiting Device Angle Tolerance\0" /* 2150, 0x300a, 0x0046 */
    "Beam Limiting Device Tolerance Sequence\0" /* 2151, 0x300a, 0x0048 */
    "Beam Limiting Device Position Tolerance\0" /* 2152, 0x300a, 0x004a */
    "Patient Support Angle Tolerance\0" /* 2153, 0x300a, 0x004c */
    "Table Top Eccentric Angle Tolerance\0" /* 2154, 0x300a, 0x004e */
    "Table Top Vertical Position Tolerance\0" /* 2155, 0x300a, 0x0051 */
    "Table Top Longitudinal Position Tolerance\0" /* 2156, 0x300a, 0x0052 */
    "Table Top Lateral Position Tolerance\0" /* 2157, 0x300a, 0x0053 */
    "RT Plan Relationship\0" /* 2158, 0x300a, 0x0055 */
    "Fraction Group Sequence\0" /* 2159, 0x300a, 0x0070 */
    "Fraction Group Number\0" /* 2160, 0x300a, 0x0071 */
    "Number of Fractions Planned\0" /* 2161, 0x300a, 0x0078 */
    "Number of Fractions Per Day\0" /* 2162, 0x300a, 0x0079 */
    "Repeat Fraction Cycle Length\0" /* 2163, 0x300a, 0x007a */
    "Fraction Pattern\0" /* 2164, 0x300a, 0x007b */
    "Number of Beams\0" /* 2165, 0x300a, 0x0080 */
    "Beam Dose Specification Point\0" /* 2166, 0x300a, 0x0082 */
    "Beam Dose\0" /* 2167, 0x300a, 0x0084 */
    "Beam Meterset\0" /* 2168, 0x300a, 0x0086 */
    "Number of Brachy Application Setups\0" /* 2169, 0x300a, 0x00a0 */
    "Brachy Application Setup Dose Specification Point\0" /* 2170, 0x300a, 0x00a2 */
    "Brachy Application Setup Dose\0" /* 2171, 0x300a, 0x00a4 */
    "Beam Sequence\0" /* 2172, 0x300a, 0x00b0 */
    "Treatment Machine Name \0" /* 2173, 0x300a, 0x00b2 */
    "Primary Dosimeter Unit\0" /* 2174, 0x300a, 0x00b3 */
    "Source-Axis Distance\0" /* 2175, 0x300a, 0x00b4 */
    "Beam Limiting Device Sequence\0" /* 2176, 0x300a, 0x00b6 */
    "RT Beam Limiting Device Type\0" /* 2177, 0x300a, 0x00b8 */
    "Source to Beam Limiting Device Distance\0" /* 2178, 0x300a, 0x00ba */
    "Number of Leaf/Jaw Pairs\0" /* 2179, 0x300a, 0x00bc */
    "Leaf Position Boundaries\0" /* 2180, 0x300a, 0x00be */
    "Beam Number\0" /* 2181, 0x300a, 0x00c0 */
    "Beam Name\0" /* 2182, 0x300a, 0x00c2 */
    "Beam Description\0" /* 2183, 0x300a, 0x00c3 */
    "Beam Type\0" /* 2184, 0x300a, 0x00c4 */
    "Radiation Type\0" /* 2185, 0x300a, 0x00c6 */
    "Reference Image Number\0" /* 2186, 0x300a, 0x00c8 */
    "Planned Verification Image Sequence\0" /* 2187, 0x300a, 0x00ca */
    "Imaging Device Specific Acquisition Parameters\0" /* 2188, 0x300a, 0x00cc */
    "Treatment Delivery Type\0" /* 2189, 0x300a, 0x00ce */
    "Number of Wedges\0" /* 2190, 0x300a, 0x00d0 */
    "Wedge Sequence\0" /* 2191, 0x300a, 0x00d1 */
    "Wedge Number\0" /* 2192, 0x300a, 0x00d2 */
    "Wedge Type\0" /* 2193, 0x300a, 0x00d3 */
    "Wedge ID\0" /* 2194, 0x300a, 0x00d4 */
    "Wedge Angle\0" /* 2195, 0x300a, 0x00d5 */
    "Wedge Factor\0" /* 2196, 0x300a, 0x00d6 */
    "Wedge Orientation\0" /* 2197, 0x300a, 0x00d8 */
    "Source to Wedge Tray Distance\0" /* 2198, 0x300a, 0x00da */
    "Number of Compensators\0" /* 2199, 0x300a, 0x00e0 */
    "Material ID\0" /* 2200, 0x300a, 0x00e1 */
    "Total Compensator Tray Factor\0" /* 2201, 0x300a, 0x00e2 */
    "Compensator Sequence\0" /* 2202, 0x300a, 0x00e3 */
    "Compensator Number\0" /* 2203, 0x300a, 0x00e4 */
    "Compensator ID\0" /* 2204, 0x300a, 0x00e5 */
    "Source to Compensator Tray Distance\0" /* 2205, 0x300a, 0x00e6 */
    "Compensator Rows\0" /* 2206, 0x300a, 0x00e7 */
    "Compensator Columns\0" /* 2207, 0x300a, 0x00e8 */
    "Compensator Pixel Spacing\0" /* 2208, 0x300a, 0x00e9 */
    "Compensator Position\0" /* 2209, 0x300a, 0x00ea */
    "Compensator Transmission Data\0" /* 2210, 0x300a, 0x00eb */
    "Compensator Thickness Data\0" /* 2211, 0x300a, 0x00ec */
    "Number of Boli\0" /* 2212, 0x300a, 0x00ed */
    "Number of Blocks\0" /* 2213, 0x300a, 0x00f0 */
    "Total Block Tray Factor\0" /* 2214, 0x300a, 0x00f2 */
    "Block Sequence\0" /* 2215, 0x300a, 0x00f4 */
    "Block Tray ID\0" /* 2216, 0x300a, 0x00f5 */
    "Source to Block Tray Distance\0" /* 2217, 0x300a, 0x00f6 */
    "Block Type\0" /* 2218, 0x300a, 0x00f8 */
    "Block Divergence\0" /* 2219, 0x300a, 0x00fa */
    "Block Number\0" /* 2220, 0x300a, 0x00fc */
    "Block Name\0" /* 2221, 0x300a, 0x00fe */
    "Block Thickness\0" /* 2222, 0x300a, 0x0100 */
    "Block Transmission\0" /* 2223, 0x300a, 0x0102 */
    "Block Number of Points\0" /* 2224, 0x300a, 0x0104 */
    "Block Data\0" /* 2225, 0x300a, 0x0106 */
    "Applicator Sequence\0" /* 2226, 0x300a, 0x0107 */
    "Applicator ID\0" /* 2227, 0x300a, 0x0108 */
    "Applicator Type\0" /* 2228, 0x300a, 0x0109 */
    "Applicator Description\0" /* 2229, 0x300a, 0x010a */
    "Cumulative Dose Reference Coefficient\0" /* 2230, 0x300a, 0x010c */
    "Final Cumulative Meterset Weight\0" /* 2231, 0x300a, 0x010e */
    "Number of Control Points\0" /* 2232, 0x300a, 0x0110 */
    "Control Point Sequence\0" /* 2233, 0x300a, 0x0111 */
    "Control Point Index\0" /* 2234, 0x300a, 0x0112 */
    "Nominal Beam Energy\0" /* 2235, 0x300a, 0x0114 */
    "Dose Rate Set\0" /* 2236, 0x300a, 0x0115 */
    "Wedge Position Sequence\0" /* 2237, 0x300a, 0x0116 */
    "Wedge Position\0" /* 2238, 0x300a, 0x0118 */
    "Beam Limiting Device Position Sequence\0" /* 2239, 0x300a, 0x011a */
    "Leaf Jaw Positions\0" /* 2240, 0x300a, 0x011c */
    "Gantry Angle\0" /* 2241, 0x300a, 0x011e */
    "Gantry Rotation Direction\0" /* 2242, 0x300a, 0x011f */
    "Beam Limiting Device Angle\0" /* 2243, 0x300a, 0x0120 */
    "Beam Limiting Device Rotation Direction\0" /* 2244, 0x300a, 0x0121 */
    "Patient Support Angle\0" /* 2245, 0x300a, 0x0122 */
    "Patient Support Rotation Direction\0" /* 2246, 0x300a, 0x0123 */
    "Table Top Eccentric Axis Distance\0" /* 2247, 0x300a, 0x0124 */
    "Table Top Eccentric Angle\0" /* 2248, 0x300a, 0x0125 */
    "Table Top Eccentric Rotation Direction\0" /* 2249, 0x300a, 0x0126 */
    "Table Top Vertical Position\0" /* 2250, 0x300a, 0x0128 */
    "Table Top Longitudinal Position\0" /* 2251, 0x300a, 0x0129 */
    "Table Top Lateral Position\0" /* 2252, 0x300a, 0x012a */
    "Isocenter Position\0" /* 2253, 0x300a, 0x012c */
    "Surface Entry Point\0" /* 2254, 0x300a, 0x012e */
    "Source to Surface Distance\0" /* 2255, 0x300a, 0x0130 */
    "Cumulative Meterset Weight\0" /* 2256, 0x300a, 0x0134 */
    "Patient Setup Sequence\0" /* 2257, 0x300a, 0x0180 */
    "Patient Setup Number\0" /* 2258, 0x300a, 0x0182 */
    "Patient Additional Position\0" /* 2259, 0x300a, 0x0184 */
    "Fixation Device Sequence\0" /* 2260, 0x300a, 0x0190 */
    "Fixation Device Type\0" /* 2261, 0x300a, 0x0192 */
    "Fixation Device Label\0" /* 2262, 0x300a, 0x0194 */
    "Fixation Device Description\0" /* 2263, 0x300a, 0x0196 */
    "Fixation Device Position\0" /* 2264, 0x300a, 0x0198 */
    "Shielding Device Sequence\0" /* 2265, 0x300a, 0x01a0 */
    "Shielding Device Type\0" /* 2266, 0x300a, 0x01a2 */
    "Shielding Device Label\0" /* 2267, 0x300a, 0x01a4 */
    "Shielding Device Description\0" /* 2268, 0x300a, 0x01a6 */
    "Shielding Device Position\0" /* 2269, 0x300a, 0x01a8 */
    "Setup Technique\0" /* 2270, 0x300a, 0x01b0 */
    "Setup TechniqueDescription\0" /* 2271, 0x300a, 0x01b2 */
    "Setup Device Sequence\0" /* 2272, 0x300a, 0x01b4 */
    "Setup Device Type\0" /* 2273, 0x300a, 0x01b6 */
    "Setup Device Label\0" /* 2274, 0x300a, 0x01b8 */
    "Setup Device Description\0" /* 2275, 0x300a, 0x01ba */
    "Setup Device Parameter\0" /* 2276, 0x300a, 0x01bc */
    "Setup ReferenceDescription\0" /* 2277, 0x300a, 0x01d0 */
    "Table Top Vertical Setup Displacement\0" /* 2278, 0x300a, 0x01d2 */
    "Table Top Longitudinal Setup Displacement\0" /* 2279, 0x300a, 0x01d4 */
    "Table Top Lateral Setup Displacement\0" /* 2280, 0x300a, 0x01d6 */
    "Brachy Treatment Technique\0" /* 2281, 0x300a, 0x0200 */
    "Brachy Treatment Type\0" /* 2282, 0x300a, 0x0202 */
    "Treatment Machine Sequence\0" /* 2283, 0x300a, 0x0206 */
    "Source Sequence\0" /* 2284, 0x300a, 0x0210 */
    "Source Number\0" /* 2285, 0x300a, 0x0212 */
    "Source Type\0" /* 2286, 0x300a, 0x0214 */
    "Source Manufacturer\0" /* 2287, 0x300a, 0x0216 */
    "Active Source Diameter\0" /* 2288, 0x300a, 0x0218 */
    "Active Source Length\0" /* 2289, 0x300a, 0x021a */
    "Source Encapsulation Nominal Thickness\0" /* 2290, 0x300a, 0x0222 */
    "Source Encapsulation Nominal Transmission\0" /* 2291, 0x300a, 0x0224 */
    "Source IsotopeName\0" /* 2292, 0x300a, 0x0226 */
    "Source Isotope Half Life\0" /* 2293, 0x300a, 0x0228 */
    "Reference Air Kerma Rate\0" /* 2294, 0x300a, 0x022a */
    "Air Kerma Rate Reference Date\0" /* 2295, 0x300a, 0x022c */
    "Air Kerma Rate Reference Time\0" /* 2296, 0x300a, 0x022e */
    "Application Setup Sequence\0" /* 2297, 0x300a, 0x0230 */
    "Application Setup Type\0" /* 2298, 0x300a, 0x0232 */
    "Application Setup Number\0" /* 2299, 0x300a, 0x0234 */
    "Application Setup Name\0" /* 2300, 0x300a, 0x0236 */
    "Application Setup Manufacturer\0" /* 2301, 0x300a, 0x0238 */
    "Template Number\0" /* 2302, 0x300a, 0x0240 */
    "Template Type\0" /* 2303, 0x300a, 0x0242 */
    "Template Name\0" /* 2304, 0x300a, 0x0244 */
    "Total Reference Air Kerma\0" /* 2305, 0x300a, 0x0250 */
    "Brachy Accessory Device Sequence\0" /* 2306, 0x300a, 0x0260 */
    "Brachy Accessory Device Number\0" /* 2307, 0x300a, 0x0262 */
    "Brachy Accessory Device ID\0" /* 2308, 0x300a, 0x0263 */
    "Brachy Accessory Device Type\0" /* 2309, 0x300a, 0x0264 */
    "Brachy Accessory Device Name\0" /* 2310, 0x300a, 0x0266 */
    "Brachy Accessory Device Nominal Thickness\0" /* 2311, 0x300a, 0x026a */
    "Brachy Accessory Device Nominal Transmission\0" /* 2312, 0x300a, 0x026c */
    "Channel Sequence\0" /* 2313, 0x300a, 0x0280 */
    "Channel Number\0" /* 2314, 0x300a, 0x0282 */
    "Channel Length\0" /* 2315, 0x300a, 0x0284 */
    "Channel Total Time\0" /* 2316, 0x300a, 0x0286 */
    "Source Movement Type\0" /* 2317, 0x300a, 0x0288 */
    "Number of Pulses\0" /* 2318, 0x300a, 0x028a */
    "Pulse Repetition Interval\0" /* 2319, 0x300a, 0x028c */
    "Source Applicator Number\0" /* 2320, 0x300a, 0x0290 */
    "Source Applicator ID\0" /* 2321, 0x300a, 0x0291 */
    "Source Applicator Type\0" /* 2322, 0x300a, 0x0292 */
    "Source Applicator Name\0" /* 2323, 0x300a, 0x0294 */
    "Source Applicator Length\0" /* 2324, 0x300a, 0x0296 */
    "Source Applicator Manufacturer\0" /* 2325, 0x300a, 0x0298 */
    "Source Applicator Wall Nominal Thickness\0" /* 2326, 0x300a, 0x029c */
    "Source Applicator Wall Nominal Transmission\0" /* 2327, 0x300a, 0x029e */
    "Source Applicator Step Size\0" /* 2328, 0x300a, 0x02a0 */
    "Transfer Tube Number\0" /* 2329, 0x300a, 0x02a2 */
    "Transfer Tube Length\0" /* 2330, 0x300a, 0x02a4 */
    "Channel Shield Sequence\0" /* 2331, 0x300a, 0x02b0 */
    "Channel Shield Number\0" /* 2332, 0x300a, 0x02b2 */
    "Channel Shield ID\0" /* 2333, 0x300a, 0x02b3 */
    "Channel Shield Name\0" /* 2334, 0x300a, 0x02b4 */
    "Channel Shield Nominal Thickness\0" /* 2335, 0x300a, 0x02b8 */
    "Channel Shield Nominal Transmission\0" /* 2336, 0x300a, 0x02ba */
    "Final Cumulative Time Weight\0" /* 2337, 0x300a, 0x02c8 */
    "Brachy Control Point Sequence\0" /* 2338, 0x300a, 0x02d0 */
    "Control Point Relative Position\0" /* 2339, 0x300a, 0x02d2 */
    "Control Point 3D Position\0" /* 2340, 0x300a, 0x02d4 */
    "Cumulative Time Weight\0" /* 2341, 0x300a, 0x02d6 */
    "Referenced RT Plan Sequence\0" /* 2342, 0x300c, 0x0002 */
    "Referenced Beam Sequence\0" /* 2343, 0x300c, 0x0004 */
    "Referenced Beam Number\0" /* 2344, 0x300c, 0x0006 */
    "Referenced Reference Image Number\0" /* 2345, 0x300c, 0x0007 */
    "Start Cumulative Meterset Weight\0" /* 2346, 0x300c, 0x0008 */
    "End Cumulative Meterset Weight\0" /* 2347, 0x300c, 0x0009 */
    "Referenced Brachy Application Setup Sequence\0" /* 2348, 0x300c, 0x000a */
    "Referenced Brachy Application Setup Number\0" /* 2349, 0x300c, 0x000c */
    "Referenced Source Number\0" /* 2350, 0x300c, 0x000e */
    "Referenced Fraction Group Sequence\0" /* 2351, 0x300c, 0x0020 */
    "Referenced Fraction Group Number\0" /* 2352, 0x300c, 0x0022 */
    "Referenced Verification Image Sequence\0" /* 2353, 0x300c, 0x0040 */
    "Referenced Reference Image Sequence\0" /* 2354, 0x300c, 0x0042 */
    "Referenced Dose Reference Sequence\0" /* 2355, 0x300c, 0x0050 */
    "Referenced Dose Reference Number\0" /* 2356, 0x300c, 0x0051 */
    "Brachy Referenced Dose Reference Sequence\0" /* 2357, 0x300c, 0x0055 */
    "Referenced Structure Set Sequence\0" /* 2358, 0x300c, 0x0060 */
    "Referenced Patient Setup Number\0" /* 2359, 0x300c, 0x006a */
    "Referenced Dose Sequence\0" /* 2360, 0x300c, 0x0080 */
    "Referenced Tolerance Table Number\0" /* 2361, 0x300c, 0x00a0 */
    "Referenced Bolus Sequence\0" /* 2362, 0x300c, 0x00b0 */
    "Referenced Wedge Number\0" /* 2363, 0x300c, 0x00c0 */
    "Referenced Compensato rNumber\0" /* 2364, 0x300c, 0x00d0 */
    "Referenced Block Number\0" /* 2365, 0x300c, 0x00e0 */
    "Referenced Control Point\0" /* 2366, 0x300c, 0x00f0 */
    "Approval Status\0" /* 2367, 0x300e, 0x0002 */
    "Review Date\0" /* 2368, 0x300e, 0x0004 */
    "Review Time\0" /* 2369, 0x300e, 0x0005 */
    "Reviewer Name\0" /* 2370, 0x300e, 0x0008 */
    "Text Group Length\0" /* 2371, 0x4000, 0x0000 */
    "Text Arbitrary\0" /* 2372, 0x4000, 0x0010 */
    "Text Comments\0" /* 2373, 0x4000, 0x4000 */
    "Results Group Length\0" /* 2374, 0x4008, 0x0000 */
    "Results ID\0" /* 2375, 0x4008, 0x0040 */
    "Results ID Issuer\0" /* 2376, 0x4008, 0x0042 */
    "Referenced Interpretation Sequence\0" /* 2377, 0x4008, 0x0050 */
    "Report Production Status\0" /* 2378, 0x4008, 0x00ff */
    "Interpretation Recorded Date\0" /* 2379, 0x4008, 0x0100 */
    "Interpretation Recorded Time\0" /* 2380, 0x4008, 0x0101 */
    "Interpretation Recorder\0" /* 2381, 0x4008, 0x0102 */
    "Reference to Recorded Sound\0" /* 2382, 0x4008, 0x0103 */
    "Interpretation Transcription Date\0" /* 2383, 0x4008, 0x0108 */
    "Interpretation Transcription Time\0" /* 2384, 0x4008, 0x0109 */
    "Interpretation Transcriber\0" /* 2385, 0x4008, 0x010a */
    "Interpretation Text\0" /* 2386, 0x4008, 0x010b */
    "Interpretation Author\0" /* 2387, 0x4008, 0x010c */
    "Interpretation Approver Sequence\0" /* 2388, 0x4008, 0x0111 */
    "Interpretation Approval Date\0" /* 2389, 0x4008, 0x0112 */
    "Interpretation Approval Time\0" /* 2390, 0x4008, 0x0113 */
    "Physician Approving Interpretation\0" /* 2391, 0x4008, 0x0114 */
    "Interpretation Diagnosis Description\0" /* 2392, 0x4008, 0x0115 */
    "InterpretationDiagnosis Code Sequence\0" /* 2393, 0x4008, 0x0117 */
    "Results Distribution List Sequence\0" /* 2394, 0x4008, 0x0118 */
    "Distribution Name\0" /* 2395, 0x4008, 0x0119 */
    "Distribution Address\0" /* 2396, 0x4008, 0x011a */
    "Interpretation ID\0" /* 2397, 0x4008, 0x0200 */
    "Interpretation ID Issuer\0" /* 2398, 0x4008, 0x0202 */
    "Interpretation Type ID\0" /* 2399, 0x4008, 0x0210 */
    "Interpretation Status ID\0" /* 2400, 0x4008, 0x0212 */
    "Impressions\0" /* 2401, 0x4008, 0x0300 */
    "Results Comments\0" /* 2402, 0x4008, 0x4000 */
    "Report ID\0" /* 2403, 0x4009, 0x0001 */
    "Report Status\0" /* 2404, 0x4009, 0x0020 */
    "Report Creation Date\0" /* 2405, 0x4009, 0x0030 */
    "Report Approving Physician\0" /* 2406, 0x4009, 0x0070 */
    "Report Text\0" /* 2407, 0x4009, 0x00e0 */
    "Report Author\0" /* 2408, 0x4009, 0x00e1 */
    "Reporting Radiologist\0" /* 2409, 0x4009, 0x00e3 */
    "Curve Group Length\0" /* 2410, 0x5000, 0x0000 */
    "Curve Dimensions\0" /* 2411, 0x5000, 0x0005 */
    "Number of Points\0" /* 2412, 0x5000, 0x0010 */
    "Type of Data\0" /* 2413, 0x5000, 0x0020 */
    "Curve Description\0" /* 2414, 0x5000, 0x0022 */
    "Axis Units\0" /* 2415, 0x5000, 0x0030 */
    "Axis Labels\0" /* 2416, 0x5000, 0x0040 */
    "Data Value Representation\0" /* 2417, 0x5000, 0x0103 */
    "Minimum Coordinate Value\0" /* 2418, 0x5000, 0x0104 */
    "Maximum Coordinate Value\0" /* 2419, 0x5000, 0x0105 */
    "Curve Range\0" /* 2420, 0x5000, 0x0106 */
    "Curve Data Descriptor\0" /* 2421, 0x5000, 0x0110 */
    "Coordinate Start Value\0" /* 2422, 0x5000, 0x0112 */
    "Coordinate Step Value\0" /* 2423, 0x5000, 0x0114 */
    "Curve Activation Layer\0" /* 2424, 0x5000, 0x1001 */
    "Audio Type\0" /* 2425, 0x5000, 0x2000 */
    "Audio Sample Format\0" /* 2426, 0x5000, 0x2002 */
    "Number of Channels\0" /* 2427, 0x5000, 0x2004 */
    "Number of Samples\0" /* 2428, 0x5000, 0x2006 */
    "Sample Rate\0" /* 2429, 0x5000, 0x2008 */
    "Total Time\0" /* 2430, 0x5000, 0x200a */
    "Audio Sample Data\0" /* 2431, 0x5000, 0x200c */
    "Audio Comments\0" /* 2432, 0x5000, 0x200e */
    "Curve Label\0" /* 2433, 0x5000, 0x2500 */
    "CurveReferenced Overlay Sequence\0" /* 2434, 0x5000, 0x2600 */
    "CurveReferenced Overlay Group\0" /* 2435, 0x5000, 0x2610 */
    "Curve Data\0" /* 2436, 0x5000, 0x3000 */
    "Overlay Group Length\0" /* 2437, 0x6000, 0x0000 */
    "Gray Palette Color Lookup Table Descriptor\0" /* 2438, 0x6000, 0x0001 */
    "Gray Palette Color Lookup Table Data\0" /* 2439, 0x6000, 0x0002 */
    "Overlay Rows\0" /* 2440, 0x6000, 0x0010 */
    "Overlay Columns\0" /* 2441, 0x6000, 0x0011 */
    "Overlay Planes\0" /* 2442, 0x6000, 0x0012 */
    "Number of Frames in Overlay\0" /* 2443, 0x6000, 0x0015 */
    "Overlay Description\0" /* 2444, 0x6000, 0x0022 */
    "Overlay Type\0" /* 2445, 0x6000, 0x0040 */
    "Overlay Subtype\0" /* 2446, 0x6000, 0x0045 */
    "Overlay Origin\0" /* 2447, 0x6000, 0x0050 */
    "Image Frame Origin\0" /* 2448, 0x6000, 0x0051 */
    "Plane Origin\0" /* 2449, 0x6000, 0x0052 */
    "Overlay Compression Code\0" /* 2450, 0x6000, 0x0060 */
    "Overlay Compression Originator\0" /* 2451, 0x6000, 0x0061 */
    "Overlay Compression Label\0" /* 2452, 0x6000, 0x0062 */
    "Overlay Compression Description\0" /* 2453, 0x6000, 0x0063 */
    "Overlay Compression Step Pointers\0" /* 2454, 0x6000, 0x0066 */
    "Overlay Repeat Interval\0" /* 2455, 0x6000, 0x0068 */
    "Overlay Bits Grouped\0" /* 2456, 0x6000, 0x0069 */
    "Overlay Bits Allocated\0" /* 2457, 0x6000, 0x0100 */
    "Overlay Bit Position\0" /* 2458, 0x6000, 0x0102 */
    "Overlay Format\0" /* 2459, 0x6000, 0x0110 */
    "Overlay Location\0" /* 2460, 0x6000, 0x0200 */
    "Overlay Code Label\0" /* 2461, 0x6000, 0x0800 */
    "Overlay Number of Tables\0" /* 2462, 0x6000, 0x0802 */
    "Overlay Code Table Location\0" /* 2463, 0x6000, 0x0803 */
    "Overlay Bits For Code Word\0" /* 2464, 0x6000, 0x0804 */
    "Overlay Activation Layer\0" /* 2465, 0x6000, 0x1001 */
    "Overlay Descriptor - Gray\0" /* 2466, 0x6000, 0x1100 */
    "Overlay Descriptor - Red\0" /* 2467, 0x6000, 0x1101 */
    "Overlay Descriptor - Green\0" /* 2468, 0x6000, 0x1102 */
    "Overlay Descriptor - Blue\0" /* 2469, 0x6000, 0x1103 */
    "Overlays - Gray\0" /* 2470, 0x6000, 0x1200 */
    "Overlays - Red\0" /* 2471, 0x6000, 0x1201 */
    "Overlays - Green\0" /* 2472, 0x6000, 0x1202 */
    "Overlays - Blue\0" /* 2473, 0x6000, 0x1203 */
    "ROI Area\0" /* 2474, 0x6000, 0x1301 */
    "ROI Mean\0" /* 2475, 0x6000, 0x1302 */
    "ROI Standard Deviation\0" /* 2476, 0x6000, 0x1303 */
    "Overlay Label\0" /* 2477, 0x6000, 0x1500 */
    "Overlay Data\0" /* 2478, 0x6000, 0x3000 */
    "Overlay Comments\0" /* 2479, 0x6000, 0x4000 */
    "?\0" /* 2480, 0x6001, 0x0000 */
    "?\0" /* 2481, 0x6001, 0x0010 */
    "?\0" /* 2482, 0x6001, 0x1010 */
    "?\0" /* 2483, 0x6001, 0x1030 */
    "?\0" /* 2484, 0x6021, 0x0000 */
    "?\0" /* 2485, 0x6021, 0x0010 */
    "Dummy\0" /* 2486, 0x7001, 0x0010 */
    "Info\0" /* 2487, 0x7003, 0x0010 */
    "Dummy\0" /* 2488, 0x7005, 0x0010 */
    "TextAnnotation\0" /* 2489, 0x7000, 0x0004 */
    "Box\0" /* 2490, 0x7000, 0x0005 */
    "ArrowEnd\0" /* 2491, 0x7000, 0x0007 */
    "Pixel Data Group Length\0" /* 2492, 0x7fe0, 0x0000 */
    "Pixel Data\0" /* 2493, 0x7fe0, 0x0010 */
    "Coefficients SDVN\0" /* 2494, 0x7fe0, 0x0020 */
    "Coefficients SDHN\0" /* 2495, 0x7fe0, 0x0030 */
    "Coefficients SDDN\0" /* 2496, 0x7fe0, 0x0040 */
    "Pixel Data\0" /* 2497, 0x7fe1, 0x0010 */
    "Variable Pixel Data Group Length\0" /* 2498, 0x7f00, 0x0000 */
    "Variable Pixel Data\0" /* 2499, 0x7f00, 0x0010 */
    "Variable Next Data Group\0" /* 2500, 0x7f00, 0x0011 */
    "Variable Coefficients SDVN\0" /* 2501, 0x7f00, 0x0020 */
    "Variable Coefficients SDHN\0" /* 2502, 0x7f00, 0x0030 */
    "Variable Coefficients SDDN\0" /* 2503, 0x7f00, 0x0040 */
    "Binary Data\0" /* 2504, 0x7fe1, 0x0000 */
    "Image Graphics Format Code\0" /* 2505, 0x7fe3, 0x0000 */
    "Image Graphics\0" /* 2506, 0x7fe3, 0x0010 */
    "Image Graphics Dummy\0" /* 2507, 0x7fe3, 0x0020 */
    "?\0" /* 2508, 0x7ff1, 0x0001 */
    "?\0" /* 2509, 0x7ff1, 0x0002 */
    "?\0" /* 2510, 0x7ff1, 0x0003 */
    "?\0" /* 2511, 0x7ff1, 0x0004 */
    "?\0" /* 2512, 0x7ff1, 0x0005 */
    "?\0" /* 2513, 0x7ff1, 0x0007 */
    "?\0" /* 2514, 0x7ff1, 0x0008 */
    "?\0" /* 2515, 0x7ff1, 0x0009 */
    "?\0" /* 2516, 0x7ff1, 0x000a */
    "?\0" /* 2517, 0x7ff1, 0x000b */
    "?\0" /* 2518, 0x7ff1, 0x000c */
    "?\0" /* 2519, 0x7ff1, 0x000d */
    "?\0" /* 2520, 0x7ff1, 0x0010 */
    "Data Set Trailing Padding\0" /* 2521, 0xfffc, 0xfffc */
    "Item\0" /* 2522, 0xfffe, 0xe000 */
    "Item Delimitation Item\0" /* 2523, 0xfffe, 0xe00d */
    "Sequence Delimitation Item\0" /* 2524, 0xfffe, 0xe0dd */
    "\0"; /* 2525, 0xffff, 0xffff */
#endif /* DESCRIPION_STR */

static const char *DCM_Get_Description(const unsigned int index)
{
#if DESCRIPION_STR
    size_t count;
    const char *p = dicom_descriptions;
    for (count = 0;
         (count < index) && (p < dicom_descriptions+sizeof(dicom_descriptions)-1);
         p++)
    {
        if (*p == '\0')
          count++;
    }
    return p;
#else
    return dicom_info[index].description;
#endif
}
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s D C M                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsDCM returns True if the image format type, identified by the
%  magick string, is DCM.
%
%  The format of the ReadDCMImage method is:
%
%      unsigned int IsDCM(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsDCM returns True if the image format type is DCM.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static MagickPassFail IsDCM(const unsigned char *magick,const size_t length)
{
  if (length < 132)
    return(False);
  if (LocaleNCompare((char *) (magick+128),"DICM",4) == 0)
    return(True);
  return(False);
}

static MagickPassFail DCM_InitDCM(DicomStream *dcm,int verbose)
{
  (void) memset(dcm,0,sizeof(*dcm));
  dcm->columns=0;
  dcm->rows=0;
  dcm->samples_per_pixel=1;
  dcm->bits_allocated=8;
  dcm->significant_bits=0;
  dcm->high_bit=0;
  dcm->bytes_per_pixel=1;
  dcm->max_value_in=255;
  dcm->max_value_out=255;
  dcm->pixel_representation=0;
  dcm->transfer_syntax=DCM_TS_IMPL_LITTLE;
  dcm->interlace=0;
  dcm->msb_state=DCM_MSB_LITTLE;
  dcm->phot_interp=DCM_PI_MONOCHROME2;
  dcm->window_center=0;
  dcm->window_width=0;
  dcm->rescale_intercept=0;
  dcm->rescale_slope=1;
  dcm->number_scenes=1;
  dcm->data=NULL;
  dcm->upper_lim=0;
  dcm->lower_lim=0;
  dcm->rescale_map=NULL;
  dcm->rescale_type=DCM_RT_HOUNSFIELD;
  dcm->rescaling=DCM_RS_NONE;
  dcm->offset_ct=0;
  dcm->offset_arr=NULL;
  dcm->frag_bytes=0;
  dcm->rle_rep_ct=0;
#if defined(USE_GRAYMAP)
  dcm->graymap=(unsigned short *) NULL;
#endif
  dcm->funcReadShort=ReadBlobLSBShort;
  dcm->funcReadLong=ReadBlobLSBLong;
  dcm->explicit_file=False;
  dcm->verbose=verbose;

  return MagickPass;
}

static void DCM_DestroyDCM(DicomStream *dcm)
{
  MagickFreeMemory(dcm->offset_arr);
  MagickFreeMemory(dcm->data);
#if defined(USE_GRAYMAP)
  MagickFreeMemory(dcm->graymap);
#endif
  MagickFreeMemory(dcm->rescale_map);
}

/*
  Parse functions for DICOM elements
*/
static MagickPassFail funcDCM_TransferSyntax(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  char
    *p;

  int
    type,
    subtype;

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  p=(char *) dcm->data;
  if (strncmp(p,"1.2.840.10008.1.2",17) == 0)
    {
      if (*(p+17) == 0)
        {
          dcm->transfer_syntax = DCM_TS_IMPL_LITTLE;
          return MagickPass;
        }
      type=0;
      subtype=0;
      /* Subtype is not always provided, but insist on type */
      if (sscanf(p+17,".%d.%d",&type,&subtype) < 1)
        {
          ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
          return MagickFail;
        }
      switch (type)
        {
        case 1:
          dcm->transfer_syntax = DCM_TS_EXPL_LITTLE;
          break;
        case 2:
          dcm->transfer_syntax = DCM_TS_EXPL_BIG;
          dcm->msb_state=DCM_MSB_BIG_PENDING;
          break;
        case 4:
          if ((subtype >= 80) && (subtype <= 81))
            dcm->transfer_syntax = DCM_TS_JPEG_LS;
          else
          if ((subtype >= 90) && (subtype <= 93))
            dcm->transfer_syntax = DCM_TS_JPEG_2000;
          else
            dcm->transfer_syntax = DCM_TS_JPEG;
          break;
        case 5:
          dcm->transfer_syntax = DCM_TS_RLE;
          break;
        }
    }
  return MagickPass;
}

static MagickPassFail funcDCM_StudyDate(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);

  (void) SetImageAttribute(image,"StudyDate",(char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_PatientName(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);

  (void) SetImageAttribute(image,"PatientName",(char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_TriggerTime(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);

  (void) SetImageAttribute(image,"TriggerTime",(char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_FieldOfView(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);

  (void) SetImageAttribute(image,"FieldOfView",(char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_SeriesNumber(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);
  (void) SetImageAttribute(image,"SeriesNumber",(char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_ImagePosition(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);
  (void) SetImageAttribute(image,"ImagePosition",(char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_ImageOrientation(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);
  (void) SetImageAttribute(image,"ImageOrientation",(char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_SliceLocation(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);
  (void) SetImageAttribute(image,"SliceLocation",(char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_SamplesPerPixel(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);
  dcm->samples_per_pixel=dcm->datum;
  return MagickPass;
}

static MagickPassFail funcDCM_PhotometricInterpretation(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  char photometric[MaxTextExtent];
  unsigned int i;

  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  (void) memset(photometric,0,sizeof(photometric));
  for (i=0; i < Min(dcm->length, MaxTextExtent-1); i++)
    photometric[i]=dcm->data[i];
  photometric[i]='\0';

  if (strncmp(photometric,"MONOCHROME1",11) == 0)
    dcm->phot_interp = DCM_PI_MONOCHROME1;
  else
    if (strncmp(photometric,"MONOCHROME2",11) == 0)
      dcm->phot_interp = DCM_PI_MONOCHROME2;
    else
      if (strncmp(photometric,"PALETTE COLOR",13) == 0)
        dcm->phot_interp = DCM_PI_PALETTE_COLOR;
      else
        if (strncmp(photometric,"RGB",3) == 0)
          dcm->phot_interp = DCM_PI_RGB;
        else
          dcm->phot_interp = DCM_PI_OTHER;
  return MagickPass;
}

static MagickPassFail funcDCM_PlanarConfiguration(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  dcm->interlace=dcm->datum;
  return MagickPass;
}

static MagickPassFail funcDCM_NumberOfFrames(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  dcm->number_scenes=MagickAtoI((char *) dcm->data);
  return MagickPass;
}

static MagickPassFail funcDCM_Rows(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  dcm->rows=dcm->datum;
  return MagickPass;
}

static MagickPassFail funcDCM_Columns(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  dcm->columns=dcm->datum;
  return MagickPass;
}

static MagickPassFail funcDCM_BitsAllocated(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  dcm->bits_allocated=dcm->datum;
  dcm->bytes_per_pixel=1;
  if (dcm->datum > 8)
    dcm->bytes_per_pixel=2;
  return MagickPass;
}

static MagickPassFail funcDCM_BitsStored(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(exception);

  dcm->significant_bits=dcm->datum;
  dcm->bytes_per_pixel=1;
  if ((dcm->significant_bits == 0U) || (dcm->significant_bits > 16U))
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "DICOM significant_bits = %u",
                              dcm->significant_bits);
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }
  if (dcm->significant_bits > 8)
    dcm->bytes_per_pixel=2;
  dcm->max_value_in=MaxValueGivenBits(dcm->significant_bits);
  dcm->max_value_out=dcm->max_value_in;
  image->depth=Min(dcm->significant_bits,QuantumDepth);
  return MagickPass;
}

static MagickPassFail funcDCM_HighBit(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  dcm->high_bit=dcm->datum;
  return MagickPass;
}

static MagickPassFail funcDCM_PixelRepresentation(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  dcm->pixel_representation=dcm->datum;
  return MagickPass;
}

static MagickPassFail funcDCM_WindowCenter(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  char
    *p;

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  p = strrchr((char *) dcm->data,'\\');
  if (p)
    p++;
  else
    p=(char *) dcm->data;
  dcm->window_center=MagickAtoF(p);
  return MagickPass;
}

static MagickPassFail funcDCM_WindowWidth(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  char
    *p;

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  p = strrchr((char *) dcm->data,'\\');
  if (p)
    p++;
  else
    p=(char *) dcm->data;
  dcm->window_width=MagickAtoF(p);
  return MagickPass;
}

static MagickPassFail funcDCM_RescaleIntercept(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  char
    *p;

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  p = strrchr((char *) dcm->data,'\\');
  if (p)
    p++;
  else
    p=(char *) dcm->data;
  dcm->rescale_intercept=MagickAtoF(p);
  return MagickPass;
}

static MagickPassFail funcDCM_RescaleSlope(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  char
    *p;

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  p = strrchr((char *) dcm->data,'\\');
  if (p)
    p++;
  else
    p=(char *) dcm->data;
  dcm->rescale_slope=MagickAtoF(p);
  return MagickPass;
}

static MagickPassFail funcDCM_RescaleType(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  if (strncmp((char *) dcm->data,"OD",2) == 0)
    dcm->rescale_type=DCM_RT_OPTICAL_DENSITY;
  else if (strncmp((char *) dcm->data,"HU",2) == 0)
    dcm->rescale_type=DCM_RT_HOUNSFIELD;
  else if (strncmp((char *) dcm->data,"US",2) == 0)
    dcm->rescale_type=DCM_RT_UNSPECIFIED;
  else
    dcm->rescale_type=DCM_RT_UNKNOWN;
  return MagickPass;
}

static MagickPassFail funcDCM_PaletteDescriptor(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  /*
    Palette descriptor tables
    element = 1101/2/3 = for red/green/blue palette
    val 0 = # of entries in LUT (0 for 65535)
    val 1 = min pix value in palette (ie pix <= val1 -> palette[0])
    val 2 = # bits in LUT (8 or 16)
    NB Required by specification to be the same for each color

    #1 - check the same each time
    #2 - use scale_remap to map vals <= (val1) to first entry
    and vals >= (val1 + palette size) to last entry
    #3 - if (val2) == 8, use UINT8 values instead of UINT16
    #4 - Check for UINT8 values packed into low bits of UINT16
    entries as per spec
  */
  ARG_NOT_USED(image);
  ARG_NOT_USED(dcm);
  ARG_NOT_USED(exception);

  return MagickPass;
}

static MagickPassFail funcDCM_LUT(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
#if defined(USE_GRAYMAP)
  /*
    1200 = grey, LUT data 3006 = LUT data
  */
  unsigned long
    colors;

  register unsigned long
    i;

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  colors=dcm->length/dcm->bytes_per_pixel;
  dcm->datum=(long) colors;
  dcm->graymap=MagickAllocateArray(unsigned short *,colors,sizeof(unsigned short));
  if (dcm->graymap == (unsigned short *) NULL)
    {
      ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,image->filename);
      return MagickFail;
    }
  for (i=0; i < (long) colors; i++)
    if (dcm->bytes_per_pixel == 1)
      dcm->graymap[i]=dcm->data[i];
    else
      dcm->graymap[i]=(unsigned short) ((short *) dcm->data)[i];
#else
  ARG_NOT_USED(image);
  ARG_NOT_USED(dcm);
  ARG_NOT_USED(exception);
#endif
  return MagickPass;
}

static MagickPassFail funcDCM_Palette(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  register long
    i;

  unsigned char
    *p;

  unsigned short
    index;

  if (dcm->data == (unsigned char *) NULL)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Palette with %" MAGICK_SIZE_T_F "u entries...",
                          (MAGICK_SIZE_T) dcm->length);
  /*
    Initialize colormap (entries are always 16 bit)
    1201/2/3 = red/green/blue palette
  */
  if (image->colormap == (PixelPacket *) NULL)
    {
      /*
        Allocate color map first time in
      */
      if (!AllocateImageColormap(image,(const unsigned long) dcm->length))
        {
          ThrowException(exception,ResourceLimitError,UnableToCreateColormap,image->filename);
          return MagickFail;
        }
    }

  /*
    Check that palette size matches previous one(s)
  */
  if (dcm->length != image->colors)
    {
      ThrowException(exception,ResourceLimitError,UnableToCreateColormap,image->filename);
      return MagickFail;
    }

  p=dcm->data;
  for (i=0; i < (long) image->colors; i++)
    {
      if (dcm->msb_state == DCM_MSB_BIG)
        index=((unsigned short) *p << 8) | (unsigned short) *(p+1);
      else
        index=(unsigned short) *p | ((unsigned short) *(p+1) << 8);
      if (dcm->element == 0x1201)
        image->colormap[i].red=ScaleShortToQuantum(index);
      else if (dcm->element == 0x1202)
        image->colormap[i].green=ScaleShortToQuantum(index);
      else
        image->colormap[i].blue=ScaleShortToQuantum(index);
      p+=2;
    }
  return MagickPass;
}

static magick_uint8_t DCM_RLE_ReadByte(Image *image, DicomStream *dcm)
{
  if (dcm->rle_rep_ct == 0)
    {
      int
        rep_ct,
        rep_char;

      /* We need to read the next command pair */
      if (dcm->frag_bytes <= 2)
        dcm->frag_bytes = 0;
      else
        dcm->frag_bytes -= 2;

      rep_ct=ReadBlobByte(image);
      rep_char=ReadBlobByte(image);
      if (rep_ct == 128)
        {
          /* Illegal value */
          return 0;
        }
      else
      if (rep_ct < 128)
        {
          /* (rep_ct+1) literal bytes */
          dcm->rle_rep_ct=rep_ct;
          dcm->rle_rep_char=-1;
          return (magick_uint8_t)rep_char;
        }
      else
        {
          /* (257-rep_ct) repeated bytes */
          dcm->rle_rep_ct=256-rep_ct;
          dcm->rle_rep_char=rep_char;
          return (magick_uint8_t)rep_char;
        }
    }

  dcm->rle_rep_ct--;
  if (dcm->rle_rep_char >= 0)
    return dcm->rle_rep_char;

  if (dcm->frag_bytes > 0)
    dcm->frag_bytes--;
  return ReadBlobByte(image);
}

static magick_uint16_t DCM_RLE_ReadShort(Image *image, DicomStream *dcm)
{
  return (((magick_uint16_t) DCM_RLE_ReadByte(image,dcm) << 4) |
          (magick_uint16_t) DCM_RLE_ReadByte(image,dcm));
}

static MagickPassFail DCM_ReadElement(Image *image, DicomStream *dcm,ExceptionInfo *exception)
{
  unsigned int
    use_explicit;

  char
    explicit_vr[MaxTextExtent],
    implicit_vr[MaxTextExtent];

  register long
    i;

  /*
    Read group and element IDs
  */
  image->offset=(long) TellBlob(image);
  dcm->group=dcm->funcReadShort(image);
  if ((dcm->msb_state == DCM_MSB_BIG_PENDING) && (dcm->group != 2))
    {
      dcm->group = (dcm->group << 8) | (dcm->group >> 8);
      dcm->funcReadShort=ReadBlobMSBShort;
      dcm->funcReadLong=ReadBlobMSBLong;
      dcm->msb_state=DCM_MSB_BIG;
    }
  dcm->element=dcm->funcReadShort(image);
  dcm->data=(unsigned char *) NULL;
  dcm->quantum=0;
  if (EOFBlob(image))
    {
      ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
      return MagickFail;
    }
  /*
    Find corresponding VR for this group and element.
  */
  for (i=0; dicom_info[i].group < 0xffffU; i++)
    if ((dcm->group == dicom_info[i].group) &&
        (dcm->element == dicom_info[i].element))
      break;
  dcm->index=i;

  /*
    Check for "explicitness", but meta-file headers always explicit.
  */
  if (ReadBlob(image,2,(char *) explicit_vr) != 2)
    {
      ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
      return MagickFail;
    }
  explicit_vr[2]='\0';
  (void) strlcpy(implicit_vr,dicom_info[dcm->index].vr,MaxTextExtent);

#if defined(NEW_IMPLICIT_LOGIC)
  use_explicit=False;
  if (isupper((int) *explicit_vr) && isupper((int) *(explicit_vr+1)))
    {
      /* Explicit VR looks to be valid */
      if (strcmp(explicit_vr,implicit_vr) == 0)
        {
          /* Explicit VR matches implicit VR so assume that it is explicit */
          use_explicit=True;
        }
      else if ((dcm->group & 1) || strcmp(implicit_vr,"xs") == 0)
        {
          /*
            We *must* use explicit type under two conditions
            1) group is odd and therefore private
            2) element vr is set as "xs" ie is not of a fixed type
          */
          use_explicit=True;
          strcpy(implicit_vr,explicit_vr);
        }
    }
  if ((!use_explicit) || (strcmp(implicit_vr,"!!") == 0))
    {
      /* Use implicit logic */
      (void) SeekBlob(image,(ExtendedSignedIntegralType) -2,SEEK_CUR);
      dcm->quantum=4;
    }
  else
    {
      /* Use explicit logic */
      dcm->quantum=2;
      if ((strcmp(explicit_vr,"OB") == 0) ||
          (strcmp(explicit_vr,"OW") == 0) ||
          (strcmp(explicit_vr,"OF") == 0) ||
          (strcmp(explicit_vr,"SQ") == 0) ||
          (strcmp(explicit_vr,"UN") == 0) ||
          (strcmp(explicit_vr,"UT") == 0))
        {
          (void) dcm->funcReadShort(image);
          if (EOFBlob(image))
            {
              ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
              return MagickFail;
            }
          dcm->quantum=4;
        }
    }
#else
  if (!dcm->explicit_file && (dcm->group != 0x0002))
    dcm->explicit_file=isupper((int) *explicit_vr) && isupper((int) *(explicit_vr+1));
  use_explicit=((dcm->group == 0x0002) || dcm->explicit_file);
  if (use_explicit && (strcmp(implicit_vr,"xs") == 0))
    (void) strlcpy(implicit_vr,explicit_vr,MaxTextExtent);
  if (!use_explicit || (strcmp(implicit_vr,"!!") == 0))
    {
      (void) SeekBlob(image,(ExtendedSignedIntegralType) -2,SEEK_CUR);
      dcm->quantum=4;
    }
  else
    {
      /*
        Assume explicit type.
      */
      dcm->quantum=2;
      if ((strcmp(explicit_vr,"OB") == 0) ||
          (strcmp(explicit_vr,"UN") == 0) ||
          (strcmp(explicit_vr,"OW") == 0) || (strcmp(explicit_vr,"SQ") == 0))
        {
          (void) dcm->funcReadShort(image)
            if (EOFBlob(image))
              {
                ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
                return MagickFail;
              }
          dcm->quantum=4;
        }
    }
#endif

  dcm->datum=0;
  if (dcm->quantum == 4)
    {
      dcm->datum=dcm->funcReadLong(image);
      if (EOFBlob(image))
        {
          ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
          return MagickFail;
        }
    }
  else if (dcm->quantum == 2)
    {
      dcm->datum=(long) dcm->funcReadShort(image);
      if (EOFBlob(image))
        {
          ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
          return MagickFail;
        }
    }
  dcm->quantum=0;
  dcm->length=1;
  if (dcm->datum != 0)
    {
      if ((strcmp(implicit_vr,"SS") == 0) ||
          (strcmp(implicit_vr,"US") == 0) ||
          (strcmp(implicit_vr,"OW") == 0))
        dcm->quantum=2;
      else if ((strcmp(implicit_vr,"UL") == 0) ||
              (strcmp(implicit_vr,"SL") == 0) ||
              (strcmp(implicit_vr,"FL") == 0) ||
              (strcmp(implicit_vr,"OF") == 0))
        dcm->quantum=4;
      else  if (strcmp(implicit_vr,"FD") == 0)
        dcm->quantum=8;
      else
        dcm->quantum=1;

      if (dcm->datum != -1)
        {
          dcm->length=(size_t) dcm->datum/dcm->quantum;
        }
      else
        {
          /*
            Sequence and item of undefined length.
          */
          dcm->quantum=0;
          dcm->length=0;
        }
    }
  /*
    Display Dicom info.
  */
  if (dcm->verbose)
    {
      const char * description;
      if (!use_explicit)
        explicit_vr[0]='\0';
      (void) fprintf(stdout,"0x%04lX %4lu %.1024s-%.1024s (0x%04x,0x%04x)",
                     image->offset,(unsigned long) dcm->length,implicit_vr,explicit_vr,
                     dcm->group,dcm->element);
      if ((description=DCM_Get_Description(dcm->index)) != (char *) NULL)
          (void) fprintf(stdout," %.1024s",description);
      (void) fprintf(stdout,": ");
    }
  if ((dcm->group == 0x7FE0) && (dcm->element == 0x0010))
    {
      if (dcm->verbose)
        (void) fprintf(stdout,"\n");
      return MagickPass;
    }
  /*
    Allocate array and read data into it
  */
  if ((dcm->length == 1) && (dcm->quantum == 1))
    {
      if ((dcm->datum=ReadBlobByte(image)) == EOF)
        {
          ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
          return MagickFail;
        }
    }
  else if ((dcm->length == 1) && (dcm->quantum == 2))
    {
      dcm->datum=dcm->funcReadShort(image);
      if (EOFBlob(image))
        {
          ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
          return MagickFail;
        }
    }
  else if ((dcm->length == 1) && (dcm->quantum == 4))
    {
      dcm->datum=dcm->funcReadLong(image);
      if (EOFBlob(image))
        {
          ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
          return MagickFail;
        }
    }
  else if ((dcm->quantum != 0) && (dcm->length != 0))
    {
      size_t
        size;

      if (dcm->length > ((size_t) GetBlobSize(image)))
        {
          ThrowException(exception,CorruptImageError,InsufficientImageDataInFile,image->filename);
          return MagickFail;
        }
      if (dcm->length > ((~0UL)/dcm->quantum))
        {
          ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
          return MagickFail;
        }
      dcm->data=MagickAllocateArray(unsigned char *,(dcm->length+1),dcm->quantum);
      if (dcm->data == (unsigned char *) NULL)
        {
          ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,image->filename);
          return MagickFail;
        }
      size=MagickArraySize(dcm->quantum,dcm->length);
      if (size == 0)
        {
          ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
          return MagickFail;
        }
      if (ReadBlob(image,size,(char *) dcm->data) != size)
        {
          ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
          return MagickFail;
        }
      dcm->data[size]=0;
    }

  if (dcm->verbose)
    {
      /*
        Display data
      */
      if (dcm->data == (unsigned char *) NULL)
        {
          (void) fprintf(stdout,"%d\n",dcm->datum);
        }
      else
        {
          for (i=0; i < (long) Max(dcm->length,4); i++)
            if (!isprint(dcm->data[i]))
              break;
          if ((i != (long) dcm->length) && (dcm->length <= 4))
            {
              long
                j,
                bin_datum;

              bin_datum=0;
              for (j=(long) dcm->length-1; j >= 0; j--)
                bin_datum=256*bin_datum+dcm->data[j];
              (void) fprintf(stdout,"%lu\n",bin_datum);
            }
          else
            {
              for (i=0; i < (long) dcm->length; i++)
                if (isprint(dcm->data[i]))
                  (void) fprintf(stdout,"%c",dcm->data[i]);
                else
                  (void) fprintf(stdout,"%c",'.');
              (void) fprintf(stdout,"\n");
            }
        }
    }
  return MagickPass;
}

static MagickPassFail DCM_SetupColormap(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  if ((image->previous) && (image->previous->colormap != (PixelPacket*)NULL))
    {
      size_t
        length;

      /*
        Clone colormap from previous image
      */
      image->storage_class=PseudoClass;
      image->colors=image->previous->colors;
      length=image->colors*sizeof(PixelPacket);
      image->colormap=MagickAllocateMemory(PixelPacket *,length);
      if (image->colormap == (PixelPacket *) NULL)
        {
          ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,image->filename);
          return MagickFail;
        }
      (void) memcpy(image->colormap,image->previous->colormap,length);
    }
  else
    {
      /*
        Create new colormap
      */
      if (AllocateImageColormap(image,dcm->max_value_out+1) == MagickFail)
        {
          ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,image->filename);
          return MagickFail;
        }
    }
  return MagickPass;
}

static MagickPassFail DCM_SetupRescaleMap(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  /*
    rescale_map maps input sample range -> output colormap range combining rescale
    and window transforms, palette scaling and palette inversion (for MONOCHROME1)
    as well as allowing for pixel_representation of 1 which causes input samples to
    be treated as signed
  */
  double
    win_center,
    win_width,
    Xr,
    Xw_min,
    Xw_max;

  unsigned int
    i;

  if (dcm->rescaling == DCM_RS_NONE)
    return MagickPass;

  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Set up rescale map for input range of %u"
                          " (%u entries)...",
                          dcm->max_value_in+1,MaxMap+1);

  /*
    The rescale map must be limited to MaxMap+1 entries, which is 256
    or 65536, depending on QuantumDepth.  Using a QuantumDepth less
    than 16 for DICOM is a bad idea.

    The dcm->significant_bits value is limited to 16 (larger values
    are outright rejected) so dcm->max_value_in and dcm->max_value_out
    are limited to 65535.
  */

  if (dcm->rescale_map == (Quantum *) NULL)
    {
      size_t num_entries = Max(MaxMap+1,dcm->max_value_in+1);
      dcm->rescale_map=MagickAllocateArray(Quantum *,num_entries,sizeof(Quantum));
      if (dcm->rescale_map == NULL)
        {
          ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,image->filename);
          return MagickFail;
        }
      (void) memset(dcm->rescale_map,0,num_entries*sizeof(Quantum));
    }

  if (dcm->window_width == 0)
    { /* zero window width */
      if (dcm->upper_lim > dcm->lower_lim)
        {
          /* Use known range within image */
          win_width=(dcm->upper_lim-dcm->lower_lim+1)*dcm->rescale_slope;
          win_center=((dcm->upper_lim+dcm->lower_lim)/2)*dcm->rescale_slope+dcm->rescale_intercept;
        }
      else
        {
          /* Use full sample range and hope for the best */
          win_width=(dcm->max_value_in+1)*dcm->rescale_slope;
          if (dcm->pixel_representation == 1)
            win_center=dcm->rescale_intercept;
          else
            win_center=win_width/2 + dcm->rescale_intercept;
        }
    }
  else
    {
      win_width=dcm->window_width;
      win_center=dcm->window_center;
    }
  Xw_min = win_center - 0.5 - ((win_width-1)/2);
  Xw_max = win_center - 0.5 + ((win_width-1)/2);
  for (i=0; i < (dcm->max_value_in+1); i++)
    {
      if ((dcm->pixel_representation == 1) && (i >= MaxValueGivenBits(dcm->significant_bits)))
        Xr = -((dcm->max_value_in+1-i) * dcm->rescale_slope) + dcm->rescale_intercept;
      else
        Xr = (i * dcm->rescale_slope) + dcm->rescale_intercept;
      if (Xr <= Xw_min)
        dcm->rescale_map[i]=0;
      else if (Xr >= Xw_max)
        dcm->rescale_map[i]=dcm->max_value_out;
      else
        dcm->rescale_map[i]=(Quantum)(((Xr-Xw_min)/(win_width-1))*dcm->max_value_out+0.5);
    }
  if (dcm->phot_interp == DCM_PI_MONOCHROME1)
    for (i=0; i <= dcm->max_value_in; i++)
      dcm->rescale_map[i]=dcm->max_value_out-dcm->rescale_map[i];

  return MagickPass;
}

void DCM_SetRescaling(DicomStream *dcm,int avoid_scaling)
{
  /*
    If avoid_scaling is True then scaling will only be applied where necessary ie
    input bit depth exceeds quantum size.

    ### TODO : Should this throw an error rather than setting DCM_RS_PRE?
  */
  dcm->rescaling=DCM_RS_NONE;
  dcm->max_value_out=dcm->max_value_in;

  if (dcm->phot_interp == DCM_PI_PALETTE_COLOR)
    {
      if (dcm->max_value_in >= MaxColormapSize)
        {
          dcm->max_value_out=MaxColormapSize-1;
          dcm->rescaling=DCM_RS_PRE;
        }
      return;
    }

  if ((dcm->phot_interp == DCM_PI_MONOCHROME1) ||
      (dcm->phot_interp == DCM_PI_MONOCHROME2))
    {
      if ((dcm->transfer_syntax == DCM_TS_JPEG) ||
          (dcm->transfer_syntax == DCM_TS_JPEG_LS) ||
          (dcm->transfer_syntax == DCM_TS_JPEG_2000))
        {
          /* Encapsulated non-native grayscale images are post rescaled by default */
          if (!avoid_scaling)
            dcm->rescaling=DCM_RS_POST;
        }
#if defined(GRAYSCALE_USES_PALETTE)
      else if (dcm->max_value_in >= MaxColormapSize)
        {
          dcm->max_value_out=MaxColormapSize-1;
          dcm->rescaling=DCM_RS_PRE;
        }
#else
      else if (dcm->max_value_in > MaxRGB)
        {
          dcm->max_value_out=MaxRGB;
          dcm->rescaling=DCM_RS_PRE;
        }
#endif
      else if (!avoid_scaling)
        {
#if !defined(GRAYSCALE_USES_PALETTE)
          dcm->max_value_out=MaxRGB;
#endif
          dcm->rescaling=DCM_RS_POST;
        }
      return;
    }

  if (avoid_scaling || (dcm->max_value_in == MaxRGB))
    return;

  dcm->max_value_out=MaxRGB;
  dcm->rescaling=DCM_RS_PRE;
}

/*
  FIXME: This code is totally broken since DCM_SetupRescaleMap
  populates dcm->rescale_map and dcm->rescale_map has
  dcm->max_value_in+1 entries, which has nothing to do with the number
  of colormap entries or the range of MaxRGB.

  Disabling this whole function and code invoking it until someone
  figures it out.
*/
static MagickPassFail DCM_PostRescaleImage(Image *image,DicomStream *dcm,unsigned long ScanLimits,ExceptionInfo *exception)
{
  unsigned long
    y,
    x;

  register PixelPacket
    *q;

  if (ScanLimits)
    {
      /*
        Causes rescan for upper/lower limits - used for encapsulated images
      */
      unsigned int
        l;

      for (y=0; y < image->rows; y++)
        {
          q=GetImagePixels(image,0,y,image->columns,1);
          if (q == (PixelPacket *) NULL)
            return MagickFail;

          if (image->storage_class == PseudoClass)
            {
              register IndexPacket
                *indexes;

              indexes=AccessMutableIndexes(image);
              for (x=0; x < image->columns; x++)
                {
                  l=indexes[x];
                  if (dcm->pixel_representation == 1)
                    if (l > ((dcm->max_value_in >> 1)))
                      l = dcm->max_value_in-l+1;
                  if (l < (unsigned int) dcm->lower_lim)
                    dcm->lower_lim = l;
                  if (l > (unsigned int) dcm->upper_lim)
                    dcm->upper_lim = l;
                }
            }
          else
            {
              for (x=0; x < image->columns; x++)
                {
                  l=q->green;
                  if (dcm->pixel_representation == 1)
                    if (l > (dcm->max_value_in >> 1))
                      l = dcm->max_value_in-l+1;
                  if (l < (unsigned int) dcm->lower_lim)
                    dcm->lower_lim = l;
                  if (l > (unsigned int) dcm->upper_lim)
                    dcm->upper_lim = l;
                  q++;
                }
            }
        }

      if (image->storage_class == PseudoClass)
        {
          /* Handle compressed range by reallocating palette */
          if (!AllocateImageColormap(image,dcm->upper_lim+1))
            {
              ThrowException(exception,ResourceLimitError,UnableToCreateColormap,image->filename);
              return MagickFail;
            }
          return MagickPass;
        }
    }

  if (DCM_SetupRescaleMap(image,dcm,exception) == MagickFail)
    return MagickFail;
  for (y=0; y < image->rows; y++)
    {
      q=GetImagePixels(image,0,y,image->columns,1);
      if (q == (PixelPacket *) NULL)
        return MagickFail;

      if (image->storage_class == PseudoClass)
        {
          register IndexPacket
            *indexes;

          indexes=AccessMutableIndexes(image);
          for (x=0; x < image->columns; x++)
            indexes[x]=dcm->rescale_map[indexes[x]];
        }
      else
        {
          for (x=0; x < image->columns; x++)
            {
              q->red=dcm->rescale_map[q->red];
              q->green=dcm->rescale_map[q->green];
              q->blue=dcm->rescale_map[q->blue];
              q++;
            }
        }
      if (!SyncImagePixels(image))
        return MagickFail;
      /*
        if (image->previous == (Image *) NULL)
        if (QuantumTick(y,image->rows))
        if (!MagickMonitorFormatted(y,image->rows,exception,
        LoadImageText,image->filename))
        return MagickFail;
      */
    }
  return MagickPass;
}

static MagickPassFail DCM_ReadPaletteImage(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  unsigned long
    y;

  register unsigned long
    x;

  register PixelPacket
    *q;

  register IndexPacket
    *indexes;

  unsigned short
    index;

  unsigned char
    byte;

  byte=0;

  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Reading Palette image...");

  for (y=0; y < image->rows; y++)
    {
      q=SetImagePixels(image,0,y,image->columns,1);
      if (q == (PixelPacket *) NULL)
        return MagickFail;
      indexes=AccessMutableIndexes(image);
      for (x=0; x < image->columns; x++)
        {
          if (dcm->bytes_per_pixel == 1)
            {
              if (dcm->transfer_syntax == DCM_TS_RLE)
                index=DCM_RLE_ReadByte(image,dcm);
              else
                index=ReadBlobByte(image);
            }
          else
          if (dcm->bits_allocated != 12)
            {
              if (dcm->transfer_syntax == DCM_TS_RLE)
                index=DCM_RLE_ReadShort(image,dcm);
              else
                index=dcm->funcReadShort(image);
            }
          else
            {
              if (x & 0x01)
                {
                  /* ### TODO - Check whether logic needs altering if msb_state != DCM_MSB_LITTLE */
                  if (dcm->transfer_syntax == DCM_TS_RLE)
                    index=DCM_RLE_ReadByte(image,dcm);
                  else
                    index=ReadBlobByte(image);
                  index=(index << 4) | byte;
                }
              else
                {
                  if (dcm->transfer_syntax == DCM_TS_RLE)
                    index=DCM_RLE_ReadByte(image,dcm);
                  else
                    index=dcm->funcReadShort(image);
                  byte=index >> 12;
                  index&=0xfff;
                }
            }
          index&=dcm->max_value_in;
          if (dcm->rescaling == DCM_RS_PRE)
            {
              /*
                ### TODO - must read as Direct Class so look up
                red/green/blue values in palette table, processed via
                rescale_map
              */
            }
          else
            {
#if defined(USE_GRAYMAP)
              if (dcm->graymap != (unsigned short *) NULL)
                index=dcm->graymap[index];
#endif
              index=(IndexPacket) (index);
              VerifyColormapIndex(image,index);
              indexes[x]=index;
              *q=image->colormap[index];
              q++;
            }

          if (EOFBlob(image))
            {
              ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
              return MagickFail;
            }
        }
      if (!SyncImagePixels(image))
        return MagickFail;
      if (image->previous == (Image *) NULL)
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,
                                      LoadImageText,image->filename,
                                      image->columns,image->rows))
            return MagickFail;
    }
  return MagickPass;
}

static MagickPassFail DCM_ReadGrayscaleImage(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  unsigned long
    y;

  register unsigned long
    x;

  register PixelPacket
    *q;

#if defined(GRAYSCALE_USES_PALETTE) /* not used */
  register IndexPacket
    *indexes;
#endif

  unsigned short
    index;

  unsigned char
    byte;

  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Reading Grayscale %lux%lu image...",image->columns,image->rows);

#if !defined(GRAYSCALE_USES_PALETTE)
  /*
    If a palette was provided, the image may be in PseudoClass
  */
  image->storage_class=DirectClass;
#endif

  dcm->lower_lim = dcm->max_value_in;
  dcm->upper_lim = -(dcm->lower_lim);
  byte=0;
  for (y=0; y < image->rows; y++)
    {
      q=SetImagePixelsEx(image,0,y,image->columns,1,exception);
      if (q == (PixelPacket *) NULL)
        return MagickFail;
#if defined(GRAYSCALE_USES_PALETTE) /* not used */
      indexes=AccessMutableIndexes(image);
#endif
      for (x=0; x < image->columns; x++)
        {
          if (dcm->bytes_per_pixel == 1)
            {
              if (dcm->transfer_syntax == DCM_TS_RLE)
                index=DCM_RLE_ReadByte(image,dcm);
              else
                index=ReadBlobByte(image);
            }
          else
          if (dcm->bits_allocated != 12)
            {
              if (dcm->transfer_syntax == DCM_TS_RLE)
                index=DCM_RLE_ReadShort(image,dcm);
              else
                index=dcm->funcReadShort(image);
            }
          else
            {
              if (x & 0x01)
                {
                  /* ### TODO - Check whether logic needs altering if msb_state != DCM_MSB_LITTLE */
                  if (dcm->transfer_syntax == DCM_TS_RLE)
                    index=DCM_RLE_ReadByte(image,dcm);
                  else
                    index=ReadBlobByte(image);
                  index=(index << 4) | byte;
                }
              else
                {
                  if (dcm->transfer_syntax == DCM_TS_RLE)
                    index=DCM_RLE_ReadShort(image,dcm);
                  else
                    index=dcm->funcReadShort(image);
                  byte=index >> 12;
                  index&=0xfff;
                }
            }
          index&=dcm->max_value_in;
          if (dcm->rescaling == DCM_RS_POST)
            {
              unsigned int
                l;

              l = index;
              if (dcm->pixel_representation == 1)
                if (l > (dcm->max_value_in >> 1))
                  l = dcm->max_value_in-l+1;
              if ((int) l < dcm->lower_lim)
                dcm->lower_lim = l;
              if ((int) l > dcm->upper_lim)
                dcm->upper_lim = l;
            }
#if defined(GRAYSCALE_USES_PALETTE) /* not used */
          if (dcm->rescaling == DCM_RS_PRE)
            indexes[x]=dcm->rescale_map[index];
          else
            indexes[x]=index;
#else
          if ((dcm->rescaling == DCM_RS_PRE) &&
              (dcm->rescale_map != (Quantum *) NULL))
            {
              index=dcm->rescale_map[index];
            }
          q->red=index;
          q->green=index;
          q->blue=index;
          q->opacity=OpaqueOpacity;
          q++;
#endif
          if (EOFBlob(image))
            {
              ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
              return MagickFail;
            }
        }
      if (!SyncImagePixelsEx(image,exception))
        return MagickFail;
      if (image->previous == (Image *) NULL)
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,
                                      LoadImageText,image->filename,
                                      image->columns,image->rows))
            return MagickFail;
    }
  return MagickPass;
}

static MagickPassFail DCM_ReadPlanarRGBImage(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  unsigned long
    plane,
    y,
    x;

  register PixelPacket
    *q;

  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Reading Planar RGB %s compressed image with %u planes...",
                          (dcm->transfer_syntax == DCM_TS_RLE ? "RLE" : "not"),
                          dcm->samples_per_pixel);
  /*
    Force image to DirectClass since we are only updating DirectClass
    representation.  The image may be in PseudoClass if we were
    previously provided with a Palette.
  */
  image->storage_class=DirectClass;

  for (plane=0; plane < dcm->samples_per_pixel; plane++)
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "  Plane %lu...",plane);
      for (y=0; y < image->rows; y++)
        {
          q=GetImagePixels(image,0,y,image->columns,1);
          if (q == (PixelPacket *) NULL)
              return MagickFail;

          for (x=0; x < image->columns; x++)
            {
              switch ((int) plane)
                {
                  case 0:
                    if (dcm->transfer_syntax == DCM_TS_RLE)
                      q->red=ScaleCharToQuantum(DCM_RLE_ReadByte(image,dcm));
                    else
                      q->red=ScaleCharToQuantum(ReadBlobByte(image));
                    break;
                  case 1:
                    if (dcm->transfer_syntax == DCM_TS_RLE)
                      q->green=ScaleCharToQuantum(DCM_RLE_ReadByte(image,dcm));
                    else
                      q->green=ScaleCharToQuantum(ReadBlobByte(image));
                    break;
                  case 2:
                    if (dcm->transfer_syntax == DCM_TS_RLE)
                      q->blue=ScaleCharToQuantum(DCM_RLE_ReadByte(image,dcm));
                    else
                      q->blue=ScaleCharToQuantum(ReadBlobByte(image));
                    break;
                  case 3:
                    if (dcm->transfer_syntax == DCM_TS_RLE)
                      q->opacity=ScaleCharToQuantum((Quantum)(MaxRGB-ScaleCharToQuantum(DCM_RLE_ReadByte(image,dcm))));
                    else
                      q->opacity=ScaleCharToQuantum((Quantum)(MaxRGB-ScaleCharToQuantum(ReadBlobByte(image))));
                    break;
                }
              if (EOFBlob(image))
                {
                  ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
                  return MagickFail;
                }
              q++;
            }
          if (!SyncImagePixels(image))
            return MagickFail;
          if (image->previous == (Image *) NULL)
            if (QuantumTick(y,image->rows))
              if (!MagickMonitorFormatted(y,image->rows,exception,
                                          LoadImageText,image->filename,
                                          image->columns,image->rows))
                return MagickFail;
        }
    }
  return MagickPass;
}

static MagickPassFail DCM_ReadRGBImage(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  unsigned long
    y,
    x;

  register PixelPacket
    *q;

  Quantum
    blue,
    green,
    red;

  red=0;
  green=0;
  blue=0;

  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Reading RGB image...");

  /*
    Force image to DirectClass since we are only updating DirectClass
    representation.  The image may be in PseudoClass if we were
    previously provided with a Palette.
  */
  image->storage_class=DirectClass;

  for (y=0; y < image->rows; y++)
    {
      q=GetImagePixels(image,0,y,image->columns,1);
      if (q == (PixelPacket *) NULL)
        return MagickFail;

      for (x=0; x < image->columns; x++)
        {
          if (dcm->bytes_per_pixel == 1)
            {
              if (dcm->transfer_syntax == DCM_TS_RLE)
                {
                  red=DCM_RLE_ReadByte(image,dcm);
                  green=DCM_RLE_ReadByte(image,dcm);
                  blue=DCM_RLE_ReadByte(image,dcm);

                }
              else
                {
                  red=ReadBlobByte(image);
                  green=ReadBlobByte(image);
                  blue=ReadBlobByte(image);
                }
            }
          else
            {
              if (dcm->transfer_syntax == DCM_TS_RLE)
                {
                  red=DCM_RLE_ReadShort(image,dcm);
                  green=DCM_RLE_ReadShort(image,dcm);
                  blue=DCM_RLE_ReadShort(image,dcm);
                }
              else
                {
                  red=dcm->funcReadShort(image);
                  green=dcm->funcReadShort(image);
                  blue=dcm->funcReadShort(image);
                }
            }
          red&=dcm->max_value_in;
          green&=dcm->max_value_in;
          blue&=dcm->max_value_in;
          if ((dcm->rescaling == DCM_RS_PRE) &&
              (dcm->rescale_map != (Quantum *) NULL))
            {
              red=dcm->rescale_map[red];
              green=dcm->rescale_map[green];
              blue=dcm->rescale_map[blue];
            }

          q->red=(Quantum) red;
          q->green=(Quantum) green;
          q->blue=(Quantum) blue;
          q->opacity=OpaqueOpacity;
          q++;
          if (EOFBlob(image))
            {
              ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,image->filename);
              return MagickFail;
            }
        }
      if (!SyncImagePixels(image))
        return MagickFail;
      if (image->previous == (Image *) NULL)
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,
                                      LoadImageText,image->filename,
                                      image->columns,image->rows))
            return MagickFail;
    }
  return MagickPass;
}

static MagickPassFail DCM_ReadOffsetTable(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  magick_uint32_t
    base_offset,
    tag,
    length,
    i;

  tag=((magick_uint32_t) dcm->funcReadShort(image) << 16) |
    (magick_uint32_t) dcm->funcReadShort(image);
  length=dcm->funcReadLong(image);
  if (tag != 0xFFFEE000)
    return MagickFail;

  dcm->offset_ct=length >> 2;
  if (dcm->offset_ct == 0)
    return MagickPass;

  if (dcm->offset_ct != dcm->number_scenes)
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      return MagickFail;
    }

  dcm->offset_arr=MagickAllocateArray(magick_uint32_t *,dcm->offset_ct,sizeof(magick_uint32_t));
  if (dcm->offset_arr == (magick_uint32_t *) NULL)
    {
      ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,image->filename);
      return MagickFail;
    }

  for (i=0; i < dcm->offset_ct; i++)
  {
    dcm->offset_arr[i]=dcm->funcReadLong(image);
    if (EOFBlob(image))
      return MagickFail;
  }
  base_offset=(magick_uint32_t)TellBlob(image);
  for (i=0; i < dcm->offset_ct; i++)
    dcm->offset_arr[i]+=base_offset;

  /*
     Seek first fragment of first frame if necessary (although it shouldn't be...)
  */
  if (TellBlob(image) != dcm->offset_arr[0])
    SeekBlob(image,dcm->offset_arr[0],SEEK_SET);
  return MagickPass;
}

static MagickPassFail DCM_ReadNonNativeImages(Image **image,const ImageInfo *image_info,DicomStream *dcm,ExceptionInfo *exception)
{
  char
    filename[MaxTextExtent];

  FILE
    *file;

  int
    c;

  Image
    *image_list,
    *next_image;

  ImageInfo
    *clone_info;

  magick_uint32_t
    scene,
    tag,
    status,
    length,
    i;

  image_list=(Image *)NULL;

  /*
    Read offset table
  */
  if (DCM_ReadOffsetTable(*image,dcm,exception) == MagickFail)
    return MagickFail;

  if (dcm->number_scenes == 0U)
    {
      ThrowException(exception,CorruptImageError,
                     ImageFileHasNoScenes,
                     image_info->filename);
      return MagickFail;
    }

  status=MagickPass;
  for (scene=0; scene < dcm->number_scenes; scene++)
    {
      /*
        Use temporary file to hold extracted data stream
      */
      file=AcquireTemporaryFileStream(filename,BinaryFileIOMode);
      if (file == (FILE *) NULL)
        {
          ThrowException(exception,FileOpenError,UnableToCreateTemporaryFile,filename);
          return MagickFail;
        }

      status=MagickPass;
      do
        {
          /*
            Read fragment tag
          */
          tag=(((magick_uint32_t) dcm->funcReadShort(*image) << 16) |
               (magick_uint32_t) dcm->funcReadShort(*image));
          length=dcm->funcReadLong(*image);
          if (EOFBlob(*image))
            {
              status=MagickFail;
              break;
            }

          if (tag == 0xFFFEE0DD)
            {
              /* Sequence delimiter tag */
              break;
            }
          else
            if (tag != 0xFFFEE000)
              {
                status=MagickFail;
                break;
              }

          /*
            Copy this fragment to the temporary file
          */
          while (length > 0)
            {
              c=ReadBlobByte(*image);
              if (c == EOF)
                {
                  status=MagickFail;
                  break;
                }
              (void) fputc(c,file);
              length--;
            }

          if (dcm->offset_ct == 0)
            {
              /*
                Assume one fragment per frame so break loop unless we are in the last frame
              */
              if (scene < dcm->number_scenes-1)
                break;
            }
          else
            {
              /* Look for end of multi-fragment frames by checking for against offset table */
              length=TellBlob(*image);
              for (i=0; i < dcm->offset_ct; i++)
                if (length == dcm->offset_arr[i])
                  {
                    break;
                  }
            }
        } while (status == MagickPass);

      (void) fclose(file);
      if (status == MagickPass)
        {
          clone_info=CloneImageInfo(image_info);
          clone_info->blob=(void *) NULL;
          clone_info->length=0;
          if (dcm->transfer_syntax == DCM_TS_JPEG_2000)
            FormatString(clone_info->filename,"jp2:%.1024s",filename);
          else
            FormatString(clone_info->filename,"jpeg:%.1024s",filename);
          next_image=ReadImage(clone_info,exception);
          DestroyImageInfo(clone_info);
          if (next_image == (Image*)NULL)
            {
              status=MagickFail;
            }
          else
            if (dcm->rescaling == DCM_RS_POST)
              {
                /*
                  ### TODO: ???
                  We cannot guarantee integrity of input data since libjpeg may already have
                  downsampled 12- or 16-bit jpegs. Best guess at the moment is to recalculate
                  scaling using the image depth (unless avoid-scaling is in force)
                */
                /* Allow for libjpeg having changed depth of image */
                dcm->significant_bits=next_image->depth;
                dcm->bytes_per_pixel=1;
                if (dcm->significant_bits > 8)
                  dcm->bytes_per_pixel=2;
                dcm->max_value_in=MaxValueGivenBits(dcm->significant_bits);
                dcm->max_value_out=dcm->max_value_in;
                status=DCM_PostRescaleImage(next_image,dcm,True,exception);
              }
          if (status == MagickPass)
            {
              strcpy(next_image->filename,(*image)->filename);
              next_image->scene=scene;
              if (image_list == (Image*)NULL)
                image_list=next_image;
              else
                AppendImageToList(&image_list,next_image);
            }
          else if (next_image != (Image *) NULL)
            {
              DestroyImage(next_image);
              next_image=(Image *) NULL;
            }
        }
      (void) LiberateTemporaryFile(filename);

      if (status == MagickFail)
        break;
    }
  if (EOFBlob(*image))
    {
      status = MagickFail;
      ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,(*image)->filename);
    }

  if (status == MagickFail)
    {
      DestroyImageList(image_list);
      image_list = (Image *) NULL;
    }
  else
    {
      DestroyImage(*image);
      *image=image_list;
    }
  return status;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d D C M I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadDCMImage reads a Digital Imaging and Communications in Medicine
%  (DICOM) file and returns it.  It It allocates the memory necessary for the
%  new Image structure and returns a pointer to the new image.
%
%  The format of the ReadDCMImage method is:
%
%      Image *ReadDCMImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadDCMImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/
#define ThrowDCMReaderException(code_,reason_,image_)   \
  {                                                     \
    DCM_DestroyDCM(&dcm);                               \
    ThrowReaderException(code_,reason_,image_);         \
}
static Image *ReadDCMImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  char
    magick[MaxTextExtent];

  Image
    *image;

  int
    scene;

  size_t
    count;

  unsigned long
    status;

  DicomStream
    dcm;

  /*
    Open image file
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  (void) DCM_InitDCM(&dcm,image_info->verbose);
  image=AllocateImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFail)
    ThrowDCMReaderException(FileOpenError,UnableToOpenFile,image);

  /*
    Read DCM preamble
  */
  if ((count=ReadBlob(image,128,(char *) magick)) != 128)
    ThrowDCMReaderException(CorruptImageError,UnexpectedEndOfFile,image);
  if ((count=ReadBlob(image,4,(char *) magick)) != 4)
    ThrowDCMReaderException(CorruptImageError,UnexpectedEndOfFile,image);
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "magick: \"%.4s\"",magick);
  if (LocaleNCompare((char *) magick,"DICM",4) != 0)
    (void) SeekBlob(image,0L,SEEK_SET);

  /*
    Loop to read DCM image header one element at a time
  */
  status=DCM_ReadElement(image,&dcm,exception);
  while ((status == MagickPass) && ((dcm.group != 0x7FE0) || (dcm.element != 0x0010)))
    {
      DicomElemParseFunc
        *pfunc;

      pfunc=dicom_info[dcm.index].pfunc;
      if (pfunc != (DicomElemParseFunc *)NULL)
        status=pfunc(image,&dcm,exception);
      MagickFreeMemory(dcm.data);
      dcm.data = NULL;
      dcm.length = 0;
      if (status == MagickPass)
        status=DCM_ReadElement(image,&dcm,exception);
    }
  if (status == MagickFail)
    goto dcm_read_failure;
#if defined(IGNORE_WINDOW_FOR_UNSPECIFIED_SCALE_TYPE)
  if (dcm.rescale_type == DCM_RT_UNSPECIFIED)
    {
      dcm.window_width=0;
      dcm.rescale_slope=1;
      dcm.rescale_intercept=0;
    }
#endif
  DCM_SetRescaling(&dcm,(AccessDefinition(image_info,"dcm","avoid-scaling") != NULL));
  /*
    Now process the image data
  */
  if ((dcm.columns == 0) || (dcm.rows == 0))
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      status=MagickFail;
    }
  else if ((dcm.samples_per_pixel == 0) || (dcm.samples_per_pixel > 4))
    {
      ThrowException(exception,CorruptImageError,ImproperImageHeader,image->filename);
      status=MagickFail;
    }
  else if ((dcm.transfer_syntax != DCM_TS_IMPL_LITTLE) &&
           (dcm.transfer_syntax != DCM_TS_EXPL_LITTLE) &&
           (dcm.transfer_syntax != DCM_TS_EXPL_BIG) &&
           (dcm.transfer_syntax != DCM_TS_RLE))
    {
      status=DCM_ReadNonNativeImages(&image,image_info,&dcm,exception);
      dcm.number_scenes=0;
    }
  else if (dcm.rescaling != DCM_RS_POST)
    {
      status=DCM_SetupRescaleMap(image,&dcm,exception);
    }

  if (status == MagickFail)
    goto dcm_read_failure;

  if (dcm.transfer_syntax == DCM_TS_RLE)
    status=DCM_ReadOffsetTable(image,&dcm,exception);

  /* Loop to process all scenes in image */
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "DICOM has %d scenes", dcm.number_scenes);
  if (status == MagickFail)
    goto dcm_read_failure;

  for (scene=0; scene < (long) dcm.number_scenes; scene++)
    {
      if (dcm.transfer_syntax == DCM_TS_RLE)
        {
          magick_uint32_t
            tag,
            length;

          /*
            Discard any remaining bytes from last fragment
          */
          if (dcm.frag_bytes)
            SeekBlob(image,dcm.frag_bytes,SEEK_CUR);

          /*
            Read fragment tag
          */
          tag=(((magick_uint32_t) dcm.funcReadShort(image)) << 16) |
            (magick_uint32_t) dcm.funcReadShort(image);
          length=dcm.funcReadLong(image);
          if ((tag != 0xFFFEE000) || (length <= 64) || EOFBlob(image))
            {
              status=MagickFail;
              ThrowDCMReaderException(CorruptImageError,UnexpectedEndOfFile,image);
              break;
            }

          /*
            Set up decompression state
          */
          dcm.frag_bytes=length;
          dcm.rle_rep_ct=0;

          /*
            Read RLE segment table
          */
          dcm.rle_seg_ct=dcm.funcReadLong(image);
          for (length=0; length < 15; length++)
            dcm.rle_seg_offsets[length]=dcm.funcReadLong(image);
          dcm.frag_bytes-=64;
          if (EOFBlob(image))
            {
              status=MagickFail;
              ThrowDCMReaderException(CorruptImageError,UnexpectedEndOfFile,image);
              break;
            }
          if (dcm.rle_seg_ct > 1)
            {
              fprintf(stdout,"Multiple RLE segments in frame are not supported\n");
              status=MagickFail;
              break;
            }
        }

      /*
        Initialize image structure.
      */
      image->columns=dcm.columns;
      image->rows=dcm.rows;
      image->interlace=(dcm.interlace==1)?PlaneInterlace:NoInterlace;
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Scene[%d]: %lux%lu", scene, image->columns, image->rows);
#if defined(GRAYSCALE_USES_PALETTE)
      if ((image->colormap == (PixelPacket *) NULL) && (dcm.samples_per_pixel == 1))
#else
        if ((image->colormap == (PixelPacket *) NULL) && (dcm.phot_interp == DCM_PI_PALETTE_COLOR))
#endif
          {
            status=DCM_SetupColormap(image,&dcm,exception);
            if (status == MagickFail)
              break;
          }
      if (image_info->ping)
        break;

      if (CheckImagePixelLimits(image, exception) != MagickPass)
        ThrowDCMReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);

      /*
        Process image according to type
      */
      if (dcm.samples_per_pixel == 1)
        {
          if (dcm.phot_interp == DCM_PI_PALETTE_COLOR)
            status=DCM_ReadPaletteImage(image,&dcm,exception);
          else
            status=DCM_ReadGrayscaleImage(image,&dcm,exception);
        }
      else
        {
          if (image->interlace == PlaneInterlace)
            status=DCM_ReadPlanarRGBImage(image,&dcm,exception);
          else
            status=DCM_ReadRGBImage(image,&dcm,exception);
        }
      if (status != MagickPass)
        break;

      if ((dcm.rescaling == DCM_RS_PRE) &&
          ((dcm.phot_interp == DCM_PI_MONOCHROME1) ||
           (dcm.phot_interp == DCM_PI_MONOCHROME2)))
        {
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Normalizing image channels...");
          NormalizeImage(image);
        }
      else
        {
          if (dcm.rescaling == DCM_RS_POST)
            {
              if (image->logging)
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "Rescaling image channels...");
              status = DCM_PostRescaleImage(image,&dcm,False,exception);
              if (status != MagickPass)
                break;
            }
        }

      /*
        Proceed to next image.
      */
      if (image_info->subrange != 0)
        if (image->scene >= (image_info->subimage+image_info->subrange-1))
          break;
      if (scene < (long) (dcm.number_scenes-1))
        {
          /*
            Allocate next image structure.
          */
          AllocateNextImage(image_info,image);
          if (image->next == (Image *) NULL)
            {
              status=MagickFail;
              break;
            }
          image=SyncNextImageInList(image);
          status=MagickMonitorFormatted(TellBlob(image),GetBlobSize(image),
                                        exception,LoadImagesText,
                                        image->filename);
          if (status == MagickFail)
            break;
        }
    }

  /*
    Free allocated resources
  */
 dcm_read_failure:
  DCM_DestroyDCM(&dcm);
  if (status == MagickPass)
    {
      /* It is possible to have success status yet have no image */
      if (image != (Image *) NULL)
        {
          while (image->previous != (Image *) NULL)
            image=image->previous;
          CloseBlob(image);
          return(image);
        }
      else
        {
          ThrowException(exception,CorruptImageError,
                         ImageFileDoesNotContainAnyImageData,
                         image_info->filename);
          return (Image *) NULL;
        }
    }
  else
    {
      DestroyImageList(image);
      return((Image *) NULL);
    }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r D C M I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterDCMImage adds attributes for the DCM image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterDCMImage method is:
%
%      RegisterDCMImage(void)
%
*/
ModuleExport void RegisterDCMImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("DCM");
  entry->decoder=(DecoderHandler) ReadDCMImage;
  entry->magick=(MagickHandler) IsDCM;
  entry->adjoin=False;
  entry->seekable_stream=True;
  entry->description="Digital Imaging and Communications in Medicine image";
  entry->note="See http://medical.nema.org/ for information on DICOM.";
  entry->module="DCM";
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r D C M I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterDCMImage removes format registrations made by the
%  DCM module from the list of supported formats.
%
%  The format of the UnregisterDCMImage method is:
%
%      UnregisterDCMImage(void)
%
*/
ModuleExport void UnregisterDCMImage(void)
{
  (void) UnregisterMagickInfo("DCM");
}
/*
   ### TODO :
   #1 Fixes on palette support:
                - Handle palette images where # of entries > MaxColormapSize - create image
                  as Direct class, store the original palette (scaled to MaxRGB) and then map
                  input values via modified palette to output RGB values.
        - Honour palette/LUT descriptors (ie values <= min value map to first
                  entry, value = (min_value + 1) maps to second entry, and so on, whilst
                  values >= (min value + palette/LUT size) map to last entry.
   #2 Use ImportImagePixelArea?
   #3 Handling of encapsulated JPEGs which downsample to 8 bit via
      libjpeg. These lose accuracy before we can rescale to handle the
          issues of PR=1 + window center/width + rescale slope/intercept on
          MONOCHROME1 or 2. Worst case : CT-MONO2-16-chest. Currently images
          are post-rescaled based on sample range. For PseudoClass grayscales
          this is done by colormap manipulation only.
   #4 JPEG/JPEG-LS/JPEG 2000: Check that multi frame handling in DCM_ReadEncapImages
      is ok
   #5 Support LUTs?
   #6 Pixel Padding value/range - make transparent or allow use to specify a color?
*/

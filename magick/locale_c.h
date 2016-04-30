#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 547

#define MGK_BlobErrorUnableToCreateBlob 1
#define MGK_BlobErrorUnableToObtainOffset 2
#define MGK_BlobErrorUnableToOpenFile 3
#define MGK_BlobErrorUnableToReadFile 4
#define MGK_BlobErrorUnableToReadToOffset 5
#define MGK_BlobErrorUnableToSeekToOffset 6
#define MGK_BlobErrorUnableToWriteBlob 7
#define MGK_BlobErrorUnrecognizedImageFormat 8
#define MGK_BlobFatalErrorDefault 9
#define MGK_BlobWarningDefault 10
#define MGK_CacheErrorInconsistentPersistentCacheDepth 11
#define MGK_CacheErrorPixelCacheIsNotOpen 12
#define MGK_CacheErrorUnableToAllocateCacheView 13
#define MGK_CacheErrorUnableToCloneCache 14
#define MGK_CacheErrorUnableToExtendCache 15
#define MGK_CacheErrorUnableToGetCacheNexus 16
#define MGK_CacheErrorUnableToGetPixelsFromCache 17
#define MGK_CacheErrorUnableToOpenCache 18
#define MGK_CacheErrorUnableToPeristPixelCache 19
#define MGK_CacheErrorUnableToReadPixelCache 20
#define MGK_CacheErrorUnableToSyncCache 21
#define MGK_CacheFatalErrorDiskAllocationFailed 22
#define MGK_CacheFatalErrorUnableToExtendPixelCache 23
#define MGK_CacheWarningDefault 24
#define MGK_CoderErrorColormapTooLarge 25
#define MGK_CoderErrorColormapTypeNotSupported 26
#define MGK_CoderErrorColorspaceModelIsNotSupported 27
#define MGK_CoderErrorColorTypeNotSupported 28
#define MGK_CoderErrorCompressionNotValid 29
#define MGK_CoderErrorDataEncodingSchemeIsNotSupported 30
#define MGK_CoderErrorDataStorageTypeIsNotSupported 31
#define MGK_CoderErrorDeltaPNGNotSupported 32
#define MGK_CoderErrorEncryptedWPGImageFileNotSupported 33
#define MGK_CoderErrorFractalCompressionNotSupported 34
#define MGK_CoderErrorImageColumnOrRowSizeIsNotSupported 35
#define MGK_CoderErrorImageDoesNotHaveAMatteChannel 36
#define MGK_CoderErrorImageIsNotTiled 37
#define MGK_CoderErrorImageTypeNotSupported 38
#define MGK_CoderErrorIncompatibleSizeOfDouble 39
#define MGK_CoderErrorIrregularChannelGeometryNotSupported 40
#define MGK_CoderErrorJNGCompressionNotSupported 41
#define MGK_CoderErrorJPEGCompressionNotSupported 42
#define MGK_CoderErrorJPEGEmbeddingFailed 43
#define MGK_CoderErrorLocationTypeIsNotSupported 44
#define MGK_CoderErrorMapStorageTypeIsNotSupported 45
#define MGK_CoderErrorMSBByteOrderNotSupported 46
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 47
#define MGK_CoderErrorMultipleRecordListNotSupported 48
#define MGK_CoderErrorNo8BIMDataIsAvailable 49
#define MGK_CoderErrorNoAPP1DataIsAvailable 50
#define MGK_CoderErrorNoBitmapOnClipboard 51
#define MGK_CoderErrorNoColorProfileAvailable 52
#define MGK_CoderErrorNoDataReturned 53
#define MGK_CoderErrorNoImageVectorGraphics 54
#define MGK_CoderErrorNoIPTCInfoWasFound 55
#define MGK_CoderErrorNoIPTCProfileAvailable 56
#define MGK_CoderErrorNumberOfImagesIsNotSupported 57
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 58
#define MGK_CoderErrorOnlyLevelZerofilesSupported 59
#define MGK_CoderErrorPNGCompressionNotSupported 60
#define MGK_CoderErrorPNGLibraryTooOld 61
#define MGK_CoderErrorRLECompressionNotSupported 62
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 63
#define MGK_CoderErrorUnableToCopyProfile 64
#define MGK_CoderErrorUnableToCreateADC 65
#define MGK_CoderErrorUnableToCreateBitmap 66
#define MGK_CoderErrorUnableToDecompressImage 67
#define MGK_CoderErrorUnableToInitializeFPXLibrary 68
#define MGK_CoderErrorUnableToOpenBlob 69
#define MGK_CoderErrorUnableToReadAspectRatio 70
#define MGK_CoderErrorUnableToReadCIELABImages 71
#define MGK_CoderErrorUnableToReadSummaryInfo 72
#define MGK_CoderErrorUnableToSetAffineMatrix 73
#define MGK_CoderErrorUnableToSetAspectRatio 74
#define MGK_CoderErrorUnableToSetColorTwist 75
#define MGK_CoderErrorUnableToSetContrast 76
#define MGK_CoderErrorUnableToSetFilteringValue 77
#define MGK_CoderErrorUnableToSetImageComments 78
#define MGK_CoderErrorUnableToSetImageTitle 79
#define MGK_CoderErrorUnableToSetJPEGLevel 80
#define MGK_CoderErrorUnableToSetRegionOfInterest 81
#define MGK_CoderErrorUnableToSetSummaryInfo 82
#define MGK_CoderErrorUnableToTranslateText 83
#define MGK_CoderErrorUnableToWriteMPEGParameters 84
#define MGK_CoderErrorUnableToWriteTemporaryFile 85
#define MGK_CoderErrorUnableToZipCompressImage 86
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 87
#define MGK_CoderErrorWebPDecodingFailedUserAbort 88
#define MGK_CoderErrorWebPEncodingFailed 89
#define MGK_CoderErrorWebPEncodingFailedBadDimension 90
#define MGK_CoderErrorWebPEncodingFailedBadWrite 91
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 92
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 93
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 94
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 95
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 96
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 97
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 98
#define MGK_CoderErrorWebPEncodingFailedUserAbort 99
#define MGK_CoderErrorWebPInvalidConfiguration 100
#define MGK_CoderErrorWebPInvalidParameter 101
#define MGK_CoderErrorZipCompressionNotSupported 102
#define MGK_CoderFatalErrorDefault 103
#define MGK_CoderWarningLosslessToLossyJPEGConversion 104
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 105
#define MGK_ConfigureErrorRegistryKeyLookupFailed 106
#define MGK_ConfigureErrorStringTokenLengthExceeded 107
#define MGK_ConfigureErrorUnableToAccessConfigureFile 108
#define MGK_ConfigureErrorUnableToAccessFontFile 109
#define MGK_ConfigureErrorUnableToAccessLogFile 110
#define MGK_ConfigureErrorUnableToAccessModuleFile 111
#define MGK_ConfigureFatalErrorDefault 112
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 113
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 114
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 115
#define MGK_ConfigureWarningDefault 116
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 117
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 118
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 119
#define MGK_CorruptImageErrorCompressionNotValid 120
#define MGK_CorruptImageErrorCorruptImage 121
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 122
#define MGK_CorruptImageErrorImageTypeNotSupported 123
#define MGK_CorruptImageErrorImproperImageHeader 124
#define MGK_CorruptImageErrorInsufficientImageDataInFile 125
#define MGK_CorruptImageErrorInvalidColormapIndex 126
#define MGK_CorruptImageErrorInvalidFileFormatVersion 127
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 128
#define MGK_CorruptImageErrorMissingImageChannel 129
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 130
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 131
#define MGK_CorruptImageErrorNotEnoughTiles 132
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 133
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 134
#define MGK_CorruptImageErrorTooMuchImageDataInFile 135
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 136
#define MGK_CorruptImageErrorUnableToReadColorProfile 137
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 138
#define MGK_CorruptImageErrorUnableToReadGenericProfile 139
#define MGK_CorruptImageErrorUnableToReadImageData 140
#define MGK_CorruptImageErrorUnableToReadImageHeader 141
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 142
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 143
#define MGK_CorruptImageErrorUnableToReadSubImageData 144
#define MGK_CorruptImageErrorUnableToReadVIDImage 145
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 146
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 147
#define MGK_CorruptImageErrorUnableToUncompressImage 148
#define MGK_CorruptImageErrorUnexpectedEndOfFile 149
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 150
#define MGK_CorruptImageErrorUnknownPatternType 151
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 152
#define MGK_CorruptImageErrorUnrecognizedImageCompression 153
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 154
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 155
#define MGK_CorruptImageFatalErrorUnableToPersistKey 156
#define MGK_CorruptImageWarningCompressionNotValid 157
#define MGK_CorruptImageWarningImproperImageHeader 158
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 159
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 160
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 161
#define MGK_CorruptImageWarningSkipToSyncByte 162
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 163
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 164
#define MGK_CorruptImageWarningUnrecognizedImageCompression 165
#define MGK_DelegateErrorDelegateFailed 166
#define MGK_DelegateErrorFailedToAllocateArgumentList 167
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 168
#define MGK_DelegateErrorFailedToComputeOutputSize 169
#define MGK_DelegateErrorFailedToFindGhostscript 170
#define MGK_DelegateErrorFailedToRenderFile 171
#define MGK_DelegateErrorFailedToScanFile 172
#define MGK_DelegateErrorNoTagFound 173
#define MGK_DelegateErrorPostscriptDelegateFailed 174
#define MGK_DelegateErrorUnableToCreateImage 175
#define MGK_DelegateErrorUnableToCreateImageComponent 176
#define MGK_DelegateErrorUnableToDecodeImageFile 177
#define MGK_DelegateErrorUnableToEncodeImageFile 178
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 179
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 180
#define MGK_DelegateErrorUnableToManageJP2Stream 181
#define MGK_DelegateErrorUnableToWriteSVGFormat 182
#define MGK_DelegateErrorWebPABIMismatch 183
#define MGK_DelegateFatalErrorDefault 184
#define MGK_DelegateWarningDefault 185
#define MGK_DrawErrorAlreadyPushingPatternDefinition 186
#define MGK_DrawErrorFloatValueConversionError 187
#define MGK_DrawErrorIntegerValueConversionError 188
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 189
#define MGK_DrawErrorTooManyCoordinates 190
#define MGK_DrawErrorUnableToPrint 191
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 192
#define MGK_DrawErrorVectorPathTruncated 193
#define MGK_DrawFatalErrorDefault 194
#define MGK_DrawWarningNotARelativeURL 195
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 196
#define MGK_DrawWarningURLNotFound 197
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 198
#define MGK_FileOpenErrorUnableToOpenFile 199
#define MGK_FileOpenErrorUnableToWriteFile 200
#define MGK_FileOpenFatalErrorDefault 201
#define MGK_FileOpenWarningDefault 202
#define MGK_ImageErrorAngleIsDiscontinuous 203
#define MGK_ImageErrorColorspaceColorProfileMismatch 204
#define MGK_ImageErrorImageColorspaceDiffers 205
#define MGK_ImageErrorImageColorspaceMismatch 206
#define MGK_ImageErrorImageDifferenceExceedsLimit 207
#define MGK_ImageErrorImageDoesNotContainResolution 208
#define MGK_ImageErrorImageOpacityDiffers 209
#define MGK_ImageErrorImageSequenceIsRequired 210
#define MGK_ImageErrorImageSizeDiffers 211
#define MGK_ImageErrorInvalidColormapIndex 212
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 213
#define MGK_ImageErrorNoImagesWereFound 214
#define MGK_ImageErrorNoImagesWereLoaded 215
#define MGK_ImageErrorNoLocaleImageAttribute 216
#define MGK_ImageErrorTooManyClusters 217
#define MGK_ImageErrorUnableToAppendImage 218
#define MGK_ImageErrorUnableToAssignProfile 219
#define MGK_ImageErrorUnableToAverageImage 220
#define MGK_ImageErrorUnableToCoalesceImage 221
#define MGK_ImageErrorUnableToCompareImages 222
#define MGK_ImageErrorUnableToCreateImageMosaic 223
#define MGK_ImageErrorUnableToCreateStereoImage 224
#define MGK_ImageErrorUnableToDeconstructImageSequence 225
#define MGK_ImageErrorUnableToFlattenImage 226
#define MGK_ImageErrorUnableToGetClipMask 227
#define MGK_ImageErrorUnableToHandleImageChannel 228
#define MGK_ImageErrorUnableToResizeImage 229
#define MGK_ImageErrorUnableToSegmentImage 230
#define MGK_ImageErrorUnableToSetClipMask 231
#define MGK_ImageErrorUnableToShearImage 232
#define MGK_ImageErrorWidthOrHeightExceedsLimit 233
#define MGK_ImageFatalErrorUnableToPersistKey 234
#define MGK_ImageWarningDefault 235
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 236
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 237
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 238
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 239
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 240
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 241
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 242
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 243
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 244
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 245
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 246
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 247
#define MGK_MissingDelegateFatalErrorDefault 248
#define MGK_MissingDelegateWarningDefault 249
#define MGK_ModuleErrorFailedToCloseModule 250
#define MGK_ModuleErrorFailedToFindSymbol 251
#define MGK_ModuleErrorUnableToLoadModule 252
#define MGK_ModuleErrorUnableToRegisterImageFormat 253
#define MGK_ModuleErrorUnrecognizedModule 254
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 255
#define MGK_ModuleWarningDefault 256
#define MGK_MonitorErrorDefault 257
#define MGK_MonitorFatalErrorDefault 258
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 259
#define MGK_MonitorWarningDefault 260
#define MGK_OptionErrorBevelWidthIsNegative 261
#define MGK_OptionErrorColorSeparatedImageRequired 262
#define MGK_OptionErrorFrameIsLessThanImageSize 263
#define MGK_OptionErrorGeometryDimensionsAreZero 264
#define MGK_OptionErrorGeometryDoesNotContainImage 265
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 266
#define MGK_OptionErrorImagesAreNotTheSameSize 267
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 268
#define MGK_OptionErrorImageSmallerThanKernelWidth 269
#define MGK_OptionErrorImageSmallerThanRadius 270
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 271
#define MGK_OptionErrorInputImagesAlreadySpecified 272
#define MGK_OptionErrorInvalidSubimageSpecification 273
#define MGK_OptionErrorKernelRadiusIsTooSmall 274
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 275
#define MGK_OptionErrorMatrixIsNotSquare 276
#define MGK_OptionErrorMatrixOrderOutOfRange 277
#define MGK_OptionErrorMissingAnImageFilename 278
#define MGK_OptionErrorMissingArgument 279
#define MGK_OptionErrorMustSpecifyAnImageName 280
#define MGK_OptionErrorMustSpecifyImageSize 281
#define MGK_OptionErrorNoBlobDefined 282
#define MGK_OptionErrorNoImagesDefined 283
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 284
#define MGK_OptionErrorNoProfileNameWasGiven 285
#define MGK_OptionErrorNullBlobArgument 286
#define MGK_OptionErrorReferenceImageRequired 287
#define MGK_OptionErrorReferenceIsNotMyType 288
#define MGK_OptionErrorRegionAreaExceedsLimit 289
#define MGK_OptionErrorRequestDidNotReturnAnImage 290
#define MGK_OptionErrorSteganoImageRequired 291
#define MGK_OptionErrorStereoImageRequired 292
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 293
#define MGK_OptionErrorUnableToAddOrRemoveProfile 294
#define MGK_OptionErrorUnableToAverageImageSequence 295
#define MGK_OptionErrorUnableToBlurImage 296
#define MGK_OptionErrorUnableToChopImage 297
#define MGK_OptionErrorUnableToColorMatrixImage 298
#define MGK_OptionErrorUnableToConstituteImage 299
#define MGK_OptionErrorUnableToConvolveImage 300
#define MGK_OptionErrorUnableToEdgeImage 301
#define MGK_OptionErrorUnableToEqualizeImage 302
#define MGK_OptionErrorUnableToFilterImage 303
#define MGK_OptionErrorUnableToFormatImageMetadata 304
#define MGK_OptionErrorUnableToFrameImage 305
#define MGK_OptionErrorUnableToOilPaintImage 306
#define MGK_OptionErrorUnableToPaintImage 307
#define MGK_OptionErrorUnableToRaiseImage 308
#define MGK_OptionErrorUnableToSharpenImage 309
#define MGK_OptionErrorUnableToThresholdImage 310
#define MGK_OptionErrorUnableToWaveImage 311
#define MGK_OptionErrorUnrecognizedAttribute 312
#define MGK_OptionErrorUnrecognizedChannelType 313
#define MGK_OptionErrorUnrecognizedColor 314
#define MGK_OptionErrorUnrecognizedColormapType 315
#define MGK_OptionErrorUnrecognizedColorspace 316
#define MGK_OptionErrorUnrecognizedCommand 317
#define MGK_OptionErrorUnrecognizedComposeOperator 318
#define MGK_OptionErrorUnrecognizedDisposeMethod 319
#define MGK_OptionErrorUnrecognizedElement 320
#define MGK_OptionErrorUnrecognizedEndianType 321
#define MGK_OptionErrorUnrecognizedGravityType 322
#define MGK_OptionErrorUnrecognizedHighlightStyle 323
#define MGK_OptionErrorUnrecognizedImageCompression 324
#define MGK_OptionErrorUnrecognizedImageFilter 325
#define MGK_OptionErrorUnrecognizedImageFormat 326
#define MGK_OptionErrorUnrecognizedImageMode 327
#define MGK_OptionErrorUnrecognizedImageType 328
#define MGK_OptionErrorUnrecognizedIntentType 329
#define MGK_OptionErrorUnrecognizedInterlaceType 330
#define MGK_OptionErrorUnrecognizedListType 331
#define MGK_OptionErrorUnrecognizedMetric 332
#define MGK_OptionErrorUnrecognizedModeType 333
#define MGK_OptionErrorUnrecognizedNoiseType 334
#define MGK_OptionErrorUnrecognizedOperator 335
#define MGK_OptionErrorUnrecognizedOption 336
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 337
#define MGK_OptionErrorUnrecognizedPixelMap 338
#define MGK_OptionErrorUnrecognizedPreviewType 339
#define MGK_OptionErrorUnrecognizedResourceType 340
#define MGK_OptionErrorUnrecognizedType 341
#define MGK_OptionErrorUnrecognizedUnitsType 342
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 343
#define MGK_OptionErrorUnsupportedSamplingFactor 344
#define MGK_OptionErrorUsageError 345
#define MGK_OptionFatalErrorInvalidColorspaceType 346
#define MGK_OptionFatalErrorInvalidEndianType 347
#define MGK_OptionFatalErrorInvalidImageType 348
#define MGK_OptionFatalErrorInvalidInterlaceType 349
#define MGK_OptionFatalErrorMissingAnImageFilename 350
#define MGK_OptionFatalErrorMissingArgument 351
#define MGK_OptionFatalErrorNoImagesWereLoaded 352
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 353
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 354
#define MGK_OptionFatalErrorUnableToOpenXServer 355
#define MGK_OptionFatalErrorUnableToPersistKey 356
#define MGK_OptionFatalErrorUnrecognizedColormapType 357
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 358
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 359
#define MGK_OptionFatalErrorUnrecognizedEndianType 360
#define MGK_OptionFatalErrorUnrecognizedFilterType 361
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 362
#define MGK_OptionFatalErrorUnrecognizedImageType 363
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 364
#define MGK_OptionFatalErrorUnrecognizedOption 365
#define MGK_OptionFatalErrorUnrecognizedResourceType 366
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 367
#define MGK_OptionWarningUnrecognizedColor 368
#define MGK_RegistryErrorImageExpected 369
#define MGK_RegistryErrorImageInfoExpected 370
#define MGK_RegistryErrorStructureSizeMismatch 371
#define MGK_RegistryErrorUnableToGetRegistryID 372
#define MGK_RegistryErrorUnableToLocateImage 373
#define MGK_RegistryErrorUnableToSetRegistry 374
#define MGK_RegistryFatalErrorDefault 375
#define MGK_RegistryWarningDefault 376
#define MGK_ResourceLimitErrorCacheResourcesExhausted 377
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 378
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 379
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 380
#define MGK_ResourceLimitErrorMemoryAllocationFailed 381
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 382
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 383
#define MGK_ResourceLimitErrorUnableToAddColorProfile 384
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 385
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 386
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 387
#define MGK_ResourceLimitErrorUnableToAllocateColormap 388
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 389
#define MGK_ResourceLimitErrorUnableToAllocateString 390
#define MGK_ResourceLimitErrorUnableToAnnotateImage 391
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 392
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 393
#define MGK_ResourceLimitErrorUnableToCloneImage 394
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 395
#define MGK_ResourceLimitErrorUnableToConstituteImage 396
#define MGK_ResourceLimitErrorUnableToConvertFont 397
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 398
#define MGK_ResourceLimitErrorUnableToCreateColormap 399
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 400
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 401
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 402
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 403
#define MGK_ResourceLimitErrorUnableToCreateXWindow 404
#define MGK_ResourceLimitErrorUnableToCropImage 405
#define MGK_ResourceLimitErrorUnableToDespeckleImage 406
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 407
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 408
#define MGK_ResourceLimitErrorUnableToDitherImage 409
#define MGK_ResourceLimitErrorUnableToDrawOnImage 410
#define MGK_ResourceLimitErrorUnableToEdgeImage 411
#define MGK_ResourceLimitErrorUnableToEmbossImage 412
#define MGK_ResourceLimitErrorUnableToEnhanceImage 413
#define MGK_ResourceLimitErrorUnableToFloodfillImage 414
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 415
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 416
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 417
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 418
#define MGK_ResourceLimitErrorUnableToLevelImage 419
#define MGK_ResourceLimitErrorUnableToMagnifyImage 420
#define MGK_ResourceLimitErrorUnableToManageColor 421
#define MGK_ResourceLimitErrorUnableToMapImage 422
#define MGK_ResourceLimitErrorUnableToMapImageSequence 423
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 424
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 425
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 426
#define MGK_ResourceLimitErrorUnableToNormalizeImage 427
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 428
#define MGK_ResourceLimitErrorUnableToQuantizeImage 429
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 430
#define MGK_ResourceLimitErrorUnableToReadTextChunk 431
#define MGK_ResourceLimitErrorUnableToReadXImage 432
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 433
#define MGK_ResourceLimitErrorUnableToResizeImage 434
#define MGK_ResourceLimitErrorUnableToRotateImage 435
#define MGK_ResourceLimitErrorUnableToSampleImage 436
#define MGK_ResourceLimitErrorUnableToScaleImage 437
#define MGK_ResourceLimitErrorUnableToSelectImage 438
#define MGK_ResourceLimitErrorUnableToSharpenImage 439
#define MGK_ResourceLimitErrorUnableToShaveImage 440
#define MGK_ResourceLimitErrorUnableToShearImage 441
#define MGK_ResourceLimitErrorUnableToSortImageColormap 442
#define MGK_ResourceLimitErrorUnableToThresholdImage 443
#define MGK_ResourceLimitErrorUnableToTransformColorspace 444
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 445
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 446
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 447
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 448
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 449
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 450
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 451
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 452
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 453
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 454
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 455
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 456
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 457
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 458
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 459
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 460
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 461
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 462
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 463
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 464
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 465
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 466
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 467
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 471
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 472
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 473
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 474
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 475
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 476
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 477
#define MGK_ResourceLimitFatalErrorUnableToConvertText 478
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 479
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 480
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 481
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 482
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 483
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 484
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 485
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 486
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 487
#define MGK_ResourceLimitWarningMemoryAllocationFailed 488
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 489
#define MGK_StreamErrorNoStreamHandlerIsDefined 490
#define MGK_StreamErrorPixelCacheIsNotOpen 491
#define MGK_StreamErrorUnableToAcquirePixelStream 492
#define MGK_StreamErrorUnableToSetPixelStream 493
#define MGK_StreamErrorUnableToSyncPixelStream 494
#define MGK_StreamFatalErrorDefault 495
#define MGK_StreamWarningDefault 496
#define MGK_TypeErrorFontSubstitutionRequired 497
#define MGK_TypeErrorUnableToGetTypeMetrics 498
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 499
#define MGK_TypeErrorUnableToReadFont 500
#define MGK_TypeErrorUnrecognizedFontEncoding 501
#define MGK_TypeFatalErrorDefault 502
#define MGK_TypeWarningDefault 503
#define MGK_WandErrorInvalidColormapIndex 504
#define MGK_WandErrorWandAPINotImplemented 505
#define MGK_WandErrorWandContainsNoImageIndexs 506
#define MGK_WandErrorWandContainsNoImages 507
#define MGK_XServerErrorColorIsNotKnownToServer 508
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 509
#define MGK_XServerErrorStandardColormapIsNotInitialized 510
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 511
#define MGK_XServerErrorUnableToCreateBitmap 512
#define MGK_XServerErrorUnableToCreateColormap 513
#define MGK_XServerErrorUnableToCreatePixmap 514
#define MGK_XServerErrorUnableToCreateProperty 515
#define MGK_XServerErrorUnableToCreateStandardColormap 516
#define MGK_XServerErrorUnableToDisplayImageInfo 517
#define MGK_XServerErrorUnableToGetProperty 518
#define MGK_XServerErrorUnableToGetStandardColormap 519
#define MGK_XServerErrorUnableToGetVisual 520
#define MGK_XServerErrorUnableToGrabMouse 521
#define MGK_XServerErrorUnableToLoadFont 522
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 523
#define MGK_XServerErrorUnableToOpenXServer 524
#define MGK_XServerErrorUnableToReadXAttributes 525
#define MGK_XServerErrorUnableToReadXWindowImage 526
#define MGK_XServerErrorUnrecognizedColormapType 527
#define MGK_XServerErrorUnrecognizedGravityType 528
#define MGK_XServerErrorUnrecognizedVisualSpecifier 529
#define MGK_XServerFatalErrorUnableToAllocateXHints 530
#define MGK_XServerFatalErrorUnableToCreateCursor 531
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 532
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 533
#define MGK_XServerFatalErrorUnableToCreateTextProperty 534
#define MGK_XServerFatalErrorUnableToCreateXImage 535
#define MGK_XServerFatalErrorUnableToCreateXPixmap 536
#define MGK_XServerFatalErrorUnableToCreateXWindow 537
#define MGK_XServerFatalErrorUnableToDisplayImage 538
#define MGK_XServerFatalErrorUnableToDitherImage 539
#define MGK_XServerFatalErrorUnableToGetPixelInfo 540
#define MGK_XServerFatalErrorUnableToGetVisual 541
#define MGK_XServerFatalErrorUnableToLoadFont 542
#define MGK_XServerFatalErrorUnableToMakeXWindow 543
#define MGK_XServerFatalErrorUnableToOpenXServer 544
#define MGK_XServerFatalErrorUnableToViewFonts 545
#define MGK_XServerWarningUnableToGetVisual 546
#define MGK_XServerWarningUsingDefaultVisual 547

#endif

#if defined(_INCLUDE_CATEGORYMAP_TABLE_)
typedef struct _CategoryInfo{
  const char *name;
  int offset;
} CategoryInfo;

static const CategoryInfo category_map[] =
  {
    { "Blob", 0 },
    { "Cache", 3 },
    { "Coder", 6 },
    { "Configure", 9 },
    { "Corrupt/Image", 12 },
    { "Delegate", 15 },
    { "Draw", 18 },
    { "File/Open", 21 },
    { "Image", 24 },
    { "Missing/Delegate", 27 },
    { "Module", 30 },
    { "Monitor", 33 },
    { "Option", 36 },
    { "Registry", 39 },
    { "Resource/Limit", 42 },
    { "Stream", 45 },
    { "Type", 48 },
    { "Wand", 51 },
    { "XServer", 52 },
    { 0, 54 }
  };
#endif

#if defined(_INCLUDE_SEVERITYMAP_TABLE_)
typedef struct _SeverityInfo{
  const char *name;
  int offset;
  ExceptionType severityid;
} SeverityInfo;

static const SeverityInfo severity_map[] =
  {
    { "Blob/Error", 0, BlobError },
    { "Blob/FatalError", 8, BlobFatalError },
    { "Blob/Warning", 9, BlobWarning },
    { "Cache/Error", 10, CacheError },
    { "Cache/FatalError", 21, CacheFatalError },
    { "Cache/Warning", 23, CacheWarning },
    { "Coder/Error", 24, CoderError },
    { "Coder/FatalError", 102, CoderFatalError },
    { "Coder/Warning", 103, CoderWarning },
    { "Configure/Error", 104, ConfigureError },
    { "Configure/FatalError", 111, ConfigureFatalError },
    { "Configure/Warning", 115, ConfigureWarning },
    { "Corrupt/Image/Error", 116, CorruptImageError },
    { "Corrupt/Image/FatalError", 155, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 156, CorruptImageWarning },
    { "Delegate/Error", 165, DelegateError },
    { "Delegate/FatalError", 183, DelegateFatalError },
    { "Delegate/Warning", 184, DelegateWarning },
    { "Draw/Error", 185, DrawError },
    { "Draw/FatalError", 193, DrawFatalError },
    { "Draw/Warning", 194, DrawWarning },
    { "File/Open/Error", 197, FileOpenError },
    { "File/Open/FatalError", 200, FileOpenFatalError },
    { "File/Open/Warning", 201, FileOpenWarning },
    { "Image/Error", 202, ImageError },
    { "Image/FatalError", 233, ImageFatalError },
    { "Image/Warning", 234, ImageWarning },
    { "Missing/Delegate/Error", 235, MissingDelegateError },
    { "Missing/Delegate/FatalError", 247, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 248, MissingDelegateWarning },
    { "Module/Error", 249, ModuleError },
    { "Module/FatalError", 254, ModuleFatalError },
    { "Module/Warning", 255, ModuleWarning },
    { "Monitor/Error", 256, MonitorError },
    { "Monitor/FatalError", 257, MonitorFatalError },
    { "Monitor/Warning", 259, MonitorWarning },
    { "Option/Error", 260, OptionError },
    { "Option/FatalError", 345, OptionFatalError },
    { "Option/Warning", 367, OptionWarning },
    { "Registry/Error", 368, RegistryError },
    { "Registry/FatalError", 374, RegistryFatalError },
    { "Registry/Warning", 375, RegistryWarning },
    { "Resource/Limit/Error", 376, ResourceLimitError },
    { "Resource/Limit/FatalError", 444, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 487, ResourceLimitWarning },
    { "Stream/Error", 488, StreamError },
    { "Stream/FatalError", 494, StreamFatalError },
    { "Stream/Warning", 495, StreamWarning },
    { "Type/Error", 496, TypeError },
    { "Type/FatalError", 501, TypeFatalError },
    { "Type/Warning", 502, TypeWarning },
    { "Wand/Error", 503, WandError },
    { "XServer/Error", 507, XServerError },
    { "XServer/FatalError", 529, XServerFatalError },
    { "XServer/Warning", 545, XServerWarning },
    { 0, 547, UndefinedException }
  };
#endif

#if defined(_INCLUDE_TAGMAP_TABLE_)
typedef struct _MessageInfo
{
  const char *name;
  int messageid;
} MessageInfo;

static const MessageInfo message_map[] =
  {
    { "UnableToCreateBlob", 1 },
    { "UnableToObtainOffset", 2 },
    { "UnableToOpenFile", 3 },
    { "UnableToReadFile", 4 },
    { "UnableToReadToOffset", 5 },
    { "UnableToSeekToOffset", 6 },
    { "UnableToWriteBlob", 7 },
    { "UnrecognizedImageFormat", 8 },
    { "Default", 9 },
    { "Default", 10 },
    { "InconsistentPersistentCacheDepth", 11 },
    { "PixelCacheIsNotOpen", 12 },
    { "UnableToAllocateCacheView", 13 },
    { "UnableToCloneCache", 14 },
    { "UnableToExtendCache", 15 },
    { "UnableToGetCacheNexus", 16 },
    { "UnableToGetPixelsFromCache", 17 },
    { "UnableToOpenCache", 18 },
    { "UnableToPeristPixelCache", 19 },
    { "UnableToReadPixelCache", 20 },
    { "UnableToSyncCache", 21 },
    { "DiskAllocationFailed", 22 },
    { "UnableToExtendPixelCache", 23 },
    { "Default", 24 },
    { "ColormapTooLarge", 25 },
    { "ColormapTypeNotSupported", 26 },
    { "ColorspaceModelIsNotSupported", 27 },
    { "ColorTypeNotSupported", 28 },
    { "CompressionNotValid", 29 },
    { "DataEncodingSchemeIsNotSupported", 30 },
    { "DataStorageTypeIsNotSupported", 31 },
    { "DeltaPNGNotSupported", 32 },
    { "EncryptedWPGImageFileNotSupported", 33 },
    { "FractalCompressionNotSupported", 34 },
    { "ImageColumnOrRowSizeIsNotSupported", 35 },
    { "ImageDoesNotHaveAMatteChannel", 36 },
    { "ImageIsNotTiled", 37 },
    { "ImageTypeNotSupported", 38 },
    { "IncompatibleSizeOfDouble", 39 },
    { "IrregularChannelGeometryNotSupported", 40 },
    { "JNGCompressionNotSupported", 41 },
    { "JPEGCompressionNotSupported", 42 },
    { "JPEGEmbeddingFailed", 43 },
    { "LocationTypeIsNotSupported", 44 },
    { "MapStorageTypeIsNotSupported", 45 },
    { "MSBByteOrderNotSupported", 46 },
    { "MultidimensionalMatricesAreNotSupported", 47 },
    { "MultipleRecordListNotSupported", 48 },
    { "No8BIMDataIsAvailable", 49 },
    { "NoAPP1DataIsAvailable", 50 },
    { "NoBitmapOnClipboard", 51 },
    { "NoColorProfileAvailable", 52 },
    { "NoDataReturned", 53 },
    { "NoImageVectorGraphics", 54 },
    { "NoIPTCInfoWasFound", 55 },
    { "NoIPTCProfileAvailable", 56 },
    { "NumberOfImagesIsNotSupported", 57 },
    { "OnlyContinuousTonePictureSupported", 58 },
    { "OnlyLevelZerofilesSupported", 59 },
    { "PNGCompressionNotSupported", 60 },
    { "PNGLibraryTooOld", 61 },
    { "RLECompressionNotSupported", 62 },
    { "SubsamplingRequiresEvenWidth", 63 },
    { "UnableToCopyProfile", 64 },
    { "UnableToCreateADC", 65 },
    { "UnableToCreateBitmap", 66 },
    { "UnableToDecompressImage", 67 },
    { "UnableToInitializeFPXLibrary", 68 },
    { "UnableToOpenBlob", 69 },
    { "UnableToReadAspectRatio", 70 },
    { "UnableToReadCIELABImages", 71 },
    { "UnableToReadSummaryInfo", 72 },
    { "UnableToSetAffineMatrix", 73 },
    { "UnableToSetAspectRatio", 74 },
    { "UnableToSetColorTwist", 75 },
    { "UnableToSetContrast", 76 },
    { "UnableToSetFilteringValue", 77 },
    { "UnableToSetImageComments", 78 },
    { "UnableToSetImageTitle", 79 },
    { "UnableToSetJPEGLevel", 80 },
    { "UnableToSetRegionOfInterest", 81 },
    { "UnableToSetSummaryInfo", 82 },
    { "UnableToTranslateText", 83 },
    { "UnableToWriteMPEGParameters", 84 },
    { "UnableToWriteTemporaryFile", 85 },
    { "UnableToZipCompressImage", 86 },
    { "UnsupportedCellTypeInTheMatrix", 87 },
    { "WebPDecodingFailedUserAbort", 88 },
    { "WebPEncodingFailed", 89 },
    { "WebPEncodingFailedBadDimension", 90 },
    { "WebPEncodingFailedBadWrite", 91 },
    { "WebPEncodingFailedBitstreamOutOfMemory", 92 },
    { "WebPEncodingFailedFileTooBig", 93 },
    { "WebPEncodingFailedInvalidConfiguration", 94 },
    { "WebPEncodingFailedNULLParameter", 95 },
    { "WebPEncodingFailedOutOfMemory", 96 },
    { "WebPEncodingFailedPartition0Overflow", 97 },
    { "WebPEncodingFailedPartitionOverflow", 98 },
    { "WebPEncodingFailedUserAbort", 99 },
    { "WebPInvalidConfiguration", 100 },
    { "WebPInvalidParameter", 101 },
    { "ZipCompressionNotSupported", 102 },
    { "Default", 103 },
    { "LosslessToLossyJPEGConversion", 104 },
    { "IncludeElementNestedTooDeeply", 105 },
    { "RegistryKeyLookupFailed", 106 },
    { "StringTokenLengthExceeded", 107 },
    { "UnableToAccessConfigureFile", 108 },
    { "UnableToAccessFontFile", 109 },
    { "UnableToAccessLogFile", 110 },
    { "UnableToAccessModuleFile", 111 },
    { "Default", 112 },
    { "UnableToChangeToWorkingDirectory", 113 },
    { "UnableToGetCurrentDirectory", 114 },
    { "UnableToRestoreCurrentDirectory", 115 },
    { "Default", 116 },
    { "AnErrorHasOccurredReadingFromFile", 117 },
    { "AnErrorHasOccurredWritingToFile", 118 },
    { "ColormapExceedsColorsLimit", 119 },
    { "CompressionNotValid", 120 },
    { "CorruptImage", 121 },
    { "ImageFileDoesNotContainAnyImageData", 122 },
    { "ImageTypeNotSupported", 123 },
    { "ImproperImageHeader", 124 },
    { "InsufficientImageDataInFile", 125 },
    { "InvalidColormapIndex", 126 },
    { "InvalidFileFormatVersion", 127 },
    { "LengthAndFilesizeDoNotMatch", 128 },
    { "MissingImageChannel", 129 },
    { "NegativeOrZeroImageSize", 130 },
    { "NonOS2HeaderSizeError", 131 },
    { "NotEnoughTiles", 132 },
    { "StaticPlanesValueNotEqualToOne", 133 },
    { "SubsamplingRequiresEvenWidth", 134 },
    { "TooMuchImageDataInFile", 135 },
    { "UnableToReadColormapFromDumpFile", 136 },
    { "UnableToReadColorProfile", 137 },
    { "UnableToReadExtensionBlock", 138 },
    { "UnableToReadGenericProfile", 139 },
    { "UnableToReadImageData", 140 },
    { "UnableToReadImageHeader", 141 },
    { "UnableToReadIPTCProfile", 142 },
    { "UnableToReadPixmapFromDumpFile", 143 },
    { "UnableToReadSubImageData", 144 },
    { "UnableToReadVIDImage", 145 },
    { "UnableToReadWindowNameFromDumpFile", 146 },
    { "UnableToRunlengthDecodeImage", 147 },
    { "UnableToUncompressImage", 148 },
    { "UnexpectedEndOfFile", 149 },
    { "UnexpectedSamplingFactor", 150 },
    { "UnknownPatternType", 151 },
    { "UnrecognizedBitsPerPixel", 152 },
    { "UnrecognizedImageCompression", 153 },
    { "UnrecognizedNumberOfColors", 154 },
    { "UnrecognizedXWDHeader", 155 },
    { "UnableToPersistKey", 156 },
    { "CompressionNotValid", 157 },
    { "ImproperImageHeader", 158 },
    { "LengthAndFilesizeDoNotMatch", 159 },
    { "NegativeOrZeroImageSize", 160 },
    { "NonOS2HeaderSizeError", 161 },
    { "SkipToSyncByte", 162 },
    { "StaticPlanesValueNotEqualToOne", 163 },
    { "UnrecognizedBitsPerPixel", 164 },
    { "UnrecognizedImageCompression", 165 },
    { "DelegateFailed", 166 },
    { "FailedToAllocateArgumentList", 167 },
    { "FailedToAllocateGhostscriptInterpreter", 168 },
    { "FailedToComputeOutputSize", 169 },
    { "FailedToFindGhostscript", 170 },
    { "FailedToRenderFile", 171 },
    { "FailedToScanFile", 172 },
    { "NoTagFound", 173 },
    { "PostscriptDelegateFailed", 174 },
    { "UnableToCreateImage", 175 },
    { "UnableToCreateImageComponent", 176 },
    { "UnableToDecodeImageFile", 177 },
    { "UnableToEncodeImageFile", 178 },
    { "UnableToInitializeFPXLibrary", 179 },
    { "UnableToInitializeWMFLibrary", 180 },
    { "UnableToManageJP2Stream", 181 },
    { "UnableToWriteSVGFormat", 182 },
    { "WebPABIMismatch", 183 },
    { "Default", 184 },
    { "Default", 185 },
    { "AlreadyPushingPatternDefinition", 186 },
    { "FloatValueConversionError", 187 },
    { "IntegerValueConversionError", 188 },
    { "NonconformingDrawingPrimitiveDefinition", 189 },
    { "TooManyCoordinates", 190 },
    { "UnableToPrint", 191 },
    { "UnbalancedGraphicContextPushPop", 192 },
    { "VectorPathTruncated", 193 },
    { "Default", 194 },
    { "NotARelativeURL", 195 },
    { "NotCurrentlyPushingPatternDefinition", 196 },
    { "URLNotFound", 197 },
    { "UnableToCreateTemporaryFile", 198 },
    { "UnableToOpenFile", 199 },
    { "UnableToWriteFile", 200 },
    { "Default", 201 },
    { "Default", 202 },
    { "AngleIsDiscontinuous", 203 },
    { "ColorspaceColorProfileMismatch", 204 },
    { "ImageColorspaceDiffers", 205 },
    { "ImageColorspaceMismatch", 206 },
    { "ImageDifferenceExceedsLimit", 207 },
    { "ImageDoesNotContainResolution", 208 },
    { "ImageOpacityDiffers", 209 },
    { "ImageSequenceIsRequired", 210 },
    { "ImageSizeDiffers", 211 },
    { "InvalidColormapIndex", 212 },
    { "LeftAndRightImageSizesDiffer", 213 },
    { "NoImagesWereFound", 214 },
    { "NoImagesWereLoaded", 215 },
    { "NoLocaleImageAttribute", 216 },
    { "TooManyClusters", 217 },
    { "UnableToAppendImage", 218 },
    { "UnableToAssignProfile", 219 },
    { "UnableToAverageImage", 220 },
    { "UnableToCoalesceImage", 221 },
    { "UnableToCompareImages", 222 },
    { "UnableToCreateImageMosaic", 223 },
    { "UnableToCreateStereoImage", 224 },
    { "UnableToDeconstructImageSequence", 225 },
    { "UnableToFlattenImage", 226 },
    { "UnableToGetClipMask", 227 },
    { "UnableToHandleImageChannel", 228 },
    { "UnableToResizeImage", 229 },
    { "UnableToSegmentImage", 230 },
    { "UnableToSetClipMask", 231 },
    { "UnableToShearImage", 232 },
    { "WidthOrHeightExceedsLimit", 233 },
    { "UnableToPersistKey", 234 },
    { "Default", 235 },
    { "DPSLibraryIsNotAvailable", 236 },
    { "FPXLibraryIsNotAvailable", 237 },
    { "FreeTypeLibraryIsNotAvailable", 238 },
    { "JPEGLibraryIsNotAvailable", 239 },
    { "LCMSLibraryIsNotAvailable", 240 },
    { "LZWEncodingNotEnabled", 241 },
    { "NoDecodeDelegateForThisImageFormat", 242 },
    { "NoEncodeDelegateForThisImageFormat", 243 },
    { "TIFFLibraryIsNotAvailable", 244 },
    { "XMLLibraryIsNotAvailable", 245 },
    { "XWindowLibraryIsNotAvailable", 246 },
    { "ZipLibraryIsNotAvailable", 247 },
    { "Default", 248 },
    { "Default", 249 },
    { "FailedToCloseModule", 250 },
    { "FailedToFindSymbol", 251 },
    { "UnableToLoadModule", 252 },
    { "UnableToRegisterImageFormat", 253 },
    { "UnrecognizedModule", 254 },
    { "UnableToInitializeModuleLoader", 255 },
    { "Default", 256 },
    { "Default", 257 },
    { "Default", 258 },
    { "UserRequestedTerminationBySignal", 259 },
    { "Default", 260 },
    { "BevelWidthIsNegative", 261 },
    { "ColorSeparatedImageRequired", 262 },
    { "FrameIsLessThanImageSize", 263 },
    { "GeometryDimensionsAreZero", 264 },
    { "GeometryDoesNotContainImage", 265 },
    { "HaldClutImageDimensionsInvalid", 266 },
    { "ImagesAreNotTheSameSize", 267 },
    { "ImageSizeMustExceedBevelWidth", 268 },
    { "ImageSmallerThanKernelWidth", 269 },
    { "ImageSmallerThanRadius", 270 },
    { "ImageWidthsOrHeightsDiffer", 271 },
    { "InputImagesAlreadySpecified", 272 },
    { "InvalidSubimageSpecification", 273 },
    { "KernelRadiusIsTooSmall", 274 },
    { "KernelWidthMustBeAnOddNumber", 275 },
    { "MatrixIsNotSquare", 276 },
    { "MatrixOrderOutOfRange", 277 },
    { "MissingAnImageFilename", 278 },
    { "MissingArgument", 279 },
    { "MustSpecifyAnImageName", 280 },
    { "MustSpecifyImageSize", 281 },
    { "NoBlobDefined", 282 },
    { "NoImagesDefined", 283 },
    { "NonzeroWidthAndHeightRequired", 284 },
    { "NoProfileNameWasGiven", 285 },
    { "NullBlobArgument", 286 },
    { "ReferenceImageRequired", 287 },
    { "ReferenceIsNotMyType", 288 },
    { "RegionAreaExceedsLimit", 289 },
    { "RequestDidNotReturnAnImage", 290 },
    { "SteganoImageRequired", 291 },
    { "StereoImageRequired", 292 },
    { "SubimageSpecificationReturnsNoImages", 293 },
    { "UnableToAddOrRemoveProfile", 294 },
    { "UnableToAverageImageSequence", 295 },
    { "UnableToBlurImage", 296 },
    { "UnableToChopImage", 297 },
    { "UnableToColorMatrixImage", 298 },
    { "UnableToConstituteImage", 299 },
    { "UnableToConvolveImage", 300 },
    { "UnableToEdgeImage", 301 },
    { "UnableToEqualizeImage", 302 },
    { "UnableToFilterImage", 303 },
    { "UnableToFormatImageMetadata", 304 },
    { "UnableToFrameImage", 305 },
    { "UnableToOilPaintImage", 306 },
    { "UnableToPaintImage", 307 },
    { "UnableToRaiseImage", 308 },
    { "UnableToSharpenImage", 309 },
    { "UnableToThresholdImage", 310 },
    { "UnableToWaveImage", 311 },
    { "UnrecognizedAttribute", 312 },
    { "UnrecognizedChannelType", 313 },
    { "UnrecognizedColor", 314 },
    { "UnrecognizedColormapType", 315 },
    { "UnrecognizedColorspace", 316 },
    { "UnrecognizedCommand", 317 },
    { "UnrecognizedComposeOperator", 318 },
    { "UnrecognizedDisposeMethod", 319 },
    { "UnrecognizedElement", 320 },
    { "UnrecognizedEndianType", 321 },
    { "UnrecognizedGravityType", 322 },
    { "UnrecognizedHighlightStyle", 323 },
    { "UnrecognizedImageCompression", 324 },
    { "UnrecognizedImageFilter", 325 },
    { "UnrecognizedImageFormat", 326 },
    { "UnrecognizedImageMode", 327 },
    { "UnrecognizedImageType", 328 },
    { "UnrecognizedIntentType", 329 },
    { "UnrecognizedInterlaceType", 330 },
    { "UnrecognizedListType", 331 },
    { "UnrecognizedMetric", 332 },
    { "UnrecognizedModeType", 333 },
    { "UnrecognizedNoiseType", 334 },
    { "UnrecognizedOperator", 335 },
    { "UnrecognizedOption", 336 },
    { "UnrecognizedPerlMagickMethod", 337 },
    { "UnrecognizedPixelMap", 338 },
    { "UnrecognizedPreviewType", 339 },
    { "UnrecognizedResourceType", 340 },
    { "UnrecognizedType", 341 },
    { "UnrecognizedUnitsType", 342 },
    { "UnrecognizedVirtualPixelMethod", 343 },
    { "UnsupportedSamplingFactor", 344 },
    { "UsageError", 345 },
    { "InvalidColorspaceType", 346 },
    { "InvalidEndianType", 347 },
    { "InvalidImageType", 348 },
    { "InvalidInterlaceType", 349 },
    { "MissingAnImageFilename", 350 },
    { "MissingArgument", 351 },
    { "NoImagesWereLoaded", 352 },
    { "OptionLengthExceedsLimit", 353 },
    { "RequestDidNotReturnAnImage", 354 },
    { "UnableToOpenXServer", 355 },
    { "UnableToPersistKey", 356 },
    { "UnrecognizedColormapType", 357 },
    { "UnrecognizedColorspaceType", 358 },
    { "UnrecognizedDisposeMethod", 359 },
    { "UnrecognizedEndianType", 360 },
    { "UnrecognizedFilterType", 361 },
    { "UnrecognizedImageCompressionType", 362 },
    { "UnrecognizedImageType", 363 },
    { "UnrecognizedInterlaceType", 364 },
    { "UnrecognizedOption", 365 },
    { "UnrecognizedResourceType", 366 },
    { "UnrecognizedVirtualPixelMethod", 367 },
    { "UnrecognizedColor", 368 },
    { "ImageExpected", 369 },
    { "ImageInfoExpected", 370 },
    { "StructureSizeMismatch", 371 },
    { "UnableToGetRegistryID", 372 },
    { "UnableToLocateImage", 373 },
    { "UnableToSetRegistry", 374 },
    { "Default", 375 },
    { "Default", 376 },
    { "CacheResourcesExhausted", 377 },
    { "ImagePixelHeightLimitExceeded", 378 },
    { "ImagePixelLimitExceeded", 379 },
    { "ImagePixelWidthLimitExceeded", 380 },
    { "MemoryAllocationFailed", 381 },
    { "NoPixelsDefinedInCache", 382 },
    { "PixelCacheAllocationFailed", 383 },
    { "UnableToAddColorProfile", 384 },
    { "UnableToAddGenericProfile", 385 },
    { "UnableToAddIPTCProfile", 386 },
    { "UnableToAllocateCoefficients", 387 },
    { "UnableToAllocateColormap", 388 },
    { "UnableToAllocateICCProfile", 389 },
    { "UnableToAllocateString", 390 },
    { "UnableToAnnotateImage", 391 },
    { "UnableToAverageImageSequence", 392 },
    { "UnableToCloneDrawingWand", 393 },
    { "UnableToCloneImage", 394 },
    { "UnableToComputeImageSignature", 395 },
    { "UnableToConstituteImage", 396 },
    { "UnableToConvertFont", 397 },
    { "UnableToConvertStringToTokens", 398 },
    { "UnableToCreateColormap", 399 },
    { "UnableToCreateColorTransform", 400 },
    { "UnableToCreateCommandWidget", 401 },
    { "UnableToCreateImageGroup", 402 },
    { "UnableToCreateImageMontage", 403 },
    { "UnableToCreateXWindow", 404 },
    { "UnableToCropImage", 405 },
    { "UnableToDespeckleImage", 406 },
    { "UnableToDetermineImageClass", 407 },
    { "UnableToDetermineTheNumberOfImageColors", 408 },
    { "UnableToDitherImage", 409 },
    { "UnableToDrawOnImage", 410 },
    { "UnableToEdgeImage", 411 },
    { "UnableToEmbossImage", 412 },
    { "UnableToEnhanceImage", 413 },
    { "UnableToFloodfillImage", 414 },
    { "UnableToGammaCorrectImage", 415 },
    { "UnableToGetBestIconSize", 416 },
    { "UnableToGetFromRegistry", 417 },
    { "UnableToGetPackageInfo", 418 },
    { "UnableToLevelImage", 419 },
    { "UnableToMagnifyImage", 420 },
    { "UnableToManageColor", 421 },
    { "UnableToMapImage", 422 },
    { "UnableToMapImageSequence", 423 },
    { "UnableToMedianFilterImage", 424 },
    { "UnableToMotionBlurImage", 425 },
    { "UnableToNoiseFilterImage", 426 },
    { "UnableToNormalizeImage", 427 },
    { "UnableToOpenColorProfile", 428 },
    { "UnableToQuantizeImage", 429 },
    { "UnableToQuantizeImageSequence", 430 },
    { "UnableToReadTextChunk", 431 },
    { "UnableToReadXImage", 432 },
    { "UnableToReadXServerColormap", 433 },
    { "UnableToResizeImage", 434 },
    { "UnableToRotateImage", 435 },
    { "UnableToSampleImage", 436 },
    { "UnableToScaleImage", 437 },
    { "UnableToSelectImage", 438 },
    { "UnableToSharpenImage", 439 },
    { "UnableToShaveImage", 440 },
    { "UnableToShearImage", 441 },
    { "UnableToSortImageColormap", 442 },
    { "UnableToThresholdImage", 443 },
    { "UnableToTransformColorspace", 444 },
    { "MemoryAllocationFailed", 445 },
    { "SemaporeOperationFailed", 446 },
    { "UnableToAllocateAscii85Info", 447 },
    { "UnableToAllocateCacheInfo", 448 },
    { "UnableToAllocateCacheView", 449 },
    { "UnableToAllocateColorInfo", 450 },
    { "UnableToAllocateDashPattern", 451 },
    { "UnableToAllocateDelegateInfo", 452 },
    { "UnableToAllocateDerivatives", 453 },
    { "UnableToAllocateDrawContext", 454 },
    { "UnableToAllocateDrawInfo", 455 },
    { "UnableToAllocateDrawingWand", 456 },
    { "UnableToAllocateGammaMap", 457 },
    { "UnableToAllocateImage", 458 },
    { "UnableToAllocateImagePixels", 459 },
    { "UnableToAllocateLogInfo", 460 },
    { "UnableToAllocateMagicInfo", 461 },
    { "UnableToAllocateMagickInfo", 462 },
    { "UnableToAllocateModuleInfo", 463 },
    { "UnableToAllocateMontageInfo", 464 },
    { "UnableToAllocateQuantizeInfo", 465 },
    { "UnableToAllocateRandomKernel", 466 },
    { "UnableToAllocateRegistryInfo", 467 },
    { "UnableToAllocateSemaphoreInfo", 468 },
    { "UnableToAllocateString", 469 },
    { "UnableToAllocateTypeInfo", 470 },
    { "UnableToAllocateWand", 471 },
    { "UnableToAnimateImageSequence", 472 },
    { "UnableToCloneBlobInfo", 473 },
    { "UnableToCloneCacheInfo", 474 },
    { "UnableToCloneImage", 475 },
    { "UnableToCloneImageInfo", 476 },
    { "UnableToConcatenateString", 477 },
    { "UnableToConvertText", 478 },
    { "UnableToCreateColormap", 479 },
    { "UnableToDestroySemaphore", 480 },
    { "UnableToDisplayImage", 481 },
    { "UnableToEscapeString", 482 },
    { "UnableToInitializeSemaphore", 483 },
    { "UnableToInterpretMSLImage", 484 },
    { "UnableToLockSemaphore", 485 },
    { "UnableToObtainRandomEntropy", 486 },
    { "UnableToUnlockSemaphore", 487 },
    { "MemoryAllocationFailed", 488 },
    { "ImageDoesNotContainTheStreamGeometry", 489 },
    { "NoStreamHandlerIsDefined", 490 },
    { "PixelCacheIsNotOpen", 491 },
    { "UnableToAcquirePixelStream", 492 },
    { "UnableToSetPixelStream", 493 },
    { "UnableToSyncPixelStream", 494 },
    { "Default", 495 },
    { "Default", 496 },
    { "FontSubstitutionRequired", 497 },
    { "UnableToGetTypeMetrics", 498 },
    { "UnableToInitializeFreetypeLibrary", 499 },
    { "UnableToReadFont", 500 },
    { "UnrecognizedFontEncoding", 501 },
    { "Default", 502 },
    { "Default", 503 },
    { "InvalidColormapIndex", 504 },
    { "WandAPINotImplemented", 505 },
    { "WandContainsNoImageIndexs", 506 },
    { "WandContainsNoImages", 507 },
    { "ColorIsNotKnownToServer", 508 },
    { "NoWindowWithSpecifiedIDExists", 509 },
    { "StandardColormapIsNotInitialized", 510 },
    { "UnableToConnectToRemoteDisplay", 511 },
    { "UnableToCreateBitmap", 512 },
    { "UnableToCreateColormap", 513 },
    { "UnableToCreatePixmap", 514 },
    { "UnableToCreateProperty", 515 },
    { "UnableToCreateStandardColormap", 516 },
    { "UnableToDisplayImageInfo", 517 },
    { "UnableToGetProperty", 518 },
    { "UnableToGetStandardColormap", 519 },
    { "UnableToGetVisual", 520 },
    { "UnableToGrabMouse", 521 },
    { "UnableToLoadFont", 522 },
    { "UnableToMatchVisualToStandardColormap", 523 },
    { "UnableToOpenXServer", 524 },
    { "UnableToReadXAttributes", 525 },
    { "UnableToReadXWindowImage", 526 },
    { "UnrecognizedColormapType", 527 },
    { "UnrecognizedGravityType", 528 },
    { "UnrecognizedVisualSpecifier", 529 },
    { "UnableToAllocateXHints", 530 },
    { "UnableToCreateCursor", 531 },
    { "UnableToCreateGraphicContext", 532 },
    { "UnableToCreateStandardColormap", 533 },
    { "UnableToCreateTextProperty", 534 },
    { "UnableToCreateXImage", 535 },
    { "UnableToCreateXPixmap", 536 },
    { "UnableToCreateXWindow", 537 },
    { "UnableToDisplayImage", 538 },
    { "UnableToDitherImage", 539 },
    { "UnableToGetPixelInfo", 540 },
    { "UnableToGetVisual", 541 },
    { "UnableToLoadFont", 542 },
    { "UnableToMakeXWindow", 543 },
    { "UnableToOpenXServer", 544 },
    { "UnableToViewFonts", 545 },
    { "UnableToGetVisual", 546 },
    { "UsingDefaultVisual", 547 },
    { 0, 0 }
  };
#endif

#if defined(_INCLUDE_MESSAGE_TABLE_)
static const char *message_dat[] =
  {
    "%1",
    "Unable to create blob",
    "Unable to obtain current offset",
    "Unable to open file",
    "Unable to read file",
    "Unable to read to offset",
    "Unable to seek to offset",
    "Unable to write blob",
    "Unrecognized image format",
    "default error",
    "default warning",
    "Inconsistent persistent cache depth",
    "Pixel cache is not open",
    "Unable to allocate cache view",
    "Unable to clone cache",
    "Unable to extend cache",
    "Unable to get cache nexus",
    "Unable to get pixels from cache",
    "Unable to open cache",
    "Unable to persist pixel cache",
    "Unable to read pixel cache",
    "Unable to sync cache (check temporary file disk space)",
    "disk allocation failed",
    "Unable to extend pixel cache",
    "default warning",
    "Colormap size exceeds limit",
    "Colormap type not supported",
    "Colorspace model is not supported",
    "Color type not supported",
    "Compression not valid",
    "Data encoding scheme is not supported",
    "Data storage type is not supported",
    "Delta-PNG is not supported",
    "Encrypted WPG image file not supported",
    "Fractal compression not supported",
    "Image column or row size is not supported",
    "Image does not have a matte channel",
    "Image is not tiles",
    "Image type not supported",
    "Incompatible size of double",
    "Irregular channel geometry not supported",
    "JNG compression is not supported",
    "JPEG compression is not supported",
    "JPEG embedding failed",
    "Location type is not supported",
    "Map storage type is not supported",
    "MSB order not supported bitmap",
    "Multi-dimensional matrices are not supported",
    "Multiple record list not supported",
    "No 8BIM data is available",
    "No APP1 data is available",
    "No bitmap on clipboard",
    "No color profile available",
    "No data returned",
    "No image vector graphics",
    "No IPTC info was found",
    "No IPTC profile available",
    "Number of images is not supported",
    "Only continuous tone picture supported",
    "Only level zero files Supported",
    "PNG compression is not supported",
    "PNG library is too old",
    "RLE compression not supported",
    "Subsampling requires that image width be evenly divisible by two",
    "Unable to copy profile",
    "Unable to create a DC",
    "Unable to create bitmap",
    "Unable to decompress image",
    "Unable to Initialize FPX library",
    "Unable to open blob",
    "Unable to read aspect ratio",
    "Unable to read CIELAB images",
    "Unable to read summary info",
    "Unable to set affine matrix",
    "Unable to set aspect ratio",
    "Unable to set color twist",
    "Unable to set contrast",
    "Unable to set filtering value",
    "Unable to set image comment",
    "Unable to set image title",
    "Unable to set JPEG level",
    "Unable to set region of interest",
    "Unable to set summary info",
    "Unable to translate text",
    "Unable to write MPEG parameters",
    "Unable to write to temporary file",
    "Unable to zip-compress image",
    "Unsupported cell type in the matrix",
    "WebP decoding failed: user abort",
    "WebP encoding failed: unknown reason",
    "WebP encoding failed: bad dimension",
    "WebP encoding failed: bad write",
    "WebP encoding failed: bitstream out of memory",
    "WebP encoding failed: File too big (> 4GB)",
    "WebP encoding failed: invalid configuration",
    "WebP encoding failed: null parameter",
    "WebP encoding failed: out of memory",
    "WebP encoding failed: partition 0 overflow (> 512K)",
    "WebP encoding failed: partition overflow (> 16M)",
    "WebP encoding failed: user abort",
    "Invalid WebP configuration parameters supplied",
    "WebP failed: invalid parameter",
    "ZIP compression is not supported",
    "default error",
    "Lossless to lossy JPEG conversion",
    "include element nested too deeply",
    "Registry key lookup failed. Package is not properly installed on this machine.",
    "String token maximum length exceeded",
    "Unable to access configuration file",
    "Unable to access font file",
    "Unable to access log configuration file",
    "Unable to access module file",
    "default error",
    "Unable to change to working directory",
    "Unable to get current working directory",
    "Unable to restore current working directory",
    "default warning",
    "An error has occurred reading from file",
    "An error has occurred writing to file",
    "Colormap exceeded colors limit",
    "Compression not valid",
    "Corrupt image",
    "Image file or blob does not contain any image data",
    "Image type not supported",
    "Improper image header",
    "Insufficient image data in file",
    "Invalid colormap index",
    "invalid file format version",
    "Length and filesize do not match",
    "Missing a required image channel",
    "Negative or zero image size",
    "Non OS2 BMP header size less than 40",
    "Not enough tiles found in level",
    "Static planes value not equal to 1",
    "Subsampling requires that image width be evenly divisible by two",
    "Too much image data in file",
    "Unable to read colormap from dump file",
    "Unable to read color profile",
    "Unable to read extension block",
    "Unable to read generic profile",
    "Unable to read image data",
    "Unable to read image header",
    "Unable to read IPTC profile",
    "Unable to read pixmap from dump file",
    "Unable to read sub image data",
    "Unable to read VID image",
    "Unable to read window name from dump file",
    "Unable to runlength decode image",
    "Unable to uncompress image",
    "Unexpected end-of-file",
    "Unexpected sampling factor",
    "Unknown pattern type",
    "Unrecognized bits per pixel",
    "Unrecognized compression",
    "Unrecognized number of colors",
    "Unrecognized XWD header",
    "Unable to persist key",
    "Compression not valid",
    "Improper image header",
    "Length and filesize do not match",
    "Negative or zero image size",
    "Non OS2 header size error",
    "Corrupt PCD image, skipping to sync byte",
    "Static planes value not equal to one",
    "Unrecognized bits per pixel",
    "Unrecognized image compression",
    "Delegate failed",
    "Failed to allocate argument list.",
    "Failed to allocate Ghostscript interpreter.",
    "Failed to compute output size",
    "Failed to find Ghostscript (not installed?).",
    "Failed to render file",
    "Failed to scan file",
    "No tag found",
    "Postscript delegate failed",
    "Unable to create image",
    "Unable to create image component",
    "Unable to decode image file",
    "Unable to encode image file",
    "Unable to initialize FPX library",
    "Unable to initialize WMF library",
    "Unable to manage JP2 stream",
    "Unable to write SVG format",
    "WebP library ABI does not match header ABI (build issue!)",
    "default error",
    "default warning",
    "Already pushing pattern definition",
    "text value does not convert to float",
    "text value does not convert to integer",
    "Non-conforming drawing primitive definition",
    "too many coordinates",
    "Unable to print",
    "unbalanced graphic context push-pop",
    "vector path truncated",
    "default error",
    "Not a relative URL",
    "Not currently pushing pattern definition",
    "URL not found",
    "Unable to create temporary file",
    "Unable to open file",
    "Unable to write file",
    "default error",
    "default warning",
    "angle is discontinuous",
    "Colorspace color profile mismatch",
    "image colorspace differs",
    "image colorspace mismatch",
    "image difference exceeds limit (%s)",
    "image does not contain resolution",
    "image opacity differs",
    "Image sequence is required",
    "image size differs",
    "Invalid colormap index",
    "left and right image sizes differ",
    "no images were found",
    "no images were loaded",
    "no [LOCALE] image attribute",
    "too many cluster",
    "unable to append image",
    "Unable to assign profile",
    "unable to average image",
    "unable to coalesce image",
    "unable to compare images",
    "unable to create image mosaic",
    "unable to create stereo image",
    "unable to deconstruct image sequence",
    "unable to flatten image",
    "Unable to get clip mask",
    "unable to handle image channel",
    "unable to resize image",
    "unable to segment image",
    "Unable to set clip mask",
    "unable to shear image",
    "width or height exceeds limit",
    "Unable to persist key",
    "default warning",
    "DPS library is not available",
    "FPX library is not available",
    "FreeType library is not available",
    "JPEG compression library is not available",
    "LCMS encoding not enabled",
    "LZW encoding not enabled",
    "No decode delegate for this image format",
    "No encode delegate for this image format",
    "TIFF library is not available",
    "XML library is not available",
    "X Window library is not available",
    "ZLIB compression library is not available",
    "default error",
    "default warning",
    "Failed to close module",
    "Failed to find symbol",
    "Unable to load module",
    "Unable to register image format",
    "Unrecognized module",
    "Unable to initialize module loader",
    "default warning",
    "default error",
    "default error",
    "User requested termination (via signal)",
    "default warning",
    "bevel width is negative",
    "color separated image required",
    "frame is less than image size",
    "geometry dimensions are zero",
    "geometry does not contain image",
    "hald clut image dimensions are invalid",
    "images are not the same size",
    "size must exceed bevel width",
    "image smaller than kernel width",
    "image smaller than radius",
    "image widths or heights differ",
    "input images already specified",
    "Invalid subimage specification",
    "kernel radius is too small",
    "kernel width must be an odd number",
    "Matrix is not square (%s elements)",
    "Matrix size is out of range",
    "Missing an image filename",
    "Option '%s' requires an argument or argument is malformed",
    "Must specify a image name",
    "Must specify image size",
    "No Binary Large OBjects defined",
    "No images defined",
    "Non-zero width and height required",
    "No profile name was given",
    "Null blob argument",
    "Reference image required",
    "Reference is not my type",
    "Region area exceeds implementation limit",
    "Request did not return an image",
    "Stegano image required",
    "Stereo image required",
    "Subimage specification returns no images",
    "Unable to add or remove profile",
    "unable to average image sequence",
    "unable to blur image",
    "unable to chop image",
    "Unable to color matrix image",
    "Unable to constitute image",
    "Unable to convolve image",
    "Unable to edge image",
    "Unable to equalize image",
    "Unable to filter image",
    "unable to format image meta data",
    "Unable to frame image",
    "unable to oil paint image",
    "Unable to paint image",
    "Unable to raise image",
    "Unable to sharpen image",
    "Unable to threshold image",
    "Unable to wave image",
    "Unrecognized attribute",
    "Unrecognized channel type",
    "Unrecognized color",
    "Unrecognized colormap type",
    "Unrecognized image colorspace",
    "Unrecognized command '%s'. Use -help for a usage summary or see manual.",
    "Unrecognized compose operator",
    "Unrecognized dispose method",
    "Unrecognized element",
    "Unrecognized endian type",
    "Unrecognized gravity type",
    "Unrecognized highlight style",
    "Unrecognized image compression",
    "Unrecognized image filter",
    "Unrecognized image format",
    "Unrecognized image mode",
    "Unrecognized image type",
    "Unrecognized intent type",
    "Unrecognized interlace type",
    "Unrecognized list type",
    "Unrecognized error metric",
    "Unrecognized mode type",
    "Unrecognized noise type",
    "Unrecognized operator",
    "Unrecognized option",
    "Unrecognized PerlMagick method",
    "Unrecognized pixel map",
    "Unrecognized preview type",
    "Unrecognized resource type",
    "Unrecognized type",
    "Unrecognized units type",
    "Unrecognized virtual pixel method",
    "Unsupported sampling factor",
    "Improper arguments supplied, please see manual",
    "Invalid colorspace type",
    "Invalid endian type",
    "Invalid image type",
    "Invalid interlace type",
    "Missing an image filename",
    "Option '%s' requires an argument or argument is malformed",
    "No images were loaded",
    "Option length exceeds limit",
    "Request did not return an image",
    "Unable to open XServer",
    "Unable to persist key",
    "Unrecognized colormap type",
    "Unrecognized colorspace type",
    "unrecognized dispose method",
    "Unrecognized endian type",
    "Unrecognized filter type",
    "unrecognized compression type",
    "Unrecognized image type",
    "Unrecognized interlace type",
    "Unrecognized option",
    "Unrecognized resource type",
    "Unrecognized virtual pixel method",
    "Unrecognized color",
    "image expected",
    "image info expected",
    "structure size mismatch",
    "Unable to get registry ID",
    "Unable to locate image",
    "Unable to set registry",
    "default error",
    "default warning",
    "Disk space limit exceeded (see -limit Disk)",
    "Image pixel height limit exceeded (see -limit Height)",
    "Image pixel limit exceeded (see -limit Pixels)",
    "Image pixel width limit exceeded (see -limit Width)",
    "Memory allocation failed",
    "No pixels defined in cache",
    "Pixel cache allocation failed",
    "unable to add ICC Color profile",
    "unable to add generic profile",
    "unable to add IPTC profile",
    "unable to allocate coefficients",
    "Unable to allocate colormap",
    "unable to allocate ICC profile",
    "unable to allocate string",
    "Unable to annotate image",
    "unable to average image sequence",
    "unable to clone drawing wand",
    "unable to clone image",
    "unable to compute image signature",
    "unable to constitute image",
    "unable to convert font",
    "unable to convert strings to tokens",
    "Unable to create colormap",
    "unable to create color transform",
    "unable to create command widget",
    "unable to create image group",
    "Unable to create image montage",
    "unable to create X window",
    "unable to crop image",
    "unable to despeckle image",
    "unable to determine image class",
    "unable to determine the number of image colors",
    "unable to dither image",
    "unable to draw on image",
    "unable to edge image",
    "unable to emboss image",
    "unable to enhance image",
    "unable to floodfill image",
    "unable to gamma correct image",
    "unable to get best icon size",
    "unable to get from registry",
    "Unable to get package info",
    "unable to level image",
    "unable to magnify image",
    "Unable to manage color",
    "Unable to map image",
    "Unable to map image sequence",
    "unable to median filter image",
    "unable to motion blur image",
    "unable to noise filter image",
    "unable to normalize image",
    "unable to open color profile",
    "unable to quantize image",
    "unable to quantize image sequence",
    "unable to read text chunk",
    "unable to read X image",
    "unable to read X server colormap",
    "unable to resize image",
    "unable to rotate image",
    "unable to sample image",
    "unable to scale image",
    "unable to select image",
    "unable to sharpen image",
    "unable to shave image",
    "unable to shear image",
    "unable to sort image colormap",
    "unable to threshold image",
    "unable to transform colorspace",
    "Memory allocation failed",
    "Semaphore operation failed",
    "unable to allocate ascii85 info",
    "unable to allocate cache info",
    "unable to allocate cache view",
    "unable to allocate color info",
    "unable to allocate dash pattern",
    "unable to allocate delegate info",
    "unable to allocate derivates",
    "unable to allocate draw context",
    "unable to allocate draw info",
    "unable to allocate drawing wand",
    "unable to allocate gamma map",
    "unable to allocate image",
    "unable to allocate image pixels",
    "unable to allocate log info",
    "unable to allocate magic info",
    "unable to allocate magick info",
    "unable to allocate module info",
    "unable to allocate montage info",
    "unable to allocate quantize info",
    "unable to allocate random kernel",
    "unable to allocate registry info",
    "unable to allocate semaphore info",
    "unable to allocate string",
    "unable to allocate type info",
    "unable to allocate wand",
    "unable to animate image sequence",
    "unable to clone blob info",
    "unable to clone cache info",
    "unable to clone image",
    "unable to clone image info",
    "unable to concatenate string",
    "unable to convert text",
    "unable to create colormap",
    "unable to destroy semaphore",
    "unable to display image",
    "unable to escape string",
    "unable to initialize semaphore",
    "unable to interpret MSL image",
    "unable to lock semaphore",
    "unable to obtain random bytes from operating system",
    "unable to unlock semaphore",
    "Memory allocation failed",
    "image does not contain the stream geometry",
    "no stream handler is defined",
    "Pixel cache is not open",
    "Unable to acquire pixel stream",
    "Unable to set pixel stream",
    "Unable to sync pixel stream",
    "default error",
    "default warning",
    "Font substitution required",
    "Unable to get type metrics",
    "Unable to initialize freetype library",
    "Unable to read font",
    "Unrecognized font encoding",
    "default error",
    "default warning",
    "invalid colormap index `%.1024s",
    "Wand API not implemented `%.1024s",
    "Wand contains no image indices `%.1024s",
    "Wand contains no images `%.1024s",
    "Color is not known to server",
    "No window with specified ID exists",
    "Standard Colormap is not initialized",
    "Unable to connect to remote display",
    "Unable to create bitmap",
    "Unable to create colormap",
    "Unable to create pixmap",
    "Unable to create property",
    "Unable to create standard colormap",
    "Unable to display image info",
    "Unable to get property",
    "Unable to get Standard Colormap",
    "Unable to get visual",
    "Unable to grab mouse",
    "Unable to load font",
    "Unable to match visual to Standard Colormap",
    "Unable to open X server",
    "Unable to read X attributes",
    "Unable to read X window image",
    "Unrecognized colormap type",
    "Unrecognized gravity type",
    "Unrecognized visual specifier",
    "Unable to allocate X hints",
    "Unable to create X cursor",
    "Unable to create graphic context",
    "unable to create standard colormap",
    "Unable to create text property",
    "Unable to create X image",
    "Unable to create X pixmap",
    "Unable to create X window",
    "unable to display image",
    "unable to dither image",
    "Unable to get pixel info",
    "Unable to get visual",
    "Unable to load font",
    "Unable to make X window",
    "Unable to open X server",
    "Unable to view fonts",
    "Unable to get visual",
    "UsingDefaultVisual",
    0
  };
#endif

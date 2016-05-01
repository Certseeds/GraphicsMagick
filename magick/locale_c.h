#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 549

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
#define MGK_CoderErrorUnsupportedBitsPerSample 87
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 88
#define MGK_CoderErrorWebPDecodingFailedUserAbort 89
#define MGK_CoderErrorWebPEncodingFailed 90
#define MGK_CoderErrorWebPEncodingFailedBadDimension 91
#define MGK_CoderErrorWebPEncodingFailedBadWrite 92
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 93
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 94
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 95
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 96
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 97
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 98
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 99
#define MGK_CoderErrorWebPEncodingFailedUserAbort 100
#define MGK_CoderErrorWebPInvalidConfiguration 101
#define MGK_CoderErrorWebPInvalidParameter 102
#define MGK_CoderErrorZipCompressionNotSupported 103
#define MGK_CoderFatalErrorDefault 104
#define MGK_CoderWarningLosslessToLossyJPEGConversion 105
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 106
#define MGK_ConfigureErrorRegistryKeyLookupFailed 107
#define MGK_ConfigureErrorStringTokenLengthExceeded 108
#define MGK_ConfigureErrorUnableToAccessConfigureFile 109
#define MGK_ConfigureErrorUnableToAccessFontFile 110
#define MGK_ConfigureErrorUnableToAccessLogFile 111
#define MGK_ConfigureErrorUnableToAccessModuleFile 112
#define MGK_ConfigureFatalErrorDefault 113
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 114
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 115
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 116
#define MGK_ConfigureWarningDefault 117
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 118
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 119
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 120
#define MGK_CorruptImageErrorCompressionNotValid 121
#define MGK_CorruptImageErrorCorruptImage 122
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 123
#define MGK_CorruptImageErrorImageTypeNotSupported 124
#define MGK_CorruptImageErrorImproperImageHeader 125
#define MGK_CorruptImageErrorInsufficientImageDataInFile 126
#define MGK_CorruptImageErrorInvalidColormapIndex 127
#define MGK_CorruptImageErrorInvalidFileFormatVersion 128
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 129
#define MGK_CorruptImageErrorMissingImageChannel 130
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 131
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 132
#define MGK_CorruptImageErrorNotEnoughTiles 133
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 134
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 135
#define MGK_CorruptImageErrorTooMuchImageDataInFile 136
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 137
#define MGK_CorruptImageErrorUnableToReadColorProfile 138
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 139
#define MGK_CorruptImageErrorUnableToReadGenericProfile 140
#define MGK_CorruptImageErrorUnableToReadImageData 141
#define MGK_CorruptImageErrorUnableToReadImageHeader 142
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 143
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 144
#define MGK_CorruptImageErrorUnableToReadSubImageData 145
#define MGK_CorruptImageErrorUnableToReadVIDImage 146
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 147
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 148
#define MGK_CorruptImageErrorUnableToUncompressImage 149
#define MGK_CorruptImageErrorUnexpectedEndOfFile 150
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 151
#define MGK_CorruptImageErrorUnknownPatternType 152
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 153
#define MGK_CorruptImageErrorUnrecognizedImageCompression 154
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 155
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 156
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 157
#define MGK_CorruptImageFatalErrorUnableToPersistKey 158
#define MGK_CorruptImageWarningCompressionNotValid 159
#define MGK_CorruptImageWarningImproperImageHeader 160
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 161
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 162
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 163
#define MGK_CorruptImageWarningSkipToSyncByte 164
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 165
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 166
#define MGK_CorruptImageWarningUnrecognizedImageCompression 167
#define MGK_DelegateErrorDelegateFailed 168
#define MGK_DelegateErrorFailedToAllocateArgumentList 169
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 170
#define MGK_DelegateErrorFailedToComputeOutputSize 171
#define MGK_DelegateErrorFailedToFindGhostscript 172
#define MGK_DelegateErrorFailedToRenderFile 173
#define MGK_DelegateErrorFailedToScanFile 174
#define MGK_DelegateErrorNoTagFound 175
#define MGK_DelegateErrorPostscriptDelegateFailed 176
#define MGK_DelegateErrorUnableToCreateImage 177
#define MGK_DelegateErrorUnableToCreateImageComponent 178
#define MGK_DelegateErrorUnableToDecodeImageFile 179
#define MGK_DelegateErrorUnableToEncodeImageFile 180
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 181
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 182
#define MGK_DelegateErrorUnableToManageJP2Stream 183
#define MGK_DelegateErrorUnableToWriteSVGFormat 184
#define MGK_DelegateErrorWebPABIMismatch 185
#define MGK_DelegateFatalErrorDefault 186
#define MGK_DelegateWarningDefault 187
#define MGK_DrawErrorAlreadyPushingPatternDefinition 188
#define MGK_DrawErrorFloatValueConversionError 189
#define MGK_DrawErrorIntegerValueConversionError 190
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 191
#define MGK_DrawErrorTooManyCoordinates 192
#define MGK_DrawErrorUnableToPrint 193
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 194
#define MGK_DrawErrorVectorPathTruncated 195
#define MGK_DrawFatalErrorDefault 196
#define MGK_DrawWarningNotARelativeURL 197
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 198
#define MGK_DrawWarningURLNotFound 199
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 200
#define MGK_FileOpenErrorUnableToOpenFile 201
#define MGK_FileOpenErrorUnableToWriteFile 202
#define MGK_FileOpenFatalErrorDefault 203
#define MGK_FileOpenWarningDefault 204
#define MGK_ImageErrorAngleIsDiscontinuous 205
#define MGK_ImageErrorColorspaceColorProfileMismatch 206
#define MGK_ImageErrorImageColorspaceDiffers 207
#define MGK_ImageErrorImageColorspaceMismatch 208
#define MGK_ImageErrorImageDifferenceExceedsLimit 209
#define MGK_ImageErrorImageDoesNotContainResolution 210
#define MGK_ImageErrorImageOpacityDiffers 211
#define MGK_ImageErrorImageSequenceIsRequired 212
#define MGK_ImageErrorImageSizeDiffers 213
#define MGK_ImageErrorInvalidColormapIndex 214
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 215
#define MGK_ImageErrorNoImagesWereFound 216
#define MGK_ImageErrorNoImagesWereLoaded 217
#define MGK_ImageErrorNoLocaleImageAttribute 218
#define MGK_ImageErrorTooManyClusters 219
#define MGK_ImageErrorUnableToAppendImage 220
#define MGK_ImageErrorUnableToAssignProfile 221
#define MGK_ImageErrorUnableToAverageImage 222
#define MGK_ImageErrorUnableToCoalesceImage 223
#define MGK_ImageErrorUnableToCompareImages 224
#define MGK_ImageErrorUnableToCreateImageMosaic 225
#define MGK_ImageErrorUnableToCreateStereoImage 226
#define MGK_ImageErrorUnableToDeconstructImageSequence 227
#define MGK_ImageErrorUnableToFlattenImage 228
#define MGK_ImageErrorUnableToGetClipMask 229
#define MGK_ImageErrorUnableToHandleImageChannel 230
#define MGK_ImageErrorUnableToResizeImage 231
#define MGK_ImageErrorUnableToSegmentImage 232
#define MGK_ImageErrorUnableToSetClipMask 233
#define MGK_ImageErrorUnableToShearImage 234
#define MGK_ImageErrorWidthOrHeightExceedsLimit 235
#define MGK_ImageFatalErrorUnableToPersistKey 236
#define MGK_ImageWarningDefault 237
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 238
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 239
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 240
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 241
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 242
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 243
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 244
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 245
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 246
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 247
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 248
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 249
#define MGK_MissingDelegateFatalErrorDefault 250
#define MGK_MissingDelegateWarningDefault 251
#define MGK_ModuleErrorFailedToCloseModule 252
#define MGK_ModuleErrorFailedToFindSymbol 253
#define MGK_ModuleErrorUnableToLoadModule 254
#define MGK_ModuleErrorUnableToRegisterImageFormat 255
#define MGK_ModuleErrorUnrecognizedModule 256
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 257
#define MGK_ModuleWarningDefault 258
#define MGK_MonitorErrorDefault 259
#define MGK_MonitorFatalErrorDefault 260
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 261
#define MGK_MonitorWarningDefault 262
#define MGK_OptionErrorBevelWidthIsNegative 263
#define MGK_OptionErrorColorSeparatedImageRequired 264
#define MGK_OptionErrorFrameIsLessThanImageSize 265
#define MGK_OptionErrorGeometryDimensionsAreZero 266
#define MGK_OptionErrorGeometryDoesNotContainImage 267
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 268
#define MGK_OptionErrorImagesAreNotTheSameSize 269
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 270
#define MGK_OptionErrorImageSmallerThanKernelWidth 271
#define MGK_OptionErrorImageSmallerThanRadius 272
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 273
#define MGK_OptionErrorInputImagesAlreadySpecified 274
#define MGK_OptionErrorInvalidSubimageSpecification 275
#define MGK_OptionErrorKernelRadiusIsTooSmall 276
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 277
#define MGK_OptionErrorMatrixIsNotSquare 278
#define MGK_OptionErrorMatrixOrderOutOfRange 279
#define MGK_OptionErrorMissingAnImageFilename 280
#define MGK_OptionErrorMissingArgument 281
#define MGK_OptionErrorMustSpecifyAnImageName 282
#define MGK_OptionErrorMustSpecifyImageSize 283
#define MGK_OptionErrorNoBlobDefined 284
#define MGK_OptionErrorNoImagesDefined 285
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 286
#define MGK_OptionErrorNoProfileNameWasGiven 287
#define MGK_OptionErrorNullBlobArgument 288
#define MGK_OptionErrorReferenceImageRequired 289
#define MGK_OptionErrorReferenceIsNotMyType 290
#define MGK_OptionErrorRegionAreaExceedsLimit 291
#define MGK_OptionErrorRequestDidNotReturnAnImage 292
#define MGK_OptionErrorSteganoImageRequired 293
#define MGK_OptionErrorStereoImageRequired 294
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 295
#define MGK_OptionErrorUnableToAddOrRemoveProfile 296
#define MGK_OptionErrorUnableToAverageImageSequence 297
#define MGK_OptionErrorUnableToBlurImage 298
#define MGK_OptionErrorUnableToChopImage 299
#define MGK_OptionErrorUnableToColorMatrixImage 300
#define MGK_OptionErrorUnableToConstituteImage 301
#define MGK_OptionErrorUnableToConvolveImage 302
#define MGK_OptionErrorUnableToEdgeImage 303
#define MGK_OptionErrorUnableToEqualizeImage 304
#define MGK_OptionErrorUnableToFilterImage 305
#define MGK_OptionErrorUnableToFormatImageMetadata 306
#define MGK_OptionErrorUnableToFrameImage 307
#define MGK_OptionErrorUnableToOilPaintImage 308
#define MGK_OptionErrorUnableToPaintImage 309
#define MGK_OptionErrorUnableToRaiseImage 310
#define MGK_OptionErrorUnableToSharpenImage 311
#define MGK_OptionErrorUnableToThresholdImage 312
#define MGK_OptionErrorUnableToWaveImage 313
#define MGK_OptionErrorUnrecognizedAttribute 314
#define MGK_OptionErrorUnrecognizedChannelType 315
#define MGK_OptionErrorUnrecognizedColor 316
#define MGK_OptionErrorUnrecognizedColormapType 317
#define MGK_OptionErrorUnrecognizedColorspace 318
#define MGK_OptionErrorUnrecognizedCommand 319
#define MGK_OptionErrorUnrecognizedComposeOperator 320
#define MGK_OptionErrorUnrecognizedDisposeMethod 321
#define MGK_OptionErrorUnrecognizedElement 322
#define MGK_OptionErrorUnrecognizedEndianType 323
#define MGK_OptionErrorUnrecognizedGravityType 324
#define MGK_OptionErrorUnrecognizedHighlightStyle 325
#define MGK_OptionErrorUnrecognizedImageCompression 326
#define MGK_OptionErrorUnrecognizedImageFilter 327
#define MGK_OptionErrorUnrecognizedImageFormat 328
#define MGK_OptionErrorUnrecognizedImageMode 329
#define MGK_OptionErrorUnrecognizedImageType 330
#define MGK_OptionErrorUnrecognizedIntentType 331
#define MGK_OptionErrorUnrecognizedInterlaceType 332
#define MGK_OptionErrorUnrecognizedListType 333
#define MGK_OptionErrorUnrecognizedMetric 334
#define MGK_OptionErrorUnrecognizedModeType 335
#define MGK_OptionErrorUnrecognizedNoiseType 336
#define MGK_OptionErrorUnrecognizedOperator 337
#define MGK_OptionErrorUnrecognizedOption 338
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 339
#define MGK_OptionErrorUnrecognizedPixelMap 340
#define MGK_OptionErrorUnrecognizedPreviewType 341
#define MGK_OptionErrorUnrecognizedResourceType 342
#define MGK_OptionErrorUnrecognizedType 343
#define MGK_OptionErrorUnrecognizedUnitsType 344
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 345
#define MGK_OptionErrorUnsupportedSamplingFactor 346
#define MGK_OptionErrorUsageError 347
#define MGK_OptionFatalErrorInvalidColorspaceType 348
#define MGK_OptionFatalErrorInvalidEndianType 349
#define MGK_OptionFatalErrorInvalidImageType 350
#define MGK_OptionFatalErrorInvalidInterlaceType 351
#define MGK_OptionFatalErrorMissingAnImageFilename 352
#define MGK_OptionFatalErrorMissingArgument 353
#define MGK_OptionFatalErrorNoImagesWereLoaded 354
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 355
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 356
#define MGK_OptionFatalErrorUnableToOpenXServer 357
#define MGK_OptionFatalErrorUnableToPersistKey 358
#define MGK_OptionFatalErrorUnrecognizedColormapType 359
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 360
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 361
#define MGK_OptionFatalErrorUnrecognizedEndianType 362
#define MGK_OptionFatalErrorUnrecognizedFilterType 363
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 364
#define MGK_OptionFatalErrorUnrecognizedImageType 365
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 366
#define MGK_OptionFatalErrorUnrecognizedOption 367
#define MGK_OptionFatalErrorUnrecognizedResourceType 368
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 369
#define MGK_OptionWarningUnrecognizedColor 370
#define MGK_RegistryErrorImageExpected 371
#define MGK_RegistryErrorImageInfoExpected 372
#define MGK_RegistryErrorStructureSizeMismatch 373
#define MGK_RegistryErrorUnableToGetRegistryID 374
#define MGK_RegistryErrorUnableToLocateImage 375
#define MGK_RegistryErrorUnableToSetRegistry 376
#define MGK_RegistryFatalErrorDefault 377
#define MGK_RegistryWarningDefault 378
#define MGK_ResourceLimitErrorCacheResourcesExhausted 379
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 380
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 381
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 382
#define MGK_ResourceLimitErrorMemoryAllocationFailed 383
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 384
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 385
#define MGK_ResourceLimitErrorUnableToAddColorProfile 386
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 387
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 388
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 389
#define MGK_ResourceLimitErrorUnableToAllocateColormap 390
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 391
#define MGK_ResourceLimitErrorUnableToAllocateString 392
#define MGK_ResourceLimitErrorUnableToAnnotateImage 393
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 394
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 395
#define MGK_ResourceLimitErrorUnableToCloneImage 396
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 397
#define MGK_ResourceLimitErrorUnableToConstituteImage 398
#define MGK_ResourceLimitErrorUnableToConvertFont 399
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 400
#define MGK_ResourceLimitErrorUnableToCreateColormap 401
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 402
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 403
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 404
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 405
#define MGK_ResourceLimitErrorUnableToCreateXWindow 406
#define MGK_ResourceLimitErrorUnableToCropImage 407
#define MGK_ResourceLimitErrorUnableToDespeckleImage 408
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 409
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 410
#define MGK_ResourceLimitErrorUnableToDitherImage 411
#define MGK_ResourceLimitErrorUnableToDrawOnImage 412
#define MGK_ResourceLimitErrorUnableToEdgeImage 413
#define MGK_ResourceLimitErrorUnableToEmbossImage 414
#define MGK_ResourceLimitErrorUnableToEnhanceImage 415
#define MGK_ResourceLimitErrorUnableToFloodfillImage 416
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 417
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 418
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 419
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 420
#define MGK_ResourceLimitErrorUnableToLevelImage 421
#define MGK_ResourceLimitErrorUnableToMagnifyImage 422
#define MGK_ResourceLimitErrorUnableToManageColor 423
#define MGK_ResourceLimitErrorUnableToMapImage 424
#define MGK_ResourceLimitErrorUnableToMapImageSequence 425
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 426
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 427
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 428
#define MGK_ResourceLimitErrorUnableToNormalizeImage 429
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 430
#define MGK_ResourceLimitErrorUnableToQuantizeImage 431
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 432
#define MGK_ResourceLimitErrorUnableToReadTextChunk 433
#define MGK_ResourceLimitErrorUnableToReadXImage 434
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 435
#define MGK_ResourceLimitErrorUnableToResizeImage 436
#define MGK_ResourceLimitErrorUnableToRotateImage 437
#define MGK_ResourceLimitErrorUnableToSampleImage 438
#define MGK_ResourceLimitErrorUnableToScaleImage 439
#define MGK_ResourceLimitErrorUnableToSelectImage 440
#define MGK_ResourceLimitErrorUnableToSharpenImage 441
#define MGK_ResourceLimitErrorUnableToShaveImage 442
#define MGK_ResourceLimitErrorUnableToShearImage 443
#define MGK_ResourceLimitErrorUnableToSortImageColormap 444
#define MGK_ResourceLimitErrorUnableToThresholdImage 445
#define MGK_ResourceLimitErrorUnableToTransformColorspace 446
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 447
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 448
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 449
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 450
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 451
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 452
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 453
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 454
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 455
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 456
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 457
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 458
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 459
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 460
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 461
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 462
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 463
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 464
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 465
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 466
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 467
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 473
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 474
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 475
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 476
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 477
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 478
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 479
#define MGK_ResourceLimitFatalErrorUnableToConvertText 480
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 481
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 482
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 483
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 484
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 485
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 486
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 487
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 488
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 489
#define MGK_ResourceLimitWarningMemoryAllocationFailed 490
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 491
#define MGK_StreamErrorNoStreamHandlerIsDefined 492
#define MGK_StreamErrorPixelCacheIsNotOpen 493
#define MGK_StreamErrorUnableToAcquirePixelStream 494
#define MGK_StreamErrorUnableToSetPixelStream 495
#define MGK_StreamErrorUnableToSyncPixelStream 496
#define MGK_StreamFatalErrorDefault 497
#define MGK_StreamWarningDefault 498
#define MGK_TypeErrorFontSubstitutionRequired 499
#define MGK_TypeErrorUnableToGetTypeMetrics 500
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 501
#define MGK_TypeErrorUnableToReadFont 502
#define MGK_TypeErrorUnrecognizedFontEncoding 503
#define MGK_TypeFatalErrorDefault 504
#define MGK_TypeWarningDefault 505
#define MGK_WandErrorInvalidColormapIndex 506
#define MGK_WandErrorWandAPINotImplemented 507
#define MGK_WandErrorWandContainsNoImageIndexs 508
#define MGK_WandErrorWandContainsNoImages 509
#define MGK_XServerErrorColorIsNotKnownToServer 510
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 511
#define MGK_XServerErrorStandardColormapIsNotInitialized 512
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 513
#define MGK_XServerErrorUnableToCreateBitmap 514
#define MGK_XServerErrorUnableToCreateColormap 515
#define MGK_XServerErrorUnableToCreatePixmap 516
#define MGK_XServerErrorUnableToCreateProperty 517
#define MGK_XServerErrorUnableToCreateStandardColormap 518
#define MGK_XServerErrorUnableToDisplayImageInfo 519
#define MGK_XServerErrorUnableToGetProperty 520
#define MGK_XServerErrorUnableToGetStandardColormap 521
#define MGK_XServerErrorUnableToGetVisual 522
#define MGK_XServerErrorUnableToGrabMouse 523
#define MGK_XServerErrorUnableToLoadFont 524
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 525
#define MGK_XServerErrorUnableToOpenXServer 526
#define MGK_XServerErrorUnableToReadXAttributes 527
#define MGK_XServerErrorUnableToReadXWindowImage 528
#define MGK_XServerErrorUnrecognizedColormapType 529
#define MGK_XServerErrorUnrecognizedGravityType 530
#define MGK_XServerErrorUnrecognizedVisualSpecifier 531
#define MGK_XServerFatalErrorUnableToAllocateXHints 532
#define MGK_XServerFatalErrorUnableToCreateCursor 533
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 534
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 535
#define MGK_XServerFatalErrorUnableToCreateTextProperty 536
#define MGK_XServerFatalErrorUnableToCreateXImage 537
#define MGK_XServerFatalErrorUnableToCreateXPixmap 538
#define MGK_XServerFatalErrorUnableToCreateXWindow 539
#define MGK_XServerFatalErrorUnableToDisplayImage 540
#define MGK_XServerFatalErrorUnableToDitherImage 541
#define MGK_XServerFatalErrorUnableToGetPixelInfo 542
#define MGK_XServerFatalErrorUnableToGetVisual 543
#define MGK_XServerFatalErrorUnableToLoadFont 544
#define MGK_XServerFatalErrorUnableToMakeXWindow 545
#define MGK_XServerFatalErrorUnableToOpenXServer 546
#define MGK_XServerFatalErrorUnableToViewFonts 547
#define MGK_XServerWarningUnableToGetVisual 548
#define MGK_XServerWarningUsingDefaultVisual 549

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
    { "Coder/FatalError", 103, CoderFatalError },
    { "Coder/Warning", 104, CoderWarning },
    { "Configure/Error", 105, ConfigureError },
    { "Configure/FatalError", 112, ConfigureFatalError },
    { "Configure/Warning", 116, ConfigureWarning },
    { "Corrupt/Image/Error", 117, CorruptImageError },
    { "Corrupt/Image/FatalError", 157, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 158, CorruptImageWarning },
    { "Delegate/Error", 167, DelegateError },
    { "Delegate/FatalError", 185, DelegateFatalError },
    { "Delegate/Warning", 186, DelegateWarning },
    { "Draw/Error", 187, DrawError },
    { "Draw/FatalError", 195, DrawFatalError },
    { "Draw/Warning", 196, DrawWarning },
    { "File/Open/Error", 199, FileOpenError },
    { "File/Open/FatalError", 202, FileOpenFatalError },
    { "File/Open/Warning", 203, FileOpenWarning },
    { "Image/Error", 204, ImageError },
    { "Image/FatalError", 235, ImageFatalError },
    { "Image/Warning", 236, ImageWarning },
    { "Missing/Delegate/Error", 237, MissingDelegateError },
    { "Missing/Delegate/FatalError", 249, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 250, MissingDelegateWarning },
    { "Module/Error", 251, ModuleError },
    { "Module/FatalError", 256, ModuleFatalError },
    { "Module/Warning", 257, ModuleWarning },
    { "Monitor/Error", 258, MonitorError },
    { "Monitor/FatalError", 259, MonitorFatalError },
    { "Monitor/Warning", 261, MonitorWarning },
    { "Option/Error", 262, OptionError },
    { "Option/FatalError", 347, OptionFatalError },
    { "Option/Warning", 369, OptionWarning },
    { "Registry/Error", 370, RegistryError },
    { "Registry/FatalError", 376, RegistryFatalError },
    { "Registry/Warning", 377, RegistryWarning },
    { "Resource/Limit/Error", 378, ResourceLimitError },
    { "Resource/Limit/FatalError", 446, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 489, ResourceLimitWarning },
    { "Stream/Error", 490, StreamError },
    { "Stream/FatalError", 496, StreamFatalError },
    { "Stream/Warning", 497, StreamWarning },
    { "Type/Error", 498, TypeError },
    { "Type/FatalError", 503, TypeFatalError },
    { "Type/Warning", 504, TypeWarning },
    { "Wand/Error", 505, WandError },
    { "XServer/Error", 509, XServerError },
    { "XServer/FatalError", 531, XServerFatalError },
    { "XServer/Warning", 547, XServerWarning },
    { 0, 549, UndefinedException }
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
    { "UnsupportedBitsPerSample", 87 },
    { "UnsupportedCellTypeInTheMatrix", 88 },
    { "WebPDecodingFailedUserAbort", 89 },
    { "WebPEncodingFailed", 90 },
    { "WebPEncodingFailedBadDimension", 91 },
    { "WebPEncodingFailedBadWrite", 92 },
    { "WebPEncodingFailedBitstreamOutOfMemory", 93 },
    { "WebPEncodingFailedFileTooBig", 94 },
    { "WebPEncodingFailedInvalidConfiguration", 95 },
    { "WebPEncodingFailedNULLParameter", 96 },
    { "WebPEncodingFailedOutOfMemory", 97 },
    { "WebPEncodingFailedPartition0Overflow", 98 },
    { "WebPEncodingFailedPartitionOverflow", 99 },
    { "WebPEncodingFailedUserAbort", 100 },
    { "WebPInvalidConfiguration", 101 },
    { "WebPInvalidParameter", 102 },
    { "ZipCompressionNotSupported", 103 },
    { "Default", 104 },
    { "LosslessToLossyJPEGConversion", 105 },
    { "IncludeElementNestedTooDeeply", 106 },
    { "RegistryKeyLookupFailed", 107 },
    { "StringTokenLengthExceeded", 108 },
    { "UnableToAccessConfigureFile", 109 },
    { "UnableToAccessFontFile", 110 },
    { "UnableToAccessLogFile", 111 },
    { "UnableToAccessModuleFile", 112 },
    { "Default", 113 },
    { "UnableToChangeToWorkingDirectory", 114 },
    { "UnableToGetCurrentDirectory", 115 },
    { "UnableToRestoreCurrentDirectory", 116 },
    { "Default", 117 },
    { "AnErrorHasOccurredReadingFromFile", 118 },
    { "AnErrorHasOccurredWritingToFile", 119 },
    { "ColormapExceedsColorsLimit", 120 },
    { "CompressionNotValid", 121 },
    { "CorruptImage", 122 },
    { "ImageFileDoesNotContainAnyImageData", 123 },
    { "ImageTypeNotSupported", 124 },
    { "ImproperImageHeader", 125 },
    { "InsufficientImageDataInFile", 126 },
    { "InvalidColormapIndex", 127 },
    { "InvalidFileFormatVersion", 128 },
    { "LengthAndFilesizeDoNotMatch", 129 },
    { "MissingImageChannel", 130 },
    { "NegativeOrZeroImageSize", 131 },
    { "NonOS2HeaderSizeError", 132 },
    { "NotEnoughTiles", 133 },
    { "StaticPlanesValueNotEqualToOne", 134 },
    { "SubsamplingRequiresEvenWidth", 135 },
    { "TooMuchImageDataInFile", 136 },
    { "UnableToReadColormapFromDumpFile", 137 },
    { "UnableToReadColorProfile", 138 },
    { "UnableToReadExtensionBlock", 139 },
    { "UnableToReadGenericProfile", 140 },
    { "UnableToReadImageData", 141 },
    { "UnableToReadImageHeader", 142 },
    { "UnableToReadIPTCProfile", 143 },
    { "UnableToReadPixmapFromDumpFile", 144 },
    { "UnableToReadSubImageData", 145 },
    { "UnableToReadVIDImage", 146 },
    { "UnableToReadWindowNameFromDumpFile", 147 },
    { "UnableToRunlengthDecodeImage", 148 },
    { "UnableToUncompressImage", 149 },
    { "UnexpectedEndOfFile", 150 },
    { "UnexpectedSamplingFactor", 151 },
    { "UnknownPatternType", 152 },
    { "UnrecognizedBitsPerPixel", 153 },
    { "UnrecognizedImageCompression", 154 },
    { "UnrecognizedNumberOfColors", 155 },
    { "UnrecognizedXWDHeader", 156 },
    { "UnsupportedBitsPerSample", 157 },
    { "UnableToPersistKey", 158 },
    { "CompressionNotValid", 159 },
    { "ImproperImageHeader", 160 },
    { "LengthAndFilesizeDoNotMatch", 161 },
    { "NegativeOrZeroImageSize", 162 },
    { "NonOS2HeaderSizeError", 163 },
    { "SkipToSyncByte", 164 },
    { "StaticPlanesValueNotEqualToOne", 165 },
    { "UnrecognizedBitsPerPixel", 166 },
    { "UnrecognizedImageCompression", 167 },
    { "DelegateFailed", 168 },
    { "FailedToAllocateArgumentList", 169 },
    { "FailedToAllocateGhostscriptInterpreter", 170 },
    { "FailedToComputeOutputSize", 171 },
    { "FailedToFindGhostscript", 172 },
    { "FailedToRenderFile", 173 },
    { "FailedToScanFile", 174 },
    { "NoTagFound", 175 },
    { "PostscriptDelegateFailed", 176 },
    { "UnableToCreateImage", 177 },
    { "UnableToCreateImageComponent", 178 },
    { "UnableToDecodeImageFile", 179 },
    { "UnableToEncodeImageFile", 180 },
    { "UnableToInitializeFPXLibrary", 181 },
    { "UnableToInitializeWMFLibrary", 182 },
    { "UnableToManageJP2Stream", 183 },
    { "UnableToWriteSVGFormat", 184 },
    { "WebPABIMismatch", 185 },
    { "Default", 186 },
    { "Default", 187 },
    { "AlreadyPushingPatternDefinition", 188 },
    { "FloatValueConversionError", 189 },
    { "IntegerValueConversionError", 190 },
    { "NonconformingDrawingPrimitiveDefinition", 191 },
    { "TooManyCoordinates", 192 },
    { "UnableToPrint", 193 },
    { "UnbalancedGraphicContextPushPop", 194 },
    { "VectorPathTruncated", 195 },
    { "Default", 196 },
    { "NotARelativeURL", 197 },
    { "NotCurrentlyPushingPatternDefinition", 198 },
    { "URLNotFound", 199 },
    { "UnableToCreateTemporaryFile", 200 },
    { "UnableToOpenFile", 201 },
    { "UnableToWriteFile", 202 },
    { "Default", 203 },
    { "Default", 204 },
    { "AngleIsDiscontinuous", 205 },
    { "ColorspaceColorProfileMismatch", 206 },
    { "ImageColorspaceDiffers", 207 },
    { "ImageColorspaceMismatch", 208 },
    { "ImageDifferenceExceedsLimit", 209 },
    { "ImageDoesNotContainResolution", 210 },
    { "ImageOpacityDiffers", 211 },
    { "ImageSequenceIsRequired", 212 },
    { "ImageSizeDiffers", 213 },
    { "InvalidColormapIndex", 214 },
    { "LeftAndRightImageSizesDiffer", 215 },
    { "NoImagesWereFound", 216 },
    { "NoImagesWereLoaded", 217 },
    { "NoLocaleImageAttribute", 218 },
    { "TooManyClusters", 219 },
    { "UnableToAppendImage", 220 },
    { "UnableToAssignProfile", 221 },
    { "UnableToAverageImage", 222 },
    { "UnableToCoalesceImage", 223 },
    { "UnableToCompareImages", 224 },
    { "UnableToCreateImageMosaic", 225 },
    { "UnableToCreateStereoImage", 226 },
    { "UnableToDeconstructImageSequence", 227 },
    { "UnableToFlattenImage", 228 },
    { "UnableToGetClipMask", 229 },
    { "UnableToHandleImageChannel", 230 },
    { "UnableToResizeImage", 231 },
    { "UnableToSegmentImage", 232 },
    { "UnableToSetClipMask", 233 },
    { "UnableToShearImage", 234 },
    { "WidthOrHeightExceedsLimit", 235 },
    { "UnableToPersistKey", 236 },
    { "Default", 237 },
    { "DPSLibraryIsNotAvailable", 238 },
    { "FPXLibraryIsNotAvailable", 239 },
    { "FreeTypeLibraryIsNotAvailable", 240 },
    { "JPEGLibraryIsNotAvailable", 241 },
    { "LCMSLibraryIsNotAvailable", 242 },
    { "LZWEncodingNotEnabled", 243 },
    { "NoDecodeDelegateForThisImageFormat", 244 },
    { "NoEncodeDelegateForThisImageFormat", 245 },
    { "TIFFLibraryIsNotAvailable", 246 },
    { "XMLLibraryIsNotAvailable", 247 },
    { "XWindowLibraryIsNotAvailable", 248 },
    { "ZipLibraryIsNotAvailable", 249 },
    { "Default", 250 },
    { "Default", 251 },
    { "FailedToCloseModule", 252 },
    { "FailedToFindSymbol", 253 },
    { "UnableToLoadModule", 254 },
    { "UnableToRegisterImageFormat", 255 },
    { "UnrecognizedModule", 256 },
    { "UnableToInitializeModuleLoader", 257 },
    { "Default", 258 },
    { "Default", 259 },
    { "Default", 260 },
    { "UserRequestedTerminationBySignal", 261 },
    { "Default", 262 },
    { "BevelWidthIsNegative", 263 },
    { "ColorSeparatedImageRequired", 264 },
    { "FrameIsLessThanImageSize", 265 },
    { "GeometryDimensionsAreZero", 266 },
    { "GeometryDoesNotContainImage", 267 },
    { "HaldClutImageDimensionsInvalid", 268 },
    { "ImagesAreNotTheSameSize", 269 },
    { "ImageSizeMustExceedBevelWidth", 270 },
    { "ImageSmallerThanKernelWidth", 271 },
    { "ImageSmallerThanRadius", 272 },
    { "ImageWidthsOrHeightsDiffer", 273 },
    { "InputImagesAlreadySpecified", 274 },
    { "InvalidSubimageSpecification", 275 },
    { "KernelRadiusIsTooSmall", 276 },
    { "KernelWidthMustBeAnOddNumber", 277 },
    { "MatrixIsNotSquare", 278 },
    { "MatrixOrderOutOfRange", 279 },
    { "MissingAnImageFilename", 280 },
    { "MissingArgument", 281 },
    { "MustSpecifyAnImageName", 282 },
    { "MustSpecifyImageSize", 283 },
    { "NoBlobDefined", 284 },
    { "NoImagesDefined", 285 },
    { "NonzeroWidthAndHeightRequired", 286 },
    { "NoProfileNameWasGiven", 287 },
    { "NullBlobArgument", 288 },
    { "ReferenceImageRequired", 289 },
    { "ReferenceIsNotMyType", 290 },
    { "RegionAreaExceedsLimit", 291 },
    { "RequestDidNotReturnAnImage", 292 },
    { "SteganoImageRequired", 293 },
    { "StereoImageRequired", 294 },
    { "SubimageSpecificationReturnsNoImages", 295 },
    { "UnableToAddOrRemoveProfile", 296 },
    { "UnableToAverageImageSequence", 297 },
    { "UnableToBlurImage", 298 },
    { "UnableToChopImage", 299 },
    { "UnableToColorMatrixImage", 300 },
    { "UnableToConstituteImage", 301 },
    { "UnableToConvolveImage", 302 },
    { "UnableToEdgeImage", 303 },
    { "UnableToEqualizeImage", 304 },
    { "UnableToFilterImage", 305 },
    { "UnableToFormatImageMetadata", 306 },
    { "UnableToFrameImage", 307 },
    { "UnableToOilPaintImage", 308 },
    { "UnableToPaintImage", 309 },
    { "UnableToRaiseImage", 310 },
    { "UnableToSharpenImage", 311 },
    { "UnableToThresholdImage", 312 },
    { "UnableToWaveImage", 313 },
    { "UnrecognizedAttribute", 314 },
    { "UnrecognizedChannelType", 315 },
    { "UnrecognizedColor", 316 },
    { "UnrecognizedColormapType", 317 },
    { "UnrecognizedColorspace", 318 },
    { "UnrecognizedCommand", 319 },
    { "UnrecognizedComposeOperator", 320 },
    { "UnrecognizedDisposeMethod", 321 },
    { "UnrecognizedElement", 322 },
    { "UnrecognizedEndianType", 323 },
    { "UnrecognizedGravityType", 324 },
    { "UnrecognizedHighlightStyle", 325 },
    { "UnrecognizedImageCompression", 326 },
    { "UnrecognizedImageFilter", 327 },
    { "UnrecognizedImageFormat", 328 },
    { "UnrecognizedImageMode", 329 },
    { "UnrecognizedImageType", 330 },
    { "UnrecognizedIntentType", 331 },
    { "UnrecognizedInterlaceType", 332 },
    { "UnrecognizedListType", 333 },
    { "UnrecognizedMetric", 334 },
    { "UnrecognizedModeType", 335 },
    { "UnrecognizedNoiseType", 336 },
    { "UnrecognizedOperator", 337 },
    { "UnrecognizedOption", 338 },
    { "UnrecognizedPerlMagickMethod", 339 },
    { "UnrecognizedPixelMap", 340 },
    { "UnrecognizedPreviewType", 341 },
    { "UnrecognizedResourceType", 342 },
    { "UnrecognizedType", 343 },
    { "UnrecognizedUnitsType", 344 },
    { "UnrecognizedVirtualPixelMethod", 345 },
    { "UnsupportedSamplingFactor", 346 },
    { "UsageError", 347 },
    { "InvalidColorspaceType", 348 },
    { "InvalidEndianType", 349 },
    { "InvalidImageType", 350 },
    { "InvalidInterlaceType", 351 },
    { "MissingAnImageFilename", 352 },
    { "MissingArgument", 353 },
    { "NoImagesWereLoaded", 354 },
    { "OptionLengthExceedsLimit", 355 },
    { "RequestDidNotReturnAnImage", 356 },
    { "UnableToOpenXServer", 357 },
    { "UnableToPersistKey", 358 },
    { "UnrecognizedColormapType", 359 },
    { "UnrecognizedColorspaceType", 360 },
    { "UnrecognizedDisposeMethod", 361 },
    { "UnrecognizedEndianType", 362 },
    { "UnrecognizedFilterType", 363 },
    { "UnrecognizedImageCompressionType", 364 },
    { "UnrecognizedImageType", 365 },
    { "UnrecognizedInterlaceType", 366 },
    { "UnrecognizedOption", 367 },
    { "UnrecognizedResourceType", 368 },
    { "UnrecognizedVirtualPixelMethod", 369 },
    { "UnrecognizedColor", 370 },
    { "ImageExpected", 371 },
    { "ImageInfoExpected", 372 },
    { "StructureSizeMismatch", 373 },
    { "UnableToGetRegistryID", 374 },
    { "UnableToLocateImage", 375 },
    { "UnableToSetRegistry", 376 },
    { "Default", 377 },
    { "Default", 378 },
    { "CacheResourcesExhausted", 379 },
    { "ImagePixelHeightLimitExceeded", 380 },
    { "ImagePixelLimitExceeded", 381 },
    { "ImagePixelWidthLimitExceeded", 382 },
    { "MemoryAllocationFailed", 383 },
    { "NoPixelsDefinedInCache", 384 },
    { "PixelCacheAllocationFailed", 385 },
    { "UnableToAddColorProfile", 386 },
    { "UnableToAddGenericProfile", 387 },
    { "UnableToAddIPTCProfile", 388 },
    { "UnableToAllocateCoefficients", 389 },
    { "UnableToAllocateColormap", 390 },
    { "UnableToAllocateICCProfile", 391 },
    { "UnableToAllocateString", 392 },
    { "UnableToAnnotateImage", 393 },
    { "UnableToAverageImageSequence", 394 },
    { "UnableToCloneDrawingWand", 395 },
    { "UnableToCloneImage", 396 },
    { "UnableToComputeImageSignature", 397 },
    { "UnableToConstituteImage", 398 },
    { "UnableToConvertFont", 399 },
    { "UnableToConvertStringToTokens", 400 },
    { "UnableToCreateColormap", 401 },
    { "UnableToCreateColorTransform", 402 },
    { "UnableToCreateCommandWidget", 403 },
    { "UnableToCreateImageGroup", 404 },
    { "UnableToCreateImageMontage", 405 },
    { "UnableToCreateXWindow", 406 },
    { "UnableToCropImage", 407 },
    { "UnableToDespeckleImage", 408 },
    { "UnableToDetermineImageClass", 409 },
    { "UnableToDetermineTheNumberOfImageColors", 410 },
    { "UnableToDitherImage", 411 },
    { "UnableToDrawOnImage", 412 },
    { "UnableToEdgeImage", 413 },
    { "UnableToEmbossImage", 414 },
    { "UnableToEnhanceImage", 415 },
    { "UnableToFloodfillImage", 416 },
    { "UnableToGammaCorrectImage", 417 },
    { "UnableToGetBestIconSize", 418 },
    { "UnableToGetFromRegistry", 419 },
    { "UnableToGetPackageInfo", 420 },
    { "UnableToLevelImage", 421 },
    { "UnableToMagnifyImage", 422 },
    { "UnableToManageColor", 423 },
    { "UnableToMapImage", 424 },
    { "UnableToMapImageSequence", 425 },
    { "UnableToMedianFilterImage", 426 },
    { "UnableToMotionBlurImage", 427 },
    { "UnableToNoiseFilterImage", 428 },
    { "UnableToNormalizeImage", 429 },
    { "UnableToOpenColorProfile", 430 },
    { "UnableToQuantizeImage", 431 },
    { "UnableToQuantizeImageSequence", 432 },
    { "UnableToReadTextChunk", 433 },
    { "UnableToReadXImage", 434 },
    { "UnableToReadXServerColormap", 435 },
    { "UnableToResizeImage", 436 },
    { "UnableToRotateImage", 437 },
    { "UnableToSampleImage", 438 },
    { "UnableToScaleImage", 439 },
    { "UnableToSelectImage", 440 },
    { "UnableToSharpenImage", 441 },
    { "UnableToShaveImage", 442 },
    { "UnableToShearImage", 443 },
    { "UnableToSortImageColormap", 444 },
    { "UnableToThresholdImage", 445 },
    { "UnableToTransformColorspace", 446 },
    { "MemoryAllocationFailed", 447 },
    { "SemaporeOperationFailed", 448 },
    { "UnableToAllocateAscii85Info", 449 },
    { "UnableToAllocateCacheInfo", 450 },
    { "UnableToAllocateCacheView", 451 },
    { "UnableToAllocateColorInfo", 452 },
    { "UnableToAllocateDashPattern", 453 },
    { "UnableToAllocateDelegateInfo", 454 },
    { "UnableToAllocateDerivatives", 455 },
    { "UnableToAllocateDrawContext", 456 },
    { "UnableToAllocateDrawInfo", 457 },
    { "UnableToAllocateDrawingWand", 458 },
    { "UnableToAllocateGammaMap", 459 },
    { "UnableToAllocateImage", 460 },
    { "UnableToAllocateImagePixels", 461 },
    { "UnableToAllocateLogInfo", 462 },
    { "UnableToAllocateMagicInfo", 463 },
    { "UnableToAllocateMagickInfo", 464 },
    { "UnableToAllocateModuleInfo", 465 },
    { "UnableToAllocateMontageInfo", 466 },
    { "UnableToAllocateQuantizeInfo", 467 },
    { "UnableToAllocateRandomKernel", 468 },
    { "UnableToAllocateRegistryInfo", 469 },
    { "UnableToAllocateSemaphoreInfo", 470 },
    { "UnableToAllocateString", 471 },
    { "UnableToAllocateTypeInfo", 472 },
    { "UnableToAllocateWand", 473 },
    { "UnableToAnimateImageSequence", 474 },
    { "UnableToCloneBlobInfo", 475 },
    { "UnableToCloneCacheInfo", 476 },
    { "UnableToCloneImage", 477 },
    { "UnableToCloneImageInfo", 478 },
    { "UnableToConcatenateString", 479 },
    { "UnableToConvertText", 480 },
    { "UnableToCreateColormap", 481 },
    { "UnableToDestroySemaphore", 482 },
    { "UnableToDisplayImage", 483 },
    { "UnableToEscapeString", 484 },
    { "UnableToInitializeSemaphore", 485 },
    { "UnableToInterpretMSLImage", 486 },
    { "UnableToLockSemaphore", 487 },
    { "UnableToObtainRandomEntropy", 488 },
    { "UnableToUnlockSemaphore", 489 },
    { "MemoryAllocationFailed", 490 },
    { "ImageDoesNotContainTheStreamGeometry", 491 },
    { "NoStreamHandlerIsDefined", 492 },
    { "PixelCacheIsNotOpen", 493 },
    { "UnableToAcquirePixelStream", 494 },
    { "UnableToSetPixelStream", 495 },
    { "UnableToSyncPixelStream", 496 },
    { "Default", 497 },
    { "Default", 498 },
    { "FontSubstitutionRequired", 499 },
    { "UnableToGetTypeMetrics", 500 },
    { "UnableToInitializeFreetypeLibrary", 501 },
    { "UnableToReadFont", 502 },
    { "UnrecognizedFontEncoding", 503 },
    { "Default", 504 },
    { "Default", 505 },
    { "InvalidColormapIndex", 506 },
    { "WandAPINotImplemented", 507 },
    { "WandContainsNoImageIndexs", 508 },
    { "WandContainsNoImages", 509 },
    { "ColorIsNotKnownToServer", 510 },
    { "NoWindowWithSpecifiedIDExists", 511 },
    { "StandardColormapIsNotInitialized", 512 },
    { "UnableToConnectToRemoteDisplay", 513 },
    { "UnableToCreateBitmap", 514 },
    { "UnableToCreateColormap", 515 },
    { "UnableToCreatePixmap", 516 },
    { "UnableToCreateProperty", 517 },
    { "UnableToCreateStandardColormap", 518 },
    { "UnableToDisplayImageInfo", 519 },
    { "UnableToGetProperty", 520 },
    { "UnableToGetStandardColormap", 521 },
    { "UnableToGetVisual", 522 },
    { "UnableToGrabMouse", 523 },
    { "UnableToLoadFont", 524 },
    { "UnableToMatchVisualToStandardColormap", 525 },
    { "UnableToOpenXServer", 526 },
    { "UnableToReadXAttributes", 527 },
    { "UnableToReadXWindowImage", 528 },
    { "UnrecognizedColormapType", 529 },
    { "UnrecognizedGravityType", 530 },
    { "UnrecognizedVisualSpecifier", 531 },
    { "UnableToAllocateXHints", 532 },
    { "UnableToCreateCursor", 533 },
    { "UnableToCreateGraphicContext", 534 },
    { "UnableToCreateStandardColormap", 535 },
    { "UnableToCreateTextProperty", 536 },
    { "UnableToCreateXImage", 537 },
    { "UnableToCreateXPixmap", 538 },
    { "UnableToCreateXWindow", 539 },
    { "UnableToDisplayImage", 540 },
    { "UnableToDitherImage", 541 },
    { "UnableToGetPixelInfo", 542 },
    { "UnableToGetVisual", 543 },
    { "UnableToLoadFont", 544 },
    { "UnableToMakeXWindow", 545 },
    { "UnableToOpenXServer", 546 },
    { "UnableToViewFonts", 547 },
    { "UnableToGetVisual", 548 },
    { "UsingDefaultVisual", 549 },
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
    "Unsupported bits per sample",
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
    "Unsupported bits per sample",
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

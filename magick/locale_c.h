#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 553

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
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 158
#define MGK_CorruptImageFatalErrorUnableToPersistKey 159
#define MGK_CorruptImageWarningCompressionNotValid 160
#define MGK_CorruptImageWarningImproperImageHeader 161
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 162
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 163
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 164
#define MGK_CorruptImageWarningSkipToSyncByte 165
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 166
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 167
#define MGK_CorruptImageWarningUnrecognizedImageCompression 168
#define MGK_DelegateErrorDelegateFailed 169
#define MGK_DelegateErrorFailedToAllocateArgumentList 170
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 171
#define MGK_DelegateErrorFailedToComputeOutputSize 172
#define MGK_DelegateErrorFailedToFindGhostscript 173
#define MGK_DelegateErrorFailedToRenderFile 174
#define MGK_DelegateErrorFailedToScanFile 175
#define MGK_DelegateErrorNoTagFound 176
#define MGK_DelegateErrorPostscriptDelegateFailed 177
#define MGK_DelegateErrorUnableToCreateImage 178
#define MGK_DelegateErrorUnableToCreateImageComponent 179
#define MGK_DelegateErrorUnableToDecodeImageFile 180
#define MGK_DelegateErrorUnableToEncodeImageFile 181
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 182
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 183
#define MGK_DelegateErrorUnableToManageJP2Stream 184
#define MGK_DelegateErrorUnableToWriteSVGFormat 185
#define MGK_DelegateErrorWebPABIMismatch 186
#define MGK_DelegateFatalErrorDefault 187
#define MGK_DelegateWarningDefault 188
#define MGK_DrawErrorAlreadyPushingPatternDefinition 189
#define MGK_DrawErrorDrawingRecursionDetected 190
#define MGK_DrawErrorFloatValueConversionError 191
#define MGK_DrawErrorIntegerValueConversionError 192
#define MGK_DrawErrorInvalidPrimitiveArgument 193
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 194
#define MGK_DrawErrorPrimitiveArithmeticOverflow 195
#define MGK_DrawErrorTooManyCoordinates 196
#define MGK_DrawErrorUnableToPrint 197
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 198
#define MGK_DrawErrorVectorPathTruncated 199
#define MGK_DrawFatalErrorDefault 200
#define MGK_DrawWarningNotARelativeURL 201
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 202
#define MGK_DrawWarningURLNotFound 203
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 204
#define MGK_FileOpenErrorUnableToOpenFile 205
#define MGK_FileOpenErrorUnableToWriteFile 206
#define MGK_FileOpenFatalErrorDefault 207
#define MGK_FileOpenWarningDefault 208
#define MGK_ImageErrorAngleIsDiscontinuous 209
#define MGK_ImageErrorColorspaceColorProfileMismatch 210
#define MGK_ImageErrorImageColorspaceDiffers 211
#define MGK_ImageErrorImageColorspaceMismatch 212
#define MGK_ImageErrorImageDifferenceExceedsLimit 213
#define MGK_ImageErrorImageDoesNotContainResolution 214
#define MGK_ImageErrorImageOpacityDiffers 215
#define MGK_ImageErrorImageSequenceIsRequired 216
#define MGK_ImageErrorImageSizeDiffers 217
#define MGK_ImageErrorInvalidColormapIndex 218
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 219
#define MGK_ImageErrorNoImagesWereFound 220
#define MGK_ImageErrorNoImagesWereLoaded 221
#define MGK_ImageErrorNoLocaleImageAttribute 222
#define MGK_ImageErrorTooManyClusters 223
#define MGK_ImageErrorUnableToAppendImage 224
#define MGK_ImageErrorUnableToAssignProfile 225
#define MGK_ImageErrorUnableToAverageImage 226
#define MGK_ImageErrorUnableToCoalesceImage 227
#define MGK_ImageErrorUnableToCompareImages 228
#define MGK_ImageErrorUnableToCreateImageMosaic 229
#define MGK_ImageErrorUnableToCreateStereoImage 230
#define MGK_ImageErrorUnableToDeconstructImageSequence 231
#define MGK_ImageErrorUnableToFlattenImage 232
#define MGK_ImageErrorUnableToGetClipMask 233
#define MGK_ImageErrorUnableToHandleImageChannel 234
#define MGK_ImageErrorUnableToResizeImage 235
#define MGK_ImageErrorUnableToSegmentImage 236
#define MGK_ImageErrorUnableToSetClipMask 237
#define MGK_ImageErrorUnableToShearImage 238
#define MGK_ImageErrorWidthOrHeightExceedsLimit 239
#define MGK_ImageFatalErrorUnableToPersistKey 240
#define MGK_ImageWarningDefault 241
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 242
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 243
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 244
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 245
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 246
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 247
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 248
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 249
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 250
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 251
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 252
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 253
#define MGK_MissingDelegateFatalErrorDefault 254
#define MGK_MissingDelegateWarningDefault 255
#define MGK_ModuleErrorFailedToCloseModule 256
#define MGK_ModuleErrorFailedToFindSymbol 257
#define MGK_ModuleErrorUnableToLoadModule 258
#define MGK_ModuleErrorUnableToRegisterImageFormat 259
#define MGK_ModuleErrorUnrecognizedModule 260
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 261
#define MGK_ModuleWarningDefault 262
#define MGK_MonitorErrorDefault 263
#define MGK_MonitorFatalErrorDefault 264
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 265
#define MGK_MonitorWarningDefault 266
#define MGK_OptionErrorBevelWidthIsNegative 267
#define MGK_OptionErrorColorSeparatedImageRequired 268
#define MGK_OptionErrorFrameIsLessThanImageSize 269
#define MGK_OptionErrorGeometryDimensionsAreZero 270
#define MGK_OptionErrorGeometryDoesNotContainImage 271
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 272
#define MGK_OptionErrorImagesAreNotTheSameSize 273
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 274
#define MGK_OptionErrorImageSmallerThanKernelWidth 275
#define MGK_OptionErrorImageSmallerThanRadius 276
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 277
#define MGK_OptionErrorInputImagesAlreadySpecified 278
#define MGK_OptionErrorInvalidSubimageSpecification 279
#define MGK_OptionErrorKernelRadiusIsTooSmall 280
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 281
#define MGK_OptionErrorMatrixIsNotSquare 282
#define MGK_OptionErrorMatrixOrderOutOfRange 283
#define MGK_OptionErrorMissingAnImageFilename 284
#define MGK_OptionErrorMissingArgument 285
#define MGK_OptionErrorMustSpecifyAnImageName 286
#define MGK_OptionErrorMustSpecifyImageSize 287
#define MGK_OptionErrorNoBlobDefined 288
#define MGK_OptionErrorNoImagesDefined 289
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 290
#define MGK_OptionErrorNoProfileNameWasGiven 291
#define MGK_OptionErrorNullBlobArgument 292
#define MGK_OptionErrorReferenceImageRequired 293
#define MGK_OptionErrorReferenceIsNotMyType 294
#define MGK_OptionErrorRegionAreaExceedsLimit 295
#define MGK_OptionErrorRequestDidNotReturnAnImage 296
#define MGK_OptionErrorSteganoImageRequired 297
#define MGK_OptionErrorStereoImageRequired 298
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 299
#define MGK_OptionErrorUnableToAddOrRemoveProfile 300
#define MGK_OptionErrorUnableToAverageImageSequence 301
#define MGK_OptionErrorUnableToBlurImage 302
#define MGK_OptionErrorUnableToChopImage 303
#define MGK_OptionErrorUnableToColorMatrixImage 304
#define MGK_OptionErrorUnableToConstituteImage 305
#define MGK_OptionErrorUnableToConvolveImage 306
#define MGK_OptionErrorUnableToEdgeImage 307
#define MGK_OptionErrorUnableToEqualizeImage 308
#define MGK_OptionErrorUnableToFilterImage 309
#define MGK_OptionErrorUnableToFormatImageMetadata 310
#define MGK_OptionErrorUnableToFrameImage 311
#define MGK_OptionErrorUnableToOilPaintImage 312
#define MGK_OptionErrorUnableToPaintImage 313
#define MGK_OptionErrorUnableToRaiseImage 314
#define MGK_OptionErrorUnableToSharpenImage 315
#define MGK_OptionErrorUnableToThresholdImage 316
#define MGK_OptionErrorUnableToWaveImage 317
#define MGK_OptionErrorUnrecognizedAttribute 318
#define MGK_OptionErrorUnrecognizedChannelType 319
#define MGK_OptionErrorUnrecognizedColor 320
#define MGK_OptionErrorUnrecognizedColormapType 321
#define MGK_OptionErrorUnrecognizedColorspace 322
#define MGK_OptionErrorUnrecognizedCommand 323
#define MGK_OptionErrorUnrecognizedComposeOperator 324
#define MGK_OptionErrorUnrecognizedDisposeMethod 325
#define MGK_OptionErrorUnrecognizedElement 326
#define MGK_OptionErrorUnrecognizedEndianType 327
#define MGK_OptionErrorUnrecognizedGravityType 328
#define MGK_OptionErrorUnrecognizedHighlightStyle 329
#define MGK_OptionErrorUnrecognizedImageCompression 330
#define MGK_OptionErrorUnrecognizedImageFilter 331
#define MGK_OptionErrorUnrecognizedImageFormat 332
#define MGK_OptionErrorUnrecognizedImageMode 333
#define MGK_OptionErrorUnrecognizedImageType 334
#define MGK_OptionErrorUnrecognizedIntentType 335
#define MGK_OptionErrorUnrecognizedInterlaceType 336
#define MGK_OptionErrorUnrecognizedListType 337
#define MGK_OptionErrorUnrecognizedMetric 338
#define MGK_OptionErrorUnrecognizedModeType 339
#define MGK_OptionErrorUnrecognizedNoiseType 340
#define MGK_OptionErrorUnrecognizedOperator 341
#define MGK_OptionErrorUnrecognizedOption 342
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 343
#define MGK_OptionErrorUnrecognizedPixelMap 344
#define MGK_OptionErrorUnrecognizedPreviewType 345
#define MGK_OptionErrorUnrecognizedResourceType 346
#define MGK_OptionErrorUnrecognizedType 347
#define MGK_OptionErrorUnrecognizedUnitsType 348
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 349
#define MGK_OptionErrorUnsupportedSamplingFactor 350
#define MGK_OptionErrorUsageError 351
#define MGK_OptionFatalErrorInvalidColorspaceType 352
#define MGK_OptionFatalErrorInvalidEndianType 353
#define MGK_OptionFatalErrorInvalidImageType 354
#define MGK_OptionFatalErrorInvalidInterlaceType 355
#define MGK_OptionFatalErrorMissingAnImageFilename 356
#define MGK_OptionFatalErrorMissingArgument 357
#define MGK_OptionFatalErrorNoImagesWereLoaded 358
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 359
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 360
#define MGK_OptionFatalErrorUnableToOpenXServer 361
#define MGK_OptionFatalErrorUnableToPersistKey 362
#define MGK_OptionFatalErrorUnrecognizedColormapType 363
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 364
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 365
#define MGK_OptionFatalErrorUnrecognizedEndianType 366
#define MGK_OptionFatalErrorUnrecognizedFilterType 367
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 368
#define MGK_OptionFatalErrorUnrecognizedImageType 369
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 370
#define MGK_OptionFatalErrorUnrecognizedOption 371
#define MGK_OptionFatalErrorUnrecognizedResourceType 372
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 373
#define MGK_OptionWarningUnrecognizedColor 374
#define MGK_RegistryErrorImageExpected 375
#define MGK_RegistryErrorImageInfoExpected 376
#define MGK_RegistryErrorStructureSizeMismatch 377
#define MGK_RegistryErrorUnableToGetRegistryID 378
#define MGK_RegistryErrorUnableToLocateImage 379
#define MGK_RegistryErrorUnableToSetRegistry 380
#define MGK_RegistryFatalErrorDefault 381
#define MGK_RegistryWarningDefault 382
#define MGK_ResourceLimitErrorCacheResourcesExhausted 383
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 384
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 385
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 386
#define MGK_ResourceLimitErrorMemoryAllocationFailed 387
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 388
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 389
#define MGK_ResourceLimitErrorUnableToAddColorProfile 390
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 391
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 392
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 393
#define MGK_ResourceLimitErrorUnableToAllocateColormap 394
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 395
#define MGK_ResourceLimitErrorUnableToAllocateString 396
#define MGK_ResourceLimitErrorUnableToAnnotateImage 397
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 398
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 399
#define MGK_ResourceLimitErrorUnableToCloneImage 400
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 401
#define MGK_ResourceLimitErrorUnableToConstituteImage 402
#define MGK_ResourceLimitErrorUnableToConvertFont 403
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 404
#define MGK_ResourceLimitErrorUnableToCreateColormap 405
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 406
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 407
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 408
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 409
#define MGK_ResourceLimitErrorUnableToCreateXWindow 410
#define MGK_ResourceLimitErrorUnableToCropImage 411
#define MGK_ResourceLimitErrorUnableToDespeckleImage 412
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 413
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 414
#define MGK_ResourceLimitErrorUnableToDitherImage 415
#define MGK_ResourceLimitErrorUnableToDrawOnImage 416
#define MGK_ResourceLimitErrorUnableToEdgeImage 417
#define MGK_ResourceLimitErrorUnableToEmbossImage 418
#define MGK_ResourceLimitErrorUnableToEnhanceImage 419
#define MGK_ResourceLimitErrorUnableToFloodfillImage 420
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 421
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 422
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 423
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 424
#define MGK_ResourceLimitErrorUnableToLevelImage 425
#define MGK_ResourceLimitErrorUnableToMagnifyImage 426
#define MGK_ResourceLimitErrorUnableToManageColor 427
#define MGK_ResourceLimitErrorUnableToMapImage 428
#define MGK_ResourceLimitErrorUnableToMapImageSequence 429
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 430
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 431
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 432
#define MGK_ResourceLimitErrorUnableToNormalizeImage 433
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 434
#define MGK_ResourceLimitErrorUnableToQuantizeImage 435
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 436
#define MGK_ResourceLimitErrorUnableToReadTextChunk 437
#define MGK_ResourceLimitErrorUnableToReadXImage 438
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 439
#define MGK_ResourceLimitErrorUnableToResizeImage 440
#define MGK_ResourceLimitErrorUnableToRotateImage 441
#define MGK_ResourceLimitErrorUnableToSampleImage 442
#define MGK_ResourceLimitErrorUnableToScaleImage 443
#define MGK_ResourceLimitErrorUnableToSelectImage 444
#define MGK_ResourceLimitErrorUnableToSharpenImage 445
#define MGK_ResourceLimitErrorUnableToShaveImage 446
#define MGK_ResourceLimitErrorUnableToShearImage 447
#define MGK_ResourceLimitErrorUnableToSortImageColormap 448
#define MGK_ResourceLimitErrorUnableToThresholdImage 449
#define MGK_ResourceLimitErrorUnableToTransformColorspace 450
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 451
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 452
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 453
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 454
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 455
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 456
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 457
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 458
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 459
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 460
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 461
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 462
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 463
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 464
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 465
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 466
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 467
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 475
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 477
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 478
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 479
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 480
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 481
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 482
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 483
#define MGK_ResourceLimitFatalErrorUnableToConvertText 484
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 485
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 486
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 487
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 488
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 489
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 490
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 491
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 492
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 493
#define MGK_ResourceLimitWarningMemoryAllocationFailed 494
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 495
#define MGK_StreamErrorNoStreamHandlerIsDefined 496
#define MGK_StreamErrorPixelCacheIsNotOpen 497
#define MGK_StreamErrorUnableToAcquirePixelStream 498
#define MGK_StreamErrorUnableToSetPixelStream 499
#define MGK_StreamErrorUnableToSyncPixelStream 500
#define MGK_StreamFatalErrorDefault 501
#define MGK_StreamWarningDefault 502
#define MGK_TypeErrorFontSubstitutionRequired 503
#define MGK_TypeErrorUnableToGetTypeMetrics 504
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 505
#define MGK_TypeErrorUnableToReadFont 506
#define MGK_TypeErrorUnrecognizedFontEncoding 507
#define MGK_TypeFatalErrorDefault 508
#define MGK_TypeWarningDefault 509
#define MGK_WandErrorInvalidColormapIndex 510
#define MGK_WandErrorWandAPINotImplemented 511
#define MGK_WandErrorWandContainsNoImageIndexs 512
#define MGK_WandErrorWandContainsNoImages 513
#define MGK_XServerErrorColorIsNotKnownToServer 514
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 515
#define MGK_XServerErrorStandardColormapIsNotInitialized 516
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 517
#define MGK_XServerErrorUnableToCreateBitmap 518
#define MGK_XServerErrorUnableToCreateColormap 519
#define MGK_XServerErrorUnableToCreatePixmap 520
#define MGK_XServerErrorUnableToCreateProperty 521
#define MGK_XServerErrorUnableToCreateStandardColormap 522
#define MGK_XServerErrorUnableToDisplayImageInfo 523
#define MGK_XServerErrorUnableToGetProperty 524
#define MGK_XServerErrorUnableToGetStandardColormap 525
#define MGK_XServerErrorUnableToGetVisual 526
#define MGK_XServerErrorUnableToGrabMouse 527
#define MGK_XServerErrorUnableToLoadFont 528
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 529
#define MGK_XServerErrorUnableToOpenXServer 530
#define MGK_XServerErrorUnableToReadXAttributes 531
#define MGK_XServerErrorUnableToReadXWindowImage 532
#define MGK_XServerErrorUnrecognizedColormapType 533
#define MGK_XServerErrorUnrecognizedGravityType 534
#define MGK_XServerErrorUnrecognizedVisualSpecifier 535
#define MGK_XServerFatalErrorUnableToAllocateXHints 536
#define MGK_XServerFatalErrorUnableToCreateCursor 537
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 538
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 539
#define MGK_XServerFatalErrorUnableToCreateTextProperty 540
#define MGK_XServerFatalErrorUnableToCreateXImage 541
#define MGK_XServerFatalErrorUnableToCreateXPixmap 542
#define MGK_XServerFatalErrorUnableToCreateXWindow 543
#define MGK_XServerFatalErrorUnableToDisplayImage 544
#define MGK_XServerFatalErrorUnableToDitherImage 545
#define MGK_XServerFatalErrorUnableToGetPixelInfo 546
#define MGK_XServerFatalErrorUnableToGetVisual 547
#define MGK_XServerFatalErrorUnableToLoadFont 548
#define MGK_XServerFatalErrorUnableToMakeXWindow 549
#define MGK_XServerFatalErrorUnableToOpenXServer 550
#define MGK_XServerFatalErrorUnableToViewFonts 551
#define MGK_XServerWarningUnableToGetVisual 552
#define MGK_XServerWarningUsingDefaultVisual 553

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
    { "Corrupt/Image/FatalError", 158, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 159, CorruptImageWarning },
    { "Delegate/Error", 168, DelegateError },
    { "Delegate/FatalError", 186, DelegateFatalError },
    { "Delegate/Warning", 187, DelegateWarning },
    { "Draw/Error", 188, DrawError },
    { "Draw/FatalError", 199, DrawFatalError },
    { "Draw/Warning", 200, DrawWarning },
    { "File/Open/Error", 203, FileOpenError },
    { "File/Open/FatalError", 206, FileOpenFatalError },
    { "File/Open/Warning", 207, FileOpenWarning },
    { "Image/Error", 208, ImageError },
    { "Image/FatalError", 239, ImageFatalError },
    { "Image/Warning", 240, ImageWarning },
    { "Missing/Delegate/Error", 241, MissingDelegateError },
    { "Missing/Delegate/FatalError", 253, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 254, MissingDelegateWarning },
    { "Module/Error", 255, ModuleError },
    { "Module/FatalError", 260, ModuleFatalError },
    { "Module/Warning", 261, ModuleWarning },
    { "Monitor/Error", 262, MonitorError },
    { "Monitor/FatalError", 263, MonitorFatalError },
    { "Monitor/Warning", 265, MonitorWarning },
    { "Option/Error", 266, OptionError },
    { "Option/FatalError", 351, OptionFatalError },
    { "Option/Warning", 373, OptionWarning },
    { "Registry/Error", 374, RegistryError },
    { "Registry/FatalError", 380, RegistryFatalError },
    { "Registry/Warning", 381, RegistryWarning },
    { "Resource/Limit/Error", 382, ResourceLimitError },
    { "Resource/Limit/FatalError", 450, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 493, ResourceLimitWarning },
    { "Stream/Error", 494, StreamError },
    { "Stream/FatalError", 500, StreamFatalError },
    { "Stream/Warning", 501, StreamWarning },
    { "Type/Error", 502, TypeError },
    { "Type/FatalError", 507, TypeFatalError },
    { "Type/Warning", 508, TypeWarning },
    { "Wand/Error", 509, WandError },
    { "XServer/Error", 513, XServerError },
    { "XServer/FatalError", 535, XServerFatalError },
    { "XServer/Warning", 551, XServerWarning },
    { 0, 553, UndefinedException }
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
    { "UnsupportedNumberOfPlanes", 158 },
    { "UnableToPersistKey", 159 },
    { "CompressionNotValid", 160 },
    { "ImproperImageHeader", 161 },
    { "LengthAndFilesizeDoNotMatch", 162 },
    { "NegativeOrZeroImageSize", 163 },
    { "NonOS2HeaderSizeError", 164 },
    { "SkipToSyncByte", 165 },
    { "StaticPlanesValueNotEqualToOne", 166 },
    { "UnrecognizedBitsPerPixel", 167 },
    { "UnrecognizedImageCompression", 168 },
    { "DelegateFailed", 169 },
    { "FailedToAllocateArgumentList", 170 },
    { "FailedToAllocateGhostscriptInterpreter", 171 },
    { "FailedToComputeOutputSize", 172 },
    { "FailedToFindGhostscript", 173 },
    { "FailedToRenderFile", 174 },
    { "FailedToScanFile", 175 },
    { "NoTagFound", 176 },
    { "PostscriptDelegateFailed", 177 },
    { "UnableToCreateImage", 178 },
    { "UnableToCreateImageComponent", 179 },
    { "UnableToDecodeImageFile", 180 },
    { "UnableToEncodeImageFile", 181 },
    { "UnableToInitializeFPXLibrary", 182 },
    { "UnableToInitializeWMFLibrary", 183 },
    { "UnableToManageJP2Stream", 184 },
    { "UnableToWriteSVGFormat", 185 },
    { "WebPABIMismatch", 186 },
    { "Default", 187 },
    { "Default", 188 },
    { "AlreadyPushingPatternDefinition", 189 },
    { "DrawingRecursionDetected", 190 },
    { "FloatValueConversionError", 191 },
    { "IntegerValueConversionError", 192 },
    { "InvalidPrimitiveArgument", 193 },
    { "NonconformingDrawingPrimitiveDefinition", 194 },
    { "PrimitiveArithmeticOverflow", 195 },
    { "TooManyCoordinates", 196 },
    { "UnableToPrint", 197 },
    { "UnbalancedGraphicContextPushPop", 198 },
    { "VectorPathTruncated", 199 },
    { "Default", 200 },
    { "NotARelativeURL", 201 },
    { "NotCurrentlyPushingPatternDefinition", 202 },
    { "URLNotFound", 203 },
    { "UnableToCreateTemporaryFile", 204 },
    { "UnableToOpenFile", 205 },
    { "UnableToWriteFile", 206 },
    { "Default", 207 },
    { "Default", 208 },
    { "AngleIsDiscontinuous", 209 },
    { "ColorspaceColorProfileMismatch", 210 },
    { "ImageColorspaceDiffers", 211 },
    { "ImageColorspaceMismatch", 212 },
    { "ImageDifferenceExceedsLimit", 213 },
    { "ImageDoesNotContainResolution", 214 },
    { "ImageOpacityDiffers", 215 },
    { "ImageSequenceIsRequired", 216 },
    { "ImageSizeDiffers", 217 },
    { "InvalidColormapIndex", 218 },
    { "LeftAndRightImageSizesDiffer", 219 },
    { "NoImagesWereFound", 220 },
    { "NoImagesWereLoaded", 221 },
    { "NoLocaleImageAttribute", 222 },
    { "TooManyClusters", 223 },
    { "UnableToAppendImage", 224 },
    { "UnableToAssignProfile", 225 },
    { "UnableToAverageImage", 226 },
    { "UnableToCoalesceImage", 227 },
    { "UnableToCompareImages", 228 },
    { "UnableToCreateImageMosaic", 229 },
    { "UnableToCreateStereoImage", 230 },
    { "UnableToDeconstructImageSequence", 231 },
    { "UnableToFlattenImage", 232 },
    { "UnableToGetClipMask", 233 },
    { "UnableToHandleImageChannel", 234 },
    { "UnableToResizeImage", 235 },
    { "UnableToSegmentImage", 236 },
    { "UnableToSetClipMask", 237 },
    { "UnableToShearImage", 238 },
    { "WidthOrHeightExceedsLimit", 239 },
    { "UnableToPersistKey", 240 },
    { "Default", 241 },
    { "DPSLibraryIsNotAvailable", 242 },
    { "FPXLibraryIsNotAvailable", 243 },
    { "FreeTypeLibraryIsNotAvailable", 244 },
    { "JPEGLibraryIsNotAvailable", 245 },
    { "LCMSLibraryIsNotAvailable", 246 },
    { "LZWEncodingNotEnabled", 247 },
    { "NoDecodeDelegateForThisImageFormat", 248 },
    { "NoEncodeDelegateForThisImageFormat", 249 },
    { "TIFFLibraryIsNotAvailable", 250 },
    { "XMLLibraryIsNotAvailable", 251 },
    { "XWindowLibraryIsNotAvailable", 252 },
    { "ZipLibraryIsNotAvailable", 253 },
    { "Default", 254 },
    { "Default", 255 },
    { "FailedToCloseModule", 256 },
    { "FailedToFindSymbol", 257 },
    { "UnableToLoadModule", 258 },
    { "UnableToRegisterImageFormat", 259 },
    { "UnrecognizedModule", 260 },
    { "UnableToInitializeModuleLoader", 261 },
    { "Default", 262 },
    { "Default", 263 },
    { "Default", 264 },
    { "UserRequestedTerminationBySignal", 265 },
    { "Default", 266 },
    { "BevelWidthIsNegative", 267 },
    { "ColorSeparatedImageRequired", 268 },
    { "FrameIsLessThanImageSize", 269 },
    { "GeometryDimensionsAreZero", 270 },
    { "GeometryDoesNotContainImage", 271 },
    { "HaldClutImageDimensionsInvalid", 272 },
    { "ImagesAreNotTheSameSize", 273 },
    { "ImageSizeMustExceedBevelWidth", 274 },
    { "ImageSmallerThanKernelWidth", 275 },
    { "ImageSmallerThanRadius", 276 },
    { "ImageWidthsOrHeightsDiffer", 277 },
    { "InputImagesAlreadySpecified", 278 },
    { "InvalidSubimageSpecification", 279 },
    { "KernelRadiusIsTooSmall", 280 },
    { "KernelWidthMustBeAnOddNumber", 281 },
    { "MatrixIsNotSquare", 282 },
    { "MatrixOrderOutOfRange", 283 },
    { "MissingAnImageFilename", 284 },
    { "MissingArgument", 285 },
    { "MustSpecifyAnImageName", 286 },
    { "MustSpecifyImageSize", 287 },
    { "NoBlobDefined", 288 },
    { "NoImagesDefined", 289 },
    { "NonzeroWidthAndHeightRequired", 290 },
    { "NoProfileNameWasGiven", 291 },
    { "NullBlobArgument", 292 },
    { "ReferenceImageRequired", 293 },
    { "ReferenceIsNotMyType", 294 },
    { "RegionAreaExceedsLimit", 295 },
    { "RequestDidNotReturnAnImage", 296 },
    { "SteganoImageRequired", 297 },
    { "StereoImageRequired", 298 },
    { "SubimageSpecificationReturnsNoImages", 299 },
    { "UnableToAddOrRemoveProfile", 300 },
    { "UnableToAverageImageSequence", 301 },
    { "UnableToBlurImage", 302 },
    { "UnableToChopImage", 303 },
    { "UnableToColorMatrixImage", 304 },
    { "UnableToConstituteImage", 305 },
    { "UnableToConvolveImage", 306 },
    { "UnableToEdgeImage", 307 },
    { "UnableToEqualizeImage", 308 },
    { "UnableToFilterImage", 309 },
    { "UnableToFormatImageMetadata", 310 },
    { "UnableToFrameImage", 311 },
    { "UnableToOilPaintImage", 312 },
    { "UnableToPaintImage", 313 },
    { "UnableToRaiseImage", 314 },
    { "UnableToSharpenImage", 315 },
    { "UnableToThresholdImage", 316 },
    { "UnableToWaveImage", 317 },
    { "UnrecognizedAttribute", 318 },
    { "UnrecognizedChannelType", 319 },
    { "UnrecognizedColor", 320 },
    { "UnrecognizedColormapType", 321 },
    { "UnrecognizedColorspace", 322 },
    { "UnrecognizedCommand", 323 },
    { "UnrecognizedComposeOperator", 324 },
    { "UnrecognizedDisposeMethod", 325 },
    { "UnrecognizedElement", 326 },
    { "UnrecognizedEndianType", 327 },
    { "UnrecognizedGravityType", 328 },
    { "UnrecognizedHighlightStyle", 329 },
    { "UnrecognizedImageCompression", 330 },
    { "UnrecognizedImageFilter", 331 },
    { "UnrecognizedImageFormat", 332 },
    { "UnrecognizedImageMode", 333 },
    { "UnrecognizedImageType", 334 },
    { "UnrecognizedIntentType", 335 },
    { "UnrecognizedInterlaceType", 336 },
    { "UnrecognizedListType", 337 },
    { "UnrecognizedMetric", 338 },
    { "UnrecognizedModeType", 339 },
    { "UnrecognizedNoiseType", 340 },
    { "UnrecognizedOperator", 341 },
    { "UnrecognizedOption", 342 },
    { "UnrecognizedPerlMagickMethod", 343 },
    { "UnrecognizedPixelMap", 344 },
    { "UnrecognizedPreviewType", 345 },
    { "UnrecognizedResourceType", 346 },
    { "UnrecognizedType", 347 },
    { "UnrecognizedUnitsType", 348 },
    { "UnrecognizedVirtualPixelMethod", 349 },
    { "UnsupportedSamplingFactor", 350 },
    { "UsageError", 351 },
    { "InvalidColorspaceType", 352 },
    { "InvalidEndianType", 353 },
    { "InvalidImageType", 354 },
    { "InvalidInterlaceType", 355 },
    { "MissingAnImageFilename", 356 },
    { "MissingArgument", 357 },
    { "NoImagesWereLoaded", 358 },
    { "OptionLengthExceedsLimit", 359 },
    { "RequestDidNotReturnAnImage", 360 },
    { "UnableToOpenXServer", 361 },
    { "UnableToPersistKey", 362 },
    { "UnrecognizedColormapType", 363 },
    { "UnrecognizedColorspaceType", 364 },
    { "UnrecognizedDisposeMethod", 365 },
    { "UnrecognizedEndianType", 366 },
    { "UnrecognizedFilterType", 367 },
    { "UnrecognizedImageCompressionType", 368 },
    { "UnrecognizedImageType", 369 },
    { "UnrecognizedInterlaceType", 370 },
    { "UnrecognizedOption", 371 },
    { "UnrecognizedResourceType", 372 },
    { "UnrecognizedVirtualPixelMethod", 373 },
    { "UnrecognizedColor", 374 },
    { "ImageExpected", 375 },
    { "ImageInfoExpected", 376 },
    { "StructureSizeMismatch", 377 },
    { "UnableToGetRegistryID", 378 },
    { "UnableToLocateImage", 379 },
    { "UnableToSetRegistry", 380 },
    { "Default", 381 },
    { "Default", 382 },
    { "CacheResourcesExhausted", 383 },
    { "ImagePixelHeightLimitExceeded", 384 },
    { "ImagePixelLimitExceeded", 385 },
    { "ImagePixelWidthLimitExceeded", 386 },
    { "MemoryAllocationFailed", 387 },
    { "NoPixelsDefinedInCache", 388 },
    { "PixelCacheAllocationFailed", 389 },
    { "UnableToAddColorProfile", 390 },
    { "UnableToAddGenericProfile", 391 },
    { "UnableToAddIPTCProfile", 392 },
    { "UnableToAllocateCoefficients", 393 },
    { "UnableToAllocateColormap", 394 },
    { "UnableToAllocateICCProfile", 395 },
    { "UnableToAllocateString", 396 },
    { "UnableToAnnotateImage", 397 },
    { "UnableToAverageImageSequence", 398 },
    { "UnableToCloneDrawingWand", 399 },
    { "UnableToCloneImage", 400 },
    { "UnableToComputeImageSignature", 401 },
    { "UnableToConstituteImage", 402 },
    { "UnableToConvertFont", 403 },
    { "UnableToConvertStringToTokens", 404 },
    { "UnableToCreateColormap", 405 },
    { "UnableToCreateColorTransform", 406 },
    { "UnableToCreateCommandWidget", 407 },
    { "UnableToCreateImageGroup", 408 },
    { "UnableToCreateImageMontage", 409 },
    { "UnableToCreateXWindow", 410 },
    { "UnableToCropImage", 411 },
    { "UnableToDespeckleImage", 412 },
    { "UnableToDetermineImageClass", 413 },
    { "UnableToDetermineTheNumberOfImageColors", 414 },
    { "UnableToDitherImage", 415 },
    { "UnableToDrawOnImage", 416 },
    { "UnableToEdgeImage", 417 },
    { "UnableToEmbossImage", 418 },
    { "UnableToEnhanceImage", 419 },
    { "UnableToFloodfillImage", 420 },
    { "UnableToGammaCorrectImage", 421 },
    { "UnableToGetBestIconSize", 422 },
    { "UnableToGetFromRegistry", 423 },
    { "UnableToGetPackageInfo", 424 },
    { "UnableToLevelImage", 425 },
    { "UnableToMagnifyImage", 426 },
    { "UnableToManageColor", 427 },
    { "UnableToMapImage", 428 },
    { "UnableToMapImageSequence", 429 },
    { "UnableToMedianFilterImage", 430 },
    { "UnableToMotionBlurImage", 431 },
    { "UnableToNoiseFilterImage", 432 },
    { "UnableToNormalizeImage", 433 },
    { "UnableToOpenColorProfile", 434 },
    { "UnableToQuantizeImage", 435 },
    { "UnableToQuantizeImageSequence", 436 },
    { "UnableToReadTextChunk", 437 },
    { "UnableToReadXImage", 438 },
    { "UnableToReadXServerColormap", 439 },
    { "UnableToResizeImage", 440 },
    { "UnableToRotateImage", 441 },
    { "UnableToSampleImage", 442 },
    { "UnableToScaleImage", 443 },
    { "UnableToSelectImage", 444 },
    { "UnableToSharpenImage", 445 },
    { "UnableToShaveImage", 446 },
    { "UnableToShearImage", 447 },
    { "UnableToSortImageColormap", 448 },
    { "UnableToThresholdImage", 449 },
    { "UnableToTransformColorspace", 450 },
    { "MemoryAllocationFailed", 451 },
    { "SemaporeOperationFailed", 452 },
    { "UnableToAllocateAscii85Info", 453 },
    { "UnableToAllocateCacheInfo", 454 },
    { "UnableToAllocateCacheView", 455 },
    { "UnableToAllocateColorInfo", 456 },
    { "UnableToAllocateDashPattern", 457 },
    { "UnableToAllocateDelegateInfo", 458 },
    { "UnableToAllocateDerivatives", 459 },
    { "UnableToAllocateDrawContext", 460 },
    { "UnableToAllocateDrawInfo", 461 },
    { "UnableToAllocateDrawingWand", 462 },
    { "UnableToAllocateGammaMap", 463 },
    { "UnableToAllocateImage", 464 },
    { "UnableToAllocateImagePixels", 465 },
    { "UnableToAllocateLogInfo", 466 },
    { "UnableToAllocateMagicInfo", 467 },
    { "UnableToAllocateMagickInfo", 468 },
    { "UnableToAllocateModuleInfo", 469 },
    { "UnableToAllocateMontageInfo", 470 },
    { "UnableToAllocateQuantizeInfo", 471 },
    { "UnableToAllocateRandomKernel", 472 },
    { "UnableToAllocateRegistryInfo", 473 },
    { "UnableToAllocateSemaphoreInfo", 474 },
    { "UnableToAllocateString", 475 },
    { "UnableToAllocateTypeInfo", 476 },
    { "UnableToAllocateWand", 477 },
    { "UnableToAnimateImageSequence", 478 },
    { "UnableToCloneBlobInfo", 479 },
    { "UnableToCloneCacheInfo", 480 },
    { "UnableToCloneImage", 481 },
    { "UnableToCloneImageInfo", 482 },
    { "UnableToConcatenateString", 483 },
    { "UnableToConvertText", 484 },
    { "UnableToCreateColormap", 485 },
    { "UnableToDestroySemaphore", 486 },
    { "UnableToDisplayImage", 487 },
    { "UnableToEscapeString", 488 },
    { "UnableToInitializeSemaphore", 489 },
    { "UnableToInterpretMSLImage", 490 },
    { "UnableToLockSemaphore", 491 },
    { "UnableToObtainRandomEntropy", 492 },
    { "UnableToUnlockSemaphore", 493 },
    { "MemoryAllocationFailed", 494 },
    { "ImageDoesNotContainTheStreamGeometry", 495 },
    { "NoStreamHandlerIsDefined", 496 },
    { "PixelCacheIsNotOpen", 497 },
    { "UnableToAcquirePixelStream", 498 },
    { "UnableToSetPixelStream", 499 },
    { "UnableToSyncPixelStream", 500 },
    { "Default", 501 },
    { "Default", 502 },
    { "FontSubstitutionRequired", 503 },
    { "UnableToGetTypeMetrics", 504 },
    { "UnableToInitializeFreetypeLibrary", 505 },
    { "UnableToReadFont", 506 },
    { "UnrecognizedFontEncoding", 507 },
    { "Default", 508 },
    { "Default", 509 },
    { "InvalidColormapIndex", 510 },
    { "WandAPINotImplemented", 511 },
    { "WandContainsNoImageIndexs", 512 },
    { "WandContainsNoImages", 513 },
    { "ColorIsNotKnownToServer", 514 },
    { "NoWindowWithSpecifiedIDExists", 515 },
    { "StandardColormapIsNotInitialized", 516 },
    { "UnableToConnectToRemoteDisplay", 517 },
    { "UnableToCreateBitmap", 518 },
    { "UnableToCreateColormap", 519 },
    { "UnableToCreatePixmap", 520 },
    { "UnableToCreateProperty", 521 },
    { "UnableToCreateStandardColormap", 522 },
    { "UnableToDisplayImageInfo", 523 },
    { "UnableToGetProperty", 524 },
    { "UnableToGetStandardColormap", 525 },
    { "UnableToGetVisual", 526 },
    { "UnableToGrabMouse", 527 },
    { "UnableToLoadFont", 528 },
    { "UnableToMatchVisualToStandardColormap", 529 },
    { "UnableToOpenXServer", 530 },
    { "UnableToReadXAttributes", 531 },
    { "UnableToReadXWindowImage", 532 },
    { "UnrecognizedColormapType", 533 },
    { "UnrecognizedGravityType", 534 },
    { "UnrecognizedVisualSpecifier", 535 },
    { "UnableToAllocateXHints", 536 },
    { "UnableToCreateCursor", 537 },
    { "UnableToCreateGraphicContext", 538 },
    { "UnableToCreateStandardColormap", 539 },
    { "UnableToCreateTextProperty", 540 },
    { "UnableToCreateXImage", 541 },
    { "UnableToCreateXPixmap", 542 },
    { "UnableToCreateXWindow", 543 },
    { "UnableToDisplayImage", 544 },
    { "UnableToDitherImage", 545 },
    { "UnableToGetPixelInfo", 546 },
    { "UnableToGetVisual", 547 },
    { "UnableToLoadFont", 548 },
    { "UnableToMakeXWindow", 549 },
    { "UnableToOpenXServer", 550 },
    { "UnableToViewFonts", 551 },
    { "UnableToGetVisual", 552 },
    { "UsingDefaultVisual", 553 },
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
    "Unsupported number of planes",
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
    "drawing recursion detected",
    "text value does not convert to float",
    "text value does not convert to integer",
    "invalid primitive argument",
    "Non-conforming drawing primitive definition",
    "primitive arithmetic overflow",
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

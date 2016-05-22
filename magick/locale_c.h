#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 551

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
#define MGK_DrawErrorFloatValueConversionError 190
#define MGK_DrawErrorIntegerValueConversionError 191
#define MGK_DrawErrorInvalidPrimitiveArgument 192
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 193
#define MGK_DrawErrorTooManyCoordinates 194
#define MGK_DrawErrorUnableToPrint 195
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 196
#define MGK_DrawErrorVectorPathTruncated 197
#define MGK_DrawFatalErrorDefault 198
#define MGK_DrawWarningNotARelativeURL 199
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 200
#define MGK_DrawWarningURLNotFound 201
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 202
#define MGK_FileOpenErrorUnableToOpenFile 203
#define MGK_FileOpenErrorUnableToWriteFile 204
#define MGK_FileOpenFatalErrorDefault 205
#define MGK_FileOpenWarningDefault 206
#define MGK_ImageErrorAngleIsDiscontinuous 207
#define MGK_ImageErrorColorspaceColorProfileMismatch 208
#define MGK_ImageErrorImageColorspaceDiffers 209
#define MGK_ImageErrorImageColorspaceMismatch 210
#define MGK_ImageErrorImageDifferenceExceedsLimit 211
#define MGK_ImageErrorImageDoesNotContainResolution 212
#define MGK_ImageErrorImageOpacityDiffers 213
#define MGK_ImageErrorImageSequenceIsRequired 214
#define MGK_ImageErrorImageSizeDiffers 215
#define MGK_ImageErrorInvalidColormapIndex 216
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 217
#define MGK_ImageErrorNoImagesWereFound 218
#define MGK_ImageErrorNoImagesWereLoaded 219
#define MGK_ImageErrorNoLocaleImageAttribute 220
#define MGK_ImageErrorTooManyClusters 221
#define MGK_ImageErrorUnableToAppendImage 222
#define MGK_ImageErrorUnableToAssignProfile 223
#define MGK_ImageErrorUnableToAverageImage 224
#define MGK_ImageErrorUnableToCoalesceImage 225
#define MGK_ImageErrorUnableToCompareImages 226
#define MGK_ImageErrorUnableToCreateImageMosaic 227
#define MGK_ImageErrorUnableToCreateStereoImage 228
#define MGK_ImageErrorUnableToDeconstructImageSequence 229
#define MGK_ImageErrorUnableToFlattenImage 230
#define MGK_ImageErrorUnableToGetClipMask 231
#define MGK_ImageErrorUnableToHandleImageChannel 232
#define MGK_ImageErrorUnableToResizeImage 233
#define MGK_ImageErrorUnableToSegmentImage 234
#define MGK_ImageErrorUnableToSetClipMask 235
#define MGK_ImageErrorUnableToShearImage 236
#define MGK_ImageErrorWidthOrHeightExceedsLimit 237
#define MGK_ImageFatalErrorUnableToPersistKey 238
#define MGK_ImageWarningDefault 239
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 240
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 241
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 242
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 243
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 244
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 245
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 246
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 247
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 248
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 249
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 250
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 251
#define MGK_MissingDelegateFatalErrorDefault 252
#define MGK_MissingDelegateWarningDefault 253
#define MGK_ModuleErrorFailedToCloseModule 254
#define MGK_ModuleErrorFailedToFindSymbol 255
#define MGK_ModuleErrorUnableToLoadModule 256
#define MGK_ModuleErrorUnableToRegisterImageFormat 257
#define MGK_ModuleErrorUnrecognizedModule 258
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 259
#define MGK_ModuleWarningDefault 260
#define MGK_MonitorErrorDefault 261
#define MGK_MonitorFatalErrorDefault 262
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 263
#define MGK_MonitorWarningDefault 264
#define MGK_OptionErrorBevelWidthIsNegative 265
#define MGK_OptionErrorColorSeparatedImageRequired 266
#define MGK_OptionErrorFrameIsLessThanImageSize 267
#define MGK_OptionErrorGeometryDimensionsAreZero 268
#define MGK_OptionErrorGeometryDoesNotContainImage 269
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 270
#define MGK_OptionErrorImagesAreNotTheSameSize 271
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 272
#define MGK_OptionErrorImageSmallerThanKernelWidth 273
#define MGK_OptionErrorImageSmallerThanRadius 274
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 275
#define MGK_OptionErrorInputImagesAlreadySpecified 276
#define MGK_OptionErrorInvalidSubimageSpecification 277
#define MGK_OptionErrorKernelRadiusIsTooSmall 278
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 279
#define MGK_OptionErrorMatrixIsNotSquare 280
#define MGK_OptionErrorMatrixOrderOutOfRange 281
#define MGK_OptionErrorMissingAnImageFilename 282
#define MGK_OptionErrorMissingArgument 283
#define MGK_OptionErrorMustSpecifyAnImageName 284
#define MGK_OptionErrorMustSpecifyImageSize 285
#define MGK_OptionErrorNoBlobDefined 286
#define MGK_OptionErrorNoImagesDefined 287
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 288
#define MGK_OptionErrorNoProfileNameWasGiven 289
#define MGK_OptionErrorNullBlobArgument 290
#define MGK_OptionErrorReferenceImageRequired 291
#define MGK_OptionErrorReferenceIsNotMyType 292
#define MGK_OptionErrorRegionAreaExceedsLimit 293
#define MGK_OptionErrorRequestDidNotReturnAnImage 294
#define MGK_OptionErrorSteganoImageRequired 295
#define MGK_OptionErrorStereoImageRequired 296
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 297
#define MGK_OptionErrorUnableToAddOrRemoveProfile 298
#define MGK_OptionErrorUnableToAverageImageSequence 299
#define MGK_OptionErrorUnableToBlurImage 300
#define MGK_OptionErrorUnableToChopImage 301
#define MGK_OptionErrorUnableToColorMatrixImage 302
#define MGK_OptionErrorUnableToConstituteImage 303
#define MGK_OptionErrorUnableToConvolveImage 304
#define MGK_OptionErrorUnableToEdgeImage 305
#define MGK_OptionErrorUnableToEqualizeImage 306
#define MGK_OptionErrorUnableToFilterImage 307
#define MGK_OptionErrorUnableToFormatImageMetadata 308
#define MGK_OptionErrorUnableToFrameImage 309
#define MGK_OptionErrorUnableToOilPaintImage 310
#define MGK_OptionErrorUnableToPaintImage 311
#define MGK_OptionErrorUnableToRaiseImage 312
#define MGK_OptionErrorUnableToSharpenImage 313
#define MGK_OptionErrorUnableToThresholdImage 314
#define MGK_OptionErrorUnableToWaveImage 315
#define MGK_OptionErrorUnrecognizedAttribute 316
#define MGK_OptionErrorUnrecognizedChannelType 317
#define MGK_OptionErrorUnrecognizedColor 318
#define MGK_OptionErrorUnrecognizedColormapType 319
#define MGK_OptionErrorUnrecognizedColorspace 320
#define MGK_OptionErrorUnrecognizedCommand 321
#define MGK_OptionErrorUnrecognizedComposeOperator 322
#define MGK_OptionErrorUnrecognizedDisposeMethod 323
#define MGK_OptionErrorUnrecognizedElement 324
#define MGK_OptionErrorUnrecognizedEndianType 325
#define MGK_OptionErrorUnrecognizedGravityType 326
#define MGK_OptionErrorUnrecognizedHighlightStyle 327
#define MGK_OptionErrorUnrecognizedImageCompression 328
#define MGK_OptionErrorUnrecognizedImageFilter 329
#define MGK_OptionErrorUnrecognizedImageFormat 330
#define MGK_OptionErrorUnrecognizedImageMode 331
#define MGK_OptionErrorUnrecognizedImageType 332
#define MGK_OptionErrorUnrecognizedIntentType 333
#define MGK_OptionErrorUnrecognizedInterlaceType 334
#define MGK_OptionErrorUnrecognizedListType 335
#define MGK_OptionErrorUnrecognizedMetric 336
#define MGK_OptionErrorUnrecognizedModeType 337
#define MGK_OptionErrorUnrecognizedNoiseType 338
#define MGK_OptionErrorUnrecognizedOperator 339
#define MGK_OptionErrorUnrecognizedOption 340
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 341
#define MGK_OptionErrorUnrecognizedPixelMap 342
#define MGK_OptionErrorUnrecognizedPreviewType 343
#define MGK_OptionErrorUnrecognizedResourceType 344
#define MGK_OptionErrorUnrecognizedType 345
#define MGK_OptionErrorUnrecognizedUnitsType 346
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 347
#define MGK_OptionErrorUnsupportedSamplingFactor 348
#define MGK_OptionErrorUsageError 349
#define MGK_OptionFatalErrorInvalidColorspaceType 350
#define MGK_OptionFatalErrorInvalidEndianType 351
#define MGK_OptionFatalErrorInvalidImageType 352
#define MGK_OptionFatalErrorInvalidInterlaceType 353
#define MGK_OptionFatalErrorMissingAnImageFilename 354
#define MGK_OptionFatalErrorMissingArgument 355
#define MGK_OptionFatalErrorNoImagesWereLoaded 356
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 357
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 358
#define MGK_OptionFatalErrorUnableToOpenXServer 359
#define MGK_OptionFatalErrorUnableToPersistKey 360
#define MGK_OptionFatalErrorUnrecognizedColormapType 361
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 362
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 363
#define MGK_OptionFatalErrorUnrecognizedEndianType 364
#define MGK_OptionFatalErrorUnrecognizedFilterType 365
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 366
#define MGK_OptionFatalErrorUnrecognizedImageType 367
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 368
#define MGK_OptionFatalErrorUnrecognizedOption 369
#define MGK_OptionFatalErrorUnrecognizedResourceType 370
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 371
#define MGK_OptionWarningUnrecognizedColor 372
#define MGK_RegistryErrorImageExpected 373
#define MGK_RegistryErrorImageInfoExpected 374
#define MGK_RegistryErrorStructureSizeMismatch 375
#define MGK_RegistryErrorUnableToGetRegistryID 376
#define MGK_RegistryErrorUnableToLocateImage 377
#define MGK_RegistryErrorUnableToSetRegistry 378
#define MGK_RegistryFatalErrorDefault 379
#define MGK_RegistryWarningDefault 380
#define MGK_ResourceLimitErrorCacheResourcesExhausted 381
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 382
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 383
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 384
#define MGK_ResourceLimitErrorMemoryAllocationFailed 385
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 386
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 387
#define MGK_ResourceLimitErrorUnableToAddColorProfile 388
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 389
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 390
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 391
#define MGK_ResourceLimitErrorUnableToAllocateColormap 392
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 393
#define MGK_ResourceLimitErrorUnableToAllocateString 394
#define MGK_ResourceLimitErrorUnableToAnnotateImage 395
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 396
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 397
#define MGK_ResourceLimitErrorUnableToCloneImage 398
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 399
#define MGK_ResourceLimitErrorUnableToConstituteImage 400
#define MGK_ResourceLimitErrorUnableToConvertFont 401
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 402
#define MGK_ResourceLimitErrorUnableToCreateColormap 403
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 404
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 405
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 406
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 407
#define MGK_ResourceLimitErrorUnableToCreateXWindow 408
#define MGK_ResourceLimitErrorUnableToCropImage 409
#define MGK_ResourceLimitErrorUnableToDespeckleImage 410
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 411
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 412
#define MGK_ResourceLimitErrorUnableToDitherImage 413
#define MGK_ResourceLimitErrorUnableToDrawOnImage 414
#define MGK_ResourceLimitErrorUnableToEdgeImage 415
#define MGK_ResourceLimitErrorUnableToEmbossImage 416
#define MGK_ResourceLimitErrorUnableToEnhanceImage 417
#define MGK_ResourceLimitErrorUnableToFloodfillImage 418
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 419
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 420
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 421
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 422
#define MGK_ResourceLimitErrorUnableToLevelImage 423
#define MGK_ResourceLimitErrorUnableToMagnifyImage 424
#define MGK_ResourceLimitErrorUnableToManageColor 425
#define MGK_ResourceLimitErrorUnableToMapImage 426
#define MGK_ResourceLimitErrorUnableToMapImageSequence 427
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 428
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 429
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 430
#define MGK_ResourceLimitErrorUnableToNormalizeImage 431
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 432
#define MGK_ResourceLimitErrorUnableToQuantizeImage 433
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 434
#define MGK_ResourceLimitErrorUnableToReadTextChunk 435
#define MGK_ResourceLimitErrorUnableToReadXImage 436
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 437
#define MGK_ResourceLimitErrorUnableToResizeImage 438
#define MGK_ResourceLimitErrorUnableToRotateImage 439
#define MGK_ResourceLimitErrorUnableToSampleImage 440
#define MGK_ResourceLimitErrorUnableToScaleImage 441
#define MGK_ResourceLimitErrorUnableToSelectImage 442
#define MGK_ResourceLimitErrorUnableToSharpenImage 443
#define MGK_ResourceLimitErrorUnableToShaveImage 444
#define MGK_ResourceLimitErrorUnableToShearImage 445
#define MGK_ResourceLimitErrorUnableToSortImageColormap 446
#define MGK_ResourceLimitErrorUnableToThresholdImage 447
#define MGK_ResourceLimitErrorUnableToTransformColorspace 448
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 449
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 450
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 451
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 452
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 453
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 454
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 455
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 456
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 457
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 458
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 459
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 460
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 461
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 462
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 463
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 464
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 465
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 466
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 467
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 475
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 476
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 477
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 478
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 479
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 480
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 481
#define MGK_ResourceLimitFatalErrorUnableToConvertText 482
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 483
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 484
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 485
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 486
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 487
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 488
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 489
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 490
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 491
#define MGK_ResourceLimitWarningMemoryAllocationFailed 492
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 493
#define MGK_StreamErrorNoStreamHandlerIsDefined 494
#define MGK_StreamErrorPixelCacheIsNotOpen 495
#define MGK_StreamErrorUnableToAcquirePixelStream 496
#define MGK_StreamErrorUnableToSetPixelStream 497
#define MGK_StreamErrorUnableToSyncPixelStream 498
#define MGK_StreamFatalErrorDefault 499
#define MGK_StreamWarningDefault 500
#define MGK_TypeErrorFontSubstitutionRequired 501
#define MGK_TypeErrorUnableToGetTypeMetrics 502
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 503
#define MGK_TypeErrorUnableToReadFont 504
#define MGK_TypeErrorUnrecognizedFontEncoding 505
#define MGK_TypeFatalErrorDefault 506
#define MGK_TypeWarningDefault 507
#define MGK_WandErrorInvalidColormapIndex 508
#define MGK_WandErrorWandAPINotImplemented 509
#define MGK_WandErrorWandContainsNoImageIndexs 510
#define MGK_WandErrorWandContainsNoImages 511
#define MGK_XServerErrorColorIsNotKnownToServer 512
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 513
#define MGK_XServerErrorStandardColormapIsNotInitialized 514
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 515
#define MGK_XServerErrorUnableToCreateBitmap 516
#define MGK_XServerErrorUnableToCreateColormap 517
#define MGK_XServerErrorUnableToCreatePixmap 518
#define MGK_XServerErrorUnableToCreateProperty 519
#define MGK_XServerErrorUnableToCreateStandardColormap 520
#define MGK_XServerErrorUnableToDisplayImageInfo 521
#define MGK_XServerErrorUnableToGetProperty 522
#define MGK_XServerErrorUnableToGetStandardColormap 523
#define MGK_XServerErrorUnableToGetVisual 524
#define MGK_XServerErrorUnableToGrabMouse 525
#define MGK_XServerErrorUnableToLoadFont 526
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 527
#define MGK_XServerErrorUnableToOpenXServer 528
#define MGK_XServerErrorUnableToReadXAttributes 529
#define MGK_XServerErrorUnableToReadXWindowImage 530
#define MGK_XServerErrorUnrecognizedColormapType 531
#define MGK_XServerErrorUnrecognizedGravityType 532
#define MGK_XServerErrorUnrecognizedVisualSpecifier 533
#define MGK_XServerFatalErrorUnableToAllocateXHints 534
#define MGK_XServerFatalErrorUnableToCreateCursor 535
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 536
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 537
#define MGK_XServerFatalErrorUnableToCreateTextProperty 538
#define MGK_XServerFatalErrorUnableToCreateXImage 539
#define MGK_XServerFatalErrorUnableToCreateXPixmap 540
#define MGK_XServerFatalErrorUnableToCreateXWindow 541
#define MGK_XServerFatalErrorUnableToDisplayImage 542
#define MGK_XServerFatalErrorUnableToDitherImage 543
#define MGK_XServerFatalErrorUnableToGetPixelInfo 544
#define MGK_XServerFatalErrorUnableToGetVisual 545
#define MGK_XServerFatalErrorUnableToLoadFont 546
#define MGK_XServerFatalErrorUnableToMakeXWindow 547
#define MGK_XServerFatalErrorUnableToOpenXServer 548
#define MGK_XServerFatalErrorUnableToViewFonts 549
#define MGK_XServerWarningUnableToGetVisual 550
#define MGK_XServerWarningUsingDefaultVisual 551

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
    { "Draw/FatalError", 197, DrawFatalError },
    { "Draw/Warning", 198, DrawWarning },
    { "File/Open/Error", 201, FileOpenError },
    { "File/Open/FatalError", 204, FileOpenFatalError },
    { "File/Open/Warning", 205, FileOpenWarning },
    { "Image/Error", 206, ImageError },
    { "Image/FatalError", 237, ImageFatalError },
    { "Image/Warning", 238, ImageWarning },
    { "Missing/Delegate/Error", 239, MissingDelegateError },
    { "Missing/Delegate/FatalError", 251, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 252, MissingDelegateWarning },
    { "Module/Error", 253, ModuleError },
    { "Module/FatalError", 258, ModuleFatalError },
    { "Module/Warning", 259, ModuleWarning },
    { "Monitor/Error", 260, MonitorError },
    { "Monitor/FatalError", 261, MonitorFatalError },
    { "Monitor/Warning", 263, MonitorWarning },
    { "Option/Error", 264, OptionError },
    { "Option/FatalError", 349, OptionFatalError },
    { "Option/Warning", 371, OptionWarning },
    { "Registry/Error", 372, RegistryError },
    { "Registry/FatalError", 378, RegistryFatalError },
    { "Registry/Warning", 379, RegistryWarning },
    { "Resource/Limit/Error", 380, ResourceLimitError },
    { "Resource/Limit/FatalError", 448, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 491, ResourceLimitWarning },
    { "Stream/Error", 492, StreamError },
    { "Stream/FatalError", 498, StreamFatalError },
    { "Stream/Warning", 499, StreamWarning },
    { "Type/Error", 500, TypeError },
    { "Type/FatalError", 505, TypeFatalError },
    { "Type/Warning", 506, TypeWarning },
    { "Wand/Error", 507, WandError },
    { "XServer/Error", 511, XServerError },
    { "XServer/FatalError", 533, XServerFatalError },
    { "XServer/Warning", 549, XServerWarning },
    { 0, 551, UndefinedException }
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
    { "FloatValueConversionError", 190 },
    { "IntegerValueConversionError", 191 },
    { "InvalidPrimitiveArgument", 192 },
    { "NonconformingDrawingPrimitiveDefinition", 193 },
    { "TooManyCoordinates", 194 },
    { "UnableToPrint", 195 },
    { "UnbalancedGraphicContextPushPop", 196 },
    { "VectorPathTruncated", 197 },
    { "Default", 198 },
    { "NotARelativeURL", 199 },
    { "NotCurrentlyPushingPatternDefinition", 200 },
    { "URLNotFound", 201 },
    { "UnableToCreateTemporaryFile", 202 },
    { "UnableToOpenFile", 203 },
    { "UnableToWriteFile", 204 },
    { "Default", 205 },
    { "Default", 206 },
    { "AngleIsDiscontinuous", 207 },
    { "ColorspaceColorProfileMismatch", 208 },
    { "ImageColorspaceDiffers", 209 },
    { "ImageColorspaceMismatch", 210 },
    { "ImageDifferenceExceedsLimit", 211 },
    { "ImageDoesNotContainResolution", 212 },
    { "ImageOpacityDiffers", 213 },
    { "ImageSequenceIsRequired", 214 },
    { "ImageSizeDiffers", 215 },
    { "InvalidColormapIndex", 216 },
    { "LeftAndRightImageSizesDiffer", 217 },
    { "NoImagesWereFound", 218 },
    { "NoImagesWereLoaded", 219 },
    { "NoLocaleImageAttribute", 220 },
    { "TooManyClusters", 221 },
    { "UnableToAppendImage", 222 },
    { "UnableToAssignProfile", 223 },
    { "UnableToAverageImage", 224 },
    { "UnableToCoalesceImage", 225 },
    { "UnableToCompareImages", 226 },
    { "UnableToCreateImageMosaic", 227 },
    { "UnableToCreateStereoImage", 228 },
    { "UnableToDeconstructImageSequence", 229 },
    { "UnableToFlattenImage", 230 },
    { "UnableToGetClipMask", 231 },
    { "UnableToHandleImageChannel", 232 },
    { "UnableToResizeImage", 233 },
    { "UnableToSegmentImage", 234 },
    { "UnableToSetClipMask", 235 },
    { "UnableToShearImage", 236 },
    { "WidthOrHeightExceedsLimit", 237 },
    { "UnableToPersistKey", 238 },
    { "Default", 239 },
    { "DPSLibraryIsNotAvailable", 240 },
    { "FPXLibraryIsNotAvailable", 241 },
    { "FreeTypeLibraryIsNotAvailable", 242 },
    { "JPEGLibraryIsNotAvailable", 243 },
    { "LCMSLibraryIsNotAvailable", 244 },
    { "LZWEncodingNotEnabled", 245 },
    { "NoDecodeDelegateForThisImageFormat", 246 },
    { "NoEncodeDelegateForThisImageFormat", 247 },
    { "TIFFLibraryIsNotAvailable", 248 },
    { "XMLLibraryIsNotAvailable", 249 },
    { "XWindowLibraryIsNotAvailable", 250 },
    { "ZipLibraryIsNotAvailable", 251 },
    { "Default", 252 },
    { "Default", 253 },
    { "FailedToCloseModule", 254 },
    { "FailedToFindSymbol", 255 },
    { "UnableToLoadModule", 256 },
    { "UnableToRegisterImageFormat", 257 },
    { "UnrecognizedModule", 258 },
    { "UnableToInitializeModuleLoader", 259 },
    { "Default", 260 },
    { "Default", 261 },
    { "Default", 262 },
    { "UserRequestedTerminationBySignal", 263 },
    { "Default", 264 },
    { "BevelWidthIsNegative", 265 },
    { "ColorSeparatedImageRequired", 266 },
    { "FrameIsLessThanImageSize", 267 },
    { "GeometryDimensionsAreZero", 268 },
    { "GeometryDoesNotContainImage", 269 },
    { "HaldClutImageDimensionsInvalid", 270 },
    { "ImagesAreNotTheSameSize", 271 },
    { "ImageSizeMustExceedBevelWidth", 272 },
    { "ImageSmallerThanKernelWidth", 273 },
    { "ImageSmallerThanRadius", 274 },
    { "ImageWidthsOrHeightsDiffer", 275 },
    { "InputImagesAlreadySpecified", 276 },
    { "InvalidSubimageSpecification", 277 },
    { "KernelRadiusIsTooSmall", 278 },
    { "KernelWidthMustBeAnOddNumber", 279 },
    { "MatrixIsNotSquare", 280 },
    { "MatrixOrderOutOfRange", 281 },
    { "MissingAnImageFilename", 282 },
    { "MissingArgument", 283 },
    { "MustSpecifyAnImageName", 284 },
    { "MustSpecifyImageSize", 285 },
    { "NoBlobDefined", 286 },
    { "NoImagesDefined", 287 },
    { "NonzeroWidthAndHeightRequired", 288 },
    { "NoProfileNameWasGiven", 289 },
    { "NullBlobArgument", 290 },
    { "ReferenceImageRequired", 291 },
    { "ReferenceIsNotMyType", 292 },
    { "RegionAreaExceedsLimit", 293 },
    { "RequestDidNotReturnAnImage", 294 },
    { "SteganoImageRequired", 295 },
    { "StereoImageRequired", 296 },
    { "SubimageSpecificationReturnsNoImages", 297 },
    { "UnableToAddOrRemoveProfile", 298 },
    { "UnableToAverageImageSequence", 299 },
    { "UnableToBlurImage", 300 },
    { "UnableToChopImage", 301 },
    { "UnableToColorMatrixImage", 302 },
    { "UnableToConstituteImage", 303 },
    { "UnableToConvolveImage", 304 },
    { "UnableToEdgeImage", 305 },
    { "UnableToEqualizeImage", 306 },
    { "UnableToFilterImage", 307 },
    { "UnableToFormatImageMetadata", 308 },
    { "UnableToFrameImage", 309 },
    { "UnableToOilPaintImage", 310 },
    { "UnableToPaintImage", 311 },
    { "UnableToRaiseImage", 312 },
    { "UnableToSharpenImage", 313 },
    { "UnableToThresholdImage", 314 },
    { "UnableToWaveImage", 315 },
    { "UnrecognizedAttribute", 316 },
    { "UnrecognizedChannelType", 317 },
    { "UnrecognizedColor", 318 },
    { "UnrecognizedColormapType", 319 },
    { "UnrecognizedColorspace", 320 },
    { "UnrecognizedCommand", 321 },
    { "UnrecognizedComposeOperator", 322 },
    { "UnrecognizedDisposeMethod", 323 },
    { "UnrecognizedElement", 324 },
    { "UnrecognizedEndianType", 325 },
    { "UnrecognizedGravityType", 326 },
    { "UnrecognizedHighlightStyle", 327 },
    { "UnrecognizedImageCompression", 328 },
    { "UnrecognizedImageFilter", 329 },
    { "UnrecognizedImageFormat", 330 },
    { "UnrecognizedImageMode", 331 },
    { "UnrecognizedImageType", 332 },
    { "UnrecognizedIntentType", 333 },
    { "UnrecognizedInterlaceType", 334 },
    { "UnrecognizedListType", 335 },
    { "UnrecognizedMetric", 336 },
    { "UnrecognizedModeType", 337 },
    { "UnrecognizedNoiseType", 338 },
    { "UnrecognizedOperator", 339 },
    { "UnrecognizedOption", 340 },
    { "UnrecognizedPerlMagickMethod", 341 },
    { "UnrecognizedPixelMap", 342 },
    { "UnrecognizedPreviewType", 343 },
    { "UnrecognizedResourceType", 344 },
    { "UnrecognizedType", 345 },
    { "UnrecognizedUnitsType", 346 },
    { "UnrecognizedVirtualPixelMethod", 347 },
    { "UnsupportedSamplingFactor", 348 },
    { "UsageError", 349 },
    { "InvalidColorspaceType", 350 },
    { "InvalidEndianType", 351 },
    { "InvalidImageType", 352 },
    { "InvalidInterlaceType", 353 },
    { "MissingAnImageFilename", 354 },
    { "MissingArgument", 355 },
    { "NoImagesWereLoaded", 356 },
    { "OptionLengthExceedsLimit", 357 },
    { "RequestDidNotReturnAnImage", 358 },
    { "UnableToOpenXServer", 359 },
    { "UnableToPersistKey", 360 },
    { "UnrecognizedColormapType", 361 },
    { "UnrecognizedColorspaceType", 362 },
    { "UnrecognizedDisposeMethod", 363 },
    { "UnrecognizedEndianType", 364 },
    { "UnrecognizedFilterType", 365 },
    { "UnrecognizedImageCompressionType", 366 },
    { "UnrecognizedImageType", 367 },
    { "UnrecognizedInterlaceType", 368 },
    { "UnrecognizedOption", 369 },
    { "UnrecognizedResourceType", 370 },
    { "UnrecognizedVirtualPixelMethod", 371 },
    { "UnrecognizedColor", 372 },
    { "ImageExpected", 373 },
    { "ImageInfoExpected", 374 },
    { "StructureSizeMismatch", 375 },
    { "UnableToGetRegistryID", 376 },
    { "UnableToLocateImage", 377 },
    { "UnableToSetRegistry", 378 },
    { "Default", 379 },
    { "Default", 380 },
    { "CacheResourcesExhausted", 381 },
    { "ImagePixelHeightLimitExceeded", 382 },
    { "ImagePixelLimitExceeded", 383 },
    { "ImagePixelWidthLimitExceeded", 384 },
    { "MemoryAllocationFailed", 385 },
    { "NoPixelsDefinedInCache", 386 },
    { "PixelCacheAllocationFailed", 387 },
    { "UnableToAddColorProfile", 388 },
    { "UnableToAddGenericProfile", 389 },
    { "UnableToAddIPTCProfile", 390 },
    { "UnableToAllocateCoefficients", 391 },
    { "UnableToAllocateColormap", 392 },
    { "UnableToAllocateICCProfile", 393 },
    { "UnableToAllocateString", 394 },
    { "UnableToAnnotateImage", 395 },
    { "UnableToAverageImageSequence", 396 },
    { "UnableToCloneDrawingWand", 397 },
    { "UnableToCloneImage", 398 },
    { "UnableToComputeImageSignature", 399 },
    { "UnableToConstituteImage", 400 },
    { "UnableToConvertFont", 401 },
    { "UnableToConvertStringToTokens", 402 },
    { "UnableToCreateColormap", 403 },
    { "UnableToCreateColorTransform", 404 },
    { "UnableToCreateCommandWidget", 405 },
    { "UnableToCreateImageGroup", 406 },
    { "UnableToCreateImageMontage", 407 },
    { "UnableToCreateXWindow", 408 },
    { "UnableToCropImage", 409 },
    { "UnableToDespeckleImage", 410 },
    { "UnableToDetermineImageClass", 411 },
    { "UnableToDetermineTheNumberOfImageColors", 412 },
    { "UnableToDitherImage", 413 },
    { "UnableToDrawOnImage", 414 },
    { "UnableToEdgeImage", 415 },
    { "UnableToEmbossImage", 416 },
    { "UnableToEnhanceImage", 417 },
    { "UnableToFloodfillImage", 418 },
    { "UnableToGammaCorrectImage", 419 },
    { "UnableToGetBestIconSize", 420 },
    { "UnableToGetFromRegistry", 421 },
    { "UnableToGetPackageInfo", 422 },
    { "UnableToLevelImage", 423 },
    { "UnableToMagnifyImage", 424 },
    { "UnableToManageColor", 425 },
    { "UnableToMapImage", 426 },
    { "UnableToMapImageSequence", 427 },
    { "UnableToMedianFilterImage", 428 },
    { "UnableToMotionBlurImage", 429 },
    { "UnableToNoiseFilterImage", 430 },
    { "UnableToNormalizeImage", 431 },
    { "UnableToOpenColorProfile", 432 },
    { "UnableToQuantizeImage", 433 },
    { "UnableToQuantizeImageSequence", 434 },
    { "UnableToReadTextChunk", 435 },
    { "UnableToReadXImage", 436 },
    { "UnableToReadXServerColormap", 437 },
    { "UnableToResizeImage", 438 },
    { "UnableToRotateImage", 439 },
    { "UnableToSampleImage", 440 },
    { "UnableToScaleImage", 441 },
    { "UnableToSelectImage", 442 },
    { "UnableToSharpenImage", 443 },
    { "UnableToShaveImage", 444 },
    { "UnableToShearImage", 445 },
    { "UnableToSortImageColormap", 446 },
    { "UnableToThresholdImage", 447 },
    { "UnableToTransformColorspace", 448 },
    { "MemoryAllocationFailed", 449 },
    { "SemaporeOperationFailed", 450 },
    { "UnableToAllocateAscii85Info", 451 },
    { "UnableToAllocateCacheInfo", 452 },
    { "UnableToAllocateCacheView", 453 },
    { "UnableToAllocateColorInfo", 454 },
    { "UnableToAllocateDashPattern", 455 },
    { "UnableToAllocateDelegateInfo", 456 },
    { "UnableToAllocateDerivatives", 457 },
    { "UnableToAllocateDrawContext", 458 },
    { "UnableToAllocateDrawInfo", 459 },
    { "UnableToAllocateDrawingWand", 460 },
    { "UnableToAllocateGammaMap", 461 },
    { "UnableToAllocateImage", 462 },
    { "UnableToAllocateImagePixels", 463 },
    { "UnableToAllocateLogInfo", 464 },
    { "UnableToAllocateMagicInfo", 465 },
    { "UnableToAllocateMagickInfo", 466 },
    { "UnableToAllocateModuleInfo", 467 },
    { "UnableToAllocateMontageInfo", 468 },
    { "UnableToAllocateQuantizeInfo", 469 },
    { "UnableToAllocateRandomKernel", 470 },
    { "UnableToAllocateRegistryInfo", 471 },
    { "UnableToAllocateSemaphoreInfo", 472 },
    { "UnableToAllocateString", 473 },
    { "UnableToAllocateTypeInfo", 474 },
    { "UnableToAllocateWand", 475 },
    { "UnableToAnimateImageSequence", 476 },
    { "UnableToCloneBlobInfo", 477 },
    { "UnableToCloneCacheInfo", 478 },
    { "UnableToCloneImage", 479 },
    { "UnableToCloneImageInfo", 480 },
    { "UnableToConcatenateString", 481 },
    { "UnableToConvertText", 482 },
    { "UnableToCreateColormap", 483 },
    { "UnableToDestroySemaphore", 484 },
    { "UnableToDisplayImage", 485 },
    { "UnableToEscapeString", 486 },
    { "UnableToInitializeSemaphore", 487 },
    { "UnableToInterpretMSLImage", 488 },
    { "UnableToLockSemaphore", 489 },
    { "UnableToObtainRandomEntropy", 490 },
    { "UnableToUnlockSemaphore", 491 },
    { "MemoryAllocationFailed", 492 },
    { "ImageDoesNotContainTheStreamGeometry", 493 },
    { "NoStreamHandlerIsDefined", 494 },
    { "PixelCacheIsNotOpen", 495 },
    { "UnableToAcquirePixelStream", 496 },
    { "UnableToSetPixelStream", 497 },
    { "UnableToSyncPixelStream", 498 },
    { "Default", 499 },
    { "Default", 500 },
    { "FontSubstitutionRequired", 501 },
    { "UnableToGetTypeMetrics", 502 },
    { "UnableToInitializeFreetypeLibrary", 503 },
    { "UnableToReadFont", 504 },
    { "UnrecognizedFontEncoding", 505 },
    { "Default", 506 },
    { "Default", 507 },
    { "InvalidColormapIndex", 508 },
    { "WandAPINotImplemented", 509 },
    { "WandContainsNoImageIndexs", 510 },
    { "WandContainsNoImages", 511 },
    { "ColorIsNotKnownToServer", 512 },
    { "NoWindowWithSpecifiedIDExists", 513 },
    { "StandardColormapIsNotInitialized", 514 },
    { "UnableToConnectToRemoteDisplay", 515 },
    { "UnableToCreateBitmap", 516 },
    { "UnableToCreateColormap", 517 },
    { "UnableToCreatePixmap", 518 },
    { "UnableToCreateProperty", 519 },
    { "UnableToCreateStandardColormap", 520 },
    { "UnableToDisplayImageInfo", 521 },
    { "UnableToGetProperty", 522 },
    { "UnableToGetStandardColormap", 523 },
    { "UnableToGetVisual", 524 },
    { "UnableToGrabMouse", 525 },
    { "UnableToLoadFont", 526 },
    { "UnableToMatchVisualToStandardColormap", 527 },
    { "UnableToOpenXServer", 528 },
    { "UnableToReadXAttributes", 529 },
    { "UnableToReadXWindowImage", 530 },
    { "UnrecognizedColormapType", 531 },
    { "UnrecognizedGravityType", 532 },
    { "UnrecognizedVisualSpecifier", 533 },
    { "UnableToAllocateXHints", 534 },
    { "UnableToCreateCursor", 535 },
    { "UnableToCreateGraphicContext", 536 },
    { "UnableToCreateStandardColormap", 537 },
    { "UnableToCreateTextProperty", 538 },
    { "UnableToCreateXImage", 539 },
    { "UnableToCreateXPixmap", 540 },
    { "UnableToCreateXWindow", 541 },
    { "UnableToDisplayImage", 542 },
    { "UnableToDitherImage", 543 },
    { "UnableToGetPixelInfo", 544 },
    { "UnableToGetVisual", 545 },
    { "UnableToLoadFont", 546 },
    { "UnableToMakeXWindow", 547 },
    { "UnableToOpenXServer", 548 },
    { "UnableToViewFonts", 549 },
    { "UnableToGetVisual", 550 },
    { "UsingDefaultVisual", 551 },
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
    "text value does not convert to float",
    "text value does not convert to integer",
    "invalid primitive argument",
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

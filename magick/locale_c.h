#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 568

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
#define MGK_CacheErrorPixelCacheDimensionsMisMatch 12
#define MGK_CacheErrorPixelCacheIsNotOpen 13
#define MGK_CacheErrorUnableToAllocateCacheView 14
#define MGK_CacheErrorUnableToCloneCache 15
#define MGK_CacheErrorUnableToExtendCache 16
#define MGK_CacheErrorUnableToGetCacheNexus 17
#define MGK_CacheErrorUnableToGetPixelsFromCache 18
#define MGK_CacheErrorUnableToOpenCache 19
#define MGK_CacheErrorUnableToPeristPixelCache 20
#define MGK_CacheErrorUnableToReadPixelCache 21
#define MGK_CacheErrorUnableToSyncCache 22
#define MGK_CacheFatalErrorDiskAllocationFailed 23
#define MGK_CacheFatalErrorUnableToExtendPixelCache 24
#define MGK_CacheWarningDefault 25
#define MGK_CoderErrorArithmeticOverflow 26
#define MGK_CoderErrorColormapTooLarge 27
#define MGK_CoderErrorColormapTypeNotSupported 28
#define MGK_CoderErrorColorspaceModelIsNotSupported 29
#define MGK_CoderErrorColorTypeNotSupported 30
#define MGK_CoderErrorCompressionNotValid 31
#define MGK_CoderErrorDataEncodingSchemeIsNotSupported 32
#define MGK_CoderErrorDataStorageTypeIsNotSupported 33
#define MGK_CoderErrorDeltaPNGNotSupported 34
#define MGK_CoderErrorDivisionByZero 35
#define MGK_CoderErrorEncryptedWPGImageFileNotSupported 36
#define MGK_CoderErrorFractalCompressionNotSupported 37
#define MGK_CoderErrorImageColumnOrRowSizeIsNotSupported 38
#define MGK_CoderErrorImageDoesNotHaveAMatteChannel 39
#define MGK_CoderErrorImageIsNotTiled 40
#define MGK_CoderErrorImageTypeNotSupported 41
#define MGK_CoderErrorIncompatibleSizeOfDouble 42
#define MGK_CoderErrorIrregularChannelGeometryNotSupported 43
#define MGK_CoderErrorJNGCompressionNotSupported 44
#define MGK_CoderErrorJPEGCompressionNotSupported 45
#define MGK_CoderErrorJPEGEmbeddingFailed 46
#define MGK_CoderErrorLocationTypeIsNotSupported 47
#define MGK_CoderErrorMapStorageTypeIsNotSupported 48
#define MGK_CoderErrorMSBByteOrderNotSupported 49
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 50
#define MGK_CoderErrorMultipleRecordListNotSupported 51
#define MGK_CoderErrorNo8BIMDataIsAvailable 52
#define MGK_CoderErrorNoAPP1DataIsAvailable 53
#define MGK_CoderErrorNoBitmapOnClipboard 54
#define MGK_CoderErrorNoColorProfileAvailable 55
#define MGK_CoderErrorNoDataReturned 56
#define MGK_CoderErrorNoImageVectorGraphics 57
#define MGK_CoderErrorNoIPTCInfoWasFound 58
#define MGK_CoderErrorNoIPTCProfileAvailable 59
#define MGK_CoderErrorNumberOfImagesIsNotSupported 60
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 61
#define MGK_CoderErrorOnlyLevelZerofilesSupported 62
#define MGK_CoderErrorPNGCompressionNotSupported 63
#define MGK_CoderErrorPNGLibraryTooOld 64
#define MGK_CoderErrorRLECompressionNotSupported 65
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 66
#define MGK_CoderErrorUnableToCopyProfile 67
#define MGK_CoderErrorUnableToCreateADC 68
#define MGK_CoderErrorUnableToCreateBitmap 69
#define MGK_CoderErrorUnableToDecompressImage 70
#define MGK_CoderErrorUnableToInitializeFPXLibrary 71
#define MGK_CoderErrorUnableToOpenBlob 72
#define MGK_CoderErrorUnableToReadAspectRatio 73
#define MGK_CoderErrorUnableToReadCIELABImages 74
#define MGK_CoderErrorUnableToReadSummaryInfo 75
#define MGK_CoderErrorUnableToSetAffineMatrix 76
#define MGK_CoderErrorUnableToSetAspectRatio 77
#define MGK_CoderErrorUnableToSetColorTwist 78
#define MGK_CoderErrorUnableToSetContrast 79
#define MGK_CoderErrorUnableToSetFilteringValue 80
#define MGK_CoderErrorUnableToSetImageComments 81
#define MGK_CoderErrorUnableToSetImageTitle 82
#define MGK_CoderErrorUnableToSetJPEGLevel 83
#define MGK_CoderErrorUnableToSetRegionOfInterest 84
#define MGK_CoderErrorUnableToSetSummaryInfo 85
#define MGK_CoderErrorUnableToTranslateText 86
#define MGK_CoderErrorUnableToWriteMPEGParameters 87
#define MGK_CoderErrorUnableToWriteTemporaryFile 88
#define MGK_CoderErrorUnableToZipCompressImage 89
#define MGK_CoderErrorUnsupportedBitsPerSample 90
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 91
#define MGK_CoderErrorWebPDecodingFailedUserAbort 92
#define MGK_CoderErrorWebPEncodingFailed 93
#define MGK_CoderErrorWebPEncodingFailedBadDimension 94
#define MGK_CoderErrorWebPEncodingFailedBadWrite 95
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 96
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 97
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 98
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 99
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 100
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 101
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 102
#define MGK_CoderErrorWebPEncodingFailedUserAbort 103
#define MGK_CoderErrorWebPInvalidConfiguration 104
#define MGK_CoderErrorWebPInvalidParameter 105
#define MGK_CoderErrorZipCompressionNotSupported 106
#define MGK_CoderFatalErrorDefault 107
#define MGK_CoderWarningLosslessToLossyJPEGConversion 108
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 109
#define MGK_ConfigureErrorRegistryKeyLookupFailed 110
#define MGK_ConfigureErrorStringTokenLengthExceeded 111
#define MGK_ConfigureErrorUnableToAccessConfigureFile 112
#define MGK_ConfigureErrorUnableToAccessFontFile 113
#define MGK_ConfigureErrorUnableToAccessLogFile 114
#define MGK_ConfigureErrorUnableToAccessModuleFile 115
#define MGK_ConfigureFatalErrorDefault 116
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 117
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 118
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 119
#define MGK_ConfigureWarningDefault 120
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 121
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 122
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 123
#define MGK_CorruptImageErrorCompressionNotValid 124
#define MGK_CorruptImageErrorCorruptImage 125
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 126
#define MGK_CorruptImageErrorImageFileHasNoScenes 127
#define MGK_CorruptImageErrorImageTypeNotSupported 128
#define MGK_CorruptImageErrorImproperImageHeader 129
#define MGK_CorruptImageErrorInsufficientImageDataInFile 130
#define MGK_CorruptImageErrorInvalidColormapIndex 131
#define MGK_CorruptImageErrorInvalidFileFormatVersion 132
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 133
#define MGK_CorruptImageErrorMissingImageChannel 134
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 135
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 136
#define MGK_CorruptImageErrorNotEnoughTiles 137
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 138
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 139
#define MGK_CorruptImageErrorTooMuchImageDataInFile 140
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 141
#define MGK_CorruptImageErrorUnableToReadColorProfile 142
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 143
#define MGK_CorruptImageErrorUnableToReadGenericProfile 144
#define MGK_CorruptImageErrorUnableToReadImageData 145
#define MGK_CorruptImageErrorUnableToReadImageHeader 146
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 147
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 148
#define MGK_CorruptImageErrorUnableToReadSubImageData 149
#define MGK_CorruptImageErrorUnableToReadVIDImage 150
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 151
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 152
#define MGK_CorruptImageErrorUnableToUncompressImage 153
#define MGK_CorruptImageErrorUnexpectedEndOfFile 154
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 155
#define MGK_CorruptImageErrorUnknownPatternType 156
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 157
#define MGK_CorruptImageErrorUnrecognizedImageCompression 158
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 159
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 160
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 161
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 162
#define MGK_CorruptImageFatalErrorUnableToPersistKey 163
#define MGK_CorruptImageWarningCompressionNotValid 164
#define MGK_CorruptImageWarningCorruptImage 165
#define MGK_CorruptImageWarningImproperImageHeader 166
#define MGK_CorruptImageWarningInvalidColormapIndex 167
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 168
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 169
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 170
#define MGK_CorruptImageWarningSkipToSyncByte 171
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 172
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 173
#define MGK_CorruptImageWarningUnrecognizedImageCompression 174
#define MGK_DelegateErrorDelegateFailed 175
#define MGK_DelegateErrorFailedToAllocateArgumentList 176
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 177
#define MGK_DelegateErrorFailedToComputeOutputSize 178
#define MGK_DelegateErrorFailedToFindGhostscript 179
#define MGK_DelegateErrorFailedToRenderFile 180
#define MGK_DelegateErrorFailedToScanFile 181
#define MGK_DelegateErrorNoTagFound 182
#define MGK_DelegateErrorPostscriptDelegateFailed 183
#define MGK_DelegateErrorUnableToCreateImage 184
#define MGK_DelegateErrorUnableToCreateImageComponent 185
#define MGK_DelegateErrorUnableToDecodeImageFile 186
#define MGK_DelegateErrorUnableToEncodeImageFile 187
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 188
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 189
#define MGK_DelegateErrorUnableToManageJP2Stream 190
#define MGK_DelegateErrorUnableToWriteSVGFormat 191
#define MGK_DelegateErrorWebPABIMismatch 192
#define MGK_DelegateFatalErrorDefault 193
#define MGK_DelegateWarningDefault 194
#define MGK_DrawErrorAlreadyPushingPatternDefinition 195
#define MGK_DrawErrorDrawingRecursionDetected 196
#define MGK_DrawErrorFloatValueConversionError 197
#define MGK_DrawErrorIntegerValueConversionError 198
#define MGK_DrawErrorInvalidPrimitiveArgument 199
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 200
#define MGK_DrawErrorPrimitiveArithmeticOverflow 201
#define MGK_DrawErrorTooManyCoordinates 202
#define MGK_DrawErrorUnableToPrint 203
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 204
#define MGK_DrawErrorUnreasonableGradientSize 205
#define MGK_DrawErrorVectorPathTruncated 206
#define MGK_DrawFatalErrorDefault 207
#define MGK_DrawWarningNotARelativeURL 208
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 209
#define MGK_DrawWarningURLNotFound 210
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 211
#define MGK_FileOpenErrorUnableToOpenFile 212
#define MGK_FileOpenErrorUnableToWriteFile 213
#define MGK_FileOpenFatalErrorDefault 214
#define MGK_FileOpenWarningDefault 215
#define MGK_ImageErrorAngleIsDiscontinuous 216
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 217
#define MGK_ImageErrorColorspaceColorProfileMismatch 218
#define MGK_ImageErrorImageColorspaceDiffers 219
#define MGK_ImageErrorImageColorspaceMismatch 220
#define MGK_ImageErrorImageDifferenceExceedsLimit 221
#define MGK_ImageErrorImageDoesNotContainResolution 222
#define MGK_ImageErrorImageIsNotColormapped 223
#define MGK_ImageErrorImageOpacityDiffers 224
#define MGK_ImageErrorImageSequenceIsRequired 225
#define MGK_ImageErrorImageSizeDiffers 226
#define MGK_ImageErrorInvalidColormapIndex 227
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 228
#define MGK_ImageErrorNoImagesWereFound 229
#define MGK_ImageErrorNoImagesWereLoaded 230
#define MGK_ImageErrorNoLocaleImageAttribute 231
#define MGK_ImageErrorTooManyClusters 232
#define MGK_ImageErrorUnableToAppendImage 233
#define MGK_ImageErrorUnableToAssignProfile 234
#define MGK_ImageErrorUnableToAverageImage 235
#define MGK_ImageErrorUnableToCoalesceImage 236
#define MGK_ImageErrorUnableToCompareImages 237
#define MGK_ImageErrorUnableToCreateImageMosaic 238
#define MGK_ImageErrorUnableToCreateStereoImage 239
#define MGK_ImageErrorUnableToDeconstructImageSequence 240
#define MGK_ImageErrorUnableToExportImagePixels 241
#define MGK_ImageErrorUnableToFlattenImage 242
#define MGK_ImageErrorUnableToGetClipMask 243
#define MGK_ImageErrorUnableToHandleImageChannel 244
#define MGK_ImageErrorUnableToImportImagePixels 245
#define MGK_ImageErrorUnableToResizeImage 246
#define MGK_ImageErrorUnableToSegmentImage 247
#define MGK_ImageErrorUnableToSetClipMask 248
#define MGK_ImageErrorUnableToShearImage 249
#define MGK_ImageErrorWidthOrHeightExceedsLimit 250
#define MGK_ImageFatalErrorUnableToPersistKey 251
#define MGK_ImageWarningDefault 252
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 253
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 254
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 255
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 256
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 257
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 258
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 259
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 260
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 261
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 262
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 263
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 264
#define MGK_MissingDelegateFatalErrorDefault 265
#define MGK_MissingDelegateWarningDefault 266
#define MGK_ModuleErrorFailedToCloseModule 267
#define MGK_ModuleErrorFailedToFindSymbol 268
#define MGK_ModuleErrorUnableToLoadModule 269
#define MGK_ModuleErrorUnableToRegisterImageFormat 270
#define MGK_ModuleErrorUnrecognizedModule 271
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 272
#define MGK_ModuleWarningDefault 273
#define MGK_MonitorErrorDefault 274
#define MGK_MonitorFatalErrorDefault 275
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 276
#define MGK_MonitorWarningDefault 277
#define MGK_OptionErrorBevelWidthIsNegative 278
#define MGK_OptionErrorColorSeparatedImageRequired 279
#define MGK_OptionErrorFrameIsLessThanImageSize 280
#define MGK_OptionErrorGeometryDimensionsAreZero 281
#define MGK_OptionErrorGeometryDoesNotContainImage 282
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 283
#define MGK_OptionErrorImagesAreNotTheSameSize 284
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 285
#define MGK_OptionErrorImageSmallerThanKernelWidth 286
#define MGK_OptionErrorImageSmallerThanRadius 287
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 288
#define MGK_OptionErrorInputImagesAlreadySpecified 289
#define MGK_OptionErrorInvalidSubimageSpecification 290
#define MGK_OptionErrorKernelRadiusIsTooSmall 291
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 292
#define MGK_OptionErrorMatrixIsNotSquare 293
#define MGK_OptionErrorMatrixOrderOutOfRange 294
#define MGK_OptionErrorMissingAnImageFilename 295
#define MGK_OptionErrorMissingArgument 296
#define MGK_OptionErrorMustSpecifyAnImageName 297
#define MGK_OptionErrorMustSpecifyImageSize 298
#define MGK_OptionErrorNoBlobDefined 299
#define MGK_OptionErrorNoImagesDefined 300
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 301
#define MGK_OptionErrorNoProfileNameWasGiven 302
#define MGK_OptionErrorNullBlobArgument 303
#define MGK_OptionErrorReferenceImageRequired 304
#define MGK_OptionErrorReferenceIsNotMyType 305
#define MGK_OptionErrorRegionAreaExceedsLimit 306
#define MGK_OptionErrorRequestDidNotReturnAnImage 307
#define MGK_OptionErrorSteganoImageRequired 308
#define MGK_OptionErrorStereoImageRequired 309
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 310
#define MGK_OptionErrorTileNotBoundedByImageDimensions 311
#define MGK_OptionErrorUnableToAddOrRemoveProfile 312
#define MGK_OptionErrorUnableToAverageImageSequence 313
#define MGK_OptionErrorUnableToBlurImage 314
#define MGK_OptionErrorUnableToChopImage 315
#define MGK_OptionErrorUnableToColorMatrixImage 316
#define MGK_OptionErrorUnableToConstituteImage 317
#define MGK_OptionErrorUnableToConvolveImage 318
#define MGK_OptionErrorUnableToEdgeImage 319
#define MGK_OptionErrorUnableToEqualizeImage 320
#define MGK_OptionErrorUnableToFilterImage 321
#define MGK_OptionErrorUnableToFormatImageMetadata 322
#define MGK_OptionErrorUnableToFrameImage 323
#define MGK_OptionErrorUnableToOilPaintImage 324
#define MGK_OptionErrorUnableToPaintImage 325
#define MGK_OptionErrorUnableToRaiseImage 326
#define MGK_OptionErrorUnableToSharpenImage 327
#define MGK_OptionErrorUnableToThresholdImage 328
#define MGK_OptionErrorUnableToWaveImage 329
#define MGK_OptionErrorUnrecognizedAttribute 330
#define MGK_OptionErrorUnrecognizedChannelType 331
#define MGK_OptionErrorUnrecognizedColor 332
#define MGK_OptionErrorUnrecognizedColormapType 333
#define MGK_OptionErrorUnrecognizedColorspace 334
#define MGK_OptionErrorUnrecognizedCommand 335
#define MGK_OptionErrorUnrecognizedComposeOperator 336
#define MGK_OptionErrorUnrecognizedDisposeMethod 337
#define MGK_OptionErrorUnrecognizedElement 338
#define MGK_OptionErrorUnrecognizedEndianType 339
#define MGK_OptionErrorUnrecognizedGravityType 340
#define MGK_OptionErrorUnrecognizedHighlightStyle 341
#define MGK_OptionErrorUnrecognizedImageCompression 342
#define MGK_OptionErrorUnrecognizedImageFilter 343
#define MGK_OptionErrorUnrecognizedImageFormat 344
#define MGK_OptionErrorUnrecognizedImageMode 345
#define MGK_OptionErrorUnrecognizedImageType 346
#define MGK_OptionErrorUnrecognizedIntentType 347
#define MGK_OptionErrorUnrecognizedInterlaceType 348
#define MGK_OptionErrorUnrecognizedListType 349
#define MGK_OptionErrorUnrecognizedMetric 350
#define MGK_OptionErrorUnrecognizedModeType 351
#define MGK_OptionErrorUnrecognizedNoiseType 352
#define MGK_OptionErrorUnrecognizedOperator 353
#define MGK_OptionErrorUnrecognizedOption 354
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 355
#define MGK_OptionErrorUnrecognizedPixelMap 356
#define MGK_OptionErrorUnrecognizedPreviewType 357
#define MGK_OptionErrorUnrecognizedResourceType 358
#define MGK_OptionErrorUnrecognizedType 359
#define MGK_OptionErrorUnrecognizedUnitsType 360
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 361
#define MGK_OptionErrorUnsupportedSamplingFactor 362
#define MGK_OptionErrorUsageError 363
#define MGK_OptionFatalErrorInvalidColorspaceType 364
#define MGK_OptionFatalErrorInvalidEndianType 365
#define MGK_OptionFatalErrorInvalidImageType 366
#define MGK_OptionFatalErrorInvalidInterlaceType 367
#define MGK_OptionFatalErrorMissingAnImageFilename 368
#define MGK_OptionFatalErrorMissingArgument 369
#define MGK_OptionFatalErrorNoImagesWereLoaded 370
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 371
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 372
#define MGK_OptionFatalErrorUnableToOpenXServer 373
#define MGK_OptionFatalErrorUnableToPersistKey 374
#define MGK_OptionFatalErrorUnrecognizedColormapType 375
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 376
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 377
#define MGK_OptionFatalErrorUnrecognizedEndianType 378
#define MGK_OptionFatalErrorUnrecognizedFilterType 379
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 380
#define MGK_OptionFatalErrorUnrecognizedImageType 381
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 382
#define MGK_OptionFatalErrorUnrecognizedOption 383
#define MGK_OptionFatalErrorUnrecognizedResourceType 384
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 385
#define MGK_OptionWarningUnrecognizedColor 386
#define MGK_RegistryErrorImageExpected 387
#define MGK_RegistryErrorImageInfoExpected 388
#define MGK_RegistryErrorStructureSizeMismatch 389
#define MGK_RegistryErrorUnableToGetRegistryID 390
#define MGK_RegistryErrorUnableToLocateImage 391
#define MGK_RegistryErrorUnableToSetRegistry 392
#define MGK_RegistryFatalErrorDefault 393
#define MGK_RegistryWarningDefault 394
#define MGK_ResourceLimitErrorCacheResourcesExhausted 395
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 396
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 397
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 398
#define MGK_ResourceLimitErrorMemoryAllocationFailed 399
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 400
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 401
#define MGK_ResourceLimitErrorUnableToAddColorProfile 402
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 403
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 404
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 405
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 406
#define MGK_ResourceLimitErrorUnableToAllocateColormap 407
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 408
#define MGK_ResourceLimitErrorUnableToAllocateImage 409
#define MGK_ResourceLimitErrorUnableToAllocateString 410
#define MGK_ResourceLimitErrorUnableToAnnotateImage 411
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 412
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 413
#define MGK_ResourceLimitErrorUnableToCloneImage 414
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 415
#define MGK_ResourceLimitErrorUnableToConstituteImage 416
#define MGK_ResourceLimitErrorUnableToConvertFont 417
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 418
#define MGK_ResourceLimitErrorUnableToCreateColormap 419
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 420
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 421
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 422
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 423
#define MGK_ResourceLimitErrorUnableToCreateXWindow 424
#define MGK_ResourceLimitErrorUnableToCropImage 425
#define MGK_ResourceLimitErrorUnableToDespeckleImage 426
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 427
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 428
#define MGK_ResourceLimitErrorUnableToDitherImage 429
#define MGK_ResourceLimitErrorUnableToDrawOnImage 430
#define MGK_ResourceLimitErrorUnableToEdgeImage 431
#define MGK_ResourceLimitErrorUnableToEmbossImage 432
#define MGK_ResourceLimitErrorUnableToEnhanceImage 433
#define MGK_ResourceLimitErrorUnableToFloodfillImage 434
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 435
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 436
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 437
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 438
#define MGK_ResourceLimitErrorUnableToLevelImage 439
#define MGK_ResourceLimitErrorUnableToMagnifyImage 440
#define MGK_ResourceLimitErrorUnableToManageColor 441
#define MGK_ResourceLimitErrorUnableToMapImage 442
#define MGK_ResourceLimitErrorUnableToMapImageSequence 443
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 444
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 445
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 446
#define MGK_ResourceLimitErrorUnableToNormalizeImage 447
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 448
#define MGK_ResourceLimitErrorUnableToQuantizeImage 449
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 450
#define MGK_ResourceLimitErrorUnableToReadTextChunk 451
#define MGK_ResourceLimitErrorUnableToReadXImage 452
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 453
#define MGK_ResourceLimitErrorUnableToResizeImage 454
#define MGK_ResourceLimitErrorUnableToRotateImage 455
#define MGK_ResourceLimitErrorUnableToSampleImage 456
#define MGK_ResourceLimitErrorUnableToScaleImage 457
#define MGK_ResourceLimitErrorUnableToSelectImage 458
#define MGK_ResourceLimitErrorUnableToSharpenImage 459
#define MGK_ResourceLimitErrorUnableToShaveImage 460
#define MGK_ResourceLimitErrorUnableToShearImage 461
#define MGK_ResourceLimitErrorUnableToSortImageColormap 462
#define MGK_ResourceLimitErrorUnableToThresholdImage 463
#define MGK_ResourceLimitErrorUnableToTransformColorspace 464
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 465
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 466
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 467
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 475
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 477
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 478
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 479
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 480
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 481
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 490
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 491
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 492
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 493
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 494
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 495
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 496
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 497
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 498
#define MGK_ResourceLimitFatalErrorUnableToConvertText 499
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 500
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 501
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 502
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 503
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 504
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 505
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 506
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 507
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 508
#define MGK_ResourceLimitWarningMemoryAllocationFailed 509
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 510
#define MGK_StreamErrorNoStreamHandlerIsDefined 511
#define MGK_StreamErrorPixelCacheIsNotOpen 512
#define MGK_StreamErrorUnableToAcquirePixelStream 513
#define MGK_StreamErrorUnableToSetPixelStream 514
#define MGK_StreamErrorUnableToSyncPixelStream 515
#define MGK_StreamFatalErrorDefault 516
#define MGK_StreamWarningDefault 517
#define MGK_TypeErrorFontSubstitutionRequired 518
#define MGK_TypeErrorUnableToGetTypeMetrics 519
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 520
#define MGK_TypeErrorUnableToReadFont 521
#define MGK_TypeErrorUnrecognizedFontEncoding 522
#define MGK_TypeFatalErrorDefault 523
#define MGK_TypeWarningDefault 524
#define MGK_WandErrorInvalidColormapIndex 525
#define MGK_WandErrorWandAPINotImplemented 526
#define MGK_WandErrorWandContainsNoImageIndexs 527
#define MGK_WandErrorWandContainsNoImages 528
#define MGK_XServerErrorColorIsNotKnownToServer 529
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 530
#define MGK_XServerErrorStandardColormapIsNotInitialized 531
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 532
#define MGK_XServerErrorUnableToCreateBitmap 533
#define MGK_XServerErrorUnableToCreateColormap 534
#define MGK_XServerErrorUnableToCreatePixmap 535
#define MGK_XServerErrorUnableToCreateProperty 536
#define MGK_XServerErrorUnableToCreateStandardColormap 537
#define MGK_XServerErrorUnableToDisplayImageInfo 538
#define MGK_XServerErrorUnableToGetProperty 539
#define MGK_XServerErrorUnableToGetStandardColormap 540
#define MGK_XServerErrorUnableToGetVisual 541
#define MGK_XServerErrorUnableToGrabMouse 542
#define MGK_XServerErrorUnableToLoadFont 543
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 544
#define MGK_XServerErrorUnableToOpenXServer 545
#define MGK_XServerErrorUnableToReadXAttributes 546
#define MGK_XServerErrorUnableToReadXWindowImage 547
#define MGK_XServerErrorUnrecognizedColormapType 548
#define MGK_XServerErrorUnrecognizedGravityType 549
#define MGK_XServerErrorUnrecognizedVisualSpecifier 550
#define MGK_XServerFatalErrorUnableToAllocateXHints 551
#define MGK_XServerFatalErrorUnableToCreateCursor 552
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 553
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 554
#define MGK_XServerFatalErrorUnableToCreateTextProperty 555
#define MGK_XServerFatalErrorUnableToCreateXImage 556
#define MGK_XServerFatalErrorUnableToCreateXPixmap 557
#define MGK_XServerFatalErrorUnableToCreateXWindow 558
#define MGK_XServerFatalErrorUnableToDisplayImage 559
#define MGK_XServerFatalErrorUnableToDitherImage 560
#define MGK_XServerFatalErrorUnableToGetPixelInfo 561
#define MGK_XServerFatalErrorUnableToGetVisual 562
#define MGK_XServerFatalErrorUnableToLoadFont 563
#define MGK_XServerFatalErrorUnableToMakeXWindow 564
#define MGK_XServerFatalErrorUnableToOpenXServer 565
#define MGK_XServerFatalErrorUnableToViewFonts 566
#define MGK_XServerWarningUnableToGetVisual 567
#define MGK_XServerWarningUsingDefaultVisual 568

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
    { "Cache/FatalError", 22, CacheFatalError },
    { "Cache/Warning", 24, CacheWarning },
    { "Coder/Error", 25, CoderError },
    { "Coder/FatalError", 106, CoderFatalError },
    { "Coder/Warning", 107, CoderWarning },
    { "Configure/Error", 108, ConfigureError },
    { "Configure/FatalError", 115, ConfigureFatalError },
    { "Configure/Warning", 119, ConfigureWarning },
    { "Corrupt/Image/Error", 120, CorruptImageError },
    { "Corrupt/Image/FatalError", 162, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 163, CorruptImageWarning },
    { "Delegate/Error", 174, DelegateError },
    { "Delegate/FatalError", 192, DelegateFatalError },
    { "Delegate/Warning", 193, DelegateWarning },
    { "Draw/Error", 194, DrawError },
    { "Draw/FatalError", 206, DrawFatalError },
    { "Draw/Warning", 207, DrawWarning },
    { "File/Open/Error", 210, FileOpenError },
    { "File/Open/FatalError", 213, FileOpenFatalError },
    { "File/Open/Warning", 214, FileOpenWarning },
    { "Image/Error", 215, ImageError },
    { "Image/FatalError", 250, ImageFatalError },
    { "Image/Warning", 251, ImageWarning },
    { "Missing/Delegate/Error", 252, MissingDelegateError },
    { "Missing/Delegate/FatalError", 264, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 265, MissingDelegateWarning },
    { "Module/Error", 266, ModuleError },
    { "Module/FatalError", 271, ModuleFatalError },
    { "Module/Warning", 272, ModuleWarning },
    { "Monitor/Error", 273, MonitorError },
    { "Monitor/FatalError", 274, MonitorFatalError },
    { "Monitor/Warning", 276, MonitorWarning },
    { "Option/Error", 277, OptionError },
    { "Option/FatalError", 363, OptionFatalError },
    { "Option/Warning", 385, OptionWarning },
    { "Registry/Error", 386, RegistryError },
    { "Registry/FatalError", 392, RegistryFatalError },
    { "Registry/Warning", 393, RegistryWarning },
    { "Resource/Limit/Error", 394, ResourceLimitError },
    { "Resource/Limit/FatalError", 464, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 508, ResourceLimitWarning },
    { "Stream/Error", 509, StreamError },
    { "Stream/FatalError", 515, StreamFatalError },
    { "Stream/Warning", 516, StreamWarning },
    { "Type/Error", 517, TypeError },
    { "Type/FatalError", 522, TypeFatalError },
    { "Type/Warning", 523, TypeWarning },
    { "Wand/Error", 524, WandError },
    { "XServer/Error", 528, XServerError },
    { "XServer/FatalError", 550, XServerFatalError },
    { "XServer/Warning", 566, XServerWarning },
    { 0, 568, UndefinedException }
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
    { "PixelCacheDimensionsMisMatch", 12 },
    { "PixelCacheIsNotOpen", 13 },
    { "UnableToAllocateCacheView", 14 },
    { "UnableToCloneCache", 15 },
    { "UnableToExtendCache", 16 },
    { "UnableToGetCacheNexus", 17 },
    { "UnableToGetPixelsFromCache", 18 },
    { "UnableToOpenCache", 19 },
    { "UnableToPeristPixelCache", 20 },
    { "UnableToReadPixelCache", 21 },
    { "UnableToSyncCache", 22 },
    { "DiskAllocationFailed", 23 },
    { "UnableToExtendPixelCache", 24 },
    { "Default", 25 },
    { "ArithmeticOverflow", 26 },
    { "ColormapTooLarge", 27 },
    { "ColormapTypeNotSupported", 28 },
    { "ColorspaceModelIsNotSupported", 29 },
    { "ColorTypeNotSupported", 30 },
    { "CompressionNotValid", 31 },
    { "DataEncodingSchemeIsNotSupported", 32 },
    { "DataStorageTypeIsNotSupported", 33 },
    { "DeltaPNGNotSupported", 34 },
    { "DivisionByZero", 35 },
    { "EncryptedWPGImageFileNotSupported", 36 },
    { "FractalCompressionNotSupported", 37 },
    { "ImageColumnOrRowSizeIsNotSupported", 38 },
    { "ImageDoesNotHaveAMatteChannel", 39 },
    { "ImageIsNotTiled", 40 },
    { "ImageTypeNotSupported", 41 },
    { "IncompatibleSizeOfDouble", 42 },
    { "IrregularChannelGeometryNotSupported", 43 },
    { "JNGCompressionNotSupported", 44 },
    { "JPEGCompressionNotSupported", 45 },
    { "JPEGEmbeddingFailed", 46 },
    { "LocationTypeIsNotSupported", 47 },
    { "MapStorageTypeIsNotSupported", 48 },
    { "MSBByteOrderNotSupported", 49 },
    { "MultidimensionalMatricesAreNotSupported", 50 },
    { "MultipleRecordListNotSupported", 51 },
    { "No8BIMDataIsAvailable", 52 },
    { "NoAPP1DataIsAvailable", 53 },
    { "NoBitmapOnClipboard", 54 },
    { "NoColorProfileAvailable", 55 },
    { "NoDataReturned", 56 },
    { "NoImageVectorGraphics", 57 },
    { "NoIPTCInfoWasFound", 58 },
    { "NoIPTCProfileAvailable", 59 },
    { "NumberOfImagesIsNotSupported", 60 },
    { "OnlyContinuousTonePictureSupported", 61 },
    { "OnlyLevelZerofilesSupported", 62 },
    { "PNGCompressionNotSupported", 63 },
    { "PNGLibraryTooOld", 64 },
    { "RLECompressionNotSupported", 65 },
    { "SubsamplingRequiresEvenWidth", 66 },
    { "UnableToCopyProfile", 67 },
    { "UnableToCreateADC", 68 },
    { "UnableToCreateBitmap", 69 },
    { "UnableToDecompressImage", 70 },
    { "UnableToInitializeFPXLibrary", 71 },
    { "UnableToOpenBlob", 72 },
    { "UnableToReadAspectRatio", 73 },
    { "UnableToReadCIELABImages", 74 },
    { "UnableToReadSummaryInfo", 75 },
    { "UnableToSetAffineMatrix", 76 },
    { "UnableToSetAspectRatio", 77 },
    { "UnableToSetColorTwist", 78 },
    { "UnableToSetContrast", 79 },
    { "UnableToSetFilteringValue", 80 },
    { "UnableToSetImageComments", 81 },
    { "UnableToSetImageTitle", 82 },
    { "UnableToSetJPEGLevel", 83 },
    { "UnableToSetRegionOfInterest", 84 },
    { "UnableToSetSummaryInfo", 85 },
    { "UnableToTranslateText", 86 },
    { "UnableToWriteMPEGParameters", 87 },
    { "UnableToWriteTemporaryFile", 88 },
    { "UnableToZipCompressImage", 89 },
    { "UnsupportedBitsPerSample", 90 },
    { "UnsupportedCellTypeInTheMatrix", 91 },
    { "WebPDecodingFailedUserAbort", 92 },
    { "WebPEncodingFailed", 93 },
    { "WebPEncodingFailedBadDimension", 94 },
    { "WebPEncodingFailedBadWrite", 95 },
    { "WebPEncodingFailedBitstreamOutOfMemory", 96 },
    { "WebPEncodingFailedFileTooBig", 97 },
    { "WebPEncodingFailedInvalidConfiguration", 98 },
    { "WebPEncodingFailedNULLParameter", 99 },
    { "WebPEncodingFailedOutOfMemory", 100 },
    { "WebPEncodingFailedPartition0Overflow", 101 },
    { "WebPEncodingFailedPartitionOverflow", 102 },
    { "WebPEncodingFailedUserAbort", 103 },
    { "WebPInvalidConfiguration", 104 },
    { "WebPInvalidParameter", 105 },
    { "ZipCompressionNotSupported", 106 },
    { "Default", 107 },
    { "LosslessToLossyJPEGConversion", 108 },
    { "IncludeElementNestedTooDeeply", 109 },
    { "RegistryKeyLookupFailed", 110 },
    { "StringTokenLengthExceeded", 111 },
    { "UnableToAccessConfigureFile", 112 },
    { "UnableToAccessFontFile", 113 },
    { "UnableToAccessLogFile", 114 },
    { "UnableToAccessModuleFile", 115 },
    { "Default", 116 },
    { "UnableToChangeToWorkingDirectory", 117 },
    { "UnableToGetCurrentDirectory", 118 },
    { "UnableToRestoreCurrentDirectory", 119 },
    { "Default", 120 },
    { "AnErrorHasOccurredReadingFromFile", 121 },
    { "AnErrorHasOccurredWritingToFile", 122 },
    { "ColormapExceedsColorsLimit", 123 },
    { "CompressionNotValid", 124 },
    { "CorruptImage", 125 },
    { "ImageFileDoesNotContainAnyImageData", 126 },
    { "ImageFileHasNoScenes", 127 },
    { "ImageTypeNotSupported", 128 },
    { "ImproperImageHeader", 129 },
    { "InsufficientImageDataInFile", 130 },
    { "InvalidColormapIndex", 131 },
    { "InvalidFileFormatVersion", 132 },
    { "LengthAndFilesizeDoNotMatch", 133 },
    { "MissingImageChannel", 134 },
    { "NegativeOrZeroImageSize", 135 },
    { "NonOS2HeaderSizeError", 136 },
    { "NotEnoughTiles", 137 },
    { "StaticPlanesValueNotEqualToOne", 138 },
    { "SubsamplingRequiresEvenWidth", 139 },
    { "TooMuchImageDataInFile", 140 },
    { "UnableToReadColormapFromDumpFile", 141 },
    { "UnableToReadColorProfile", 142 },
    { "UnableToReadExtensionBlock", 143 },
    { "UnableToReadGenericProfile", 144 },
    { "UnableToReadImageData", 145 },
    { "UnableToReadImageHeader", 146 },
    { "UnableToReadIPTCProfile", 147 },
    { "UnableToReadPixmapFromDumpFile", 148 },
    { "UnableToReadSubImageData", 149 },
    { "UnableToReadVIDImage", 150 },
    { "UnableToReadWindowNameFromDumpFile", 151 },
    { "UnableToRunlengthDecodeImage", 152 },
    { "UnableToUncompressImage", 153 },
    { "UnexpectedEndOfFile", 154 },
    { "UnexpectedSamplingFactor", 155 },
    { "UnknownPatternType", 156 },
    { "UnrecognizedBitsPerPixel", 157 },
    { "UnrecognizedImageCompression", 158 },
    { "UnrecognizedNumberOfColors", 159 },
    { "UnrecognizedXWDHeader", 160 },
    { "UnsupportedBitsPerSample", 161 },
    { "UnsupportedNumberOfPlanes", 162 },
    { "UnableToPersistKey", 163 },
    { "CompressionNotValid", 164 },
    { "CorruptImage", 165 },
    { "ImproperImageHeader", 166 },
    { "InvalidColormapIndex", 167 },
    { "LengthAndFilesizeDoNotMatch", 168 },
    { "NegativeOrZeroImageSize", 169 },
    { "NonOS2HeaderSizeError", 170 },
    { "SkipToSyncByte", 171 },
    { "StaticPlanesValueNotEqualToOne", 172 },
    { "UnrecognizedBitsPerPixel", 173 },
    { "UnrecognizedImageCompression", 174 },
    { "DelegateFailed", 175 },
    { "FailedToAllocateArgumentList", 176 },
    { "FailedToAllocateGhostscriptInterpreter", 177 },
    { "FailedToComputeOutputSize", 178 },
    { "FailedToFindGhostscript", 179 },
    { "FailedToRenderFile", 180 },
    { "FailedToScanFile", 181 },
    { "NoTagFound", 182 },
    { "PostscriptDelegateFailed", 183 },
    { "UnableToCreateImage", 184 },
    { "UnableToCreateImageComponent", 185 },
    { "UnableToDecodeImageFile", 186 },
    { "UnableToEncodeImageFile", 187 },
    { "UnableToInitializeFPXLibrary", 188 },
    { "UnableToInitializeWMFLibrary", 189 },
    { "UnableToManageJP2Stream", 190 },
    { "UnableToWriteSVGFormat", 191 },
    { "WebPABIMismatch", 192 },
    { "Default", 193 },
    { "Default", 194 },
    { "AlreadyPushingPatternDefinition", 195 },
    { "DrawingRecursionDetected", 196 },
    { "FloatValueConversionError", 197 },
    { "IntegerValueConversionError", 198 },
    { "InvalidPrimitiveArgument", 199 },
    { "NonconformingDrawingPrimitiveDefinition", 200 },
    { "PrimitiveArithmeticOverflow", 201 },
    { "TooManyCoordinates", 202 },
    { "UnableToPrint", 203 },
    { "UnbalancedGraphicContextPushPop", 204 },
    { "UnreasonableGradientSize", 205 },
    { "VectorPathTruncated", 206 },
    { "Default", 207 },
    { "NotARelativeURL", 208 },
    { "NotCurrentlyPushingPatternDefinition", 209 },
    { "URLNotFound", 210 },
    { "UnableToCreateTemporaryFile", 211 },
    { "UnableToOpenFile", 212 },
    { "UnableToWriteFile", 213 },
    { "Default", 214 },
    { "Default", 215 },
    { "AngleIsDiscontinuous", 216 },
    { "CMYKAImageLacksAlphaChannel", 217 },
    { "ColorspaceColorProfileMismatch", 218 },
    { "ImageColorspaceDiffers", 219 },
    { "ImageColorspaceMismatch", 220 },
    { "ImageDifferenceExceedsLimit", 221 },
    { "ImageDoesNotContainResolution", 222 },
    { "ImageIsNotColormapped", 223 },
    { "ImageOpacityDiffers", 224 },
    { "ImageSequenceIsRequired", 225 },
    { "ImageSizeDiffers", 226 },
    { "InvalidColormapIndex", 227 },
    { "LeftAndRightImageSizesDiffer", 228 },
    { "NoImagesWereFound", 229 },
    { "NoImagesWereLoaded", 230 },
    { "NoLocaleImageAttribute", 231 },
    { "TooManyClusters", 232 },
    { "UnableToAppendImage", 233 },
    { "UnableToAssignProfile", 234 },
    { "UnableToAverageImage", 235 },
    { "UnableToCoalesceImage", 236 },
    { "UnableToCompareImages", 237 },
    { "UnableToCreateImageMosaic", 238 },
    { "UnableToCreateStereoImage", 239 },
    { "UnableToDeconstructImageSequence", 240 },
    { "UnableToExportImagePixels", 241 },
    { "UnableToFlattenImage", 242 },
    { "UnableToGetClipMask", 243 },
    { "UnableToHandleImageChannel", 244 },
    { "UnableToImportImagePixels", 245 },
    { "UnableToResizeImage", 246 },
    { "UnableToSegmentImage", 247 },
    { "UnableToSetClipMask", 248 },
    { "UnableToShearImage", 249 },
    { "WidthOrHeightExceedsLimit", 250 },
    { "UnableToPersistKey", 251 },
    { "Default", 252 },
    { "DPSLibraryIsNotAvailable", 253 },
    { "FPXLibraryIsNotAvailable", 254 },
    { "FreeTypeLibraryIsNotAvailable", 255 },
    { "JPEGLibraryIsNotAvailable", 256 },
    { "LCMSLibraryIsNotAvailable", 257 },
    { "LZWEncodingNotEnabled", 258 },
    { "NoDecodeDelegateForThisImageFormat", 259 },
    { "NoEncodeDelegateForThisImageFormat", 260 },
    { "TIFFLibraryIsNotAvailable", 261 },
    { "XMLLibraryIsNotAvailable", 262 },
    { "XWindowLibraryIsNotAvailable", 263 },
    { "ZipLibraryIsNotAvailable", 264 },
    { "Default", 265 },
    { "Default", 266 },
    { "FailedToCloseModule", 267 },
    { "FailedToFindSymbol", 268 },
    { "UnableToLoadModule", 269 },
    { "UnableToRegisterImageFormat", 270 },
    { "UnrecognizedModule", 271 },
    { "UnableToInitializeModuleLoader", 272 },
    { "Default", 273 },
    { "Default", 274 },
    { "Default", 275 },
    { "UserRequestedTerminationBySignal", 276 },
    { "Default", 277 },
    { "BevelWidthIsNegative", 278 },
    { "ColorSeparatedImageRequired", 279 },
    { "FrameIsLessThanImageSize", 280 },
    { "GeometryDimensionsAreZero", 281 },
    { "GeometryDoesNotContainImage", 282 },
    { "HaldClutImageDimensionsInvalid", 283 },
    { "ImagesAreNotTheSameSize", 284 },
    { "ImageSizeMustExceedBevelWidth", 285 },
    { "ImageSmallerThanKernelWidth", 286 },
    { "ImageSmallerThanRadius", 287 },
    { "ImageWidthsOrHeightsDiffer", 288 },
    { "InputImagesAlreadySpecified", 289 },
    { "InvalidSubimageSpecification", 290 },
    { "KernelRadiusIsTooSmall", 291 },
    { "KernelWidthMustBeAnOddNumber", 292 },
    { "MatrixIsNotSquare", 293 },
    { "MatrixOrderOutOfRange", 294 },
    { "MissingAnImageFilename", 295 },
    { "MissingArgument", 296 },
    { "MustSpecifyAnImageName", 297 },
    { "MustSpecifyImageSize", 298 },
    { "NoBlobDefined", 299 },
    { "NoImagesDefined", 300 },
    { "NonzeroWidthAndHeightRequired", 301 },
    { "NoProfileNameWasGiven", 302 },
    { "NullBlobArgument", 303 },
    { "ReferenceImageRequired", 304 },
    { "ReferenceIsNotMyType", 305 },
    { "RegionAreaExceedsLimit", 306 },
    { "RequestDidNotReturnAnImage", 307 },
    { "SteganoImageRequired", 308 },
    { "StereoImageRequired", 309 },
    { "SubimageSpecificationReturnsNoImages", 310 },
    { "TileNotBoundedByImageDimensions", 311 },
    { "UnableToAddOrRemoveProfile", 312 },
    { "UnableToAverageImageSequence", 313 },
    { "UnableToBlurImage", 314 },
    { "UnableToChopImage", 315 },
    { "UnableToColorMatrixImage", 316 },
    { "UnableToConstituteImage", 317 },
    { "UnableToConvolveImage", 318 },
    { "UnableToEdgeImage", 319 },
    { "UnableToEqualizeImage", 320 },
    { "UnableToFilterImage", 321 },
    { "UnableToFormatImageMetadata", 322 },
    { "UnableToFrameImage", 323 },
    { "UnableToOilPaintImage", 324 },
    { "UnableToPaintImage", 325 },
    { "UnableToRaiseImage", 326 },
    { "UnableToSharpenImage", 327 },
    { "UnableToThresholdImage", 328 },
    { "UnableToWaveImage", 329 },
    { "UnrecognizedAttribute", 330 },
    { "UnrecognizedChannelType", 331 },
    { "UnrecognizedColor", 332 },
    { "UnrecognizedColormapType", 333 },
    { "UnrecognizedColorspace", 334 },
    { "UnrecognizedCommand", 335 },
    { "UnrecognizedComposeOperator", 336 },
    { "UnrecognizedDisposeMethod", 337 },
    { "UnrecognizedElement", 338 },
    { "UnrecognizedEndianType", 339 },
    { "UnrecognizedGravityType", 340 },
    { "UnrecognizedHighlightStyle", 341 },
    { "UnrecognizedImageCompression", 342 },
    { "UnrecognizedImageFilter", 343 },
    { "UnrecognizedImageFormat", 344 },
    { "UnrecognizedImageMode", 345 },
    { "UnrecognizedImageType", 346 },
    { "UnrecognizedIntentType", 347 },
    { "UnrecognizedInterlaceType", 348 },
    { "UnrecognizedListType", 349 },
    { "UnrecognizedMetric", 350 },
    { "UnrecognizedModeType", 351 },
    { "UnrecognizedNoiseType", 352 },
    { "UnrecognizedOperator", 353 },
    { "UnrecognizedOption", 354 },
    { "UnrecognizedPerlMagickMethod", 355 },
    { "UnrecognizedPixelMap", 356 },
    { "UnrecognizedPreviewType", 357 },
    { "UnrecognizedResourceType", 358 },
    { "UnrecognizedType", 359 },
    { "UnrecognizedUnitsType", 360 },
    { "UnrecognizedVirtualPixelMethod", 361 },
    { "UnsupportedSamplingFactor", 362 },
    { "UsageError", 363 },
    { "InvalidColorspaceType", 364 },
    { "InvalidEndianType", 365 },
    { "InvalidImageType", 366 },
    { "InvalidInterlaceType", 367 },
    { "MissingAnImageFilename", 368 },
    { "MissingArgument", 369 },
    { "NoImagesWereLoaded", 370 },
    { "OptionLengthExceedsLimit", 371 },
    { "RequestDidNotReturnAnImage", 372 },
    { "UnableToOpenXServer", 373 },
    { "UnableToPersistKey", 374 },
    { "UnrecognizedColormapType", 375 },
    { "UnrecognizedColorspaceType", 376 },
    { "UnrecognizedDisposeMethod", 377 },
    { "UnrecognizedEndianType", 378 },
    { "UnrecognizedFilterType", 379 },
    { "UnrecognizedImageCompressionType", 380 },
    { "UnrecognizedImageType", 381 },
    { "UnrecognizedInterlaceType", 382 },
    { "UnrecognizedOption", 383 },
    { "UnrecognizedResourceType", 384 },
    { "UnrecognizedVirtualPixelMethod", 385 },
    { "UnrecognizedColor", 386 },
    { "ImageExpected", 387 },
    { "ImageInfoExpected", 388 },
    { "StructureSizeMismatch", 389 },
    { "UnableToGetRegistryID", 390 },
    { "UnableToLocateImage", 391 },
    { "UnableToSetRegistry", 392 },
    { "Default", 393 },
    { "Default", 394 },
    { "CacheResourcesExhausted", 395 },
    { "ImagePixelHeightLimitExceeded", 396 },
    { "ImagePixelLimitExceeded", 397 },
    { "ImagePixelWidthLimitExceeded", 398 },
    { "MemoryAllocationFailed", 399 },
    { "NoPixelsDefinedInCache", 400 },
    { "PixelCacheAllocationFailed", 401 },
    { "UnableToAddColorProfile", 402 },
    { "UnableToAddGenericProfile", 403 },
    { "UnableToAddIPTCProfile", 404 },
    { "UnableToAddOrRemoveProfile", 405 },
    { "UnableToAllocateCoefficients", 406 },
    { "UnableToAllocateColormap", 407 },
    { "UnableToAllocateICCProfile", 408 },
    { "UnableToAllocateImage", 409 },
    { "UnableToAllocateString", 410 },
    { "UnableToAnnotateImage", 411 },
    { "UnableToAverageImageSequence", 412 },
    { "UnableToCloneDrawingWand", 413 },
    { "UnableToCloneImage", 414 },
    { "UnableToComputeImageSignature", 415 },
    { "UnableToConstituteImage", 416 },
    { "UnableToConvertFont", 417 },
    { "UnableToConvertStringToTokens", 418 },
    { "UnableToCreateColormap", 419 },
    { "UnableToCreateColorTransform", 420 },
    { "UnableToCreateCommandWidget", 421 },
    { "UnableToCreateImageGroup", 422 },
    { "UnableToCreateImageMontage", 423 },
    { "UnableToCreateXWindow", 424 },
    { "UnableToCropImage", 425 },
    { "UnableToDespeckleImage", 426 },
    { "UnableToDetermineImageClass", 427 },
    { "UnableToDetermineTheNumberOfImageColors", 428 },
    { "UnableToDitherImage", 429 },
    { "UnableToDrawOnImage", 430 },
    { "UnableToEdgeImage", 431 },
    { "UnableToEmbossImage", 432 },
    { "UnableToEnhanceImage", 433 },
    { "UnableToFloodfillImage", 434 },
    { "UnableToGammaCorrectImage", 435 },
    { "UnableToGetBestIconSize", 436 },
    { "UnableToGetFromRegistry", 437 },
    { "UnableToGetPackageInfo", 438 },
    { "UnableToLevelImage", 439 },
    { "UnableToMagnifyImage", 440 },
    { "UnableToManageColor", 441 },
    { "UnableToMapImage", 442 },
    { "UnableToMapImageSequence", 443 },
    { "UnableToMedianFilterImage", 444 },
    { "UnableToMotionBlurImage", 445 },
    { "UnableToNoiseFilterImage", 446 },
    { "UnableToNormalizeImage", 447 },
    { "UnableToOpenColorProfile", 448 },
    { "UnableToQuantizeImage", 449 },
    { "UnableToQuantizeImageSequence", 450 },
    { "UnableToReadTextChunk", 451 },
    { "UnableToReadXImage", 452 },
    { "UnableToReadXServerColormap", 453 },
    { "UnableToResizeImage", 454 },
    { "UnableToRotateImage", 455 },
    { "UnableToSampleImage", 456 },
    { "UnableToScaleImage", 457 },
    { "UnableToSelectImage", 458 },
    { "UnableToSharpenImage", 459 },
    { "UnableToShaveImage", 460 },
    { "UnableToShearImage", 461 },
    { "UnableToSortImageColormap", 462 },
    { "UnableToThresholdImage", 463 },
    { "UnableToTransformColorspace", 464 },
    { "MemoryAllocationFailed", 465 },
    { "SemaporeOperationFailed", 466 },
    { "UnableToAllocateAscii85Info", 467 },
    { "UnableToAllocateCacheInfo", 468 },
    { "UnableToAllocateCacheView", 469 },
    { "UnableToAllocateColorInfo", 470 },
    { "UnableToAllocateDashPattern", 471 },
    { "UnableToAllocateDelegateInfo", 472 },
    { "UnableToAllocateDerivatives", 473 },
    { "UnableToAllocateDrawContext", 474 },
    { "UnableToAllocateDrawInfo", 475 },
    { "UnableToAllocateDrawingWand", 476 },
    { "UnableToAllocateGammaMap", 477 },
    { "UnableToAllocateImage", 478 },
    { "UnableToAllocateImagePixels", 479 },
    { "UnableToAllocateLogInfo", 480 },
    { "UnableToAllocateMagicInfo", 481 },
    { "UnableToAllocateMagickInfo", 482 },
    { "UnableToAllocateMagickMap", 483 },
    { "UnableToAllocateModuleInfo", 484 },
    { "UnableToAllocateMontageInfo", 485 },
    { "UnableToAllocateQuantizeInfo", 486 },
    { "UnableToAllocateRandomKernel", 487 },
    { "UnableToAllocateRegistryInfo", 488 },
    { "UnableToAllocateSemaphoreInfo", 489 },
    { "UnableToAllocateString", 490 },
    { "UnableToAllocateTypeInfo", 491 },
    { "UnableToAllocateWand", 492 },
    { "UnableToAnimateImageSequence", 493 },
    { "UnableToCloneBlobInfo", 494 },
    { "UnableToCloneCacheInfo", 495 },
    { "UnableToCloneImage", 496 },
    { "UnableToCloneImageInfo", 497 },
    { "UnableToConcatenateString", 498 },
    { "UnableToConvertText", 499 },
    { "UnableToCreateColormap", 500 },
    { "UnableToDestroySemaphore", 501 },
    { "UnableToDisplayImage", 502 },
    { "UnableToEscapeString", 503 },
    { "UnableToInitializeSemaphore", 504 },
    { "UnableToInterpretMSLImage", 505 },
    { "UnableToLockSemaphore", 506 },
    { "UnableToObtainRandomEntropy", 507 },
    { "UnableToUnlockSemaphore", 508 },
    { "MemoryAllocationFailed", 509 },
    { "ImageDoesNotContainTheStreamGeometry", 510 },
    { "NoStreamHandlerIsDefined", 511 },
    { "PixelCacheIsNotOpen", 512 },
    { "UnableToAcquirePixelStream", 513 },
    { "UnableToSetPixelStream", 514 },
    { "UnableToSyncPixelStream", 515 },
    { "Default", 516 },
    { "Default", 517 },
    { "FontSubstitutionRequired", 518 },
    { "UnableToGetTypeMetrics", 519 },
    { "UnableToInitializeFreetypeLibrary", 520 },
    { "UnableToReadFont", 521 },
    { "UnrecognizedFontEncoding", 522 },
    { "Default", 523 },
    { "Default", 524 },
    { "InvalidColormapIndex", 525 },
    { "WandAPINotImplemented", 526 },
    { "WandContainsNoImageIndexs", 527 },
    { "WandContainsNoImages", 528 },
    { "ColorIsNotKnownToServer", 529 },
    { "NoWindowWithSpecifiedIDExists", 530 },
    { "StandardColormapIsNotInitialized", 531 },
    { "UnableToConnectToRemoteDisplay", 532 },
    { "UnableToCreateBitmap", 533 },
    { "UnableToCreateColormap", 534 },
    { "UnableToCreatePixmap", 535 },
    { "UnableToCreateProperty", 536 },
    { "UnableToCreateStandardColormap", 537 },
    { "UnableToDisplayImageInfo", 538 },
    { "UnableToGetProperty", 539 },
    { "UnableToGetStandardColormap", 540 },
    { "UnableToGetVisual", 541 },
    { "UnableToGrabMouse", 542 },
    { "UnableToLoadFont", 543 },
    { "UnableToMatchVisualToStandardColormap", 544 },
    { "UnableToOpenXServer", 545 },
    { "UnableToReadXAttributes", 546 },
    { "UnableToReadXWindowImage", 547 },
    { "UnrecognizedColormapType", 548 },
    { "UnrecognizedGravityType", 549 },
    { "UnrecognizedVisualSpecifier", 550 },
    { "UnableToAllocateXHints", 551 },
    { "UnableToCreateCursor", 552 },
    { "UnableToCreateGraphicContext", 553 },
    { "UnableToCreateStandardColormap", 554 },
    { "UnableToCreateTextProperty", 555 },
    { "UnableToCreateXImage", 556 },
    { "UnableToCreateXPixmap", 557 },
    { "UnableToCreateXWindow", 558 },
    { "UnableToDisplayImage", 559 },
    { "UnableToDitherImage", 560 },
    { "UnableToGetPixelInfo", 561 },
    { "UnableToGetVisual", 562 },
    { "UnableToLoadFont", 563 },
    { "UnableToMakeXWindow", 564 },
    { "UnableToOpenXServer", 565 },
    { "UnableToViewFonts", 566 },
    { "UnableToGetVisual", 567 },
    { "UsingDefaultVisual", 568 },
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
    "Pixel cache dimensions incompatible with image dimensions",
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
    "Arithmetic overflow",
    "Colormap size exceeds limit",
    "Colormap type not supported",
    "Colorspace model is not supported",
    "Color type not supported",
    "Compression not valid",
    "Data encoding scheme is not supported",
    "Data storage type is not supported",
    "Delta-PNG is not supported",
    "Division by zero",
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
    "Image file has no scenes",
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
    "Corrupt image (some data returned)",
    "Improper image header",
    "Invalid colormap index",
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
    "unreasonable gradient image size",
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
    "CMYKA image lacks an alpha channel (indexes)",
    "Colorspace color profile mismatch",
    "image colorspace differs",
    "image colorspace mismatch",
    "image difference exceeds limit (%s)",
    "image does not contain resolution",
    "image is not colormapped",
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
    "unable to export image pixels",
    "unable to flatten image",
    "Unable to get clip mask",
    "unable to handle image channel",
    "unable to import image pixels",
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
    "Tile is not bounded by image dimensions",
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
    "unable to add or remove profile",
    "unable to allocate coefficients",
    "Unable to allocate colormap",
    "unable to allocate ICC profile",
    "Unable to allocate image",
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
    "unable to allocate magick map",
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

#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 574

#define MGK_BlobErrorUnableToCreateBlob 1
#define MGK_BlobErrorUnableToDeduceImageFormat 2
#define MGK_BlobErrorUnableToObtainOffset 3
#define MGK_BlobErrorUnableToOpenFile 4
#define MGK_BlobErrorUnableToReadFile 5
#define MGK_BlobErrorUnableToReadToOffset 6
#define MGK_BlobErrorUnableToSeekToOffset 7
#define MGK_BlobErrorUnableToWriteBlob 8
#define MGK_BlobErrorUnrecognizedImageFormat 9
#define MGK_BlobFatalErrorDefault 10
#define MGK_BlobWarningDefault 11
#define MGK_CacheErrorInconsistentPersistentCacheDepth 12
#define MGK_CacheErrorPixelCacheDimensionsMisMatch 13
#define MGK_CacheErrorPixelCacheIsNotOpen 14
#define MGK_CacheErrorUnableToAllocateCacheView 15
#define MGK_CacheErrorUnableToCloneCache 16
#define MGK_CacheErrorUnableToExtendCache 17
#define MGK_CacheErrorUnableToGetCacheNexus 18
#define MGK_CacheErrorUnableToGetPixelsFromCache 19
#define MGK_CacheErrorUnableToOpenCache 20
#define MGK_CacheErrorUnableToPeristPixelCache 21
#define MGK_CacheErrorUnableToReadPixelCache 22
#define MGK_CacheErrorUnableToSyncCache 23
#define MGK_CacheFatalErrorDiskAllocationFailed 24
#define MGK_CacheFatalErrorUnableToExtendPixelCache 25
#define MGK_CacheWarningDefault 26
#define MGK_CoderErrorArithmeticOverflow 27
#define MGK_CoderErrorColormapTooLarge 28
#define MGK_CoderErrorColormapTypeNotSupported 29
#define MGK_CoderErrorColorspaceModelIsNotSupported 30
#define MGK_CoderErrorColorTypeNotSupported 31
#define MGK_CoderErrorCompressionNotValid 32
#define MGK_CoderErrorDataEncodingSchemeIsNotSupported 33
#define MGK_CoderErrorDataStorageTypeIsNotSupported 34
#define MGK_CoderErrorDecodedImageNotReturned 35
#define MGK_CoderErrorDeltaPNGNotSupported 36
#define MGK_CoderErrorDivisionByZero 37
#define MGK_CoderErrorEncryptedWPGImageFileNotSupported 38
#define MGK_CoderErrorFractalCompressionNotSupported 39
#define MGK_CoderErrorImageColumnOrRowSizeIsNotSupported 40
#define MGK_CoderErrorImageDoesNotHaveAMatteChannel 41
#define MGK_CoderErrorImageIsNotTiled 42
#define MGK_CoderErrorImageTypeNotSupported 43
#define MGK_CoderErrorIncompatibleSizeOfDouble 44
#define MGK_CoderErrorIrregularChannelGeometryNotSupported 45
#define MGK_CoderErrorJNGCompressionNotSupported 46
#define MGK_CoderErrorJPEGCompressionNotSupported 47
#define MGK_CoderErrorJPEGEmbeddingFailed 48
#define MGK_CoderErrorLocationTypeIsNotSupported 49
#define MGK_CoderErrorMapStorageTypeIsNotSupported 50
#define MGK_CoderErrorMSBByteOrderNotSupported 51
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 52
#define MGK_CoderErrorMultipleRecordListNotSupported 53
#define MGK_CoderErrorNo8BIMDataIsAvailable 54
#define MGK_CoderErrorNoAPP1DataIsAvailable 55
#define MGK_CoderErrorNoBitmapOnClipboard 56
#define MGK_CoderErrorNoColorProfileAvailable 57
#define MGK_CoderErrorNoDataReturned 58
#define MGK_CoderErrorNoImageVectorGraphics 59
#define MGK_CoderErrorNoIPTCInfoWasFound 60
#define MGK_CoderErrorNoIPTCProfileAvailable 61
#define MGK_CoderErrorNumberOfImagesIsNotSupported 62
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 63
#define MGK_CoderErrorOnlyLevelZerofilesSupported 64
#define MGK_CoderErrorPNGCompressionNotSupported 65
#define MGK_CoderErrorPNGLibraryTooOld 66
#define MGK_CoderErrorRLECompressionNotSupported 67
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 68
#define MGK_CoderErrorUnableToCopyProfile 69
#define MGK_CoderErrorUnableToCreateADC 70
#define MGK_CoderErrorUnableToCreateBitmap 71
#define MGK_CoderErrorUnableToDecompressImage 72
#define MGK_CoderErrorUnableToInitializeFPXLibrary 73
#define MGK_CoderErrorUnableToOpenBlob 74
#define MGK_CoderErrorUnableToReadAspectRatio 75
#define MGK_CoderErrorUnableToReadCIELABImages 76
#define MGK_CoderErrorUnableToReadSummaryInfo 77
#define MGK_CoderErrorUnableToSetAffineMatrix 78
#define MGK_CoderErrorUnableToSetAspectRatio 79
#define MGK_CoderErrorUnableToSetColorTwist 80
#define MGK_CoderErrorUnableToSetContrast 81
#define MGK_CoderErrorUnableToSetFilteringValue 82
#define MGK_CoderErrorUnableToSetImageComments 83
#define MGK_CoderErrorUnableToSetImageTitle 84
#define MGK_CoderErrorUnableToSetJPEGLevel 85
#define MGK_CoderErrorUnableToSetRegionOfInterest 86
#define MGK_CoderErrorUnableToSetSummaryInfo 87
#define MGK_CoderErrorUnableToTranslateText 88
#define MGK_CoderErrorUnableToWriteMPEGParameters 89
#define MGK_CoderErrorUnableToWriteTemporaryFile 90
#define MGK_CoderErrorUnableToZipCompressImage 91
#define MGK_CoderErrorUnsupportedBitsPerSample 92
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 93
#define MGK_CoderErrorUnsupportedSamplesPerPixel 94
#define MGK_CoderErrorWebPDecodingFailedUserAbort 95
#define MGK_CoderErrorWebPEncodingFailed 96
#define MGK_CoderErrorWebPEncodingFailedBadDimension 97
#define MGK_CoderErrorWebPEncodingFailedBadWrite 98
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 99
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 100
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 101
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 102
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 103
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 104
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 105
#define MGK_CoderErrorWebPEncodingFailedUserAbort 106
#define MGK_CoderErrorWebPInvalidConfiguration 107
#define MGK_CoderErrorWebPInvalidParameter 108
#define MGK_CoderErrorZipCompressionNotSupported 109
#define MGK_CoderFatalErrorDefault 110
#define MGK_CoderWarningLosslessToLossyJPEGConversion 111
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 112
#define MGK_ConfigureErrorRegistryKeyLookupFailed 113
#define MGK_ConfigureErrorStringTokenLengthExceeded 114
#define MGK_ConfigureErrorUnableToAccessConfigureFile 115
#define MGK_ConfigureErrorUnableToAccessFontFile 116
#define MGK_ConfigureErrorUnableToAccessLogFile 117
#define MGK_ConfigureErrorUnableToAccessModuleFile 118
#define MGK_ConfigureFatalErrorDefault 119
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 120
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 121
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 122
#define MGK_ConfigureWarningDefault 123
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 124
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 125
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 126
#define MGK_CorruptImageErrorCompressionNotValid 127
#define MGK_CorruptImageErrorCorruptImage 128
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 129
#define MGK_CorruptImageErrorImageFileHasNoScenes 130
#define MGK_CorruptImageErrorImageTypeNotSupported 131
#define MGK_CorruptImageErrorImproperImageHeader 132
#define MGK_CorruptImageErrorInsufficientImageDataInFile 133
#define MGK_CorruptImageErrorInvalidColormapIndex 134
#define MGK_CorruptImageErrorInvalidFileFormatVersion 135
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 136
#define MGK_CorruptImageErrorMissingImageChannel 137
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 138
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 139
#define MGK_CorruptImageErrorNotEnoughTiles 140
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 141
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 142
#define MGK_CorruptImageErrorTooMuchImageDataInFile 143
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 144
#define MGK_CorruptImageErrorUnableToReadColorProfile 145
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 146
#define MGK_CorruptImageErrorUnableToReadGenericProfile 147
#define MGK_CorruptImageErrorUnableToReadImageData 148
#define MGK_CorruptImageErrorUnableToReadImageHeader 149
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 150
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 151
#define MGK_CorruptImageErrorUnableToReadSubImageData 152
#define MGK_CorruptImageErrorUnableToReadVIDImage 153
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 154
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 155
#define MGK_CorruptImageErrorUnableToUncompressImage 156
#define MGK_CorruptImageErrorUnexpectedEndOfFile 157
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 158
#define MGK_CorruptImageErrorUnknownPatternType 159
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 160
#define MGK_CorruptImageErrorUnrecognizedImageCompression 161
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 162
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 163
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 164
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 165
#define MGK_CorruptImageFatalErrorUnableToPersistKey 166
#define MGK_CorruptImageWarningCompressionNotValid 167
#define MGK_CorruptImageWarningCorruptImage 168
#define MGK_CorruptImageWarningImproperImageHeader 169
#define MGK_CorruptImageWarningInvalidColormapIndex 170
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 171
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 172
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 173
#define MGK_CorruptImageWarningSkipToSyncByte 174
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 175
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 176
#define MGK_CorruptImageWarningUnrecognizedImageCompression 177
#define MGK_DelegateErrorDelegateFailed 178
#define MGK_DelegateErrorFailedToAllocateArgumentList 179
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 180
#define MGK_DelegateErrorFailedToComputeOutputSize 181
#define MGK_DelegateErrorFailedToFindGhostscript 182
#define MGK_DelegateErrorFailedToRenderFile 183
#define MGK_DelegateErrorFailedToScanFile 184
#define MGK_DelegateErrorNoTagFound 185
#define MGK_DelegateErrorPostscriptDelegateFailed 186
#define MGK_DelegateErrorUnableToCreateImage 187
#define MGK_DelegateErrorUnableToCreateImageComponent 188
#define MGK_DelegateErrorUnableToDecodeImageFile 189
#define MGK_DelegateErrorUnableToEncodeImageFile 190
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 191
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 192
#define MGK_DelegateErrorUnableToManageJP2Stream 193
#define MGK_DelegateErrorUnableToWriteSVGFormat 194
#define MGK_DelegateErrorWebPABIMismatch 195
#define MGK_DelegateFatalErrorDefault 196
#define MGK_DelegateWarningDefault 197
#define MGK_DrawErrorAlreadyPushingPatternDefinition 198
#define MGK_DrawErrorDrawingRecursionDetected 199
#define MGK_DrawErrorFloatValueConversionError 200
#define MGK_DrawErrorIntegerValueConversionError 201
#define MGK_DrawErrorInvalidPrimitiveArgument 202
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 203
#define MGK_DrawErrorPrimitiveArithmeticOverflow 204
#define MGK_DrawErrorTooManyCoordinates 205
#define MGK_DrawErrorUnableToPrint 206
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 207
#define MGK_DrawErrorUnreasonableGradientSize 208
#define MGK_DrawErrorVectorPathTruncated 209
#define MGK_DrawFatalErrorDefault 210
#define MGK_DrawWarningNotARelativeURL 211
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 212
#define MGK_DrawWarningURLNotFound 213
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 214
#define MGK_FileOpenErrorUnableToOpenFile 215
#define MGK_FileOpenErrorUnableToWriteFile 216
#define MGK_FileOpenFatalErrorDefault 217
#define MGK_FileOpenWarningDefault 218
#define MGK_ImageErrorAngleIsDiscontinuous 219
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 220
#define MGK_ImageErrorColorspaceColorProfileMismatch 221
#define MGK_ImageErrorImageColorspaceDiffers 222
#define MGK_ImageErrorImageColorspaceMismatch 223
#define MGK_ImageErrorImageDifferenceExceedsLimit 224
#define MGK_ImageErrorImageDoesNotContainResolution 225
#define MGK_ImageErrorImageIsNotColormapped 226
#define MGK_ImageErrorImageOpacityDiffers 227
#define MGK_ImageErrorImageSequenceIsRequired 228
#define MGK_ImageErrorImageSizeDiffers 229
#define MGK_ImageErrorInvalidColormapIndex 230
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 231
#define MGK_ImageErrorNoImagesWereFound 232
#define MGK_ImageErrorNoImagesWereLoaded 233
#define MGK_ImageErrorNoLocaleImageAttribute 234
#define MGK_ImageErrorTooManyClusters 235
#define MGK_ImageErrorUnableToAppendImage 236
#define MGK_ImageErrorUnableToAssignProfile 237
#define MGK_ImageErrorUnableToAverageImage 238
#define MGK_ImageErrorUnableToCoalesceImage 239
#define MGK_ImageErrorUnableToCompareImages 240
#define MGK_ImageErrorUnableToCreateImageMosaic 241
#define MGK_ImageErrorUnableToCreateStereoImage 242
#define MGK_ImageErrorUnableToDeconstructImageSequence 243
#define MGK_ImageErrorUnableToExportImagePixels 244
#define MGK_ImageErrorUnableToFlattenImage 245
#define MGK_ImageErrorUnableToGetClipMask 246
#define MGK_ImageErrorUnableToGetCompositeMask 247
#define MGK_ImageErrorUnableToHandleImageChannel 248
#define MGK_ImageErrorUnableToImportImagePixels 249
#define MGK_ImageErrorUnableToResizeImage 250
#define MGK_ImageErrorUnableToSegmentImage 251
#define MGK_ImageErrorUnableToSetClipMask 252
#define MGK_ImageErrorUnableToSetCompositeMask 253
#define MGK_ImageErrorUnableToShearImage 254
#define MGK_ImageErrorWidthOrHeightExceedsLimit 255
#define MGK_ImageFatalErrorUnableToPersistKey 256
#define MGK_ImageWarningDefault 257
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 258
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 259
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 260
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 261
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 262
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 263
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 264
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 265
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 266
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 267
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 268
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 269
#define MGK_MissingDelegateFatalErrorDefault 270
#define MGK_MissingDelegateWarningDefault 271
#define MGK_ModuleErrorFailedToCloseModule 272
#define MGK_ModuleErrorFailedToFindSymbol 273
#define MGK_ModuleErrorUnableToLoadModule 274
#define MGK_ModuleErrorUnableToRegisterImageFormat 275
#define MGK_ModuleErrorUnrecognizedModule 276
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 277
#define MGK_ModuleWarningDefault 278
#define MGK_MonitorErrorDefault 279
#define MGK_MonitorFatalErrorDefault 280
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 281
#define MGK_MonitorWarningDefault 282
#define MGK_OptionErrorBevelWidthIsNegative 283
#define MGK_OptionErrorColorSeparatedImageRequired 284
#define MGK_OptionErrorFrameIsLessThanImageSize 285
#define MGK_OptionErrorGeometryDimensionsAreZero 286
#define MGK_OptionErrorGeometryDoesNotContainImage 287
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 288
#define MGK_OptionErrorImagesAreNotTheSameSize 289
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 290
#define MGK_OptionErrorImageSmallerThanKernelWidth 291
#define MGK_OptionErrorImageSmallerThanRadius 292
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 293
#define MGK_OptionErrorInputImagesAlreadySpecified 294
#define MGK_OptionErrorInvalidSubimageSpecification 295
#define MGK_OptionErrorKernelRadiusIsTooSmall 296
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 297
#define MGK_OptionErrorMatrixIsNotSquare 298
#define MGK_OptionErrorMatrixOrderOutOfRange 299
#define MGK_OptionErrorMissingAnImageFilename 300
#define MGK_OptionErrorMissingArgument 301
#define MGK_OptionErrorMustSpecifyAnImageName 302
#define MGK_OptionErrorMustSpecifyImageSize 303
#define MGK_OptionErrorNoBlobDefined 304
#define MGK_OptionErrorNoImagesDefined 305
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 306
#define MGK_OptionErrorNoProfileNameWasGiven 307
#define MGK_OptionErrorNullBlobArgument 308
#define MGK_OptionErrorReferenceImageRequired 309
#define MGK_OptionErrorReferenceIsNotMyType 310
#define MGK_OptionErrorRegionAreaExceedsLimit 311
#define MGK_OptionErrorRequestDidNotReturnAnImage 312
#define MGK_OptionErrorSteganoImageRequired 313
#define MGK_OptionErrorStereoImageRequired 314
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 315
#define MGK_OptionErrorTileNotBoundedByImageDimensions 316
#define MGK_OptionErrorUnableToAddOrRemoveProfile 317
#define MGK_OptionErrorUnableToAverageImageSequence 318
#define MGK_OptionErrorUnableToBlurImage 319
#define MGK_OptionErrorUnableToChopImage 320
#define MGK_OptionErrorUnableToColorMatrixImage 321
#define MGK_OptionErrorUnableToConstituteImage 322
#define MGK_OptionErrorUnableToConvolveImage 323
#define MGK_OptionErrorUnableToEdgeImage 324
#define MGK_OptionErrorUnableToEqualizeImage 325
#define MGK_OptionErrorUnableToFilterImage 326
#define MGK_OptionErrorUnableToFormatImageMetadata 327
#define MGK_OptionErrorUnableToFrameImage 328
#define MGK_OptionErrorUnableToOilPaintImage 329
#define MGK_OptionErrorUnableToPaintImage 330
#define MGK_OptionErrorUnableToRaiseImage 331
#define MGK_OptionErrorUnableToSharpenImage 332
#define MGK_OptionErrorUnableToThresholdImage 333
#define MGK_OptionErrorUnableToWaveImage 334
#define MGK_OptionErrorUnrecognizedAttribute 335
#define MGK_OptionErrorUnrecognizedChannelType 336
#define MGK_OptionErrorUnrecognizedColor 337
#define MGK_OptionErrorUnrecognizedColormapType 338
#define MGK_OptionErrorUnrecognizedColorspace 339
#define MGK_OptionErrorUnrecognizedCommand 340
#define MGK_OptionErrorUnrecognizedComposeOperator 341
#define MGK_OptionErrorUnrecognizedDisposeMethod 342
#define MGK_OptionErrorUnrecognizedElement 343
#define MGK_OptionErrorUnrecognizedEndianType 344
#define MGK_OptionErrorUnrecognizedGravityType 345
#define MGK_OptionErrorUnrecognizedHighlightStyle 346
#define MGK_OptionErrorUnrecognizedImageCompression 347
#define MGK_OptionErrorUnrecognizedImageFilter 348
#define MGK_OptionErrorUnrecognizedImageFormat 349
#define MGK_OptionErrorUnrecognizedImageMode 350
#define MGK_OptionErrorUnrecognizedImageType 351
#define MGK_OptionErrorUnrecognizedIntentType 352
#define MGK_OptionErrorUnrecognizedInterlaceType 353
#define MGK_OptionErrorUnrecognizedListType 354
#define MGK_OptionErrorUnrecognizedMetric 355
#define MGK_OptionErrorUnrecognizedModeType 356
#define MGK_OptionErrorUnrecognizedNoiseType 357
#define MGK_OptionErrorUnrecognizedOperator 358
#define MGK_OptionErrorUnrecognizedOption 359
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 360
#define MGK_OptionErrorUnrecognizedPixelMap 361
#define MGK_OptionErrorUnrecognizedPreviewType 362
#define MGK_OptionErrorUnrecognizedResourceType 363
#define MGK_OptionErrorUnrecognizedType 364
#define MGK_OptionErrorUnrecognizedUnitsType 365
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 366
#define MGK_OptionErrorUnsupportedSamplingFactor 367
#define MGK_OptionErrorUsageError 368
#define MGK_OptionFatalErrorInvalidColorspaceType 369
#define MGK_OptionFatalErrorInvalidEndianType 370
#define MGK_OptionFatalErrorInvalidImageType 371
#define MGK_OptionFatalErrorInvalidInterlaceType 372
#define MGK_OptionFatalErrorMissingAnImageFilename 373
#define MGK_OptionFatalErrorMissingArgument 374
#define MGK_OptionFatalErrorNoImagesWereLoaded 375
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 376
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 377
#define MGK_OptionFatalErrorUnableToOpenXServer 378
#define MGK_OptionFatalErrorUnableToPersistKey 379
#define MGK_OptionFatalErrorUnrecognizedColormapType 380
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 381
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 382
#define MGK_OptionFatalErrorUnrecognizedEndianType 383
#define MGK_OptionFatalErrorUnrecognizedFilterType 384
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 385
#define MGK_OptionFatalErrorUnrecognizedImageType 386
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 387
#define MGK_OptionFatalErrorUnrecognizedOption 388
#define MGK_OptionFatalErrorUnrecognizedResourceType 389
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 390
#define MGK_OptionWarningUnrecognizedColor 391
#define MGK_RegistryErrorImageExpected 392
#define MGK_RegistryErrorImageInfoExpected 393
#define MGK_RegistryErrorStructureSizeMismatch 394
#define MGK_RegistryErrorUnableToGetRegistryID 395
#define MGK_RegistryErrorUnableToLocateImage 396
#define MGK_RegistryErrorUnableToSetRegistry 397
#define MGK_RegistryFatalErrorDefault 398
#define MGK_RegistryWarningDefault 399
#define MGK_ResourceLimitErrorCacheResourcesExhausted 400
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 401
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 402
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 403
#define MGK_ResourceLimitErrorMemoryAllocationFailed 404
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 405
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 406
#define MGK_ResourceLimitErrorUnableToAddColorProfile 407
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 408
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 409
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 410
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 411
#define MGK_ResourceLimitErrorUnableToAllocateColormap 412
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 413
#define MGK_ResourceLimitErrorUnableToAllocateImage 414
#define MGK_ResourceLimitErrorUnableToAllocateString 415
#define MGK_ResourceLimitErrorUnableToAnnotateImage 416
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 417
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 418
#define MGK_ResourceLimitErrorUnableToCloneImage 419
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 420
#define MGK_ResourceLimitErrorUnableToConstituteImage 421
#define MGK_ResourceLimitErrorUnableToConvertFont 422
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 423
#define MGK_ResourceLimitErrorUnableToCreateColormap 424
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 425
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 426
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 427
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 428
#define MGK_ResourceLimitErrorUnableToCreateXWindow 429
#define MGK_ResourceLimitErrorUnableToCropImage 430
#define MGK_ResourceLimitErrorUnableToDespeckleImage 431
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 432
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 433
#define MGK_ResourceLimitErrorUnableToDitherImage 434
#define MGK_ResourceLimitErrorUnableToDrawOnImage 435
#define MGK_ResourceLimitErrorUnableToEdgeImage 436
#define MGK_ResourceLimitErrorUnableToEmbossImage 437
#define MGK_ResourceLimitErrorUnableToEnhanceImage 438
#define MGK_ResourceLimitErrorUnableToFloodfillImage 439
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 440
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 441
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 442
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 443
#define MGK_ResourceLimitErrorUnableToLevelImage 444
#define MGK_ResourceLimitErrorUnableToMagnifyImage 445
#define MGK_ResourceLimitErrorUnableToManageColor 446
#define MGK_ResourceLimitErrorUnableToMapImage 447
#define MGK_ResourceLimitErrorUnableToMapImageSequence 448
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 449
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 450
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 451
#define MGK_ResourceLimitErrorUnableToNormalizeImage 452
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 453
#define MGK_ResourceLimitErrorUnableToQuantizeImage 454
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 455
#define MGK_ResourceLimitErrorUnableToReadTextChunk 456
#define MGK_ResourceLimitErrorUnableToReadXImage 457
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 458
#define MGK_ResourceLimitErrorUnableToResizeImage 459
#define MGK_ResourceLimitErrorUnableToRotateImage 460
#define MGK_ResourceLimitErrorUnableToSampleImage 461
#define MGK_ResourceLimitErrorUnableToScaleImage 462
#define MGK_ResourceLimitErrorUnableToSelectImage 463
#define MGK_ResourceLimitErrorUnableToSharpenImage 464
#define MGK_ResourceLimitErrorUnableToShaveImage 465
#define MGK_ResourceLimitErrorUnableToShearImage 466
#define MGK_ResourceLimitErrorUnableToSortImageColormap 467
#define MGK_ResourceLimitErrorUnableToThresholdImage 468
#define MGK_ResourceLimitErrorUnableToTransformColorspace 469
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 470
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 475
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 477
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 478
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 479
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 480
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 481
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 490
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 491
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 492
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 493
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 494
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 495
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 496
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 497
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 498
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 499
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 500
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 501
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 502
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 503
#define MGK_ResourceLimitFatalErrorUnableToConvertText 504
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 505
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 506
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 507
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 508
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 509
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 510
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 511
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 512
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 513
#define MGK_ResourceLimitWarningMemoryAllocationFailed 514
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 515
#define MGK_StreamErrorNoStreamHandlerIsDefined 516
#define MGK_StreamErrorPixelCacheIsNotOpen 517
#define MGK_StreamErrorUnableToAcquirePixelStream 518
#define MGK_StreamErrorUnableToSetPixelStream 519
#define MGK_StreamErrorUnableToSyncPixelStream 520
#define MGK_StreamFatalErrorDefault 521
#define MGK_StreamWarningDefault 522
#define MGK_TypeErrorFontNotSpecified 523
#define MGK_TypeErrorFontSubstitutionRequired 524
#define MGK_TypeErrorUnableToGetTypeMetrics 525
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 526
#define MGK_TypeErrorUnableToReadFont 527
#define MGK_TypeErrorUnrecognizedFontEncoding 528
#define MGK_TypeFatalErrorDefault 529
#define MGK_TypeWarningDefault 530
#define MGK_WandErrorInvalidColormapIndex 531
#define MGK_WandErrorWandAPINotImplemented 532
#define MGK_WandErrorWandContainsNoImageIndexs 533
#define MGK_WandErrorWandContainsNoImages 534
#define MGK_XServerErrorColorIsNotKnownToServer 535
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 536
#define MGK_XServerErrorStandardColormapIsNotInitialized 537
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 538
#define MGK_XServerErrorUnableToCreateBitmap 539
#define MGK_XServerErrorUnableToCreateColormap 540
#define MGK_XServerErrorUnableToCreatePixmap 541
#define MGK_XServerErrorUnableToCreateProperty 542
#define MGK_XServerErrorUnableToCreateStandardColormap 543
#define MGK_XServerErrorUnableToDisplayImageInfo 544
#define MGK_XServerErrorUnableToGetProperty 545
#define MGK_XServerErrorUnableToGetStandardColormap 546
#define MGK_XServerErrorUnableToGetVisual 547
#define MGK_XServerErrorUnableToGrabMouse 548
#define MGK_XServerErrorUnableToLoadFont 549
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 550
#define MGK_XServerErrorUnableToOpenXServer 551
#define MGK_XServerErrorUnableToReadXAttributes 552
#define MGK_XServerErrorUnableToReadXWindowImage 553
#define MGK_XServerErrorUnrecognizedColormapType 554
#define MGK_XServerErrorUnrecognizedGravityType 555
#define MGK_XServerErrorUnrecognizedVisualSpecifier 556
#define MGK_XServerFatalErrorUnableToAllocateXHints 557
#define MGK_XServerFatalErrorUnableToCreateCursor 558
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 559
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 560
#define MGK_XServerFatalErrorUnableToCreateTextProperty 561
#define MGK_XServerFatalErrorUnableToCreateXImage 562
#define MGK_XServerFatalErrorUnableToCreateXPixmap 563
#define MGK_XServerFatalErrorUnableToCreateXWindow 564
#define MGK_XServerFatalErrorUnableToDisplayImage 565
#define MGK_XServerFatalErrorUnableToDitherImage 566
#define MGK_XServerFatalErrorUnableToGetPixelInfo 567
#define MGK_XServerFatalErrorUnableToGetVisual 568
#define MGK_XServerFatalErrorUnableToLoadFont 569
#define MGK_XServerFatalErrorUnableToMakeXWindow 570
#define MGK_XServerFatalErrorUnableToOpenXServer 571
#define MGK_XServerFatalErrorUnableToViewFonts 572
#define MGK_XServerWarningUnableToGetVisual 573
#define MGK_XServerWarningUsingDefaultVisual 574

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
    { "Blob/FatalError", 9, BlobFatalError },
    { "Blob/Warning", 10, BlobWarning },
    { "Cache/Error", 11, CacheError },
    { "Cache/FatalError", 23, CacheFatalError },
    { "Cache/Warning", 25, CacheWarning },
    { "Coder/Error", 26, CoderError },
    { "Coder/FatalError", 109, CoderFatalError },
    { "Coder/Warning", 110, CoderWarning },
    { "Configure/Error", 111, ConfigureError },
    { "Configure/FatalError", 118, ConfigureFatalError },
    { "Configure/Warning", 122, ConfigureWarning },
    { "Corrupt/Image/Error", 123, CorruptImageError },
    { "Corrupt/Image/FatalError", 165, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 166, CorruptImageWarning },
    { "Delegate/Error", 177, DelegateError },
    { "Delegate/FatalError", 195, DelegateFatalError },
    { "Delegate/Warning", 196, DelegateWarning },
    { "Draw/Error", 197, DrawError },
    { "Draw/FatalError", 209, DrawFatalError },
    { "Draw/Warning", 210, DrawWarning },
    { "File/Open/Error", 213, FileOpenError },
    { "File/Open/FatalError", 216, FileOpenFatalError },
    { "File/Open/Warning", 217, FileOpenWarning },
    { "Image/Error", 218, ImageError },
    { "Image/FatalError", 255, ImageFatalError },
    { "Image/Warning", 256, ImageWarning },
    { "Missing/Delegate/Error", 257, MissingDelegateError },
    { "Missing/Delegate/FatalError", 269, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 270, MissingDelegateWarning },
    { "Module/Error", 271, ModuleError },
    { "Module/FatalError", 276, ModuleFatalError },
    { "Module/Warning", 277, ModuleWarning },
    { "Monitor/Error", 278, MonitorError },
    { "Monitor/FatalError", 279, MonitorFatalError },
    { "Monitor/Warning", 281, MonitorWarning },
    { "Option/Error", 282, OptionError },
    { "Option/FatalError", 368, OptionFatalError },
    { "Option/Warning", 390, OptionWarning },
    { "Registry/Error", 391, RegistryError },
    { "Registry/FatalError", 397, RegistryFatalError },
    { "Registry/Warning", 398, RegistryWarning },
    { "Resource/Limit/Error", 399, ResourceLimitError },
    { "Resource/Limit/FatalError", 469, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 513, ResourceLimitWarning },
    { "Stream/Error", 514, StreamError },
    { "Stream/FatalError", 520, StreamFatalError },
    { "Stream/Warning", 521, StreamWarning },
    { "Type/Error", 522, TypeError },
    { "Type/FatalError", 528, TypeFatalError },
    { "Type/Warning", 529, TypeWarning },
    { "Wand/Error", 530, WandError },
    { "XServer/Error", 534, XServerError },
    { "XServer/FatalError", 556, XServerFatalError },
    { "XServer/Warning", 572, XServerWarning },
    { 0, 574, UndefinedException }
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
    { "UnableToDeduceImageFormat", 2 },
    { "UnableToObtainOffset", 3 },
    { "UnableToOpenFile", 4 },
    { "UnableToReadFile", 5 },
    { "UnableToReadToOffset", 6 },
    { "UnableToSeekToOffset", 7 },
    { "UnableToWriteBlob", 8 },
    { "UnrecognizedImageFormat", 9 },
    { "Default", 10 },
    { "Default", 11 },
    { "InconsistentPersistentCacheDepth", 12 },
    { "PixelCacheDimensionsMisMatch", 13 },
    { "PixelCacheIsNotOpen", 14 },
    { "UnableToAllocateCacheView", 15 },
    { "UnableToCloneCache", 16 },
    { "UnableToExtendCache", 17 },
    { "UnableToGetCacheNexus", 18 },
    { "UnableToGetPixelsFromCache", 19 },
    { "UnableToOpenCache", 20 },
    { "UnableToPeristPixelCache", 21 },
    { "UnableToReadPixelCache", 22 },
    { "UnableToSyncCache", 23 },
    { "DiskAllocationFailed", 24 },
    { "UnableToExtendPixelCache", 25 },
    { "Default", 26 },
    { "ArithmeticOverflow", 27 },
    { "ColormapTooLarge", 28 },
    { "ColormapTypeNotSupported", 29 },
    { "ColorspaceModelIsNotSupported", 30 },
    { "ColorTypeNotSupported", 31 },
    { "CompressionNotValid", 32 },
    { "DataEncodingSchemeIsNotSupported", 33 },
    { "DataStorageTypeIsNotSupported", 34 },
    { "DecodedImageNotReturned", 35 },
    { "DeltaPNGNotSupported", 36 },
    { "DivisionByZero", 37 },
    { "EncryptedWPGImageFileNotSupported", 38 },
    { "FractalCompressionNotSupported", 39 },
    { "ImageColumnOrRowSizeIsNotSupported", 40 },
    { "ImageDoesNotHaveAMatteChannel", 41 },
    { "ImageIsNotTiled", 42 },
    { "ImageTypeNotSupported", 43 },
    { "IncompatibleSizeOfDouble", 44 },
    { "IrregularChannelGeometryNotSupported", 45 },
    { "JNGCompressionNotSupported", 46 },
    { "JPEGCompressionNotSupported", 47 },
    { "JPEGEmbeddingFailed", 48 },
    { "LocationTypeIsNotSupported", 49 },
    { "MapStorageTypeIsNotSupported", 50 },
    { "MSBByteOrderNotSupported", 51 },
    { "MultidimensionalMatricesAreNotSupported", 52 },
    { "MultipleRecordListNotSupported", 53 },
    { "No8BIMDataIsAvailable", 54 },
    { "NoAPP1DataIsAvailable", 55 },
    { "NoBitmapOnClipboard", 56 },
    { "NoColorProfileAvailable", 57 },
    { "NoDataReturned", 58 },
    { "NoImageVectorGraphics", 59 },
    { "NoIPTCInfoWasFound", 60 },
    { "NoIPTCProfileAvailable", 61 },
    { "NumberOfImagesIsNotSupported", 62 },
    { "OnlyContinuousTonePictureSupported", 63 },
    { "OnlyLevelZerofilesSupported", 64 },
    { "PNGCompressionNotSupported", 65 },
    { "PNGLibraryTooOld", 66 },
    { "RLECompressionNotSupported", 67 },
    { "SubsamplingRequiresEvenWidth", 68 },
    { "UnableToCopyProfile", 69 },
    { "UnableToCreateADC", 70 },
    { "UnableToCreateBitmap", 71 },
    { "UnableToDecompressImage", 72 },
    { "UnableToInitializeFPXLibrary", 73 },
    { "UnableToOpenBlob", 74 },
    { "UnableToReadAspectRatio", 75 },
    { "UnableToReadCIELABImages", 76 },
    { "UnableToReadSummaryInfo", 77 },
    { "UnableToSetAffineMatrix", 78 },
    { "UnableToSetAspectRatio", 79 },
    { "UnableToSetColorTwist", 80 },
    { "UnableToSetContrast", 81 },
    { "UnableToSetFilteringValue", 82 },
    { "UnableToSetImageComments", 83 },
    { "UnableToSetImageTitle", 84 },
    { "UnableToSetJPEGLevel", 85 },
    { "UnableToSetRegionOfInterest", 86 },
    { "UnableToSetSummaryInfo", 87 },
    { "UnableToTranslateText", 88 },
    { "UnableToWriteMPEGParameters", 89 },
    { "UnableToWriteTemporaryFile", 90 },
    { "UnableToZipCompressImage", 91 },
    { "UnsupportedBitsPerSample", 92 },
    { "UnsupportedCellTypeInTheMatrix", 93 },
    { "UnsupportedSamplesPerPixel", 94 },
    { "WebPDecodingFailedUserAbort", 95 },
    { "WebPEncodingFailed", 96 },
    { "WebPEncodingFailedBadDimension", 97 },
    { "WebPEncodingFailedBadWrite", 98 },
    { "WebPEncodingFailedBitstreamOutOfMemory", 99 },
    { "WebPEncodingFailedFileTooBig", 100 },
    { "WebPEncodingFailedInvalidConfiguration", 101 },
    { "WebPEncodingFailedNULLParameter", 102 },
    { "WebPEncodingFailedOutOfMemory", 103 },
    { "WebPEncodingFailedPartition0Overflow", 104 },
    { "WebPEncodingFailedPartitionOverflow", 105 },
    { "WebPEncodingFailedUserAbort", 106 },
    { "WebPInvalidConfiguration", 107 },
    { "WebPInvalidParameter", 108 },
    { "ZipCompressionNotSupported", 109 },
    { "Default", 110 },
    { "LosslessToLossyJPEGConversion", 111 },
    { "IncludeElementNestedTooDeeply", 112 },
    { "RegistryKeyLookupFailed", 113 },
    { "StringTokenLengthExceeded", 114 },
    { "UnableToAccessConfigureFile", 115 },
    { "UnableToAccessFontFile", 116 },
    { "UnableToAccessLogFile", 117 },
    { "UnableToAccessModuleFile", 118 },
    { "Default", 119 },
    { "UnableToChangeToWorkingDirectory", 120 },
    { "UnableToGetCurrentDirectory", 121 },
    { "UnableToRestoreCurrentDirectory", 122 },
    { "Default", 123 },
    { "AnErrorHasOccurredReadingFromFile", 124 },
    { "AnErrorHasOccurredWritingToFile", 125 },
    { "ColormapExceedsColorsLimit", 126 },
    { "CompressionNotValid", 127 },
    { "CorruptImage", 128 },
    { "ImageFileDoesNotContainAnyImageData", 129 },
    { "ImageFileHasNoScenes", 130 },
    { "ImageTypeNotSupported", 131 },
    { "ImproperImageHeader", 132 },
    { "InsufficientImageDataInFile", 133 },
    { "InvalidColormapIndex", 134 },
    { "InvalidFileFormatVersion", 135 },
    { "LengthAndFilesizeDoNotMatch", 136 },
    { "MissingImageChannel", 137 },
    { "NegativeOrZeroImageSize", 138 },
    { "NonOS2HeaderSizeError", 139 },
    { "NotEnoughTiles", 140 },
    { "StaticPlanesValueNotEqualToOne", 141 },
    { "SubsamplingRequiresEvenWidth", 142 },
    { "TooMuchImageDataInFile", 143 },
    { "UnableToReadColormapFromDumpFile", 144 },
    { "UnableToReadColorProfile", 145 },
    { "UnableToReadExtensionBlock", 146 },
    { "UnableToReadGenericProfile", 147 },
    { "UnableToReadImageData", 148 },
    { "UnableToReadImageHeader", 149 },
    { "UnableToReadIPTCProfile", 150 },
    { "UnableToReadPixmapFromDumpFile", 151 },
    { "UnableToReadSubImageData", 152 },
    { "UnableToReadVIDImage", 153 },
    { "UnableToReadWindowNameFromDumpFile", 154 },
    { "UnableToRunlengthDecodeImage", 155 },
    { "UnableToUncompressImage", 156 },
    { "UnexpectedEndOfFile", 157 },
    { "UnexpectedSamplingFactor", 158 },
    { "UnknownPatternType", 159 },
    { "UnrecognizedBitsPerPixel", 160 },
    { "UnrecognizedImageCompression", 161 },
    { "UnrecognizedNumberOfColors", 162 },
    { "UnrecognizedXWDHeader", 163 },
    { "UnsupportedBitsPerSample", 164 },
    { "UnsupportedNumberOfPlanes", 165 },
    { "UnableToPersistKey", 166 },
    { "CompressionNotValid", 167 },
    { "CorruptImage", 168 },
    { "ImproperImageHeader", 169 },
    { "InvalidColormapIndex", 170 },
    { "LengthAndFilesizeDoNotMatch", 171 },
    { "NegativeOrZeroImageSize", 172 },
    { "NonOS2HeaderSizeError", 173 },
    { "SkipToSyncByte", 174 },
    { "StaticPlanesValueNotEqualToOne", 175 },
    { "UnrecognizedBitsPerPixel", 176 },
    { "UnrecognizedImageCompression", 177 },
    { "DelegateFailed", 178 },
    { "FailedToAllocateArgumentList", 179 },
    { "FailedToAllocateGhostscriptInterpreter", 180 },
    { "FailedToComputeOutputSize", 181 },
    { "FailedToFindGhostscript", 182 },
    { "FailedToRenderFile", 183 },
    { "FailedToScanFile", 184 },
    { "NoTagFound", 185 },
    { "PostscriptDelegateFailed", 186 },
    { "UnableToCreateImage", 187 },
    { "UnableToCreateImageComponent", 188 },
    { "UnableToDecodeImageFile", 189 },
    { "UnableToEncodeImageFile", 190 },
    { "UnableToInitializeFPXLibrary", 191 },
    { "UnableToInitializeWMFLibrary", 192 },
    { "UnableToManageJP2Stream", 193 },
    { "UnableToWriteSVGFormat", 194 },
    { "WebPABIMismatch", 195 },
    { "Default", 196 },
    { "Default", 197 },
    { "AlreadyPushingPatternDefinition", 198 },
    { "DrawingRecursionDetected", 199 },
    { "FloatValueConversionError", 200 },
    { "IntegerValueConversionError", 201 },
    { "InvalidPrimitiveArgument", 202 },
    { "NonconformingDrawingPrimitiveDefinition", 203 },
    { "PrimitiveArithmeticOverflow", 204 },
    { "TooManyCoordinates", 205 },
    { "UnableToPrint", 206 },
    { "UnbalancedGraphicContextPushPop", 207 },
    { "UnreasonableGradientSize", 208 },
    { "VectorPathTruncated", 209 },
    { "Default", 210 },
    { "NotARelativeURL", 211 },
    { "NotCurrentlyPushingPatternDefinition", 212 },
    { "URLNotFound", 213 },
    { "UnableToCreateTemporaryFile", 214 },
    { "UnableToOpenFile", 215 },
    { "UnableToWriteFile", 216 },
    { "Default", 217 },
    { "Default", 218 },
    { "AngleIsDiscontinuous", 219 },
    { "CMYKAImageLacksAlphaChannel", 220 },
    { "ColorspaceColorProfileMismatch", 221 },
    { "ImageColorspaceDiffers", 222 },
    { "ImageColorspaceMismatch", 223 },
    { "ImageDifferenceExceedsLimit", 224 },
    { "ImageDoesNotContainResolution", 225 },
    { "ImageIsNotColormapped", 226 },
    { "ImageOpacityDiffers", 227 },
    { "ImageSequenceIsRequired", 228 },
    { "ImageSizeDiffers", 229 },
    { "InvalidColormapIndex", 230 },
    { "LeftAndRightImageSizesDiffer", 231 },
    { "NoImagesWereFound", 232 },
    { "NoImagesWereLoaded", 233 },
    { "NoLocaleImageAttribute", 234 },
    { "TooManyClusters", 235 },
    { "UnableToAppendImage", 236 },
    { "UnableToAssignProfile", 237 },
    { "UnableToAverageImage", 238 },
    { "UnableToCoalesceImage", 239 },
    { "UnableToCompareImages", 240 },
    { "UnableToCreateImageMosaic", 241 },
    { "UnableToCreateStereoImage", 242 },
    { "UnableToDeconstructImageSequence", 243 },
    { "UnableToExportImagePixels", 244 },
    { "UnableToFlattenImage", 245 },
    { "UnableToGetClipMask", 246 },
    { "UnableToGetCompositeMask", 247 },
    { "UnableToHandleImageChannel", 248 },
    { "UnableToImportImagePixels", 249 },
    { "UnableToResizeImage", 250 },
    { "UnableToSegmentImage", 251 },
    { "UnableToSetClipMask", 252 },
    { "UnableToSetCompositeMask", 253 },
    { "UnableToShearImage", 254 },
    { "WidthOrHeightExceedsLimit", 255 },
    { "UnableToPersistKey", 256 },
    { "Default", 257 },
    { "DPSLibraryIsNotAvailable", 258 },
    { "FPXLibraryIsNotAvailable", 259 },
    { "FreeTypeLibraryIsNotAvailable", 260 },
    { "JPEGLibraryIsNotAvailable", 261 },
    { "LCMSLibraryIsNotAvailable", 262 },
    { "LZWEncodingNotEnabled", 263 },
    { "NoDecodeDelegateForThisImageFormat", 264 },
    { "NoEncodeDelegateForThisImageFormat", 265 },
    { "TIFFLibraryIsNotAvailable", 266 },
    { "XMLLibraryIsNotAvailable", 267 },
    { "XWindowLibraryIsNotAvailable", 268 },
    { "ZipLibraryIsNotAvailable", 269 },
    { "Default", 270 },
    { "Default", 271 },
    { "FailedToCloseModule", 272 },
    { "FailedToFindSymbol", 273 },
    { "UnableToLoadModule", 274 },
    { "UnableToRegisterImageFormat", 275 },
    { "UnrecognizedModule", 276 },
    { "UnableToInitializeModuleLoader", 277 },
    { "Default", 278 },
    { "Default", 279 },
    { "Default", 280 },
    { "UserRequestedTerminationBySignal", 281 },
    { "Default", 282 },
    { "BevelWidthIsNegative", 283 },
    { "ColorSeparatedImageRequired", 284 },
    { "FrameIsLessThanImageSize", 285 },
    { "GeometryDimensionsAreZero", 286 },
    { "GeometryDoesNotContainImage", 287 },
    { "HaldClutImageDimensionsInvalid", 288 },
    { "ImagesAreNotTheSameSize", 289 },
    { "ImageSizeMustExceedBevelWidth", 290 },
    { "ImageSmallerThanKernelWidth", 291 },
    { "ImageSmallerThanRadius", 292 },
    { "ImageWidthsOrHeightsDiffer", 293 },
    { "InputImagesAlreadySpecified", 294 },
    { "InvalidSubimageSpecification", 295 },
    { "KernelRadiusIsTooSmall", 296 },
    { "KernelWidthMustBeAnOddNumber", 297 },
    { "MatrixIsNotSquare", 298 },
    { "MatrixOrderOutOfRange", 299 },
    { "MissingAnImageFilename", 300 },
    { "MissingArgument", 301 },
    { "MustSpecifyAnImageName", 302 },
    { "MustSpecifyImageSize", 303 },
    { "NoBlobDefined", 304 },
    { "NoImagesDefined", 305 },
    { "NonzeroWidthAndHeightRequired", 306 },
    { "NoProfileNameWasGiven", 307 },
    { "NullBlobArgument", 308 },
    { "ReferenceImageRequired", 309 },
    { "ReferenceIsNotMyType", 310 },
    { "RegionAreaExceedsLimit", 311 },
    { "RequestDidNotReturnAnImage", 312 },
    { "SteganoImageRequired", 313 },
    { "StereoImageRequired", 314 },
    { "SubimageSpecificationReturnsNoImages", 315 },
    { "TileNotBoundedByImageDimensions", 316 },
    { "UnableToAddOrRemoveProfile", 317 },
    { "UnableToAverageImageSequence", 318 },
    { "UnableToBlurImage", 319 },
    { "UnableToChopImage", 320 },
    { "UnableToColorMatrixImage", 321 },
    { "UnableToConstituteImage", 322 },
    { "UnableToConvolveImage", 323 },
    { "UnableToEdgeImage", 324 },
    { "UnableToEqualizeImage", 325 },
    { "UnableToFilterImage", 326 },
    { "UnableToFormatImageMetadata", 327 },
    { "UnableToFrameImage", 328 },
    { "UnableToOilPaintImage", 329 },
    { "UnableToPaintImage", 330 },
    { "UnableToRaiseImage", 331 },
    { "UnableToSharpenImage", 332 },
    { "UnableToThresholdImage", 333 },
    { "UnableToWaveImage", 334 },
    { "UnrecognizedAttribute", 335 },
    { "UnrecognizedChannelType", 336 },
    { "UnrecognizedColor", 337 },
    { "UnrecognizedColormapType", 338 },
    { "UnrecognizedColorspace", 339 },
    { "UnrecognizedCommand", 340 },
    { "UnrecognizedComposeOperator", 341 },
    { "UnrecognizedDisposeMethod", 342 },
    { "UnrecognizedElement", 343 },
    { "UnrecognizedEndianType", 344 },
    { "UnrecognizedGravityType", 345 },
    { "UnrecognizedHighlightStyle", 346 },
    { "UnrecognizedImageCompression", 347 },
    { "UnrecognizedImageFilter", 348 },
    { "UnrecognizedImageFormat", 349 },
    { "UnrecognizedImageMode", 350 },
    { "UnrecognizedImageType", 351 },
    { "UnrecognizedIntentType", 352 },
    { "UnrecognizedInterlaceType", 353 },
    { "UnrecognizedListType", 354 },
    { "UnrecognizedMetric", 355 },
    { "UnrecognizedModeType", 356 },
    { "UnrecognizedNoiseType", 357 },
    { "UnrecognizedOperator", 358 },
    { "UnrecognizedOption", 359 },
    { "UnrecognizedPerlMagickMethod", 360 },
    { "UnrecognizedPixelMap", 361 },
    { "UnrecognizedPreviewType", 362 },
    { "UnrecognizedResourceType", 363 },
    { "UnrecognizedType", 364 },
    { "UnrecognizedUnitsType", 365 },
    { "UnrecognizedVirtualPixelMethod", 366 },
    { "UnsupportedSamplingFactor", 367 },
    { "UsageError", 368 },
    { "InvalidColorspaceType", 369 },
    { "InvalidEndianType", 370 },
    { "InvalidImageType", 371 },
    { "InvalidInterlaceType", 372 },
    { "MissingAnImageFilename", 373 },
    { "MissingArgument", 374 },
    { "NoImagesWereLoaded", 375 },
    { "OptionLengthExceedsLimit", 376 },
    { "RequestDidNotReturnAnImage", 377 },
    { "UnableToOpenXServer", 378 },
    { "UnableToPersistKey", 379 },
    { "UnrecognizedColormapType", 380 },
    { "UnrecognizedColorspaceType", 381 },
    { "UnrecognizedDisposeMethod", 382 },
    { "UnrecognizedEndianType", 383 },
    { "UnrecognizedFilterType", 384 },
    { "UnrecognizedImageCompressionType", 385 },
    { "UnrecognizedImageType", 386 },
    { "UnrecognizedInterlaceType", 387 },
    { "UnrecognizedOption", 388 },
    { "UnrecognizedResourceType", 389 },
    { "UnrecognizedVirtualPixelMethod", 390 },
    { "UnrecognizedColor", 391 },
    { "ImageExpected", 392 },
    { "ImageInfoExpected", 393 },
    { "StructureSizeMismatch", 394 },
    { "UnableToGetRegistryID", 395 },
    { "UnableToLocateImage", 396 },
    { "UnableToSetRegistry", 397 },
    { "Default", 398 },
    { "Default", 399 },
    { "CacheResourcesExhausted", 400 },
    { "ImagePixelHeightLimitExceeded", 401 },
    { "ImagePixelLimitExceeded", 402 },
    { "ImagePixelWidthLimitExceeded", 403 },
    { "MemoryAllocationFailed", 404 },
    { "NoPixelsDefinedInCache", 405 },
    { "PixelCacheAllocationFailed", 406 },
    { "UnableToAddColorProfile", 407 },
    { "UnableToAddGenericProfile", 408 },
    { "UnableToAddIPTCProfile", 409 },
    { "UnableToAddOrRemoveProfile", 410 },
    { "UnableToAllocateCoefficients", 411 },
    { "UnableToAllocateColormap", 412 },
    { "UnableToAllocateICCProfile", 413 },
    { "UnableToAllocateImage", 414 },
    { "UnableToAllocateString", 415 },
    { "UnableToAnnotateImage", 416 },
    { "UnableToAverageImageSequence", 417 },
    { "UnableToCloneDrawingWand", 418 },
    { "UnableToCloneImage", 419 },
    { "UnableToComputeImageSignature", 420 },
    { "UnableToConstituteImage", 421 },
    { "UnableToConvertFont", 422 },
    { "UnableToConvertStringToTokens", 423 },
    { "UnableToCreateColormap", 424 },
    { "UnableToCreateColorTransform", 425 },
    { "UnableToCreateCommandWidget", 426 },
    { "UnableToCreateImageGroup", 427 },
    { "UnableToCreateImageMontage", 428 },
    { "UnableToCreateXWindow", 429 },
    { "UnableToCropImage", 430 },
    { "UnableToDespeckleImage", 431 },
    { "UnableToDetermineImageClass", 432 },
    { "UnableToDetermineTheNumberOfImageColors", 433 },
    { "UnableToDitherImage", 434 },
    { "UnableToDrawOnImage", 435 },
    { "UnableToEdgeImage", 436 },
    { "UnableToEmbossImage", 437 },
    { "UnableToEnhanceImage", 438 },
    { "UnableToFloodfillImage", 439 },
    { "UnableToGammaCorrectImage", 440 },
    { "UnableToGetBestIconSize", 441 },
    { "UnableToGetFromRegistry", 442 },
    { "UnableToGetPackageInfo", 443 },
    { "UnableToLevelImage", 444 },
    { "UnableToMagnifyImage", 445 },
    { "UnableToManageColor", 446 },
    { "UnableToMapImage", 447 },
    { "UnableToMapImageSequence", 448 },
    { "UnableToMedianFilterImage", 449 },
    { "UnableToMotionBlurImage", 450 },
    { "UnableToNoiseFilterImage", 451 },
    { "UnableToNormalizeImage", 452 },
    { "UnableToOpenColorProfile", 453 },
    { "UnableToQuantizeImage", 454 },
    { "UnableToQuantizeImageSequence", 455 },
    { "UnableToReadTextChunk", 456 },
    { "UnableToReadXImage", 457 },
    { "UnableToReadXServerColormap", 458 },
    { "UnableToResizeImage", 459 },
    { "UnableToRotateImage", 460 },
    { "UnableToSampleImage", 461 },
    { "UnableToScaleImage", 462 },
    { "UnableToSelectImage", 463 },
    { "UnableToSharpenImage", 464 },
    { "UnableToShaveImage", 465 },
    { "UnableToShearImage", 466 },
    { "UnableToSortImageColormap", 467 },
    { "UnableToThresholdImage", 468 },
    { "UnableToTransformColorspace", 469 },
    { "MemoryAllocationFailed", 470 },
    { "SemaporeOperationFailed", 471 },
    { "UnableToAllocateAscii85Info", 472 },
    { "UnableToAllocateCacheInfo", 473 },
    { "UnableToAllocateCacheView", 474 },
    { "UnableToAllocateColorInfo", 475 },
    { "UnableToAllocateDashPattern", 476 },
    { "UnableToAllocateDelegateInfo", 477 },
    { "UnableToAllocateDerivatives", 478 },
    { "UnableToAllocateDrawContext", 479 },
    { "UnableToAllocateDrawInfo", 480 },
    { "UnableToAllocateDrawingWand", 481 },
    { "UnableToAllocateGammaMap", 482 },
    { "UnableToAllocateImage", 483 },
    { "UnableToAllocateImagePixels", 484 },
    { "UnableToAllocateLogInfo", 485 },
    { "UnableToAllocateMagicInfo", 486 },
    { "UnableToAllocateMagickInfo", 487 },
    { "UnableToAllocateMagickMap", 488 },
    { "UnableToAllocateModuleInfo", 489 },
    { "UnableToAllocateMontageInfo", 490 },
    { "UnableToAllocateQuantizeInfo", 491 },
    { "UnableToAllocateRandomKernel", 492 },
    { "UnableToAllocateRegistryInfo", 493 },
    { "UnableToAllocateSemaphoreInfo", 494 },
    { "UnableToAllocateString", 495 },
    { "UnableToAllocateTypeInfo", 496 },
    { "UnableToAllocateWand", 497 },
    { "UnableToAnimateImageSequence", 498 },
    { "UnableToCloneBlobInfo", 499 },
    { "UnableToCloneCacheInfo", 500 },
    { "UnableToCloneImage", 501 },
    { "UnableToCloneImageInfo", 502 },
    { "UnableToConcatenateString", 503 },
    { "UnableToConvertText", 504 },
    { "UnableToCreateColormap", 505 },
    { "UnableToDestroySemaphore", 506 },
    { "UnableToDisplayImage", 507 },
    { "UnableToEscapeString", 508 },
    { "UnableToInitializeSemaphore", 509 },
    { "UnableToInterpretMSLImage", 510 },
    { "UnableToLockSemaphore", 511 },
    { "UnableToObtainRandomEntropy", 512 },
    { "UnableToUnlockSemaphore", 513 },
    { "MemoryAllocationFailed", 514 },
    { "ImageDoesNotContainTheStreamGeometry", 515 },
    { "NoStreamHandlerIsDefined", 516 },
    { "PixelCacheIsNotOpen", 517 },
    { "UnableToAcquirePixelStream", 518 },
    { "UnableToSetPixelStream", 519 },
    { "UnableToSyncPixelStream", 520 },
    { "Default", 521 },
    { "Default", 522 },
    { "FontNotSpecified", 523 },
    { "FontSubstitutionRequired", 524 },
    { "UnableToGetTypeMetrics", 525 },
    { "UnableToInitializeFreetypeLibrary", 526 },
    { "UnableToReadFont", 527 },
    { "UnrecognizedFontEncoding", 528 },
    { "Default", 529 },
    { "Default", 530 },
    { "InvalidColormapIndex", 531 },
    { "WandAPINotImplemented", 532 },
    { "WandContainsNoImageIndexs", 533 },
    { "WandContainsNoImages", 534 },
    { "ColorIsNotKnownToServer", 535 },
    { "NoWindowWithSpecifiedIDExists", 536 },
    { "StandardColormapIsNotInitialized", 537 },
    { "UnableToConnectToRemoteDisplay", 538 },
    { "UnableToCreateBitmap", 539 },
    { "UnableToCreateColormap", 540 },
    { "UnableToCreatePixmap", 541 },
    { "UnableToCreateProperty", 542 },
    { "UnableToCreateStandardColormap", 543 },
    { "UnableToDisplayImageInfo", 544 },
    { "UnableToGetProperty", 545 },
    { "UnableToGetStandardColormap", 546 },
    { "UnableToGetVisual", 547 },
    { "UnableToGrabMouse", 548 },
    { "UnableToLoadFont", 549 },
    { "UnableToMatchVisualToStandardColormap", 550 },
    { "UnableToOpenXServer", 551 },
    { "UnableToReadXAttributes", 552 },
    { "UnableToReadXWindowImage", 553 },
    { "UnrecognizedColormapType", 554 },
    { "UnrecognizedGravityType", 555 },
    { "UnrecognizedVisualSpecifier", 556 },
    { "UnableToAllocateXHints", 557 },
    { "UnableToCreateCursor", 558 },
    { "UnableToCreateGraphicContext", 559 },
    { "UnableToCreateStandardColormap", 560 },
    { "UnableToCreateTextProperty", 561 },
    { "UnableToCreateXImage", 562 },
    { "UnableToCreateXPixmap", 563 },
    { "UnableToCreateXWindow", 564 },
    { "UnableToDisplayImage", 565 },
    { "UnableToDitherImage", 566 },
    { "UnableToGetPixelInfo", 567 },
    { "UnableToGetVisual", 568 },
    { "UnableToLoadFont", 569 },
    { "UnableToMakeXWindow", 570 },
    { "UnableToOpenXServer", 571 },
    { "UnableToViewFonts", 572 },
    { "UnableToGetVisual", 573 },
    { "UsingDefaultVisual", 574 },
    { 0, 0 }
  };
#endif

#if defined(_INCLUDE_MESSAGE_TABLE_)
static const char *message_dat[] =
  {
    "%1",
    "Unable to create blob",
    "Unable to deduce image format",
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
    "Coder did not return an image (this is a bug)",
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
    "Unsupported samples per pixel",
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
    "Unable to get composite mask",
    "unable to handle image channel",
    "unable to import image pixels",
    "unable to resize image",
    "unable to segment image",
    "Unable to set clip mask",
    "Unable to set composite mask",
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
    "Font name not specified",
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

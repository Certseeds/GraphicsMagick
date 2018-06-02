#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 573

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
#define MGK_CoderErrorDeltaPNGNotSupported 35
#define MGK_CoderErrorDivisionByZero 36
#define MGK_CoderErrorEncryptedWPGImageFileNotSupported 37
#define MGK_CoderErrorFractalCompressionNotSupported 38
#define MGK_CoderErrorImageColumnOrRowSizeIsNotSupported 39
#define MGK_CoderErrorImageDoesNotHaveAMatteChannel 40
#define MGK_CoderErrorImageIsNotTiled 41
#define MGK_CoderErrorImageTypeNotSupported 42
#define MGK_CoderErrorIncompatibleSizeOfDouble 43
#define MGK_CoderErrorIrregularChannelGeometryNotSupported 44
#define MGK_CoderErrorJNGCompressionNotSupported 45
#define MGK_CoderErrorJPEGCompressionNotSupported 46
#define MGK_CoderErrorJPEGEmbeddingFailed 47
#define MGK_CoderErrorLocationTypeIsNotSupported 48
#define MGK_CoderErrorMapStorageTypeIsNotSupported 49
#define MGK_CoderErrorMSBByteOrderNotSupported 50
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 51
#define MGK_CoderErrorMultipleRecordListNotSupported 52
#define MGK_CoderErrorNo8BIMDataIsAvailable 53
#define MGK_CoderErrorNoAPP1DataIsAvailable 54
#define MGK_CoderErrorNoBitmapOnClipboard 55
#define MGK_CoderErrorNoColorProfileAvailable 56
#define MGK_CoderErrorNoDataReturned 57
#define MGK_CoderErrorNoImageVectorGraphics 58
#define MGK_CoderErrorNoIPTCInfoWasFound 59
#define MGK_CoderErrorNoIPTCProfileAvailable 60
#define MGK_CoderErrorNumberOfImagesIsNotSupported 61
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 62
#define MGK_CoderErrorOnlyLevelZerofilesSupported 63
#define MGK_CoderErrorPNGCompressionNotSupported 64
#define MGK_CoderErrorPNGLibraryTooOld 65
#define MGK_CoderErrorRLECompressionNotSupported 66
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 67
#define MGK_CoderErrorUnableToCopyProfile 68
#define MGK_CoderErrorUnableToCreateADC 69
#define MGK_CoderErrorUnableToCreateBitmap 70
#define MGK_CoderErrorUnableToDecompressImage 71
#define MGK_CoderErrorUnableToInitializeFPXLibrary 72
#define MGK_CoderErrorUnableToOpenBlob 73
#define MGK_CoderErrorUnableToReadAspectRatio 74
#define MGK_CoderErrorUnableToReadCIELABImages 75
#define MGK_CoderErrorUnableToReadSummaryInfo 76
#define MGK_CoderErrorUnableToSetAffineMatrix 77
#define MGK_CoderErrorUnableToSetAspectRatio 78
#define MGK_CoderErrorUnableToSetColorTwist 79
#define MGK_CoderErrorUnableToSetContrast 80
#define MGK_CoderErrorUnableToSetFilteringValue 81
#define MGK_CoderErrorUnableToSetImageComments 82
#define MGK_CoderErrorUnableToSetImageTitle 83
#define MGK_CoderErrorUnableToSetJPEGLevel 84
#define MGK_CoderErrorUnableToSetRegionOfInterest 85
#define MGK_CoderErrorUnableToSetSummaryInfo 86
#define MGK_CoderErrorUnableToTranslateText 87
#define MGK_CoderErrorUnableToWriteMPEGParameters 88
#define MGK_CoderErrorUnableToWriteTemporaryFile 89
#define MGK_CoderErrorUnableToZipCompressImage 90
#define MGK_CoderErrorUnsupportedBitsPerSample 91
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 92
#define MGK_CoderErrorUnsupportedSamplesPerPixel 93
#define MGK_CoderErrorWebPDecodingFailedUserAbort 94
#define MGK_CoderErrorWebPEncodingFailed 95
#define MGK_CoderErrorWebPEncodingFailedBadDimension 96
#define MGK_CoderErrorWebPEncodingFailedBadWrite 97
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 98
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 99
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 100
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 101
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 102
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 103
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 104
#define MGK_CoderErrorWebPEncodingFailedUserAbort 105
#define MGK_CoderErrorWebPInvalidConfiguration 106
#define MGK_CoderErrorWebPInvalidParameter 107
#define MGK_CoderErrorZipCompressionNotSupported 108
#define MGK_CoderFatalErrorDefault 109
#define MGK_CoderWarningLosslessToLossyJPEGConversion 110
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 111
#define MGK_ConfigureErrorRegistryKeyLookupFailed 112
#define MGK_ConfigureErrorStringTokenLengthExceeded 113
#define MGK_ConfigureErrorUnableToAccessConfigureFile 114
#define MGK_ConfigureErrorUnableToAccessFontFile 115
#define MGK_ConfigureErrorUnableToAccessLogFile 116
#define MGK_ConfigureErrorUnableToAccessModuleFile 117
#define MGK_ConfigureFatalErrorDefault 118
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 119
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 120
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 121
#define MGK_ConfigureWarningDefault 122
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 123
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 124
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 125
#define MGK_CorruptImageErrorCompressionNotValid 126
#define MGK_CorruptImageErrorCorruptImage 127
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 128
#define MGK_CorruptImageErrorImageFileHasNoScenes 129
#define MGK_CorruptImageErrorImageTypeNotSupported 130
#define MGK_CorruptImageErrorImproperImageHeader 131
#define MGK_CorruptImageErrorInsufficientImageDataInFile 132
#define MGK_CorruptImageErrorInvalidColormapIndex 133
#define MGK_CorruptImageErrorInvalidFileFormatVersion 134
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 135
#define MGK_CorruptImageErrorMissingImageChannel 136
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 137
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 138
#define MGK_CorruptImageErrorNotEnoughTiles 139
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 140
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 141
#define MGK_CorruptImageErrorTooMuchImageDataInFile 142
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 143
#define MGK_CorruptImageErrorUnableToReadColorProfile 144
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 145
#define MGK_CorruptImageErrorUnableToReadGenericProfile 146
#define MGK_CorruptImageErrorUnableToReadImageData 147
#define MGK_CorruptImageErrorUnableToReadImageHeader 148
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 149
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 150
#define MGK_CorruptImageErrorUnableToReadSubImageData 151
#define MGK_CorruptImageErrorUnableToReadVIDImage 152
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 153
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 154
#define MGK_CorruptImageErrorUnableToUncompressImage 155
#define MGK_CorruptImageErrorUnexpectedEndOfFile 156
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 157
#define MGK_CorruptImageErrorUnknownPatternType 158
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 159
#define MGK_CorruptImageErrorUnrecognizedImageCompression 160
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 161
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 162
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 163
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 164
#define MGK_CorruptImageFatalErrorUnableToPersistKey 165
#define MGK_CorruptImageWarningCompressionNotValid 166
#define MGK_CorruptImageWarningCorruptImage 167
#define MGK_CorruptImageWarningImproperImageHeader 168
#define MGK_CorruptImageWarningInvalidColormapIndex 169
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 170
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 171
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 172
#define MGK_CorruptImageWarningSkipToSyncByte 173
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 174
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 175
#define MGK_CorruptImageWarningUnrecognizedImageCompression 176
#define MGK_DelegateErrorDelegateFailed 177
#define MGK_DelegateErrorFailedToAllocateArgumentList 178
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 179
#define MGK_DelegateErrorFailedToComputeOutputSize 180
#define MGK_DelegateErrorFailedToFindGhostscript 181
#define MGK_DelegateErrorFailedToRenderFile 182
#define MGK_DelegateErrorFailedToScanFile 183
#define MGK_DelegateErrorNoTagFound 184
#define MGK_DelegateErrorPostscriptDelegateFailed 185
#define MGK_DelegateErrorUnableToCreateImage 186
#define MGK_DelegateErrorUnableToCreateImageComponent 187
#define MGK_DelegateErrorUnableToDecodeImageFile 188
#define MGK_DelegateErrorUnableToEncodeImageFile 189
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 190
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 191
#define MGK_DelegateErrorUnableToManageJP2Stream 192
#define MGK_DelegateErrorUnableToWriteSVGFormat 193
#define MGK_DelegateErrorWebPABIMismatch 194
#define MGK_DelegateFatalErrorDefault 195
#define MGK_DelegateWarningDefault 196
#define MGK_DrawErrorAlreadyPushingPatternDefinition 197
#define MGK_DrawErrorDrawingRecursionDetected 198
#define MGK_DrawErrorFloatValueConversionError 199
#define MGK_DrawErrorIntegerValueConversionError 200
#define MGK_DrawErrorInvalidPrimitiveArgument 201
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 202
#define MGK_DrawErrorPrimitiveArithmeticOverflow 203
#define MGK_DrawErrorTooManyCoordinates 204
#define MGK_DrawErrorUnableToPrint 205
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 206
#define MGK_DrawErrorUnreasonableGradientSize 207
#define MGK_DrawErrorVectorPathTruncated 208
#define MGK_DrawFatalErrorDefault 209
#define MGK_DrawWarningNotARelativeURL 210
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 211
#define MGK_DrawWarningURLNotFound 212
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 213
#define MGK_FileOpenErrorUnableToOpenFile 214
#define MGK_FileOpenErrorUnableToWriteFile 215
#define MGK_FileOpenFatalErrorDefault 216
#define MGK_FileOpenWarningDefault 217
#define MGK_ImageErrorAngleIsDiscontinuous 218
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 219
#define MGK_ImageErrorColorspaceColorProfileMismatch 220
#define MGK_ImageErrorImageColorspaceDiffers 221
#define MGK_ImageErrorImageColorspaceMismatch 222
#define MGK_ImageErrorImageDifferenceExceedsLimit 223
#define MGK_ImageErrorImageDoesNotContainResolution 224
#define MGK_ImageErrorImageIsNotColormapped 225
#define MGK_ImageErrorImageOpacityDiffers 226
#define MGK_ImageErrorImageSequenceIsRequired 227
#define MGK_ImageErrorImageSizeDiffers 228
#define MGK_ImageErrorInvalidColormapIndex 229
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 230
#define MGK_ImageErrorNoImagesWereFound 231
#define MGK_ImageErrorNoImagesWereLoaded 232
#define MGK_ImageErrorNoLocaleImageAttribute 233
#define MGK_ImageErrorTooManyClusters 234
#define MGK_ImageErrorUnableToAppendImage 235
#define MGK_ImageErrorUnableToAssignProfile 236
#define MGK_ImageErrorUnableToAverageImage 237
#define MGK_ImageErrorUnableToCoalesceImage 238
#define MGK_ImageErrorUnableToCompareImages 239
#define MGK_ImageErrorUnableToCreateImageMosaic 240
#define MGK_ImageErrorUnableToCreateStereoImage 241
#define MGK_ImageErrorUnableToDeconstructImageSequence 242
#define MGK_ImageErrorUnableToExportImagePixels 243
#define MGK_ImageErrorUnableToFlattenImage 244
#define MGK_ImageErrorUnableToGetClipMask 245
#define MGK_ImageErrorUnableToGetCompositeMask 246
#define MGK_ImageErrorUnableToHandleImageChannel 247
#define MGK_ImageErrorUnableToImportImagePixels 248
#define MGK_ImageErrorUnableToResizeImage 249
#define MGK_ImageErrorUnableToSegmentImage 250
#define MGK_ImageErrorUnableToSetClipMask 251
#define MGK_ImageErrorUnableToSetCompositeMask 252
#define MGK_ImageErrorUnableToShearImage 253
#define MGK_ImageErrorWidthOrHeightExceedsLimit 254
#define MGK_ImageFatalErrorUnableToPersistKey 255
#define MGK_ImageWarningDefault 256
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 257
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 258
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 259
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 260
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 261
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 262
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 263
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 264
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 265
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 266
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 267
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 268
#define MGK_MissingDelegateFatalErrorDefault 269
#define MGK_MissingDelegateWarningDefault 270
#define MGK_ModuleErrorFailedToCloseModule 271
#define MGK_ModuleErrorFailedToFindSymbol 272
#define MGK_ModuleErrorUnableToLoadModule 273
#define MGK_ModuleErrorUnableToRegisterImageFormat 274
#define MGK_ModuleErrorUnrecognizedModule 275
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 276
#define MGK_ModuleWarningDefault 277
#define MGK_MonitorErrorDefault 278
#define MGK_MonitorFatalErrorDefault 279
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 280
#define MGK_MonitorWarningDefault 281
#define MGK_OptionErrorBevelWidthIsNegative 282
#define MGK_OptionErrorColorSeparatedImageRequired 283
#define MGK_OptionErrorFrameIsLessThanImageSize 284
#define MGK_OptionErrorGeometryDimensionsAreZero 285
#define MGK_OptionErrorGeometryDoesNotContainImage 286
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 287
#define MGK_OptionErrorImagesAreNotTheSameSize 288
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 289
#define MGK_OptionErrorImageSmallerThanKernelWidth 290
#define MGK_OptionErrorImageSmallerThanRadius 291
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 292
#define MGK_OptionErrorInputImagesAlreadySpecified 293
#define MGK_OptionErrorInvalidSubimageSpecification 294
#define MGK_OptionErrorKernelRadiusIsTooSmall 295
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 296
#define MGK_OptionErrorMatrixIsNotSquare 297
#define MGK_OptionErrorMatrixOrderOutOfRange 298
#define MGK_OptionErrorMissingAnImageFilename 299
#define MGK_OptionErrorMissingArgument 300
#define MGK_OptionErrorMustSpecifyAnImageName 301
#define MGK_OptionErrorMustSpecifyImageSize 302
#define MGK_OptionErrorNoBlobDefined 303
#define MGK_OptionErrorNoImagesDefined 304
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 305
#define MGK_OptionErrorNoProfileNameWasGiven 306
#define MGK_OptionErrorNullBlobArgument 307
#define MGK_OptionErrorReferenceImageRequired 308
#define MGK_OptionErrorReferenceIsNotMyType 309
#define MGK_OptionErrorRegionAreaExceedsLimit 310
#define MGK_OptionErrorRequestDidNotReturnAnImage 311
#define MGK_OptionErrorSteganoImageRequired 312
#define MGK_OptionErrorStereoImageRequired 313
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 314
#define MGK_OptionErrorTileNotBoundedByImageDimensions 315
#define MGK_OptionErrorUnableToAddOrRemoveProfile 316
#define MGK_OptionErrorUnableToAverageImageSequence 317
#define MGK_OptionErrorUnableToBlurImage 318
#define MGK_OptionErrorUnableToChopImage 319
#define MGK_OptionErrorUnableToColorMatrixImage 320
#define MGK_OptionErrorUnableToConstituteImage 321
#define MGK_OptionErrorUnableToConvolveImage 322
#define MGK_OptionErrorUnableToEdgeImage 323
#define MGK_OptionErrorUnableToEqualizeImage 324
#define MGK_OptionErrorUnableToFilterImage 325
#define MGK_OptionErrorUnableToFormatImageMetadata 326
#define MGK_OptionErrorUnableToFrameImage 327
#define MGK_OptionErrorUnableToOilPaintImage 328
#define MGK_OptionErrorUnableToPaintImage 329
#define MGK_OptionErrorUnableToRaiseImage 330
#define MGK_OptionErrorUnableToSharpenImage 331
#define MGK_OptionErrorUnableToThresholdImage 332
#define MGK_OptionErrorUnableToWaveImage 333
#define MGK_OptionErrorUnrecognizedAttribute 334
#define MGK_OptionErrorUnrecognizedChannelType 335
#define MGK_OptionErrorUnrecognizedColor 336
#define MGK_OptionErrorUnrecognizedColormapType 337
#define MGK_OptionErrorUnrecognizedColorspace 338
#define MGK_OptionErrorUnrecognizedCommand 339
#define MGK_OptionErrorUnrecognizedComposeOperator 340
#define MGK_OptionErrorUnrecognizedDisposeMethod 341
#define MGK_OptionErrorUnrecognizedElement 342
#define MGK_OptionErrorUnrecognizedEndianType 343
#define MGK_OptionErrorUnrecognizedGravityType 344
#define MGK_OptionErrorUnrecognizedHighlightStyle 345
#define MGK_OptionErrorUnrecognizedImageCompression 346
#define MGK_OptionErrorUnrecognizedImageFilter 347
#define MGK_OptionErrorUnrecognizedImageFormat 348
#define MGK_OptionErrorUnrecognizedImageMode 349
#define MGK_OptionErrorUnrecognizedImageType 350
#define MGK_OptionErrorUnrecognizedIntentType 351
#define MGK_OptionErrorUnrecognizedInterlaceType 352
#define MGK_OptionErrorUnrecognizedListType 353
#define MGK_OptionErrorUnrecognizedMetric 354
#define MGK_OptionErrorUnrecognizedModeType 355
#define MGK_OptionErrorUnrecognizedNoiseType 356
#define MGK_OptionErrorUnrecognizedOperator 357
#define MGK_OptionErrorUnrecognizedOption 358
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 359
#define MGK_OptionErrorUnrecognizedPixelMap 360
#define MGK_OptionErrorUnrecognizedPreviewType 361
#define MGK_OptionErrorUnrecognizedResourceType 362
#define MGK_OptionErrorUnrecognizedType 363
#define MGK_OptionErrorUnrecognizedUnitsType 364
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 365
#define MGK_OptionErrorUnsupportedSamplingFactor 366
#define MGK_OptionErrorUsageError 367
#define MGK_OptionFatalErrorInvalidColorspaceType 368
#define MGK_OptionFatalErrorInvalidEndianType 369
#define MGK_OptionFatalErrorInvalidImageType 370
#define MGK_OptionFatalErrorInvalidInterlaceType 371
#define MGK_OptionFatalErrorMissingAnImageFilename 372
#define MGK_OptionFatalErrorMissingArgument 373
#define MGK_OptionFatalErrorNoImagesWereLoaded 374
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 375
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 376
#define MGK_OptionFatalErrorUnableToOpenXServer 377
#define MGK_OptionFatalErrorUnableToPersistKey 378
#define MGK_OptionFatalErrorUnrecognizedColormapType 379
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 380
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 381
#define MGK_OptionFatalErrorUnrecognizedEndianType 382
#define MGK_OptionFatalErrorUnrecognizedFilterType 383
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 384
#define MGK_OptionFatalErrorUnrecognizedImageType 385
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 386
#define MGK_OptionFatalErrorUnrecognizedOption 387
#define MGK_OptionFatalErrorUnrecognizedResourceType 388
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 389
#define MGK_OptionWarningUnrecognizedColor 390
#define MGK_RegistryErrorImageExpected 391
#define MGK_RegistryErrorImageInfoExpected 392
#define MGK_RegistryErrorStructureSizeMismatch 393
#define MGK_RegistryErrorUnableToGetRegistryID 394
#define MGK_RegistryErrorUnableToLocateImage 395
#define MGK_RegistryErrorUnableToSetRegistry 396
#define MGK_RegistryFatalErrorDefault 397
#define MGK_RegistryWarningDefault 398
#define MGK_ResourceLimitErrorCacheResourcesExhausted 399
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 400
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 401
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 402
#define MGK_ResourceLimitErrorMemoryAllocationFailed 403
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 404
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 405
#define MGK_ResourceLimitErrorUnableToAddColorProfile 406
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 407
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 408
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 409
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 410
#define MGK_ResourceLimitErrorUnableToAllocateColormap 411
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 412
#define MGK_ResourceLimitErrorUnableToAllocateImage 413
#define MGK_ResourceLimitErrorUnableToAllocateString 414
#define MGK_ResourceLimitErrorUnableToAnnotateImage 415
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 416
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 417
#define MGK_ResourceLimitErrorUnableToCloneImage 418
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 419
#define MGK_ResourceLimitErrorUnableToConstituteImage 420
#define MGK_ResourceLimitErrorUnableToConvertFont 421
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 422
#define MGK_ResourceLimitErrorUnableToCreateColormap 423
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 424
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 425
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 426
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 427
#define MGK_ResourceLimitErrorUnableToCreateXWindow 428
#define MGK_ResourceLimitErrorUnableToCropImage 429
#define MGK_ResourceLimitErrorUnableToDespeckleImage 430
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 431
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 432
#define MGK_ResourceLimitErrorUnableToDitherImage 433
#define MGK_ResourceLimitErrorUnableToDrawOnImage 434
#define MGK_ResourceLimitErrorUnableToEdgeImage 435
#define MGK_ResourceLimitErrorUnableToEmbossImage 436
#define MGK_ResourceLimitErrorUnableToEnhanceImage 437
#define MGK_ResourceLimitErrorUnableToFloodfillImage 438
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 439
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 440
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 441
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 442
#define MGK_ResourceLimitErrorUnableToLevelImage 443
#define MGK_ResourceLimitErrorUnableToMagnifyImage 444
#define MGK_ResourceLimitErrorUnableToManageColor 445
#define MGK_ResourceLimitErrorUnableToMapImage 446
#define MGK_ResourceLimitErrorUnableToMapImageSequence 447
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 448
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 449
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 450
#define MGK_ResourceLimitErrorUnableToNormalizeImage 451
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 452
#define MGK_ResourceLimitErrorUnableToQuantizeImage 453
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 454
#define MGK_ResourceLimitErrorUnableToReadTextChunk 455
#define MGK_ResourceLimitErrorUnableToReadXImage 456
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 457
#define MGK_ResourceLimitErrorUnableToResizeImage 458
#define MGK_ResourceLimitErrorUnableToRotateImage 459
#define MGK_ResourceLimitErrorUnableToSampleImage 460
#define MGK_ResourceLimitErrorUnableToScaleImage 461
#define MGK_ResourceLimitErrorUnableToSelectImage 462
#define MGK_ResourceLimitErrorUnableToSharpenImage 463
#define MGK_ResourceLimitErrorUnableToShaveImage 464
#define MGK_ResourceLimitErrorUnableToShearImage 465
#define MGK_ResourceLimitErrorUnableToSortImageColormap 466
#define MGK_ResourceLimitErrorUnableToThresholdImage 467
#define MGK_ResourceLimitErrorUnableToTransformColorspace 468
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 469
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 475
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 477
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 478
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 479
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 480
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 481
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 490
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 491
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 492
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 493
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 494
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 495
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 496
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 497
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 498
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 499
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 500
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 501
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 502
#define MGK_ResourceLimitFatalErrorUnableToConvertText 503
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 504
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 505
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 506
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 507
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 508
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 509
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 510
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 511
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 512
#define MGK_ResourceLimitWarningMemoryAllocationFailed 513
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 514
#define MGK_StreamErrorNoStreamHandlerIsDefined 515
#define MGK_StreamErrorPixelCacheIsNotOpen 516
#define MGK_StreamErrorUnableToAcquirePixelStream 517
#define MGK_StreamErrorUnableToSetPixelStream 518
#define MGK_StreamErrorUnableToSyncPixelStream 519
#define MGK_StreamFatalErrorDefault 520
#define MGK_StreamWarningDefault 521
#define MGK_TypeErrorFontNotSpecified 522
#define MGK_TypeErrorFontSubstitutionRequired 523
#define MGK_TypeErrorUnableToGetTypeMetrics 524
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 525
#define MGK_TypeErrorUnableToReadFont 526
#define MGK_TypeErrorUnrecognizedFontEncoding 527
#define MGK_TypeFatalErrorDefault 528
#define MGK_TypeWarningDefault 529
#define MGK_WandErrorInvalidColormapIndex 530
#define MGK_WandErrorWandAPINotImplemented 531
#define MGK_WandErrorWandContainsNoImageIndexs 532
#define MGK_WandErrorWandContainsNoImages 533
#define MGK_XServerErrorColorIsNotKnownToServer 534
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 535
#define MGK_XServerErrorStandardColormapIsNotInitialized 536
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 537
#define MGK_XServerErrorUnableToCreateBitmap 538
#define MGK_XServerErrorUnableToCreateColormap 539
#define MGK_XServerErrorUnableToCreatePixmap 540
#define MGK_XServerErrorUnableToCreateProperty 541
#define MGK_XServerErrorUnableToCreateStandardColormap 542
#define MGK_XServerErrorUnableToDisplayImageInfo 543
#define MGK_XServerErrorUnableToGetProperty 544
#define MGK_XServerErrorUnableToGetStandardColormap 545
#define MGK_XServerErrorUnableToGetVisual 546
#define MGK_XServerErrorUnableToGrabMouse 547
#define MGK_XServerErrorUnableToLoadFont 548
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 549
#define MGK_XServerErrorUnableToOpenXServer 550
#define MGK_XServerErrorUnableToReadXAttributes 551
#define MGK_XServerErrorUnableToReadXWindowImage 552
#define MGK_XServerErrorUnrecognizedColormapType 553
#define MGK_XServerErrorUnrecognizedGravityType 554
#define MGK_XServerErrorUnrecognizedVisualSpecifier 555
#define MGK_XServerFatalErrorUnableToAllocateXHints 556
#define MGK_XServerFatalErrorUnableToCreateCursor 557
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 558
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 559
#define MGK_XServerFatalErrorUnableToCreateTextProperty 560
#define MGK_XServerFatalErrorUnableToCreateXImage 561
#define MGK_XServerFatalErrorUnableToCreateXPixmap 562
#define MGK_XServerFatalErrorUnableToCreateXWindow 563
#define MGK_XServerFatalErrorUnableToDisplayImage 564
#define MGK_XServerFatalErrorUnableToDitherImage 565
#define MGK_XServerFatalErrorUnableToGetPixelInfo 566
#define MGK_XServerFatalErrorUnableToGetVisual 567
#define MGK_XServerFatalErrorUnableToLoadFont 568
#define MGK_XServerFatalErrorUnableToMakeXWindow 569
#define MGK_XServerFatalErrorUnableToOpenXServer 570
#define MGK_XServerFatalErrorUnableToViewFonts 571
#define MGK_XServerWarningUnableToGetVisual 572
#define MGK_XServerWarningUsingDefaultVisual 573

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
    { "Coder/FatalError", 108, CoderFatalError },
    { "Coder/Warning", 109, CoderWarning },
    { "Configure/Error", 110, ConfigureError },
    { "Configure/FatalError", 117, ConfigureFatalError },
    { "Configure/Warning", 121, ConfigureWarning },
    { "Corrupt/Image/Error", 122, CorruptImageError },
    { "Corrupt/Image/FatalError", 164, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 165, CorruptImageWarning },
    { "Delegate/Error", 176, DelegateError },
    { "Delegate/FatalError", 194, DelegateFatalError },
    { "Delegate/Warning", 195, DelegateWarning },
    { "Draw/Error", 196, DrawError },
    { "Draw/FatalError", 208, DrawFatalError },
    { "Draw/Warning", 209, DrawWarning },
    { "File/Open/Error", 212, FileOpenError },
    { "File/Open/FatalError", 215, FileOpenFatalError },
    { "File/Open/Warning", 216, FileOpenWarning },
    { "Image/Error", 217, ImageError },
    { "Image/FatalError", 254, ImageFatalError },
    { "Image/Warning", 255, ImageWarning },
    { "Missing/Delegate/Error", 256, MissingDelegateError },
    { "Missing/Delegate/FatalError", 268, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 269, MissingDelegateWarning },
    { "Module/Error", 270, ModuleError },
    { "Module/FatalError", 275, ModuleFatalError },
    { "Module/Warning", 276, ModuleWarning },
    { "Monitor/Error", 277, MonitorError },
    { "Monitor/FatalError", 278, MonitorFatalError },
    { "Monitor/Warning", 280, MonitorWarning },
    { "Option/Error", 281, OptionError },
    { "Option/FatalError", 367, OptionFatalError },
    { "Option/Warning", 389, OptionWarning },
    { "Registry/Error", 390, RegistryError },
    { "Registry/FatalError", 396, RegistryFatalError },
    { "Registry/Warning", 397, RegistryWarning },
    { "Resource/Limit/Error", 398, ResourceLimitError },
    { "Resource/Limit/FatalError", 468, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 512, ResourceLimitWarning },
    { "Stream/Error", 513, StreamError },
    { "Stream/FatalError", 519, StreamFatalError },
    { "Stream/Warning", 520, StreamWarning },
    { "Type/Error", 521, TypeError },
    { "Type/FatalError", 527, TypeFatalError },
    { "Type/Warning", 528, TypeWarning },
    { "Wand/Error", 529, WandError },
    { "XServer/Error", 533, XServerError },
    { "XServer/FatalError", 555, XServerFatalError },
    { "XServer/Warning", 571, XServerWarning },
    { 0, 573, UndefinedException }
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
    { "DeltaPNGNotSupported", 35 },
    { "DivisionByZero", 36 },
    { "EncryptedWPGImageFileNotSupported", 37 },
    { "FractalCompressionNotSupported", 38 },
    { "ImageColumnOrRowSizeIsNotSupported", 39 },
    { "ImageDoesNotHaveAMatteChannel", 40 },
    { "ImageIsNotTiled", 41 },
    { "ImageTypeNotSupported", 42 },
    { "IncompatibleSizeOfDouble", 43 },
    { "IrregularChannelGeometryNotSupported", 44 },
    { "JNGCompressionNotSupported", 45 },
    { "JPEGCompressionNotSupported", 46 },
    { "JPEGEmbeddingFailed", 47 },
    { "LocationTypeIsNotSupported", 48 },
    { "MapStorageTypeIsNotSupported", 49 },
    { "MSBByteOrderNotSupported", 50 },
    { "MultidimensionalMatricesAreNotSupported", 51 },
    { "MultipleRecordListNotSupported", 52 },
    { "No8BIMDataIsAvailable", 53 },
    { "NoAPP1DataIsAvailable", 54 },
    { "NoBitmapOnClipboard", 55 },
    { "NoColorProfileAvailable", 56 },
    { "NoDataReturned", 57 },
    { "NoImageVectorGraphics", 58 },
    { "NoIPTCInfoWasFound", 59 },
    { "NoIPTCProfileAvailable", 60 },
    { "NumberOfImagesIsNotSupported", 61 },
    { "OnlyContinuousTonePictureSupported", 62 },
    { "OnlyLevelZerofilesSupported", 63 },
    { "PNGCompressionNotSupported", 64 },
    { "PNGLibraryTooOld", 65 },
    { "RLECompressionNotSupported", 66 },
    { "SubsamplingRequiresEvenWidth", 67 },
    { "UnableToCopyProfile", 68 },
    { "UnableToCreateADC", 69 },
    { "UnableToCreateBitmap", 70 },
    { "UnableToDecompressImage", 71 },
    { "UnableToInitializeFPXLibrary", 72 },
    { "UnableToOpenBlob", 73 },
    { "UnableToReadAspectRatio", 74 },
    { "UnableToReadCIELABImages", 75 },
    { "UnableToReadSummaryInfo", 76 },
    { "UnableToSetAffineMatrix", 77 },
    { "UnableToSetAspectRatio", 78 },
    { "UnableToSetColorTwist", 79 },
    { "UnableToSetContrast", 80 },
    { "UnableToSetFilteringValue", 81 },
    { "UnableToSetImageComments", 82 },
    { "UnableToSetImageTitle", 83 },
    { "UnableToSetJPEGLevel", 84 },
    { "UnableToSetRegionOfInterest", 85 },
    { "UnableToSetSummaryInfo", 86 },
    { "UnableToTranslateText", 87 },
    { "UnableToWriteMPEGParameters", 88 },
    { "UnableToWriteTemporaryFile", 89 },
    { "UnableToZipCompressImage", 90 },
    { "UnsupportedBitsPerSample", 91 },
    { "UnsupportedCellTypeInTheMatrix", 92 },
    { "UnsupportedSamplesPerPixel", 93 },
    { "WebPDecodingFailedUserAbort", 94 },
    { "WebPEncodingFailed", 95 },
    { "WebPEncodingFailedBadDimension", 96 },
    { "WebPEncodingFailedBadWrite", 97 },
    { "WebPEncodingFailedBitstreamOutOfMemory", 98 },
    { "WebPEncodingFailedFileTooBig", 99 },
    { "WebPEncodingFailedInvalidConfiguration", 100 },
    { "WebPEncodingFailedNULLParameter", 101 },
    { "WebPEncodingFailedOutOfMemory", 102 },
    { "WebPEncodingFailedPartition0Overflow", 103 },
    { "WebPEncodingFailedPartitionOverflow", 104 },
    { "WebPEncodingFailedUserAbort", 105 },
    { "WebPInvalidConfiguration", 106 },
    { "WebPInvalidParameter", 107 },
    { "ZipCompressionNotSupported", 108 },
    { "Default", 109 },
    { "LosslessToLossyJPEGConversion", 110 },
    { "IncludeElementNestedTooDeeply", 111 },
    { "RegistryKeyLookupFailed", 112 },
    { "StringTokenLengthExceeded", 113 },
    { "UnableToAccessConfigureFile", 114 },
    { "UnableToAccessFontFile", 115 },
    { "UnableToAccessLogFile", 116 },
    { "UnableToAccessModuleFile", 117 },
    { "Default", 118 },
    { "UnableToChangeToWorkingDirectory", 119 },
    { "UnableToGetCurrentDirectory", 120 },
    { "UnableToRestoreCurrentDirectory", 121 },
    { "Default", 122 },
    { "AnErrorHasOccurredReadingFromFile", 123 },
    { "AnErrorHasOccurredWritingToFile", 124 },
    { "ColormapExceedsColorsLimit", 125 },
    { "CompressionNotValid", 126 },
    { "CorruptImage", 127 },
    { "ImageFileDoesNotContainAnyImageData", 128 },
    { "ImageFileHasNoScenes", 129 },
    { "ImageTypeNotSupported", 130 },
    { "ImproperImageHeader", 131 },
    { "InsufficientImageDataInFile", 132 },
    { "InvalidColormapIndex", 133 },
    { "InvalidFileFormatVersion", 134 },
    { "LengthAndFilesizeDoNotMatch", 135 },
    { "MissingImageChannel", 136 },
    { "NegativeOrZeroImageSize", 137 },
    { "NonOS2HeaderSizeError", 138 },
    { "NotEnoughTiles", 139 },
    { "StaticPlanesValueNotEqualToOne", 140 },
    { "SubsamplingRequiresEvenWidth", 141 },
    { "TooMuchImageDataInFile", 142 },
    { "UnableToReadColormapFromDumpFile", 143 },
    { "UnableToReadColorProfile", 144 },
    { "UnableToReadExtensionBlock", 145 },
    { "UnableToReadGenericProfile", 146 },
    { "UnableToReadImageData", 147 },
    { "UnableToReadImageHeader", 148 },
    { "UnableToReadIPTCProfile", 149 },
    { "UnableToReadPixmapFromDumpFile", 150 },
    { "UnableToReadSubImageData", 151 },
    { "UnableToReadVIDImage", 152 },
    { "UnableToReadWindowNameFromDumpFile", 153 },
    { "UnableToRunlengthDecodeImage", 154 },
    { "UnableToUncompressImage", 155 },
    { "UnexpectedEndOfFile", 156 },
    { "UnexpectedSamplingFactor", 157 },
    { "UnknownPatternType", 158 },
    { "UnrecognizedBitsPerPixel", 159 },
    { "UnrecognizedImageCompression", 160 },
    { "UnrecognizedNumberOfColors", 161 },
    { "UnrecognizedXWDHeader", 162 },
    { "UnsupportedBitsPerSample", 163 },
    { "UnsupportedNumberOfPlanes", 164 },
    { "UnableToPersistKey", 165 },
    { "CompressionNotValid", 166 },
    { "CorruptImage", 167 },
    { "ImproperImageHeader", 168 },
    { "InvalidColormapIndex", 169 },
    { "LengthAndFilesizeDoNotMatch", 170 },
    { "NegativeOrZeroImageSize", 171 },
    { "NonOS2HeaderSizeError", 172 },
    { "SkipToSyncByte", 173 },
    { "StaticPlanesValueNotEqualToOne", 174 },
    { "UnrecognizedBitsPerPixel", 175 },
    { "UnrecognizedImageCompression", 176 },
    { "DelegateFailed", 177 },
    { "FailedToAllocateArgumentList", 178 },
    { "FailedToAllocateGhostscriptInterpreter", 179 },
    { "FailedToComputeOutputSize", 180 },
    { "FailedToFindGhostscript", 181 },
    { "FailedToRenderFile", 182 },
    { "FailedToScanFile", 183 },
    { "NoTagFound", 184 },
    { "PostscriptDelegateFailed", 185 },
    { "UnableToCreateImage", 186 },
    { "UnableToCreateImageComponent", 187 },
    { "UnableToDecodeImageFile", 188 },
    { "UnableToEncodeImageFile", 189 },
    { "UnableToInitializeFPXLibrary", 190 },
    { "UnableToInitializeWMFLibrary", 191 },
    { "UnableToManageJP2Stream", 192 },
    { "UnableToWriteSVGFormat", 193 },
    { "WebPABIMismatch", 194 },
    { "Default", 195 },
    { "Default", 196 },
    { "AlreadyPushingPatternDefinition", 197 },
    { "DrawingRecursionDetected", 198 },
    { "FloatValueConversionError", 199 },
    { "IntegerValueConversionError", 200 },
    { "InvalidPrimitiveArgument", 201 },
    { "NonconformingDrawingPrimitiveDefinition", 202 },
    { "PrimitiveArithmeticOverflow", 203 },
    { "TooManyCoordinates", 204 },
    { "UnableToPrint", 205 },
    { "UnbalancedGraphicContextPushPop", 206 },
    { "UnreasonableGradientSize", 207 },
    { "VectorPathTruncated", 208 },
    { "Default", 209 },
    { "NotARelativeURL", 210 },
    { "NotCurrentlyPushingPatternDefinition", 211 },
    { "URLNotFound", 212 },
    { "UnableToCreateTemporaryFile", 213 },
    { "UnableToOpenFile", 214 },
    { "UnableToWriteFile", 215 },
    { "Default", 216 },
    { "Default", 217 },
    { "AngleIsDiscontinuous", 218 },
    { "CMYKAImageLacksAlphaChannel", 219 },
    { "ColorspaceColorProfileMismatch", 220 },
    { "ImageColorspaceDiffers", 221 },
    { "ImageColorspaceMismatch", 222 },
    { "ImageDifferenceExceedsLimit", 223 },
    { "ImageDoesNotContainResolution", 224 },
    { "ImageIsNotColormapped", 225 },
    { "ImageOpacityDiffers", 226 },
    { "ImageSequenceIsRequired", 227 },
    { "ImageSizeDiffers", 228 },
    { "InvalidColormapIndex", 229 },
    { "LeftAndRightImageSizesDiffer", 230 },
    { "NoImagesWereFound", 231 },
    { "NoImagesWereLoaded", 232 },
    { "NoLocaleImageAttribute", 233 },
    { "TooManyClusters", 234 },
    { "UnableToAppendImage", 235 },
    { "UnableToAssignProfile", 236 },
    { "UnableToAverageImage", 237 },
    { "UnableToCoalesceImage", 238 },
    { "UnableToCompareImages", 239 },
    { "UnableToCreateImageMosaic", 240 },
    { "UnableToCreateStereoImage", 241 },
    { "UnableToDeconstructImageSequence", 242 },
    { "UnableToExportImagePixels", 243 },
    { "UnableToFlattenImage", 244 },
    { "UnableToGetClipMask", 245 },
    { "UnableToGetCompositeMask", 246 },
    { "UnableToHandleImageChannel", 247 },
    { "UnableToImportImagePixels", 248 },
    { "UnableToResizeImage", 249 },
    { "UnableToSegmentImage", 250 },
    { "UnableToSetClipMask", 251 },
    { "UnableToSetCompositeMask", 252 },
    { "UnableToShearImage", 253 },
    { "WidthOrHeightExceedsLimit", 254 },
    { "UnableToPersistKey", 255 },
    { "Default", 256 },
    { "DPSLibraryIsNotAvailable", 257 },
    { "FPXLibraryIsNotAvailable", 258 },
    { "FreeTypeLibraryIsNotAvailable", 259 },
    { "JPEGLibraryIsNotAvailable", 260 },
    { "LCMSLibraryIsNotAvailable", 261 },
    { "LZWEncodingNotEnabled", 262 },
    { "NoDecodeDelegateForThisImageFormat", 263 },
    { "NoEncodeDelegateForThisImageFormat", 264 },
    { "TIFFLibraryIsNotAvailable", 265 },
    { "XMLLibraryIsNotAvailable", 266 },
    { "XWindowLibraryIsNotAvailable", 267 },
    { "ZipLibraryIsNotAvailable", 268 },
    { "Default", 269 },
    { "Default", 270 },
    { "FailedToCloseModule", 271 },
    { "FailedToFindSymbol", 272 },
    { "UnableToLoadModule", 273 },
    { "UnableToRegisterImageFormat", 274 },
    { "UnrecognizedModule", 275 },
    { "UnableToInitializeModuleLoader", 276 },
    { "Default", 277 },
    { "Default", 278 },
    { "Default", 279 },
    { "UserRequestedTerminationBySignal", 280 },
    { "Default", 281 },
    { "BevelWidthIsNegative", 282 },
    { "ColorSeparatedImageRequired", 283 },
    { "FrameIsLessThanImageSize", 284 },
    { "GeometryDimensionsAreZero", 285 },
    { "GeometryDoesNotContainImage", 286 },
    { "HaldClutImageDimensionsInvalid", 287 },
    { "ImagesAreNotTheSameSize", 288 },
    { "ImageSizeMustExceedBevelWidth", 289 },
    { "ImageSmallerThanKernelWidth", 290 },
    { "ImageSmallerThanRadius", 291 },
    { "ImageWidthsOrHeightsDiffer", 292 },
    { "InputImagesAlreadySpecified", 293 },
    { "InvalidSubimageSpecification", 294 },
    { "KernelRadiusIsTooSmall", 295 },
    { "KernelWidthMustBeAnOddNumber", 296 },
    { "MatrixIsNotSquare", 297 },
    { "MatrixOrderOutOfRange", 298 },
    { "MissingAnImageFilename", 299 },
    { "MissingArgument", 300 },
    { "MustSpecifyAnImageName", 301 },
    { "MustSpecifyImageSize", 302 },
    { "NoBlobDefined", 303 },
    { "NoImagesDefined", 304 },
    { "NonzeroWidthAndHeightRequired", 305 },
    { "NoProfileNameWasGiven", 306 },
    { "NullBlobArgument", 307 },
    { "ReferenceImageRequired", 308 },
    { "ReferenceIsNotMyType", 309 },
    { "RegionAreaExceedsLimit", 310 },
    { "RequestDidNotReturnAnImage", 311 },
    { "SteganoImageRequired", 312 },
    { "StereoImageRequired", 313 },
    { "SubimageSpecificationReturnsNoImages", 314 },
    { "TileNotBoundedByImageDimensions", 315 },
    { "UnableToAddOrRemoveProfile", 316 },
    { "UnableToAverageImageSequence", 317 },
    { "UnableToBlurImage", 318 },
    { "UnableToChopImage", 319 },
    { "UnableToColorMatrixImage", 320 },
    { "UnableToConstituteImage", 321 },
    { "UnableToConvolveImage", 322 },
    { "UnableToEdgeImage", 323 },
    { "UnableToEqualizeImage", 324 },
    { "UnableToFilterImage", 325 },
    { "UnableToFormatImageMetadata", 326 },
    { "UnableToFrameImage", 327 },
    { "UnableToOilPaintImage", 328 },
    { "UnableToPaintImage", 329 },
    { "UnableToRaiseImage", 330 },
    { "UnableToSharpenImage", 331 },
    { "UnableToThresholdImage", 332 },
    { "UnableToWaveImage", 333 },
    { "UnrecognizedAttribute", 334 },
    { "UnrecognizedChannelType", 335 },
    { "UnrecognizedColor", 336 },
    { "UnrecognizedColormapType", 337 },
    { "UnrecognizedColorspace", 338 },
    { "UnrecognizedCommand", 339 },
    { "UnrecognizedComposeOperator", 340 },
    { "UnrecognizedDisposeMethod", 341 },
    { "UnrecognizedElement", 342 },
    { "UnrecognizedEndianType", 343 },
    { "UnrecognizedGravityType", 344 },
    { "UnrecognizedHighlightStyle", 345 },
    { "UnrecognizedImageCompression", 346 },
    { "UnrecognizedImageFilter", 347 },
    { "UnrecognizedImageFormat", 348 },
    { "UnrecognizedImageMode", 349 },
    { "UnrecognizedImageType", 350 },
    { "UnrecognizedIntentType", 351 },
    { "UnrecognizedInterlaceType", 352 },
    { "UnrecognizedListType", 353 },
    { "UnrecognizedMetric", 354 },
    { "UnrecognizedModeType", 355 },
    { "UnrecognizedNoiseType", 356 },
    { "UnrecognizedOperator", 357 },
    { "UnrecognizedOption", 358 },
    { "UnrecognizedPerlMagickMethod", 359 },
    { "UnrecognizedPixelMap", 360 },
    { "UnrecognizedPreviewType", 361 },
    { "UnrecognizedResourceType", 362 },
    { "UnrecognizedType", 363 },
    { "UnrecognizedUnitsType", 364 },
    { "UnrecognizedVirtualPixelMethod", 365 },
    { "UnsupportedSamplingFactor", 366 },
    { "UsageError", 367 },
    { "InvalidColorspaceType", 368 },
    { "InvalidEndianType", 369 },
    { "InvalidImageType", 370 },
    { "InvalidInterlaceType", 371 },
    { "MissingAnImageFilename", 372 },
    { "MissingArgument", 373 },
    { "NoImagesWereLoaded", 374 },
    { "OptionLengthExceedsLimit", 375 },
    { "RequestDidNotReturnAnImage", 376 },
    { "UnableToOpenXServer", 377 },
    { "UnableToPersistKey", 378 },
    { "UnrecognizedColormapType", 379 },
    { "UnrecognizedColorspaceType", 380 },
    { "UnrecognizedDisposeMethod", 381 },
    { "UnrecognizedEndianType", 382 },
    { "UnrecognizedFilterType", 383 },
    { "UnrecognizedImageCompressionType", 384 },
    { "UnrecognizedImageType", 385 },
    { "UnrecognizedInterlaceType", 386 },
    { "UnrecognizedOption", 387 },
    { "UnrecognizedResourceType", 388 },
    { "UnrecognizedVirtualPixelMethod", 389 },
    { "UnrecognizedColor", 390 },
    { "ImageExpected", 391 },
    { "ImageInfoExpected", 392 },
    { "StructureSizeMismatch", 393 },
    { "UnableToGetRegistryID", 394 },
    { "UnableToLocateImage", 395 },
    { "UnableToSetRegistry", 396 },
    { "Default", 397 },
    { "Default", 398 },
    { "CacheResourcesExhausted", 399 },
    { "ImagePixelHeightLimitExceeded", 400 },
    { "ImagePixelLimitExceeded", 401 },
    { "ImagePixelWidthLimitExceeded", 402 },
    { "MemoryAllocationFailed", 403 },
    { "NoPixelsDefinedInCache", 404 },
    { "PixelCacheAllocationFailed", 405 },
    { "UnableToAddColorProfile", 406 },
    { "UnableToAddGenericProfile", 407 },
    { "UnableToAddIPTCProfile", 408 },
    { "UnableToAddOrRemoveProfile", 409 },
    { "UnableToAllocateCoefficients", 410 },
    { "UnableToAllocateColormap", 411 },
    { "UnableToAllocateICCProfile", 412 },
    { "UnableToAllocateImage", 413 },
    { "UnableToAllocateString", 414 },
    { "UnableToAnnotateImage", 415 },
    { "UnableToAverageImageSequence", 416 },
    { "UnableToCloneDrawingWand", 417 },
    { "UnableToCloneImage", 418 },
    { "UnableToComputeImageSignature", 419 },
    { "UnableToConstituteImage", 420 },
    { "UnableToConvertFont", 421 },
    { "UnableToConvertStringToTokens", 422 },
    { "UnableToCreateColormap", 423 },
    { "UnableToCreateColorTransform", 424 },
    { "UnableToCreateCommandWidget", 425 },
    { "UnableToCreateImageGroup", 426 },
    { "UnableToCreateImageMontage", 427 },
    { "UnableToCreateXWindow", 428 },
    { "UnableToCropImage", 429 },
    { "UnableToDespeckleImage", 430 },
    { "UnableToDetermineImageClass", 431 },
    { "UnableToDetermineTheNumberOfImageColors", 432 },
    { "UnableToDitherImage", 433 },
    { "UnableToDrawOnImage", 434 },
    { "UnableToEdgeImage", 435 },
    { "UnableToEmbossImage", 436 },
    { "UnableToEnhanceImage", 437 },
    { "UnableToFloodfillImage", 438 },
    { "UnableToGammaCorrectImage", 439 },
    { "UnableToGetBestIconSize", 440 },
    { "UnableToGetFromRegistry", 441 },
    { "UnableToGetPackageInfo", 442 },
    { "UnableToLevelImage", 443 },
    { "UnableToMagnifyImage", 444 },
    { "UnableToManageColor", 445 },
    { "UnableToMapImage", 446 },
    { "UnableToMapImageSequence", 447 },
    { "UnableToMedianFilterImage", 448 },
    { "UnableToMotionBlurImage", 449 },
    { "UnableToNoiseFilterImage", 450 },
    { "UnableToNormalizeImage", 451 },
    { "UnableToOpenColorProfile", 452 },
    { "UnableToQuantizeImage", 453 },
    { "UnableToQuantizeImageSequence", 454 },
    { "UnableToReadTextChunk", 455 },
    { "UnableToReadXImage", 456 },
    { "UnableToReadXServerColormap", 457 },
    { "UnableToResizeImage", 458 },
    { "UnableToRotateImage", 459 },
    { "UnableToSampleImage", 460 },
    { "UnableToScaleImage", 461 },
    { "UnableToSelectImage", 462 },
    { "UnableToSharpenImage", 463 },
    { "UnableToShaveImage", 464 },
    { "UnableToShearImage", 465 },
    { "UnableToSortImageColormap", 466 },
    { "UnableToThresholdImage", 467 },
    { "UnableToTransformColorspace", 468 },
    { "MemoryAllocationFailed", 469 },
    { "SemaporeOperationFailed", 470 },
    { "UnableToAllocateAscii85Info", 471 },
    { "UnableToAllocateCacheInfo", 472 },
    { "UnableToAllocateCacheView", 473 },
    { "UnableToAllocateColorInfo", 474 },
    { "UnableToAllocateDashPattern", 475 },
    { "UnableToAllocateDelegateInfo", 476 },
    { "UnableToAllocateDerivatives", 477 },
    { "UnableToAllocateDrawContext", 478 },
    { "UnableToAllocateDrawInfo", 479 },
    { "UnableToAllocateDrawingWand", 480 },
    { "UnableToAllocateGammaMap", 481 },
    { "UnableToAllocateImage", 482 },
    { "UnableToAllocateImagePixels", 483 },
    { "UnableToAllocateLogInfo", 484 },
    { "UnableToAllocateMagicInfo", 485 },
    { "UnableToAllocateMagickInfo", 486 },
    { "UnableToAllocateMagickMap", 487 },
    { "UnableToAllocateModuleInfo", 488 },
    { "UnableToAllocateMontageInfo", 489 },
    { "UnableToAllocateQuantizeInfo", 490 },
    { "UnableToAllocateRandomKernel", 491 },
    { "UnableToAllocateRegistryInfo", 492 },
    { "UnableToAllocateSemaphoreInfo", 493 },
    { "UnableToAllocateString", 494 },
    { "UnableToAllocateTypeInfo", 495 },
    { "UnableToAllocateWand", 496 },
    { "UnableToAnimateImageSequence", 497 },
    { "UnableToCloneBlobInfo", 498 },
    { "UnableToCloneCacheInfo", 499 },
    { "UnableToCloneImage", 500 },
    { "UnableToCloneImageInfo", 501 },
    { "UnableToConcatenateString", 502 },
    { "UnableToConvertText", 503 },
    { "UnableToCreateColormap", 504 },
    { "UnableToDestroySemaphore", 505 },
    { "UnableToDisplayImage", 506 },
    { "UnableToEscapeString", 507 },
    { "UnableToInitializeSemaphore", 508 },
    { "UnableToInterpretMSLImage", 509 },
    { "UnableToLockSemaphore", 510 },
    { "UnableToObtainRandomEntropy", 511 },
    { "UnableToUnlockSemaphore", 512 },
    { "MemoryAllocationFailed", 513 },
    { "ImageDoesNotContainTheStreamGeometry", 514 },
    { "NoStreamHandlerIsDefined", 515 },
    { "PixelCacheIsNotOpen", 516 },
    { "UnableToAcquirePixelStream", 517 },
    { "UnableToSetPixelStream", 518 },
    { "UnableToSyncPixelStream", 519 },
    { "Default", 520 },
    { "Default", 521 },
    { "FontNotSpecified", 522 },
    { "FontSubstitutionRequired", 523 },
    { "UnableToGetTypeMetrics", 524 },
    { "UnableToInitializeFreetypeLibrary", 525 },
    { "UnableToReadFont", 526 },
    { "UnrecognizedFontEncoding", 527 },
    { "Default", 528 },
    { "Default", 529 },
    { "InvalidColormapIndex", 530 },
    { "WandAPINotImplemented", 531 },
    { "WandContainsNoImageIndexs", 532 },
    { "WandContainsNoImages", 533 },
    { "ColorIsNotKnownToServer", 534 },
    { "NoWindowWithSpecifiedIDExists", 535 },
    { "StandardColormapIsNotInitialized", 536 },
    { "UnableToConnectToRemoteDisplay", 537 },
    { "UnableToCreateBitmap", 538 },
    { "UnableToCreateColormap", 539 },
    { "UnableToCreatePixmap", 540 },
    { "UnableToCreateProperty", 541 },
    { "UnableToCreateStandardColormap", 542 },
    { "UnableToDisplayImageInfo", 543 },
    { "UnableToGetProperty", 544 },
    { "UnableToGetStandardColormap", 545 },
    { "UnableToGetVisual", 546 },
    { "UnableToGrabMouse", 547 },
    { "UnableToLoadFont", 548 },
    { "UnableToMatchVisualToStandardColormap", 549 },
    { "UnableToOpenXServer", 550 },
    { "UnableToReadXAttributes", 551 },
    { "UnableToReadXWindowImage", 552 },
    { "UnrecognizedColormapType", 553 },
    { "UnrecognizedGravityType", 554 },
    { "UnrecognizedVisualSpecifier", 555 },
    { "UnableToAllocateXHints", 556 },
    { "UnableToCreateCursor", 557 },
    { "UnableToCreateGraphicContext", 558 },
    { "UnableToCreateStandardColormap", 559 },
    { "UnableToCreateTextProperty", 560 },
    { "UnableToCreateXImage", 561 },
    { "UnableToCreateXPixmap", 562 },
    { "UnableToCreateXWindow", 563 },
    { "UnableToDisplayImage", 564 },
    { "UnableToDitherImage", 565 },
    { "UnableToGetPixelInfo", 566 },
    { "UnableToGetVisual", 567 },
    { "UnableToLoadFont", 568 },
    { "UnableToMakeXWindow", 569 },
    { "UnableToOpenXServer", 570 },
    { "UnableToViewFonts", 571 },
    { "UnableToGetVisual", 572 },
    { "UsingDefaultVisual", 573 },
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

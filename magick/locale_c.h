#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 566

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
#define MGK_CoderErrorColormapTooLarge 26
#define MGK_CoderErrorColormapTypeNotSupported 27
#define MGK_CoderErrorColorspaceModelIsNotSupported 28
#define MGK_CoderErrorColorTypeNotSupported 29
#define MGK_CoderErrorCompressionNotValid 30
#define MGK_CoderErrorDataEncodingSchemeIsNotSupported 31
#define MGK_CoderErrorDataStorageTypeIsNotSupported 32
#define MGK_CoderErrorDeltaPNGNotSupported 33
#define MGK_CoderErrorEncryptedWPGImageFileNotSupported 34
#define MGK_CoderErrorFractalCompressionNotSupported 35
#define MGK_CoderErrorImageColumnOrRowSizeIsNotSupported 36
#define MGK_CoderErrorImageDoesNotHaveAMatteChannel 37
#define MGK_CoderErrorImageIsNotTiled 38
#define MGK_CoderErrorImageTypeNotSupported 39
#define MGK_CoderErrorIncompatibleSizeOfDouble 40
#define MGK_CoderErrorIrregularChannelGeometryNotSupported 41
#define MGK_CoderErrorJNGCompressionNotSupported 42
#define MGK_CoderErrorJPEGCompressionNotSupported 43
#define MGK_CoderErrorJPEGEmbeddingFailed 44
#define MGK_CoderErrorLocationTypeIsNotSupported 45
#define MGK_CoderErrorMapStorageTypeIsNotSupported 46
#define MGK_CoderErrorMSBByteOrderNotSupported 47
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 48
#define MGK_CoderErrorMultipleRecordListNotSupported 49
#define MGK_CoderErrorNo8BIMDataIsAvailable 50
#define MGK_CoderErrorNoAPP1DataIsAvailable 51
#define MGK_CoderErrorNoBitmapOnClipboard 52
#define MGK_CoderErrorNoColorProfileAvailable 53
#define MGK_CoderErrorNoDataReturned 54
#define MGK_CoderErrorNoImageVectorGraphics 55
#define MGK_CoderErrorNoIPTCInfoWasFound 56
#define MGK_CoderErrorNoIPTCProfileAvailable 57
#define MGK_CoderErrorNumberOfImagesIsNotSupported 58
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 59
#define MGK_CoderErrorOnlyLevelZerofilesSupported 60
#define MGK_CoderErrorPNGCompressionNotSupported 61
#define MGK_CoderErrorPNGLibraryTooOld 62
#define MGK_CoderErrorRLECompressionNotSupported 63
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 64
#define MGK_CoderErrorUnableToCopyProfile 65
#define MGK_CoderErrorUnableToCreateADC 66
#define MGK_CoderErrorUnableToCreateBitmap 67
#define MGK_CoderErrorUnableToDecompressImage 68
#define MGK_CoderErrorUnableToInitializeFPXLibrary 69
#define MGK_CoderErrorUnableToOpenBlob 70
#define MGK_CoderErrorUnableToReadAspectRatio 71
#define MGK_CoderErrorUnableToReadCIELABImages 72
#define MGK_CoderErrorUnableToReadSummaryInfo 73
#define MGK_CoderErrorUnableToSetAffineMatrix 74
#define MGK_CoderErrorUnableToSetAspectRatio 75
#define MGK_CoderErrorUnableToSetColorTwist 76
#define MGK_CoderErrorUnableToSetContrast 77
#define MGK_CoderErrorUnableToSetFilteringValue 78
#define MGK_CoderErrorUnableToSetImageComments 79
#define MGK_CoderErrorUnableToSetImageTitle 80
#define MGK_CoderErrorUnableToSetJPEGLevel 81
#define MGK_CoderErrorUnableToSetRegionOfInterest 82
#define MGK_CoderErrorUnableToSetSummaryInfo 83
#define MGK_CoderErrorUnableToTranslateText 84
#define MGK_CoderErrorUnableToWriteMPEGParameters 85
#define MGK_CoderErrorUnableToWriteTemporaryFile 86
#define MGK_CoderErrorUnableToZipCompressImage 87
#define MGK_CoderErrorUnsupportedBitsPerSample 88
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 89
#define MGK_CoderErrorWebPDecodingFailedUserAbort 90
#define MGK_CoderErrorWebPEncodingFailed 91
#define MGK_CoderErrorWebPEncodingFailedBadDimension 92
#define MGK_CoderErrorWebPEncodingFailedBadWrite 93
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 94
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 95
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 96
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 97
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 98
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 99
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 100
#define MGK_CoderErrorWebPEncodingFailedUserAbort 101
#define MGK_CoderErrorWebPInvalidConfiguration 102
#define MGK_CoderErrorWebPInvalidParameter 103
#define MGK_CoderErrorZipCompressionNotSupported 104
#define MGK_CoderFatalErrorDefault 105
#define MGK_CoderWarningLosslessToLossyJPEGConversion 106
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 107
#define MGK_ConfigureErrorRegistryKeyLookupFailed 108
#define MGK_ConfigureErrorStringTokenLengthExceeded 109
#define MGK_ConfigureErrorUnableToAccessConfigureFile 110
#define MGK_ConfigureErrorUnableToAccessFontFile 111
#define MGK_ConfigureErrorUnableToAccessLogFile 112
#define MGK_ConfigureErrorUnableToAccessModuleFile 113
#define MGK_ConfigureFatalErrorDefault 114
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 115
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 116
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 117
#define MGK_ConfigureWarningDefault 118
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 119
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 120
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 121
#define MGK_CorruptImageErrorCompressionNotValid 122
#define MGK_CorruptImageErrorCorruptImage 123
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 124
#define MGK_CorruptImageErrorImageFileHasNoScenes 125
#define MGK_CorruptImageErrorImageTypeNotSupported 126
#define MGK_CorruptImageErrorImproperImageHeader 127
#define MGK_CorruptImageErrorInsufficientImageDataInFile 128
#define MGK_CorruptImageErrorInvalidColormapIndex 129
#define MGK_CorruptImageErrorInvalidFileFormatVersion 130
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 131
#define MGK_CorruptImageErrorMissingImageChannel 132
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 133
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 134
#define MGK_CorruptImageErrorNotEnoughTiles 135
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 136
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 137
#define MGK_CorruptImageErrorTooMuchImageDataInFile 138
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 139
#define MGK_CorruptImageErrorUnableToReadColorProfile 140
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 141
#define MGK_CorruptImageErrorUnableToReadGenericProfile 142
#define MGK_CorruptImageErrorUnableToReadImageData 143
#define MGK_CorruptImageErrorUnableToReadImageHeader 144
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 145
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 146
#define MGK_CorruptImageErrorUnableToReadSubImageData 147
#define MGK_CorruptImageErrorUnableToReadVIDImage 148
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 149
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 150
#define MGK_CorruptImageErrorUnableToUncompressImage 151
#define MGK_CorruptImageErrorUnexpectedEndOfFile 152
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 153
#define MGK_CorruptImageErrorUnknownPatternType 154
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 155
#define MGK_CorruptImageErrorUnrecognizedImageCompression 156
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 157
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 158
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 159
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 160
#define MGK_CorruptImageFatalErrorUnableToPersistKey 161
#define MGK_CorruptImageWarningCompressionNotValid 162
#define MGK_CorruptImageWarningCorruptImage 163
#define MGK_CorruptImageWarningImproperImageHeader 164
#define MGK_CorruptImageWarningInvalidColormapIndex 165
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 166
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 167
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 168
#define MGK_CorruptImageWarningSkipToSyncByte 169
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 170
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 171
#define MGK_CorruptImageWarningUnrecognizedImageCompression 172
#define MGK_DelegateErrorDelegateFailed 173
#define MGK_DelegateErrorFailedToAllocateArgumentList 174
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 175
#define MGK_DelegateErrorFailedToComputeOutputSize 176
#define MGK_DelegateErrorFailedToFindGhostscript 177
#define MGK_DelegateErrorFailedToRenderFile 178
#define MGK_DelegateErrorFailedToScanFile 179
#define MGK_DelegateErrorNoTagFound 180
#define MGK_DelegateErrorPostscriptDelegateFailed 181
#define MGK_DelegateErrorUnableToCreateImage 182
#define MGK_DelegateErrorUnableToCreateImageComponent 183
#define MGK_DelegateErrorUnableToDecodeImageFile 184
#define MGK_DelegateErrorUnableToEncodeImageFile 185
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 186
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 187
#define MGK_DelegateErrorUnableToManageJP2Stream 188
#define MGK_DelegateErrorUnableToWriteSVGFormat 189
#define MGK_DelegateErrorWebPABIMismatch 190
#define MGK_DelegateFatalErrorDefault 191
#define MGK_DelegateWarningDefault 192
#define MGK_DrawErrorAlreadyPushingPatternDefinition 193
#define MGK_DrawErrorDrawingRecursionDetected 194
#define MGK_DrawErrorFloatValueConversionError 195
#define MGK_DrawErrorIntegerValueConversionError 196
#define MGK_DrawErrorInvalidPrimitiveArgument 197
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 198
#define MGK_DrawErrorPrimitiveArithmeticOverflow 199
#define MGK_DrawErrorTooManyCoordinates 200
#define MGK_DrawErrorUnableToPrint 201
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 202
#define MGK_DrawErrorUnreasonableGradientSize 203
#define MGK_DrawErrorVectorPathTruncated 204
#define MGK_DrawFatalErrorDefault 205
#define MGK_DrawWarningNotARelativeURL 206
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 207
#define MGK_DrawWarningURLNotFound 208
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 209
#define MGK_FileOpenErrorUnableToOpenFile 210
#define MGK_FileOpenErrorUnableToWriteFile 211
#define MGK_FileOpenFatalErrorDefault 212
#define MGK_FileOpenWarningDefault 213
#define MGK_ImageErrorAngleIsDiscontinuous 214
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 215
#define MGK_ImageErrorColorspaceColorProfileMismatch 216
#define MGK_ImageErrorImageColorspaceDiffers 217
#define MGK_ImageErrorImageColorspaceMismatch 218
#define MGK_ImageErrorImageDifferenceExceedsLimit 219
#define MGK_ImageErrorImageDoesNotContainResolution 220
#define MGK_ImageErrorImageIsNotColormapped 221
#define MGK_ImageErrorImageOpacityDiffers 222
#define MGK_ImageErrorImageSequenceIsRequired 223
#define MGK_ImageErrorImageSizeDiffers 224
#define MGK_ImageErrorInvalidColormapIndex 225
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 226
#define MGK_ImageErrorNoImagesWereFound 227
#define MGK_ImageErrorNoImagesWereLoaded 228
#define MGK_ImageErrorNoLocaleImageAttribute 229
#define MGK_ImageErrorTooManyClusters 230
#define MGK_ImageErrorUnableToAppendImage 231
#define MGK_ImageErrorUnableToAssignProfile 232
#define MGK_ImageErrorUnableToAverageImage 233
#define MGK_ImageErrorUnableToCoalesceImage 234
#define MGK_ImageErrorUnableToCompareImages 235
#define MGK_ImageErrorUnableToCreateImageMosaic 236
#define MGK_ImageErrorUnableToCreateStereoImage 237
#define MGK_ImageErrorUnableToDeconstructImageSequence 238
#define MGK_ImageErrorUnableToExportImagePixels 239
#define MGK_ImageErrorUnableToFlattenImage 240
#define MGK_ImageErrorUnableToGetClipMask 241
#define MGK_ImageErrorUnableToHandleImageChannel 242
#define MGK_ImageErrorUnableToImportImagePixels 243
#define MGK_ImageErrorUnableToResizeImage 244
#define MGK_ImageErrorUnableToSegmentImage 245
#define MGK_ImageErrorUnableToSetClipMask 246
#define MGK_ImageErrorUnableToShearImage 247
#define MGK_ImageErrorWidthOrHeightExceedsLimit 248
#define MGK_ImageFatalErrorUnableToPersistKey 249
#define MGK_ImageWarningDefault 250
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 251
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 252
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 253
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 254
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 255
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 256
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 257
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 258
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 259
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 260
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 261
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 262
#define MGK_MissingDelegateFatalErrorDefault 263
#define MGK_MissingDelegateWarningDefault 264
#define MGK_ModuleErrorFailedToCloseModule 265
#define MGK_ModuleErrorFailedToFindSymbol 266
#define MGK_ModuleErrorUnableToLoadModule 267
#define MGK_ModuleErrorUnableToRegisterImageFormat 268
#define MGK_ModuleErrorUnrecognizedModule 269
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 270
#define MGK_ModuleWarningDefault 271
#define MGK_MonitorErrorDefault 272
#define MGK_MonitorFatalErrorDefault 273
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 274
#define MGK_MonitorWarningDefault 275
#define MGK_OptionErrorBevelWidthIsNegative 276
#define MGK_OptionErrorColorSeparatedImageRequired 277
#define MGK_OptionErrorFrameIsLessThanImageSize 278
#define MGK_OptionErrorGeometryDimensionsAreZero 279
#define MGK_OptionErrorGeometryDoesNotContainImage 280
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 281
#define MGK_OptionErrorImagesAreNotTheSameSize 282
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 283
#define MGK_OptionErrorImageSmallerThanKernelWidth 284
#define MGK_OptionErrorImageSmallerThanRadius 285
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 286
#define MGK_OptionErrorInputImagesAlreadySpecified 287
#define MGK_OptionErrorInvalidSubimageSpecification 288
#define MGK_OptionErrorKernelRadiusIsTooSmall 289
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 290
#define MGK_OptionErrorMatrixIsNotSquare 291
#define MGK_OptionErrorMatrixOrderOutOfRange 292
#define MGK_OptionErrorMissingAnImageFilename 293
#define MGK_OptionErrorMissingArgument 294
#define MGK_OptionErrorMustSpecifyAnImageName 295
#define MGK_OptionErrorMustSpecifyImageSize 296
#define MGK_OptionErrorNoBlobDefined 297
#define MGK_OptionErrorNoImagesDefined 298
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 299
#define MGK_OptionErrorNoProfileNameWasGiven 300
#define MGK_OptionErrorNullBlobArgument 301
#define MGK_OptionErrorReferenceImageRequired 302
#define MGK_OptionErrorReferenceIsNotMyType 303
#define MGK_OptionErrorRegionAreaExceedsLimit 304
#define MGK_OptionErrorRequestDidNotReturnAnImage 305
#define MGK_OptionErrorSteganoImageRequired 306
#define MGK_OptionErrorStereoImageRequired 307
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 308
#define MGK_OptionErrorTileNotBoundedByImageDimensions 309
#define MGK_OptionErrorUnableToAddOrRemoveProfile 310
#define MGK_OptionErrorUnableToAverageImageSequence 311
#define MGK_OptionErrorUnableToBlurImage 312
#define MGK_OptionErrorUnableToChopImage 313
#define MGK_OptionErrorUnableToColorMatrixImage 314
#define MGK_OptionErrorUnableToConstituteImage 315
#define MGK_OptionErrorUnableToConvolveImage 316
#define MGK_OptionErrorUnableToEdgeImage 317
#define MGK_OptionErrorUnableToEqualizeImage 318
#define MGK_OptionErrorUnableToFilterImage 319
#define MGK_OptionErrorUnableToFormatImageMetadata 320
#define MGK_OptionErrorUnableToFrameImage 321
#define MGK_OptionErrorUnableToOilPaintImage 322
#define MGK_OptionErrorUnableToPaintImage 323
#define MGK_OptionErrorUnableToRaiseImage 324
#define MGK_OptionErrorUnableToSharpenImage 325
#define MGK_OptionErrorUnableToThresholdImage 326
#define MGK_OptionErrorUnableToWaveImage 327
#define MGK_OptionErrorUnrecognizedAttribute 328
#define MGK_OptionErrorUnrecognizedChannelType 329
#define MGK_OptionErrorUnrecognizedColor 330
#define MGK_OptionErrorUnrecognizedColormapType 331
#define MGK_OptionErrorUnrecognizedColorspace 332
#define MGK_OptionErrorUnrecognizedCommand 333
#define MGK_OptionErrorUnrecognizedComposeOperator 334
#define MGK_OptionErrorUnrecognizedDisposeMethod 335
#define MGK_OptionErrorUnrecognizedElement 336
#define MGK_OptionErrorUnrecognizedEndianType 337
#define MGK_OptionErrorUnrecognizedGravityType 338
#define MGK_OptionErrorUnrecognizedHighlightStyle 339
#define MGK_OptionErrorUnrecognizedImageCompression 340
#define MGK_OptionErrorUnrecognizedImageFilter 341
#define MGK_OptionErrorUnrecognizedImageFormat 342
#define MGK_OptionErrorUnrecognizedImageMode 343
#define MGK_OptionErrorUnrecognizedImageType 344
#define MGK_OptionErrorUnrecognizedIntentType 345
#define MGK_OptionErrorUnrecognizedInterlaceType 346
#define MGK_OptionErrorUnrecognizedListType 347
#define MGK_OptionErrorUnrecognizedMetric 348
#define MGK_OptionErrorUnrecognizedModeType 349
#define MGK_OptionErrorUnrecognizedNoiseType 350
#define MGK_OptionErrorUnrecognizedOperator 351
#define MGK_OptionErrorUnrecognizedOption 352
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 353
#define MGK_OptionErrorUnrecognizedPixelMap 354
#define MGK_OptionErrorUnrecognizedPreviewType 355
#define MGK_OptionErrorUnrecognizedResourceType 356
#define MGK_OptionErrorUnrecognizedType 357
#define MGK_OptionErrorUnrecognizedUnitsType 358
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 359
#define MGK_OptionErrorUnsupportedSamplingFactor 360
#define MGK_OptionErrorUsageError 361
#define MGK_OptionFatalErrorInvalidColorspaceType 362
#define MGK_OptionFatalErrorInvalidEndianType 363
#define MGK_OptionFatalErrorInvalidImageType 364
#define MGK_OptionFatalErrorInvalidInterlaceType 365
#define MGK_OptionFatalErrorMissingAnImageFilename 366
#define MGK_OptionFatalErrorMissingArgument 367
#define MGK_OptionFatalErrorNoImagesWereLoaded 368
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 369
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 370
#define MGK_OptionFatalErrorUnableToOpenXServer 371
#define MGK_OptionFatalErrorUnableToPersistKey 372
#define MGK_OptionFatalErrorUnrecognizedColormapType 373
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 374
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 375
#define MGK_OptionFatalErrorUnrecognizedEndianType 376
#define MGK_OptionFatalErrorUnrecognizedFilterType 377
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 378
#define MGK_OptionFatalErrorUnrecognizedImageType 379
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 380
#define MGK_OptionFatalErrorUnrecognizedOption 381
#define MGK_OptionFatalErrorUnrecognizedResourceType 382
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 383
#define MGK_OptionWarningUnrecognizedColor 384
#define MGK_RegistryErrorImageExpected 385
#define MGK_RegistryErrorImageInfoExpected 386
#define MGK_RegistryErrorStructureSizeMismatch 387
#define MGK_RegistryErrorUnableToGetRegistryID 388
#define MGK_RegistryErrorUnableToLocateImage 389
#define MGK_RegistryErrorUnableToSetRegistry 390
#define MGK_RegistryFatalErrorDefault 391
#define MGK_RegistryWarningDefault 392
#define MGK_ResourceLimitErrorCacheResourcesExhausted 393
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 394
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 395
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 396
#define MGK_ResourceLimitErrorMemoryAllocationFailed 397
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 398
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 399
#define MGK_ResourceLimitErrorUnableToAddColorProfile 400
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 401
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 402
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 403
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 404
#define MGK_ResourceLimitErrorUnableToAllocateColormap 405
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 406
#define MGK_ResourceLimitErrorUnableToAllocateImage 407
#define MGK_ResourceLimitErrorUnableToAllocateString 408
#define MGK_ResourceLimitErrorUnableToAnnotateImage 409
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 410
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 411
#define MGK_ResourceLimitErrorUnableToCloneImage 412
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 413
#define MGK_ResourceLimitErrorUnableToConstituteImage 414
#define MGK_ResourceLimitErrorUnableToConvertFont 415
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 416
#define MGK_ResourceLimitErrorUnableToCreateColormap 417
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 418
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 419
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 420
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 421
#define MGK_ResourceLimitErrorUnableToCreateXWindow 422
#define MGK_ResourceLimitErrorUnableToCropImage 423
#define MGK_ResourceLimitErrorUnableToDespeckleImage 424
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 425
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 426
#define MGK_ResourceLimitErrorUnableToDitherImage 427
#define MGK_ResourceLimitErrorUnableToDrawOnImage 428
#define MGK_ResourceLimitErrorUnableToEdgeImage 429
#define MGK_ResourceLimitErrorUnableToEmbossImage 430
#define MGK_ResourceLimitErrorUnableToEnhanceImage 431
#define MGK_ResourceLimitErrorUnableToFloodfillImage 432
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 433
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 434
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 435
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 436
#define MGK_ResourceLimitErrorUnableToLevelImage 437
#define MGK_ResourceLimitErrorUnableToMagnifyImage 438
#define MGK_ResourceLimitErrorUnableToManageColor 439
#define MGK_ResourceLimitErrorUnableToMapImage 440
#define MGK_ResourceLimitErrorUnableToMapImageSequence 441
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 442
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 443
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 444
#define MGK_ResourceLimitErrorUnableToNormalizeImage 445
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 446
#define MGK_ResourceLimitErrorUnableToQuantizeImage 447
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 448
#define MGK_ResourceLimitErrorUnableToReadTextChunk 449
#define MGK_ResourceLimitErrorUnableToReadXImage 450
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 451
#define MGK_ResourceLimitErrorUnableToResizeImage 452
#define MGK_ResourceLimitErrorUnableToRotateImage 453
#define MGK_ResourceLimitErrorUnableToSampleImage 454
#define MGK_ResourceLimitErrorUnableToScaleImage 455
#define MGK_ResourceLimitErrorUnableToSelectImage 456
#define MGK_ResourceLimitErrorUnableToSharpenImage 457
#define MGK_ResourceLimitErrorUnableToShaveImage 458
#define MGK_ResourceLimitErrorUnableToShearImage 459
#define MGK_ResourceLimitErrorUnableToSortImageColormap 460
#define MGK_ResourceLimitErrorUnableToThresholdImage 461
#define MGK_ResourceLimitErrorUnableToTransformColorspace 462
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 463
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 464
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 465
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 466
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 467
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 475
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 477
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 478
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 479
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 480
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 481
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 490
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 491
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 492
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 493
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 494
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 495
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 496
#define MGK_ResourceLimitFatalErrorUnableToConvertText 497
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 498
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 499
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 500
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 501
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 502
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 503
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 504
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 505
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 506
#define MGK_ResourceLimitWarningMemoryAllocationFailed 507
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 508
#define MGK_StreamErrorNoStreamHandlerIsDefined 509
#define MGK_StreamErrorPixelCacheIsNotOpen 510
#define MGK_StreamErrorUnableToAcquirePixelStream 511
#define MGK_StreamErrorUnableToSetPixelStream 512
#define MGK_StreamErrorUnableToSyncPixelStream 513
#define MGK_StreamFatalErrorDefault 514
#define MGK_StreamWarningDefault 515
#define MGK_TypeErrorFontSubstitutionRequired 516
#define MGK_TypeErrorUnableToGetTypeMetrics 517
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 518
#define MGK_TypeErrorUnableToReadFont 519
#define MGK_TypeErrorUnrecognizedFontEncoding 520
#define MGK_TypeFatalErrorDefault 521
#define MGK_TypeWarningDefault 522
#define MGK_WandErrorInvalidColormapIndex 523
#define MGK_WandErrorWandAPINotImplemented 524
#define MGK_WandErrorWandContainsNoImageIndexs 525
#define MGK_WandErrorWandContainsNoImages 526
#define MGK_XServerErrorColorIsNotKnownToServer 527
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 528
#define MGK_XServerErrorStandardColormapIsNotInitialized 529
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 530
#define MGK_XServerErrorUnableToCreateBitmap 531
#define MGK_XServerErrorUnableToCreateColormap 532
#define MGK_XServerErrorUnableToCreatePixmap 533
#define MGK_XServerErrorUnableToCreateProperty 534
#define MGK_XServerErrorUnableToCreateStandardColormap 535
#define MGK_XServerErrorUnableToDisplayImageInfo 536
#define MGK_XServerErrorUnableToGetProperty 537
#define MGK_XServerErrorUnableToGetStandardColormap 538
#define MGK_XServerErrorUnableToGetVisual 539
#define MGK_XServerErrorUnableToGrabMouse 540
#define MGK_XServerErrorUnableToLoadFont 541
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 542
#define MGK_XServerErrorUnableToOpenXServer 543
#define MGK_XServerErrorUnableToReadXAttributes 544
#define MGK_XServerErrorUnableToReadXWindowImage 545
#define MGK_XServerErrorUnrecognizedColormapType 546
#define MGK_XServerErrorUnrecognizedGravityType 547
#define MGK_XServerErrorUnrecognizedVisualSpecifier 548
#define MGK_XServerFatalErrorUnableToAllocateXHints 549
#define MGK_XServerFatalErrorUnableToCreateCursor 550
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 551
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 552
#define MGK_XServerFatalErrorUnableToCreateTextProperty 553
#define MGK_XServerFatalErrorUnableToCreateXImage 554
#define MGK_XServerFatalErrorUnableToCreateXPixmap 555
#define MGK_XServerFatalErrorUnableToCreateXWindow 556
#define MGK_XServerFatalErrorUnableToDisplayImage 557
#define MGK_XServerFatalErrorUnableToDitherImage 558
#define MGK_XServerFatalErrorUnableToGetPixelInfo 559
#define MGK_XServerFatalErrorUnableToGetVisual 560
#define MGK_XServerFatalErrorUnableToLoadFont 561
#define MGK_XServerFatalErrorUnableToMakeXWindow 562
#define MGK_XServerFatalErrorUnableToOpenXServer 563
#define MGK_XServerFatalErrorUnableToViewFonts 564
#define MGK_XServerWarningUnableToGetVisual 565
#define MGK_XServerWarningUsingDefaultVisual 566

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
    { "Coder/FatalError", 104, CoderFatalError },
    { "Coder/Warning", 105, CoderWarning },
    { "Configure/Error", 106, ConfigureError },
    { "Configure/FatalError", 113, ConfigureFatalError },
    { "Configure/Warning", 117, ConfigureWarning },
    { "Corrupt/Image/Error", 118, CorruptImageError },
    { "Corrupt/Image/FatalError", 160, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 161, CorruptImageWarning },
    { "Delegate/Error", 172, DelegateError },
    { "Delegate/FatalError", 190, DelegateFatalError },
    { "Delegate/Warning", 191, DelegateWarning },
    { "Draw/Error", 192, DrawError },
    { "Draw/FatalError", 204, DrawFatalError },
    { "Draw/Warning", 205, DrawWarning },
    { "File/Open/Error", 208, FileOpenError },
    { "File/Open/FatalError", 211, FileOpenFatalError },
    { "File/Open/Warning", 212, FileOpenWarning },
    { "Image/Error", 213, ImageError },
    { "Image/FatalError", 248, ImageFatalError },
    { "Image/Warning", 249, ImageWarning },
    { "Missing/Delegate/Error", 250, MissingDelegateError },
    { "Missing/Delegate/FatalError", 262, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 263, MissingDelegateWarning },
    { "Module/Error", 264, ModuleError },
    { "Module/FatalError", 269, ModuleFatalError },
    { "Module/Warning", 270, ModuleWarning },
    { "Monitor/Error", 271, MonitorError },
    { "Monitor/FatalError", 272, MonitorFatalError },
    { "Monitor/Warning", 274, MonitorWarning },
    { "Option/Error", 275, OptionError },
    { "Option/FatalError", 361, OptionFatalError },
    { "Option/Warning", 383, OptionWarning },
    { "Registry/Error", 384, RegistryError },
    { "Registry/FatalError", 390, RegistryFatalError },
    { "Registry/Warning", 391, RegistryWarning },
    { "Resource/Limit/Error", 392, ResourceLimitError },
    { "Resource/Limit/FatalError", 462, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 506, ResourceLimitWarning },
    { "Stream/Error", 507, StreamError },
    { "Stream/FatalError", 513, StreamFatalError },
    { "Stream/Warning", 514, StreamWarning },
    { "Type/Error", 515, TypeError },
    { "Type/FatalError", 520, TypeFatalError },
    { "Type/Warning", 521, TypeWarning },
    { "Wand/Error", 522, WandError },
    { "XServer/Error", 526, XServerError },
    { "XServer/FatalError", 548, XServerFatalError },
    { "XServer/Warning", 564, XServerWarning },
    { 0, 566, UndefinedException }
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
    { "ColormapTooLarge", 26 },
    { "ColormapTypeNotSupported", 27 },
    { "ColorspaceModelIsNotSupported", 28 },
    { "ColorTypeNotSupported", 29 },
    { "CompressionNotValid", 30 },
    { "DataEncodingSchemeIsNotSupported", 31 },
    { "DataStorageTypeIsNotSupported", 32 },
    { "DeltaPNGNotSupported", 33 },
    { "EncryptedWPGImageFileNotSupported", 34 },
    { "FractalCompressionNotSupported", 35 },
    { "ImageColumnOrRowSizeIsNotSupported", 36 },
    { "ImageDoesNotHaveAMatteChannel", 37 },
    { "ImageIsNotTiled", 38 },
    { "ImageTypeNotSupported", 39 },
    { "IncompatibleSizeOfDouble", 40 },
    { "IrregularChannelGeometryNotSupported", 41 },
    { "JNGCompressionNotSupported", 42 },
    { "JPEGCompressionNotSupported", 43 },
    { "JPEGEmbeddingFailed", 44 },
    { "LocationTypeIsNotSupported", 45 },
    { "MapStorageTypeIsNotSupported", 46 },
    { "MSBByteOrderNotSupported", 47 },
    { "MultidimensionalMatricesAreNotSupported", 48 },
    { "MultipleRecordListNotSupported", 49 },
    { "No8BIMDataIsAvailable", 50 },
    { "NoAPP1DataIsAvailable", 51 },
    { "NoBitmapOnClipboard", 52 },
    { "NoColorProfileAvailable", 53 },
    { "NoDataReturned", 54 },
    { "NoImageVectorGraphics", 55 },
    { "NoIPTCInfoWasFound", 56 },
    { "NoIPTCProfileAvailable", 57 },
    { "NumberOfImagesIsNotSupported", 58 },
    { "OnlyContinuousTonePictureSupported", 59 },
    { "OnlyLevelZerofilesSupported", 60 },
    { "PNGCompressionNotSupported", 61 },
    { "PNGLibraryTooOld", 62 },
    { "RLECompressionNotSupported", 63 },
    { "SubsamplingRequiresEvenWidth", 64 },
    { "UnableToCopyProfile", 65 },
    { "UnableToCreateADC", 66 },
    { "UnableToCreateBitmap", 67 },
    { "UnableToDecompressImage", 68 },
    { "UnableToInitializeFPXLibrary", 69 },
    { "UnableToOpenBlob", 70 },
    { "UnableToReadAspectRatio", 71 },
    { "UnableToReadCIELABImages", 72 },
    { "UnableToReadSummaryInfo", 73 },
    { "UnableToSetAffineMatrix", 74 },
    { "UnableToSetAspectRatio", 75 },
    { "UnableToSetColorTwist", 76 },
    { "UnableToSetContrast", 77 },
    { "UnableToSetFilteringValue", 78 },
    { "UnableToSetImageComments", 79 },
    { "UnableToSetImageTitle", 80 },
    { "UnableToSetJPEGLevel", 81 },
    { "UnableToSetRegionOfInterest", 82 },
    { "UnableToSetSummaryInfo", 83 },
    { "UnableToTranslateText", 84 },
    { "UnableToWriteMPEGParameters", 85 },
    { "UnableToWriteTemporaryFile", 86 },
    { "UnableToZipCompressImage", 87 },
    { "UnsupportedBitsPerSample", 88 },
    { "UnsupportedCellTypeInTheMatrix", 89 },
    { "WebPDecodingFailedUserAbort", 90 },
    { "WebPEncodingFailed", 91 },
    { "WebPEncodingFailedBadDimension", 92 },
    { "WebPEncodingFailedBadWrite", 93 },
    { "WebPEncodingFailedBitstreamOutOfMemory", 94 },
    { "WebPEncodingFailedFileTooBig", 95 },
    { "WebPEncodingFailedInvalidConfiguration", 96 },
    { "WebPEncodingFailedNULLParameter", 97 },
    { "WebPEncodingFailedOutOfMemory", 98 },
    { "WebPEncodingFailedPartition0Overflow", 99 },
    { "WebPEncodingFailedPartitionOverflow", 100 },
    { "WebPEncodingFailedUserAbort", 101 },
    { "WebPInvalidConfiguration", 102 },
    { "WebPInvalidParameter", 103 },
    { "ZipCompressionNotSupported", 104 },
    { "Default", 105 },
    { "LosslessToLossyJPEGConversion", 106 },
    { "IncludeElementNestedTooDeeply", 107 },
    { "RegistryKeyLookupFailed", 108 },
    { "StringTokenLengthExceeded", 109 },
    { "UnableToAccessConfigureFile", 110 },
    { "UnableToAccessFontFile", 111 },
    { "UnableToAccessLogFile", 112 },
    { "UnableToAccessModuleFile", 113 },
    { "Default", 114 },
    { "UnableToChangeToWorkingDirectory", 115 },
    { "UnableToGetCurrentDirectory", 116 },
    { "UnableToRestoreCurrentDirectory", 117 },
    { "Default", 118 },
    { "AnErrorHasOccurredReadingFromFile", 119 },
    { "AnErrorHasOccurredWritingToFile", 120 },
    { "ColormapExceedsColorsLimit", 121 },
    { "CompressionNotValid", 122 },
    { "CorruptImage", 123 },
    { "ImageFileDoesNotContainAnyImageData", 124 },
    { "ImageFileHasNoScenes", 125 },
    { "ImageTypeNotSupported", 126 },
    { "ImproperImageHeader", 127 },
    { "InsufficientImageDataInFile", 128 },
    { "InvalidColormapIndex", 129 },
    { "InvalidFileFormatVersion", 130 },
    { "LengthAndFilesizeDoNotMatch", 131 },
    { "MissingImageChannel", 132 },
    { "NegativeOrZeroImageSize", 133 },
    { "NonOS2HeaderSizeError", 134 },
    { "NotEnoughTiles", 135 },
    { "StaticPlanesValueNotEqualToOne", 136 },
    { "SubsamplingRequiresEvenWidth", 137 },
    { "TooMuchImageDataInFile", 138 },
    { "UnableToReadColormapFromDumpFile", 139 },
    { "UnableToReadColorProfile", 140 },
    { "UnableToReadExtensionBlock", 141 },
    { "UnableToReadGenericProfile", 142 },
    { "UnableToReadImageData", 143 },
    { "UnableToReadImageHeader", 144 },
    { "UnableToReadIPTCProfile", 145 },
    { "UnableToReadPixmapFromDumpFile", 146 },
    { "UnableToReadSubImageData", 147 },
    { "UnableToReadVIDImage", 148 },
    { "UnableToReadWindowNameFromDumpFile", 149 },
    { "UnableToRunlengthDecodeImage", 150 },
    { "UnableToUncompressImage", 151 },
    { "UnexpectedEndOfFile", 152 },
    { "UnexpectedSamplingFactor", 153 },
    { "UnknownPatternType", 154 },
    { "UnrecognizedBitsPerPixel", 155 },
    { "UnrecognizedImageCompression", 156 },
    { "UnrecognizedNumberOfColors", 157 },
    { "UnrecognizedXWDHeader", 158 },
    { "UnsupportedBitsPerSample", 159 },
    { "UnsupportedNumberOfPlanes", 160 },
    { "UnableToPersistKey", 161 },
    { "CompressionNotValid", 162 },
    { "CorruptImage", 163 },
    { "ImproperImageHeader", 164 },
    { "InvalidColormapIndex", 165 },
    { "LengthAndFilesizeDoNotMatch", 166 },
    { "NegativeOrZeroImageSize", 167 },
    { "NonOS2HeaderSizeError", 168 },
    { "SkipToSyncByte", 169 },
    { "StaticPlanesValueNotEqualToOne", 170 },
    { "UnrecognizedBitsPerPixel", 171 },
    { "UnrecognizedImageCompression", 172 },
    { "DelegateFailed", 173 },
    { "FailedToAllocateArgumentList", 174 },
    { "FailedToAllocateGhostscriptInterpreter", 175 },
    { "FailedToComputeOutputSize", 176 },
    { "FailedToFindGhostscript", 177 },
    { "FailedToRenderFile", 178 },
    { "FailedToScanFile", 179 },
    { "NoTagFound", 180 },
    { "PostscriptDelegateFailed", 181 },
    { "UnableToCreateImage", 182 },
    { "UnableToCreateImageComponent", 183 },
    { "UnableToDecodeImageFile", 184 },
    { "UnableToEncodeImageFile", 185 },
    { "UnableToInitializeFPXLibrary", 186 },
    { "UnableToInitializeWMFLibrary", 187 },
    { "UnableToManageJP2Stream", 188 },
    { "UnableToWriteSVGFormat", 189 },
    { "WebPABIMismatch", 190 },
    { "Default", 191 },
    { "Default", 192 },
    { "AlreadyPushingPatternDefinition", 193 },
    { "DrawingRecursionDetected", 194 },
    { "FloatValueConversionError", 195 },
    { "IntegerValueConversionError", 196 },
    { "InvalidPrimitiveArgument", 197 },
    { "NonconformingDrawingPrimitiveDefinition", 198 },
    { "PrimitiveArithmeticOverflow", 199 },
    { "TooManyCoordinates", 200 },
    { "UnableToPrint", 201 },
    { "UnbalancedGraphicContextPushPop", 202 },
    { "UnreasonableGradientSize", 203 },
    { "VectorPathTruncated", 204 },
    { "Default", 205 },
    { "NotARelativeURL", 206 },
    { "NotCurrentlyPushingPatternDefinition", 207 },
    { "URLNotFound", 208 },
    { "UnableToCreateTemporaryFile", 209 },
    { "UnableToOpenFile", 210 },
    { "UnableToWriteFile", 211 },
    { "Default", 212 },
    { "Default", 213 },
    { "AngleIsDiscontinuous", 214 },
    { "CMYKAImageLacksAlphaChannel", 215 },
    { "ColorspaceColorProfileMismatch", 216 },
    { "ImageColorspaceDiffers", 217 },
    { "ImageColorspaceMismatch", 218 },
    { "ImageDifferenceExceedsLimit", 219 },
    { "ImageDoesNotContainResolution", 220 },
    { "ImageIsNotColormapped", 221 },
    { "ImageOpacityDiffers", 222 },
    { "ImageSequenceIsRequired", 223 },
    { "ImageSizeDiffers", 224 },
    { "InvalidColormapIndex", 225 },
    { "LeftAndRightImageSizesDiffer", 226 },
    { "NoImagesWereFound", 227 },
    { "NoImagesWereLoaded", 228 },
    { "NoLocaleImageAttribute", 229 },
    { "TooManyClusters", 230 },
    { "UnableToAppendImage", 231 },
    { "UnableToAssignProfile", 232 },
    { "UnableToAverageImage", 233 },
    { "UnableToCoalesceImage", 234 },
    { "UnableToCompareImages", 235 },
    { "UnableToCreateImageMosaic", 236 },
    { "UnableToCreateStereoImage", 237 },
    { "UnableToDeconstructImageSequence", 238 },
    { "UnableToExportImagePixels", 239 },
    { "UnableToFlattenImage", 240 },
    { "UnableToGetClipMask", 241 },
    { "UnableToHandleImageChannel", 242 },
    { "UnableToImportImagePixels", 243 },
    { "UnableToResizeImage", 244 },
    { "UnableToSegmentImage", 245 },
    { "UnableToSetClipMask", 246 },
    { "UnableToShearImage", 247 },
    { "WidthOrHeightExceedsLimit", 248 },
    { "UnableToPersistKey", 249 },
    { "Default", 250 },
    { "DPSLibraryIsNotAvailable", 251 },
    { "FPXLibraryIsNotAvailable", 252 },
    { "FreeTypeLibraryIsNotAvailable", 253 },
    { "JPEGLibraryIsNotAvailable", 254 },
    { "LCMSLibraryIsNotAvailable", 255 },
    { "LZWEncodingNotEnabled", 256 },
    { "NoDecodeDelegateForThisImageFormat", 257 },
    { "NoEncodeDelegateForThisImageFormat", 258 },
    { "TIFFLibraryIsNotAvailable", 259 },
    { "XMLLibraryIsNotAvailable", 260 },
    { "XWindowLibraryIsNotAvailable", 261 },
    { "ZipLibraryIsNotAvailable", 262 },
    { "Default", 263 },
    { "Default", 264 },
    { "FailedToCloseModule", 265 },
    { "FailedToFindSymbol", 266 },
    { "UnableToLoadModule", 267 },
    { "UnableToRegisterImageFormat", 268 },
    { "UnrecognizedModule", 269 },
    { "UnableToInitializeModuleLoader", 270 },
    { "Default", 271 },
    { "Default", 272 },
    { "Default", 273 },
    { "UserRequestedTerminationBySignal", 274 },
    { "Default", 275 },
    { "BevelWidthIsNegative", 276 },
    { "ColorSeparatedImageRequired", 277 },
    { "FrameIsLessThanImageSize", 278 },
    { "GeometryDimensionsAreZero", 279 },
    { "GeometryDoesNotContainImage", 280 },
    { "HaldClutImageDimensionsInvalid", 281 },
    { "ImagesAreNotTheSameSize", 282 },
    { "ImageSizeMustExceedBevelWidth", 283 },
    { "ImageSmallerThanKernelWidth", 284 },
    { "ImageSmallerThanRadius", 285 },
    { "ImageWidthsOrHeightsDiffer", 286 },
    { "InputImagesAlreadySpecified", 287 },
    { "InvalidSubimageSpecification", 288 },
    { "KernelRadiusIsTooSmall", 289 },
    { "KernelWidthMustBeAnOddNumber", 290 },
    { "MatrixIsNotSquare", 291 },
    { "MatrixOrderOutOfRange", 292 },
    { "MissingAnImageFilename", 293 },
    { "MissingArgument", 294 },
    { "MustSpecifyAnImageName", 295 },
    { "MustSpecifyImageSize", 296 },
    { "NoBlobDefined", 297 },
    { "NoImagesDefined", 298 },
    { "NonzeroWidthAndHeightRequired", 299 },
    { "NoProfileNameWasGiven", 300 },
    { "NullBlobArgument", 301 },
    { "ReferenceImageRequired", 302 },
    { "ReferenceIsNotMyType", 303 },
    { "RegionAreaExceedsLimit", 304 },
    { "RequestDidNotReturnAnImage", 305 },
    { "SteganoImageRequired", 306 },
    { "StereoImageRequired", 307 },
    { "SubimageSpecificationReturnsNoImages", 308 },
    { "TileNotBoundedByImageDimensions", 309 },
    { "UnableToAddOrRemoveProfile", 310 },
    { "UnableToAverageImageSequence", 311 },
    { "UnableToBlurImage", 312 },
    { "UnableToChopImage", 313 },
    { "UnableToColorMatrixImage", 314 },
    { "UnableToConstituteImage", 315 },
    { "UnableToConvolveImage", 316 },
    { "UnableToEdgeImage", 317 },
    { "UnableToEqualizeImage", 318 },
    { "UnableToFilterImage", 319 },
    { "UnableToFormatImageMetadata", 320 },
    { "UnableToFrameImage", 321 },
    { "UnableToOilPaintImage", 322 },
    { "UnableToPaintImage", 323 },
    { "UnableToRaiseImage", 324 },
    { "UnableToSharpenImage", 325 },
    { "UnableToThresholdImage", 326 },
    { "UnableToWaveImage", 327 },
    { "UnrecognizedAttribute", 328 },
    { "UnrecognizedChannelType", 329 },
    { "UnrecognizedColor", 330 },
    { "UnrecognizedColormapType", 331 },
    { "UnrecognizedColorspace", 332 },
    { "UnrecognizedCommand", 333 },
    { "UnrecognizedComposeOperator", 334 },
    { "UnrecognizedDisposeMethod", 335 },
    { "UnrecognizedElement", 336 },
    { "UnrecognizedEndianType", 337 },
    { "UnrecognizedGravityType", 338 },
    { "UnrecognizedHighlightStyle", 339 },
    { "UnrecognizedImageCompression", 340 },
    { "UnrecognizedImageFilter", 341 },
    { "UnrecognizedImageFormat", 342 },
    { "UnrecognizedImageMode", 343 },
    { "UnrecognizedImageType", 344 },
    { "UnrecognizedIntentType", 345 },
    { "UnrecognizedInterlaceType", 346 },
    { "UnrecognizedListType", 347 },
    { "UnrecognizedMetric", 348 },
    { "UnrecognizedModeType", 349 },
    { "UnrecognizedNoiseType", 350 },
    { "UnrecognizedOperator", 351 },
    { "UnrecognizedOption", 352 },
    { "UnrecognizedPerlMagickMethod", 353 },
    { "UnrecognizedPixelMap", 354 },
    { "UnrecognizedPreviewType", 355 },
    { "UnrecognizedResourceType", 356 },
    { "UnrecognizedType", 357 },
    { "UnrecognizedUnitsType", 358 },
    { "UnrecognizedVirtualPixelMethod", 359 },
    { "UnsupportedSamplingFactor", 360 },
    { "UsageError", 361 },
    { "InvalidColorspaceType", 362 },
    { "InvalidEndianType", 363 },
    { "InvalidImageType", 364 },
    { "InvalidInterlaceType", 365 },
    { "MissingAnImageFilename", 366 },
    { "MissingArgument", 367 },
    { "NoImagesWereLoaded", 368 },
    { "OptionLengthExceedsLimit", 369 },
    { "RequestDidNotReturnAnImage", 370 },
    { "UnableToOpenXServer", 371 },
    { "UnableToPersistKey", 372 },
    { "UnrecognizedColormapType", 373 },
    { "UnrecognizedColorspaceType", 374 },
    { "UnrecognizedDisposeMethod", 375 },
    { "UnrecognizedEndianType", 376 },
    { "UnrecognizedFilterType", 377 },
    { "UnrecognizedImageCompressionType", 378 },
    { "UnrecognizedImageType", 379 },
    { "UnrecognizedInterlaceType", 380 },
    { "UnrecognizedOption", 381 },
    { "UnrecognizedResourceType", 382 },
    { "UnrecognizedVirtualPixelMethod", 383 },
    { "UnrecognizedColor", 384 },
    { "ImageExpected", 385 },
    { "ImageInfoExpected", 386 },
    { "StructureSizeMismatch", 387 },
    { "UnableToGetRegistryID", 388 },
    { "UnableToLocateImage", 389 },
    { "UnableToSetRegistry", 390 },
    { "Default", 391 },
    { "Default", 392 },
    { "CacheResourcesExhausted", 393 },
    { "ImagePixelHeightLimitExceeded", 394 },
    { "ImagePixelLimitExceeded", 395 },
    { "ImagePixelWidthLimitExceeded", 396 },
    { "MemoryAllocationFailed", 397 },
    { "NoPixelsDefinedInCache", 398 },
    { "PixelCacheAllocationFailed", 399 },
    { "UnableToAddColorProfile", 400 },
    { "UnableToAddGenericProfile", 401 },
    { "UnableToAddIPTCProfile", 402 },
    { "UnableToAddOrRemoveProfile", 403 },
    { "UnableToAllocateCoefficients", 404 },
    { "UnableToAllocateColormap", 405 },
    { "UnableToAllocateICCProfile", 406 },
    { "UnableToAllocateImage", 407 },
    { "UnableToAllocateString", 408 },
    { "UnableToAnnotateImage", 409 },
    { "UnableToAverageImageSequence", 410 },
    { "UnableToCloneDrawingWand", 411 },
    { "UnableToCloneImage", 412 },
    { "UnableToComputeImageSignature", 413 },
    { "UnableToConstituteImage", 414 },
    { "UnableToConvertFont", 415 },
    { "UnableToConvertStringToTokens", 416 },
    { "UnableToCreateColormap", 417 },
    { "UnableToCreateColorTransform", 418 },
    { "UnableToCreateCommandWidget", 419 },
    { "UnableToCreateImageGroup", 420 },
    { "UnableToCreateImageMontage", 421 },
    { "UnableToCreateXWindow", 422 },
    { "UnableToCropImage", 423 },
    { "UnableToDespeckleImage", 424 },
    { "UnableToDetermineImageClass", 425 },
    { "UnableToDetermineTheNumberOfImageColors", 426 },
    { "UnableToDitherImage", 427 },
    { "UnableToDrawOnImage", 428 },
    { "UnableToEdgeImage", 429 },
    { "UnableToEmbossImage", 430 },
    { "UnableToEnhanceImage", 431 },
    { "UnableToFloodfillImage", 432 },
    { "UnableToGammaCorrectImage", 433 },
    { "UnableToGetBestIconSize", 434 },
    { "UnableToGetFromRegistry", 435 },
    { "UnableToGetPackageInfo", 436 },
    { "UnableToLevelImage", 437 },
    { "UnableToMagnifyImage", 438 },
    { "UnableToManageColor", 439 },
    { "UnableToMapImage", 440 },
    { "UnableToMapImageSequence", 441 },
    { "UnableToMedianFilterImage", 442 },
    { "UnableToMotionBlurImage", 443 },
    { "UnableToNoiseFilterImage", 444 },
    { "UnableToNormalizeImage", 445 },
    { "UnableToOpenColorProfile", 446 },
    { "UnableToQuantizeImage", 447 },
    { "UnableToQuantizeImageSequence", 448 },
    { "UnableToReadTextChunk", 449 },
    { "UnableToReadXImage", 450 },
    { "UnableToReadXServerColormap", 451 },
    { "UnableToResizeImage", 452 },
    { "UnableToRotateImage", 453 },
    { "UnableToSampleImage", 454 },
    { "UnableToScaleImage", 455 },
    { "UnableToSelectImage", 456 },
    { "UnableToSharpenImage", 457 },
    { "UnableToShaveImage", 458 },
    { "UnableToShearImage", 459 },
    { "UnableToSortImageColormap", 460 },
    { "UnableToThresholdImage", 461 },
    { "UnableToTransformColorspace", 462 },
    { "MemoryAllocationFailed", 463 },
    { "SemaporeOperationFailed", 464 },
    { "UnableToAllocateAscii85Info", 465 },
    { "UnableToAllocateCacheInfo", 466 },
    { "UnableToAllocateCacheView", 467 },
    { "UnableToAllocateColorInfo", 468 },
    { "UnableToAllocateDashPattern", 469 },
    { "UnableToAllocateDelegateInfo", 470 },
    { "UnableToAllocateDerivatives", 471 },
    { "UnableToAllocateDrawContext", 472 },
    { "UnableToAllocateDrawInfo", 473 },
    { "UnableToAllocateDrawingWand", 474 },
    { "UnableToAllocateGammaMap", 475 },
    { "UnableToAllocateImage", 476 },
    { "UnableToAllocateImagePixels", 477 },
    { "UnableToAllocateLogInfo", 478 },
    { "UnableToAllocateMagicInfo", 479 },
    { "UnableToAllocateMagickInfo", 480 },
    { "UnableToAllocateMagickMap", 481 },
    { "UnableToAllocateModuleInfo", 482 },
    { "UnableToAllocateMontageInfo", 483 },
    { "UnableToAllocateQuantizeInfo", 484 },
    { "UnableToAllocateRandomKernel", 485 },
    { "UnableToAllocateRegistryInfo", 486 },
    { "UnableToAllocateSemaphoreInfo", 487 },
    { "UnableToAllocateString", 488 },
    { "UnableToAllocateTypeInfo", 489 },
    { "UnableToAllocateWand", 490 },
    { "UnableToAnimateImageSequence", 491 },
    { "UnableToCloneBlobInfo", 492 },
    { "UnableToCloneCacheInfo", 493 },
    { "UnableToCloneImage", 494 },
    { "UnableToCloneImageInfo", 495 },
    { "UnableToConcatenateString", 496 },
    { "UnableToConvertText", 497 },
    { "UnableToCreateColormap", 498 },
    { "UnableToDestroySemaphore", 499 },
    { "UnableToDisplayImage", 500 },
    { "UnableToEscapeString", 501 },
    { "UnableToInitializeSemaphore", 502 },
    { "UnableToInterpretMSLImage", 503 },
    { "UnableToLockSemaphore", 504 },
    { "UnableToObtainRandomEntropy", 505 },
    { "UnableToUnlockSemaphore", 506 },
    { "MemoryAllocationFailed", 507 },
    { "ImageDoesNotContainTheStreamGeometry", 508 },
    { "NoStreamHandlerIsDefined", 509 },
    { "PixelCacheIsNotOpen", 510 },
    { "UnableToAcquirePixelStream", 511 },
    { "UnableToSetPixelStream", 512 },
    { "UnableToSyncPixelStream", 513 },
    { "Default", 514 },
    { "Default", 515 },
    { "FontSubstitutionRequired", 516 },
    { "UnableToGetTypeMetrics", 517 },
    { "UnableToInitializeFreetypeLibrary", 518 },
    { "UnableToReadFont", 519 },
    { "UnrecognizedFontEncoding", 520 },
    { "Default", 521 },
    { "Default", 522 },
    { "InvalidColormapIndex", 523 },
    { "WandAPINotImplemented", 524 },
    { "WandContainsNoImageIndexs", 525 },
    { "WandContainsNoImages", 526 },
    { "ColorIsNotKnownToServer", 527 },
    { "NoWindowWithSpecifiedIDExists", 528 },
    { "StandardColormapIsNotInitialized", 529 },
    { "UnableToConnectToRemoteDisplay", 530 },
    { "UnableToCreateBitmap", 531 },
    { "UnableToCreateColormap", 532 },
    { "UnableToCreatePixmap", 533 },
    { "UnableToCreateProperty", 534 },
    { "UnableToCreateStandardColormap", 535 },
    { "UnableToDisplayImageInfo", 536 },
    { "UnableToGetProperty", 537 },
    { "UnableToGetStandardColormap", 538 },
    { "UnableToGetVisual", 539 },
    { "UnableToGrabMouse", 540 },
    { "UnableToLoadFont", 541 },
    { "UnableToMatchVisualToStandardColormap", 542 },
    { "UnableToOpenXServer", 543 },
    { "UnableToReadXAttributes", 544 },
    { "UnableToReadXWindowImage", 545 },
    { "UnrecognizedColormapType", 546 },
    { "UnrecognizedGravityType", 547 },
    { "UnrecognizedVisualSpecifier", 548 },
    { "UnableToAllocateXHints", 549 },
    { "UnableToCreateCursor", 550 },
    { "UnableToCreateGraphicContext", 551 },
    { "UnableToCreateStandardColormap", 552 },
    { "UnableToCreateTextProperty", 553 },
    { "UnableToCreateXImage", 554 },
    { "UnableToCreateXPixmap", 555 },
    { "UnableToCreateXWindow", 556 },
    { "UnableToDisplayImage", 557 },
    { "UnableToDitherImage", 558 },
    { "UnableToGetPixelInfo", 559 },
    { "UnableToGetVisual", 560 },
    { "UnableToLoadFont", 561 },
    { "UnableToMakeXWindow", 562 },
    { "UnableToOpenXServer", 563 },
    { "UnableToViewFonts", 564 },
    { "UnableToGetVisual", 565 },
    { "UsingDefaultVisual", 566 },
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

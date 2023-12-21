#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int) MAGICK_FUNC_CONST;

#define MAX_LOCALE_MSGS 592

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
#define MGK_CacheErrorEmptyCacheNexus 12
#define MGK_CacheErrorInconsistentPersistentCacheDepth 13
#define MGK_CacheErrorPixelCacheDimensionsMisMatch 14
#define MGK_CacheErrorPixelCacheIsNotOpen 15
#define MGK_CacheErrorUnableToAllocateCacheView 16
#define MGK_CacheErrorUnableToCloneCache 17
#define MGK_CacheErrorUnableToExtendCache 18
#define MGK_CacheErrorUnableToGetCacheNexus 19
#define MGK_CacheErrorUnableToGetPixelsFromCache 20
#define MGK_CacheErrorUnableToOpenCache 21
#define MGK_CacheErrorUnableToPeristPixelCache 22
#define MGK_CacheErrorUnableToReadPixelCache 23
#define MGK_CacheErrorUnableToSyncCache 24
#define MGK_CacheFatalErrorDiskAllocationFailed 25
#define MGK_CacheFatalErrorUnableToExtendPixelCache 26
#define MGK_CacheWarningDefault 27
#define MGK_CoderErrorArithmeticOverflow 28
#define MGK_CoderErrorColormapTooLarge 29
#define MGK_CoderErrorColormapTypeNotSupported 30
#define MGK_CoderErrorColorspaceModelIsNotSupported 31
#define MGK_CoderErrorColorTypeNotSupported 32
#define MGK_CoderErrorCompressionNotValid 33
#define MGK_CoderErrorDataEncodingSchemeIsNotSupported 34
#define MGK_CoderErrorDataStorageTypeIsNotSupported 35
#define MGK_CoderErrorDecodedImageNotReturned 36
#define MGK_CoderErrorDeltaPNGNotSupported 37
#define MGK_CoderErrorDivisionByZero 38
#define MGK_CoderErrorEncryptedWPGImageFileNotSupported 39
#define MGK_CoderErrorFractalCompressionNotSupported 40
#define MGK_CoderErrorImageColumnOrRowSizeIsNotSupported 41
#define MGK_CoderErrorImageDoesNotHaveAMatteChannel 42
#define MGK_CoderErrorImageIsNotTiled 43
#define MGK_CoderErrorImageTypeNotSupported 44
#define MGK_CoderErrorIncompatibleSizeOfDouble 45
#define MGK_CoderErrorIrregularChannelGeometryNotSupported 46
#define MGK_CoderErrorJNGCompressionNotSupported 47
#define MGK_CoderErrorJPEGCompressionNotSupported 48
#define MGK_CoderErrorJPEGEmbeddingFailed 49
#define MGK_CoderErrorJXLDecoderAPIFailure 50
#define MGK_CoderErrorJXLEncoderAPIFailure 51
#define MGK_CoderErrorLocationTypeIsNotSupported 52
#define MGK_CoderErrorMapStorageTypeIsNotSupported 53
#define MGK_CoderErrorMSBByteOrderNotSupported 54
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 55
#define MGK_CoderErrorMultipleRecordListNotSupported 56
#define MGK_CoderErrorNo8BIMDataIsAvailable 57
#define MGK_CoderErrorNoAPP1DataIsAvailable 58
#define MGK_CoderErrorNoBitmapOnClipboard 59
#define MGK_CoderErrorNoColorProfileAvailable 60
#define MGK_CoderErrorNoDataReturned 61
#define MGK_CoderErrorNoImageVectorGraphics 62
#define MGK_CoderErrorNoIPTCInfoWasFound 63
#define MGK_CoderErrorNoIPTCProfileAvailable 64
#define MGK_CoderErrorNumberOfImagesIsNotSupported 65
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 66
#define MGK_CoderErrorOnlyLevelZerofilesSupported 67
#define MGK_CoderErrorPNGCompressionNotSupported 68
#define MGK_CoderErrorPNGLibraryTooOld 69
#define MGK_CoderErrorRLECompressionNotSupported 70
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 71
#define MGK_CoderErrorUnableToCopyProfile 72
#define MGK_CoderErrorUnableToCreateADC 73
#define MGK_CoderErrorUnableToCreateBitmap 74
#define MGK_CoderErrorUnableToDecompressImage 75
#define MGK_CoderErrorUnableToInitializeFPXLibrary 76
#define MGK_CoderErrorUnableToOpenBlob 77
#define MGK_CoderErrorUnableToReadAspectRatio 78
#define MGK_CoderErrorUnableToReadCIELABImages 79
#define MGK_CoderErrorUnableToReadSummaryInfo 80
#define MGK_CoderErrorUnableToSetAffineMatrix 81
#define MGK_CoderErrorUnableToSetAspectRatio 82
#define MGK_CoderErrorUnableToSetColorTwist 83
#define MGK_CoderErrorUnableToSetContrast 84
#define MGK_CoderErrorUnableToSetFilteringValue 85
#define MGK_CoderErrorUnableToSetImageComments 86
#define MGK_CoderErrorUnableToSetImageTitle 87
#define MGK_CoderErrorUnableToSetJPEGLevel 88
#define MGK_CoderErrorUnableToSetRegionOfInterest 89
#define MGK_CoderErrorUnableToSetSummaryInfo 90
#define MGK_CoderErrorUnableToTranslateText 91
#define MGK_CoderErrorUnableToWriteMPEGParameters 92
#define MGK_CoderErrorUnableToWriteTemporaryFile 93
#define MGK_CoderErrorUnableToZipCompressImage 94
#define MGK_CoderErrorUnsupportedBitsPerSample 95
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 96
#define MGK_CoderErrorUnsupportedNumberOfColumns 97
#define MGK_CoderErrorUnsupportedNumberOfRows 98
#define MGK_CoderErrorUnsupportedSamplesPerPixel 99
#define MGK_CoderErrorWebPDecodingFailedUserAbort 100
#define MGK_CoderErrorWebPEncodingFailed 101
#define MGK_CoderErrorWebPEncodingFailedBadDimension 102
#define MGK_CoderErrorWebPEncodingFailedBadWrite 103
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 104
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 105
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 106
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 107
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 108
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 109
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 110
#define MGK_CoderErrorWebPEncodingFailedUserAbort 111
#define MGK_CoderErrorWebPInvalidConfiguration 112
#define MGK_CoderErrorWebPInvalidParameter 113
#define MGK_CoderErrorZipCompressionNotSupported 114
#define MGK_CoderFatalErrorDefault 115
#define MGK_CoderWarningLosslessToLossyJPEGConversion 116
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 117
#define MGK_ConfigureErrorRegistryKeyLookupFailed 118
#define MGK_ConfigureErrorStringTokenLengthExceeded 119
#define MGK_ConfigureErrorUnableToAccessConfigureFile 120
#define MGK_ConfigureErrorUnableToAccessFontFile 121
#define MGK_ConfigureErrorUnableToAccessLogFile 122
#define MGK_ConfigureErrorUnableToAccessModuleFile 123
#define MGK_ConfigureFatalErrorDefault 124
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 125
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 126
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 127
#define MGK_ConfigureWarningDefault 128
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 129
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 130
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 131
#define MGK_CorruptImageErrorCompressionNotValid 132
#define MGK_CorruptImageErrorCorruptImage 133
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 134
#define MGK_CorruptImageErrorImageFileHasNoScenes 135
#define MGK_CorruptImageErrorImageTypeNotSupported 136
#define MGK_CorruptImageErrorImproperImageHeader 137
#define MGK_CorruptImageErrorInsufficientImageDataInFile 138
#define MGK_CorruptImageErrorInvalidColormapIndex 139
#define MGK_CorruptImageErrorInvalidFileFormatVersion 140
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 141
#define MGK_CorruptImageErrorMissingImageChannel 142
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 143
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 144
#define MGK_CorruptImageErrorNotEnoughTiles 145
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 146
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 147
#define MGK_CorruptImageErrorTooMuchImageDataInFile 148
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 149
#define MGK_CorruptImageErrorUnableToReadColorProfile 150
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 151
#define MGK_CorruptImageErrorUnableToReadGenericProfile 152
#define MGK_CorruptImageErrorUnableToReadImageData 153
#define MGK_CorruptImageErrorUnableToReadImageHeader 154
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 155
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 156
#define MGK_CorruptImageErrorUnableToReadSubImageData 157
#define MGK_CorruptImageErrorUnableToReadVIDImage 158
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 159
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 160
#define MGK_CorruptImageErrorUnableToUncompressImage 161
#define MGK_CorruptImageErrorUnexpectedEndOfFile 162
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 163
#define MGK_CorruptImageErrorUnknownPatternType 164
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 165
#define MGK_CorruptImageErrorUnrecognizedImageCompression 166
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 167
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 168
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 169
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 170
#define MGK_CorruptImageFatalErrorUnableToPersistKey 171
#define MGK_CorruptImageWarningCompressionNotValid 172
#define MGK_CorruptImageWarningCorruptImage 173
#define MGK_CorruptImageWarningImproperImageHeader 174
#define MGK_CorruptImageWarningInvalidColormapIndex 175
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 176
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 177
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 178
#define MGK_CorruptImageWarningSkipToSyncByte 179
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 180
#define MGK_CorruptImageWarningUnableToParseEmbeddedProfile 181
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 182
#define MGK_CorruptImageWarningUnrecognizedImageCompression 183
#define MGK_DelegateErrorDelegateFailed 184
#define MGK_DelegateErrorFailedToAllocateArgumentList 185
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 186
#define MGK_DelegateErrorFailedToComputeOutputSize 187
#define MGK_DelegateErrorFailedToFindGhostscript 188
#define MGK_DelegateErrorFailedToRenderFile 189
#define MGK_DelegateErrorFailedToScanFile 190
#define MGK_DelegateErrorNoTagFound 191
#define MGK_DelegateErrorPostscriptDelegateFailed 192
#define MGK_DelegateErrorUnableToCreateImage 193
#define MGK_DelegateErrorUnableToCreateImageComponent 194
#define MGK_DelegateErrorUnableToDecodeImageFile 195
#define MGK_DelegateErrorUnableToEncodeImageFile 196
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 197
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 198
#define MGK_DelegateErrorUnableToManageJP2Stream 199
#define MGK_DelegateErrorUnableToWriteSVGFormat 200
#define MGK_DelegateErrorWebPABIMismatch 201
#define MGK_DelegateFatalErrorDefault 202
#define MGK_DelegateWarningDefault 203
#define MGK_DrawErrorAlreadyPushingPatternDefinition 204
#define MGK_DrawErrorArithmeticOverflow 205
#define MGK_DrawErrorDrawingRecursionDetected 206
#define MGK_DrawErrorFloatValueConversionError 207
#define MGK_DrawErrorIntegerValueConversionError 208
#define MGK_DrawErrorInvalidPrimitiveArgument 209
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 210
#define MGK_DrawErrorPrimitiveArithmeticOverflow 211
#define MGK_DrawErrorTooManyCoordinates 212
#define MGK_DrawErrorUnableToDrawOnImage 213
#define MGK_DrawErrorUnableToPrint 214
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 215
#define MGK_DrawErrorUnbalancedPushPop 216
#define MGK_DrawErrorUnreasonableAffineMatrix 217
#define MGK_DrawErrorUnreasonableDashPolygonLength 218
#define MGK_DrawErrorUnreasonableGradientSize 219
#define MGK_DrawErrorVectorPathTruncated 220
#define MGK_DrawFatalErrorDefault 221
#define MGK_DrawWarningNotARelativeURL 222
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 223
#define MGK_DrawWarningURLNotFound 224
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 225
#define MGK_FileOpenErrorUnableToOpenFile 226
#define MGK_FileOpenErrorUnableToWriteFile 227
#define MGK_FileOpenFatalErrorDefault 228
#define MGK_FileOpenWarningDefault 229
#define MGK_ImageErrorAngleIsDiscontinuous 230
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 231
#define MGK_ImageErrorColorspaceColorProfileMismatch 232
#define MGK_ImageErrorImageColorspaceDiffers 233
#define MGK_ImageErrorImageColorspaceMismatch 234
#define MGK_ImageErrorImageDifferenceExceedsLimit 235
#define MGK_ImageErrorImageDoesNotContainResolution 236
#define MGK_ImageErrorImageIsNotColormapped 237
#define MGK_ImageErrorImageOpacityDiffers 238
#define MGK_ImageErrorImageSequenceIsRequired 239
#define MGK_ImageErrorImageSizeDiffers 240
#define MGK_ImageErrorInvalidColormapIndex 241
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 242
#define MGK_ImageErrorNoImagesWereFound 243
#define MGK_ImageErrorNoImagesWereLoaded 244
#define MGK_ImageErrorNoLocaleImageAttribute 245
#define MGK_ImageErrorTooManyClusters 246
#define MGK_ImageErrorUnableToAppendImage 247
#define MGK_ImageErrorUnableToAssignProfile 248
#define MGK_ImageErrorUnableToAverageImage 249
#define MGK_ImageErrorUnableToCoalesceImage 250
#define MGK_ImageErrorUnableToCompareImages 251
#define MGK_ImageErrorUnableToCreateImageMosaic 252
#define MGK_ImageErrorUnableToCreateStereoImage 253
#define MGK_ImageErrorUnableToDeconstructImageSequence 254
#define MGK_ImageErrorUnableToExportImagePixels 255
#define MGK_ImageErrorUnableToFlattenImage 256
#define MGK_ImageErrorUnableToGetClipMask 257
#define MGK_ImageErrorUnableToGetCompositeMask 258
#define MGK_ImageErrorUnableToHandleImageChannel 259
#define MGK_ImageErrorUnableToImportImagePixels 260
#define MGK_ImageErrorUnableToResizeImage 261
#define MGK_ImageErrorUnableToSegmentImage 262
#define MGK_ImageErrorUnableToSetClipMask 263
#define MGK_ImageErrorUnableToSetCompositeMask 264
#define MGK_ImageErrorUnableToShearImage 265
#define MGK_ImageErrorWidthOrHeightExceedsLimit 266
#define MGK_ImageFatalErrorUnableToPersistKey 267
#define MGK_ImageWarningDefault 268
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 269
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 270
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 271
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 272
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 273
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 274
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 275
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 276
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 277
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 278
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 279
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 280
#define MGK_MissingDelegateFatalErrorDefault 281
#define MGK_MissingDelegateWarningDefault 282
#define MGK_ModuleErrorFailedToCloseModule 283
#define MGK_ModuleErrorFailedToFindSymbol 284
#define MGK_ModuleErrorUnableToLoadModule 285
#define MGK_ModuleErrorUnableToRegisterImageFormat 286
#define MGK_ModuleErrorUnrecognizedModule 287
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 288
#define MGK_ModuleWarningDefault 289
#define MGK_MonitorErrorDefault 290
#define MGK_MonitorFatalErrorDefault 291
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 292
#define MGK_MonitorWarningDefault 293
#define MGK_OptionErrorBevelWidthIsNegative 294
#define MGK_OptionErrorColorSeparatedImageRequired 295
#define MGK_OptionErrorFrameIsLessThanImageSize 296
#define MGK_OptionErrorGeometryDimensionsAreZero 297
#define MGK_OptionErrorGeometryDoesNotContainImage 298
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 299
#define MGK_OptionErrorImagesAreNotTheSameSize 300
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 301
#define MGK_OptionErrorImageSmallerThanKernelWidth 302
#define MGK_OptionErrorImageSmallerThanRadius 303
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 304
#define MGK_OptionErrorInputImagesAlreadySpecified 305
#define MGK_OptionErrorInvalidSubimageSpecification 306
#define MGK_OptionErrorKernelRadiusIsTooSmall 307
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 308
#define MGK_OptionErrorMatrixIsNotSquare 309
#define MGK_OptionErrorMatrixOrderOutOfRange 310
#define MGK_OptionErrorMissingAnImageFilename 311
#define MGK_OptionErrorMissingArgument 312
#define MGK_OptionErrorMustSpecifyAnImageName 313
#define MGK_OptionErrorMustSpecifyImageSize 314
#define MGK_OptionErrorNoBlobDefined 315
#define MGK_OptionErrorNoImagesDefined 316
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 317
#define MGK_OptionErrorNoProfileNameWasGiven 318
#define MGK_OptionErrorNullBlobArgument 319
#define MGK_OptionErrorReferenceImageRequired 320
#define MGK_OptionErrorReferenceIsNotMyType 321
#define MGK_OptionErrorRegionAreaExceedsLimit 322
#define MGK_OptionErrorRequestDidNotReturnAnImage 323
#define MGK_OptionErrorSteganoImageRequired 324
#define MGK_OptionErrorStereoImageRequired 325
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 326
#define MGK_OptionErrorTileNotBoundedByImageDimensions 327
#define MGK_OptionErrorUnableToAddOrRemoveProfile 328
#define MGK_OptionErrorUnableToAverageImageSequence 329
#define MGK_OptionErrorUnableToBlurImage 330
#define MGK_OptionErrorUnableToChopImage 331
#define MGK_OptionErrorUnableToColorMatrixImage 332
#define MGK_OptionErrorUnableToConstituteImage 333
#define MGK_OptionErrorUnableToConvolveImage 334
#define MGK_OptionErrorUnableToEdgeImage 335
#define MGK_OptionErrorUnableToEqualizeImage 336
#define MGK_OptionErrorUnableToFilterImage 337
#define MGK_OptionErrorUnableToFormatImageMetadata 338
#define MGK_OptionErrorUnableToFrameImage 339
#define MGK_OptionErrorUnableToOilPaintImage 340
#define MGK_OptionErrorUnableToPaintImage 341
#define MGK_OptionErrorUnableToRaiseImage 342
#define MGK_OptionErrorUnableToSharpenImage 343
#define MGK_OptionErrorUnableToSpreadImage 344
#define MGK_OptionErrorUnableToThresholdImage 345
#define MGK_OptionErrorUnableToWaveImage 346
#define MGK_OptionErrorUnrecognizedAttribute 347
#define MGK_OptionErrorUnrecognizedChannelType 348
#define MGK_OptionErrorUnrecognizedColor 349
#define MGK_OptionErrorUnrecognizedColormapType 350
#define MGK_OptionErrorUnrecognizedColorspace 351
#define MGK_OptionErrorUnrecognizedCommand 352
#define MGK_OptionErrorUnrecognizedComposeOperator 353
#define MGK_OptionErrorUnrecognizedDisposeMethod 354
#define MGK_OptionErrorUnrecognizedElement 355
#define MGK_OptionErrorUnrecognizedEndianType 356
#define MGK_OptionErrorUnrecognizedGravityType 357
#define MGK_OptionErrorUnrecognizedHighlightStyle 358
#define MGK_OptionErrorUnrecognizedImageCompression 359
#define MGK_OptionErrorUnrecognizedImageFilter 360
#define MGK_OptionErrorUnrecognizedImageFormat 361
#define MGK_OptionErrorUnrecognizedImageMode 362
#define MGK_OptionErrorUnrecognizedImageType 363
#define MGK_OptionErrorUnrecognizedIntentType 364
#define MGK_OptionErrorUnrecognizedInterlaceType 365
#define MGK_OptionErrorUnrecognizedListType 366
#define MGK_OptionErrorUnrecognizedMetric 367
#define MGK_OptionErrorUnrecognizedModeType 368
#define MGK_OptionErrorUnrecognizedNoiseType 369
#define MGK_OptionErrorUnrecognizedOperator 370
#define MGK_OptionErrorUnrecognizedOption 371
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 372
#define MGK_OptionErrorUnrecognizedPixelMap 373
#define MGK_OptionErrorUnrecognizedPreviewType 374
#define MGK_OptionErrorUnrecognizedResourceType 375
#define MGK_OptionErrorUnrecognizedType 376
#define MGK_OptionErrorUnrecognizedUnitsType 377
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 378
#define MGK_OptionErrorUnsupportedSamplingFactor 379
#define MGK_OptionErrorUsageError 380
#define MGK_OptionFatalErrorInvalidColorspaceType 381
#define MGK_OptionFatalErrorInvalidEndianType 382
#define MGK_OptionFatalErrorInvalidImageType 383
#define MGK_OptionFatalErrorInvalidInterlaceType 384
#define MGK_OptionFatalErrorMissingAnImageFilename 385
#define MGK_OptionFatalErrorMissingArgument 386
#define MGK_OptionFatalErrorNoImagesWereLoaded 387
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 388
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 389
#define MGK_OptionFatalErrorUnableToOpenXServer 390
#define MGK_OptionFatalErrorUnableToPersistKey 391
#define MGK_OptionFatalErrorUnrecognizedColormapType 392
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 393
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 394
#define MGK_OptionFatalErrorUnrecognizedEndianType 395
#define MGK_OptionFatalErrorUnrecognizedFilterType 396
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 397
#define MGK_OptionFatalErrorUnrecognizedImageType 398
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 399
#define MGK_OptionFatalErrorUnrecognizedOption 400
#define MGK_OptionFatalErrorUnrecognizedResourceType 401
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 402
#define MGK_OptionWarningUnrecognizedColor 403
#define MGK_RegistryErrorImageExpected 404
#define MGK_RegistryErrorImageInfoExpected 405
#define MGK_RegistryErrorStructureSizeMismatch 406
#define MGK_RegistryErrorUnableToGetRegistryID 407
#define MGK_RegistryErrorUnableToLocateImage 408
#define MGK_RegistryErrorUnableToSetRegistry 409
#define MGK_RegistryFatalErrorDefault 410
#define MGK_RegistryWarningDefault 411
#define MGK_ResourceLimitErrorCacheResourcesExhausted 412
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 413
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 414
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 415
#define MGK_ResourceLimitErrorMemoryAllocationFailed 416
#define MGK_ResourceLimitErrorNexusPixelHeightLimitExceeded 417
#define MGK_ResourceLimitErrorNexusPixelLimitExceeded 418
#define MGK_ResourceLimitErrorNexusPixelWidthLimitExceeded 419
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 420
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 421
#define MGK_ResourceLimitErrorReadLimitExceeded 422
#define MGK_ResourceLimitErrorUnableToAddColorProfile 423
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 424
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 425
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 426
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 427
#define MGK_ResourceLimitErrorUnableToAllocateColormap 428
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 429
#define MGK_ResourceLimitErrorUnableToAllocateImage 430
#define MGK_ResourceLimitErrorUnableToAllocateString 431
#define MGK_ResourceLimitErrorUnableToAnnotateImage 432
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 433
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 434
#define MGK_ResourceLimitErrorUnableToCloneImage 435
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 436
#define MGK_ResourceLimitErrorUnableToConstituteImage 437
#define MGK_ResourceLimitErrorUnableToConvertFont 438
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 439
#define MGK_ResourceLimitErrorUnableToCreateColormap 440
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 441
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 442
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 443
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 444
#define MGK_ResourceLimitErrorUnableToCreateXWindow 445
#define MGK_ResourceLimitErrorUnableToCropImage 446
#define MGK_ResourceLimitErrorUnableToDespeckleImage 447
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 448
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 449
#define MGK_ResourceLimitErrorUnableToDitherImage 450
#define MGK_ResourceLimitErrorUnableToDrawOnImage 451
#define MGK_ResourceLimitErrorUnableToEdgeImage 452
#define MGK_ResourceLimitErrorUnableToEmbossImage 453
#define MGK_ResourceLimitErrorUnableToEnhanceImage 454
#define MGK_ResourceLimitErrorUnableToFloodfillImage 455
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 456
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 457
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 458
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 459
#define MGK_ResourceLimitErrorUnableToInterpretMSLImage 460
#define MGK_ResourceLimitErrorUnableToLevelImage 461
#define MGK_ResourceLimitErrorUnableToMagnifyImage 462
#define MGK_ResourceLimitErrorUnableToManageColor 463
#define MGK_ResourceLimitErrorUnableToMapImage 464
#define MGK_ResourceLimitErrorUnableToMapImageSequence 465
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 466
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 467
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 468
#define MGK_ResourceLimitErrorUnableToNormalizeImage 469
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 470
#define MGK_ResourceLimitErrorUnableToQuantizeImage 471
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 472
#define MGK_ResourceLimitErrorUnableToReadTextChunk 473
#define MGK_ResourceLimitErrorUnableToReadXImage 474
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 475
#define MGK_ResourceLimitErrorUnableToResizeImage 476
#define MGK_ResourceLimitErrorUnableToRotateImage 477
#define MGK_ResourceLimitErrorUnableToSampleImage 478
#define MGK_ResourceLimitErrorUnableToScaleImage 479
#define MGK_ResourceLimitErrorUnableToSelectImage 480
#define MGK_ResourceLimitErrorUnableToSharpenImage 481
#define MGK_ResourceLimitErrorUnableToShaveImage 482
#define MGK_ResourceLimitErrorUnableToShearImage 483
#define MGK_ResourceLimitErrorUnableToSortImageColormap 484
#define MGK_ResourceLimitErrorUnableToThresholdImage 485
#define MGK_ResourceLimitErrorUnableToTransformColorspace 486
#define MGK_ResourceLimitErrorWriteLimitExceeded 487
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 488
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 490
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 491
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 492
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 493
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 494
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 495
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 496
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 497
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 498
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 499
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 500
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 501
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 502
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 503
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 504
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 505
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 506
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 507
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 508
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 509
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 510
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 511
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 512
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 513
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 514
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 515
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 516
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 517
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 518
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 519
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 520
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 521
#define MGK_ResourceLimitFatalErrorUnableToConvertText 522
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 523
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 524
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 525
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 526
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 527
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 528
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 529
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 530
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 531
#define MGK_ResourceLimitWarningMemoryAllocationFailed 532
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 533
#define MGK_StreamErrorNoStreamHandlerIsDefined 534
#define MGK_StreamErrorPixelCacheIsNotOpen 535
#define MGK_StreamErrorUnableToAcquirePixelStream 536
#define MGK_StreamErrorUnableToSetPixelStream 537
#define MGK_StreamErrorUnableToSyncPixelStream 538
#define MGK_StreamFatalErrorDefault 539
#define MGK_StreamWarningDefault 540
#define MGK_TypeErrorFontNotSpecified 541
#define MGK_TypeErrorFontSubstitutionRequired 542
#define MGK_TypeErrorUnableToGetTypeMetrics 543
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 544
#define MGK_TypeErrorUnableToReadFont 545
#define MGK_TypeErrorUnrecognizedFontEncoding 546
#define MGK_TypeFatalErrorDefault 547
#define MGK_TypeWarningDefault 548
#define MGK_WandErrorInvalidColormapIndex 549
#define MGK_WandErrorWandAPINotImplemented 550
#define MGK_WandErrorWandContainsNoImageIndexs 551
#define MGK_WandErrorWandContainsNoImages 552
#define MGK_XServerErrorColorIsNotKnownToServer 553
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 554
#define MGK_XServerErrorStandardColormapIsNotInitialized 555
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 556
#define MGK_XServerErrorUnableToCreateBitmap 557
#define MGK_XServerErrorUnableToCreateColormap 558
#define MGK_XServerErrorUnableToCreatePixmap 559
#define MGK_XServerErrorUnableToCreateProperty 560
#define MGK_XServerErrorUnableToCreateStandardColormap 561
#define MGK_XServerErrorUnableToDisplayImageInfo 562
#define MGK_XServerErrorUnableToGetProperty 563
#define MGK_XServerErrorUnableToGetStandardColormap 564
#define MGK_XServerErrorUnableToGetVisual 565
#define MGK_XServerErrorUnableToGrabMouse 566
#define MGK_XServerErrorUnableToLoadFont 567
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 568
#define MGK_XServerErrorUnableToOpenXServer 569
#define MGK_XServerErrorUnableToReadXAttributes 570
#define MGK_XServerErrorUnableToReadXWindowImage 571
#define MGK_XServerErrorUnrecognizedColormapType 572
#define MGK_XServerErrorUnrecognizedGravityType 573
#define MGK_XServerErrorUnrecognizedVisualSpecifier 574
#define MGK_XServerFatalErrorUnableToAllocateXHints 575
#define MGK_XServerFatalErrorUnableToCreateCursor 576
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 577
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 578
#define MGK_XServerFatalErrorUnableToCreateTextProperty 579
#define MGK_XServerFatalErrorUnableToCreateXImage 580
#define MGK_XServerFatalErrorUnableToCreateXPixmap 581
#define MGK_XServerFatalErrorUnableToCreateXWindow 582
#define MGK_XServerFatalErrorUnableToDisplayImage 583
#define MGK_XServerFatalErrorUnableToDitherImage 584
#define MGK_XServerFatalErrorUnableToGetPixelInfo 585
#define MGK_XServerFatalErrorUnableToGetVisual 586
#define MGK_XServerFatalErrorUnableToLoadFont 587
#define MGK_XServerFatalErrorUnableToMakeXWindow 588
#define MGK_XServerFatalErrorUnableToOpenXServer 589
#define MGK_XServerFatalErrorUnableToViewFonts 590
#define MGK_XServerWarningUnableToGetVisual 591
#define MGK_XServerWarningUsingDefaultVisual 592

#endif

#if defined(_INCLUDE_CATEGORYMAP_TABLE_)
typedef struct _CategoryInfo{
  const char name[17];
  unsigned int offset;
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
    { "", 54 }
  };
#endif

#if defined(_INCLUDE_SEVERITYMAP_TABLE_)
typedef struct _SeverityInfo{
  const char name[28];
  unsigned int offset;
  ExceptionType severityid;
} SeverityInfo;

static const SeverityInfo severity_map[] =
  {
    { "Blob/Error", 0, BlobError },
    { "Blob/FatalError", 9, BlobFatalError },
    { "Blob/Warning", 10, BlobWarning },
    { "Cache/Error", 11, CacheError },
    { "Cache/FatalError", 24, CacheFatalError },
    { "Cache/Warning", 26, CacheWarning },
    { "Coder/Error", 27, CoderError },
    { "Coder/FatalError", 114, CoderFatalError },
    { "Coder/Warning", 115, CoderWarning },
    { "Configure/Error", 116, ConfigureError },
    { "Configure/FatalError", 123, ConfigureFatalError },
    { "Configure/Warning", 127, ConfigureWarning },
    { "Corrupt/Image/Error", 128, CorruptImageError },
    { "Corrupt/Image/FatalError", 170, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 171, CorruptImageWarning },
    { "Delegate/Error", 183, DelegateError },
    { "Delegate/FatalError", 201, DelegateFatalError },
    { "Delegate/Warning", 202, DelegateWarning },
    { "Draw/Error", 203, DrawError },
    { "Draw/FatalError", 220, DrawFatalError },
    { "Draw/Warning", 221, DrawWarning },
    { "File/Open/Error", 224, FileOpenError },
    { "File/Open/FatalError", 227, FileOpenFatalError },
    { "File/Open/Warning", 228, FileOpenWarning },
    { "Image/Error", 229, ImageError },
    { "Image/FatalError", 266, ImageFatalError },
    { "Image/Warning", 267, ImageWarning },
    { "Missing/Delegate/Error", 268, MissingDelegateError },
    { "Missing/Delegate/FatalError", 280, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 281, MissingDelegateWarning },
    { "Module/Error", 282, ModuleError },
    { "Module/FatalError", 287, ModuleFatalError },
    { "Module/Warning", 288, ModuleWarning },
    { "Monitor/Error", 289, MonitorError },
    { "Monitor/FatalError", 290, MonitorFatalError },
    { "Monitor/Warning", 292, MonitorWarning },
    { "Option/Error", 293, OptionError },
    { "Option/FatalError", 380, OptionFatalError },
    { "Option/Warning", 402, OptionWarning },
    { "Registry/Error", 403, RegistryError },
    { "Registry/FatalError", 409, RegistryFatalError },
    { "Registry/Warning", 410, RegistryWarning },
    { "Resource/Limit/Error", 411, ResourceLimitError },
    { "Resource/Limit/FatalError", 487, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 531, ResourceLimitWarning },
    { "Stream/Error", 532, StreamError },
    { "Stream/FatalError", 538, StreamFatalError },
    { "Stream/Warning", 539, StreamWarning },
    { "Type/Error", 540, TypeError },
    { "Type/FatalError", 546, TypeFatalError },
    { "Type/Warning", 547, TypeWarning },
    { "Wand/Error", 548, WandError },
    { "XServer/Error", 552, XServerError },
    { "XServer/FatalError", 574, XServerFatalError },
    { "XServer/Warning", 590, XServerWarning },
    { "", 592, UndefinedException }
  };
#endif

#if defined(_INCLUDE_TAGMAP_TABLE_)
typedef struct _MessageInfo
{
  const char name[40];
  unsigned int messageid;
} MessageInfo;

static const MessageInfo message_map[] =
  {
    { "UnableToCreateBlob", MGK_BlobErrorUnableToCreateBlob },
    { "UnableToDeduceImageFormat", MGK_BlobErrorUnableToDeduceImageFormat },
    { "UnableToObtainOffset", MGK_BlobErrorUnableToObtainOffset },
    { "UnableToOpenFile", MGK_BlobErrorUnableToOpenFile },
    { "UnableToReadFile", MGK_BlobErrorUnableToReadFile },
    { "UnableToReadToOffset", MGK_BlobErrorUnableToReadToOffset },
    { "UnableToSeekToOffset", MGK_BlobErrorUnableToSeekToOffset },
    { "UnableToWriteBlob", MGK_BlobErrorUnableToWriteBlob },
    { "UnrecognizedImageFormat", MGK_BlobErrorUnrecognizedImageFormat },
    { "Default", MGK_BlobFatalErrorDefault },
    { "Default", MGK_BlobWarningDefault },
    { "EmptyCacheNexus", MGK_CacheErrorEmptyCacheNexus },
    { "InconsistentPersistentCacheDepth", MGK_CacheErrorInconsistentPersistentCacheDepth },
    { "PixelCacheDimensionsMisMatch", MGK_CacheErrorPixelCacheDimensionsMisMatch },
    { "PixelCacheIsNotOpen", MGK_CacheErrorPixelCacheIsNotOpen },
    { "UnableToAllocateCacheView", MGK_CacheErrorUnableToAllocateCacheView },
    { "UnableToCloneCache", MGK_CacheErrorUnableToCloneCache },
    { "UnableToExtendCache", MGK_CacheErrorUnableToExtendCache },
    { "UnableToGetCacheNexus", MGK_CacheErrorUnableToGetCacheNexus },
    { "UnableToGetPixelsFromCache", MGK_CacheErrorUnableToGetPixelsFromCache },
    { "UnableToOpenCache", MGK_CacheErrorUnableToOpenCache },
    { "UnableToPeristPixelCache", MGK_CacheErrorUnableToPeristPixelCache },
    { "UnableToReadPixelCache", MGK_CacheErrorUnableToReadPixelCache },
    { "UnableToSyncCache", MGK_CacheErrorUnableToSyncCache },
    { "DiskAllocationFailed", MGK_CacheFatalErrorDiskAllocationFailed },
    { "UnableToExtendPixelCache", MGK_CacheFatalErrorUnableToExtendPixelCache },
    { "Default", MGK_CacheWarningDefault },
    { "ArithmeticOverflow", MGK_CoderErrorArithmeticOverflow },
    { "ColormapTooLarge", MGK_CoderErrorColormapTooLarge },
    { "ColormapTypeNotSupported", MGK_CoderErrorColormapTypeNotSupported },
    { "ColorspaceModelIsNotSupported", MGK_CoderErrorColorspaceModelIsNotSupported },
    { "ColorTypeNotSupported", MGK_CoderErrorColorTypeNotSupported },
    { "CompressionNotValid", MGK_CoderErrorCompressionNotValid },
    { "DataEncodingSchemeIsNotSupported", MGK_CoderErrorDataEncodingSchemeIsNotSupported },
    { "DataStorageTypeIsNotSupported", MGK_CoderErrorDataStorageTypeIsNotSupported },
    { "DecodedImageNotReturned", MGK_CoderErrorDecodedImageNotReturned },
    { "DeltaPNGNotSupported", MGK_CoderErrorDeltaPNGNotSupported },
    { "DivisionByZero", MGK_CoderErrorDivisionByZero },
    { "EncryptedWPGImageFileNotSupported", MGK_CoderErrorEncryptedWPGImageFileNotSupported },
    { "FractalCompressionNotSupported", MGK_CoderErrorFractalCompressionNotSupported },
    { "ImageColumnOrRowSizeIsNotSupported", MGK_CoderErrorImageColumnOrRowSizeIsNotSupported },
    { "ImageDoesNotHaveAMatteChannel", MGK_CoderErrorImageDoesNotHaveAMatteChannel },
    { "ImageIsNotTiled", MGK_CoderErrorImageIsNotTiled },
    { "ImageTypeNotSupported", MGK_CoderErrorImageTypeNotSupported },
    { "IncompatibleSizeOfDouble", MGK_CoderErrorIncompatibleSizeOfDouble },
    { "IrregularChannelGeometryNotSupported", MGK_CoderErrorIrregularChannelGeometryNotSupported },
    { "JNGCompressionNotSupported", MGK_CoderErrorJNGCompressionNotSupported },
    { "JPEGCompressionNotSupported", MGK_CoderErrorJPEGCompressionNotSupported },
    { "JPEGEmbeddingFailed", MGK_CoderErrorJPEGEmbeddingFailed },
    { "JXLDecoderAPIFailure", MGK_CoderErrorJXLDecoderAPIFailure },
    { "JXLEncoderAPIFailure", MGK_CoderErrorJXLEncoderAPIFailure },
    { "LocationTypeIsNotSupported", MGK_CoderErrorLocationTypeIsNotSupported },
    { "MapStorageTypeIsNotSupported", MGK_CoderErrorMapStorageTypeIsNotSupported },
    { "MSBByteOrderNotSupported", MGK_CoderErrorMSBByteOrderNotSupported },
    { "MultidimensionalMatricesAreNotSupported", MGK_CoderErrorMultidimensionalMatricesAreNotSupported },
    { "MultipleRecordListNotSupported", MGK_CoderErrorMultipleRecordListNotSupported },
    { "No8BIMDataIsAvailable", MGK_CoderErrorNo8BIMDataIsAvailable },
    { "NoAPP1DataIsAvailable", MGK_CoderErrorNoAPP1DataIsAvailable },
    { "NoBitmapOnClipboard", MGK_CoderErrorNoBitmapOnClipboard },
    { "NoColorProfileAvailable", MGK_CoderErrorNoColorProfileAvailable },
    { "NoDataReturned", MGK_CoderErrorNoDataReturned },
    { "NoImageVectorGraphics", MGK_CoderErrorNoImageVectorGraphics },
    { "NoIPTCInfoWasFound", MGK_CoderErrorNoIPTCInfoWasFound },
    { "NoIPTCProfileAvailable", MGK_CoderErrorNoIPTCProfileAvailable },
    { "NumberOfImagesIsNotSupported", MGK_CoderErrorNumberOfImagesIsNotSupported },
    { "OnlyContinuousTonePictureSupported", MGK_CoderErrorOnlyContinuousTonePictureSupported },
    { "OnlyLevelZerofilesSupported", MGK_CoderErrorOnlyLevelZerofilesSupported },
    { "PNGCompressionNotSupported", MGK_CoderErrorPNGCompressionNotSupported },
    { "PNGLibraryTooOld", MGK_CoderErrorPNGLibraryTooOld },
    { "RLECompressionNotSupported", MGK_CoderErrorRLECompressionNotSupported },
    { "SubsamplingRequiresEvenWidth", MGK_CoderErrorSubsamplingRequiresEvenWidth },
    { "UnableToCopyProfile", MGK_CoderErrorUnableToCopyProfile },
    { "UnableToCreateADC", MGK_CoderErrorUnableToCreateADC },
    { "UnableToCreateBitmap", MGK_CoderErrorUnableToCreateBitmap },
    { "UnableToDecompressImage", MGK_CoderErrorUnableToDecompressImage },
    { "UnableToInitializeFPXLibrary", MGK_CoderErrorUnableToInitializeFPXLibrary },
    { "UnableToOpenBlob", MGK_CoderErrorUnableToOpenBlob },
    { "UnableToReadAspectRatio", MGK_CoderErrorUnableToReadAspectRatio },
    { "UnableToReadCIELABImages", MGK_CoderErrorUnableToReadCIELABImages },
    { "UnableToReadSummaryInfo", MGK_CoderErrorUnableToReadSummaryInfo },
    { "UnableToSetAffineMatrix", MGK_CoderErrorUnableToSetAffineMatrix },
    { "UnableToSetAspectRatio", MGK_CoderErrorUnableToSetAspectRatio },
    { "UnableToSetColorTwist", MGK_CoderErrorUnableToSetColorTwist },
    { "UnableToSetContrast", MGK_CoderErrorUnableToSetContrast },
    { "UnableToSetFilteringValue", MGK_CoderErrorUnableToSetFilteringValue },
    { "UnableToSetImageComments", MGK_CoderErrorUnableToSetImageComments },
    { "UnableToSetImageTitle", MGK_CoderErrorUnableToSetImageTitle },
    { "UnableToSetJPEGLevel", MGK_CoderErrorUnableToSetJPEGLevel },
    { "UnableToSetRegionOfInterest", MGK_CoderErrorUnableToSetRegionOfInterest },
    { "UnableToSetSummaryInfo", MGK_CoderErrorUnableToSetSummaryInfo },
    { "UnableToTranslateText", MGK_CoderErrorUnableToTranslateText },
    { "UnableToWriteMPEGParameters", MGK_CoderErrorUnableToWriteMPEGParameters },
    { "UnableToWriteTemporaryFile", MGK_CoderErrorUnableToWriteTemporaryFile },
    { "UnableToZipCompressImage", MGK_CoderErrorUnableToZipCompressImage },
    { "UnsupportedBitsPerSample", MGK_CoderErrorUnsupportedBitsPerSample },
    { "UnsupportedCellTypeInTheMatrix", MGK_CoderErrorUnsupportedCellTypeInTheMatrix },
    { "UnsupportedNumberOfColumns", MGK_CoderErrorUnsupportedNumberOfColumns },
    { "UnsupportedNumberOfRows", MGK_CoderErrorUnsupportedNumberOfRows },
    { "UnsupportedSamplesPerPixel", MGK_CoderErrorUnsupportedSamplesPerPixel },
    { "WebPDecodingFailedUserAbort", MGK_CoderErrorWebPDecodingFailedUserAbort },
    { "WebPEncodingFailed", MGK_CoderErrorWebPEncodingFailed },
    { "WebPEncodingFailedBadDimension", MGK_CoderErrorWebPEncodingFailedBadDimension },
    { "WebPEncodingFailedBadWrite", MGK_CoderErrorWebPEncodingFailedBadWrite },
    { "WebPEncodingFailedBitstreamOutOfMemory", MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory },
    { "WebPEncodingFailedFileTooBig", MGK_CoderErrorWebPEncodingFailedFileTooBig },
    { "WebPEncodingFailedInvalidConfiguration", MGK_CoderErrorWebPEncodingFailedInvalidConfiguration },
    { "WebPEncodingFailedNULLParameter", MGK_CoderErrorWebPEncodingFailedNULLParameter },
    { "WebPEncodingFailedOutOfMemory", MGK_CoderErrorWebPEncodingFailedOutOfMemory },
    { "WebPEncodingFailedPartition0Overflow", MGK_CoderErrorWebPEncodingFailedPartition0Overflow },
    { "WebPEncodingFailedPartitionOverflow", MGK_CoderErrorWebPEncodingFailedPartitionOverflow },
    { "WebPEncodingFailedUserAbort", MGK_CoderErrorWebPEncodingFailedUserAbort },
    { "WebPInvalidConfiguration", MGK_CoderErrorWebPInvalidConfiguration },
    { "WebPInvalidParameter", MGK_CoderErrorWebPInvalidParameter },
    { "ZipCompressionNotSupported", MGK_CoderErrorZipCompressionNotSupported },
    { "Default", MGK_CoderFatalErrorDefault },
    { "LosslessToLossyJPEGConversion", MGK_CoderWarningLosslessToLossyJPEGConversion },
    { "IncludeElementNestedTooDeeply", MGK_ConfigureErrorIncludeElementNestedTooDeeply },
    { "RegistryKeyLookupFailed", MGK_ConfigureErrorRegistryKeyLookupFailed },
    { "StringTokenLengthExceeded", MGK_ConfigureErrorStringTokenLengthExceeded },
    { "UnableToAccessConfigureFile", MGK_ConfigureErrorUnableToAccessConfigureFile },
    { "UnableToAccessFontFile", MGK_ConfigureErrorUnableToAccessFontFile },
    { "UnableToAccessLogFile", MGK_ConfigureErrorUnableToAccessLogFile },
    { "UnableToAccessModuleFile", MGK_ConfigureErrorUnableToAccessModuleFile },
    { "Default", MGK_ConfigureFatalErrorDefault },
    { "UnableToChangeToWorkingDirectory", MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory },
    { "UnableToGetCurrentDirectory", MGK_ConfigureFatalErrorUnableToGetCurrentDirectory },
    { "UnableToRestoreCurrentDirectory", MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory },
    { "Default", MGK_ConfigureWarningDefault },
    { "AnErrorHasOccurredReadingFromFile", MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile },
    { "AnErrorHasOccurredWritingToFile", MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile },
    { "ColormapExceedsColorsLimit", MGK_CorruptImageErrorColormapExceedsColorsLimit },
    { "CompressionNotValid", MGK_CorruptImageErrorCompressionNotValid },
    { "CorruptImage", MGK_CorruptImageErrorCorruptImage },
    { "ImageFileDoesNotContainAnyImageData", MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData },
    { "ImageFileHasNoScenes", MGK_CorruptImageErrorImageFileHasNoScenes },
    { "ImageTypeNotSupported", MGK_CorruptImageErrorImageTypeNotSupported },
    { "ImproperImageHeader", MGK_CorruptImageErrorImproperImageHeader },
    { "InsufficientImageDataInFile", MGK_CorruptImageErrorInsufficientImageDataInFile },
    { "InvalidColormapIndex", MGK_CorruptImageErrorInvalidColormapIndex },
    { "InvalidFileFormatVersion", MGK_CorruptImageErrorInvalidFileFormatVersion },
    { "LengthAndFilesizeDoNotMatch", MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch },
    { "MissingImageChannel", MGK_CorruptImageErrorMissingImageChannel },
    { "NegativeOrZeroImageSize", MGK_CorruptImageErrorNegativeOrZeroImageSize },
    { "NonOS2HeaderSizeError", MGK_CorruptImageErrorNonOS2HeaderSizeError },
    { "NotEnoughTiles", MGK_CorruptImageErrorNotEnoughTiles },
    { "StaticPlanesValueNotEqualToOne", MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne },
    { "SubsamplingRequiresEvenWidth", MGK_CorruptImageErrorSubsamplingRequiresEvenWidth },
    { "TooMuchImageDataInFile", MGK_CorruptImageErrorTooMuchImageDataInFile },
    { "UnableToReadColormapFromDumpFile", MGK_CorruptImageErrorUnableToReadColormapFromDumpFile },
    { "UnableToReadColorProfile", MGK_CorruptImageErrorUnableToReadColorProfile },
    { "UnableToReadExtensionBlock", MGK_CorruptImageErrorUnableToReadExtensionBlock },
    { "UnableToReadGenericProfile", MGK_CorruptImageErrorUnableToReadGenericProfile },
    { "UnableToReadImageData", MGK_CorruptImageErrorUnableToReadImageData },
    { "UnableToReadImageHeader", MGK_CorruptImageErrorUnableToReadImageHeader },
    { "UnableToReadIPTCProfile", MGK_CorruptImageErrorUnableToReadIPTCProfile },
    { "UnableToReadPixmapFromDumpFile", MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile },
    { "UnableToReadSubImageData", MGK_CorruptImageErrorUnableToReadSubImageData },
    { "UnableToReadVIDImage", MGK_CorruptImageErrorUnableToReadVIDImage },
    { "UnableToReadWindowNameFromDumpFile", MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile },
    { "UnableToRunlengthDecodeImage", MGK_CorruptImageErrorUnableToRunlengthDecodeImage },
    { "UnableToUncompressImage", MGK_CorruptImageErrorUnableToUncompressImage },
    { "UnexpectedEndOfFile", MGK_CorruptImageErrorUnexpectedEndOfFile },
    { "UnexpectedSamplingFactor", MGK_CorruptImageErrorUnexpectedSamplingFactor },
    { "UnknownPatternType", MGK_CorruptImageErrorUnknownPatternType },
    { "UnrecognizedBitsPerPixel", MGK_CorruptImageErrorUnrecognizedBitsPerPixel },
    { "UnrecognizedImageCompression", MGK_CorruptImageErrorUnrecognizedImageCompression },
    { "UnrecognizedNumberOfColors", MGK_CorruptImageErrorUnrecognizedNumberOfColors },
    { "UnrecognizedXWDHeader", MGK_CorruptImageErrorUnrecognizedXWDHeader },
    { "UnsupportedBitsPerSample", MGK_CorruptImageErrorUnsupportedBitsPerSample },
    { "UnsupportedNumberOfPlanes", MGK_CorruptImageErrorUnsupportedNumberOfPlanes },
    { "UnableToPersistKey", MGK_CorruptImageFatalErrorUnableToPersistKey },
    { "CompressionNotValid", MGK_CorruptImageWarningCompressionNotValid },
    { "CorruptImage", MGK_CorruptImageWarningCorruptImage },
    { "ImproperImageHeader", MGK_CorruptImageWarningImproperImageHeader },
    { "InvalidColormapIndex", MGK_CorruptImageWarningInvalidColormapIndex },
    { "LengthAndFilesizeDoNotMatch", MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch },
    { "NegativeOrZeroImageSize", MGK_CorruptImageWarningNegativeOrZeroImageSize },
    { "NonOS2HeaderSizeError", MGK_CorruptImageWarningNonOS2HeaderSizeError },
    { "SkipToSyncByte", MGK_CorruptImageWarningSkipToSyncByte },
    { "StaticPlanesValueNotEqualToOne", MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne },
    { "UnableToParseEmbeddedProfile", MGK_CorruptImageWarningUnableToParseEmbeddedProfile },
    { "UnrecognizedBitsPerPixel", MGK_CorruptImageWarningUnrecognizedBitsPerPixel },
    { "UnrecognizedImageCompression", MGK_CorruptImageWarningUnrecognizedImageCompression },
    { "DelegateFailed", MGK_DelegateErrorDelegateFailed },
    { "FailedToAllocateArgumentList", MGK_DelegateErrorFailedToAllocateArgumentList },
    { "FailedToAllocateGhostscriptInterpreter", MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter },
    { "FailedToComputeOutputSize", MGK_DelegateErrorFailedToComputeOutputSize },
    { "FailedToFindGhostscript", MGK_DelegateErrorFailedToFindGhostscript },
    { "FailedToRenderFile", MGK_DelegateErrorFailedToRenderFile },
    { "FailedToScanFile", MGK_DelegateErrorFailedToScanFile },
    { "NoTagFound", MGK_DelegateErrorNoTagFound },
    { "PostscriptDelegateFailed", MGK_DelegateErrorPostscriptDelegateFailed },
    { "UnableToCreateImage", MGK_DelegateErrorUnableToCreateImage },
    { "UnableToCreateImageComponent", MGK_DelegateErrorUnableToCreateImageComponent },
    { "UnableToDecodeImageFile", MGK_DelegateErrorUnableToDecodeImageFile },
    { "UnableToEncodeImageFile", MGK_DelegateErrorUnableToEncodeImageFile },
    { "UnableToInitializeFPXLibrary", MGK_DelegateErrorUnableToInitializeFPXLibrary },
    { "UnableToInitializeWMFLibrary", MGK_DelegateErrorUnableToInitializeWMFLibrary },
    { "UnableToManageJP2Stream", MGK_DelegateErrorUnableToManageJP2Stream },
    { "UnableToWriteSVGFormat", MGK_DelegateErrorUnableToWriteSVGFormat },
    { "WebPABIMismatch", MGK_DelegateErrorWebPABIMismatch },
    { "Default", MGK_DelegateFatalErrorDefault },
    { "Default", MGK_DelegateWarningDefault },
    { "AlreadyPushingPatternDefinition", MGK_DrawErrorAlreadyPushingPatternDefinition },
    { "ArithmeticOverflow", MGK_DrawErrorArithmeticOverflow },
    { "DrawingRecursionDetected", MGK_DrawErrorDrawingRecursionDetected },
    { "FloatValueConversionError", MGK_DrawErrorFloatValueConversionError },
    { "IntegerValueConversionError", MGK_DrawErrorIntegerValueConversionError },
    { "InvalidPrimitiveArgument", MGK_DrawErrorInvalidPrimitiveArgument },
    { "NonconformingDrawingPrimitiveDefinition", MGK_DrawErrorNonconformingDrawingPrimitiveDefinition },
    { "PrimitiveArithmeticOverflow", MGK_DrawErrorPrimitiveArithmeticOverflow },
    { "TooManyCoordinates", MGK_DrawErrorTooManyCoordinates },
    { "UnableToDrawOnImage", MGK_DrawErrorUnableToDrawOnImage },
    { "UnableToPrint", MGK_DrawErrorUnableToPrint },
    { "UnbalancedGraphicContextPushPop", MGK_DrawErrorUnbalancedGraphicContextPushPop },
    { "UnbalancedPushPop", MGK_DrawErrorUnbalancedPushPop },
    { "UnreasonableAffineMatrix", MGK_DrawErrorUnreasonableAffineMatrix },
    { "UnreasonableDashPolygonLength", MGK_DrawErrorUnreasonableDashPolygonLength },
    { "UnreasonableGradientSize", MGK_DrawErrorUnreasonableGradientSize },
    { "VectorPathTruncated", MGK_DrawErrorVectorPathTruncated },
    { "Default", MGK_DrawFatalErrorDefault },
    { "NotARelativeURL", MGK_DrawWarningNotARelativeURL },
    { "NotCurrentlyPushingPatternDefinition", MGK_DrawWarningNotCurrentlyPushingPatternDefinition },
    { "URLNotFound", MGK_DrawWarningURLNotFound },
    { "UnableToCreateTemporaryFile", MGK_FileOpenErrorUnableToCreateTemporaryFile },
    { "UnableToOpenFile", MGK_FileOpenErrorUnableToOpenFile },
    { "UnableToWriteFile", MGK_FileOpenErrorUnableToWriteFile },
    { "Default", MGK_FileOpenFatalErrorDefault },
    { "Default", MGK_FileOpenWarningDefault },
    { "AngleIsDiscontinuous", MGK_ImageErrorAngleIsDiscontinuous },
    { "CMYKAImageLacksAlphaChannel", MGK_ImageErrorCMYKAImageLacksAlphaChannel },
    { "ColorspaceColorProfileMismatch", MGK_ImageErrorColorspaceColorProfileMismatch },
    { "ImageColorspaceDiffers", MGK_ImageErrorImageColorspaceDiffers },
    { "ImageColorspaceMismatch", MGK_ImageErrorImageColorspaceMismatch },
    { "ImageDifferenceExceedsLimit", MGK_ImageErrorImageDifferenceExceedsLimit },
    { "ImageDoesNotContainResolution", MGK_ImageErrorImageDoesNotContainResolution },
    { "ImageIsNotColormapped", MGK_ImageErrorImageIsNotColormapped },
    { "ImageOpacityDiffers", MGK_ImageErrorImageOpacityDiffers },
    { "ImageSequenceIsRequired", MGK_ImageErrorImageSequenceIsRequired },
    { "ImageSizeDiffers", MGK_ImageErrorImageSizeDiffers },
    { "InvalidColormapIndex", MGK_ImageErrorInvalidColormapIndex },
    { "LeftAndRightImageSizesDiffer", MGK_ImageErrorLeftAndRightImageSizesDiffer },
    { "NoImagesWereFound", MGK_ImageErrorNoImagesWereFound },
    { "NoImagesWereLoaded", MGK_ImageErrorNoImagesWereLoaded },
    { "NoLocaleImageAttribute", MGK_ImageErrorNoLocaleImageAttribute },
    { "TooManyClusters", MGK_ImageErrorTooManyClusters },
    { "UnableToAppendImage", MGK_ImageErrorUnableToAppendImage },
    { "UnableToAssignProfile", MGK_ImageErrorUnableToAssignProfile },
    { "UnableToAverageImage", MGK_ImageErrorUnableToAverageImage },
    { "UnableToCoalesceImage", MGK_ImageErrorUnableToCoalesceImage },
    { "UnableToCompareImages", MGK_ImageErrorUnableToCompareImages },
    { "UnableToCreateImageMosaic", MGK_ImageErrorUnableToCreateImageMosaic },
    { "UnableToCreateStereoImage", MGK_ImageErrorUnableToCreateStereoImage },
    { "UnableToDeconstructImageSequence", MGK_ImageErrorUnableToDeconstructImageSequence },
    { "UnableToExportImagePixels", MGK_ImageErrorUnableToExportImagePixels },
    { "UnableToFlattenImage", MGK_ImageErrorUnableToFlattenImage },
    { "UnableToGetClipMask", MGK_ImageErrorUnableToGetClipMask },
    { "UnableToGetCompositeMask", MGK_ImageErrorUnableToGetCompositeMask },
    { "UnableToHandleImageChannel", MGK_ImageErrorUnableToHandleImageChannel },
    { "UnableToImportImagePixels", MGK_ImageErrorUnableToImportImagePixels },
    { "UnableToResizeImage", MGK_ImageErrorUnableToResizeImage },
    { "UnableToSegmentImage", MGK_ImageErrorUnableToSegmentImage },
    { "UnableToSetClipMask", MGK_ImageErrorUnableToSetClipMask },
    { "UnableToSetCompositeMask", MGK_ImageErrorUnableToSetCompositeMask },
    { "UnableToShearImage", MGK_ImageErrorUnableToShearImage },
    { "WidthOrHeightExceedsLimit", MGK_ImageErrorWidthOrHeightExceedsLimit },
    { "UnableToPersistKey", MGK_ImageFatalErrorUnableToPersistKey },
    { "Default", MGK_ImageWarningDefault },
    { "DPSLibraryIsNotAvailable", MGK_MissingDelegateErrorDPSLibraryIsNotAvailable },
    { "FPXLibraryIsNotAvailable", MGK_MissingDelegateErrorFPXLibraryIsNotAvailable },
    { "FreeTypeLibraryIsNotAvailable", MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable },
    { "JPEGLibraryIsNotAvailable", MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable },
    { "LCMSLibraryIsNotAvailable", MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable },
    { "LZWEncodingNotEnabled", MGK_MissingDelegateErrorLZWEncodingNotEnabled },
    { "NoDecodeDelegateForThisImageFormat", MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat },
    { "NoEncodeDelegateForThisImageFormat", MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat },
    { "TIFFLibraryIsNotAvailable", MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable },
    { "XMLLibraryIsNotAvailable", MGK_MissingDelegateErrorXMLLibraryIsNotAvailable },
    { "XWindowLibraryIsNotAvailable", MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable },
    { "ZipLibraryIsNotAvailable", MGK_MissingDelegateErrorZipLibraryIsNotAvailable },
    { "Default", MGK_MissingDelegateFatalErrorDefault },
    { "Default", MGK_MissingDelegateWarningDefault },
    { "FailedToCloseModule", MGK_ModuleErrorFailedToCloseModule },
    { "FailedToFindSymbol", MGK_ModuleErrorFailedToFindSymbol },
    { "UnableToLoadModule", MGK_ModuleErrorUnableToLoadModule },
    { "UnableToRegisterImageFormat", MGK_ModuleErrorUnableToRegisterImageFormat },
    { "UnrecognizedModule", MGK_ModuleErrorUnrecognizedModule },
    { "UnableToInitializeModuleLoader", MGK_ModuleFatalErrorUnableToInitializeModuleLoader },
    { "Default", MGK_ModuleWarningDefault },
    { "Default", MGK_MonitorErrorDefault },
    { "Default", MGK_MonitorFatalErrorDefault },
    { "UserRequestedTerminationBySignal", MGK_MonitorFatalErrorUserRequestedTerminationBySignal },
    { "Default", MGK_MonitorWarningDefault },
    { "BevelWidthIsNegative", MGK_OptionErrorBevelWidthIsNegative },
    { "ColorSeparatedImageRequired", MGK_OptionErrorColorSeparatedImageRequired },
    { "FrameIsLessThanImageSize", MGK_OptionErrorFrameIsLessThanImageSize },
    { "GeometryDimensionsAreZero", MGK_OptionErrorGeometryDimensionsAreZero },
    { "GeometryDoesNotContainImage", MGK_OptionErrorGeometryDoesNotContainImage },
    { "HaldClutImageDimensionsInvalid", MGK_OptionErrorHaldClutImageDimensionsInvalid },
    { "ImagesAreNotTheSameSize", MGK_OptionErrorImagesAreNotTheSameSize },
    { "ImageSizeMustExceedBevelWidth", MGK_OptionErrorImageSizeMustExceedBevelWidth },
    { "ImageSmallerThanKernelWidth", MGK_OptionErrorImageSmallerThanKernelWidth },
    { "ImageSmallerThanRadius", MGK_OptionErrorImageSmallerThanRadius },
    { "ImageWidthsOrHeightsDiffer", MGK_OptionErrorImageWidthsOrHeightsDiffer },
    { "InputImagesAlreadySpecified", MGK_OptionErrorInputImagesAlreadySpecified },
    { "InvalidSubimageSpecification", MGK_OptionErrorInvalidSubimageSpecification },
    { "KernelRadiusIsTooSmall", MGK_OptionErrorKernelRadiusIsTooSmall },
    { "KernelWidthMustBeAnOddNumber", MGK_OptionErrorKernelWidthMustBeAnOddNumber },
    { "MatrixIsNotSquare", MGK_OptionErrorMatrixIsNotSquare },
    { "MatrixOrderOutOfRange", MGK_OptionErrorMatrixOrderOutOfRange },
    { "MissingAnImageFilename", MGK_OptionErrorMissingAnImageFilename },
    { "MissingArgument", MGK_OptionErrorMissingArgument },
    { "MustSpecifyAnImageName", MGK_OptionErrorMustSpecifyAnImageName },
    { "MustSpecifyImageSize", MGK_OptionErrorMustSpecifyImageSize },
    { "NoBlobDefined", MGK_OptionErrorNoBlobDefined },
    { "NoImagesDefined", MGK_OptionErrorNoImagesDefined },
    { "NonzeroWidthAndHeightRequired", MGK_OptionErrorNonzeroWidthAndHeightRequired },
    { "NoProfileNameWasGiven", MGK_OptionErrorNoProfileNameWasGiven },
    { "NullBlobArgument", MGK_OptionErrorNullBlobArgument },
    { "ReferenceImageRequired", MGK_OptionErrorReferenceImageRequired },
    { "ReferenceIsNotMyType", MGK_OptionErrorReferenceIsNotMyType },
    { "RegionAreaExceedsLimit", MGK_OptionErrorRegionAreaExceedsLimit },
    { "RequestDidNotReturnAnImage", MGK_OptionErrorRequestDidNotReturnAnImage },
    { "SteganoImageRequired", MGK_OptionErrorSteganoImageRequired },
    { "StereoImageRequired", MGK_OptionErrorStereoImageRequired },
    { "SubimageSpecificationReturnsNoImages", MGK_OptionErrorSubimageSpecificationReturnsNoImages },
    { "TileNotBoundedByImageDimensions", MGK_OptionErrorTileNotBoundedByImageDimensions },
    { "UnableToAddOrRemoveProfile", MGK_OptionErrorUnableToAddOrRemoveProfile },
    { "UnableToAverageImageSequence", MGK_OptionErrorUnableToAverageImageSequence },
    { "UnableToBlurImage", MGK_OptionErrorUnableToBlurImage },
    { "UnableToChopImage", MGK_OptionErrorUnableToChopImage },
    { "UnableToColorMatrixImage", MGK_OptionErrorUnableToColorMatrixImage },
    { "UnableToConstituteImage", MGK_OptionErrorUnableToConstituteImage },
    { "UnableToConvolveImage", MGK_OptionErrorUnableToConvolveImage },
    { "UnableToEdgeImage", MGK_OptionErrorUnableToEdgeImage },
    { "UnableToEqualizeImage", MGK_OptionErrorUnableToEqualizeImage },
    { "UnableToFilterImage", MGK_OptionErrorUnableToFilterImage },
    { "UnableToFormatImageMetadata", MGK_OptionErrorUnableToFormatImageMetadata },
    { "UnableToFrameImage", MGK_OptionErrorUnableToFrameImage },
    { "UnableToOilPaintImage", MGK_OptionErrorUnableToOilPaintImage },
    { "UnableToPaintImage", MGK_OptionErrorUnableToPaintImage },
    { "UnableToRaiseImage", MGK_OptionErrorUnableToRaiseImage },
    { "UnableToSharpenImage", MGK_OptionErrorUnableToSharpenImage },
    { "UnableToSpreadImage", MGK_OptionErrorUnableToSpreadImage },
    { "UnableToThresholdImage", MGK_OptionErrorUnableToThresholdImage },
    { "UnableToWaveImage", MGK_OptionErrorUnableToWaveImage },
    { "UnrecognizedAttribute", MGK_OptionErrorUnrecognizedAttribute },
    { "UnrecognizedChannelType", MGK_OptionErrorUnrecognizedChannelType },
    { "UnrecognizedColor", MGK_OptionErrorUnrecognizedColor },
    { "UnrecognizedColormapType", MGK_OptionErrorUnrecognizedColormapType },
    { "UnrecognizedColorspace", MGK_OptionErrorUnrecognizedColorspace },
    { "UnrecognizedCommand", MGK_OptionErrorUnrecognizedCommand },
    { "UnrecognizedComposeOperator", MGK_OptionErrorUnrecognizedComposeOperator },
    { "UnrecognizedDisposeMethod", MGK_OptionErrorUnrecognizedDisposeMethod },
    { "UnrecognizedElement", MGK_OptionErrorUnrecognizedElement },
    { "UnrecognizedEndianType", MGK_OptionErrorUnrecognizedEndianType },
    { "UnrecognizedGravityType", MGK_OptionErrorUnrecognizedGravityType },
    { "UnrecognizedHighlightStyle", MGK_OptionErrorUnrecognizedHighlightStyle },
    { "UnrecognizedImageCompression", MGK_OptionErrorUnrecognizedImageCompression },
    { "UnrecognizedImageFilter", MGK_OptionErrorUnrecognizedImageFilter },
    { "UnrecognizedImageFormat", MGK_OptionErrorUnrecognizedImageFormat },
    { "UnrecognizedImageMode", MGK_OptionErrorUnrecognizedImageMode },
    { "UnrecognizedImageType", MGK_OptionErrorUnrecognizedImageType },
    { "UnrecognizedIntentType", MGK_OptionErrorUnrecognizedIntentType },
    { "UnrecognizedInterlaceType", MGK_OptionErrorUnrecognizedInterlaceType },
    { "UnrecognizedListType", MGK_OptionErrorUnrecognizedListType },
    { "UnrecognizedMetric", MGK_OptionErrorUnrecognizedMetric },
    { "UnrecognizedModeType", MGK_OptionErrorUnrecognizedModeType },
    { "UnrecognizedNoiseType", MGK_OptionErrorUnrecognizedNoiseType },
    { "UnrecognizedOperator", MGK_OptionErrorUnrecognizedOperator },
    { "UnrecognizedOption", MGK_OptionErrorUnrecognizedOption },
    { "UnrecognizedPerlMagickMethod", MGK_OptionErrorUnrecognizedPerlMagickMethod },
    { "UnrecognizedPixelMap", MGK_OptionErrorUnrecognizedPixelMap },
    { "UnrecognizedPreviewType", MGK_OptionErrorUnrecognizedPreviewType },
    { "UnrecognizedResourceType", MGK_OptionErrorUnrecognizedResourceType },
    { "UnrecognizedType", MGK_OptionErrorUnrecognizedType },
    { "UnrecognizedUnitsType", MGK_OptionErrorUnrecognizedUnitsType },
    { "UnrecognizedVirtualPixelMethod", MGK_OptionErrorUnrecognizedVirtualPixelMethod },
    { "UnsupportedSamplingFactor", MGK_OptionErrorUnsupportedSamplingFactor },
    { "UsageError", MGK_OptionErrorUsageError },
    { "InvalidColorspaceType", MGK_OptionFatalErrorInvalidColorspaceType },
    { "InvalidEndianType", MGK_OptionFatalErrorInvalidEndianType },
    { "InvalidImageType", MGK_OptionFatalErrorInvalidImageType },
    { "InvalidInterlaceType", MGK_OptionFatalErrorInvalidInterlaceType },
    { "MissingAnImageFilename", MGK_OptionFatalErrorMissingAnImageFilename },
    { "MissingArgument", MGK_OptionFatalErrorMissingArgument },
    { "NoImagesWereLoaded", MGK_OptionFatalErrorNoImagesWereLoaded },
    { "OptionLengthExceedsLimit", MGK_OptionFatalErrorOptionLengthExceedsLimit },
    { "RequestDidNotReturnAnImage", MGK_OptionFatalErrorRequestDidNotReturnAnImage },
    { "UnableToOpenXServer", MGK_OptionFatalErrorUnableToOpenXServer },
    { "UnableToPersistKey", MGK_OptionFatalErrorUnableToPersistKey },
    { "UnrecognizedColormapType", MGK_OptionFatalErrorUnrecognizedColormapType },
    { "UnrecognizedColorspaceType", MGK_OptionFatalErrorUnrecognizedColorspaceType },
    { "UnrecognizedDisposeMethod", MGK_OptionFatalErrorUnrecognizedDisposeMethod },
    { "UnrecognizedEndianType", MGK_OptionFatalErrorUnrecognizedEndianType },
    { "UnrecognizedFilterType", MGK_OptionFatalErrorUnrecognizedFilterType },
    { "UnrecognizedImageCompressionType", MGK_OptionFatalErrorUnrecognizedImageCompressionType },
    { "UnrecognizedImageType", MGK_OptionFatalErrorUnrecognizedImageType },
    { "UnrecognizedInterlaceType", MGK_OptionFatalErrorUnrecognizedInterlaceType },
    { "UnrecognizedOption", MGK_OptionFatalErrorUnrecognizedOption },
    { "UnrecognizedResourceType", MGK_OptionFatalErrorUnrecognizedResourceType },
    { "UnrecognizedVirtualPixelMethod", MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod },
    { "UnrecognizedColor", MGK_OptionWarningUnrecognizedColor },
    { "ImageExpected", MGK_RegistryErrorImageExpected },
    { "ImageInfoExpected", MGK_RegistryErrorImageInfoExpected },
    { "StructureSizeMismatch", MGK_RegistryErrorStructureSizeMismatch },
    { "UnableToGetRegistryID", MGK_RegistryErrorUnableToGetRegistryID },
    { "UnableToLocateImage", MGK_RegistryErrorUnableToLocateImage },
    { "UnableToSetRegistry", MGK_RegistryErrorUnableToSetRegistry },
    { "Default", MGK_RegistryFatalErrorDefault },
    { "Default", MGK_RegistryWarningDefault },
    { "CacheResourcesExhausted", MGK_ResourceLimitErrorCacheResourcesExhausted },
    { "ImagePixelHeightLimitExceeded", MGK_ResourceLimitErrorImagePixelHeightLimitExceeded },
    { "ImagePixelLimitExceeded", MGK_ResourceLimitErrorImagePixelLimitExceeded },
    { "ImagePixelWidthLimitExceeded", MGK_ResourceLimitErrorImagePixelWidthLimitExceeded },
    { "MemoryAllocationFailed", MGK_ResourceLimitErrorMemoryAllocationFailed },
    { "NexusPixelHeightLimitExceeded", MGK_ResourceLimitErrorNexusPixelHeightLimitExceeded },
    { "NexusPixelLimitExceeded", MGK_ResourceLimitErrorNexusPixelLimitExceeded },
    { "NexusPixelWidthLimitExceeded", MGK_ResourceLimitErrorNexusPixelWidthLimitExceeded },
    { "NoPixelsDefinedInCache", MGK_ResourceLimitErrorNoPixelsDefinedInCache },
    { "PixelCacheAllocationFailed", MGK_ResourceLimitErrorPixelCacheAllocationFailed },
    { "ReadLimitExceeded", MGK_ResourceLimitErrorReadLimitExceeded },
    { "UnableToAddColorProfile", MGK_ResourceLimitErrorUnableToAddColorProfile },
    { "UnableToAddGenericProfile", MGK_ResourceLimitErrorUnableToAddGenericProfile },
    { "UnableToAddIPTCProfile", MGK_ResourceLimitErrorUnableToAddIPTCProfile },
    { "UnableToAddOrRemoveProfile", MGK_ResourceLimitErrorUnableToAddOrRemoveProfile },
    { "UnableToAllocateCoefficients", MGK_ResourceLimitErrorUnableToAllocateCoefficients },
    { "UnableToAllocateColormap", MGK_ResourceLimitErrorUnableToAllocateColormap },
    { "UnableToAllocateICCProfile", MGK_ResourceLimitErrorUnableToAllocateICCProfile },
    { "UnableToAllocateImage", MGK_ResourceLimitErrorUnableToAllocateImage },
    { "UnableToAllocateString", MGK_ResourceLimitErrorUnableToAllocateString },
    { "UnableToAnnotateImage", MGK_ResourceLimitErrorUnableToAnnotateImage },
    { "UnableToAverageImageSequence", MGK_ResourceLimitErrorUnableToAverageImageSequence },
    { "UnableToCloneDrawingWand", MGK_ResourceLimitErrorUnableToCloneDrawingWand },
    { "UnableToCloneImage", MGK_ResourceLimitErrorUnableToCloneImage },
    { "UnableToComputeImageSignature", MGK_ResourceLimitErrorUnableToComputeImageSignature },
    { "UnableToConstituteImage", MGK_ResourceLimitErrorUnableToConstituteImage },
    { "UnableToConvertFont", MGK_ResourceLimitErrorUnableToConvertFont },
    { "UnableToConvertStringToTokens", MGK_ResourceLimitErrorUnableToConvertStringToTokens },
    { "UnableToCreateColormap", MGK_ResourceLimitErrorUnableToCreateColormap },
    { "UnableToCreateColorTransform", MGK_ResourceLimitErrorUnableToCreateColorTransform },
    { "UnableToCreateCommandWidget", MGK_ResourceLimitErrorUnableToCreateCommandWidget },
    { "UnableToCreateImageGroup", MGK_ResourceLimitErrorUnableToCreateImageGroup },
    { "UnableToCreateImageMontage", MGK_ResourceLimitErrorUnableToCreateImageMontage },
    { "UnableToCreateXWindow", MGK_ResourceLimitErrorUnableToCreateXWindow },
    { "UnableToCropImage", MGK_ResourceLimitErrorUnableToCropImage },
    { "UnableToDespeckleImage", MGK_ResourceLimitErrorUnableToDespeckleImage },
    { "UnableToDetermineImageClass", MGK_ResourceLimitErrorUnableToDetermineImageClass },
    { "UnableToDetermineTheNumberOfImageColors", MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors },
    { "UnableToDitherImage", MGK_ResourceLimitErrorUnableToDitherImage },
    { "UnableToDrawOnImage", MGK_ResourceLimitErrorUnableToDrawOnImage },
    { "UnableToEdgeImage", MGK_ResourceLimitErrorUnableToEdgeImage },
    { "UnableToEmbossImage", MGK_ResourceLimitErrorUnableToEmbossImage },
    { "UnableToEnhanceImage", MGK_ResourceLimitErrorUnableToEnhanceImage },
    { "UnableToFloodfillImage", MGK_ResourceLimitErrorUnableToFloodfillImage },
    { "UnableToGammaCorrectImage", MGK_ResourceLimitErrorUnableToGammaCorrectImage },
    { "UnableToGetBestIconSize", MGK_ResourceLimitErrorUnableToGetBestIconSize },
    { "UnableToGetFromRegistry", MGK_ResourceLimitErrorUnableToGetFromRegistry },
    { "UnableToGetPackageInfo", MGK_ResourceLimitErrorUnableToGetPackageInfo },
    { "UnableToInterpretMSLImage", MGK_ResourceLimitErrorUnableToInterpretMSLImage },
    { "UnableToLevelImage", MGK_ResourceLimitErrorUnableToLevelImage },
    { "UnableToMagnifyImage", MGK_ResourceLimitErrorUnableToMagnifyImage },
    { "UnableToManageColor", MGK_ResourceLimitErrorUnableToManageColor },
    { "UnableToMapImage", MGK_ResourceLimitErrorUnableToMapImage },
    { "UnableToMapImageSequence", MGK_ResourceLimitErrorUnableToMapImageSequence },
    { "UnableToMedianFilterImage", MGK_ResourceLimitErrorUnableToMedianFilterImage },
    { "UnableToMotionBlurImage", MGK_ResourceLimitErrorUnableToMotionBlurImage },
    { "UnableToNoiseFilterImage", MGK_ResourceLimitErrorUnableToNoiseFilterImage },
    { "UnableToNormalizeImage", MGK_ResourceLimitErrorUnableToNormalizeImage },
    { "UnableToOpenColorProfile", MGK_ResourceLimitErrorUnableToOpenColorProfile },
    { "UnableToQuantizeImage", MGK_ResourceLimitErrorUnableToQuantizeImage },
    { "UnableToQuantizeImageSequence", MGK_ResourceLimitErrorUnableToQuantizeImageSequence },
    { "UnableToReadTextChunk", MGK_ResourceLimitErrorUnableToReadTextChunk },
    { "UnableToReadXImage", MGK_ResourceLimitErrorUnableToReadXImage },
    { "UnableToReadXServerColormap", MGK_ResourceLimitErrorUnableToReadXServerColormap },
    { "UnableToResizeImage", MGK_ResourceLimitErrorUnableToResizeImage },
    { "UnableToRotateImage", MGK_ResourceLimitErrorUnableToRotateImage },
    { "UnableToSampleImage", MGK_ResourceLimitErrorUnableToSampleImage },
    { "UnableToScaleImage", MGK_ResourceLimitErrorUnableToScaleImage },
    { "UnableToSelectImage", MGK_ResourceLimitErrorUnableToSelectImage },
    { "UnableToSharpenImage", MGK_ResourceLimitErrorUnableToSharpenImage },
    { "UnableToShaveImage", MGK_ResourceLimitErrorUnableToShaveImage },
    { "UnableToShearImage", MGK_ResourceLimitErrorUnableToShearImage },
    { "UnableToSortImageColormap", MGK_ResourceLimitErrorUnableToSortImageColormap },
    { "UnableToThresholdImage", MGK_ResourceLimitErrorUnableToThresholdImage },
    { "UnableToTransformColorspace", MGK_ResourceLimitErrorUnableToTransformColorspace },
    { "WriteLimitExceeded", MGK_ResourceLimitErrorWriteLimitExceeded },
    { "MemoryAllocationFailed", MGK_ResourceLimitFatalErrorMemoryAllocationFailed },
    { "SemaporeOperationFailed", MGK_ResourceLimitFatalErrorSemaporeOperationFailed },
    { "UnableToAllocateAscii85Info", MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info },
    { "UnableToAllocateCacheInfo", MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo },
    { "UnableToAllocateCacheView", MGK_ResourceLimitFatalErrorUnableToAllocateCacheView },
    { "UnableToAllocateColorInfo", MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo },
    { "UnableToAllocateDashPattern", MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern },
    { "UnableToAllocateDelegateInfo", MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo },
    { "UnableToAllocateDerivatives", MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives },
    { "UnableToAllocateDrawContext", MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext },
    { "UnableToAllocateDrawInfo", MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo },
    { "UnableToAllocateDrawingWand", MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand },
    { "UnableToAllocateGammaMap", MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap },
    { "UnableToAllocateImage", MGK_ResourceLimitFatalErrorUnableToAllocateImage },
    { "UnableToAllocateImagePixels", MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels },
    { "UnableToAllocateLogInfo", MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo },
    { "UnableToAllocateMagicInfo", MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo },
    { "UnableToAllocateMagickInfo", MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo },
    { "UnableToAllocateMagickMap", MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap },
    { "UnableToAllocateModuleInfo", MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo },
    { "UnableToAllocateMontageInfo", MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo },
    { "UnableToAllocateQuantizeInfo", MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo },
    { "UnableToAllocateRandomKernel", MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel },
    { "UnableToAllocateRegistryInfo", MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo },
    { "UnableToAllocateSemaphoreInfo", MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo },
    { "UnableToAllocateString", MGK_ResourceLimitFatalErrorUnableToAllocateString },
    { "UnableToAllocateTypeInfo", MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo },
    { "UnableToAllocateWand", MGK_ResourceLimitFatalErrorUnableToAllocateWand },
    { "UnableToAnimateImageSequence", MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence },
    { "UnableToCloneBlobInfo", MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo },
    { "UnableToCloneCacheInfo", MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo },
    { "UnableToCloneImage", MGK_ResourceLimitFatalErrorUnableToCloneImage },
    { "UnableToCloneImageInfo", MGK_ResourceLimitFatalErrorUnableToCloneImageInfo },
    { "UnableToConcatenateString", MGK_ResourceLimitFatalErrorUnableToConcatenateString },
    { "UnableToConvertText", MGK_ResourceLimitFatalErrorUnableToConvertText },
    { "UnableToCreateColormap", MGK_ResourceLimitFatalErrorUnableToCreateColormap },
    { "UnableToDestroySemaphore", MGK_ResourceLimitFatalErrorUnableToDestroySemaphore },
    { "UnableToDisplayImage", MGK_ResourceLimitFatalErrorUnableToDisplayImage },
    { "UnableToEscapeString", MGK_ResourceLimitFatalErrorUnableToEscapeString },
    { "UnableToInitializeSemaphore", MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore },
    { "UnableToInterpretMSLImage", MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage },
    { "UnableToLockSemaphore", MGK_ResourceLimitFatalErrorUnableToLockSemaphore },
    { "UnableToObtainRandomEntropy", MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy },
    { "UnableToUnlockSemaphore", MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore },
    { "MemoryAllocationFailed", MGK_ResourceLimitWarningMemoryAllocationFailed },
    { "ImageDoesNotContainTheStreamGeometry", MGK_StreamErrorImageDoesNotContainTheStreamGeometry },
    { "NoStreamHandlerIsDefined", MGK_StreamErrorNoStreamHandlerIsDefined },
    { "PixelCacheIsNotOpen", MGK_StreamErrorPixelCacheIsNotOpen },
    { "UnableToAcquirePixelStream", MGK_StreamErrorUnableToAcquirePixelStream },
    { "UnableToSetPixelStream", MGK_StreamErrorUnableToSetPixelStream },
    { "UnableToSyncPixelStream", MGK_StreamErrorUnableToSyncPixelStream },
    { "Default", MGK_StreamFatalErrorDefault },
    { "Default", MGK_StreamWarningDefault },
    { "FontNotSpecified", MGK_TypeErrorFontNotSpecified },
    { "FontSubstitutionRequired", MGK_TypeErrorFontSubstitutionRequired },
    { "UnableToGetTypeMetrics", MGK_TypeErrorUnableToGetTypeMetrics },
    { "UnableToInitializeFreetypeLibrary", MGK_TypeErrorUnableToInitializeFreetypeLibrary },
    { "UnableToReadFont", MGK_TypeErrorUnableToReadFont },
    { "UnrecognizedFontEncoding", MGK_TypeErrorUnrecognizedFontEncoding },
    { "Default", MGK_TypeFatalErrorDefault },
    { "Default", MGK_TypeWarningDefault },
    { "InvalidColormapIndex", MGK_WandErrorInvalidColormapIndex },
    { "WandAPINotImplemented", MGK_WandErrorWandAPINotImplemented },
    { "WandContainsNoImageIndexs", MGK_WandErrorWandContainsNoImageIndexs },
    { "WandContainsNoImages", MGK_WandErrorWandContainsNoImages },
    { "ColorIsNotKnownToServer", MGK_XServerErrorColorIsNotKnownToServer },
    { "NoWindowWithSpecifiedIDExists", MGK_XServerErrorNoWindowWithSpecifiedIDExists },
    { "StandardColormapIsNotInitialized", MGK_XServerErrorStandardColormapIsNotInitialized },
    { "UnableToConnectToRemoteDisplay", MGK_XServerErrorUnableToConnectToRemoteDisplay },
    { "UnableToCreateBitmap", MGK_XServerErrorUnableToCreateBitmap },
    { "UnableToCreateColormap", MGK_XServerErrorUnableToCreateColormap },
    { "UnableToCreatePixmap", MGK_XServerErrorUnableToCreatePixmap },
    { "UnableToCreateProperty", MGK_XServerErrorUnableToCreateProperty },
    { "UnableToCreateStandardColormap", MGK_XServerErrorUnableToCreateStandardColormap },
    { "UnableToDisplayImageInfo", MGK_XServerErrorUnableToDisplayImageInfo },
    { "UnableToGetProperty", MGK_XServerErrorUnableToGetProperty },
    { "UnableToGetStandardColormap", MGK_XServerErrorUnableToGetStandardColormap },
    { "UnableToGetVisual", MGK_XServerErrorUnableToGetVisual },
    { "UnableToGrabMouse", MGK_XServerErrorUnableToGrabMouse },
    { "UnableToLoadFont", MGK_XServerErrorUnableToLoadFont },
    { "UnableToMatchVisualToStandardColormap", MGK_XServerErrorUnableToMatchVisualToStandardColormap },
    { "UnableToOpenXServer", MGK_XServerErrorUnableToOpenXServer },
    { "UnableToReadXAttributes", MGK_XServerErrorUnableToReadXAttributes },
    { "UnableToReadXWindowImage", MGK_XServerErrorUnableToReadXWindowImage },
    { "UnrecognizedColormapType", MGK_XServerErrorUnrecognizedColormapType },
    { "UnrecognizedGravityType", MGK_XServerErrorUnrecognizedGravityType },
    { "UnrecognizedVisualSpecifier", MGK_XServerErrorUnrecognizedVisualSpecifier },
    { "UnableToAllocateXHints", MGK_XServerFatalErrorUnableToAllocateXHints },
    { "UnableToCreateCursor", MGK_XServerFatalErrorUnableToCreateCursor },
    { "UnableToCreateGraphicContext", MGK_XServerFatalErrorUnableToCreateGraphicContext },
    { "UnableToCreateStandardColormap", MGK_XServerFatalErrorUnableToCreateStandardColormap },
    { "UnableToCreateTextProperty", MGK_XServerFatalErrorUnableToCreateTextProperty },
    { "UnableToCreateXImage", MGK_XServerFatalErrorUnableToCreateXImage },
    { "UnableToCreateXPixmap", MGK_XServerFatalErrorUnableToCreateXPixmap },
    { "UnableToCreateXWindow", MGK_XServerFatalErrorUnableToCreateXWindow },
    { "UnableToDisplayImage", MGK_XServerFatalErrorUnableToDisplayImage },
    { "UnableToDitherImage", MGK_XServerFatalErrorUnableToDitherImage },
    { "UnableToGetPixelInfo", MGK_XServerFatalErrorUnableToGetPixelInfo },
    { "UnableToGetVisual", MGK_XServerFatalErrorUnableToGetVisual },
    { "UnableToLoadFont", MGK_XServerFatalErrorUnableToLoadFont },
    { "UnableToMakeXWindow", MGK_XServerFatalErrorUnableToMakeXWindow },
    { "UnableToOpenXServer", MGK_XServerFatalErrorUnableToOpenXServer },
    { "UnableToViewFonts", MGK_XServerFatalErrorUnableToViewFonts },
    { "UnableToGetVisual", MGK_XServerWarningUnableToGetVisual },
    { "UsingDefaultVisual", MGK_XServerWarningUsingDefaultVisual },
    { "", 0 }
  };
#endif /* if defined(_INCLUDE_TAGMAP_TABLE_) */

#if defined(_INCLUDE_MESSAGE_TABLE_)
static const char message_dat[] =
    "%1\0"
    "Unable to create blob\0"
    "Unable to deduce image format\0"
    "Unable to obtain current offset\0"
    "Unable to open file\0"
    "Unable to read file\0"
    "Unable to read to offset\0"
    "Unable to seek to offset\0"
    "Unable to write blob\0"
    "Unrecognized image format\0"
    "default error\0"
    "default warning\0"
    "Cache nexus contains no pixels\0"
    "Inconsistent persistent cache depth\0"
    "Pixel cache dimensions incompatible with image dimensions\0"
    "Pixel cache is not open\0"
    "Unable to allocate cache view\0"
    "Unable to clone cache\0"
    "Unable to extend cache\0"
    "Unable to get cache nexus\0"
    "Unable to get pixels from cache\0"
    "Unable to open cache\0"
    "Unable to persist pixel cache\0"
    "Unable to read pixel cache\0"
    "Unable to sync cache (check temporary file disk space)\0"
    "disk allocation failed\0"
    "Unable to extend pixel cache\0"
    "default warning\0"
    "Arithmetic overflow\0"
    "Colormap size exceeds limit\0"
    "Colormap type not supported\0"
    "Colorspace model is not supported\0"
    "Color type not supported\0"
    "Compression not valid\0"
    "Data encoding scheme is not supported\0"
    "Data storage type is not supported\0"
    "Coder did not return an image (this is a bug, please report it!)\0"
    "Delta-PNG is not supported\0"
    "Division by zero\0"
    "Encrypted WPG image file not supported\0"
    "Fractal compression not supported\0"
    "Image column or row size is not supported\0"
    "Image does not have a matte channel\0"
    "Image is not tiles\0"
    "Image type not supported\0"
    "Incompatible size of double\0"
    "Irregular channel geometry not supported\0"
    "JNG compression is not supported\0"
    "JPEG compression is not supported\0"
    "JPEG embedding failed\0"
    "JXL decoder API failure\0"
    "JXL encoder API failure\0"
    "Location type is not supported\0"
    "Map storage type is not supported\0"
    "MSB order not supported bitmap\0"
    "Multi-dimensional matrices are not supported\0"
    "Multiple record list not supported\0"
    "No 8BIM data is available\0"
    "No APP1 data is available\0"
    "No bitmap on clipboard\0"
    "No color profile available\0"
    "No data returned\0"
    "No image vector graphics\0"
    "No IPTC info was found\0"
    "No IPTC profile available\0"
    "Number of images is not supported\0"
    "Only continuous tone picture supported\0"
    "Only level zero files Supported\0"
    "PNG compression is not supported\0"
    "PNG library is too old\0"
    "RLE compression not supported\0"
    "Subsampling requires that image width be evenly divisible by two\0"
    "Unable to copy profile\0"
    "Unable to create a DC\0"
    "Unable to create bitmap\0"
    "Unable to decompress image\0"
    "Unable to Initialize FPX library\0"
    "Unable to open blob\0"
    "Unable to read aspect ratio\0"
    "Unable to read CIELAB images\0"
    "Unable to read summary info\0"
    "Unable to set affine matrix\0"
    "Unable to set aspect ratio\0"
    "Unable to set color twist\0"
    "Unable to set contrast\0"
    "Unable to set filtering value\0"
    "Unable to set image comment\0"
    "Unable to set image title\0"
    "Unable to set JPEG level\0"
    "Unable to set region of interest\0"
    "Unable to set summary info\0"
    "Unable to translate text\0"
    "Unable to write MPEG parameters\0"
    "Unable to write to temporary file\0"
    "Unable to zip-compress image\0"
    "Unsupported bits per sample\0"
    "Unsupported cell type in the matrix\0"
    "Unsupported number of columns\0"
    "Unsupported number of rows\0"
    "Unsupported samples per pixel\0"
    "WebP decoding failed: user abort\0"
    "WebP encoding failed: unknown reason\0"
    "WebP encoding failed: bad dimension\0"
    "WebP encoding failed: bad write\0"
    "WebP encoding failed: bitstream out of memory\0"
    "WebP encoding failed: File too big (> 4GB)\0"
    "WebP encoding failed: invalid configuration\0"
    "WebP encoding failed: null parameter\0"
    "WebP encoding failed: out of memory\0"
    "WebP encoding failed: partition 0 overflow (> 512K)\0"
    "WebP encoding failed: partition overflow (> 16M)\0"
    "WebP encoding failed: user abort\0"
    "Invalid WebP configuration parameters supplied\0"
    "WebP failed: invalid parameter\0"
    "ZIP compression is not supported\0"
    "default error\0"
    "Lossless to lossy JPEG conversion\0"
    "include element nested too deeply\0"
    "Registry key lookup failed. Package is not properly installed on this machine.\0"
    "String token maximum length exceeded\0"
    "Unable to access configuration file\0"
    "Unable to access font file\0"
    "Unable to access log configuration file\0"
    "Unable to access module file\0"
    "default error\0"
    "Unable to change to working directory\0"
    "Unable to get current working directory\0"
    "Unable to restore current working directory\0"
    "default warning\0"
    "An error has occurred reading from file\0"
    "An error has occurred writing to file\0"
    "Colormap exceeded colors limit\0"
    "Compression not valid\0"
    "Corrupt image\0"
    "Image file or blob does not contain any image data\0"
    "Image file has no scenes\0"
    "Image type not supported\0"
    "Improper image header\0"
    "Insufficient image data in file\0"
    "Invalid colormap index\0"
    "invalid file format version\0"
    "Length and filesize do not match\0"
    "Missing a required image channel\0"
    "Negative or zero image size\0"
    "Non OS2 BMP header size less than 40\0"
    "Not enough tiles found in level\0"
    "Static planes value not equal to 1\0"
    "Subsampling requires that image width be evenly divisible by two\0"
    "Too much image data in file\0"
    "Unable to read colormap from dump file\0"
    "Unable to read color profile\0"
    "Unable to read extension block\0"
    "Unable to read generic profile\0"
    "Unable to read image data\0"
    "Unable to read image header\0"
    "Unable to read IPTC profile\0"
    "Unable to read pixmap from dump file\0"
    "Unable to read sub image data\0"
    "Unable to read VID image\0"
    "Unable to read window name from dump file\0"
    "Unable to runlength decode image\0"
    "Unable to uncompress image\0"
    "Unexpected end-of-file\0"
    "Unexpected sampling factor\0"
    "Unknown pattern type\0"
    "Unrecognized bits per pixel\0"
    "Unrecognized compression\0"
    "Unrecognized number of colors\0"
    "Unrecognized XWD header\0"
    "Unsupported bits per sample\0"
    "Unsupported number of planes\0"
    "Unable to persist key\0"
    "Compression not valid\0"
    "Corrupt image (some data returned)\0"
    "Improper image header\0"
    "Invalid colormap index\0"
    "Length and filesize do not match\0"
    "Negative or zero image size\0"
    "Non OS2 header size error\0"
    "Corrupt PCD image, skipping to sync byte\0"
    "Static planes value not equal to one\0"
    "Unable to parse embedded profile\0"
    "Unrecognized bits per pixel\0"
    "Unrecognized image compression\0"
    "Delegate failed\0"
    "Failed to allocate argument list.\0"
    "Failed to allocate Ghostscript interpreter.\0"
    "Failed to compute output size\0"
    "Failed to find Ghostscript (not installed?).\0"
    "Failed to render file\0"
    "Failed to scan file\0"
    "No tag found\0"
    "Postscript delegate failed\0"
    "Unable to create image\0"
    "Unable to create image component\0"
    "Unable to decode image file\0"
    "Unable to encode image file\0"
    "Unable to initialize FPX library\0"
    "Unable to initialize WMF library\0"
    "Unable to manage JP2 stream\0"
    "Unable to write SVG format\0"
    "WebP library ABI does not match header ABI (build issue!)\0"
    "default error\0"
    "default warning\0"
    "Already pushing pattern definition\0"
    "arithmetic overflow\0"
    "drawing recursion detected\0"
    "text value does not convert to float\0"
    "text value does not convert to integer\0"
    "invalid primitive argument\0"
    "Non-conforming drawing primitive definition\0"
    "primitive arithmetic overflow\0"
    "too many coordinates\0"
    "unable to draw on image\0"
    "Unable to print\0"
    "unbalanced graphic context push-pop\0"
    "unbalanced push-pop\0"
    "unreasonable affine matrix\0"
    "unreasonable dash polygon length\0"
    "unreasonable gradient image size\0"
    "vector path truncated\0"
    "default error\0"
    "Not a relative URL\0"
    "Not currently pushing pattern definition\0"
    "URL not found\0"
    "Unable to create temporary file\0"
    "Unable to open file\0"
    "Unable to write file\0"
    "default error\0"
    "default warning\0"
    "angle is discontinuous\0"
    "CMYKA image lacks an alpha channel (indexes)\0"
    "Colorspace color profile mismatch\0"
    "image colorspace differs\0"
    "image colorspace mismatch\0"
    "image difference exceeds limit\0"
    "image does not contain resolution\0"
    "image is not colormapped\0"
    "image opacity differs\0"
    "Image sequence is required\0"
    "image size differs\0"
    "Invalid colormap index\0"
    "left and right image sizes differ\0"
    "no images were found\0"
    "no images were loaded\0"
    "no [LOCALE] image attribute\0"
    "too many cluster\0"
    "unable to append image\0"
    "Unable to assign profile\0"
    "unable to average image\0"
    "unable to coalesce image\0"
    "unable to compare images\0"
    "unable to create image mosaic\0"
    "unable to create stereo image\0"
    "unable to deconstruct image sequence\0"
    "unable to export image pixels\0"
    "unable to flatten image\0"
    "Unable to get clip mask\0"
    "Unable to get composite mask\0"
    "unable to handle image channel\0"
    "unable to import image pixels\0"
    "unable to resize image\0"
    "unable to segment image\0"
    "Unable to set clip mask\0"
    "Unable to set composite mask\0"
    "unable to shear image\0"
    "width or height exceeds limit\0"
    "Unable to persist key\0"
    "default warning\0"
    "DPS library is not available\0"
    "FPX library is not available\0"
    "FreeType library is not available\0"
    "JPEG compression library is not available\0"
    "LCMS encoding not enabled\0"
    "LZW encoding not enabled\0"
    "No decode delegate for this image format\0"
    "No encode delegate for this image format\0"
    "TIFF library is not available\0"
    "XML library is not available\0"
    "X Window library is not available\0"
    "ZLIB compression library is not available\0"
    "default error\0"
    "default warning\0"
    "Failed to close module\0"
    "Failed to find symbol\0"
    "Unable to load module\0"
    "Unable to register image format\0"
    "Unrecognized module\0"
    "Unable to initialize module loader\0"
    "default warning\0"
    "default error\0"
    "default error\0"
    "User requested termination (via signal)\0"
    "default warning\0"
    "bevel width is negative\0"
    "color separated image required\0"
    "frame is less than image size\0"
    "geometry dimensions are zero\0"
    "geometry does not contain image\0"
    "hald clut image dimensions are invalid\0"
    "images are not the same size\0"
    "size must exceed bevel width\0"
    "image smaller than kernel width\0"
    "image smaller than radius\0"
    "image widths or heights differ\0"
    "input images already specified\0"
    "Invalid subimage specification\0"
    "kernel radius is too small\0"
    "kernel width must be an odd number\0"
    "Matrix is not square (%s elements)\0"
    "Matrix size is out of range\0"
    "Missing an image filename\0"
    "Option '%s' requires an argument or argument is malformed\0"
    "Must specify a image name\0"
    "Must specify image size\0"
    "No Binary Large OBjects defined\0"
    "No images defined\0"
    "Non-zero width and height required\0"
    "No profile name was given\0"
    "Null blob argument\0"
    "Reference image required\0"
    "Reference is not my type\0"
    "Region area exceeds implementation limit\0"
    "Request did not return an image\0"
    "Stegano image required\0"
    "Stereo image required\0"
    "Subimage specification returns no images\0"
    "Tile is not bounded by image dimensions\0"
    "Unable to add or remove profile\0"
    "unable to average image sequence\0"
    "unable to blur image\0"
    "unable to chop image\0"
    "Unable to color matrix image\0"
    "Unable to constitute image\0"
    "Unable to convolve image\0"
    "Unable to edge image\0"
    "Unable to equalize image\0"
    "Unable to filter image\0"
    "unable to format image meta data\0"
    "Unable to frame image\0"
    "unable to oil paint image\0"
    "Unable to paint image\0"
    "Unable to raise image\0"
    "Unable to sharpen image\0"
    "Unable to spread image\0"
    "Unable to threshold image\0"
    "Unable to wave image\0"
    "Unrecognized attribute\0"
    "Unrecognized channel type\0"
    "Unrecognized color\0"
    "Unrecognized colormap type\0"
    "Unrecognized image colorspace\0"
    "Unrecognized command '%s'. Use -help for a usage summary or see manual.\0"
    "Unrecognized compose operator\0"
    "Unrecognized dispose method\0"
    "Unrecognized element\0"
    "Unrecognized endian type\0"
    "Unrecognized gravity type\0"
    "Unrecognized highlight style\0"
    "Unrecognized image compression\0"
    "Unrecognized image filter\0"
    "Unrecognized image format\0"
    "Unrecognized image mode\0"
    "Unrecognized image type\0"
    "Unrecognized intent type\0"
    "Unrecognized interlace type\0"
    "Unrecognized list type\0"
    "Unrecognized error metric\0"
    "Unrecognized mode type\0"
    "Unrecognized noise type\0"
    "Unrecognized operator\0"
    "Unrecognized option\0"
    "Unrecognized PerlMagick method\0"
    "Unrecognized pixel map\0"
    "Unrecognized preview type\0"
    "Unrecognized resource type\0"
    "Unrecognized type\0"
    "Unrecognized units type\0"
    "Unrecognized virtual pixel method\0"
    "Unsupported sampling factor\0"
    "Improper arguments supplied, please see manual\0"
    "Invalid colorspace type\0"
    "Invalid endian type\0"
    "Invalid image type\0"
    "Invalid interlace type\0"
    "Missing an image filename\0"
    "Option '%s' requires an argument or argument is malformed\0"
    "No images were loaded\0"
    "Option length exceeds limit\0"
    "Request did not return an image\0"
    "Unable to open XServer\0"
    "Unable to persist key\0"
    "Unrecognized colormap type\0"
    "Unrecognized colorspace type\0"
    "unrecognized dispose method\0"
    "Unrecognized endian type\0"
    "Unrecognized filter type\0"
    "unrecognized compression type\0"
    "Unrecognized image type\0"
    "Unrecognized interlace type\0"
    "Unrecognized option\0"
    "Unrecognized resource type\0"
    "Unrecognized virtual pixel method\0"
    "Unrecognized color\0"
    "image expected\0"
    "image info expected\0"
    "structure size mismatch\0"
    "Unable to get registry ID\0"
    "Unable to locate image\0"
    "Unable to set registry\0"
    "default error\0"
    "default warning\0"
    "Disk space limit exceeded (see -limit Disk)\0"
    "Image pixel height limit exceeded (see -limit Height)\0"
    "Image pixel limit exceeded (see -limit Pixels)\0"
    "Image pixel width limit exceeded (see -limit Width)\0"
    "Memory allocation failed\0"
    "Pixel nexus height limit exceeded (see -limit Height)\0"
    "Pixel nexus limit exceeded (see -limit Pixels)\0"
    "Pixel nexus width limit exceeded (see -limit Width)\0"
    "No pixels defined in cache\0"
    "Pixel cache allocation failed\0"
    "Read limit exceeded (see -limit Read)\0"
    "unable to add ICC Color profile\0"
    "unable to add generic profile\0"
    "unable to add IPTC profile\0"
    "unable to add or remove profile\0"
    "unable to allocate coefficients\0"
    "Unable to allocate colormap\0"
    "unable to allocate ICC profile\0"
    "Unable to allocate image\0"
    "unable to allocate string\0"
    "Unable to annotate image\0"
    "unable to average image sequence\0"
    "unable to clone drawing wand\0"
    "unable to clone image\0"
    "unable to compute image signature\0"
    "unable to constitute image\0"
    "unable to convert font\0"
    "unable to convert strings to tokens\0"
    "Unable to create colormap\0"
    "unable to create color transform\0"
    "unable to create command widget\0"
    "unable to create image group\0"
    "Unable to create image montage\0"
    "unable to create X window\0"
    "unable to crop image\0"
    "unable to despeckle image\0"
    "unable to determine image class\0"
    "unable to determine the number of image colors\0"
    "unable to dither image\0"
    "unable to draw on image\0"
    "unable to edge image\0"
    "unable to emboss image\0"
    "unable to enhance image\0"
    "unable to floodfill image\0"
    "unable to gamma correct image\0"
    "unable to get best icon size\0"
    "unable to get from registry\0"
    "Unable to get package info\0"
    "unable to interpret MSL image\0"
    "unable to level image\0"
    "unable to magnify image\0"
    "Unable to manage color\0"
    "Unable to map image\0"
    "Unable to map image sequence\0"
    "unable to median filter image\0"
    "unable to motion blur image\0"
    "unable to noise filter image\0"
    "unable to normalize image\0"
    "unable to open color profile\0"
    "unable to quantize image\0"
    "unable to quantize image sequence\0"
    "unable to read text chunk\0"
    "unable to read X image\0"
    "unable to read X server colormap\0"
    "unable to resize image\0"
    "unable to rotate image\0"
    "unable to sample image\0"
    "unable to scale image\0"
    "unable to select image\0"
    "unable to sharpen image\0"
    "unable to shave image\0"
    "unable to shear image\0"
    "unable to sort image colormap\0"
    "unable to threshold image\0"
    "unable to transform colorspace\0"
    "Write limit exceeded (see -limit Write)\0"
    "Memory allocation failed\0"
    "Semaphore operation failed\0"
    "unable to allocate ascii85 info\0"
    "unable to allocate cache info\0"
    "unable to allocate cache view\0"
    "unable to allocate color info\0"
    "unable to allocate dash pattern\0"
    "unable to allocate delegate info\0"
    "unable to allocate derivates\0"
    "unable to allocate draw context\0"
    "unable to allocate draw info\0"
    "unable to allocate drawing wand\0"
    "unable to allocate gamma map\0"
    "unable to allocate image\0"
    "unable to allocate image pixels\0"
    "unable to allocate log info\0"
    "unable to allocate magic info\0"
    "unable to allocate magick info\0"
    "unable to allocate magick map\0"
    "unable to allocate module info\0"
    "unable to allocate montage info\0"
    "unable to allocate quantize info\0"
    "unable to allocate random kernel\0"
    "unable to allocate registry info\0"
    "unable to allocate semaphore info\0"
    "unable to allocate string\0"
    "unable to allocate type info\0"
    "unable to allocate wand\0"
    "unable to animate image sequence\0"
    "unable to clone blob info\0"
    "unable to clone cache info\0"
    "unable to clone image\0"
    "unable to clone image info\0"
    "unable to concatenate string\0"
    "unable to convert text\0"
    "unable to create colormap\0"
    "unable to destroy semaphore\0"
    "unable to display image\0"
    "unable to escape string\0"
    "unable to initialize semaphore\0"
    "unable to interpret MSL image\0"
    "unable to lock semaphore\0"
    "unable to obtain random bytes from operating system\0"
    "unable to unlock semaphore\0"
    "Memory allocation failed\0"
    "image does not contain the stream geometry\0"
    "no stream handler is defined\0"
    "Pixel cache is not open\0"
    "Unable to acquire pixel stream\0"
    "Unable to set pixel stream\0"
    "Unable to sync pixel stream\0"
    "default error\0"
    "default warning\0"
    "Font name not specified\0"
    "Font substitution required\0"
    "Unable to get type metrics\0"
    "Unable to initialize freetype library\0"
    "Unable to read font\0"
    "Unrecognized font encoding\0"
    "default error\0"
    "default warning\0"
    "invalid colormap index `%.1024s\0"
    "Wand API not implemented `%.1024s\0"
    "Wand contains no image indices `%.1024s\0"
    "Wand contains no images `%.1024s\0"
    "Color is not known to server\0"
    "No window with specified ID exists\0"
    "Standard Colormap is not initialized\0"
    "Unable to connect to remote display\0"
    "Unable to create bitmap\0"
    "Unable to create colormap\0"
    "Unable to create pixmap\0"
    "Unable to create property\0"
    "Unable to create standard colormap\0"
    "Unable to display image info\0"
    "Unable to get property\0"
    "Unable to get Standard Colormap\0"
    "Unable to get visual\0"
    "Unable to grab mouse\0"
    "Unable to load font\0"
    "Unable to match visual to Standard Colormap\0"
    "Unable to open X server\0"
    "Unable to read X attributes\0"
    "Unable to read X window image\0"
    "Unrecognized colormap type\0"
    "Unrecognized gravity type\0"
    "Unrecognized visual specifier\0"
    "Unable to allocate X hints\0"
    "Unable to create X cursor\0"
    "Unable to create graphic context\0"
    "unable to create standard colormap\0"
    "Unable to create text property\0"
    "Unable to create X image\0"
    "Unable to create X pixmap\0"
    "Unable to create X window\0"
    "unable to display image\0"
    "unable to dither image\0"
    "Unable to get pixel info\0"
    "Unable to get visual\0"
    "Unable to load font\0"
    "Unable to make X window\0"
    "Unable to open X server\0"
    "Unable to view fonts\0"
    "Unable to get visual\0"
    "UsingDefaultVisual\0"
  ;

static const unsigned short message_dat_offsets[] =
  {
    0,
    3,
    25,
    55,
    87,
    107,
    127,
    152,
    177,
    198,
    224,
    238,
    254,
    285,
    321,
    379,
    403,
    433,
    455,
    478,
    504,
    536,
    557,
    587,
    614,
    669,
    692,
    721,
    737,
    757,
    785,
    813,
    847,
    872,
    894,
    932,
    967,
    1032,
    1059,
    1076,
    1115,
    1149,
    1191,
    1227,
    1246,
    1271,
    1299,
    1340,
    1373,
    1407,
    1429,
    1453,
    1477,
    1508,
    1542,
    1573,
    1618,
    1653,
    1679,
    1705,
    1728,
    1755,
    1772,
    1797,
    1820,
    1846,
    1880,
    1919,
    1951,
    1984,
    2007,
    2037,
    2102,
    2125,
    2147,
    2171,
    2198,
    2231,
    2251,
    2279,
    2308,
    2336,
    2364,
    2391,
    2417,
    2440,
    2470,
    2498,
    2524,
    2549,
    2582,
    2609,
    2634,
    2666,
    2700,
    2729,
    2757,
    2793,
    2823,
    2850,
    2880,
    2913,
    2950,
    2986,
    3018,
    3064,
    3107,
    3151,
    3188,
    3224,
    3276,
    3325,
    3358,
    3405,
    3436,
    3469,
    3483,
    3517,
    3551,
    3630,
    3667,
    3703,
    3730,
    3770,
    3799,
    3813,
    3851,
    3891,
    3935,
    3951,
    3991,
    4029,
    4060,
    4082,
    4096,
    4147,
    4172,
    4197,
    4219,
    4251,
    4274,
    4302,
    4335,
    4368,
    4396,
    4433,
    4465,
    4500,
    4565,
    4593,
    4632,
    4661,
    4692,
    4723,
    4749,
    4777,
    4805,
    4842,
    4872,
    4897,
    4939,
    4972,
    4999,
    5022,
    5049,
    5070,
    5098,
    5123,
    5153,
    5177,
    5205,
    5234,
    5256,
    5278,
    5313,
    5335,
    5358,
    5391,
    5419,
    5445,
    5486,
    5523,
    5556,
    5584,
    5615,
    5631,
    5665,
    5709,
    5739,
    5784,
    5806,
    5826,
    5839,
    5866,
    5889,
    5922,
    5950,
    5978,
    6011,
    6044,
    6072,
    6099,
    6157,
    6171,
    6187,
    6222,
    6242,
    6269,
    6306,
    6345,
    6372,
    6416,
    6446,
    6467,
    6491,
    6507,
    6543,
    6563,
    6590,
    6623,
    6656,
    6678,
    6692,
    6711,
    6752,
    6766,
    6798,
    6818,
    6839,
    6853,
    6869,
    6892,
    6937,
    6971,
    6996,
    7022,
    7053,
    7087,
    7112,
    7134,
    7161,
    7180,
    7203,
    7237,
    7258,
    7280,
    7308,
    7325,
    7348,
    7373,
    7397,
    7422,
    7447,
    7477,
    7507,
    7544,
    7574,
    7598,
    7622,
    7651,
    7682,
    7712,
    7735,
    7759,
    7783,
    7812,
    7834,
    7864,
    7886,
    7902,
    7931,
    7960,
    7994,
    8036,
    8062,
    8087,
    8128,
    8169,
    8199,
    8228,
    8262,
    8304,
    8318,
    8334,
    8357,
    8379,
    8401,
    8433,
    8453,
    8488,
    8504,
    8518,
    8532,
    8572,
    8588,
    8612,
    8643,
    8673,
    8702,
    8734,
    8773,
    8802,
    8831,
    8863,
    8889,
    8920,
    8951,
    8982,
    9009,
    9044,
    9079,
    9107,
    9133,
    9191,
    9217,
    9241,
    9273,
    9291,
    9326,
    9352,
    9371,
    9396,
    9421,
    9462,
    9494,
    9517,
    9539,
    9580,
    9620,
    9652,
    9685,
    9706,
    9727,
    9756,
    9783,
    9808,
    9829,
    9854,
    9877,
    9910,
    9932,
    9958,
    9980,
    10002,
    10026,
    10049,
    10075,
    10096,
    10119,
    10145,
    10164,
    10191,
    10221,
    10293,
    10323,
    10351,
    10372,
    10397,
    10423,
    10452,
    10483,
    10509,
    10535,
    10559,
    10583,
    10608,
    10636,
    10659,
    10685,
    10708,
    10732,
    10754,
    10774,
    10805,
    10828,
    10854,
    10881,
    10899,
    10923,
    10957,
    10985,
    11032,
    11056,
    11076,
    11095,
    11118,
    11144,
    11202,
    11224,
    11252,
    11284,
    11307,
    11329,
    11356,
    11385,
    11413,
    11438,
    11463,
    11493,
    11517,
    11545,
    11565,
    11592,
    11626,
    11645,
    11660,
    11680,
    11704,
    11730,
    11753,
    11776,
    11790,
    11806,
    11850,
    11904,
    11951,
    12003,
    12028,
    12082,
    12129,
    12181,
    12208,
    12238,
    12276,
    12308,
    12338,
    12365,
    12397,
    12429,
    12457,
    12488,
    12513,
    12539,
    12564,
    12597,
    12626,
    12648,
    12682,
    12709,
    12732,
    12768,
    12794,
    12827,
    12859,
    12888,
    12919,
    12945,
    12966,
    12992,
    13024,
    13071,
    13094,
    13118,
    13139,
    13162,
    13186,
    13212,
    13242,
    13271,
    13299,
    13326,
    13356,
    13378,
    13402,
    13425,
    13445,
    13474,
    13504,
    13532,
    13561,
    13587,
    13616,
    13641,
    13675,
    13701,
    13724,
    13757,
    13780,
    13803,
    13826,
    13848,
    13871,
    13895,
    13917,
    13939,
    13969,
    13995,
    14026,
    14066,
    14091,
    14118,
    14150,
    14180,
    14210,
    14240,
    14272,
    14305,
    14334,
    14366,
    14395,
    14427,
    14456,
    14481,
    14513,
    14541,
    14571,
    14602,
    14632,
    14663,
    14695,
    14728,
    14761,
    14794,
    14828,
    14854,
    14883,
    14907,
    14940,
    14966,
    14993,
    15015,
    15042,
    15071,
    15094,
    15120,
    15148,
    15172,
    15196,
    15227,
    15257,
    15282,
    15334,
    15361,
    15386,
    15429,
    15458,
    15482,
    15513,
    15540,
    15568,
    15582,
    15598,
    15622,
    15649,
    15676,
    15714,
    15734,
    15761,
    15775,
    15791,
    15823,
    15857,
    15897,
    15930,
    15959,
    15994,
    16031,
    16067,
    16091,
    16117,
    16141,
    16167,
    16202,
    16231,
    16254,
    16286,
    16307,
    16328,
    16348,
    16392,
    16416,
    16444,
    16474,
    16501,
    16527,
    16557,
    16584,
    16610,
    16643,
    16678,
    16709,
    16734,
    16760,
    16786,
    16810,
    16833,
    16858,
    16879,
    16899,
    16923,
    16947,
    16968,
    16989,
    17008,
    0
  };
#endif /* if defined(_INCLUDE_MESSAGE_TABLE_) */

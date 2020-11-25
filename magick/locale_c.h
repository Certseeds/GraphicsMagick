#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int) MAGICK_FUNC_CONST;

#define MAX_LOCALE_MSGS 585

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
#define MGK_CoderErrorLocationTypeIsNotSupported 50
#define MGK_CoderErrorMapStorageTypeIsNotSupported 51
#define MGK_CoderErrorMSBByteOrderNotSupported 52
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 53
#define MGK_CoderErrorMultipleRecordListNotSupported 54
#define MGK_CoderErrorNo8BIMDataIsAvailable 55
#define MGK_CoderErrorNoAPP1DataIsAvailable 56
#define MGK_CoderErrorNoBitmapOnClipboard 57
#define MGK_CoderErrorNoColorProfileAvailable 58
#define MGK_CoderErrorNoDataReturned 59
#define MGK_CoderErrorNoImageVectorGraphics 60
#define MGK_CoderErrorNoIPTCInfoWasFound 61
#define MGK_CoderErrorNoIPTCProfileAvailable 62
#define MGK_CoderErrorNumberOfImagesIsNotSupported 63
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 64
#define MGK_CoderErrorOnlyLevelZerofilesSupported 65
#define MGK_CoderErrorPNGCompressionNotSupported 66
#define MGK_CoderErrorPNGLibraryTooOld 67
#define MGK_CoderErrorRLECompressionNotSupported 68
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 69
#define MGK_CoderErrorUnableToCopyProfile 70
#define MGK_CoderErrorUnableToCreateADC 71
#define MGK_CoderErrorUnableToCreateBitmap 72
#define MGK_CoderErrorUnableToDecompressImage 73
#define MGK_CoderErrorUnableToInitializeFPXLibrary 74
#define MGK_CoderErrorUnableToOpenBlob 75
#define MGK_CoderErrorUnableToReadAspectRatio 76
#define MGK_CoderErrorUnableToReadCIELABImages 77
#define MGK_CoderErrorUnableToReadSummaryInfo 78
#define MGK_CoderErrorUnableToSetAffineMatrix 79
#define MGK_CoderErrorUnableToSetAspectRatio 80
#define MGK_CoderErrorUnableToSetColorTwist 81
#define MGK_CoderErrorUnableToSetContrast 82
#define MGK_CoderErrorUnableToSetFilteringValue 83
#define MGK_CoderErrorUnableToSetImageComments 84
#define MGK_CoderErrorUnableToSetImageTitle 85
#define MGK_CoderErrorUnableToSetJPEGLevel 86
#define MGK_CoderErrorUnableToSetRegionOfInterest 87
#define MGK_CoderErrorUnableToSetSummaryInfo 88
#define MGK_CoderErrorUnableToTranslateText 89
#define MGK_CoderErrorUnableToWriteMPEGParameters 90
#define MGK_CoderErrorUnableToWriteTemporaryFile 91
#define MGK_CoderErrorUnableToZipCompressImage 92
#define MGK_CoderErrorUnsupportedBitsPerSample 93
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 94
#define MGK_CoderErrorUnsupportedNumberOfColumns 95
#define MGK_CoderErrorUnsupportedNumberOfRows 96
#define MGK_CoderErrorUnsupportedSamplesPerPixel 97
#define MGK_CoderErrorWebPDecodingFailedUserAbort 98
#define MGK_CoderErrorWebPEncodingFailed 99
#define MGK_CoderErrorWebPEncodingFailedBadDimension 100
#define MGK_CoderErrorWebPEncodingFailedBadWrite 101
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 102
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 103
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 104
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 105
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 106
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 107
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 108
#define MGK_CoderErrorWebPEncodingFailedUserAbort 109
#define MGK_CoderErrorWebPInvalidConfiguration 110
#define MGK_CoderErrorWebPInvalidParameter 111
#define MGK_CoderErrorZipCompressionNotSupported 112
#define MGK_CoderFatalErrorDefault 113
#define MGK_CoderWarningLosslessToLossyJPEGConversion 114
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 115
#define MGK_ConfigureErrorRegistryKeyLookupFailed 116
#define MGK_ConfigureErrorStringTokenLengthExceeded 117
#define MGK_ConfigureErrorUnableToAccessConfigureFile 118
#define MGK_ConfigureErrorUnableToAccessFontFile 119
#define MGK_ConfigureErrorUnableToAccessLogFile 120
#define MGK_ConfigureErrorUnableToAccessModuleFile 121
#define MGK_ConfigureFatalErrorDefault 122
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 123
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 124
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 125
#define MGK_ConfigureWarningDefault 126
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 127
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 128
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 129
#define MGK_CorruptImageErrorCompressionNotValid 130
#define MGK_CorruptImageErrorCorruptImage 131
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 132
#define MGK_CorruptImageErrorImageFileHasNoScenes 133
#define MGK_CorruptImageErrorImageTypeNotSupported 134
#define MGK_CorruptImageErrorImproperImageHeader 135
#define MGK_CorruptImageErrorInsufficientImageDataInFile 136
#define MGK_CorruptImageErrorInvalidColormapIndex 137
#define MGK_CorruptImageErrorInvalidFileFormatVersion 138
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 139
#define MGK_CorruptImageErrorMissingImageChannel 140
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 141
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 142
#define MGK_CorruptImageErrorNotEnoughTiles 143
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 144
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 145
#define MGK_CorruptImageErrorTooMuchImageDataInFile 146
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 147
#define MGK_CorruptImageErrorUnableToReadColorProfile 148
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 149
#define MGK_CorruptImageErrorUnableToReadGenericProfile 150
#define MGK_CorruptImageErrorUnableToReadImageData 151
#define MGK_CorruptImageErrorUnableToReadImageHeader 152
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 153
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 154
#define MGK_CorruptImageErrorUnableToReadSubImageData 155
#define MGK_CorruptImageErrorUnableToReadVIDImage 156
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 157
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 158
#define MGK_CorruptImageErrorUnableToUncompressImage 159
#define MGK_CorruptImageErrorUnexpectedEndOfFile 160
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 161
#define MGK_CorruptImageErrorUnknownPatternType 162
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 163
#define MGK_CorruptImageErrorUnrecognizedImageCompression 164
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 165
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 166
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 167
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 168
#define MGK_CorruptImageFatalErrorUnableToPersistKey 169
#define MGK_CorruptImageWarningCompressionNotValid 170
#define MGK_CorruptImageWarningCorruptImage 171
#define MGK_CorruptImageWarningImproperImageHeader 172
#define MGK_CorruptImageWarningInvalidColormapIndex 173
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 174
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 175
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 176
#define MGK_CorruptImageWarningSkipToSyncByte 177
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 178
#define MGK_CorruptImageWarningUnableToParseEmbeddedProfile 179
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 180
#define MGK_CorruptImageWarningUnrecognizedImageCompression 181
#define MGK_DelegateErrorDelegateFailed 182
#define MGK_DelegateErrorFailedToAllocateArgumentList 183
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 184
#define MGK_DelegateErrorFailedToComputeOutputSize 185
#define MGK_DelegateErrorFailedToFindGhostscript 186
#define MGK_DelegateErrorFailedToRenderFile 187
#define MGK_DelegateErrorFailedToScanFile 188
#define MGK_DelegateErrorNoTagFound 189
#define MGK_DelegateErrorPostscriptDelegateFailed 190
#define MGK_DelegateErrorUnableToCreateImage 191
#define MGK_DelegateErrorUnableToCreateImageComponent 192
#define MGK_DelegateErrorUnableToDecodeImageFile 193
#define MGK_DelegateErrorUnableToEncodeImageFile 194
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 195
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 196
#define MGK_DelegateErrorUnableToManageJP2Stream 197
#define MGK_DelegateErrorUnableToWriteSVGFormat 198
#define MGK_DelegateErrorWebPABIMismatch 199
#define MGK_DelegateFatalErrorDefault 200
#define MGK_DelegateWarningDefault 201
#define MGK_DrawErrorAlreadyPushingPatternDefinition 202
#define MGK_DrawErrorArithmeticOverflow 203
#define MGK_DrawErrorDrawingRecursionDetected 204
#define MGK_DrawErrorFloatValueConversionError 205
#define MGK_DrawErrorIntegerValueConversionError 206
#define MGK_DrawErrorInvalidPrimitiveArgument 207
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 208
#define MGK_DrawErrorPrimitiveArithmeticOverflow 209
#define MGK_DrawErrorTooManyCoordinates 210
#define MGK_DrawErrorUnableToDrawOnImage 211
#define MGK_DrawErrorUnableToPrint 212
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 213
#define MGK_DrawErrorUnbalancedPushPop 214
#define MGK_DrawErrorUnreasonableDashPolygonLength 215
#define MGK_DrawErrorUnreasonableGradientSize 216
#define MGK_DrawErrorVectorPathTruncated 217
#define MGK_DrawFatalErrorDefault 218
#define MGK_DrawWarningNotARelativeURL 219
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 220
#define MGK_DrawWarningURLNotFound 221
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 222
#define MGK_FileOpenErrorUnableToOpenFile 223
#define MGK_FileOpenErrorUnableToWriteFile 224
#define MGK_FileOpenFatalErrorDefault 225
#define MGK_FileOpenWarningDefault 226
#define MGK_ImageErrorAngleIsDiscontinuous 227
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 228
#define MGK_ImageErrorColorspaceColorProfileMismatch 229
#define MGK_ImageErrorImageColorspaceDiffers 230
#define MGK_ImageErrorImageColorspaceMismatch 231
#define MGK_ImageErrorImageDifferenceExceedsLimit 232
#define MGK_ImageErrorImageDoesNotContainResolution 233
#define MGK_ImageErrorImageIsNotColormapped 234
#define MGK_ImageErrorImageOpacityDiffers 235
#define MGK_ImageErrorImageSequenceIsRequired 236
#define MGK_ImageErrorImageSizeDiffers 237
#define MGK_ImageErrorInvalidColormapIndex 238
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 239
#define MGK_ImageErrorNoImagesWereFound 240
#define MGK_ImageErrorNoImagesWereLoaded 241
#define MGK_ImageErrorNoLocaleImageAttribute 242
#define MGK_ImageErrorTooManyClusters 243
#define MGK_ImageErrorUnableToAppendImage 244
#define MGK_ImageErrorUnableToAssignProfile 245
#define MGK_ImageErrorUnableToAverageImage 246
#define MGK_ImageErrorUnableToCoalesceImage 247
#define MGK_ImageErrorUnableToCompareImages 248
#define MGK_ImageErrorUnableToCreateImageMosaic 249
#define MGK_ImageErrorUnableToCreateStereoImage 250
#define MGK_ImageErrorUnableToDeconstructImageSequence 251
#define MGK_ImageErrorUnableToExportImagePixels 252
#define MGK_ImageErrorUnableToFlattenImage 253
#define MGK_ImageErrorUnableToGetClipMask 254
#define MGK_ImageErrorUnableToGetCompositeMask 255
#define MGK_ImageErrorUnableToHandleImageChannel 256
#define MGK_ImageErrorUnableToImportImagePixels 257
#define MGK_ImageErrorUnableToResizeImage 258
#define MGK_ImageErrorUnableToSegmentImage 259
#define MGK_ImageErrorUnableToSetClipMask 260
#define MGK_ImageErrorUnableToSetCompositeMask 261
#define MGK_ImageErrorUnableToShearImage 262
#define MGK_ImageErrorWidthOrHeightExceedsLimit 263
#define MGK_ImageFatalErrorUnableToPersistKey 264
#define MGK_ImageWarningDefault 265
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 266
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 267
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 268
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 269
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 270
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 271
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 272
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 273
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 274
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 275
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 276
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 277
#define MGK_MissingDelegateFatalErrorDefault 278
#define MGK_MissingDelegateWarningDefault 279
#define MGK_ModuleErrorFailedToCloseModule 280
#define MGK_ModuleErrorFailedToFindSymbol 281
#define MGK_ModuleErrorUnableToLoadModule 282
#define MGK_ModuleErrorUnableToRegisterImageFormat 283
#define MGK_ModuleErrorUnrecognizedModule 284
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 285
#define MGK_ModuleWarningDefault 286
#define MGK_MonitorErrorDefault 287
#define MGK_MonitorFatalErrorDefault 288
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 289
#define MGK_MonitorWarningDefault 290
#define MGK_OptionErrorBevelWidthIsNegative 291
#define MGK_OptionErrorColorSeparatedImageRequired 292
#define MGK_OptionErrorFrameIsLessThanImageSize 293
#define MGK_OptionErrorGeometryDimensionsAreZero 294
#define MGK_OptionErrorGeometryDoesNotContainImage 295
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 296
#define MGK_OptionErrorImagesAreNotTheSameSize 297
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 298
#define MGK_OptionErrorImageSmallerThanKernelWidth 299
#define MGK_OptionErrorImageSmallerThanRadius 300
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 301
#define MGK_OptionErrorInputImagesAlreadySpecified 302
#define MGK_OptionErrorInvalidSubimageSpecification 303
#define MGK_OptionErrorKernelRadiusIsTooSmall 304
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 305
#define MGK_OptionErrorMatrixIsNotSquare 306
#define MGK_OptionErrorMatrixOrderOutOfRange 307
#define MGK_OptionErrorMissingAnImageFilename 308
#define MGK_OptionErrorMissingArgument 309
#define MGK_OptionErrorMustSpecifyAnImageName 310
#define MGK_OptionErrorMustSpecifyImageSize 311
#define MGK_OptionErrorNoBlobDefined 312
#define MGK_OptionErrorNoImagesDefined 313
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 314
#define MGK_OptionErrorNoProfileNameWasGiven 315
#define MGK_OptionErrorNullBlobArgument 316
#define MGK_OptionErrorReferenceImageRequired 317
#define MGK_OptionErrorReferenceIsNotMyType 318
#define MGK_OptionErrorRegionAreaExceedsLimit 319
#define MGK_OptionErrorRequestDidNotReturnAnImage 320
#define MGK_OptionErrorSteganoImageRequired 321
#define MGK_OptionErrorStereoImageRequired 322
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 323
#define MGK_OptionErrorTileNotBoundedByImageDimensions 324
#define MGK_OptionErrorUnableToAddOrRemoveProfile 325
#define MGK_OptionErrorUnableToAverageImageSequence 326
#define MGK_OptionErrorUnableToBlurImage 327
#define MGK_OptionErrorUnableToChopImage 328
#define MGK_OptionErrorUnableToColorMatrixImage 329
#define MGK_OptionErrorUnableToConstituteImage 330
#define MGK_OptionErrorUnableToConvolveImage 331
#define MGK_OptionErrorUnableToEdgeImage 332
#define MGK_OptionErrorUnableToEqualizeImage 333
#define MGK_OptionErrorUnableToFilterImage 334
#define MGK_OptionErrorUnableToFormatImageMetadata 335
#define MGK_OptionErrorUnableToFrameImage 336
#define MGK_OptionErrorUnableToOilPaintImage 337
#define MGK_OptionErrorUnableToPaintImage 338
#define MGK_OptionErrorUnableToRaiseImage 339
#define MGK_OptionErrorUnableToSharpenImage 340
#define MGK_OptionErrorUnableToThresholdImage 341
#define MGK_OptionErrorUnableToWaveImage 342
#define MGK_OptionErrorUnrecognizedAttribute 343
#define MGK_OptionErrorUnrecognizedChannelType 344
#define MGK_OptionErrorUnrecognizedColor 345
#define MGK_OptionErrorUnrecognizedColormapType 346
#define MGK_OptionErrorUnrecognizedColorspace 347
#define MGK_OptionErrorUnrecognizedCommand 348
#define MGK_OptionErrorUnrecognizedComposeOperator 349
#define MGK_OptionErrorUnrecognizedDisposeMethod 350
#define MGK_OptionErrorUnrecognizedElement 351
#define MGK_OptionErrorUnrecognizedEndianType 352
#define MGK_OptionErrorUnrecognizedGravityType 353
#define MGK_OptionErrorUnrecognizedHighlightStyle 354
#define MGK_OptionErrorUnrecognizedImageCompression 355
#define MGK_OptionErrorUnrecognizedImageFilter 356
#define MGK_OptionErrorUnrecognizedImageFormat 357
#define MGK_OptionErrorUnrecognizedImageMode 358
#define MGK_OptionErrorUnrecognizedImageType 359
#define MGK_OptionErrorUnrecognizedIntentType 360
#define MGK_OptionErrorUnrecognizedInterlaceType 361
#define MGK_OptionErrorUnrecognizedListType 362
#define MGK_OptionErrorUnrecognizedMetric 363
#define MGK_OptionErrorUnrecognizedModeType 364
#define MGK_OptionErrorUnrecognizedNoiseType 365
#define MGK_OptionErrorUnrecognizedOperator 366
#define MGK_OptionErrorUnrecognizedOption 367
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 368
#define MGK_OptionErrorUnrecognizedPixelMap 369
#define MGK_OptionErrorUnrecognizedPreviewType 370
#define MGK_OptionErrorUnrecognizedResourceType 371
#define MGK_OptionErrorUnrecognizedType 372
#define MGK_OptionErrorUnrecognizedUnitsType 373
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 374
#define MGK_OptionErrorUnsupportedSamplingFactor 375
#define MGK_OptionErrorUsageError 376
#define MGK_OptionFatalErrorInvalidColorspaceType 377
#define MGK_OptionFatalErrorInvalidEndianType 378
#define MGK_OptionFatalErrorInvalidImageType 379
#define MGK_OptionFatalErrorInvalidInterlaceType 380
#define MGK_OptionFatalErrorMissingAnImageFilename 381
#define MGK_OptionFatalErrorMissingArgument 382
#define MGK_OptionFatalErrorNoImagesWereLoaded 383
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 384
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 385
#define MGK_OptionFatalErrorUnableToOpenXServer 386
#define MGK_OptionFatalErrorUnableToPersistKey 387
#define MGK_OptionFatalErrorUnrecognizedColormapType 388
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 389
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 390
#define MGK_OptionFatalErrorUnrecognizedEndianType 391
#define MGK_OptionFatalErrorUnrecognizedFilterType 392
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 393
#define MGK_OptionFatalErrorUnrecognizedImageType 394
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 395
#define MGK_OptionFatalErrorUnrecognizedOption 396
#define MGK_OptionFatalErrorUnrecognizedResourceType 397
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 398
#define MGK_OptionWarningUnrecognizedColor 399
#define MGK_RegistryErrorImageExpected 400
#define MGK_RegistryErrorImageInfoExpected 401
#define MGK_RegistryErrorStructureSizeMismatch 402
#define MGK_RegistryErrorUnableToGetRegistryID 403
#define MGK_RegistryErrorUnableToLocateImage 404
#define MGK_RegistryErrorUnableToSetRegistry 405
#define MGK_RegistryFatalErrorDefault 406
#define MGK_RegistryWarningDefault 407
#define MGK_ResourceLimitErrorCacheResourcesExhausted 408
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 409
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 410
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 411
#define MGK_ResourceLimitErrorMemoryAllocationFailed 412
#define MGK_ResourceLimitErrorNexusPixelHeightLimitExceeded 413
#define MGK_ResourceLimitErrorNexusPixelLimitExceeded 414
#define MGK_ResourceLimitErrorNexusPixelWidthLimitExceeded 415
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 416
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 417
#define MGK_ResourceLimitErrorUnableToAddColorProfile 418
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 419
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 420
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 421
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 422
#define MGK_ResourceLimitErrorUnableToAllocateColormap 423
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 424
#define MGK_ResourceLimitErrorUnableToAllocateImage 425
#define MGK_ResourceLimitErrorUnableToAllocateString 426
#define MGK_ResourceLimitErrorUnableToAnnotateImage 427
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 428
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 429
#define MGK_ResourceLimitErrorUnableToCloneImage 430
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 431
#define MGK_ResourceLimitErrorUnableToConstituteImage 432
#define MGK_ResourceLimitErrorUnableToConvertFont 433
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 434
#define MGK_ResourceLimitErrorUnableToCreateColormap 435
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 436
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 437
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 438
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 439
#define MGK_ResourceLimitErrorUnableToCreateXWindow 440
#define MGK_ResourceLimitErrorUnableToCropImage 441
#define MGK_ResourceLimitErrorUnableToDespeckleImage 442
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 443
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 444
#define MGK_ResourceLimitErrorUnableToDitherImage 445
#define MGK_ResourceLimitErrorUnableToDrawOnImage 446
#define MGK_ResourceLimitErrorUnableToEdgeImage 447
#define MGK_ResourceLimitErrorUnableToEmbossImage 448
#define MGK_ResourceLimitErrorUnableToEnhanceImage 449
#define MGK_ResourceLimitErrorUnableToFloodfillImage 450
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 451
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 452
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 453
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 454
#define MGK_ResourceLimitErrorUnableToLevelImage 455
#define MGK_ResourceLimitErrorUnableToMagnifyImage 456
#define MGK_ResourceLimitErrorUnableToManageColor 457
#define MGK_ResourceLimitErrorUnableToMapImage 458
#define MGK_ResourceLimitErrorUnableToMapImageSequence 459
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 460
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 461
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 462
#define MGK_ResourceLimitErrorUnableToNormalizeImage 463
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 464
#define MGK_ResourceLimitErrorUnableToQuantizeImage 465
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 466
#define MGK_ResourceLimitErrorUnableToReadTextChunk 467
#define MGK_ResourceLimitErrorUnableToReadXImage 468
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 469
#define MGK_ResourceLimitErrorUnableToResizeImage 470
#define MGK_ResourceLimitErrorUnableToRotateImage 471
#define MGK_ResourceLimitErrorUnableToSampleImage 472
#define MGK_ResourceLimitErrorUnableToScaleImage 473
#define MGK_ResourceLimitErrorUnableToSelectImage 474
#define MGK_ResourceLimitErrorUnableToSharpenImage 475
#define MGK_ResourceLimitErrorUnableToShaveImage 476
#define MGK_ResourceLimitErrorUnableToShearImage 477
#define MGK_ResourceLimitErrorUnableToSortImageColormap 478
#define MGK_ResourceLimitErrorUnableToThresholdImage 479
#define MGK_ResourceLimitErrorUnableToTransformColorspace 480
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 481
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 490
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 491
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 492
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 493
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 494
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 495
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 496
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 497
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 498
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 499
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 500
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 501
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 502
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 503
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 504
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 505
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 506
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 507
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 508
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 509
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 510
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 511
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 512
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 513
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 514
#define MGK_ResourceLimitFatalErrorUnableToConvertText 515
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 516
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 517
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 518
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 519
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 520
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 521
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 522
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 523
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 524
#define MGK_ResourceLimitWarningMemoryAllocationFailed 525
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 526
#define MGK_StreamErrorNoStreamHandlerIsDefined 527
#define MGK_StreamErrorPixelCacheIsNotOpen 528
#define MGK_StreamErrorUnableToAcquirePixelStream 529
#define MGK_StreamErrorUnableToSetPixelStream 530
#define MGK_StreamErrorUnableToSyncPixelStream 531
#define MGK_StreamFatalErrorDefault 532
#define MGK_StreamWarningDefault 533
#define MGK_TypeErrorFontNotSpecified 534
#define MGK_TypeErrorFontSubstitutionRequired 535
#define MGK_TypeErrorUnableToGetTypeMetrics 536
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 537
#define MGK_TypeErrorUnableToReadFont 538
#define MGK_TypeErrorUnrecognizedFontEncoding 539
#define MGK_TypeFatalErrorDefault 540
#define MGK_TypeWarningDefault 541
#define MGK_WandErrorInvalidColormapIndex 542
#define MGK_WandErrorWandAPINotImplemented 543
#define MGK_WandErrorWandContainsNoImageIndexs 544
#define MGK_WandErrorWandContainsNoImages 545
#define MGK_XServerErrorColorIsNotKnownToServer 546
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 547
#define MGK_XServerErrorStandardColormapIsNotInitialized 548
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 549
#define MGK_XServerErrorUnableToCreateBitmap 550
#define MGK_XServerErrorUnableToCreateColormap 551
#define MGK_XServerErrorUnableToCreatePixmap 552
#define MGK_XServerErrorUnableToCreateProperty 553
#define MGK_XServerErrorUnableToCreateStandardColormap 554
#define MGK_XServerErrorUnableToDisplayImageInfo 555
#define MGK_XServerErrorUnableToGetProperty 556
#define MGK_XServerErrorUnableToGetStandardColormap 557
#define MGK_XServerErrorUnableToGetVisual 558
#define MGK_XServerErrorUnableToGrabMouse 559
#define MGK_XServerErrorUnableToLoadFont 560
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 561
#define MGK_XServerErrorUnableToOpenXServer 562
#define MGK_XServerErrorUnableToReadXAttributes 563
#define MGK_XServerErrorUnableToReadXWindowImage 564
#define MGK_XServerErrorUnrecognizedColormapType 565
#define MGK_XServerErrorUnrecognizedGravityType 566
#define MGK_XServerErrorUnrecognizedVisualSpecifier 567
#define MGK_XServerFatalErrorUnableToAllocateXHints 568
#define MGK_XServerFatalErrorUnableToCreateCursor 569
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 570
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 571
#define MGK_XServerFatalErrorUnableToCreateTextProperty 572
#define MGK_XServerFatalErrorUnableToCreateXImage 573
#define MGK_XServerFatalErrorUnableToCreateXPixmap 574
#define MGK_XServerFatalErrorUnableToCreateXWindow 575
#define MGK_XServerFatalErrorUnableToDisplayImage 576
#define MGK_XServerFatalErrorUnableToDitherImage 577
#define MGK_XServerFatalErrorUnableToGetPixelInfo 578
#define MGK_XServerFatalErrorUnableToGetVisual 579
#define MGK_XServerFatalErrorUnableToLoadFont 580
#define MGK_XServerFatalErrorUnableToMakeXWindow 581
#define MGK_XServerFatalErrorUnableToOpenXServer 582
#define MGK_XServerFatalErrorUnableToViewFonts 583
#define MGK_XServerWarningUnableToGetVisual 584
#define MGK_XServerWarningUsingDefaultVisual 585

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
    { "Coder/FatalError", 112, CoderFatalError },
    { "Coder/Warning", 113, CoderWarning },
    { "Configure/Error", 114, ConfigureError },
    { "Configure/FatalError", 121, ConfigureFatalError },
    { "Configure/Warning", 125, ConfigureWarning },
    { "Corrupt/Image/Error", 126, CorruptImageError },
    { "Corrupt/Image/FatalError", 168, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 169, CorruptImageWarning },
    { "Delegate/Error", 181, DelegateError },
    { "Delegate/FatalError", 199, DelegateFatalError },
    { "Delegate/Warning", 200, DelegateWarning },
    { "Draw/Error", 201, DrawError },
    { "Draw/FatalError", 217, DrawFatalError },
    { "Draw/Warning", 218, DrawWarning },
    { "File/Open/Error", 221, FileOpenError },
    { "File/Open/FatalError", 224, FileOpenFatalError },
    { "File/Open/Warning", 225, FileOpenWarning },
    { "Image/Error", 226, ImageError },
    { "Image/FatalError", 263, ImageFatalError },
    { "Image/Warning", 264, ImageWarning },
    { "Missing/Delegate/Error", 265, MissingDelegateError },
    { "Missing/Delegate/FatalError", 277, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 278, MissingDelegateWarning },
    { "Module/Error", 279, ModuleError },
    { "Module/FatalError", 284, ModuleFatalError },
    { "Module/Warning", 285, ModuleWarning },
    { "Monitor/Error", 286, MonitorError },
    { "Monitor/FatalError", 287, MonitorFatalError },
    { "Monitor/Warning", 289, MonitorWarning },
    { "Option/Error", 290, OptionError },
    { "Option/FatalError", 376, OptionFatalError },
    { "Option/Warning", 398, OptionWarning },
    { "Registry/Error", 399, RegistryError },
    { "Registry/FatalError", 405, RegistryFatalError },
    { "Registry/Warning", 406, RegistryWarning },
    { "Resource/Limit/Error", 407, ResourceLimitError },
    { "Resource/Limit/FatalError", 480, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 524, ResourceLimitWarning },
    { "Stream/Error", 525, StreamError },
    { "Stream/FatalError", 531, StreamFatalError },
    { "Stream/Warning", 532, StreamWarning },
    { "Type/Error", 533, TypeError },
    { "Type/FatalError", 539, TypeFatalError },
    { "Type/Warning", 540, TypeWarning },
    { "Wand/Error", 541, WandError },
    { "XServer/Error", 545, XServerError },
    { "XServer/FatalError", 567, XServerFatalError },
    { "XServer/Warning", 583, XServerWarning },
    { "", 585, UndefinedException }
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
    "image difference exceeds limit (%s)\0"
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
    1460,
    1494,
    1525,
    1570,
    1605,
    1631,
    1657,
    1680,
    1707,
    1724,
    1749,
    1772,
    1798,
    1832,
    1871,
    1903,
    1936,
    1959,
    1989,
    2054,
    2077,
    2099,
    2123,
    2150,
    2183,
    2203,
    2231,
    2260,
    2288,
    2316,
    2343,
    2369,
    2392,
    2422,
    2450,
    2476,
    2501,
    2534,
    2561,
    2586,
    2618,
    2652,
    2681,
    2709,
    2745,
    2775,
    2802,
    2832,
    2865,
    2902,
    2938,
    2970,
    3016,
    3059,
    3103,
    3140,
    3176,
    3228,
    3277,
    3310,
    3357,
    3388,
    3421,
    3435,
    3469,
    3503,
    3582,
    3619,
    3655,
    3682,
    3722,
    3751,
    3765,
    3803,
    3843,
    3887,
    3903,
    3943,
    3981,
    4012,
    4034,
    4048,
    4099,
    4124,
    4149,
    4171,
    4203,
    4226,
    4254,
    4287,
    4320,
    4348,
    4385,
    4417,
    4452,
    4517,
    4545,
    4584,
    4613,
    4644,
    4675,
    4701,
    4729,
    4757,
    4794,
    4824,
    4849,
    4891,
    4924,
    4951,
    4974,
    5001,
    5022,
    5050,
    5075,
    5105,
    5129,
    5157,
    5186,
    5208,
    5230,
    5265,
    5287,
    5310,
    5343,
    5371,
    5397,
    5438,
    5475,
    5508,
    5536,
    5567,
    5583,
    5617,
    5661,
    5691,
    5736,
    5758,
    5778,
    5791,
    5818,
    5841,
    5874,
    5902,
    5930,
    5963,
    5996,
    6024,
    6051,
    6109,
    6123,
    6139,
    6174,
    6194,
    6221,
    6258,
    6297,
    6324,
    6368,
    6398,
    6419,
    6443,
    6459,
    6495,
    6515,
    6548,
    6581,
    6603,
    6617,
    6636,
    6677,
    6691,
    6723,
    6743,
    6764,
    6778,
    6794,
    6817,
    6862,
    6896,
    6921,
    6947,
    6983,
    7017,
    7042,
    7064,
    7091,
    7110,
    7133,
    7167,
    7188,
    7210,
    7238,
    7255,
    7278,
    7303,
    7327,
    7352,
    7377,
    7407,
    7437,
    7474,
    7504,
    7528,
    7552,
    7581,
    7612,
    7642,
    7665,
    7689,
    7713,
    7742,
    7764,
    7794,
    7816,
    7832,
    7861,
    7890,
    7924,
    7966,
    7992,
    8017,
    8058,
    8099,
    8129,
    8158,
    8192,
    8234,
    8248,
    8264,
    8287,
    8309,
    8331,
    8363,
    8383,
    8418,
    8434,
    8448,
    8462,
    8502,
    8518,
    8542,
    8573,
    8603,
    8632,
    8664,
    8703,
    8732,
    8761,
    8793,
    8819,
    8850,
    8881,
    8912,
    8939,
    8974,
    9009,
    9037,
    9063,
    9121,
    9147,
    9171,
    9203,
    9221,
    9256,
    9282,
    9301,
    9326,
    9351,
    9392,
    9424,
    9447,
    9469,
    9510,
    9550,
    9582,
    9615,
    9636,
    9657,
    9686,
    9713,
    9738,
    9759,
    9784,
    9807,
    9840,
    9862,
    9888,
    9910,
    9932,
    9956,
    9982,
    10003,
    10026,
    10052,
    10071,
    10098,
    10128,
    10200,
    10230,
    10258,
    10279,
    10304,
    10330,
    10359,
    10390,
    10416,
    10442,
    10466,
    10490,
    10515,
    10543,
    10566,
    10592,
    10615,
    10639,
    10661,
    10681,
    10712,
    10735,
    10761,
    10788,
    10806,
    10830,
    10864,
    10892,
    10939,
    10963,
    10983,
    11002,
    11025,
    11051,
    11109,
    11131,
    11159,
    11191,
    11214,
    11236,
    11263,
    11292,
    11320,
    11345,
    11370,
    11400,
    11424,
    11452,
    11472,
    11499,
    11533,
    11552,
    11567,
    11587,
    11611,
    11637,
    11660,
    11683,
    11697,
    11713,
    11757,
    11811,
    11858,
    11910,
    11935,
    11989,
    12036,
    12088,
    12115,
    12145,
    12177,
    12207,
    12234,
    12266,
    12298,
    12326,
    12357,
    12382,
    12408,
    12433,
    12466,
    12495,
    12517,
    12551,
    12578,
    12601,
    12637,
    12663,
    12696,
    12728,
    12757,
    12788,
    12814,
    12835,
    12861,
    12893,
    12940,
    12963,
    12987,
    13008,
    13031,
    13055,
    13081,
    13111,
    13140,
    13168,
    13195,
    13217,
    13241,
    13264,
    13284,
    13313,
    13343,
    13371,
    13400,
    13426,
    13455,
    13480,
    13514,
    13540,
    13563,
    13596,
    13619,
    13642,
    13665,
    13687,
    13710,
    13734,
    13756,
    13778,
    13808,
    13834,
    13865,
    13890,
    13917,
    13949,
    13979,
    14009,
    14039,
    14071,
    14104,
    14133,
    14165,
    14194,
    14226,
    14255,
    14280,
    14312,
    14340,
    14370,
    14401,
    14431,
    14462,
    14494,
    14527,
    14560,
    14593,
    14627,
    14653,
    14682,
    14706,
    14739,
    14765,
    14792,
    14814,
    14841,
    14870,
    14893,
    14919,
    14947,
    14971,
    14995,
    15026,
    15056,
    15081,
    15133,
    15160,
    15185,
    15228,
    15257,
    15281,
    15312,
    15339,
    15367,
    15381,
    15397,
    15421,
    15448,
    15475,
    15513,
    15533,
    15560,
    15574,
    15590,
    15622,
    15656,
    15696,
    15729,
    15758,
    15793,
    15830,
    15866,
    15890,
    15916,
    15940,
    15966,
    16001,
    16030,
    16053,
    16085,
    16106,
    16127,
    16147,
    16191,
    16215,
    16243,
    16273,
    16300,
    16326,
    16356,
    16383,
    16409,
    16442,
    16477,
    16508,
    16533,
    16559,
    16585,
    16609,
    16632,
    16657,
    16678,
    16698,
    16722,
    16746,
    16767,
    16788,
    16807,
    0
  };
#endif /* if defined(_INCLUDE_MESSAGE_TABLE_) */

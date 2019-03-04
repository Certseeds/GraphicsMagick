#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int) MAGICK_FUNC_CONST;

#define MAX_LOCALE_MSGS 579

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
#define MGK_CoderErrorUnsupportedSamplesPerPixel 95
#define MGK_CoderErrorWebPDecodingFailedUserAbort 96
#define MGK_CoderErrorWebPEncodingFailed 97
#define MGK_CoderErrorWebPEncodingFailedBadDimension 98
#define MGK_CoderErrorWebPEncodingFailedBadWrite 99
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 100
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 101
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 102
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 103
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 104
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 105
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 106
#define MGK_CoderErrorWebPEncodingFailedUserAbort 107
#define MGK_CoderErrorWebPInvalidConfiguration 108
#define MGK_CoderErrorWebPInvalidParameter 109
#define MGK_CoderErrorZipCompressionNotSupported 110
#define MGK_CoderFatalErrorDefault 111
#define MGK_CoderWarningLosslessToLossyJPEGConversion 112
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 113
#define MGK_ConfigureErrorRegistryKeyLookupFailed 114
#define MGK_ConfigureErrorStringTokenLengthExceeded 115
#define MGK_ConfigureErrorUnableToAccessConfigureFile 116
#define MGK_ConfigureErrorUnableToAccessFontFile 117
#define MGK_ConfigureErrorUnableToAccessLogFile 118
#define MGK_ConfigureErrorUnableToAccessModuleFile 119
#define MGK_ConfigureFatalErrorDefault 120
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 121
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 122
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 123
#define MGK_ConfigureWarningDefault 124
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 125
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 126
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 127
#define MGK_CorruptImageErrorCompressionNotValid 128
#define MGK_CorruptImageErrorCorruptImage 129
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 130
#define MGK_CorruptImageErrorImageFileHasNoScenes 131
#define MGK_CorruptImageErrorImageTypeNotSupported 132
#define MGK_CorruptImageErrorImproperImageHeader 133
#define MGK_CorruptImageErrorInsufficientImageDataInFile 134
#define MGK_CorruptImageErrorInvalidColormapIndex 135
#define MGK_CorruptImageErrorInvalidFileFormatVersion 136
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 137
#define MGK_CorruptImageErrorMissingImageChannel 138
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 139
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 140
#define MGK_CorruptImageErrorNotEnoughTiles 141
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 142
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 143
#define MGK_CorruptImageErrorTooMuchImageDataInFile 144
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 145
#define MGK_CorruptImageErrorUnableToReadColorProfile 146
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 147
#define MGK_CorruptImageErrorUnableToReadGenericProfile 148
#define MGK_CorruptImageErrorUnableToReadImageData 149
#define MGK_CorruptImageErrorUnableToReadImageHeader 150
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 151
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 152
#define MGK_CorruptImageErrorUnableToReadSubImageData 153
#define MGK_CorruptImageErrorUnableToReadVIDImage 154
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 155
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 156
#define MGK_CorruptImageErrorUnableToUncompressImage 157
#define MGK_CorruptImageErrorUnexpectedEndOfFile 158
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 159
#define MGK_CorruptImageErrorUnknownPatternType 160
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 161
#define MGK_CorruptImageErrorUnrecognizedImageCompression 162
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 163
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 164
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 165
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 166
#define MGK_CorruptImageFatalErrorUnableToPersistKey 167
#define MGK_CorruptImageWarningCompressionNotValid 168
#define MGK_CorruptImageWarningCorruptImage 169
#define MGK_CorruptImageWarningImproperImageHeader 170
#define MGK_CorruptImageWarningInvalidColormapIndex 171
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 172
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 173
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 174
#define MGK_CorruptImageWarningSkipToSyncByte 175
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 176
#define MGK_CorruptImageWarningUnableToParseEmbeddedProfile 177
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 178
#define MGK_CorruptImageWarningUnrecognizedImageCompression 179
#define MGK_DelegateErrorDelegateFailed 180
#define MGK_DelegateErrorFailedToAllocateArgumentList 181
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 182
#define MGK_DelegateErrorFailedToComputeOutputSize 183
#define MGK_DelegateErrorFailedToFindGhostscript 184
#define MGK_DelegateErrorFailedToRenderFile 185
#define MGK_DelegateErrorFailedToScanFile 186
#define MGK_DelegateErrorNoTagFound 187
#define MGK_DelegateErrorPostscriptDelegateFailed 188
#define MGK_DelegateErrorUnableToCreateImage 189
#define MGK_DelegateErrorUnableToCreateImageComponent 190
#define MGK_DelegateErrorUnableToDecodeImageFile 191
#define MGK_DelegateErrorUnableToEncodeImageFile 192
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 193
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 194
#define MGK_DelegateErrorUnableToManageJP2Stream 195
#define MGK_DelegateErrorUnableToWriteSVGFormat 196
#define MGK_DelegateErrorWebPABIMismatch 197
#define MGK_DelegateFatalErrorDefault 198
#define MGK_DelegateWarningDefault 199
#define MGK_DrawErrorAlreadyPushingPatternDefinition 200
#define MGK_DrawErrorDrawingRecursionDetected 201
#define MGK_DrawErrorFloatValueConversionError 202
#define MGK_DrawErrorIntegerValueConversionError 203
#define MGK_DrawErrorInvalidPrimitiveArgument 204
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 205
#define MGK_DrawErrorPrimitiveArithmeticOverflow 206
#define MGK_DrawErrorTooManyCoordinates 207
#define MGK_DrawErrorUnableToPrint 208
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 209
#define MGK_DrawErrorUnreasonableGradientSize 210
#define MGK_DrawErrorVectorPathTruncated 211
#define MGK_DrawFatalErrorDefault 212
#define MGK_DrawWarningNotARelativeURL 213
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 214
#define MGK_DrawWarningURLNotFound 215
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 216
#define MGK_FileOpenErrorUnableToOpenFile 217
#define MGK_FileOpenErrorUnableToWriteFile 218
#define MGK_FileOpenFatalErrorDefault 219
#define MGK_FileOpenWarningDefault 220
#define MGK_ImageErrorAngleIsDiscontinuous 221
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 222
#define MGK_ImageErrorColorspaceColorProfileMismatch 223
#define MGK_ImageErrorImageColorspaceDiffers 224
#define MGK_ImageErrorImageColorspaceMismatch 225
#define MGK_ImageErrorImageDifferenceExceedsLimit 226
#define MGK_ImageErrorImageDoesNotContainResolution 227
#define MGK_ImageErrorImageIsNotColormapped 228
#define MGK_ImageErrorImageOpacityDiffers 229
#define MGK_ImageErrorImageSequenceIsRequired 230
#define MGK_ImageErrorImageSizeDiffers 231
#define MGK_ImageErrorInvalidColormapIndex 232
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 233
#define MGK_ImageErrorNoImagesWereFound 234
#define MGK_ImageErrorNoImagesWereLoaded 235
#define MGK_ImageErrorNoLocaleImageAttribute 236
#define MGK_ImageErrorTooManyClusters 237
#define MGK_ImageErrorUnableToAppendImage 238
#define MGK_ImageErrorUnableToAssignProfile 239
#define MGK_ImageErrorUnableToAverageImage 240
#define MGK_ImageErrorUnableToCoalesceImage 241
#define MGK_ImageErrorUnableToCompareImages 242
#define MGK_ImageErrorUnableToCreateImageMosaic 243
#define MGK_ImageErrorUnableToCreateStereoImage 244
#define MGK_ImageErrorUnableToDeconstructImageSequence 245
#define MGK_ImageErrorUnableToExportImagePixels 246
#define MGK_ImageErrorUnableToFlattenImage 247
#define MGK_ImageErrorUnableToGetClipMask 248
#define MGK_ImageErrorUnableToGetCompositeMask 249
#define MGK_ImageErrorUnableToHandleImageChannel 250
#define MGK_ImageErrorUnableToImportImagePixels 251
#define MGK_ImageErrorUnableToResizeImage 252
#define MGK_ImageErrorUnableToSegmentImage 253
#define MGK_ImageErrorUnableToSetClipMask 254
#define MGK_ImageErrorUnableToSetCompositeMask 255
#define MGK_ImageErrorUnableToShearImage 256
#define MGK_ImageErrorWidthOrHeightExceedsLimit 257
#define MGK_ImageFatalErrorUnableToPersistKey 258
#define MGK_ImageWarningDefault 259
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 260
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 261
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 262
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 263
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 264
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 265
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 266
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 267
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 268
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 269
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 270
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 271
#define MGK_MissingDelegateFatalErrorDefault 272
#define MGK_MissingDelegateWarningDefault 273
#define MGK_ModuleErrorFailedToCloseModule 274
#define MGK_ModuleErrorFailedToFindSymbol 275
#define MGK_ModuleErrorUnableToLoadModule 276
#define MGK_ModuleErrorUnableToRegisterImageFormat 277
#define MGK_ModuleErrorUnrecognizedModule 278
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 279
#define MGK_ModuleWarningDefault 280
#define MGK_MonitorErrorDefault 281
#define MGK_MonitorFatalErrorDefault 282
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 283
#define MGK_MonitorWarningDefault 284
#define MGK_OptionErrorBevelWidthIsNegative 285
#define MGK_OptionErrorColorSeparatedImageRequired 286
#define MGK_OptionErrorFrameIsLessThanImageSize 287
#define MGK_OptionErrorGeometryDimensionsAreZero 288
#define MGK_OptionErrorGeometryDoesNotContainImage 289
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 290
#define MGK_OptionErrorImagesAreNotTheSameSize 291
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 292
#define MGK_OptionErrorImageSmallerThanKernelWidth 293
#define MGK_OptionErrorImageSmallerThanRadius 294
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 295
#define MGK_OptionErrorInputImagesAlreadySpecified 296
#define MGK_OptionErrorInvalidSubimageSpecification 297
#define MGK_OptionErrorKernelRadiusIsTooSmall 298
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 299
#define MGK_OptionErrorMatrixIsNotSquare 300
#define MGK_OptionErrorMatrixOrderOutOfRange 301
#define MGK_OptionErrorMissingAnImageFilename 302
#define MGK_OptionErrorMissingArgument 303
#define MGK_OptionErrorMustSpecifyAnImageName 304
#define MGK_OptionErrorMustSpecifyImageSize 305
#define MGK_OptionErrorNoBlobDefined 306
#define MGK_OptionErrorNoImagesDefined 307
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 308
#define MGK_OptionErrorNoProfileNameWasGiven 309
#define MGK_OptionErrorNullBlobArgument 310
#define MGK_OptionErrorReferenceImageRequired 311
#define MGK_OptionErrorReferenceIsNotMyType 312
#define MGK_OptionErrorRegionAreaExceedsLimit 313
#define MGK_OptionErrorRequestDidNotReturnAnImage 314
#define MGK_OptionErrorSteganoImageRequired 315
#define MGK_OptionErrorStereoImageRequired 316
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 317
#define MGK_OptionErrorTileNotBoundedByImageDimensions 318
#define MGK_OptionErrorUnableToAddOrRemoveProfile 319
#define MGK_OptionErrorUnableToAverageImageSequence 320
#define MGK_OptionErrorUnableToBlurImage 321
#define MGK_OptionErrorUnableToChopImage 322
#define MGK_OptionErrorUnableToColorMatrixImage 323
#define MGK_OptionErrorUnableToConstituteImage 324
#define MGK_OptionErrorUnableToConvolveImage 325
#define MGK_OptionErrorUnableToEdgeImage 326
#define MGK_OptionErrorUnableToEqualizeImage 327
#define MGK_OptionErrorUnableToFilterImage 328
#define MGK_OptionErrorUnableToFormatImageMetadata 329
#define MGK_OptionErrorUnableToFrameImage 330
#define MGK_OptionErrorUnableToOilPaintImage 331
#define MGK_OptionErrorUnableToPaintImage 332
#define MGK_OptionErrorUnableToRaiseImage 333
#define MGK_OptionErrorUnableToSharpenImage 334
#define MGK_OptionErrorUnableToThresholdImage 335
#define MGK_OptionErrorUnableToWaveImage 336
#define MGK_OptionErrorUnrecognizedAttribute 337
#define MGK_OptionErrorUnrecognizedChannelType 338
#define MGK_OptionErrorUnrecognizedColor 339
#define MGK_OptionErrorUnrecognizedColormapType 340
#define MGK_OptionErrorUnrecognizedColorspace 341
#define MGK_OptionErrorUnrecognizedCommand 342
#define MGK_OptionErrorUnrecognizedComposeOperator 343
#define MGK_OptionErrorUnrecognizedDisposeMethod 344
#define MGK_OptionErrorUnrecognizedElement 345
#define MGK_OptionErrorUnrecognizedEndianType 346
#define MGK_OptionErrorUnrecognizedGravityType 347
#define MGK_OptionErrorUnrecognizedHighlightStyle 348
#define MGK_OptionErrorUnrecognizedImageCompression 349
#define MGK_OptionErrorUnrecognizedImageFilter 350
#define MGK_OptionErrorUnrecognizedImageFormat 351
#define MGK_OptionErrorUnrecognizedImageMode 352
#define MGK_OptionErrorUnrecognizedImageType 353
#define MGK_OptionErrorUnrecognizedIntentType 354
#define MGK_OptionErrorUnrecognizedInterlaceType 355
#define MGK_OptionErrorUnrecognizedListType 356
#define MGK_OptionErrorUnrecognizedMetric 357
#define MGK_OptionErrorUnrecognizedModeType 358
#define MGK_OptionErrorUnrecognizedNoiseType 359
#define MGK_OptionErrorUnrecognizedOperator 360
#define MGK_OptionErrorUnrecognizedOption 361
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 362
#define MGK_OptionErrorUnrecognizedPixelMap 363
#define MGK_OptionErrorUnrecognizedPreviewType 364
#define MGK_OptionErrorUnrecognizedResourceType 365
#define MGK_OptionErrorUnrecognizedType 366
#define MGK_OptionErrorUnrecognizedUnitsType 367
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 368
#define MGK_OptionErrorUnsupportedSamplingFactor 369
#define MGK_OptionErrorUsageError 370
#define MGK_OptionFatalErrorInvalidColorspaceType 371
#define MGK_OptionFatalErrorInvalidEndianType 372
#define MGK_OptionFatalErrorInvalidImageType 373
#define MGK_OptionFatalErrorInvalidInterlaceType 374
#define MGK_OptionFatalErrorMissingAnImageFilename 375
#define MGK_OptionFatalErrorMissingArgument 376
#define MGK_OptionFatalErrorNoImagesWereLoaded 377
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 378
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 379
#define MGK_OptionFatalErrorUnableToOpenXServer 380
#define MGK_OptionFatalErrorUnableToPersistKey 381
#define MGK_OptionFatalErrorUnrecognizedColormapType 382
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 383
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 384
#define MGK_OptionFatalErrorUnrecognizedEndianType 385
#define MGK_OptionFatalErrorUnrecognizedFilterType 386
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 387
#define MGK_OptionFatalErrorUnrecognizedImageType 388
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 389
#define MGK_OptionFatalErrorUnrecognizedOption 390
#define MGK_OptionFatalErrorUnrecognizedResourceType 391
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 392
#define MGK_OptionWarningUnrecognizedColor 393
#define MGK_RegistryErrorImageExpected 394
#define MGK_RegistryErrorImageInfoExpected 395
#define MGK_RegistryErrorStructureSizeMismatch 396
#define MGK_RegistryErrorUnableToGetRegistryID 397
#define MGK_RegistryErrorUnableToLocateImage 398
#define MGK_RegistryErrorUnableToSetRegistry 399
#define MGK_RegistryFatalErrorDefault 400
#define MGK_RegistryWarningDefault 401
#define MGK_ResourceLimitErrorCacheResourcesExhausted 402
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 403
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 404
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 405
#define MGK_ResourceLimitErrorMemoryAllocationFailed 406
#define MGK_ResourceLimitErrorNexusPixelHeightLimitExceeded 407
#define MGK_ResourceLimitErrorNexusPixelLimitExceeded 408
#define MGK_ResourceLimitErrorNexusPixelWidthLimitExceeded 409
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 410
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 411
#define MGK_ResourceLimitErrorUnableToAddColorProfile 412
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 413
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 414
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 415
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 416
#define MGK_ResourceLimitErrorUnableToAllocateColormap 417
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 418
#define MGK_ResourceLimitErrorUnableToAllocateImage 419
#define MGK_ResourceLimitErrorUnableToAllocateString 420
#define MGK_ResourceLimitErrorUnableToAnnotateImage 421
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 422
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 423
#define MGK_ResourceLimitErrorUnableToCloneImage 424
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 425
#define MGK_ResourceLimitErrorUnableToConstituteImage 426
#define MGK_ResourceLimitErrorUnableToConvertFont 427
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 428
#define MGK_ResourceLimitErrorUnableToCreateColormap 429
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 430
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 431
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 432
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 433
#define MGK_ResourceLimitErrorUnableToCreateXWindow 434
#define MGK_ResourceLimitErrorUnableToCropImage 435
#define MGK_ResourceLimitErrorUnableToDespeckleImage 436
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 437
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 438
#define MGK_ResourceLimitErrorUnableToDitherImage 439
#define MGK_ResourceLimitErrorUnableToDrawOnImage 440
#define MGK_ResourceLimitErrorUnableToEdgeImage 441
#define MGK_ResourceLimitErrorUnableToEmbossImage 442
#define MGK_ResourceLimitErrorUnableToEnhanceImage 443
#define MGK_ResourceLimitErrorUnableToFloodfillImage 444
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 445
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 446
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 447
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 448
#define MGK_ResourceLimitErrorUnableToLevelImage 449
#define MGK_ResourceLimitErrorUnableToMagnifyImage 450
#define MGK_ResourceLimitErrorUnableToManageColor 451
#define MGK_ResourceLimitErrorUnableToMapImage 452
#define MGK_ResourceLimitErrorUnableToMapImageSequence 453
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 454
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 455
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 456
#define MGK_ResourceLimitErrorUnableToNormalizeImage 457
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 458
#define MGK_ResourceLimitErrorUnableToQuantizeImage 459
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 460
#define MGK_ResourceLimitErrorUnableToReadTextChunk 461
#define MGK_ResourceLimitErrorUnableToReadXImage 462
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 463
#define MGK_ResourceLimitErrorUnableToResizeImage 464
#define MGK_ResourceLimitErrorUnableToRotateImage 465
#define MGK_ResourceLimitErrorUnableToSampleImage 466
#define MGK_ResourceLimitErrorUnableToScaleImage 467
#define MGK_ResourceLimitErrorUnableToSelectImage 468
#define MGK_ResourceLimitErrorUnableToSharpenImage 469
#define MGK_ResourceLimitErrorUnableToShaveImage 470
#define MGK_ResourceLimitErrorUnableToShearImage 471
#define MGK_ResourceLimitErrorUnableToSortImageColormap 472
#define MGK_ResourceLimitErrorUnableToThresholdImage 473
#define MGK_ResourceLimitErrorUnableToTransformColorspace 474
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 475
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 477
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 478
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 479
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 480
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 481
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 490
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 491
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 492
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 493
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 494
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 495
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 496
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 497
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 498
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 499
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 500
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 501
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 502
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 503
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 504
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 505
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 506
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 507
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 508
#define MGK_ResourceLimitFatalErrorUnableToConvertText 509
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 510
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 511
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 512
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 513
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 514
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 515
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 516
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 517
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 518
#define MGK_ResourceLimitWarningMemoryAllocationFailed 519
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 520
#define MGK_StreamErrorNoStreamHandlerIsDefined 521
#define MGK_StreamErrorPixelCacheIsNotOpen 522
#define MGK_StreamErrorUnableToAcquirePixelStream 523
#define MGK_StreamErrorUnableToSetPixelStream 524
#define MGK_StreamErrorUnableToSyncPixelStream 525
#define MGK_StreamFatalErrorDefault 526
#define MGK_StreamWarningDefault 527
#define MGK_TypeErrorFontNotSpecified 528
#define MGK_TypeErrorFontSubstitutionRequired 529
#define MGK_TypeErrorUnableToGetTypeMetrics 530
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 531
#define MGK_TypeErrorUnableToReadFont 532
#define MGK_TypeErrorUnrecognizedFontEncoding 533
#define MGK_TypeFatalErrorDefault 534
#define MGK_TypeWarningDefault 535
#define MGK_WandErrorInvalidColormapIndex 536
#define MGK_WandErrorWandAPINotImplemented 537
#define MGK_WandErrorWandContainsNoImageIndexs 538
#define MGK_WandErrorWandContainsNoImages 539
#define MGK_XServerErrorColorIsNotKnownToServer 540
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 541
#define MGK_XServerErrorStandardColormapIsNotInitialized 542
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 543
#define MGK_XServerErrorUnableToCreateBitmap 544
#define MGK_XServerErrorUnableToCreateColormap 545
#define MGK_XServerErrorUnableToCreatePixmap 546
#define MGK_XServerErrorUnableToCreateProperty 547
#define MGK_XServerErrorUnableToCreateStandardColormap 548
#define MGK_XServerErrorUnableToDisplayImageInfo 549
#define MGK_XServerErrorUnableToGetProperty 550
#define MGK_XServerErrorUnableToGetStandardColormap 551
#define MGK_XServerErrorUnableToGetVisual 552
#define MGK_XServerErrorUnableToGrabMouse 553
#define MGK_XServerErrorUnableToLoadFont 554
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 555
#define MGK_XServerErrorUnableToOpenXServer 556
#define MGK_XServerErrorUnableToReadXAttributes 557
#define MGK_XServerErrorUnableToReadXWindowImage 558
#define MGK_XServerErrorUnrecognizedColormapType 559
#define MGK_XServerErrorUnrecognizedGravityType 560
#define MGK_XServerErrorUnrecognizedVisualSpecifier 561
#define MGK_XServerFatalErrorUnableToAllocateXHints 562
#define MGK_XServerFatalErrorUnableToCreateCursor 563
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 564
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 565
#define MGK_XServerFatalErrorUnableToCreateTextProperty 566
#define MGK_XServerFatalErrorUnableToCreateXImage 567
#define MGK_XServerFatalErrorUnableToCreateXPixmap 568
#define MGK_XServerFatalErrorUnableToCreateXWindow 569
#define MGK_XServerFatalErrorUnableToDisplayImage 570
#define MGK_XServerFatalErrorUnableToDitherImage 571
#define MGK_XServerFatalErrorUnableToGetPixelInfo 572
#define MGK_XServerFatalErrorUnableToGetVisual 573
#define MGK_XServerFatalErrorUnableToLoadFont 574
#define MGK_XServerFatalErrorUnableToMakeXWindow 575
#define MGK_XServerFatalErrorUnableToOpenXServer 576
#define MGK_XServerFatalErrorUnableToViewFonts 577
#define MGK_XServerWarningUnableToGetVisual 578
#define MGK_XServerWarningUsingDefaultVisual 579

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
    { "Cache/FatalError", 24, CacheFatalError },
    { "Cache/Warning", 26, CacheWarning },
    { "Coder/Error", 27, CoderError },
    { "Coder/FatalError", 110, CoderFatalError },
    { "Coder/Warning", 111, CoderWarning },
    { "Configure/Error", 112, ConfigureError },
    { "Configure/FatalError", 119, ConfigureFatalError },
    { "Configure/Warning", 123, ConfigureWarning },
    { "Corrupt/Image/Error", 124, CorruptImageError },
    { "Corrupt/Image/FatalError", 166, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 167, CorruptImageWarning },
    { "Delegate/Error", 179, DelegateError },
    { "Delegate/FatalError", 197, DelegateFatalError },
    { "Delegate/Warning", 198, DelegateWarning },
    { "Draw/Error", 199, DrawError },
    { "Draw/FatalError", 211, DrawFatalError },
    { "Draw/Warning", 212, DrawWarning },
    { "File/Open/Error", 215, FileOpenError },
    { "File/Open/FatalError", 218, FileOpenFatalError },
    { "File/Open/Warning", 219, FileOpenWarning },
    { "Image/Error", 220, ImageError },
    { "Image/FatalError", 257, ImageFatalError },
    { "Image/Warning", 258, ImageWarning },
    { "Missing/Delegate/Error", 259, MissingDelegateError },
    { "Missing/Delegate/FatalError", 271, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 272, MissingDelegateWarning },
    { "Module/Error", 273, ModuleError },
    { "Module/FatalError", 278, ModuleFatalError },
    { "Module/Warning", 279, ModuleWarning },
    { "Monitor/Error", 280, MonitorError },
    { "Monitor/FatalError", 281, MonitorFatalError },
    { "Monitor/Warning", 283, MonitorWarning },
    { "Option/Error", 284, OptionError },
    { "Option/FatalError", 370, OptionFatalError },
    { "Option/Warning", 392, OptionWarning },
    { "Registry/Error", 393, RegistryError },
    { "Registry/FatalError", 399, RegistryFatalError },
    { "Registry/Warning", 400, RegistryWarning },
    { "Resource/Limit/Error", 401, ResourceLimitError },
    { "Resource/Limit/FatalError", 474, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 518, ResourceLimitWarning },
    { "Stream/Error", 519, StreamError },
    { "Stream/FatalError", 525, StreamFatalError },
    { "Stream/Warning", 526, StreamWarning },
    { "Type/Error", 527, TypeError },
    { "Type/FatalError", 533, TypeFatalError },
    { "Type/Warning", 534, TypeWarning },
    { "Wand/Error", 535, WandError },
    { "XServer/Error", 539, XServerError },
    { "XServer/FatalError", 561, XServerFatalError },
    { "XServer/Warning", 577, XServerWarning },
    { 0, 579, UndefinedException }
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
    { "EmptyCacheNexus", 12 },
    { "InconsistentPersistentCacheDepth", 13 },
    { "PixelCacheDimensionsMisMatch", 14 },
    { "PixelCacheIsNotOpen", 15 },
    { "UnableToAllocateCacheView", 16 },
    { "UnableToCloneCache", 17 },
    { "UnableToExtendCache", 18 },
    { "UnableToGetCacheNexus", 19 },
    { "UnableToGetPixelsFromCache", 20 },
    { "UnableToOpenCache", 21 },
    { "UnableToPeristPixelCache", 22 },
    { "UnableToReadPixelCache", 23 },
    { "UnableToSyncCache", 24 },
    { "DiskAllocationFailed", 25 },
    { "UnableToExtendPixelCache", 26 },
    { "Default", 27 },
    { "ArithmeticOverflow", 28 },
    { "ColormapTooLarge", 29 },
    { "ColormapTypeNotSupported", 30 },
    { "ColorspaceModelIsNotSupported", 31 },
    { "ColorTypeNotSupported", 32 },
    { "CompressionNotValid", 33 },
    { "DataEncodingSchemeIsNotSupported", 34 },
    { "DataStorageTypeIsNotSupported", 35 },
    { "DecodedImageNotReturned", 36 },
    { "DeltaPNGNotSupported", 37 },
    { "DivisionByZero", 38 },
    { "EncryptedWPGImageFileNotSupported", 39 },
    { "FractalCompressionNotSupported", 40 },
    { "ImageColumnOrRowSizeIsNotSupported", 41 },
    { "ImageDoesNotHaveAMatteChannel", 42 },
    { "ImageIsNotTiled", 43 },
    { "ImageTypeNotSupported", 44 },
    { "IncompatibleSizeOfDouble", 45 },
    { "IrregularChannelGeometryNotSupported", 46 },
    { "JNGCompressionNotSupported", 47 },
    { "JPEGCompressionNotSupported", 48 },
    { "JPEGEmbeddingFailed", 49 },
    { "LocationTypeIsNotSupported", 50 },
    { "MapStorageTypeIsNotSupported", 51 },
    { "MSBByteOrderNotSupported", 52 },
    { "MultidimensionalMatricesAreNotSupported", 53 },
    { "MultipleRecordListNotSupported", 54 },
    { "No8BIMDataIsAvailable", 55 },
    { "NoAPP1DataIsAvailable", 56 },
    { "NoBitmapOnClipboard", 57 },
    { "NoColorProfileAvailable", 58 },
    { "NoDataReturned", 59 },
    { "NoImageVectorGraphics", 60 },
    { "NoIPTCInfoWasFound", 61 },
    { "NoIPTCProfileAvailable", 62 },
    { "NumberOfImagesIsNotSupported", 63 },
    { "OnlyContinuousTonePictureSupported", 64 },
    { "OnlyLevelZerofilesSupported", 65 },
    { "PNGCompressionNotSupported", 66 },
    { "PNGLibraryTooOld", 67 },
    { "RLECompressionNotSupported", 68 },
    { "SubsamplingRequiresEvenWidth", 69 },
    { "UnableToCopyProfile", 70 },
    { "UnableToCreateADC", 71 },
    { "UnableToCreateBitmap", 72 },
    { "UnableToDecompressImage", 73 },
    { "UnableToInitializeFPXLibrary", 74 },
    { "UnableToOpenBlob", 75 },
    { "UnableToReadAspectRatio", 76 },
    { "UnableToReadCIELABImages", 77 },
    { "UnableToReadSummaryInfo", 78 },
    { "UnableToSetAffineMatrix", 79 },
    { "UnableToSetAspectRatio", 80 },
    { "UnableToSetColorTwist", 81 },
    { "UnableToSetContrast", 82 },
    { "UnableToSetFilteringValue", 83 },
    { "UnableToSetImageComments", 84 },
    { "UnableToSetImageTitle", 85 },
    { "UnableToSetJPEGLevel", 86 },
    { "UnableToSetRegionOfInterest", 87 },
    { "UnableToSetSummaryInfo", 88 },
    { "UnableToTranslateText", 89 },
    { "UnableToWriteMPEGParameters", 90 },
    { "UnableToWriteTemporaryFile", 91 },
    { "UnableToZipCompressImage", 92 },
    { "UnsupportedBitsPerSample", 93 },
    { "UnsupportedCellTypeInTheMatrix", 94 },
    { "UnsupportedSamplesPerPixel", 95 },
    { "WebPDecodingFailedUserAbort", 96 },
    { "WebPEncodingFailed", 97 },
    { "WebPEncodingFailedBadDimension", 98 },
    { "WebPEncodingFailedBadWrite", 99 },
    { "WebPEncodingFailedBitstreamOutOfMemory", 100 },
    { "WebPEncodingFailedFileTooBig", 101 },
    { "WebPEncodingFailedInvalidConfiguration", 102 },
    { "WebPEncodingFailedNULLParameter", 103 },
    { "WebPEncodingFailedOutOfMemory", 104 },
    { "WebPEncodingFailedPartition0Overflow", 105 },
    { "WebPEncodingFailedPartitionOverflow", 106 },
    { "WebPEncodingFailedUserAbort", 107 },
    { "WebPInvalidConfiguration", 108 },
    { "WebPInvalidParameter", 109 },
    { "ZipCompressionNotSupported", 110 },
    { "Default", 111 },
    { "LosslessToLossyJPEGConversion", 112 },
    { "IncludeElementNestedTooDeeply", 113 },
    { "RegistryKeyLookupFailed", 114 },
    { "StringTokenLengthExceeded", 115 },
    { "UnableToAccessConfigureFile", 116 },
    { "UnableToAccessFontFile", 117 },
    { "UnableToAccessLogFile", 118 },
    { "UnableToAccessModuleFile", 119 },
    { "Default", 120 },
    { "UnableToChangeToWorkingDirectory", 121 },
    { "UnableToGetCurrentDirectory", 122 },
    { "UnableToRestoreCurrentDirectory", 123 },
    { "Default", 124 },
    { "AnErrorHasOccurredReadingFromFile", 125 },
    { "AnErrorHasOccurredWritingToFile", 126 },
    { "ColormapExceedsColorsLimit", 127 },
    { "CompressionNotValid", 128 },
    { "CorruptImage", 129 },
    { "ImageFileDoesNotContainAnyImageData", 130 },
    { "ImageFileHasNoScenes", 131 },
    { "ImageTypeNotSupported", 132 },
    { "ImproperImageHeader", 133 },
    { "InsufficientImageDataInFile", 134 },
    { "InvalidColormapIndex", 135 },
    { "InvalidFileFormatVersion", 136 },
    { "LengthAndFilesizeDoNotMatch", 137 },
    { "MissingImageChannel", 138 },
    { "NegativeOrZeroImageSize", 139 },
    { "NonOS2HeaderSizeError", 140 },
    { "NotEnoughTiles", 141 },
    { "StaticPlanesValueNotEqualToOne", 142 },
    { "SubsamplingRequiresEvenWidth", 143 },
    { "TooMuchImageDataInFile", 144 },
    { "UnableToReadColormapFromDumpFile", 145 },
    { "UnableToReadColorProfile", 146 },
    { "UnableToReadExtensionBlock", 147 },
    { "UnableToReadGenericProfile", 148 },
    { "UnableToReadImageData", 149 },
    { "UnableToReadImageHeader", 150 },
    { "UnableToReadIPTCProfile", 151 },
    { "UnableToReadPixmapFromDumpFile", 152 },
    { "UnableToReadSubImageData", 153 },
    { "UnableToReadVIDImage", 154 },
    { "UnableToReadWindowNameFromDumpFile", 155 },
    { "UnableToRunlengthDecodeImage", 156 },
    { "UnableToUncompressImage", 157 },
    { "UnexpectedEndOfFile", 158 },
    { "UnexpectedSamplingFactor", 159 },
    { "UnknownPatternType", 160 },
    { "UnrecognizedBitsPerPixel", 161 },
    { "UnrecognizedImageCompression", 162 },
    { "UnrecognizedNumberOfColors", 163 },
    { "UnrecognizedXWDHeader", 164 },
    { "UnsupportedBitsPerSample", 165 },
    { "UnsupportedNumberOfPlanes", 166 },
    { "UnableToPersistKey", 167 },
    { "CompressionNotValid", 168 },
    { "CorruptImage", 169 },
    { "ImproperImageHeader", 170 },
    { "InvalidColormapIndex", 171 },
    { "LengthAndFilesizeDoNotMatch", 172 },
    { "NegativeOrZeroImageSize", 173 },
    { "NonOS2HeaderSizeError", 174 },
    { "SkipToSyncByte", 175 },
    { "StaticPlanesValueNotEqualToOne", 176 },
    { "UnableToParseEmbeddedProfile", 177 },
    { "UnrecognizedBitsPerPixel", 178 },
    { "UnrecognizedImageCompression", 179 },
    { "DelegateFailed", 180 },
    { "FailedToAllocateArgumentList", 181 },
    { "FailedToAllocateGhostscriptInterpreter", 182 },
    { "FailedToComputeOutputSize", 183 },
    { "FailedToFindGhostscript", 184 },
    { "FailedToRenderFile", 185 },
    { "FailedToScanFile", 186 },
    { "NoTagFound", 187 },
    { "PostscriptDelegateFailed", 188 },
    { "UnableToCreateImage", 189 },
    { "UnableToCreateImageComponent", 190 },
    { "UnableToDecodeImageFile", 191 },
    { "UnableToEncodeImageFile", 192 },
    { "UnableToInitializeFPXLibrary", 193 },
    { "UnableToInitializeWMFLibrary", 194 },
    { "UnableToManageJP2Stream", 195 },
    { "UnableToWriteSVGFormat", 196 },
    { "WebPABIMismatch", 197 },
    { "Default", 198 },
    { "Default", 199 },
    { "AlreadyPushingPatternDefinition", 200 },
    { "DrawingRecursionDetected", 201 },
    { "FloatValueConversionError", 202 },
    { "IntegerValueConversionError", 203 },
    { "InvalidPrimitiveArgument", 204 },
    { "NonconformingDrawingPrimitiveDefinition", 205 },
    { "PrimitiveArithmeticOverflow", 206 },
    { "TooManyCoordinates", 207 },
    { "UnableToPrint", 208 },
    { "UnbalancedGraphicContextPushPop", 209 },
    { "UnreasonableGradientSize", 210 },
    { "VectorPathTruncated", 211 },
    { "Default", 212 },
    { "NotARelativeURL", 213 },
    { "NotCurrentlyPushingPatternDefinition", 214 },
    { "URLNotFound", 215 },
    { "UnableToCreateTemporaryFile", 216 },
    { "UnableToOpenFile", 217 },
    { "UnableToWriteFile", 218 },
    { "Default", 219 },
    { "Default", 220 },
    { "AngleIsDiscontinuous", 221 },
    { "CMYKAImageLacksAlphaChannel", 222 },
    { "ColorspaceColorProfileMismatch", 223 },
    { "ImageColorspaceDiffers", 224 },
    { "ImageColorspaceMismatch", 225 },
    { "ImageDifferenceExceedsLimit", 226 },
    { "ImageDoesNotContainResolution", 227 },
    { "ImageIsNotColormapped", 228 },
    { "ImageOpacityDiffers", 229 },
    { "ImageSequenceIsRequired", 230 },
    { "ImageSizeDiffers", 231 },
    { "InvalidColormapIndex", 232 },
    { "LeftAndRightImageSizesDiffer", 233 },
    { "NoImagesWereFound", 234 },
    { "NoImagesWereLoaded", 235 },
    { "NoLocaleImageAttribute", 236 },
    { "TooManyClusters", 237 },
    { "UnableToAppendImage", 238 },
    { "UnableToAssignProfile", 239 },
    { "UnableToAverageImage", 240 },
    { "UnableToCoalesceImage", 241 },
    { "UnableToCompareImages", 242 },
    { "UnableToCreateImageMosaic", 243 },
    { "UnableToCreateStereoImage", 244 },
    { "UnableToDeconstructImageSequence", 245 },
    { "UnableToExportImagePixels", 246 },
    { "UnableToFlattenImage", 247 },
    { "UnableToGetClipMask", 248 },
    { "UnableToGetCompositeMask", 249 },
    { "UnableToHandleImageChannel", 250 },
    { "UnableToImportImagePixels", 251 },
    { "UnableToResizeImage", 252 },
    { "UnableToSegmentImage", 253 },
    { "UnableToSetClipMask", 254 },
    { "UnableToSetCompositeMask", 255 },
    { "UnableToShearImage", 256 },
    { "WidthOrHeightExceedsLimit", 257 },
    { "UnableToPersistKey", 258 },
    { "Default", 259 },
    { "DPSLibraryIsNotAvailable", 260 },
    { "FPXLibraryIsNotAvailable", 261 },
    { "FreeTypeLibraryIsNotAvailable", 262 },
    { "JPEGLibraryIsNotAvailable", 263 },
    { "LCMSLibraryIsNotAvailable", 264 },
    { "LZWEncodingNotEnabled", 265 },
    { "NoDecodeDelegateForThisImageFormat", 266 },
    { "NoEncodeDelegateForThisImageFormat", 267 },
    { "TIFFLibraryIsNotAvailable", 268 },
    { "XMLLibraryIsNotAvailable", 269 },
    { "XWindowLibraryIsNotAvailable", 270 },
    { "ZipLibraryIsNotAvailable", 271 },
    { "Default", 272 },
    { "Default", 273 },
    { "FailedToCloseModule", 274 },
    { "FailedToFindSymbol", 275 },
    { "UnableToLoadModule", 276 },
    { "UnableToRegisterImageFormat", 277 },
    { "UnrecognizedModule", 278 },
    { "UnableToInitializeModuleLoader", 279 },
    { "Default", 280 },
    { "Default", 281 },
    { "Default", 282 },
    { "UserRequestedTerminationBySignal", 283 },
    { "Default", 284 },
    { "BevelWidthIsNegative", 285 },
    { "ColorSeparatedImageRequired", 286 },
    { "FrameIsLessThanImageSize", 287 },
    { "GeometryDimensionsAreZero", 288 },
    { "GeometryDoesNotContainImage", 289 },
    { "HaldClutImageDimensionsInvalid", 290 },
    { "ImagesAreNotTheSameSize", 291 },
    { "ImageSizeMustExceedBevelWidth", 292 },
    { "ImageSmallerThanKernelWidth", 293 },
    { "ImageSmallerThanRadius", 294 },
    { "ImageWidthsOrHeightsDiffer", 295 },
    { "InputImagesAlreadySpecified", 296 },
    { "InvalidSubimageSpecification", 297 },
    { "KernelRadiusIsTooSmall", 298 },
    { "KernelWidthMustBeAnOddNumber", 299 },
    { "MatrixIsNotSquare", 300 },
    { "MatrixOrderOutOfRange", 301 },
    { "MissingAnImageFilename", 302 },
    { "MissingArgument", 303 },
    { "MustSpecifyAnImageName", 304 },
    { "MustSpecifyImageSize", 305 },
    { "NoBlobDefined", 306 },
    { "NoImagesDefined", 307 },
    { "NonzeroWidthAndHeightRequired", 308 },
    { "NoProfileNameWasGiven", 309 },
    { "NullBlobArgument", 310 },
    { "ReferenceImageRequired", 311 },
    { "ReferenceIsNotMyType", 312 },
    { "RegionAreaExceedsLimit", 313 },
    { "RequestDidNotReturnAnImage", 314 },
    { "SteganoImageRequired", 315 },
    { "StereoImageRequired", 316 },
    { "SubimageSpecificationReturnsNoImages", 317 },
    { "TileNotBoundedByImageDimensions", 318 },
    { "UnableToAddOrRemoveProfile", 319 },
    { "UnableToAverageImageSequence", 320 },
    { "UnableToBlurImage", 321 },
    { "UnableToChopImage", 322 },
    { "UnableToColorMatrixImage", 323 },
    { "UnableToConstituteImage", 324 },
    { "UnableToConvolveImage", 325 },
    { "UnableToEdgeImage", 326 },
    { "UnableToEqualizeImage", 327 },
    { "UnableToFilterImage", 328 },
    { "UnableToFormatImageMetadata", 329 },
    { "UnableToFrameImage", 330 },
    { "UnableToOilPaintImage", 331 },
    { "UnableToPaintImage", 332 },
    { "UnableToRaiseImage", 333 },
    { "UnableToSharpenImage", 334 },
    { "UnableToThresholdImage", 335 },
    { "UnableToWaveImage", 336 },
    { "UnrecognizedAttribute", 337 },
    { "UnrecognizedChannelType", 338 },
    { "UnrecognizedColor", 339 },
    { "UnrecognizedColormapType", 340 },
    { "UnrecognizedColorspace", 341 },
    { "UnrecognizedCommand", 342 },
    { "UnrecognizedComposeOperator", 343 },
    { "UnrecognizedDisposeMethod", 344 },
    { "UnrecognizedElement", 345 },
    { "UnrecognizedEndianType", 346 },
    { "UnrecognizedGravityType", 347 },
    { "UnrecognizedHighlightStyle", 348 },
    { "UnrecognizedImageCompression", 349 },
    { "UnrecognizedImageFilter", 350 },
    { "UnrecognizedImageFormat", 351 },
    { "UnrecognizedImageMode", 352 },
    { "UnrecognizedImageType", 353 },
    { "UnrecognizedIntentType", 354 },
    { "UnrecognizedInterlaceType", 355 },
    { "UnrecognizedListType", 356 },
    { "UnrecognizedMetric", 357 },
    { "UnrecognizedModeType", 358 },
    { "UnrecognizedNoiseType", 359 },
    { "UnrecognizedOperator", 360 },
    { "UnrecognizedOption", 361 },
    { "UnrecognizedPerlMagickMethod", 362 },
    { "UnrecognizedPixelMap", 363 },
    { "UnrecognizedPreviewType", 364 },
    { "UnrecognizedResourceType", 365 },
    { "UnrecognizedType", 366 },
    { "UnrecognizedUnitsType", 367 },
    { "UnrecognizedVirtualPixelMethod", 368 },
    { "UnsupportedSamplingFactor", 369 },
    { "UsageError", 370 },
    { "InvalidColorspaceType", 371 },
    { "InvalidEndianType", 372 },
    { "InvalidImageType", 373 },
    { "InvalidInterlaceType", 374 },
    { "MissingAnImageFilename", 375 },
    { "MissingArgument", 376 },
    { "NoImagesWereLoaded", 377 },
    { "OptionLengthExceedsLimit", 378 },
    { "RequestDidNotReturnAnImage", 379 },
    { "UnableToOpenXServer", 380 },
    { "UnableToPersistKey", 381 },
    { "UnrecognizedColormapType", 382 },
    { "UnrecognizedColorspaceType", 383 },
    { "UnrecognizedDisposeMethod", 384 },
    { "UnrecognizedEndianType", 385 },
    { "UnrecognizedFilterType", 386 },
    { "UnrecognizedImageCompressionType", 387 },
    { "UnrecognizedImageType", 388 },
    { "UnrecognizedInterlaceType", 389 },
    { "UnrecognizedOption", 390 },
    { "UnrecognizedResourceType", 391 },
    { "UnrecognizedVirtualPixelMethod", 392 },
    { "UnrecognizedColor", 393 },
    { "ImageExpected", 394 },
    { "ImageInfoExpected", 395 },
    { "StructureSizeMismatch", 396 },
    { "UnableToGetRegistryID", 397 },
    { "UnableToLocateImage", 398 },
    { "UnableToSetRegistry", 399 },
    { "Default", 400 },
    { "Default", 401 },
    { "CacheResourcesExhausted", 402 },
    { "ImagePixelHeightLimitExceeded", 403 },
    { "ImagePixelLimitExceeded", 404 },
    { "ImagePixelWidthLimitExceeded", 405 },
    { "MemoryAllocationFailed", 406 },
    { "NexusPixelHeightLimitExceeded", 407 },
    { "NexusPixelLimitExceeded", 408 },
    { "NexusPixelWidthLimitExceeded", 409 },
    { "NoPixelsDefinedInCache", 410 },
    { "PixelCacheAllocationFailed", 411 },
    { "UnableToAddColorProfile", 412 },
    { "UnableToAddGenericProfile", 413 },
    { "UnableToAddIPTCProfile", 414 },
    { "UnableToAddOrRemoveProfile", 415 },
    { "UnableToAllocateCoefficients", 416 },
    { "UnableToAllocateColormap", 417 },
    { "UnableToAllocateICCProfile", 418 },
    { "UnableToAllocateImage", 419 },
    { "UnableToAllocateString", 420 },
    { "UnableToAnnotateImage", 421 },
    { "UnableToAverageImageSequence", 422 },
    { "UnableToCloneDrawingWand", 423 },
    { "UnableToCloneImage", 424 },
    { "UnableToComputeImageSignature", 425 },
    { "UnableToConstituteImage", 426 },
    { "UnableToConvertFont", 427 },
    { "UnableToConvertStringToTokens", 428 },
    { "UnableToCreateColormap", 429 },
    { "UnableToCreateColorTransform", 430 },
    { "UnableToCreateCommandWidget", 431 },
    { "UnableToCreateImageGroup", 432 },
    { "UnableToCreateImageMontage", 433 },
    { "UnableToCreateXWindow", 434 },
    { "UnableToCropImage", 435 },
    { "UnableToDespeckleImage", 436 },
    { "UnableToDetermineImageClass", 437 },
    { "UnableToDetermineTheNumberOfImageColors", 438 },
    { "UnableToDitherImage", 439 },
    { "UnableToDrawOnImage", 440 },
    { "UnableToEdgeImage", 441 },
    { "UnableToEmbossImage", 442 },
    { "UnableToEnhanceImage", 443 },
    { "UnableToFloodfillImage", 444 },
    { "UnableToGammaCorrectImage", 445 },
    { "UnableToGetBestIconSize", 446 },
    { "UnableToGetFromRegistry", 447 },
    { "UnableToGetPackageInfo", 448 },
    { "UnableToLevelImage", 449 },
    { "UnableToMagnifyImage", 450 },
    { "UnableToManageColor", 451 },
    { "UnableToMapImage", 452 },
    { "UnableToMapImageSequence", 453 },
    { "UnableToMedianFilterImage", 454 },
    { "UnableToMotionBlurImage", 455 },
    { "UnableToNoiseFilterImage", 456 },
    { "UnableToNormalizeImage", 457 },
    { "UnableToOpenColorProfile", 458 },
    { "UnableToQuantizeImage", 459 },
    { "UnableToQuantizeImageSequence", 460 },
    { "UnableToReadTextChunk", 461 },
    { "UnableToReadXImage", 462 },
    { "UnableToReadXServerColormap", 463 },
    { "UnableToResizeImage", 464 },
    { "UnableToRotateImage", 465 },
    { "UnableToSampleImage", 466 },
    { "UnableToScaleImage", 467 },
    { "UnableToSelectImage", 468 },
    { "UnableToSharpenImage", 469 },
    { "UnableToShaveImage", 470 },
    { "UnableToShearImage", 471 },
    { "UnableToSortImageColormap", 472 },
    { "UnableToThresholdImage", 473 },
    { "UnableToTransformColorspace", 474 },
    { "MemoryAllocationFailed", 475 },
    { "SemaporeOperationFailed", 476 },
    { "UnableToAllocateAscii85Info", 477 },
    { "UnableToAllocateCacheInfo", 478 },
    { "UnableToAllocateCacheView", 479 },
    { "UnableToAllocateColorInfo", 480 },
    { "UnableToAllocateDashPattern", 481 },
    { "UnableToAllocateDelegateInfo", 482 },
    { "UnableToAllocateDerivatives", 483 },
    { "UnableToAllocateDrawContext", 484 },
    { "UnableToAllocateDrawInfo", 485 },
    { "UnableToAllocateDrawingWand", 486 },
    { "UnableToAllocateGammaMap", 487 },
    { "UnableToAllocateImage", 488 },
    { "UnableToAllocateImagePixels", 489 },
    { "UnableToAllocateLogInfo", 490 },
    { "UnableToAllocateMagicInfo", 491 },
    { "UnableToAllocateMagickInfo", 492 },
    { "UnableToAllocateMagickMap", 493 },
    { "UnableToAllocateModuleInfo", 494 },
    { "UnableToAllocateMontageInfo", 495 },
    { "UnableToAllocateQuantizeInfo", 496 },
    { "UnableToAllocateRandomKernel", 497 },
    { "UnableToAllocateRegistryInfo", 498 },
    { "UnableToAllocateSemaphoreInfo", 499 },
    { "UnableToAllocateString", 500 },
    { "UnableToAllocateTypeInfo", 501 },
    { "UnableToAllocateWand", 502 },
    { "UnableToAnimateImageSequence", 503 },
    { "UnableToCloneBlobInfo", 504 },
    { "UnableToCloneCacheInfo", 505 },
    { "UnableToCloneImage", 506 },
    { "UnableToCloneImageInfo", 507 },
    { "UnableToConcatenateString", 508 },
    { "UnableToConvertText", 509 },
    { "UnableToCreateColormap", 510 },
    { "UnableToDestroySemaphore", 511 },
    { "UnableToDisplayImage", 512 },
    { "UnableToEscapeString", 513 },
    { "UnableToInitializeSemaphore", 514 },
    { "UnableToInterpretMSLImage", 515 },
    { "UnableToLockSemaphore", 516 },
    { "UnableToObtainRandomEntropy", 517 },
    { "UnableToUnlockSemaphore", 518 },
    { "MemoryAllocationFailed", 519 },
    { "ImageDoesNotContainTheStreamGeometry", 520 },
    { "NoStreamHandlerIsDefined", 521 },
    { "PixelCacheIsNotOpen", 522 },
    { "UnableToAcquirePixelStream", 523 },
    { "UnableToSetPixelStream", 524 },
    { "UnableToSyncPixelStream", 525 },
    { "Default", 526 },
    { "Default", 527 },
    { "FontNotSpecified", 528 },
    { "FontSubstitutionRequired", 529 },
    { "UnableToGetTypeMetrics", 530 },
    { "UnableToInitializeFreetypeLibrary", 531 },
    { "UnableToReadFont", 532 },
    { "UnrecognizedFontEncoding", 533 },
    { "Default", 534 },
    { "Default", 535 },
    { "InvalidColormapIndex", 536 },
    { "WandAPINotImplemented", 537 },
    { "WandContainsNoImageIndexs", 538 },
    { "WandContainsNoImages", 539 },
    { "ColorIsNotKnownToServer", 540 },
    { "NoWindowWithSpecifiedIDExists", 541 },
    { "StandardColormapIsNotInitialized", 542 },
    { "UnableToConnectToRemoteDisplay", 543 },
    { "UnableToCreateBitmap", 544 },
    { "UnableToCreateColormap", 545 },
    { "UnableToCreatePixmap", 546 },
    { "UnableToCreateProperty", 547 },
    { "UnableToCreateStandardColormap", 548 },
    { "UnableToDisplayImageInfo", 549 },
    { "UnableToGetProperty", 550 },
    { "UnableToGetStandardColormap", 551 },
    { "UnableToGetVisual", 552 },
    { "UnableToGrabMouse", 553 },
    { "UnableToLoadFont", 554 },
    { "UnableToMatchVisualToStandardColormap", 555 },
    { "UnableToOpenXServer", 556 },
    { "UnableToReadXAttributes", 557 },
    { "UnableToReadXWindowImage", 558 },
    { "UnrecognizedColormapType", 559 },
    { "UnrecognizedGravityType", 560 },
    { "UnrecognizedVisualSpecifier", 561 },
    { "UnableToAllocateXHints", 562 },
    { "UnableToCreateCursor", 563 },
    { "UnableToCreateGraphicContext", 564 },
    { "UnableToCreateStandardColormap", 565 },
    { "UnableToCreateTextProperty", 566 },
    { "UnableToCreateXImage", 567 },
    { "UnableToCreateXPixmap", 568 },
    { "UnableToCreateXWindow", 569 },
    { "UnableToDisplayImage", 570 },
    { "UnableToDitherImage", 571 },
    { "UnableToGetPixelInfo", 572 },
    { "UnableToGetVisual", 573 },
    { "UnableToLoadFont", 574 },
    { "UnableToMakeXWindow", 575 },
    { "UnableToOpenXServer", 576 },
    { "UnableToViewFonts", 577 },
    { "UnableToGetVisual", 578 },
    { "UsingDefaultVisual", 579 },
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
    "Cache nexus contains no pixels",
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
    "Coder did not return an image (this is a bug, please report it!)",
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
    "Unable to parse embedded profile",
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
    "Pixel nexus height limit exceeded (see -limit Height)",
    "Pixel nexus limit exceeded (see -limit Pixels)",
    "Pixel nexus width limit exceeded (see -limit Width)",
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

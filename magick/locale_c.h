#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 570

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
#define MGK_ImageErrorUnableToGetCompositeMask 244
#define MGK_ImageErrorUnableToHandleImageChannel 245
#define MGK_ImageErrorUnableToImportImagePixels 246
#define MGK_ImageErrorUnableToResizeImage 247
#define MGK_ImageErrorUnableToSegmentImage 248
#define MGK_ImageErrorUnableToSetClipMask 249
#define MGK_ImageErrorUnableToSetCompositeMask 250
#define MGK_ImageErrorUnableToShearImage 251
#define MGK_ImageErrorWidthOrHeightExceedsLimit 252
#define MGK_ImageFatalErrorUnableToPersistKey 253
#define MGK_ImageWarningDefault 254
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 255
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 256
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 257
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 258
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 259
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 260
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 261
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 262
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 263
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 264
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 265
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 266
#define MGK_MissingDelegateFatalErrorDefault 267
#define MGK_MissingDelegateWarningDefault 268
#define MGK_ModuleErrorFailedToCloseModule 269
#define MGK_ModuleErrorFailedToFindSymbol 270
#define MGK_ModuleErrorUnableToLoadModule 271
#define MGK_ModuleErrorUnableToRegisterImageFormat 272
#define MGK_ModuleErrorUnrecognizedModule 273
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 274
#define MGK_ModuleWarningDefault 275
#define MGK_MonitorErrorDefault 276
#define MGK_MonitorFatalErrorDefault 277
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 278
#define MGK_MonitorWarningDefault 279
#define MGK_OptionErrorBevelWidthIsNegative 280
#define MGK_OptionErrorColorSeparatedImageRequired 281
#define MGK_OptionErrorFrameIsLessThanImageSize 282
#define MGK_OptionErrorGeometryDimensionsAreZero 283
#define MGK_OptionErrorGeometryDoesNotContainImage 284
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 285
#define MGK_OptionErrorImagesAreNotTheSameSize 286
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 287
#define MGK_OptionErrorImageSmallerThanKernelWidth 288
#define MGK_OptionErrorImageSmallerThanRadius 289
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 290
#define MGK_OptionErrorInputImagesAlreadySpecified 291
#define MGK_OptionErrorInvalidSubimageSpecification 292
#define MGK_OptionErrorKernelRadiusIsTooSmall 293
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 294
#define MGK_OptionErrorMatrixIsNotSquare 295
#define MGK_OptionErrorMatrixOrderOutOfRange 296
#define MGK_OptionErrorMissingAnImageFilename 297
#define MGK_OptionErrorMissingArgument 298
#define MGK_OptionErrorMustSpecifyAnImageName 299
#define MGK_OptionErrorMustSpecifyImageSize 300
#define MGK_OptionErrorNoBlobDefined 301
#define MGK_OptionErrorNoImagesDefined 302
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 303
#define MGK_OptionErrorNoProfileNameWasGiven 304
#define MGK_OptionErrorNullBlobArgument 305
#define MGK_OptionErrorReferenceImageRequired 306
#define MGK_OptionErrorReferenceIsNotMyType 307
#define MGK_OptionErrorRegionAreaExceedsLimit 308
#define MGK_OptionErrorRequestDidNotReturnAnImage 309
#define MGK_OptionErrorSteganoImageRequired 310
#define MGK_OptionErrorStereoImageRequired 311
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 312
#define MGK_OptionErrorTileNotBoundedByImageDimensions 313
#define MGK_OptionErrorUnableToAddOrRemoveProfile 314
#define MGK_OptionErrorUnableToAverageImageSequence 315
#define MGK_OptionErrorUnableToBlurImage 316
#define MGK_OptionErrorUnableToChopImage 317
#define MGK_OptionErrorUnableToColorMatrixImage 318
#define MGK_OptionErrorUnableToConstituteImage 319
#define MGK_OptionErrorUnableToConvolveImage 320
#define MGK_OptionErrorUnableToEdgeImage 321
#define MGK_OptionErrorUnableToEqualizeImage 322
#define MGK_OptionErrorUnableToFilterImage 323
#define MGK_OptionErrorUnableToFormatImageMetadata 324
#define MGK_OptionErrorUnableToFrameImage 325
#define MGK_OptionErrorUnableToOilPaintImage 326
#define MGK_OptionErrorUnableToPaintImage 327
#define MGK_OptionErrorUnableToRaiseImage 328
#define MGK_OptionErrorUnableToSharpenImage 329
#define MGK_OptionErrorUnableToThresholdImage 330
#define MGK_OptionErrorUnableToWaveImage 331
#define MGK_OptionErrorUnrecognizedAttribute 332
#define MGK_OptionErrorUnrecognizedChannelType 333
#define MGK_OptionErrorUnrecognizedColor 334
#define MGK_OptionErrorUnrecognizedColormapType 335
#define MGK_OptionErrorUnrecognizedColorspace 336
#define MGK_OptionErrorUnrecognizedCommand 337
#define MGK_OptionErrorUnrecognizedComposeOperator 338
#define MGK_OptionErrorUnrecognizedDisposeMethod 339
#define MGK_OptionErrorUnrecognizedElement 340
#define MGK_OptionErrorUnrecognizedEndianType 341
#define MGK_OptionErrorUnrecognizedGravityType 342
#define MGK_OptionErrorUnrecognizedHighlightStyle 343
#define MGK_OptionErrorUnrecognizedImageCompression 344
#define MGK_OptionErrorUnrecognizedImageFilter 345
#define MGK_OptionErrorUnrecognizedImageFormat 346
#define MGK_OptionErrorUnrecognizedImageMode 347
#define MGK_OptionErrorUnrecognizedImageType 348
#define MGK_OptionErrorUnrecognizedIntentType 349
#define MGK_OptionErrorUnrecognizedInterlaceType 350
#define MGK_OptionErrorUnrecognizedListType 351
#define MGK_OptionErrorUnrecognizedMetric 352
#define MGK_OptionErrorUnrecognizedModeType 353
#define MGK_OptionErrorUnrecognizedNoiseType 354
#define MGK_OptionErrorUnrecognizedOperator 355
#define MGK_OptionErrorUnrecognizedOption 356
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 357
#define MGK_OptionErrorUnrecognizedPixelMap 358
#define MGK_OptionErrorUnrecognizedPreviewType 359
#define MGK_OptionErrorUnrecognizedResourceType 360
#define MGK_OptionErrorUnrecognizedType 361
#define MGK_OptionErrorUnrecognizedUnitsType 362
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 363
#define MGK_OptionErrorUnsupportedSamplingFactor 364
#define MGK_OptionErrorUsageError 365
#define MGK_OptionFatalErrorInvalidColorspaceType 366
#define MGK_OptionFatalErrorInvalidEndianType 367
#define MGK_OptionFatalErrorInvalidImageType 368
#define MGK_OptionFatalErrorInvalidInterlaceType 369
#define MGK_OptionFatalErrorMissingAnImageFilename 370
#define MGK_OptionFatalErrorMissingArgument 371
#define MGK_OptionFatalErrorNoImagesWereLoaded 372
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 373
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 374
#define MGK_OptionFatalErrorUnableToOpenXServer 375
#define MGK_OptionFatalErrorUnableToPersistKey 376
#define MGK_OptionFatalErrorUnrecognizedColormapType 377
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 378
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 379
#define MGK_OptionFatalErrorUnrecognizedEndianType 380
#define MGK_OptionFatalErrorUnrecognizedFilterType 381
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 382
#define MGK_OptionFatalErrorUnrecognizedImageType 383
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 384
#define MGK_OptionFatalErrorUnrecognizedOption 385
#define MGK_OptionFatalErrorUnrecognizedResourceType 386
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 387
#define MGK_OptionWarningUnrecognizedColor 388
#define MGK_RegistryErrorImageExpected 389
#define MGK_RegistryErrorImageInfoExpected 390
#define MGK_RegistryErrorStructureSizeMismatch 391
#define MGK_RegistryErrorUnableToGetRegistryID 392
#define MGK_RegistryErrorUnableToLocateImage 393
#define MGK_RegistryErrorUnableToSetRegistry 394
#define MGK_RegistryFatalErrorDefault 395
#define MGK_RegistryWarningDefault 396
#define MGK_ResourceLimitErrorCacheResourcesExhausted 397
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 398
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 399
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 400
#define MGK_ResourceLimitErrorMemoryAllocationFailed 401
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 402
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 403
#define MGK_ResourceLimitErrorUnableToAddColorProfile 404
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 405
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 406
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 407
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 408
#define MGK_ResourceLimitErrorUnableToAllocateColormap 409
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 410
#define MGK_ResourceLimitErrorUnableToAllocateImage 411
#define MGK_ResourceLimitErrorUnableToAllocateString 412
#define MGK_ResourceLimitErrorUnableToAnnotateImage 413
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 414
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 415
#define MGK_ResourceLimitErrorUnableToCloneImage 416
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 417
#define MGK_ResourceLimitErrorUnableToConstituteImage 418
#define MGK_ResourceLimitErrorUnableToConvertFont 419
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 420
#define MGK_ResourceLimitErrorUnableToCreateColormap 421
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 422
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 423
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 424
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 425
#define MGK_ResourceLimitErrorUnableToCreateXWindow 426
#define MGK_ResourceLimitErrorUnableToCropImage 427
#define MGK_ResourceLimitErrorUnableToDespeckleImage 428
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 429
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 430
#define MGK_ResourceLimitErrorUnableToDitherImage 431
#define MGK_ResourceLimitErrorUnableToDrawOnImage 432
#define MGK_ResourceLimitErrorUnableToEdgeImage 433
#define MGK_ResourceLimitErrorUnableToEmbossImage 434
#define MGK_ResourceLimitErrorUnableToEnhanceImage 435
#define MGK_ResourceLimitErrorUnableToFloodfillImage 436
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 437
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 438
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 439
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 440
#define MGK_ResourceLimitErrorUnableToLevelImage 441
#define MGK_ResourceLimitErrorUnableToMagnifyImage 442
#define MGK_ResourceLimitErrorUnableToManageColor 443
#define MGK_ResourceLimitErrorUnableToMapImage 444
#define MGK_ResourceLimitErrorUnableToMapImageSequence 445
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 446
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 447
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 448
#define MGK_ResourceLimitErrorUnableToNormalizeImage 449
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 450
#define MGK_ResourceLimitErrorUnableToQuantizeImage 451
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 452
#define MGK_ResourceLimitErrorUnableToReadTextChunk 453
#define MGK_ResourceLimitErrorUnableToReadXImage 454
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 455
#define MGK_ResourceLimitErrorUnableToResizeImage 456
#define MGK_ResourceLimitErrorUnableToRotateImage 457
#define MGK_ResourceLimitErrorUnableToSampleImage 458
#define MGK_ResourceLimitErrorUnableToScaleImage 459
#define MGK_ResourceLimitErrorUnableToSelectImage 460
#define MGK_ResourceLimitErrorUnableToSharpenImage 461
#define MGK_ResourceLimitErrorUnableToShaveImage 462
#define MGK_ResourceLimitErrorUnableToShearImage 463
#define MGK_ResourceLimitErrorUnableToSortImageColormap 464
#define MGK_ResourceLimitErrorUnableToThresholdImage 465
#define MGK_ResourceLimitErrorUnableToTransformColorspace 466
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 467
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 475
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 477
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 478
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 479
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 480
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 481
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 490
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 491
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 492
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 493
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 494
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 495
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 496
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 497
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 498
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 499
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 500
#define MGK_ResourceLimitFatalErrorUnableToConvertText 501
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 502
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 503
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 504
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 505
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 506
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 507
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 508
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 509
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 510
#define MGK_ResourceLimitWarningMemoryAllocationFailed 511
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 512
#define MGK_StreamErrorNoStreamHandlerIsDefined 513
#define MGK_StreamErrorPixelCacheIsNotOpen 514
#define MGK_StreamErrorUnableToAcquirePixelStream 515
#define MGK_StreamErrorUnableToSetPixelStream 516
#define MGK_StreamErrorUnableToSyncPixelStream 517
#define MGK_StreamFatalErrorDefault 518
#define MGK_StreamWarningDefault 519
#define MGK_TypeErrorFontSubstitutionRequired 520
#define MGK_TypeErrorUnableToGetTypeMetrics 521
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 522
#define MGK_TypeErrorUnableToReadFont 523
#define MGK_TypeErrorUnrecognizedFontEncoding 524
#define MGK_TypeFatalErrorDefault 525
#define MGK_TypeWarningDefault 526
#define MGK_WandErrorInvalidColormapIndex 527
#define MGK_WandErrorWandAPINotImplemented 528
#define MGK_WandErrorWandContainsNoImageIndexs 529
#define MGK_WandErrorWandContainsNoImages 530
#define MGK_XServerErrorColorIsNotKnownToServer 531
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 532
#define MGK_XServerErrorStandardColormapIsNotInitialized 533
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 534
#define MGK_XServerErrorUnableToCreateBitmap 535
#define MGK_XServerErrorUnableToCreateColormap 536
#define MGK_XServerErrorUnableToCreatePixmap 537
#define MGK_XServerErrorUnableToCreateProperty 538
#define MGK_XServerErrorUnableToCreateStandardColormap 539
#define MGK_XServerErrorUnableToDisplayImageInfo 540
#define MGK_XServerErrorUnableToGetProperty 541
#define MGK_XServerErrorUnableToGetStandardColormap 542
#define MGK_XServerErrorUnableToGetVisual 543
#define MGK_XServerErrorUnableToGrabMouse 544
#define MGK_XServerErrorUnableToLoadFont 545
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 546
#define MGK_XServerErrorUnableToOpenXServer 547
#define MGK_XServerErrorUnableToReadXAttributes 548
#define MGK_XServerErrorUnableToReadXWindowImage 549
#define MGK_XServerErrorUnrecognizedColormapType 550
#define MGK_XServerErrorUnrecognizedGravityType 551
#define MGK_XServerErrorUnrecognizedVisualSpecifier 552
#define MGK_XServerFatalErrorUnableToAllocateXHints 553
#define MGK_XServerFatalErrorUnableToCreateCursor 554
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 555
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 556
#define MGK_XServerFatalErrorUnableToCreateTextProperty 557
#define MGK_XServerFatalErrorUnableToCreateXImage 558
#define MGK_XServerFatalErrorUnableToCreateXPixmap 559
#define MGK_XServerFatalErrorUnableToCreateXWindow 560
#define MGK_XServerFatalErrorUnableToDisplayImage 561
#define MGK_XServerFatalErrorUnableToDitherImage 562
#define MGK_XServerFatalErrorUnableToGetPixelInfo 563
#define MGK_XServerFatalErrorUnableToGetVisual 564
#define MGK_XServerFatalErrorUnableToLoadFont 565
#define MGK_XServerFatalErrorUnableToMakeXWindow 566
#define MGK_XServerFatalErrorUnableToOpenXServer 567
#define MGK_XServerFatalErrorUnableToViewFonts 568
#define MGK_XServerWarningUnableToGetVisual 569
#define MGK_XServerWarningUsingDefaultVisual 570

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
    { "Image/FatalError", 252, ImageFatalError },
    { "Image/Warning", 253, ImageWarning },
    { "Missing/Delegate/Error", 254, MissingDelegateError },
    { "Missing/Delegate/FatalError", 266, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 267, MissingDelegateWarning },
    { "Module/Error", 268, ModuleError },
    { "Module/FatalError", 273, ModuleFatalError },
    { "Module/Warning", 274, ModuleWarning },
    { "Monitor/Error", 275, MonitorError },
    { "Monitor/FatalError", 276, MonitorFatalError },
    { "Monitor/Warning", 278, MonitorWarning },
    { "Option/Error", 279, OptionError },
    { "Option/FatalError", 365, OptionFatalError },
    { "Option/Warning", 387, OptionWarning },
    { "Registry/Error", 388, RegistryError },
    { "Registry/FatalError", 394, RegistryFatalError },
    { "Registry/Warning", 395, RegistryWarning },
    { "Resource/Limit/Error", 396, ResourceLimitError },
    { "Resource/Limit/FatalError", 466, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 510, ResourceLimitWarning },
    { "Stream/Error", 511, StreamError },
    { "Stream/FatalError", 517, StreamFatalError },
    { "Stream/Warning", 518, StreamWarning },
    { "Type/Error", 519, TypeError },
    { "Type/FatalError", 524, TypeFatalError },
    { "Type/Warning", 525, TypeWarning },
    { "Wand/Error", 526, WandError },
    { "XServer/Error", 530, XServerError },
    { "XServer/FatalError", 552, XServerFatalError },
    { "XServer/Warning", 568, XServerWarning },
    { 0, 570, UndefinedException }
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
    { "UnableToGetCompositeMask", 244 },
    { "UnableToHandleImageChannel", 245 },
    { "UnableToImportImagePixels", 246 },
    { "UnableToResizeImage", 247 },
    { "UnableToSegmentImage", 248 },
    { "UnableToSetClipMask", 249 },
    { "UnableToSetCompositeMask", 250 },
    { "UnableToShearImage", 251 },
    { "WidthOrHeightExceedsLimit", 252 },
    { "UnableToPersistKey", 253 },
    { "Default", 254 },
    { "DPSLibraryIsNotAvailable", 255 },
    { "FPXLibraryIsNotAvailable", 256 },
    { "FreeTypeLibraryIsNotAvailable", 257 },
    { "JPEGLibraryIsNotAvailable", 258 },
    { "LCMSLibraryIsNotAvailable", 259 },
    { "LZWEncodingNotEnabled", 260 },
    { "NoDecodeDelegateForThisImageFormat", 261 },
    { "NoEncodeDelegateForThisImageFormat", 262 },
    { "TIFFLibraryIsNotAvailable", 263 },
    { "XMLLibraryIsNotAvailable", 264 },
    { "XWindowLibraryIsNotAvailable", 265 },
    { "ZipLibraryIsNotAvailable", 266 },
    { "Default", 267 },
    { "Default", 268 },
    { "FailedToCloseModule", 269 },
    { "FailedToFindSymbol", 270 },
    { "UnableToLoadModule", 271 },
    { "UnableToRegisterImageFormat", 272 },
    { "UnrecognizedModule", 273 },
    { "UnableToInitializeModuleLoader", 274 },
    { "Default", 275 },
    { "Default", 276 },
    { "Default", 277 },
    { "UserRequestedTerminationBySignal", 278 },
    { "Default", 279 },
    { "BevelWidthIsNegative", 280 },
    { "ColorSeparatedImageRequired", 281 },
    { "FrameIsLessThanImageSize", 282 },
    { "GeometryDimensionsAreZero", 283 },
    { "GeometryDoesNotContainImage", 284 },
    { "HaldClutImageDimensionsInvalid", 285 },
    { "ImagesAreNotTheSameSize", 286 },
    { "ImageSizeMustExceedBevelWidth", 287 },
    { "ImageSmallerThanKernelWidth", 288 },
    { "ImageSmallerThanRadius", 289 },
    { "ImageWidthsOrHeightsDiffer", 290 },
    { "InputImagesAlreadySpecified", 291 },
    { "InvalidSubimageSpecification", 292 },
    { "KernelRadiusIsTooSmall", 293 },
    { "KernelWidthMustBeAnOddNumber", 294 },
    { "MatrixIsNotSquare", 295 },
    { "MatrixOrderOutOfRange", 296 },
    { "MissingAnImageFilename", 297 },
    { "MissingArgument", 298 },
    { "MustSpecifyAnImageName", 299 },
    { "MustSpecifyImageSize", 300 },
    { "NoBlobDefined", 301 },
    { "NoImagesDefined", 302 },
    { "NonzeroWidthAndHeightRequired", 303 },
    { "NoProfileNameWasGiven", 304 },
    { "NullBlobArgument", 305 },
    { "ReferenceImageRequired", 306 },
    { "ReferenceIsNotMyType", 307 },
    { "RegionAreaExceedsLimit", 308 },
    { "RequestDidNotReturnAnImage", 309 },
    { "SteganoImageRequired", 310 },
    { "StereoImageRequired", 311 },
    { "SubimageSpecificationReturnsNoImages", 312 },
    { "TileNotBoundedByImageDimensions", 313 },
    { "UnableToAddOrRemoveProfile", 314 },
    { "UnableToAverageImageSequence", 315 },
    { "UnableToBlurImage", 316 },
    { "UnableToChopImage", 317 },
    { "UnableToColorMatrixImage", 318 },
    { "UnableToConstituteImage", 319 },
    { "UnableToConvolveImage", 320 },
    { "UnableToEdgeImage", 321 },
    { "UnableToEqualizeImage", 322 },
    { "UnableToFilterImage", 323 },
    { "UnableToFormatImageMetadata", 324 },
    { "UnableToFrameImage", 325 },
    { "UnableToOilPaintImage", 326 },
    { "UnableToPaintImage", 327 },
    { "UnableToRaiseImage", 328 },
    { "UnableToSharpenImage", 329 },
    { "UnableToThresholdImage", 330 },
    { "UnableToWaveImage", 331 },
    { "UnrecognizedAttribute", 332 },
    { "UnrecognizedChannelType", 333 },
    { "UnrecognizedColor", 334 },
    { "UnrecognizedColormapType", 335 },
    { "UnrecognizedColorspace", 336 },
    { "UnrecognizedCommand", 337 },
    { "UnrecognizedComposeOperator", 338 },
    { "UnrecognizedDisposeMethod", 339 },
    { "UnrecognizedElement", 340 },
    { "UnrecognizedEndianType", 341 },
    { "UnrecognizedGravityType", 342 },
    { "UnrecognizedHighlightStyle", 343 },
    { "UnrecognizedImageCompression", 344 },
    { "UnrecognizedImageFilter", 345 },
    { "UnrecognizedImageFormat", 346 },
    { "UnrecognizedImageMode", 347 },
    { "UnrecognizedImageType", 348 },
    { "UnrecognizedIntentType", 349 },
    { "UnrecognizedInterlaceType", 350 },
    { "UnrecognizedListType", 351 },
    { "UnrecognizedMetric", 352 },
    { "UnrecognizedModeType", 353 },
    { "UnrecognizedNoiseType", 354 },
    { "UnrecognizedOperator", 355 },
    { "UnrecognizedOption", 356 },
    { "UnrecognizedPerlMagickMethod", 357 },
    { "UnrecognizedPixelMap", 358 },
    { "UnrecognizedPreviewType", 359 },
    { "UnrecognizedResourceType", 360 },
    { "UnrecognizedType", 361 },
    { "UnrecognizedUnitsType", 362 },
    { "UnrecognizedVirtualPixelMethod", 363 },
    { "UnsupportedSamplingFactor", 364 },
    { "UsageError", 365 },
    { "InvalidColorspaceType", 366 },
    { "InvalidEndianType", 367 },
    { "InvalidImageType", 368 },
    { "InvalidInterlaceType", 369 },
    { "MissingAnImageFilename", 370 },
    { "MissingArgument", 371 },
    { "NoImagesWereLoaded", 372 },
    { "OptionLengthExceedsLimit", 373 },
    { "RequestDidNotReturnAnImage", 374 },
    { "UnableToOpenXServer", 375 },
    { "UnableToPersistKey", 376 },
    { "UnrecognizedColormapType", 377 },
    { "UnrecognizedColorspaceType", 378 },
    { "UnrecognizedDisposeMethod", 379 },
    { "UnrecognizedEndianType", 380 },
    { "UnrecognizedFilterType", 381 },
    { "UnrecognizedImageCompressionType", 382 },
    { "UnrecognizedImageType", 383 },
    { "UnrecognizedInterlaceType", 384 },
    { "UnrecognizedOption", 385 },
    { "UnrecognizedResourceType", 386 },
    { "UnrecognizedVirtualPixelMethod", 387 },
    { "UnrecognizedColor", 388 },
    { "ImageExpected", 389 },
    { "ImageInfoExpected", 390 },
    { "StructureSizeMismatch", 391 },
    { "UnableToGetRegistryID", 392 },
    { "UnableToLocateImage", 393 },
    { "UnableToSetRegistry", 394 },
    { "Default", 395 },
    { "Default", 396 },
    { "CacheResourcesExhausted", 397 },
    { "ImagePixelHeightLimitExceeded", 398 },
    { "ImagePixelLimitExceeded", 399 },
    { "ImagePixelWidthLimitExceeded", 400 },
    { "MemoryAllocationFailed", 401 },
    { "NoPixelsDefinedInCache", 402 },
    { "PixelCacheAllocationFailed", 403 },
    { "UnableToAddColorProfile", 404 },
    { "UnableToAddGenericProfile", 405 },
    { "UnableToAddIPTCProfile", 406 },
    { "UnableToAddOrRemoveProfile", 407 },
    { "UnableToAllocateCoefficients", 408 },
    { "UnableToAllocateColormap", 409 },
    { "UnableToAllocateICCProfile", 410 },
    { "UnableToAllocateImage", 411 },
    { "UnableToAllocateString", 412 },
    { "UnableToAnnotateImage", 413 },
    { "UnableToAverageImageSequence", 414 },
    { "UnableToCloneDrawingWand", 415 },
    { "UnableToCloneImage", 416 },
    { "UnableToComputeImageSignature", 417 },
    { "UnableToConstituteImage", 418 },
    { "UnableToConvertFont", 419 },
    { "UnableToConvertStringToTokens", 420 },
    { "UnableToCreateColormap", 421 },
    { "UnableToCreateColorTransform", 422 },
    { "UnableToCreateCommandWidget", 423 },
    { "UnableToCreateImageGroup", 424 },
    { "UnableToCreateImageMontage", 425 },
    { "UnableToCreateXWindow", 426 },
    { "UnableToCropImage", 427 },
    { "UnableToDespeckleImage", 428 },
    { "UnableToDetermineImageClass", 429 },
    { "UnableToDetermineTheNumberOfImageColors", 430 },
    { "UnableToDitherImage", 431 },
    { "UnableToDrawOnImage", 432 },
    { "UnableToEdgeImage", 433 },
    { "UnableToEmbossImage", 434 },
    { "UnableToEnhanceImage", 435 },
    { "UnableToFloodfillImage", 436 },
    { "UnableToGammaCorrectImage", 437 },
    { "UnableToGetBestIconSize", 438 },
    { "UnableToGetFromRegistry", 439 },
    { "UnableToGetPackageInfo", 440 },
    { "UnableToLevelImage", 441 },
    { "UnableToMagnifyImage", 442 },
    { "UnableToManageColor", 443 },
    { "UnableToMapImage", 444 },
    { "UnableToMapImageSequence", 445 },
    { "UnableToMedianFilterImage", 446 },
    { "UnableToMotionBlurImage", 447 },
    { "UnableToNoiseFilterImage", 448 },
    { "UnableToNormalizeImage", 449 },
    { "UnableToOpenColorProfile", 450 },
    { "UnableToQuantizeImage", 451 },
    { "UnableToQuantizeImageSequence", 452 },
    { "UnableToReadTextChunk", 453 },
    { "UnableToReadXImage", 454 },
    { "UnableToReadXServerColormap", 455 },
    { "UnableToResizeImage", 456 },
    { "UnableToRotateImage", 457 },
    { "UnableToSampleImage", 458 },
    { "UnableToScaleImage", 459 },
    { "UnableToSelectImage", 460 },
    { "UnableToSharpenImage", 461 },
    { "UnableToShaveImage", 462 },
    { "UnableToShearImage", 463 },
    { "UnableToSortImageColormap", 464 },
    { "UnableToThresholdImage", 465 },
    { "UnableToTransformColorspace", 466 },
    { "MemoryAllocationFailed", 467 },
    { "SemaporeOperationFailed", 468 },
    { "UnableToAllocateAscii85Info", 469 },
    { "UnableToAllocateCacheInfo", 470 },
    { "UnableToAllocateCacheView", 471 },
    { "UnableToAllocateColorInfo", 472 },
    { "UnableToAllocateDashPattern", 473 },
    { "UnableToAllocateDelegateInfo", 474 },
    { "UnableToAllocateDerivatives", 475 },
    { "UnableToAllocateDrawContext", 476 },
    { "UnableToAllocateDrawInfo", 477 },
    { "UnableToAllocateDrawingWand", 478 },
    { "UnableToAllocateGammaMap", 479 },
    { "UnableToAllocateImage", 480 },
    { "UnableToAllocateImagePixels", 481 },
    { "UnableToAllocateLogInfo", 482 },
    { "UnableToAllocateMagicInfo", 483 },
    { "UnableToAllocateMagickInfo", 484 },
    { "UnableToAllocateMagickMap", 485 },
    { "UnableToAllocateModuleInfo", 486 },
    { "UnableToAllocateMontageInfo", 487 },
    { "UnableToAllocateQuantizeInfo", 488 },
    { "UnableToAllocateRandomKernel", 489 },
    { "UnableToAllocateRegistryInfo", 490 },
    { "UnableToAllocateSemaphoreInfo", 491 },
    { "UnableToAllocateString", 492 },
    { "UnableToAllocateTypeInfo", 493 },
    { "UnableToAllocateWand", 494 },
    { "UnableToAnimateImageSequence", 495 },
    { "UnableToCloneBlobInfo", 496 },
    { "UnableToCloneCacheInfo", 497 },
    { "UnableToCloneImage", 498 },
    { "UnableToCloneImageInfo", 499 },
    { "UnableToConcatenateString", 500 },
    { "UnableToConvertText", 501 },
    { "UnableToCreateColormap", 502 },
    { "UnableToDestroySemaphore", 503 },
    { "UnableToDisplayImage", 504 },
    { "UnableToEscapeString", 505 },
    { "UnableToInitializeSemaphore", 506 },
    { "UnableToInterpretMSLImage", 507 },
    { "UnableToLockSemaphore", 508 },
    { "UnableToObtainRandomEntropy", 509 },
    { "UnableToUnlockSemaphore", 510 },
    { "MemoryAllocationFailed", 511 },
    { "ImageDoesNotContainTheStreamGeometry", 512 },
    { "NoStreamHandlerIsDefined", 513 },
    { "PixelCacheIsNotOpen", 514 },
    { "UnableToAcquirePixelStream", 515 },
    { "UnableToSetPixelStream", 516 },
    { "UnableToSyncPixelStream", 517 },
    { "Default", 518 },
    { "Default", 519 },
    { "FontSubstitutionRequired", 520 },
    { "UnableToGetTypeMetrics", 521 },
    { "UnableToInitializeFreetypeLibrary", 522 },
    { "UnableToReadFont", 523 },
    { "UnrecognizedFontEncoding", 524 },
    { "Default", 525 },
    { "Default", 526 },
    { "InvalidColormapIndex", 527 },
    { "WandAPINotImplemented", 528 },
    { "WandContainsNoImageIndexs", 529 },
    { "WandContainsNoImages", 530 },
    { "ColorIsNotKnownToServer", 531 },
    { "NoWindowWithSpecifiedIDExists", 532 },
    { "StandardColormapIsNotInitialized", 533 },
    { "UnableToConnectToRemoteDisplay", 534 },
    { "UnableToCreateBitmap", 535 },
    { "UnableToCreateColormap", 536 },
    { "UnableToCreatePixmap", 537 },
    { "UnableToCreateProperty", 538 },
    { "UnableToCreateStandardColormap", 539 },
    { "UnableToDisplayImageInfo", 540 },
    { "UnableToGetProperty", 541 },
    { "UnableToGetStandardColormap", 542 },
    { "UnableToGetVisual", 543 },
    { "UnableToGrabMouse", 544 },
    { "UnableToLoadFont", 545 },
    { "UnableToMatchVisualToStandardColormap", 546 },
    { "UnableToOpenXServer", 547 },
    { "UnableToReadXAttributes", 548 },
    { "UnableToReadXWindowImage", 549 },
    { "UnrecognizedColormapType", 550 },
    { "UnrecognizedGravityType", 551 },
    { "UnrecognizedVisualSpecifier", 552 },
    { "UnableToAllocateXHints", 553 },
    { "UnableToCreateCursor", 554 },
    { "UnableToCreateGraphicContext", 555 },
    { "UnableToCreateStandardColormap", 556 },
    { "UnableToCreateTextProperty", 557 },
    { "UnableToCreateXImage", 558 },
    { "UnableToCreateXPixmap", 559 },
    { "UnableToCreateXWindow", 560 },
    { "UnableToDisplayImage", 561 },
    { "UnableToDitherImage", 562 },
    { "UnableToGetPixelInfo", 563 },
    { "UnableToGetVisual", 564 },
    { "UnableToLoadFont", 565 },
    { "UnableToMakeXWindow", 566 },
    { "UnableToOpenXServer", 567 },
    { "UnableToViewFonts", 568 },
    { "UnableToGetVisual", 569 },
    { "UsingDefaultVisual", 570 },
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

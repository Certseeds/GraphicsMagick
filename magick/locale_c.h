#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 565

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
#define MGK_CorruptImageErrorImageFileHasNoScenes 124
#define MGK_CorruptImageErrorImageTypeNotSupported 125
#define MGK_CorruptImageErrorImproperImageHeader 126
#define MGK_CorruptImageErrorInsufficientImageDataInFile 127
#define MGK_CorruptImageErrorInvalidColormapIndex 128
#define MGK_CorruptImageErrorInvalidFileFormatVersion 129
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 130
#define MGK_CorruptImageErrorMissingImageChannel 131
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 132
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 133
#define MGK_CorruptImageErrorNotEnoughTiles 134
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 135
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 136
#define MGK_CorruptImageErrorTooMuchImageDataInFile 137
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 138
#define MGK_CorruptImageErrorUnableToReadColorProfile 139
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 140
#define MGK_CorruptImageErrorUnableToReadGenericProfile 141
#define MGK_CorruptImageErrorUnableToReadImageData 142
#define MGK_CorruptImageErrorUnableToReadImageHeader 143
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 144
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 145
#define MGK_CorruptImageErrorUnableToReadSubImageData 146
#define MGK_CorruptImageErrorUnableToReadVIDImage 147
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 148
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 149
#define MGK_CorruptImageErrorUnableToUncompressImage 150
#define MGK_CorruptImageErrorUnexpectedEndOfFile 151
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 152
#define MGK_CorruptImageErrorUnknownPatternType 153
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 154
#define MGK_CorruptImageErrorUnrecognizedImageCompression 155
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 156
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 157
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 158
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 159
#define MGK_CorruptImageFatalErrorUnableToPersistKey 160
#define MGK_CorruptImageWarningCompressionNotValid 161
#define MGK_CorruptImageWarningCorruptImage 162
#define MGK_CorruptImageWarningImproperImageHeader 163
#define MGK_CorruptImageWarningInvalidColormapIndex 164
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 165
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 166
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 167
#define MGK_CorruptImageWarningSkipToSyncByte 168
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 169
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 170
#define MGK_CorruptImageWarningUnrecognizedImageCompression 171
#define MGK_DelegateErrorDelegateFailed 172
#define MGK_DelegateErrorFailedToAllocateArgumentList 173
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 174
#define MGK_DelegateErrorFailedToComputeOutputSize 175
#define MGK_DelegateErrorFailedToFindGhostscript 176
#define MGK_DelegateErrorFailedToRenderFile 177
#define MGK_DelegateErrorFailedToScanFile 178
#define MGK_DelegateErrorNoTagFound 179
#define MGK_DelegateErrorPostscriptDelegateFailed 180
#define MGK_DelegateErrorUnableToCreateImage 181
#define MGK_DelegateErrorUnableToCreateImageComponent 182
#define MGK_DelegateErrorUnableToDecodeImageFile 183
#define MGK_DelegateErrorUnableToEncodeImageFile 184
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 185
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 186
#define MGK_DelegateErrorUnableToManageJP2Stream 187
#define MGK_DelegateErrorUnableToWriteSVGFormat 188
#define MGK_DelegateErrorWebPABIMismatch 189
#define MGK_DelegateFatalErrorDefault 190
#define MGK_DelegateWarningDefault 191
#define MGK_DrawErrorAlreadyPushingPatternDefinition 192
#define MGK_DrawErrorDrawingRecursionDetected 193
#define MGK_DrawErrorFloatValueConversionError 194
#define MGK_DrawErrorIntegerValueConversionError 195
#define MGK_DrawErrorInvalidPrimitiveArgument 196
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 197
#define MGK_DrawErrorPrimitiveArithmeticOverflow 198
#define MGK_DrawErrorTooManyCoordinates 199
#define MGK_DrawErrorUnableToPrint 200
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 201
#define MGK_DrawErrorUnreasonableGradientSize 202
#define MGK_DrawErrorVectorPathTruncated 203
#define MGK_DrawFatalErrorDefault 204
#define MGK_DrawWarningNotARelativeURL 205
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 206
#define MGK_DrawWarningURLNotFound 207
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 208
#define MGK_FileOpenErrorUnableToOpenFile 209
#define MGK_FileOpenErrorUnableToWriteFile 210
#define MGK_FileOpenFatalErrorDefault 211
#define MGK_FileOpenWarningDefault 212
#define MGK_ImageErrorAngleIsDiscontinuous 213
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 214
#define MGK_ImageErrorColorspaceColorProfileMismatch 215
#define MGK_ImageErrorImageColorspaceDiffers 216
#define MGK_ImageErrorImageColorspaceMismatch 217
#define MGK_ImageErrorImageDifferenceExceedsLimit 218
#define MGK_ImageErrorImageDoesNotContainResolution 219
#define MGK_ImageErrorImageIsNotColormapped 220
#define MGK_ImageErrorImageOpacityDiffers 221
#define MGK_ImageErrorImageSequenceIsRequired 222
#define MGK_ImageErrorImageSizeDiffers 223
#define MGK_ImageErrorInvalidColormapIndex 224
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 225
#define MGK_ImageErrorNoImagesWereFound 226
#define MGK_ImageErrorNoImagesWereLoaded 227
#define MGK_ImageErrorNoLocaleImageAttribute 228
#define MGK_ImageErrorTooManyClusters 229
#define MGK_ImageErrorUnableToAppendImage 230
#define MGK_ImageErrorUnableToAssignProfile 231
#define MGK_ImageErrorUnableToAverageImage 232
#define MGK_ImageErrorUnableToCoalesceImage 233
#define MGK_ImageErrorUnableToCompareImages 234
#define MGK_ImageErrorUnableToCreateImageMosaic 235
#define MGK_ImageErrorUnableToCreateStereoImage 236
#define MGK_ImageErrorUnableToDeconstructImageSequence 237
#define MGK_ImageErrorUnableToExportImagePixels 238
#define MGK_ImageErrorUnableToFlattenImage 239
#define MGK_ImageErrorUnableToGetClipMask 240
#define MGK_ImageErrorUnableToHandleImageChannel 241
#define MGK_ImageErrorUnableToImportImagePixels 242
#define MGK_ImageErrorUnableToResizeImage 243
#define MGK_ImageErrorUnableToSegmentImage 244
#define MGK_ImageErrorUnableToSetClipMask 245
#define MGK_ImageErrorUnableToShearImage 246
#define MGK_ImageErrorWidthOrHeightExceedsLimit 247
#define MGK_ImageFatalErrorUnableToPersistKey 248
#define MGK_ImageWarningDefault 249
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 250
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 251
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 252
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 253
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 254
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 255
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 256
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 257
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 258
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 259
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 260
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 261
#define MGK_MissingDelegateFatalErrorDefault 262
#define MGK_MissingDelegateWarningDefault 263
#define MGK_ModuleErrorFailedToCloseModule 264
#define MGK_ModuleErrorFailedToFindSymbol 265
#define MGK_ModuleErrorUnableToLoadModule 266
#define MGK_ModuleErrorUnableToRegisterImageFormat 267
#define MGK_ModuleErrorUnrecognizedModule 268
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 269
#define MGK_ModuleWarningDefault 270
#define MGK_MonitorErrorDefault 271
#define MGK_MonitorFatalErrorDefault 272
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 273
#define MGK_MonitorWarningDefault 274
#define MGK_OptionErrorBevelWidthIsNegative 275
#define MGK_OptionErrorColorSeparatedImageRequired 276
#define MGK_OptionErrorFrameIsLessThanImageSize 277
#define MGK_OptionErrorGeometryDimensionsAreZero 278
#define MGK_OptionErrorGeometryDoesNotContainImage 279
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 280
#define MGK_OptionErrorImagesAreNotTheSameSize 281
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 282
#define MGK_OptionErrorImageSmallerThanKernelWidth 283
#define MGK_OptionErrorImageSmallerThanRadius 284
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 285
#define MGK_OptionErrorInputImagesAlreadySpecified 286
#define MGK_OptionErrorInvalidSubimageSpecification 287
#define MGK_OptionErrorKernelRadiusIsTooSmall 288
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 289
#define MGK_OptionErrorMatrixIsNotSquare 290
#define MGK_OptionErrorMatrixOrderOutOfRange 291
#define MGK_OptionErrorMissingAnImageFilename 292
#define MGK_OptionErrorMissingArgument 293
#define MGK_OptionErrorMustSpecifyAnImageName 294
#define MGK_OptionErrorMustSpecifyImageSize 295
#define MGK_OptionErrorNoBlobDefined 296
#define MGK_OptionErrorNoImagesDefined 297
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 298
#define MGK_OptionErrorNoProfileNameWasGiven 299
#define MGK_OptionErrorNullBlobArgument 300
#define MGK_OptionErrorReferenceImageRequired 301
#define MGK_OptionErrorReferenceIsNotMyType 302
#define MGK_OptionErrorRegionAreaExceedsLimit 303
#define MGK_OptionErrorRequestDidNotReturnAnImage 304
#define MGK_OptionErrorSteganoImageRequired 305
#define MGK_OptionErrorStereoImageRequired 306
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 307
#define MGK_OptionErrorTileNotBoundedByImageDimensions 308
#define MGK_OptionErrorUnableToAddOrRemoveProfile 309
#define MGK_OptionErrorUnableToAverageImageSequence 310
#define MGK_OptionErrorUnableToBlurImage 311
#define MGK_OptionErrorUnableToChopImage 312
#define MGK_OptionErrorUnableToColorMatrixImage 313
#define MGK_OptionErrorUnableToConstituteImage 314
#define MGK_OptionErrorUnableToConvolveImage 315
#define MGK_OptionErrorUnableToEdgeImage 316
#define MGK_OptionErrorUnableToEqualizeImage 317
#define MGK_OptionErrorUnableToFilterImage 318
#define MGK_OptionErrorUnableToFormatImageMetadata 319
#define MGK_OptionErrorUnableToFrameImage 320
#define MGK_OptionErrorUnableToOilPaintImage 321
#define MGK_OptionErrorUnableToPaintImage 322
#define MGK_OptionErrorUnableToRaiseImage 323
#define MGK_OptionErrorUnableToSharpenImage 324
#define MGK_OptionErrorUnableToThresholdImage 325
#define MGK_OptionErrorUnableToWaveImage 326
#define MGK_OptionErrorUnrecognizedAttribute 327
#define MGK_OptionErrorUnrecognizedChannelType 328
#define MGK_OptionErrorUnrecognizedColor 329
#define MGK_OptionErrorUnrecognizedColormapType 330
#define MGK_OptionErrorUnrecognizedColorspace 331
#define MGK_OptionErrorUnrecognizedCommand 332
#define MGK_OptionErrorUnrecognizedComposeOperator 333
#define MGK_OptionErrorUnrecognizedDisposeMethod 334
#define MGK_OptionErrorUnrecognizedElement 335
#define MGK_OptionErrorUnrecognizedEndianType 336
#define MGK_OptionErrorUnrecognizedGravityType 337
#define MGK_OptionErrorUnrecognizedHighlightStyle 338
#define MGK_OptionErrorUnrecognizedImageCompression 339
#define MGK_OptionErrorUnrecognizedImageFilter 340
#define MGK_OptionErrorUnrecognizedImageFormat 341
#define MGK_OptionErrorUnrecognizedImageMode 342
#define MGK_OptionErrorUnrecognizedImageType 343
#define MGK_OptionErrorUnrecognizedIntentType 344
#define MGK_OptionErrorUnrecognizedInterlaceType 345
#define MGK_OptionErrorUnrecognizedListType 346
#define MGK_OptionErrorUnrecognizedMetric 347
#define MGK_OptionErrorUnrecognizedModeType 348
#define MGK_OptionErrorUnrecognizedNoiseType 349
#define MGK_OptionErrorUnrecognizedOperator 350
#define MGK_OptionErrorUnrecognizedOption 351
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 352
#define MGK_OptionErrorUnrecognizedPixelMap 353
#define MGK_OptionErrorUnrecognizedPreviewType 354
#define MGK_OptionErrorUnrecognizedResourceType 355
#define MGK_OptionErrorUnrecognizedType 356
#define MGK_OptionErrorUnrecognizedUnitsType 357
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 358
#define MGK_OptionErrorUnsupportedSamplingFactor 359
#define MGK_OptionErrorUsageError 360
#define MGK_OptionFatalErrorInvalidColorspaceType 361
#define MGK_OptionFatalErrorInvalidEndianType 362
#define MGK_OptionFatalErrorInvalidImageType 363
#define MGK_OptionFatalErrorInvalidInterlaceType 364
#define MGK_OptionFatalErrorMissingAnImageFilename 365
#define MGK_OptionFatalErrorMissingArgument 366
#define MGK_OptionFatalErrorNoImagesWereLoaded 367
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 368
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 369
#define MGK_OptionFatalErrorUnableToOpenXServer 370
#define MGK_OptionFatalErrorUnableToPersistKey 371
#define MGK_OptionFatalErrorUnrecognizedColormapType 372
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 373
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 374
#define MGK_OptionFatalErrorUnrecognizedEndianType 375
#define MGK_OptionFatalErrorUnrecognizedFilterType 376
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 377
#define MGK_OptionFatalErrorUnrecognizedImageType 378
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 379
#define MGK_OptionFatalErrorUnrecognizedOption 380
#define MGK_OptionFatalErrorUnrecognizedResourceType 381
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 382
#define MGK_OptionWarningUnrecognizedColor 383
#define MGK_RegistryErrorImageExpected 384
#define MGK_RegistryErrorImageInfoExpected 385
#define MGK_RegistryErrorStructureSizeMismatch 386
#define MGK_RegistryErrorUnableToGetRegistryID 387
#define MGK_RegistryErrorUnableToLocateImage 388
#define MGK_RegistryErrorUnableToSetRegistry 389
#define MGK_RegistryFatalErrorDefault 390
#define MGK_RegistryWarningDefault 391
#define MGK_ResourceLimitErrorCacheResourcesExhausted 392
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 393
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 394
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 395
#define MGK_ResourceLimitErrorMemoryAllocationFailed 396
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 397
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 398
#define MGK_ResourceLimitErrorUnableToAddColorProfile 399
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 400
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 401
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 402
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 403
#define MGK_ResourceLimitErrorUnableToAllocateColormap 404
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 405
#define MGK_ResourceLimitErrorUnableToAllocateImage 406
#define MGK_ResourceLimitErrorUnableToAllocateString 407
#define MGK_ResourceLimitErrorUnableToAnnotateImage 408
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 409
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 410
#define MGK_ResourceLimitErrorUnableToCloneImage 411
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 412
#define MGK_ResourceLimitErrorUnableToConstituteImage 413
#define MGK_ResourceLimitErrorUnableToConvertFont 414
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 415
#define MGK_ResourceLimitErrorUnableToCreateColormap 416
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 417
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 418
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 419
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 420
#define MGK_ResourceLimitErrorUnableToCreateXWindow 421
#define MGK_ResourceLimitErrorUnableToCropImage 422
#define MGK_ResourceLimitErrorUnableToDespeckleImage 423
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 424
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 425
#define MGK_ResourceLimitErrorUnableToDitherImage 426
#define MGK_ResourceLimitErrorUnableToDrawOnImage 427
#define MGK_ResourceLimitErrorUnableToEdgeImage 428
#define MGK_ResourceLimitErrorUnableToEmbossImage 429
#define MGK_ResourceLimitErrorUnableToEnhanceImage 430
#define MGK_ResourceLimitErrorUnableToFloodfillImage 431
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 432
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 433
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 434
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 435
#define MGK_ResourceLimitErrorUnableToLevelImage 436
#define MGK_ResourceLimitErrorUnableToMagnifyImage 437
#define MGK_ResourceLimitErrorUnableToManageColor 438
#define MGK_ResourceLimitErrorUnableToMapImage 439
#define MGK_ResourceLimitErrorUnableToMapImageSequence 440
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 441
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 442
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 443
#define MGK_ResourceLimitErrorUnableToNormalizeImage 444
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 445
#define MGK_ResourceLimitErrorUnableToQuantizeImage 446
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 447
#define MGK_ResourceLimitErrorUnableToReadTextChunk 448
#define MGK_ResourceLimitErrorUnableToReadXImage 449
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 450
#define MGK_ResourceLimitErrorUnableToResizeImage 451
#define MGK_ResourceLimitErrorUnableToRotateImage 452
#define MGK_ResourceLimitErrorUnableToSampleImage 453
#define MGK_ResourceLimitErrorUnableToScaleImage 454
#define MGK_ResourceLimitErrorUnableToSelectImage 455
#define MGK_ResourceLimitErrorUnableToSharpenImage 456
#define MGK_ResourceLimitErrorUnableToShaveImage 457
#define MGK_ResourceLimitErrorUnableToShearImage 458
#define MGK_ResourceLimitErrorUnableToSortImageColormap 459
#define MGK_ResourceLimitErrorUnableToThresholdImage 460
#define MGK_ResourceLimitErrorUnableToTransformColorspace 461
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 462
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 463
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 464
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 465
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 466
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 467
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 475
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 477
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 478
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 479
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 480
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 481
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 489
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 490
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 491
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 492
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 493
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 494
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 495
#define MGK_ResourceLimitFatalErrorUnableToConvertText 496
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 497
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 498
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 499
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 500
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 501
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 502
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 503
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 504
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 505
#define MGK_ResourceLimitWarningMemoryAllocationFailed 506
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 507
#define MGK_StreamErrorNoStreamHandlerIsDefined 508
#define MGK_StreamErrorPixelCacheIsNotOpen 509
#define MGK_StreamErrorUnableToAcquirePixelStream 510
#define MGK_StreamErrorUnableToSetPixelStream 511
#define MGK_StreamErrorUnableToSyncPixelStream 512
#define MGK_StreamFatalErrorDefault 513
#define MGK_StreamWarningDefault 514
#define MGK_TypeErrorFontSubstitutionRequired 515
#define MGK_TypeErrorUnableToGetTypeMetrics 516
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 517
#define MGK_TypeErrorUnableToReadFont 518
#define MGK_TypeErrorUnrecognizedFontEncoding 519
#define MGK_TypeFatalErrorDefault 520
#define MGK_TypeWarningDefault 521
#define MGK_WandErrorInvalidColormapIndex 522
#define MGK_WandErrorWandAPINotImplemented 523
#define MGK_WandErrorWandContainsNoImageIndexs 524
#define MGK_WandErrorWandContainsNoImages 525
#define MGK_XServerErrorColorIsNotKnownToServer 526
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 527
#define MGK_XServerErrorStandardColormapIsNotInitialized 528
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 529
#define MGK_XServerErrorUnableToCreateBitmap 530
#define MGK_XServerErrorUnableToCreateColormap 531
#define MGK_XServerErrorUnableToCreatePixmap 532
#define MGK_XServerErrorUnableToCreateProperty 533
#define MGK_XServerErrorUnableToCreateStandardColormap 534
#define MGK_XServerErrorUnableToDisplayImageInfo 535
#define MGK_XServerErrorUnableToGetProperty 536
#define MGK_XServerErrorUnableToGetStandardColormap 537
#define MGK_XServerErrorUnableToGetVisual 538
#define MGK_XServerErrorUnableToGrabMouse 539
#define MGK_XServerErrorUnableToLoadFont 540
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 541
#define MGK_XServerErrorUnableToOpenXServer 542
#define MGK_XServerErrorUnableToReadXAttributes 543
#define MGK_XServerErrorUnableToReadXWindowImage 544
#define MGK_XServerErrorUnrecognizedColormapType 545
#define MGK_XServerErrorUnrecognizedGravityType 546
#define MGK_XServerErrorUnrecognizedVisualSpecifier 547
#define MGK_XServerFatalErrorUnableToAllocateXHints 548
#define MGK_XServerFatalErrorUnableToCreateCursor 549
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 550
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 551
#define MGK_XServerFatalErrorUnableToCreateTextProperty 552
#define MGK_XServerFatalErrorUnableToCreateXImage 553
#define MGK_XServerFatalErrorUnableToCreateXPixmap 554
#define MGK_XServerFatalErrorUnableToCreateXWindow 555
#define MGK_XServerFatalErrorUnableToDisplayImage 556
#define MGK_XServerFatalErrorUnableToDitherImage 557
#define MGK_XServerFatalErrorUnableToGetPixelInfo 558
#define MGK_XServerFatalErrorUnableToGetVisual 559
#define MGK_XServerFatalErrorUnableToLoadFont 560
#define MGK_XServerFatalErrorUnableToMakeXWindow 561
#define MGK_XServerFatalErrorUnableToOpenXServer 562
#define MGK_XServerFatalErrorUnableToViewFonts 563
#define MGK_XServerWarningUnableToGetVisual 564
#define MGK_XServerWarningUsingDefaultVisual 565

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
    { "Corrupt/Image/FatalError", 159, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 160, CorruptImageWarning },
    { "Delegate/Error", 171, DelegateError },
    { "Delegate/FatalError", 189, DelegateFatalError },
    { "Delegate/Warning", 190, DelegateWarning },
    { "Draw/Error", 191, DrawError },
    { "Draw/FatalError", 203, DrawFatalError },
    { "Draw/Warning", 204, DrawWarning },
    { "File/Open/Error", 207, FileOpenError },
    { "File/Open/FatalError", 210, FileOpenFatalError },
    { "File/Open/Warning", 211, FileOpenWarning },
    { "Image/Error", 212, ImageError },
    { "Image/FatalError", 247, ImageFatalError },
    { "Image/Warning", 248, ImageWarning },
    { "Missing/Delegate/Error", 249, MissingDelegateError },
    { "Missing/Delegate/FatalError", 261, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 262, MissingDelegateWarning },
    { "Module/Error", 263, ModuleError },
    { "Module/FatalError", 268, ModuleFatalError },
    { "Module/Warning", 269, ModuleWarning },
    { "Monitor/Error", 270, MonitorError },
    { "Monitor/FatalError", 271, MonitorFatalError },
    { "Monitor/Warning", 273, MonitorWarning },
    { "Option/Error", 274, OptionError },
    { "Option/FatalError", 360, OptionFatalError },
    { "Option/Warning", 382, OptionWarning },
    { "Registry/Error", 383, RegistryError },
    { "Registry/FatalError", 389, RegistryFatalError },
    { "Registry/Warning", 390, RegistryWarning },
    { "Resource/Limit/Error", 391, ResourceLimitError },
    { "Resource/Limit/FatalError", 461, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 505, ResourceLimitWarning },
    { "Stream/Error", 506, StreamError },
    { "Stream/FatalError", 512, StreamFatalError },
    { "Stream/Warning", 513, StreamWarning },
    { "Type/Error", 514, TypeError },
    { "Type/FatalError", 519, TypeFatalError },
    { "Type/Warning", 520, TypeWarning },
    { "Wand/Error", 521, WandError },
    { "XServer/Error", 525, XServerError },
    { "XServer/FatalError", 547, XServerFatalError },
    { "XServer/Warning", 563, XServerWarning },
    { 0, 565, UndefinedException }
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
    { "ImageFileHasNoScenes", 124 },
    { "ImageTypeNotSupported", 125 },
    { "ImproperImageHeader", 126 },
    { "InsufficientImageDataInFile", 127 },
    { "InvalidColormapIndex", 128 },
    { "InvalidFileFormatVersion", 129 },
    { "LengthAndFilesizeDoNotMatch", 130 },
    { "MissingImageChannel", 131 },
    { "NegativeOrZeroImageSize", 132 },
    { "NonOS2HeaderSizeError", 133 },
    { "NotEnoughTiles", 134 },
    { "StaticPlanesValueNotEqualToOne", 135 },
    { "SubsamplingRequiresEvenWidth", 136 },
    { "TooMuchImageDataInFile", 137 },
    { "UnableToReadColormapFromDumpFile", 138 },
    { "UnableToReadColorProfile", 139 },
    { "UnableToReadExtensionBlock", 140 },
    { "UnableToReadGenericProfile", 141 },
    { "UnableToReadImageData", 142 },
    { "UnableToReadImageHeader", 143 },
    { "UnableToReadIPTCProfile", 144 },
    { "UnableToReadPixmapFromDumpFile", 145 },
    { "UnableToReadSubImageData", 146 },
    { "UnableToReadVIDImage", 147 },
    { "UnableToReadWindowNameFromDumpFile", 148 },
    { "UnableToRunlengthDecodeImage", 149 },
    { "UnableToUncompressImage", 150 },
    { "UnexpectedEndOfFile", 151 },
    { "UnexpectedSamplingFactor", 152 },
    { "UnknownPatternType", 153 },
    { "UnrecognizedBitsPerPixel", 154 },
    { "UnrecognizedImageCompression", 155 },
    { "UnrecognizedNumberOfColors", 156 },
    { "UnrecognizedXWDHeader", 157 },
    { "UnsupportedBitsPerSample", 158 },
    { "UnsupportedNumberOfPlanes", 159 },
    { "UnableToPersistKey", 160 },
    { "CompressionNotValid", 161 },
    { "CorruptImage", 162 },
    { "ImproperImageHeader", 163 },
    { "InvalidColormapIndex", 164 },
    { "LengthAndFilesizeDoNotMatch", 165 },
    { "NegativeOrZeroImageSize", 166 },
    { "NonOS2HeaderSizeError", 167 },
    { "SkipToSyncByte", 168 },
    { "StaticPlanesValueNotEqualToOne", 169 },
    { "UnrecognizedBitsPerPixel", 170 },
    { "UnrecognizedImageCompression", 171 },
    { "DelegateFailed", 172 },
    { "FailedToAllocateArgumentList", 173 },
    { "FailedToAllocateGhostscriptInterpreter", 174 },
    { "FailedToComputeOutputSize", 175 },
    { "FailedToFindGhostscript", 176 },
    { "FailedToRenderFile", 177 },
    { "FailedToScanFile", 178 },
    { "NoTagFound", 179 },
    { "PostscriptDelegateFailed", 180 },
    { "UnableToCreateImage", 181 },
    { "UnableToCreateImageComponent", 182 },
    { "UnableToDecodeImageFile", 183 },
    { "UnableToEncodeImageFile", 184 },
    { "UnableToInitializeFPXLibrary", 185 },
    { "UnableToInitializeWMFLibrary", 186 },
    { "UnableToManageJP2Stream", 187 },
    { "UnableToWriteSVGFormat", 188 },
    { "WebPABIMismatch", 189 },
    { "Default", 190 },
    { "Default", 191 },
    { "AlreadyPushingPatternDefinition", 192 },
    { "DrawingRecursionDetected", 193 },
    { "FloatValueConversionError", 194 },
    { "IntegerValueConversionError", 195 },
    { "InvalidPrimitiveArgument", 196 },
    { "NonconformingDrawingPrimitiveDefinition", 197 },
    { "PrimitiveArithmeticOverflow", 198 },
    { "TooManyCoordinates", 199 },
    { "UnableToPrint", 200 },
    { "UnbalancedGraphicContextPushPop", 201 },
    { "UnreasonableGradientSize", 202 },
    { "VectorPathTruncated", 203 },
    { "Default", 204 },
    { "NotARelativeURL", 205 },
    { "NotCurrentlyPushingPatternDefinition", 206 },
    { "URLNotFound", 207 },
    { "UnableToCreateTemporaryFile", 208 },
    { "UnableToOpenFile", 209 },
    { "UnableToWriteFile", 210 },
    { "Default", 211 },
    { "Default", 212 },
    { "AngleIsDiscontinuous", 213 },
    { "CMYKAImageLacksAlphaChannel", 214 },
    { "ColorspaceColorProfileMismatch", 215 },
    { "ImageColorspaceDiffers", 216 },
    { "ImageColorspaceMismatch", 217 },
    { "ImageDifferenceExceedsLimit", 218 },
    { "ImageDoesNotContainResolution", 219 },
    { "ImageIsNotColormapped", 220 },
    { "ImageOpacityDiffers", 221 },
    { "ImageSequenceIsRequired", 222 },
    { "ImageSizeDiffers", 223 },
    { "InvalidColormapIndex", 224 },
    { "LeftAndRightImageSizesDiffer", 225 },
    { "NoImagesWereFound", 226 },
    { "NoImagesWereLoaded", 227 },
    { "NoLocaleImageAttribute", 228 },
    { "TooManyClusters", 229 },
    { "UnableToAppendImage", 230 },
    { "UnableToAssignProfile", 231 },
    { "UnableToAverageImage", 232 },
    { "UnableToCoalesceImage", 233 },
    { "UnableToCompareImages", 234 },
    { "UnableToCreateImageMosaic", 235 },
    { "UnableToCreateStereoImage", 236 },
    { "UnableToDeconstructImageSequence", 237 },
    { "UnableToExportImagePixels", 238 },
    { "UnableToFlattenImage", 239 },
    { "UnableToGetClipMask", 240 },
    { "UnableToHandleImageChannel", 241 },
    { "UnableToImportImagePixels", 242 },
    { "UnableToResizeImage", 243 },
    { "UnableToSegmentImage", 244 },
    { "UnableToSetClipMask", 245 },
    { "UnableToShearImage", 246 },
    { "WidthOrHeightExceedsLimit", 247 },
    { "UnableToPersistKey", 248 },
    { "Default", 249 },
    { "DPSLibraryIsNotAvailable", 250 },
    { "FPXLibraryIsNotAvailable", 251 },
    { "FreeTypeLibraryIsNotAvailable", 252 },
    { "JPEGLibraryIsNotAvailable", 253 },
    { "LCMSLibraryIsNotAvailable", 254 },
    { "LZWEncodingNotEnabled", 255 },
    { "NoDecodeDelegateForThisImageFormat", 256 },
    { "NoEncodeDelegateForThisImageFormat", 257 },
    { "TIFFLibraryIsNotAvailable", 258 },
    { "XMLLibraryIsNotAvailable", 259 },
    { "XWindowLibraryIsNotAvailable", 260 },
    { "ZipLibraryIsNotAvailable", 261 },
    { "Default", 262 },
    { "Default", 263 },
    { "FailedToCloseModule", 264 },
    { "FailedToFindSymbol", 265 },
    { "UnableToLoadModule", 266 },
    { "UnableToRegisterImageFormat", 267 },
    { "UnrecognizedModule", 268 },
    { "UnableToInitializeModuleLoader", 269 },
    { "Default", 270 },
    { "Default", 271 },
    { "Default", 272 },
    { "UserRequestedTerminationBySignal", 273 },
    { "Default", 274 },
    { "BevelWidthIsNegative", 275 },
    { "ColorSeparatedImageRequired", 276 },
    { "FrameIsLessThanImageSize", 277 },
    { "GeometryDimensionsAreZero", 278 },
    { "GeometryDoesNotContainImage", 279 },
    { "HaldClutImageDimensionsInvalid", 280 },
    { "ImagesAreNotTheSameSize", 281 },
    { "ImageSizeMustExceedBevelWidth", 282 },
    { "ImageSmallerThanKernelWidth", 283 },
    { "ImageSmallerThanRadius", 284 },
    { "ImageWidthsOrHeightsDiffer", 285 },
    { "InputImagesAlreadySpecified", 286 },
    { "InvalidSubimageSpecification", 287 },
    { "KernelRadiusIsTooSmall", 288 },
    { "KernelWidthMustBeAnOddNumber", 289 },
    { "MatrixIsNotSquare", 290 },
    { "MatrixOrderOutOfRange", 291 },
    { "MissingAnImageFilename", 292 },
    { "MissingArgument", 293 },
    { "MustSpecifyAnImageName", 294 },
    { "MustSpecifyImageSize", 295 },
    { "NoBlobDefined", 296 },
    { "NoImagesDefined", 297 },
    { "NonzeroWidthAndHeightRequired", 298 },
    { "NoProfileNameWasGiven", 299 },
    { "NullBlobArgument", 300 },
    { "ReferenceImageRequired", 301 },
    { "ReferenceIsNotMyType", 302 },
    { "RegionAreaExceedsLimit", 303 },
    { "RequestDidNotReturnAnImage", 304 },
    { "SteganoImageRequired", 305 },
    { "StereoImageRequired", 306 },
    { "SubimageSpecificationReturnsNoImages", 307 },
    { "TileNotBoundedByImageDimensions", 308 },
    { "UnableToAddOrRemoveProfile", 309 },
    { "UnableToAverageImageSequence", 310 },
    { "UnableToBlurImage", 311 },
    { "UnableToChopImage", 312 },
    { "UnableToColorMatrixImage", 313 },
    { "UnableToConstituteImage", 314 },
    { "UnableToConvolveImage", 315 },
    { "UnableToEdgeImage", 316 },
    { "UnableToEqualizeImage", 317 },
    { "UnableToFilterImage", 318 },
    { "UnableToFormatImageMetadata", 319 },
    { "UnableToFrameImage", 320 },
    { "UnableToOilPaintImage", 321 },
    { "UnableToPaintImage", 322 },
    { "UnableToRaiseImage", 323 },
    { "UnableToSharpenImage", 324 },
    { "UnableToThresholdImage", 325 },
    { "UnableToWaveImage", 326 },
    { "UnrecognizedAttribute", 327 },
    { "UnrecognizedChannelType", 328 },
    { "UnrecognizedColor", 329 },
    { "UnrecognizedColormapType", 330 },
    { "UnrecognizedColorspace", 331 },
    { "UnrecognizedCommand", 332 },
    { "UnrecognizedComposeOperator", 333 },
    { "UnrecognizedDisposeMethod", 334 },
    { "UnrecognizedElement", 335 },
    { "UnrecognizedEndianType", 336 },
    { "UnrecognizedGravityType", 337 },
    { "UnrecognizedHighlightStyle", 338 },
    { "UnrecognizedImageCompression", 339 },
    { "UnrecognizedImageFilter", 340 },
    { "UnrecognizedImageFormat", 341 },
    { "UnrecognizedImageMode", 342 },
    { "UnrecognizedImageType", 343 },
    { "UnrecognizedIntentType", 344 },
    { "UnrecognizedInterlaceType", 345 },
    { "UnrecognizedListType", 346 },
    { "UnrecognizedMetric", 347 },
    { "UnrecognizedModeType", 348 },
    { "UnrecognizedNoiseType", 349 },
    { "UnrecognizedOperator", 350 },
    { "UnrecognizedOption", 351 },
    { "UnrecognizedPerlMagickMethod", 352 },
    { "UnrecognizedPixelMap", 353 },
    { "UnrecognizedPreviewType", 354 },
    { "UnrecognizedResourceType", 355 },
    { "UnrecognizedType", 356 },
    { "UnrecognizedUnitsType", 357 },
    { "UnrecognizedVirtualPixelMethod", 358 },
    { "UnsupportedSamplingFactor", 359 },
    { "UsageError", 360 },
    { "InvalidColorspaceType", 361 },
    { "InvalidEndianType", 362 },
    { "InvalidImageType", 363 },
    { "InvalidInterlaceType", 364 },
    { "MissingAnImageFilename", 365 },
    { "MissingArgument", 366 },
    { "NoImagesWereLoaded", 367 },
    { "OptionLengthExceedsLimit", 368 },
    { "RequestDidNotReturnAnImage", 369 },
    { "UnableToOpenXServer", 370 },
    { "UnableToPersistKey", 371 },
    { "UnrecognizedColormapType", 372 },
    { "UnrecognizedColorspaceType", 373 },
    { "UnrecognizedDisposeMethod", 374 },
    { "UnrecognizedEndianType", 375 },
    { "UnrecognizedFilterType", 376 },
    { "UnrecognizedImageCompressionType", 377 },
    { "UnrecognizedImageType", 378 },
    { "UnrecognizedInterlaceType", 379 },
    { "UnrecognizedOption", 380 },
    { "UnrecognizedResourceType", 381 },
    { "UnrecognizedVirtualPixelMethod", 382 },
    { "UnrecognizedColor", 383 },
    { "ImageExpected", 384 },
    { "ImageInfoExpected", 385 },
    { "StructureSizeMismatch", 386 },
    { "UnableToGetRegistryID", 387 },
    { "UnableToLocateImage", 388 },
    { "UnableToSetRegistry", 389 },
    { "Default", 390 },
    { "Default", 391 },
    { "CacheResourcesExhausted", 392 },
    { "ImagePixelHeightLimitExceeded", 393 },
    { "ImagePixelLimitExceeded", 394 },
    { "ImagePixelWidthLimitExceeded", 395 },
    { "MemoryAllocationFailed", 396 },
    { "NoPixelsDefinedInCache", 397 },
    { "PixelCacheAllocationFailed", 398 },
    { "UnableToAddColorProfile", 399 },
    { "UnableToAddGenericProfile", 400 },
    { "UnableToAddIPTCProfile", 401 },
    { "UnableToAddOrRemoveProfile", 402 },
    { "UnableToAllocateCoefficients", 403 },
    { "UnableToAllocateColormap", 404 },
    { "UnableToAllocateICCProfile", 405 },
    { "UnableToAllocateImage", 406 },
    { "UnableToAllocateString", 407 },
    { "UnableToAnnotateImage", 408 },
    { "UnableToAverageImageSequence", 409 },
    { "UnableToCloneDrawingWand", 410 },
    { "UnableToCloneImage", 411 },
    { "UnableToComputeImageSignature", 412 },
    { "UnableToConstituteImage", 413 },
    { "UnableToConvertFont", 414 },
    { "UnableToConvertStringToTokens", 415 },
    { "UnableToCreateColormap", 416 },
    { "UnableToCreateColorTransform", 417 },
    { "UnableToCreateCommandWidget", 418 },
    { "UnableToCreateImageGroup", 419 },
    { "UnableToCreateImageMontage", 420 },
    { "UnableToCreateXWindow", 421 },
    { "UnableToCropImage", 422 },
    { "UnableToDespeckleImage", 423 },
    { "UnableToDetermineImageClass", 424 },
    { "UnableToDetermineTheNumberOfImageColors", 425 },
    { "UnableToDitherImage", 426 },
    { "UnableToDrawOnImage", 427 },
    { "UnableToEdgeImage", 428 },
    { "UnableToEmbossImage", 429 },
    { "UnableToEnhanceImage", 430 },
    { "UnableToFloodfillImage", 431 },
    { "UnableToGammaCorrectImage", 432 },
    { "UnableToGetBestIconSize", 433 },
    { "UnableToGetFromRegistry", 434 },
    { "UnableToGetPackageInfo", 435 },
    { "UnableToLevelImage", 436 },
    { "UnableToMagnifyImage", 437 },
    { "UnableToManageColor", 438 },
    { "UnableToMapImage", 439 },
    { "UnableToMapImageSequence", 440 },
    { "UnableToMedianFilterImage", 441 },
    { "UnableToMotionBlurImage", 442 },
    { "UnableToNoiseFilterImage", 443 },
    { "UnableToNormalizeImage", 444 },
    { "UnableToOpenColorProfile", 445 },
    { "UnableToQuantizeImage", 446 },
    { "UnableToQuantizeImageSequence", 447 },
    { "UnableToReadTextChunk", 448 },
    { "UnableToReadXImage", 449 },
    { "UnableToReadXServerColormap", 450 },
    { "UnableToResizeImage", 451 },
    { "UnableToRotateImage", 452 },
    { "UnableToSampleImage", 453 },
    { "UnableToScaleImage", 454 },
    { "UnableToSelectImage", 455 },
    { "UnableToSharpenImage", 456 },
    { "UnableToShaveImage", 457 },
    { "UnableToShearImage", 458 },
    { "UnableToSortImageColormap", 459 },
    { "UnableToThresholdImage", 460 },
    { "UnableToTransformColorspace", 461 },
    { "MemoryAllocationFailed", 462 },
    { "SemaporeOperationFailed", 463 },
    { "UnableToAllocateAscii85Info", 464 },
    { "UnableToAllocateCacheInfo", 465 },
    { "UnableToAllocateCacheView", 466 },
    { "UnableToAllocateColorInfo", 467 },
    { "UnableToAllocateDashPattern", 468 },
    { "UnableToAllocateDelegateInfo", 469 },
    { "UnableToAllocateDerivatives", 470 },
    { "UnableToAllocateDrawContext", 471 },
    { "UnableToAllocateDrawInfo", 472 },
    { "UnableToAllocateDrawingWand", 473 },
    { "UnableToAllocateGammaMap", 474 },
    { "UnableToAllocateImage", 475 },
    { "UnableToAllocateImagePixels", 476 },
    { "UnableToAllocateLogInfo", 477 },
    { "UnableToAllocateMagicInfo", 478 },
    { "UnableToAllocateMagickInfo", 479 },
    { "UnableToAllocateMagickMap", 480 },
    { "UnableToAllocateModuleInfo", 481 },
    { "UnableToAllocateMontageInfo", 482 },
    { "UnableToAllocateQuantizeInfo", 483 },
    { "UnableToAllocateRandomKernel", 484 },
    { "UnableToAllocateRegistryInfo", 485 },
    { "UnableToAllocateSemaphoreInfo", 486 },
    { "UnableToAllocateString", 487 },
    { "UnableToAllocateTypeInfo", 488 },
    { "UnableToAllocateWand", 489 },
    { "UnableToAnimateImageSequence", 490 },
    { "UnableToCloneBlobInfo", 491 },
    { "UnableToCloneCacheInfo", 492 },
    { "UnableToCloneImage", 493 },
    { "UnableToCloneImageInfo", 494 },
    { "UnableToConcatenateString", 495 },
    { "UnableToConvertText", 496 },
    { "UnableToCreateColormap", 497 },
    { "UnableToDestroySemaphore", 498 },
    { "UnableToDisplayImage", 499 },
    { "UnableToEscapeString", 500 },
    { "UnableToInitializeSemaphore", 501 },
    { "UnableToInterpretMSLImage", 502 },
    { "UnableToLockSemaphore", 503 },
    { "UnableToObtainRandomEntropy", 504 },
    { "UnableToUnlockSemaphore", 505 },
    { "MemoryAllocationFailed", 506 },
    { "ImageDoesNotContainTheStreamGeometry", 507 },
    { "NoStreamHandlerIsDefined", 508 },
    { "PixelCacheIsNotOpen", 509 },
    { "UnableToAcquirePixelStream", 510 },
    { "UnableToSetPixelStream", 511 },
    { "UnableToSyncPixelStream", 512 },
    { "Default", 513 },
    { "Default", 514 },
    { "FontSubstitutionRequired", 515 },
    { "UnableToGetTypeMetrics", 516 },
    { "UnableToInitializeFreetypeLibrary", 517 },
    { "UnableToReadFont", 518 },
    { "UnrecognizedFontEncoding", 519 },
    { "Default", 520 },
    { "Default", 521 },
    { "InvalidColormapIndex", 522 },
    { "WandAPINotImplemented", 523 },
    { "WandContainsNoImageIndexs", 524 },
    { "WandContainsNoImages", 525 },
    { "ColorIsNotKnownToServer", 526 },
    { "NoWindowWithSpecifiedIDExists", 527 },
    { "StandardColormapIsNotInitialized", 528 },
    { "UnableToConnectToRemoteDisplay", 529 },
    { "UnableToCreateBitmap", 530 },
    { "UnableToCreateColormap", 531 },
    { "UnableToCreatePixmap", 532 },
    { "UnableToCreateProperty", 533 },
    { "UnableToCreateStandardColormap", 534 },
    { "UnableToDisplayImageInfo", 535 },
    { "UnableToGetProperty", 536 },
    { "UnableToGetStandardColormap", 537 },
    { "UnableToGetVisual", 538 },
    { "UnableToGrabMouse", 539 },
    { "UnableToLoadFont", 540 },
    { "UnableToMatchVisualToStandardColormap", 541 },
    { "UnableToOpenXServer", 542 },
    { "UnableToReadXAttributes", 543 },
    { "UnableToReadXWindowImage", 544 },
    { "UnrecognizedColormapType", 545 },
    { "UnrecognizedGravityType", 546 },
    { "UnrecognizedVisualSpecifier", 547 },
    { "UnableToAllocateXHints", 548 },
    { "UnableToCreateCursor", 549 },
    { "UnableToCreateGraphicContext", 550 },
    { "UnableToCreateStandardColormap", 551 },
    { "UnableToCreateTextProperty", 552 },
    { "UnableToCreateXImage", 553 },
    { "UnableToCreateXPixmap", 554 },
    { "UnableToCreateXWindow", 555 },
    { "UnableToDisplayImage", 556 },
    { "UnableToDitherImage", 557 },
    { "UnableToGetPixelInfo", 558 },
    { "UnableToGetVisual", 559 },
    { "UnableToLoadFont", 560 },
    { "UnableToMakeXWindow", 561 },
    { "UnableToOpenXServer", 562 },
    { "UnableToViewFonts", 563 },
    { "UnableToGetVisual", 564 },
    { "UsingDefaultVisual", 565 },
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

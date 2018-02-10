#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int);

#define MAX_LOCALE_MSGS 567

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
#define MGK_CoderErrorArithmeticOverflow 25
#define MGK_CoderErrorColormapTooLarge 26
#define MGK_CoderErrorColormapTypeNotSupported 27
#define MGK_CoderErrorColorspaceModelIsNotSupported 28
#define MGK_CoderErrorColorTypeNotSupported 29
#define MGK_CoderErrorCompressionNotValid 30
#define MGK_CoderErrorDataEncodingSchemeIsNotSupported 31
#define MGK_CoderErrorDataStorageTypeIsNotSupported 32
#define MGK_CoderErrorDeltaPNGNotSupported 33
#define MGK_CoderErrorDivisionByZero 34
#define MGK_CoderErrorEncryptedWPGImageFileNotSupported 35
#define MGK_CoderErrorFractalCompressionNotSupported 36
#define MGK_CoderErrorImageColumnOrRowSizeIsNotSupported 37
#define MGK_CoderErrorImageDoesNotHaveAMatteChannel 38
#define MGK_CoderErrorImageIsNotTiled 39
#define MGK_CoderErrorImageTypeNotSupported 40
#define MGK_CoderErrorIncompatibleSizeOfDouble 41
#define MGK_CoderErrorIrregularChannelGeometryNotSupported 42
#define MGK_CoderErrorJNGCompressionNotSupported 43
#define MGK_CoderErrorJPEGCompressionNotSupported 44
#define MGK_CoderErrorJPEGEmbeddingFailed 45
#define MGK_CoderErrorLocationTypeIsNotSupported 46
#define MGK_CoderErrorMapStorageTypeIsNotSupported 47
#define MGK_CoderErrorMSBByteOrderNotSupported 48
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 49
#define MGK_CoderErrorMultipleRecordListNotSupported 50
#define MGK_CoderErrorNo8BIMDataIsAvailable 51
#define MGK_CoderErrorNoAPP1DataIsAvailable 52
#define MGK_CoderErrorNoBitmapOnClipboard 53
#define MGK_CoderErrorNoColorProfileAvailable 54
#define MGK_CoderErrorNoDataReturned 55
#define MGK_CoderErrorNoImageVectorGraphics 56
#define MGK_CoderErrorNoIPTCInfoWasFound 57
#define MGK_CoderErrorNoIPTCProfileAvailable 58
#define MGK_CoderErrorNumberOfImagesIsNotSupported 59
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 60
#define MGK_CoderErrorOnlyLevelZerofilesSupported 61
#define MGK_CoderErrorPNGCompressionNotSupported 62
#define MGK_CoderErrorPNGLibraryTooOld 63
#define MGK_CoderErrorRLECompressionNotSupported 64
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 65
#define MGK_CoderErrorUnableToCopyProfile 66
#define MGK_CoderErrorUnableToCreateADC 67
#define MGK_CoderErrorUnableToCreateBitmap 68
#define MGK_CoderErrorUnableToDecompressImage 69
#define MGK_CoderErrorUnableToInitializeFPXLibrary 70
#define MGK_CoderErrorUnableToOpenBlob 71
#define MGK_CoderErrorUnableToReadAspectRatio 72
#define MGK_CoderErrorUnableToReadCIELABImages 73
#define MGK_CoderErrorUnableToReadSummaryInfo 74
#define MGK_CoderErrorUnableToSetAffineMatrix 75
#define MGK_CoderErrorUnableToSetAspectRatio 76
#define MGK_CoderErrorUnableToSetColorTwist 77
#define MGK_CoderErrorUnableToSetContrast 78
#define MGK_CoderErrorUnableToSetFilteringValue 79
#define MGK_CoderErrorUnableToSetImageComments 80
#define MGK_CoderErrorUnableToSetImageTitle 81
#define MGK_CoderErrorUnableToSetJPEGLevel 82
#define MGK_CoderErrorUnableToSetRegionOfInterest 83
#define MGK_CoderErrorUnableToSetSummaryInfo 84
#define MGK_CoderErrorUnableToTranslateText 85
#define MGK_CoderErrorUnableToWriteMPEGParameters 86
#define MGK_CoderErrorUnableToWriteTemporaryFile 87
#define MGK_CoderErrorUnableToZipCompressImage 88
#define MGK_CoderErrorUnsupportedBitsPerSample 89
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 90
#define MGK_CoderErrorWebPDecodingFailedUserAbort 91
#define MGK_CoderErrorWebPEncodingFailed 92
#define MGK_CoderErrorWebPEncodingFailedBadDimension 93
#define MGK_CoderErrorWebPEncodingFailedBadWrite 94
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 95
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 96
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 97
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 98
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 99
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 100
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 101
#define MGK_CoderErrorWebPEncodingFailedUserAbort 102
#define MGK_CoderErrorWebPInvalidConfiguration 103
#define MGK_CoderErrorWebPInvalidParameter 104
#define MGK_CoderErrorZipCompressionNotSupported 105
#define MGK_CoderFatalErrorDefault 106
#define MGK_CoderWarningLosslessToLossyJPEGConversion 107
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 108
#define MGK_ConfigureErrorRegistryKeyLookupFailed 109
#define MGK_ConfigureErrorStringTokenLengthExceeded 110
#define MGK_ConfigureErrorUnableToAccessConfigureFile 111
#define MGK_ConfigureErrorUnableToAccessFontFile 112
#define MGK_ConfigureErrorUnableToAccessLogFile 113
#define MGK_ConfigureErrorUnableToAccessModuleFile 114
#define MGK_ConfigureFatalErrorDefault 115
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 116
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 117
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 118
#define MGK_ConfigureWarningDefault 119
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 120
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 121
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 122
#define MGK_CorruptImageErrorCompressionNotValid 123
#define MGK_CorruptImageErrorCorruptImage 124
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 125
#define MGK_CorruptImageErrorImageFileHasNoScenes 126
#define MGK_CorruptImageErrorImageTypeNotSupported 127
#define MGK_CorruptImageErrorImproperImageHeader 128
#define MGK_CorruptImageErrorInsufficientImageDataInFile 129
#define MGK_CorruptImageErrorInvalidColormapIndex 130
#define MGK_CorruptImageErrorInvalidFileFormatVersion 131
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 132
#define MGK_CorruptImageErrorMissingImageChannel 133
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 134
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 135
#define MGK_CorruptImageErrorNotEnoughTiles 136
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 137
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 138
#define MGK_CorruptImageErrorTooMuchImageDataInFile 139
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 140
#define MGK_CorruptImageErrorUnableToReadColorProfile 141
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 142
#define MGK_CorruptImageErrorUnableToReadGenericProfile 143
#define MGK_CorruptImageErrorUnableToReadImageData 144
#define MGK_CorruptImageErrorUnableToReadImageHeader 145
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 146
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 147
#define MGK_CorruptImageErrorUnableToReadSubImageData 148
#define MGK_CorruptImageErrorUnableToReadVIDImage 149
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 150
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 151
#define MGK_CorruptImageErrorUnableToUncompressImage 152
#define MGK_CorruptImageErrorUnexpectedEndOfFile 153
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 154
#define MGK_CorruptImageErrorUnknownPatternType 155
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 156
#define MGK_CorruptImageErrorUnrecognizedImageCompression 157
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 158
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 159
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 160
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 161
#define MGK_CorruptImageFatalErrorUnableToPersistKey 162
#define MGK_CorruptImageWarningCompressionNotValid 163
#define MGK_CorruptImageWarningCorruptImage 164
#define MGK_CorruptImageWarningImproperImageHeader 165
#define MGK_CorruptImageWarningInvalidColormapIndex 166
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 167
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 168
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 169
#define MGK_CorruptImageWarningSkipToSyncByte 170
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 171
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 172
#define MGK_CorruptImageWarningUnrecognizedImageCompression 173
#define MGK_DelegateErrorDelegateFailed 174
#define MGK_DelegateErrorFailedToAllocateArgumentList 175
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 176
#define MGK_DelegateErrorFailedToComputeOutputSize 177
#define MGK_DelegateErrorFailedToFindGhostscript 178
#define MGK_DelegateErrorFailedToRenderFile 179
#define MGK_DelegateErrorFailedToScanFile 180
#define MGK_DelegateErrorNoTagFound 181
#define MGK_DelegateErrorPostscriptDelegateFailed 182
#define MGK_DelegateErrorUnableToCreateImage 183
#define MGK_DelegateErrorUnableToCreateImageComponent 184
#define MGK_DelegateErrorUnableToDecodeImageFile 185
#define MGK_DelegateErrorUnableToEncodeImageFile 186
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 187
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 188
#define MGK_DelegateErrorUnableToManageJP2Stream 189
#define MGK_DelegateErrorUnableToWriteSVGFormat 190
#define MGK_DelegateErrorWebPABIMismatch 191
#define MGK_DelegateFatalErrorDefault 192
#define MGK_DelegateWarningDefault 193
#define MGK_DrawErrorAlreadyPushingPatternDefinition 194
#define MGK_DrawErrorDrawingRecursionDetected 195
#define MGK_DrawErrorFloatValueConversionError 196
#define MGK_DrawErrorIntegerValueConversionError 197
#define MGK_DrawErrorInvalidPrimitiveArgument 198
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 199
#define MGK_DrawErrorPrimitiveArithmeticOverflow 200
#define MGK_DrawErrorTooManyCoordinates 201
#define MGK_DrawErrorUnableToPrint 202
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 203
#define MGK_DrawErrorUnreasonableGradientSize 204
#define MGK_DrawErrorVectorPathTruncated 205
#define MGK_DrawFatalErrorDefault 206
#define MGK_DrawWarningNotARelativeURL 207
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 208
#define MGK_DrawWarningURLNotFound 209
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 210
#define MGK_FileOpenErrorUnableToOpenFile 211
#define MGK_FileOpenErrorUnableToWriteFile 212
#define MGK_FileOpenFatalErrorDefault 213
#define MGK_FileOpenWarningDefault 214
#define MGK_ImageErrorAngleIsDiscontinuous 215
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 216
#define MGK_ImageErrorColorspaceColorProfileMismatch 217
#define MGK_ImageErrorImageColorspaceDiffers 218
#define MGK_ImageErrorImageColorspaceMismatch 219
#define MGK_ImageErrorImageDifferenceExceedsLimit 220
#define MGK_ImageErrorImageDoesNotContainResolution 221
#define MGK_ImageErrorImageIsNotColormapped 222
#define MGK_ImageErrorImageOpacityDiffers 223
#define MGK_ImageErrorImageSequenceIsRequired 224
#define MGK_ImageErrorImageSizeDiffers 225
#define MGK_ImageErrorInvalidColormapIndex 226
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 227
#define MGK_ImageErrorNoImagesWereFound 228
#define MGK_ImageErrorNoImagesWereLoaded 229
#define MGK_ImageErrorNoLocaleImageAttribute 230
#define MGK_ImageErrorTooManyClusters 231
#define MGK_ImageErrorUnableToAppendImage 232
#define MGK_ImageErrorUnableToAssignProfile 233
#define MGK_ImageErrorUnableToAverageImage 234
#define MGK_ImageErrorUnableToCoalesceImage 235
#define MGK_ImageErrorUnableToCompareImages 236
#define MGK_ImageErrorUnableToCreateImageMosaic 237
#define MGK_ImageErrorUnableToCreateStereoImage 238
#define MGK_ImageErrorUnableToDeconstructImageSequence 239
#define MGK_ImageErrorUnableToExportImagePixels 240
#define MGK_ImageErrorUnableToFlattenImage 241
#define MGK_ImageErrorUnableToGetClipMask 242
#define MGK_ImageErrorUnableToHandleImageChannel 243
#define MGK_ImageErrorUnableToImportImagePixels 244
#define MGK_ImageErrorUnableToResizeImage 245
#define MGK_ImageErrorUnableToSegmentImage 246
#define MGK_ImageErrorUnableToSetClipMask 247
#define MGK_ImageErrorUnableToShearImage 248
#define MGK_ImageErrorWidthOrHeightExceedsLimit 249
#define MGK_ImageFatalErrorUnableToPersistKey 250
#define MGK_ImageWarningDefault 251
#define MGK_MissingDelegateErrorDPSLibraryIsNotAvailable 252
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 253
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 254
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 255
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 256
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 257
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 258
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 259
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 260
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 261
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 262
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 263
#define MGK_MissingDelegateFatalErrorDefault 264
#define MGK_MissingDelegateWarningDefault 265
#define MGK_ModuleErrorFailedToCloseModule 266
#define MGK_ModuleErrorFailedToFindSymbol 267
#define MGK_ModuleErrorUnableToLoadModule 268
#define MGK_ModuleErrorUnableToRegisterImageFormat 269
#define MGK_ModuleErrorUnrecognizedModule 270
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 271
#define MGK_ModuleWarningDefault 272
#define MGK_MonitorErrorDefault 273
#define MGK_MonitorFatalErrorDefault 274
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 275
#define MGK_MonitorWarningDefault 276
#define MGK_OptionErrorBevelWidthIsNegative 277
#define MGK_OptionErrorColorSeparatedImageRequired 278
#define MGK_OptionErrorFrameIsLessThanImageSize 279
#define MGK_OptionErrorGeometryDimensionsAreZero 280
#define MGK_OptionErrorGeometryDoesNotContainImage 281
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 282
#define MGK_OptionErrorImagesAreNotTheSameSize 283
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 284
#define MGK_OptionErrorImageSmallerThanKernelWidth 285
#define MGK_OptionErrorImageSmallerThanRadius 286
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 287
#define MGK_OptionErrorInputImagesAlreadySpecified 288
#define MGK_OptionErrorInvalidSubimageSpecification 289
#define MGK_OptionErrorKernelRadiusIsTooSmall 290
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 291
#define MGK_OptionErrorMatrixIsNotSquare 292
#define MGK_OptionErrorMatrixOrderOutOfRange 293
#define MGK_OptionErrorMissingAnImageFilename 294
#define MGK_OptionErrorMissingArgument 295
#define MGK_OptionErrorMustSpecifyAnImageName 296
#define MGK_OptionErrorMustSpecifyImageSize 297
#define MGK_OptionErrorNoBlobDefined 298
#define MGK_OptionErrorNoImagesDefined 299
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 300
#define MGK_OptionErrorNoProfileNameWasGiven 301
#define MGK_OptionErrorNullBlobArgument 302
#define MGK_OptionErrorReferenceImageRequired 303
#define MGK_OptionErrorReferenceIsNotMyType 304
#define MGK_OptionErrorRegionAreaExceedsLimit 305
#define MGK_OptionErrorRequestDidNotReturnAnImage 306
#define MGK_OptionErrorSteganoImageRequired 307
#define MGK_OptionErrorStereoImageRequired 308
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 309
#define MGK_OptionErrorTileNotBoundedByImageDimensions 310
#define MGK_OptionErrorUnableToAddOrRemoveProfile 311
#define MGK_OptionErrorUnableToAverageImageSequence 312
#define MGK_OptionErrorUnableToBlurImage 313
#define MGK_OptionErrorUnableToChopImage 314
#define MGK_OptionErrorUnableToColorMatrixImage 315
#define MGK_OptionErrorUnableToConstituteImage 316
#define MGK_OptionErrorUnableToConvolveImage 317
#define MGK_OptionErrorUnableToEdgeImage 318
#define MGK_OptionErrorUnableToEqualizeImage 319
#define MGK_OptionErrorUnableToFilterImage 320
#define MGK_OptionErrorUnableToFormatImageMetadata 321
#define MGK_OptionErrorUnableToFrameImage 322
#define MGK_OptionErrorUnableToOilPaintImage 323
#define MGK_OptionErrorUnableToPaintImage 324
#define MGK_OptionErrorUnableToRaiseImage 325
#define MGK_OptionErrorUnableToSharpenImage 326
#define MGK_OptionErrorUnableToThresholdImage 327
#define MGK_OptionErrorUnableToWaveImage 328
#define MGK_OptionErrorUnrecognizedAttribute 329
#define MGK_OptionErrorUnrecognizedChannelType 330
#define MGK_OptionErrorUnrecognizedColor 331
#define MGK_OptionErrorUnrecognizedColormapType 332
#define MGK_OptionErrorUnrecognizedColorspace 333
#define MGK_OptionErrorUnrecognizedCommand 334
#define MGK_OptionErrorUnrecognizedComposeOperator 335
#define MGK_OptionErrorUnrecognizedDisposeMethod 336
#define MGK_OptionErrorUnrecognizedElement 337
#define MGK_OptionErrorUnrecognizedEndianType 338
#define MGK_OptionErrorUnrecognizedGravityType 339
#define MGK_OptionErrorUnrecognizedHighlightStyle 340
#define MGK_OptionErrorUnrecognizedImageCompression 341
#define MGK_OptionErrorUnrecognizedImageFilter 342
#define MGK_OptionErrorUnrecognizedImageFormat 343
#define MGK_OptionErrorUnrecognizedImageMode 344
#define MGK_OptionErrorUnrecognizedImageType 345
#define MGK_OptionErrorUnrecognizedIntentType 346
#define MGK_OptionErrorUnrecognizedInterlaceType 347
#define MGK_OptionErrorUnrecognizedListType 348
#define MGK_OptionErrorUnrecognizedMetric 349
#define MGK_OptionErrorUnrecognizedModeType 350
#define MGK_OptionErrorUnrecognizedNoiseType 351
#define MGK_OptionErrorUnrecognizedOperator 352
#define MGK_OptionErrorUnrecognizedOption 353
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 354
#define MGK_OptionErrorUnrecognizedPixelMap 355
#define MGK_OptionErrorUnrecognizedPreviewType 356
#define MGK_OptionErrorUnrecognizedResourceType 357
#define MGK_OptionErrorUnrecognizedType 358
#define MGK_OptionErrorUnrecognizedUnitsType 359
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 360
#define MGK_OptionErrorUnsupportedSamplingFactor 361
#define MGK_OptionErrorUsageError 362
#define MGK_OptionFatalErrorInvalidColorspaceType 363
#define MGK_OptionFatalErrorInvalidEndianType 364
#define MGK_OptionFatalErrorInvalidImageType 365
#define MGK_OptionFatalErrorInvalidInterlaceType 366
#define MGK_OptionFatalErrorMissingAnImageFilename 367
#define MGK_OptionFatalErrorMissingArgument 368
#define MGK_OptionFatalErrorNoImagesWereLoaded 369
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 370
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 371
#define MGK_OptionFatalErrorUnableToOpenXServer 372
#define MGK_OptionFatalErrorUnableToPersistKey 373
#define MGK_OptionFatalErrorUnrecognizedColormapType 374
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 375
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 376
#define MGK_OptionFatalErrorUnrecognizedEndianType 377
#define MGK_OptionFatalErrorUnrecognizedFilterType 378
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 379
#define MGK_OptionFatalErrorUnrecognizedImageType 380
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 381
#define MGK_OptionFatalErrorUnrecognizedOption 382
#define MGK_OptionFatalErrorUnrecognizedResourceType 383
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 384
#define MGK_OptionWarningUnrecognizedColor 385
#define MGK_RegistryErrorImageExpected 386
#define MGK_RegistryErrorImageInfoExpected 387
#define MGK_RegistryErrorStructureSizeMismatch 388
#define MGK_RegistryErrorUnableToGetRegistryID 389
#define MGK_RegistryErrorUnableToLocateImage 390
#define MGK_RegistryErrorUnableToSetRegistry 391
#define MGK_RegistryFatalErrorDefault 392
#define MGK_RegistryWarningDefault 393
#define MGK_ResourceLimitErrorCacheResourcesExhausted 394
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 395
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 396
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 397
#define MGK_ResourceLimitErrorMemoryAllocationFailed 398
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 399
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 400
#define MGK_ResourceLimitErrorUnableToAddColorProfile 401
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 402
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 403
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 404
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 405
#define MGK_ResourceLimitErrorUnableToAllocateColormap 406
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 407
#define MGK_ResourceLimitErrorUnableToAllocateImage 408
#define MGK_ResourceLimitErrorUnableToAllocateString 409
#define MGK_ResourceLimitErrorUnableToAnnotateImage 410
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 411
#define MGK_ResourceLimitErrorUnableToCloneDrawingWand 412
#define MGK_ResourceLimitErrorUnableToCloneImage 413
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 414
#define MGK_ResourceLimitErrorUnableToConstituteImage 415
#define MGK_ResourceLimitErrorUnableToConvertFont 416
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 417
#define MGK_ResourceLimitErrorUnableToCreateColormap 418
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 419
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 420
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 421
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 422
#define MGK_ResourceLimitErrorUnableToCreateXWindow 423
#define MGK_ResourceLimitErrorUnableToCropImage 424
#define MGK_ResourceLimitErrorUnableToDespeckleImage 425
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 426
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 427
#define MGK_ResourceLimitErrorUnableToDitherImage 428
#define MGK_ResourceLimitErrorUnableToDrawOnImage 429
#define MGK_ResourceLimitErrorUnableToEdgeImage 430
#define MGK_ResourceLimitErrorUnableToEmbossImage 431
#define MGK_ResourceLimitErrorUnableToEnhanceImage 432
#define MGK_ResourceLimitErrorUnableToFloodfillImage 433
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 434
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 435
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 436
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 437
#define MGK_ResourceLimitErrorUnableToLevelImage 438
#define MGK_ResourceLimitErrorUnableToMagnifyImage 439
#define MGK_ResourceLimitErrorUnableToManageColor 440
#define MGK_ResourceLimitErrorUnableToMapImage 441
#define MGK_ResourceLimitErrorUnableToMapImageSequence 442
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 443
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 444
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 445
#define MGK_ResourceLimitErrorUnableToNormalizeImage 446
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 447
#define MGK_ResourceLimitErrorUnableToQuantizeImage 448
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 449
#define MGK_ResourceLimitErrorUnableToReadTextChunk 450
#define MGK_ResourceLimitErrorUnableToReadXImage 451
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 452
#define MGK_ResourceLimitErrorUnableToResizeImage 453
#define MGK_ResourceLimitErrorUnableToRotateImage 454
#define MGK_ResourceLimitErrorUnableToSampleImage 455
#define MGK_ResourceLimitErrorUnableToScaleImage 456
#define MGK_ResourceLimitErrorUnableToSelectImage 457
#define MGK_ResourceLimitErrorUnableToSharpenImage 458
#define MGK_ResourceLimitErrorUnableToShaveImage 459
#define MGK_ResourceLimitErrorUnableToShearImage 460
#define MGK_ResourceLimitErrorUnableToSortImageColormap 461
#define MGK_ResourceLimitErrorUnableToThresholdImage 462
#define MGK_ResourceLimitErrorUnableToTransformColorspace 463
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 464
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 465
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 466
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 467
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 468
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 469
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 470
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 471
#define MGK_ResourceLimitFatalErrorUnableToAllocateDerivatives 472
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 473
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 474
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 475
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 476
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 477
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 478
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 479
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 480
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 481
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 482
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 483
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 484
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 485
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 486
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 487
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 488
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 489
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 490
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 491
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 492
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 493
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 494
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 495
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 496
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 497
#define MGK_ResourceLimitFatalErrorUnableToConvertText 498
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 499
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 500
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 501
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 502
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 503
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 504
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 505
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 506
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 507
#define MGK_ResourceLimitWarningMemoryAllocationFailed 508
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 509
#define MGK_StreamErrorNoStreamHandlerIsDefined 510
#define MGK_StreamErrorPixelCacheIsNotOpen 511
#define MGK_StreamErrorUnableToAcquirePixelStream 512
#define MGK_StreamErrorUnableToSetPixelStream 513
#define MGK_StreamErrorUnableToSyncPixelStream 514
#define MGK_StreamFatalErrorDefault 515
#define MGK_StreamWarningDefault 516
#define MGK_TypeErrorFontSubstitutionRequired 517
#define MGK_TypeErrorUnableToGetTypeMetrics 518
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 519
#define MGK_TypeErrorUnableToReadFont 520
#define MGK_TypeErrorUnrecognizedFontEncoding 521
#define MGK_TypeFatalErrorDefault 522
#define MGK_TypeWarningDefault 523
#define MGK_WandErrorInvalidColormapIndex 524
#define MGK_WandErrorWandAPINotImplemented 525
#define MGK_WandErrorWandContainsNoImageIndexs 526
#define MGK_WandErrorWandContainsNoImages 527
#define MGK_XServerErrorColorIsNotKnownToServer 528
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 529
#define MGK_XServerErrorStandardColormapIsNotInitialized 530
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 531
#define MGK_XServerErrorUnableToCreateBitmap 532
#define MGK_XServerErrorUnableToCreateColormap 533
#define MGK_XServerErrorUnableToCreatePixmap 534
#define MGK_XServerErrorUnableToCreateProperty 535
#define MGK_XServerErrorUnableToCreateStandardColormap 536
#define MGK_XServerErrorUnableToDisplayImageInfo 537
#define MGK_XServerErrorUnableToGetProperty 538
#define MGK_XServerErrorUnableToGetStandardColormap 539
#define MGK_XServerErrorUnableToGetVisual 540
#define MGK_XServerErrorUnableToGrabMouse 541
#define MGK_XServerErrorUnableToLoadFont 542
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 543
#define MGK_XServerErrorUnableToOpenXServer 544
#define MGK_XServerErrorUnableToReadXAttributes 545
#define MGK_XServerErrorUnableToReadXWindowImage 546
#define MGK_XServerErrorUnrecognizedColormapType 547
#define MGK_XServerErrorUnrecognizedGravityType 548
#define MGK_XServerErrorUnrecognizedVisualSpecifier 549
#define MGK_XServerFatalErrorUnableToAllocateXHints 550
#define MGK_XServerFatalErrorUnableToCreateCursor 551
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 552
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 553
#define MGK_XServerFatalErrorUnableToCreateTextProperty 554
#define MGK_XServerFatalErrorUnableToCreateXImage 555
#define MGK_XServerFatalErrorUnableToCreateXPixmap 556
#define MGK_XServerFatalErrorUnableToCreateXWindow 557
#define MGK_XServerFatalErrorUnableToDisplayImage 558
#define MGK_XServerFatalErrorUnableToDitherImage 559
#define MGK_XServerFatalErrorUnableToGetPixelInfo 560
#define MGK_XServerFatalErrorUnableToGetVisual 561
#define MGK_XServerFatalErrorUnableToLoadFont 562
#define MGK_XServerFatalErrorUnableToMakeXWindow 563
#define MGK_XServerFatalErrorUnableToOpenXServer 564
#define MGK_XServerFatalErrorUnableToViewFonts 565
#define MGK_XServerWarningUnableToGetVisual 566
#define MGK_XServerWarningUsingDefaultVisual 567

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
    { "Coder/FatalError", 105, CoderFatalError },
    { "Coder/Warning", 106, CoderWarning },
    { "Configure/Error", 107, ConfigureError },
    { "Configure/FatalError", 114, ConfigureFatalError },
    { "Configure/Warning", 118, ConfigureWarning },
    { "Corrupt/Image/Error", 119, CorruptImageError },
    { "Corrupt/Image/FatalError", 161, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 162, CorruptImageWarning },
    { "Delegate/Error", 173, DelegateError },
    { "Delegate/FatalError", 191, DelegateFatalError },
    { "Delegate/Warning", 192, DelegateWarning },
    { "Draw/Error", 193, DrawError },
    { "Draw/FatalError", 205, DrawFatalError },
    { "Draw/Warning", 206, DrawWarning },
    { "File/Open/Error", 209, FileOpenError },
    { "File/Open/FatalError", 212, FileOpenFatalError },
    { "File/Open/Warning", 213, FileOpenWarning },
    { "Image/Error", 214, ImageError },
    { "Image/FatalError", 249, ImageFatalError },
    { "Image/Warning", 250, ImageWarning },
    { "Missing/Delegate/Error", 251, MissingDelegateError },
    { "Missing/Delegate/FatalError", 263, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 264, MissingDelegateWarning },
    { "Module/Error", 265, ModuleError },
    { "Module/FatalError", 270, ModuleFatalError },
    { "Module/Warning", 271, ModuleWarning },
    { "Monitor/Error", 272, MonitorError },
    { "Monitor/FatalError", 273, MonitorFatalError },
    { "Monitor/Warning", 275, MonitorWarning },
    { "Option/Error", 276, OptionError },
    { "Option/FatalError", 362, OptionFatalError },
    { "Option/Warning", 384, OptionWarning },
    { "Registry/Error", 385, RegistryError },
    { "Registry/FatalError", 391, RegistryFatalError },
    { "Registry/Warning", 392, RegistryWarning },
    { "Resource/Limit/Error", 393, ResourceLimitError },
    { "Resource/Limit/FatalError", 463, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 507, ResourceLimitWarning },
    { "Stream/Error", 508, StreamError },
    { "Stream/FatalError", 514, StreamFatalError },
    { "Stream/Warning", 515, StreamWarning },
    { "Type/Error", 516, TypeError },
    { "Type/FatalError", 521, TypeFatalError },
    { "Type/Warning", 522, TypeWarning },
    { "Wand/Error", 523, WandError },
    { "XServer/Error", 527, XServerError },
    { "XServer/FatalError", 549, XServerFatalError },
    { "XServer/Warning", 565, XServerWarning },
    { 0, 567, UndefinedException }
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
    { "ArithmeticOverflow", 25 },
    { "ColormapTooLarge", 26 },
    { "ColormapTypeNotSupported", 27 },
    { "ColorspaceModelIsNotSupported", 28 },
    { "ColorTypeNotSupported", 29 },
    { "CompressionNotValid", 30 },
    { "DataEncodingSchemeIsNotSupported", 31 },
    { "DataStorageTypeIsNotSupported", 32 },
    { "DeltaPNGNotSupported", 33 },
    { "DivisionByZero", 34 },
    { "EncryptedWPGImageFileNotSupported", 35 },
    { "FractalCompressionNotSupported", 36 },
    { "ImageColumnOrRowSizeIsNotSupported", 37 },
    { "ImageDoesNotHaveAMatteChannel", 38 },
    { "ImageIsNotTiled", 39 },
    { "ImageTypeNotSupported", 40 },
    { "IncompatibleSizeOfDouble", 41 },
    { "IrregularChannelGeometryNotSupported", 42 },
    { "JNGCompressionNotSupported", 43 },
    { "JPEGCompressionNotSupported", 44 },
    { "JPEGEmbeddingFailed", 45 },
    { "LocationTypeIsNotSupported", 46 },
    { "MapStorageTypeIsNotSupported", 47 },
    { "MSBByteOrderNotSupported", 48 },
    { "MultidimensionalMatricesAreNotSupported", 49 },
    { "MultipleRecordListNotSupported", 50 },
    { "No8BIMDataIsAvailable", 51 },
    { "NoAPP1DataIsAvailable", 52 },
    { "NoBitmapOnClipboard", 53 },
    { "NoColorProfileAvailable", 54 },
    { "NoDataReturned", 55 },
    { "NoImageVectorGraphics", 56 },
    { "NoIPTCInfoWasFound", 57 },
    { "NoIPTCProfileAvailable", 58 },
    { "NumberOfImagesIsNotSupported", 59 },
    { "OnlyContinuousTonePictureSupported", 60 },
    { "OnlyLevelZerofilesSupported", 61 },
    { "PNGCompressionNotSupported", 62 },
    { "PNGLibraryTooOld", 63 },
    { "RLECompressionNotSupported", 64 },
    { "SubsamplingRequiresEvenWidth", 65 },
    { "UnableToCopyProfile", 66 },
    { "UnableToCreateADC", 67 },
    { "UnableToCreateBitmap", 68 },
    { "UnableToDecompressImage", 69 },
    { "UnableToInitializeFPXLibrary", 70 },
    { "UnableToOpenBlob", 71 },
    { "UnableToReadAspectRatio", 72 },
    { "UnableToReadCIELABImages", 73 },
    { "UnableToReadSummaryInfo", 74 },
    { "UnableToSetAffineMatrix", 75 },
    { "UnableToSetAspectRatio", 76 },
    { "UnableToSetColorTwist", 77 },
    { "UnableToSetContrast", 78 },
    { "UnableToSetFilteringValue", 79 },
    { "UnableToSetImageComments", 80 },
    { "UnableToSetImageTitle", 81 },
    { "UnableToSetJPEGLevel", 82 },
    { "UnableToSetRegionOfInterest", 83 },
    { "UnableToSetSummaryInfo", 84 },
    { "UnableToTranslateText", 85 },
    { "UnableToWriteMPEGParameters", 86 },
    { "UnableToWriteTemporaryFile", 87 },
    { "UnableToZipCompressImage", 88 },
    { "UnsupportedBitsPerSample", 89 },
    { "UnsupportedCellTypeInTheMatrix", 90 },
    { "WebPDecodingFailedUserAbort", 91 },
    { "WebPEncodingFailed", 92 },
    { "WebPEncodingFailedBadDimension", 93 },
    { "WebPEncodingFailedBadWrite", 94 },
    { "WebPEncodingFailedBitstreamOutOfMemory", 95 },
    { "WebPEncodingFailedFileTooBig", 96 },
    { "WebPEncodingFailedInvalidConfiguration", 97 },
    { "WebPEncodingFailedNULLParameter", 98 },
    { "WebPEncodingFailedOutOfMemory", 99 },
    { "WebPEncodingFailedPartition0Overflow", 100 },
    { "WebPEncodingFailedPartitionOverflow", 101 },
    { "WebPEncodingFailedUserAbort", 102 },
    { "WebPInvalidConfiguration", 103 },
    { "WebPInvalidParameter", 104 },
    { "ZipCompressionNotSupported", 105 },
    { "Default", 106 },
    { "LosslessToLossyJPEGConversion", 107 },
    { "IncludeElementNestedTooDeeply", 108 },
    { "RegistryKeyLookupFailed", 109 },
    { "StringTokenLengthExceeded", 110 },
    { "UnableToAccessConfigureFile", 111 },
    { "UnableToAccessFontFile", 112 },
    { "UnableToAccessLogFile", 113 },
    { "UnableToAccessModuleFile", 114 },
    { "Default", 115 },
    { "UnableToChangeToWorkingDirectory", 116 },
    { "UnableToGetCurrentDirectory", 117 },
    { "UnableToRestoreCurrentDirectory", 118 },
    { "Default", 119 },
    { "AnErrorHasOccurredReadingFromFile", 120 },
    { "AnErrorHasOccurredWritingToFile", 121 },
    { "ColormapExceedsColorsLimit", 122 },
    { "CompressionNotValid", 123 },
    { "CorruptImage", 124 },
    { "ImageFileDoesNotContainAnyImageData", 125 },
    { "ImageFileHasNoScenes", 126 },
    { "ImageTypeNotSupported", 127 },
    { "ImproperImageHeader", 128 },
    { "InsufficientImageDataInFile", 129 },
    { "InvalidColormapIndex", 130 },
    { "InvalidFileFormatVersion", 131 },
    { "LengthAndFilesizeDoNotMatch", 132 },
    { "MissingImageChannel", 133 },
    { "NegativeOrZeroImageSize", 134 },
    { "NonOS2HeaderSizeError", 135 },
    { "NotEnoughTiles", 136 },
    { "StaticPlanesValueNotEqualToOne", 137 },
    { "SubsamplingRequiresEvenWidth", 138 },
    { "TooMuchImageDataInFile", 139 },
    { "UnableToReadColormapFromDumpFile", 140 },
    { "UnableToReadColorProfile", 141 },
    { "UnableToReadExtensionBlock", 142 },
    { "UnableToReadGenericProfile", 143 },
    { "UnableToReadImageData", 144 },
    { "UnableToReadImageHeader", 145 },
    { "UnableToReadIPTCProfile", 146 },
    { "UnableToReadPixmapFromDumpFile", 147 },
    { "UnableToReadSubImageData", 148 },
    { "UnableToReadVIDImage", 149 },
    { "UnableToReadWindowNameFromDumpFile", 150 },
    { "UnableToRunlengthDecodeImage", 151 },
    { "UnableToUncompressImage", 152 },
    { "UnexpectedEndOfFile", 153 },
    { "UnexpectedSamplingFactor", 154 },
    { "UnknownPatternType", 155 },
    { "UnrecognizedBitsPerPixel", 156 },
    { "UnrecognizedImageCompression", 157 },
    { "UnrecognizedNumberOfColors", 158 },
    { "UnrecognizedXWDHeader", 159 },
    { "UnsupportedBitsPerSample", 160 },
    { "UnsupportedNumberOfPlanes", 161 },
    { "UnableToPersistKey", 162 },
    { "CompressionNotValid", 163 },
    { "CorruptImage", 164 },
    { "ImproperImageHeader", 165 },
    { "InvalidColormapIndex", 166 },
    { "LengthAndFilesizeDoNotMatch", 167 },
    { "NegativeOrZeroImageSize", 168 },
    { "NonOS2HeaderSizeError", 169 },
    { "SkipToSyncByte", 170 },
    { "StaticPlanesValueNotEqualToOne", 171 },
    { "UnrecognizedBitsPerPixel", 172 },
    { "UnrecognizedImageCompression", 173 },
    { "DelegateFailed", 174 },
    { "FailedToAllocateArgumentList", 175 },
    { "FailedToAllocateGhostscriptInterpreter", 176 },
    { "FailedToComputeOutputSize", 177 },
    { "FailedToFindGhostscript", 178 },
    { "FailedToRenderFile", 179 },
    { "FailedToScanFile", 180 },
    { "NoTagFound", 181 },
    { "PostscriptDelegateFailed", 182 },
    { "UnableToCreateImage", 183 },
    { "UnableToCreateImageComponent", 184 },
    { "UnableToDecodeImageFile", 185 },
    { "UnableToEncodeImageFile", 186 },
    { "UnableToInitializeFPXLibrary", 187 },
    { "UnableToInitializeWMFLibrary", 188 },
    { "UnableToManageJP2Stream", 189 },
    { "UnableToWriteSVGFormat", 190 },
    { "WebPABIMismatch", 191 },
    { "Default", 192 },
    { "Default", 193 },
    { "AlreadyPushingPatternDefinition", 194 },
    { "DrawingRecursionDetected", 195 },
    { "FloatValueConversionError", 196 },
    { "IntegerValueConversionError", 197 },
    { "InvalidPrimitiveArgument", 198 },
    { "NonconformingDrawingPrimitiveDefinition", 199 },
    { "PrimitiveArithmeticOverflow", 200 },
    { "TooManyCoordinates", 201 },
    { "UnableToPrint", 202 },
    { "UnbalancedGraphicContextPushPop", 203 },
    { "UnreasonableGradientSize", 204 },
    { "VectorPathTruncated", 205 },
    { "Default", 206 },
    { "NotARelativeURL", 207 },
    { "NotCurrentlyPushingPatternDefinition", 208 },
    { "URLNotFound", 209 },
    { "UnableToCreateTemporaryFile", 210 },
    { "UnableToOpenFile", 211 },
    { "UnableToWriteFile", 212 },
    { "Default", 213 },
    { "Default", 214 },
    { "AngleIsDiscontinuous", 215 },
    { "CMYKAImageLacksAlphaChannel", 216 },
    { "ColorspaceColorProfileMismatch", 217 },
    { "ImageColorspaceDiffers", 218 },
    { "ImageColorspaceMismatch", 219 },
    { "ImageDifferenceExceedsLimit", 220 },
    { "ImageDoesNotContainResolution", 221 },
    { "ImageIsNotColormapped", 222 },
    { "ImageOpacityDiffers", 223 },
    { "ImageSequenceIsRequired", 224 },
    { "ImageSizeDiffers", 225 },
    { "InvalidColormapIndex", 226 },
    { "LeftAndRightImageSizesDiffer", 227 },
    { "NoImagesWereFound", 228 },
    { "NoImagesWereLoaded", 229 },
    { "NoLocaleImageAttribute", 230 },
    { "TooManyClusters", 231 },
    { "UnableToAppendImage", 232 },
    { "UnableToAssignProfile", 233 },
    { "UnableToAverageImage", 234 },
    { "UnableToCoalesceImage", 235 },
    { "UnableToCompareImages", 236 },
    { "UnableToCreateImageMosaic", 237 },
    { "UnableToCreateStereoImage", 238 },
    { "UnableToDeconstructImageSequence", 239 },
    { "UnableToExportImagePixels", 240 },
    { "UnableToFlattenImage", 241 },
    { "UnableToGetClipMask", 242 },
    { "UnableToHandleImageChannel", 243 },
    { "UnableToImportImagePixels", 244 },
    { "UnableToResizeImage", 245 },
    { "UnableToSegmentImage", 246 },
    { "UnableToSetClipMask", 247 },
    { "UnableToShearImage", 248 },
    { "WidthOrHeightExceedsLimit", 249 },
    { "UnableToPersistKey", 250 },
    { "Default", 251 },
    { "DPSLibraryIsNotAvailable", 252 },
    { "FPXLibraryIsNotAvailable", 253 },
    { "FreeTypeLibraryIsNotAvailable", 254 },
    { "JPEGLibraryIsNotAvailable", 255 },
    { "LCMSLibraryIsNotAvailable", 256 },
    { "LZWEncodingNotEnabled", 257 },
    { "NoDecodeDelegateForThisImageFormat", 258 },
    { "NoEncodeDelegateForThisImageFormat", 259 },
    { "TIFFLibraryIsNotAvailable", 260 },
    { "XMLLibraryIsNotAvailable", 261 },
    { "XWindowLibraryIsNotAvailable", 262 },
    { "ZipLibraryIsNotAvailable", 263 },
    { "Default", 264 },
    { "Default", 265 },
    { "FailedToCloseModule", 266 },
    { "FailedToFindSymbol", 267 },
    { "UnableToLoadModule", 268 },
    { "UnableToRegisterImageFormat", 269 },
    { "UnrecognizedModule", 270 },
    { "UnableToInitializeModuleLoader", 271 },
    { "Default", 272 },
    { "Default", 273 },
    { "Default", 274 },
    { "UserRequestedTerminationBySignal", 275 },
    { "Default", 276 },
    { "BevelWidthIsNegative", 277 },
    { "ColorSeparatedImageRequired", 278 },
    { "FrameIsLessThanImageSize", 279 },
    { "GeometryDimensionsAreZero", 280 },
    { "GeometryDoesNotContainImage", 281 },
    { "HaldClutImageDimensionsInvalid", 282 },
    { "ImagesAreNotTheSameSize", 283 },
    { "ImageSizeMustExceedBevelWidth", 284 },
    { "ImageSmallerThanKernelWidth", 285 },
    { "ImageSmallerThanRadius", 286 },
    { "ImageWidthsOrHeightsDiffer", 287 },
    { "InputImagesAlreadySpecified", 288 },
    { "InvalidSubimageSpecification", 289 },
    { "KernelRadiusIsTooSmall", 290 },
    { "KernelWidthMustBeAnOddNumber", 291 },
    { "MatrixIsNotSquare", 292 },
    { "MatrixOrderOutOfRange", 293 },
    { "MissingAnImageFilename", 294 },
    { "MissingArgument", 295 },
    { "MustSpecifyAnImageName", 296 },
    { "MustSpecifyImageSize", 297 },
    { "NoBlobDefined", 298 },
    { "NoImagesDefined", 299 },
    { "NonzeroWidthAndHeightRequired", 300 },
    { "NoProfileNameWasGiven", 301 },
    { "NullBlobArgument", 302 },
    { "ReferenceImageRequired", 303 },
    { "ReferenceIsNotMyType", 304 },
    { "RegionAreaExceedsLimit", 305 },
    { "RequestDidNotReturnAnImage", 306 },
    { "SteganoImageRequired", 307 },
    { "StereoImageRequired", 308 },
    { "SubimageSpecificationReturnsNoImages", 309 },
    { "TileNotBoundedByImageDimensions", 310 },
    { "UnableToAddOrRemoveProfile", 311 },
    { "UnableToAverageImageSequence", 312 },
    { "UnableToBlurImage", 313 },
    { "UnableToChopImage", 314 },
    { "UnableToColorMatrixImage", 315 },
    { "UnableToConstituteImage", 316 },
    { "UnableToConvolveImage", 317 },
    { "UnableToEdgeImage", 318 },
    { "UnableToEqualizeImage", 319 },
    { "UnableToFilterImage", 320 },
    { "UnableToFormatImageMetadata", 321 },
    { "UnableToFrameImage", 322 },
    { "UnableToOilPaintImage", 323 },
    { "UnableToPaintImage", 324 },
    { "UnableToRaiseImage", 325 },
    { "UnableToSharpenImage", 326 },
    { "UnableToThresholdImage", 327 },
    { "UnableToWaveImage", 328 },
    { "UnrecognizedAttribute", 329 },
    { "UnrecognizedChannelType", 330 },
    { "UnrecognizedColor", 331 },
    { "UnrecognizedColormapType", 332 },
    { "UnrecognizedColorspace", 333 },
    { "UnrecognizedCommand", 334 },
    { "UnrecognizedComposeOperator", 335 },
    { "UnrecognizedDisposeMethod", 336 },
    { "UnrecognizedElement", 337 },
    { "UnrecognizedEndianType", 338 },
    { "UnrecognizedGravityType", 339 },
    { "UnrecognizedHighlightStyle", 340 },
    { "UnrecognizedImageCompression", 341 },
    { "UnrecognizedImageFilter", 342 },
    { "UnrecognizedImageFormat", 343 },
    { "UnrecognizedImageMode", 344 },
    { "UnrecognizedImageType", 345 },
    { "UnrecognizedIntentType", 346 },
    { "UnrecognizedInterlaceType", 347 },
    { "UnrecognizedListType", 348 },
    { "UnrecognizedMetric", 349 },
    { "UnrecognizedModeType", 350 },
    { "UnrecognizedNoiseType", 351 },
    { "UnrecognizedOperator", 352 },
    { "UnrecognizedOption", 353 },
    { "UnrecognizedPerlMagickMethod", 354 },
    { "UnrecognizedPixelMap", 355 },
    { "UnrecognizedPreviewType", 356 },
    { "UnrecognizedResourceType", 357 },
    { "UnrecognizedType", 358 },
    { "UnrecognizedUnitsType", 359 },
    { "UnrecognizedVirtualPixelMethod", 360 },
    { "UnsupportedSamplingFactor", 361 },
    { "UsageError", 362 },
    { "InvalidColorspaceType", 363 },
    { "InvalidEndianType", 364 },
    { "InvalidImageType", 365 },
    { "InvalidInterlaceType", 366 },
    { "MissingAnImageFilename", 367 },
    { "MissingArgument", 368 },
    { "NoImagesWereLoaded", 369 },
    { "OptionLengthExceedsLimit", 370 },
    { "RequestDidNotReturnAnImage", 371 },
    { "UnableToOpenXServer", 372 },
    { "UnableToPersistKey", 373 },
    { "UnrecognizedColormapType", 374 },
    { "UnrecognizedColorspaceType", 375 },
    { "UnrecognizedDisposeMethod", 376 },
    { "UnrecognizedEndianType", 377 },
    { "UnrecognizedFilterType", 378 },
    { "UnrecognizedImageCompressionType", 379 },
    { "UnrecognizedImageType", 380 },
    { "UnrecognizedInterlaceType", 381 },
    { "UnrecognizedOption", 382 },
    { "UnrecognizedResourceType", 383 },
    { "UnrecognizedVirtualPixelMethod", 384 },
    { "UnrecognizedColor", 385 },
    { "ImageExpected", 386 },
    { "ImageInfoExpected", 387 },
    { "StructureSizeMismatch", 388 },
    { "UnableToGetRegistryID", 389 },
    { "UnableToLocateImage", 390 },
    { "UnableToSetRegistry", 391 },
    { "Default", 392 },
    { "Default", 393 },
    { "CacheResourcesExhausted", 394 },
    { "ImagePixelHeightLimitExceeded", 395 },
    { "ImagePixelLimitExceeded", 396 },
    { "ImagePixelWidthLimitExceeded", 397 },
    { "MemoryAllocationFailed", 398 },
    { "NoPixelsDefinedInCache", 399 },
    { "PixelCacheAllocationFailed", 400 },
    { "UnableToAddColorProfile", 401 },
    { "UnableToAddGenericProfile", 402 },
    { "UnableToAddIPTCProfile", 403 },
    { "UnableToAddOrRemoveProfile", 404 },
    { "UnableToAllocateCoefficients", 405 },
    { "UnableToAllocateColormap", 406 },
    { "UnableToAllocateICCProfile", 407 },
    { "UnableToAllocateImage", 408 },
    { "UnableToAllocateString", 409 },
    { "UnableToAnnotateImage", 410 },
    { "UnableToAverageImageSequence", 411 },
    { "UnableToCloneDrawingWand", 412 },
    { "UnableToCloneImage", 413 },
    { "UnableToComputeImageSignature", 414 },
    { "UnableToConstituteImage", 415 },
    { "UnableToConvertFont", 416 },
    { "UnableToConvertStringToTokens", 417 },
    { "UnableToCreateColormap", 418 },
    { "UnableToCreateColorTransform", 419 },
    { "UnableToCreateCommandWidget", 420 },
    { "UnableToCreateImageGroup", 421 },
    { "UnableToCreateImageMontage", 422 },
    { "UnableToCreateXWindow", 423 },
    { "UnableToCropImage", 424 },
    { "UnableToDespeckleImage", 425 },
    { "UnableToDetermineImageClass", 426 },
    { "UnableToDetermineTheNumberOfImageColors", 427 },
    { "UnableToDitherImage", 428 },
    { "UnableToDrawOnImage", 429 },
    { "UnableToEdgeImage", 430 },
    { "UnableToEmbossImage", 431 },
    { "UnableToEnhanceImage", 432 },
    { "UnableToFloodfillImage", 433 },
    { "UnableToGammaCorrectImage", 434 },
    { "UnableToGetBestIconSize", 435 },
    { "UnableToGetFromRegistry", 436 },
    { "UnableToGetPackageInfo", 437 },
    { "UnableToLevelImage", 438 },
    { "UnableToMagnifyImage", 439 },
    { "UnableToManageColor", 440 },
    { "UnableToMapImage", 441 },
    { "UnableToMapImageSequence", 442 },
    { "UnableToMedianFilterImage", 443 },
    { "UnableToMotionBlurImage", 444 },
    { "UnableToNoiseFilterImage", 445 },
    { "UnableToNormalizeImage", 446 },
    { "UnableToOpenColorProfile", 447 },
    { "UnableToQuantizeImage", 448 },
    { "UnableToQuantizeImageSequence", 449 },
    { "UnableToReadTextChunk", 450 },
    { "UnableToReadXImage", 451 },
    { "UnableToReadXServerColormap", 452 },
    { "UnableToResizeImage", 453 },
    { "UnableToRotateImage", 454 },
    { "UnableToSampleImage", 455 },
    { "UnableToScaleImage", 456 },
    { "UnableToSelectImage", 457 },
    { "UnableToSharpenImage", 458 },
    { "UnableToShaveImage", 459 },
    { "UnableToShearImage", 460 },
    { "UnableToSortImageColormap", 461 },
    { "UnableToThresholdImage", 462 },
    { "UnableToTransformColorspace", 463 },
    { "MemoryAllocationFailed", 464 },
    { "SemaporeOperationFailed", 465 },
    { "UnableToAllocateAscii85Info", 466 },
    { "UnableToAllocateCacheInfo", 467 },
    { "UnableToAllocateCacheView", 468 },
    { "UnableToAllocateColorInfo", 469 },
    { "UnableToAllocateDashPattern", 470 },
    { "UnableToAllocateDelegateInfo", 471 },
    { "UnableToAllocateDerivatives", 472 },
    { "UnableToAllocateDrawContext", 473 },
    { "UnableToAllocateDrawInfo", 474 },
    { "UnableToAllocateDrawingWand", 475 },
    { "UnableToAllocateGammaMap", 476 },
    { "UnableToAllocateImage", 477 },
    { "UnableToAllocateImagePixels", 478 },
    { "UnableToAllocateLogInfo", 479 },
    { "UnableToAllocateMagicInfo", 480 },
    { "UnableToAllocateMagickInfo", 481 },
    { "UnableToAllocateMagickMap", 482 },
    { "UnableToAllocateModuleInfo", 483 },
    { "UnableToAllocateMontageInfo", 484 },
    { "UnableToAllocateQuantizeInfo", 485 },
    { "UnableToAllocateRandomKernel", 486 },
    { "UnableToAllocateRegistryInfo", 487 },
    { "UnableToAllocateSemaphoreInfo", 488 },
    { "UnableToAllocateString", 489 },
    { "UnableToAllocateTypeInfo", 490 },
    { "UnableToAllocateWand", 491 },
    { "UnableToAnimateImageSequence", 492 },
    { "UnableToCloneBlobInfo", 493 },
    { "UnableToCloneCacheInfo", 494 },
    { "UnableToCloneImage", 495 },
    { "UnableToCloneImageInfo", 496 },
    { "UnableToConcatenateString", 497 },
    { "UnableToConvertText", 498 },
    { "UnableToCreateColormap", 499 },
    { "UnableToDestroySemaphore", 500 },
    { "UnableToDisplayImage", 501 },
    { "UnableToEscapeString", 502 },
    { "UnableToInitializeSemaphore", 503 },
    { "UnableToInterpretMSLImage", 504 },
    { "UnableToLockSemaphore", 505 },
    { "UnableToObtainRandomEntropy", 506 },
    { "UnableToUnlockSemaphore", 507 },
    { "MemoryAllocationFailed", 508 },
    { "ImageDoesNotContainTheStreamGeometry", 509 },
    { "NoStreamHandlerIsDefined", 510 },
    { "PixelCacheIsNotOpen", 511 },
    { "UnableToAcquirePixelStream", 512 },
    { "UnableToSetPixelStream", 513 },
    { "UnableToSyncPixelStream", 514 },
    { "Default", 515 },
    { "Default", 516 },
    { "FontSubstitutionRequired", 517 },
    { "UnableToGetTypeMetrics", 518 },
    { "UnableToInitializeFreetypeLibrary", 519 },
    { "UnableToReadFont", 520 },
    { "UnrecognizedFontEncoding", 521 },
    { "Default", 522 },
    { "Default", 523 },
    { "InvalidColormapIndex", 524 },
    { "WandAPINotImplemented", 525 },
    { "WandContainsNoImageIndexs", 526 },
    { "WandContainsNoImages", 527 },
    { "ColorIsNotKnownToServer", 528 },
    { "NoWindowWithSpecifiedIDExists", 529 },
    { "StandardColormapIsNotInitialized", 530 },
    { "UnableToConnectToRemoteDisplay", 531 },
    { "UnableToCreateBitmap", 532 },
    { "UnableToCreateColormap", 533 },
    { "UnableToCreatePixmap", 534 },
    { "UnableToCreateProperty", 535 },
    { "UnableToCreateStandardColormap", 536 },
    { "UnableToDisplayImageInfo", 537 },
    { "UnableToGetProperty", 538 },
    { "UnableToGetStandardColormap", 539 },
    { "UnableToGetVisual", 540 },
    { "UnableToGrabMouse", 541 },
    { "UnableToLoadFont", 542 },
    { "UnableToMatchVisualToStandardColormap", 543 },
    { "UnableToOpenXServer", 544 },
    { "UnableToReadXAttributes", 545 },
    { "UnableToReadXWindowImage", 546 },
    { "UnrecognizedColormapType", 547 },
    { "UnrecognizedGravityType", 548 },
    { "UnrecognizedVisualSpecifier", 549 },
    { "UnableToAllocateXHints", 550 },
    { "UnableToCreateCursor", 551 },
    { "UnableToCreateGraphicContext", 552 },
    { "UnableToCreateStandardColormap", 553 },
    { "UnableToCreateTextProperty", 554 },
    { "UnableToCreateXImage", 555 },
    { "UnableToCreateXPixmap", 556 },
    { "UnableToCreateXWindow", 557 },
    { "UnableToDisplayImage", 558 },
    { "UnableToDitherImage", 559 },
    { "UnableToGetPixelInfo", 560 },
    { "UnableToGetVisual", 561 },
    { "UnableToLoadFont", 562 },
    { "UnableToMakeXWindow", 563 },
    { "UnableToOpenXServer", 564 },
    { "UnableToViewFonts", 565 },
    { "UnableToGetVisual", 566 },
    { "UsingDefaultVisual", 567 },
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

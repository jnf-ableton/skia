/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkBitmap.h"
#include "SkForceLinking.h"
#include "SkGraphics.h"
#include "SkImageDecoder.h"

__SK_FORCE_IMAGE_DECODER_LINKING;

/**
   Simple program to test Skia's ability to decode images without
   errors or debug messages. */
int main(int argc, char ** argv) {
    if (argc < 2) {
        SkDebugf("Usage:\n %s imagefile\n\n", argv[0]);
        return 3;
    }
    SkBitmap bitmap;
    if (!(SkImageDecoder::DecodeFile(argv[1], &bitmap))) {
        return 2;
    }
    if (bitmap.empty()) {
        return 1;
    }
    return 0;
}

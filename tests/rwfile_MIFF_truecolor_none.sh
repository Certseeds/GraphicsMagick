#!/bin/sh
# Copyright (C) 2004-2009 GraphicsMagick Group
. ${srcdir}/tests/common.shi
${MEMCHECK} ./rwfile  -filespec 'out_truecolor_none_%d' -compress none ${SRCDIR}/input_truecolor.miff MIFF

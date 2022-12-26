#!/bin/sh
# Simple filter to filter a ChangeLog to something in reStructuredText.
#
expand | sed -e 's/^        \* /  - /g ; s/^        /    /g ; s/\*/\\*/g; s/\_/\\_/g'

#!/bin/sh
# Copyright (C) 2003-2022 GraphicsMagick Group
#
# This program is covered by multiple licenses, which are described in
# Copyright.txt. You should have received a copy of Copyright.txt with this
# package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
#
# Convert the specified POSIX path to a Windows path under MinGW and
# Cygwin The optional second parameter specifies a level of back-slash
# escaping to apply for each forward-slash position in order to
# produce a native Windows path (using back-slashes) to support
# varying levels of POSIX shell variable substitutions in scripts when
# it is necessary to preserve/store native Windows paths.  If the
# second parameter is not provided then a Windows-compatible path is
# produced using only forward slashes (which are still accepted by
# Windows).
#
# Note that Cygwin includes the 'cygpath' utility, which already provides
# path translation capability.
#
# Written by Bob Friesenhahn <bfriesen@simple.dallas.tx.us> June 2002
#
arg="$1"
escapes='none'
if test -n "$2"
then
  escapes="$2"
  if test $escapes -gt 3
  then
    printf "$0: escape level must in range 0 - 3\n"
    exit 1
  fi
fi
result=''
length=0
max_length=0
mount | sed -e 's:\\:/:g'  | (
  IFS="\n"
  while read mount_entry
  do
    win_mount_path=`printf "$mount_entry\n" | sed -e 's: .*::g'`
    unix_mount_path=`printf "$mount_entry\n" | sed -e 's:.* on ::;s: type .*::'`
    temp=`printf "$arg" | sed -e "s!^$unix_mount_path!$win_mount_path!"`
    if test "$temp" != "$arg"
    then
      candidate="$temp"
      length=${#unix_mount_path}
      if test $length -gt $max_length
      then
        result=$candidate
        max_length=$length
      fi
    fi
  done
  if test -z "$result"
  then
    printf "$0: path \"$arg\" is not mounted\n"
    exit 1
  fi
  case "$escapes" in
    0)
     printf "${result}" | sed -e 's:/:\\:g'
     ;;
    1)
     printf "${result}" | sed -e 's:/:\\\\:g'
     ;;
    2)
     printf "${result}" | sed -e 's:/:\\\\\\\\:g'
     ;;
    3)
     printf "${result}" | sed -e 's:/:\\\\\\\\\\\\\\\\:g'
     ;;
    *)
     printf "${result}"
     ;;
  esac
  exit 0;
 )

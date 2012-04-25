#!/usr/bin/env sh

#$uname=`uname`

#if [[ "$uname" == "Linux" -o "$uname" == "Darwin" ]]
#then
   ./tools/pde2cpp.py ../jsshell/js $1 | astyle
#else
#   ./tools/pde2cpp.py ../jsshell/js $1
#fi

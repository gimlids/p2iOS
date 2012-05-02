#!/usr/bin/env sh

#$uname=`uname`

js=`which js`

#if [[ "$uname" == "Linux" -o "$uname" == "Darwin" ]]
#then
   ./tools/pde2cpp.py $js $1 > runtime/openFrameworks/apps/p2iOSapps/p2iOSApp/src/main.mm
#else
#   ./tools/pde2cpp.py ../jsshell/js $1
#fi

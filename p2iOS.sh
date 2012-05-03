#!/usr/bin/env sh

#$uname=`uname`

js=`which js`

output_path="runtime/openFrameworks/apps/p2iOSapps/p2iOSApp/src/main.mm"

#if [[ "$uname" == "Linux" -o "$uname" == "Darwin" ]]
#then
   ./tools/pde2cpp.py $js $1 > $output_path
   astyle $output_path
#else
#   ./tools/pde2cpp.py ../jsshell/js $1
#fi

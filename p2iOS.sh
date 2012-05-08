#!/usr/bin/env bash

#$uname=`uname`

js=`which js`

example_name=`basename $1`
for str in $(echo $example_name | tr "." "\n")
do
   example_name=$str
   break
done

apps_dir="runtime/openFrameworks/apps/p2iOSapps"
template_path="$apps_dir/p2iOSApp"
app_dir="$apps_dir/$example_name"
output_path="$app_dir/src/main.mm"

rm -r $app_dir
cp -R $template_path $app_dir
#mv $app_dir/p2iOSApp.xcodeproj $app_dir/$example_name.xcodeproj


./tools/pde2cpp.py $js $1 > $output_path
astyle $output_path
rm $output_path.orig
cp $1 $app_dir/src/

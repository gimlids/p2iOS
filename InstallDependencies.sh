$uname=`uname`

if [[ "$uname" == "Linux" ]]; then
   sudo apt-get install astyle
elif [[ "$uname" == "Darwin" ]]; then
   brew install astyle
fi

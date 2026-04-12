echo "Compiling 'chekNum.c'..."

cc chekNum.c -o chekNum

echo -e "\nRunning test for: '$@'..."

./chekNum "$@"
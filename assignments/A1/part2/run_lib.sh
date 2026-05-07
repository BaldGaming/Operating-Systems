#Creates folder build will compiled files and runs main file "libshell"
mkdir build
cc libshell.c -o ./build/libshell
cc reader_shell.c -o ./build/reader
cc catalog_shell.c -o ./build/catalog
cc archive_shell.c -o ./build/archive
./build/libshell
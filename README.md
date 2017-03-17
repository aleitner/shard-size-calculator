Shard size calculator for determining optimal shard size to be uploaded to storj network.

build on osx
OSX
`gcc src/shard_size.c -o bin/shard_size_darwin`

Windows
32 bit
`/usr/local/gcc-4.8.0-qt-4.8.4-for-mingw32/win32-gcc/bin/i586-mingw32-gcc src/shard_size.c -o bin/shard_size_win32.exe`

Linux
32 bit
`/usr/local/gcc-4.8.1-for-linux32/bin/i586-pc-linux-gcc --static src/shard_size.c -o bin/shard_size_linux32 -lm`

64 bit
`/usr/local/gcc-4.8.1-for-linux64/bin/x86_64-pc-linux-gcc --static src/shard_size.c -o bin/shard_size_linux64 -lm`

run
`bin/shard_size file_size`

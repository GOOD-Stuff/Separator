# Separator

Splitting lines in files into substrings using specified delimiters.

Used C++17, Boost 1.75, GCC 9.3.0.

Build for Linux (kernel 4.15.0), x64.

### HowTo

For build:

```bash
export BOOT_ROOT=<path to boost/build directory>
export BOOT_INCLUDEDIR=<path to boost/build/include directory>
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

For launch:

```bash
./separator input/ result.txt
# or launch already compiled binary
bin/separator input/ result.txt
```




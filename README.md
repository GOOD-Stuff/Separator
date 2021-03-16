# Separator

Splitting lines in files into substrings using specified delimiters.

Used C++17, Boost 1.75, GCC 9.3.0.

Build for Linux (kernel 4.15.0), x64.

### HowTo

For build:

```bash
export BOOST_ROOT=<path to boost directory>
export BOOST_INCLUDEDIR=<path to boost/include directory>
chmod +x build.sh
./build.sh
```

For launch:

```bash
Release/separator input/ result.txt
# or launch already compiled binary
bin/separator input/ result.txt
```




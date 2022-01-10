#!/bin/bash
echo "Cross compiling the KVP storage repository with provided toolchain"
cd ~/KVPStorageBuildroot
mkdir build_ARM
cd ~/KVPStorageBuildroot/build_ARM
cmake -DCMAKE_TOOLCHAIN_FILE=~/buildroot/output/host/share/buildroot/toolchainfile.cmake  ..
make
echo "Cross compile finished"
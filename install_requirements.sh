#!/bin/bash
echo "KVP storage for embedded environment build started"

echo "Cloning KVP storage repository"
cd ~
git clone https://github.com/egeengin/KVPStorageBuildroot.git
echo "KVP storage repository is cloned"

echo "Building the dependencies"
sudo apt -y install build-essential
sudo apt-get -y install manpages-dev libncurses5-dev libncursesw5-dev git make cmake
echo "Dependicies are built"

echo "Cloning Buildroot repository"
git clone git://git.buildroot.net/buildroot
echo "Buildroot repository is cloned"
cd buildroot
cp ~/KVPStorageBuildroot/br/armconfig.config ~/buildroot/

echo "Configuring and building a buildroot for ARM having SSH connection"
make qemu_arm_versatile_defconfig # to make configuration as is in the hint provided
make menuconfig
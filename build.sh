#!/bin/bash
VER=555.42.02

wget -c "https://github.com/NVIDIA/nvidia-settings/archive/refs/tags/$VER.zip"
unzip "$VER.zip"
mv nvidia-settings-$VER nvidia-settings
cd nvidia-settings
	make -j$(nproc)
cd -

mkdir -p build
cd build
	cmake ..
	make -j$(nproc)
cd -

cp build/nvoc nvoc

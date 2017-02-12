#!/usr/bin/env bash

prefix_dir=`pwd`

GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "${GREEN}\n"
printf "${GREEN}-------------------------------------\n"
printf "${GREEN}----- start to build libmp3lame -----\n"
printf "${GREEN}-------------------------------------\n\n${NC}"
sleep 1

tar -xzf ./dep/lame-3.99.5.tar.gz -C .
cd lame-3.99.5
./configure --prefix=$prefix_dir --enable-shared=yes --enable-static=no
make -j8 && make install
cd ..


printf "${GREEN}\n"
printf "${GREEN}-------------------------------------\n"
printf "${GREEN}------ start to build libopus -------\n"
printf "${GREEN}-------------------------------------\n\n${NC}"
sleep 1

tar -xzf ./dep/opus-1.1.3.tar.gz -C .
cd opus-1.1.3
./configure --prefix=$prefix_dir --enable-shared=yes --enable-static=no --disable-dependency-tracking --disable-doc --disable-extra-programs --enable-custom-modes
make -j8 && make install
cd ..


printf "${GREEN}\n"
printf "${GREEN}-------------------------------------\n"
printf "${GREEN}----- start to build libfdk-aac -----\n"
printf "${GREEN}-------------------------------------\n\n${NC}"
sleep 1

tar -xzf ./dep/fdk-aac-0.1.5.tar.gz -C .
cd fdk-aac-0.1.5
autoreconf -fiv
./configure --prefix=$prefix_dir --enable-static=no
make -j8 && make install
cd ..


printf "${GREEN}\n"
printf "${GREEN}-------------------------------------\n"
printf "${GREEN}------- start to build ffmpeg -------\n"
printf "${GREEN}-------------------------------------\n\n${NC}"

tar -xzf ./dep/FFmpeg-n3.1.2.tar.gz -C .
cd FFmpeg-n3.1.2
./configure --prefix=$prefix_dir \
            --disable-doc \
            --enable-nonfree \
            --extra-cflags="-I$prefix_dir/include" \
            --extra-ldflags="-L$prefix_dir/lib" \
            --disable-yasm \
            --disable-debug \
            --disable-static \
            --enable-shared \
            --disable-programs \
            --disable-avdevice \
            --disable-swscale \
            --disable-postproc \
            --disable-avfilter \
            --disable-network \
            --disable-pixelutils \
            --disable-sdl \
            --disable-d3d11va \
            --disable-dxva2 \
            --disable-nvenc \
            --disable-vaapi \
            --disable-vda \
            --disable-vdpau \
            --disable-videotoolbox \
            --enable-libmp3lame \
            --enable-libfdk-aac \
            --enable-libopus
make -j8 && make install
cd ..


printf "${GREEN}\n"
printf "${GREEN}-------------------------------------\n"
printf "${GREEN}------- build libtranscoding --------\n"
printf "${GREEN}-------------------------------------\n\n${NC}"
sleep 1

gcc ./src/io_in_memory.c ./src/transcoding.c -std=c99 -shared -fpic -O2 -I$prefix_dir/include -L$prefix_dir/lib -lavutil -lavcodec -lavformat -lswresample -o $prefix_dir/lib/libtranscoding.so


rm -rf bin
rm -rf share
rm -rf lame-3.99.5
rm -rf opus-1.1.3
rm -rf fdk-aac-0.1.5
rm -rf FFmpeg-n3.1.2


printf "${GREEN}\n"
printf "${GREEN}Note: to build the demo, run this: \n"
printf
printf "${GREEN} gcc -o demo.exe ./src/demo.c -std=c99 -I./include -L./lib -ltranscoding -lavutil -lavcodec -lavformat -lswresample -lfdk-aac"
printf
printf "${GREEN}----------------- all done ------------------\n\n\n${NC}"

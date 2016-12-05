#!/usr/bin/env bash

prefix_dir=`pwd`

tar -xzf ./dep/lame-3.99.5.tar.gz -C .
cd lame-3.99.5
./configure --prefix=$prefix_dir --enable-shared=yes --enable-static=no
make && make install
cd ..

tar -xzf ./dep/opus-1.1.3.tar.gz -C .
cd opus-1.1.3
./configure --prefix=$prefix_dir --enable-shared=yes --enable-static=no --disable-dependency-tracking --disable-doc --disable-extra-programs --enable-custom-modes
make && make install
cd ..

tar -xzf ./dep/FFmpeg-n3.1.2.tar.gz -C .
cd FFmpeg-n3.1.2

./configure --prefix=$prefix_dir \
            --disable-doc \
            --enable-nonfree \
            --enable-gpl \
            --extra-cflags="-march=native -I$prefix_dir/include" \
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
            --enable-libopus \
            --disable-everything \
            --enable-demuxer=aac,ac3,ape,asf,eac3,flac,mp3,ogg,pcm_alaw,pcm_f32be,pcm_f32le,pcm_f64be,pcm_f64le,pcm_mulaw,pcm_s16be,pcm_s16le,pcm_s24be,pcm_s24le,pcm_s32be,pcm_s32le,pcm_s8,pcm_u16be,pcm_u16le,pcm_u24be,pcm_u24le,pcm_u32be,pcm_u32le,pcm_u8,wav \
            --enable-decoder=aac,ac3,ape,eac3,flac,libopus,mp1,mp2,mp3,opus,pcm_alaw,pcm_f32be,pcm_f32le,pcm_f64be,pcm_f64le,pcm_mulaw,pcm_s16be,pcm_s16be_planar,pcm_s16le,pcm_s16le_planar,pcm_s24be,pcm_s24daud,pcm_s24le,pcm_s24le_planar,pcm_s32be,pcm_s32le,pcm_s32le_planar,pcm_s8,pcm_s8_planar,pcm_u16be,pcm_u16le,pcm_u24be,pcm_u24le,pcm_u32be,pcm_u32le,pcm_u8,vorbis,wavpack,wmalossless,wmapro,wmav1,wmav2,wmavoice \
            --enable-encoder=aac,ac3,eac3,flac,mp2,libmp3lame,libopus,pcm_alaw,pcm_f32be,pcm_f32le,pcm_f64be,pcm_f64le,pcm_mulaw,pcm_s16be,pcm_s16be_planar,pcm_s16le,pcm_s16le_planar,pcm_s24be,pcm_s24daud,pcm_s24le,pcm_s24le_planar,pcm_s32be,pcm_s32le,pcm_s32le_planar,pcm_s8,pcm_s8_planar,pcm_u16be,pcm_u16le,pcm_u24be,pcm_u24le,pcm_u32be,pcm_u32le,pcm_u8,vorbis,wavpack,wmav1,wmav2 \
            --enable-muxer=ac3,asf,eac3,flac,mp2,mp3,oga,ogg,opus,pcm_alaw,pcm_f32be,pcm_f32le,pcm_f64be,pcm_f64le,pcm_mulaw,pcm_s16be,pcm_s16le,pcm_s24be,pcm_s24le,pcm_s32be,pcm_s32le,pcm_s8,pcm_u16be,pcm_u16le,pcm_u24be,pcm_u24le,pcm_u32be,pcm_u32le,pcm_u8,wav \
            --enable-parser=ac3,mpegaudio,flac,aac,vorbis,opus

make && make install


cd ..
rm -rf bin
rm -rf share
rm -rf lame-3.99.5
rm -rf opus-1.1.3
rm -rf FFmpeg-n3.1.2

gcc ./src/io_in_memory.c ./src/transcoding.c -std=c99 -shared -fpic -O2 -I$prefix_dir/include -L$prefix_dir/lib -lavutil -lavcodec -lavformat -lswresample -o $prefix_dir/lib/libtranscoding.so

# gcc ./src/demo.c -std=c99 -O2 -I$prefix_dir/include -L$prefix_dir/lib -ltranscoding -o demo.exe

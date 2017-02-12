# transcoding

Tencent job, transcoding audio in memory based on ffmpeg

## Download dependencies

Download all dependencies into `dep` folder:

1. [libfdk-aac](https://github.com/mstorsjo/fdk-aac)
2. [libmp3lame](http://lame.sourceforge.net/)
3. [libopus](http://opus-codec.org/downloads/)
4. [ffmpeg](https://ffmpeg.org/download.html)

## Build

It's easy, just run:

    sh build.sh

## Demo

To build the demo, run this:

    gcc -o demo ./src/demo.c -std=c99 -I./include -L./lib -ltranscoding -lavutil -lavcodec -lavformat -lswresample -lfdk-aac

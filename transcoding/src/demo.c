//
//  main.c
//
//  Created by tangshi on 16/10/19.
//  Copyright © 2016年 tangshi. All rights reserved.
//

#include <stdio.h>
#include "transcoding.h"

long get_file_size(FILE *fp) {
    long size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }
    else {
        FILE *src_file = fopen(argv[1], "rb");
        long file_size = get_file_size(src_file);

        BufferData src_buf;
        src_buf.buf = (uint8_t *)malloc(file_size);
        src_buf.size = file_size;
        fread(src_buf.buf, src_buf.size, 1, src_file);
        fclose(src_file);

        BufferData dst_buf;
        TranscodingArgs args;
        args.sample_rate = 48000;
        args.bit_rate = 32000;
        args.format_name = "opus";

        transcoding(&dst_buf, args, src_buf);

        FILE *dst_file = fopen(argv[2], "wb");
        fwrite(dst_buf.buf, dst_buf.size, 1, dst_file);
        fclose(dst_file);

        free(src_buf.buf);
        free(dst_buf.buf);

        return 0;
    }
}


//
//  main.c
//  audio_encoder
//
//  Created by tangshi on 16/10/19.
//  Copyright © 2016年 tangshi. All rights reserved.
//

#include <stdio.h>
#include "transcoding.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }
    else {
        return transcoding(argv[1], argv[2]);
    }
}


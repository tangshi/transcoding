//
//  transcoding.h
//
//  Created by tangshi on 16/10/19.
//  Copyright © 2016年 tangshi. All rights reserved.
//

#ifndef transcoding_transcoding_h
#define transcoding_transcoding_h

#include <stdint.h>

#include "io_in_memory.h"


/**
 Target audio args
 
 @bit_rate: controls the compression rate of target audio, pass 0 to use default value
 @format_name: target media container name,
  see all supported formats name by executing `ffmpeg -formats`
 */
typedef struct TranscodingArgs {
    int64_t bit_rate;
    char   *format_name;
} TranscodingArgs;


/**
 transcoding audio format in memory

 @param[in,out] p_dst_buf pointer to output audio buffer
 @param args target audio format args
 @param src_buf source audio buffer

 @return 0 on success or negative on error
 */
int transcoding(BufferData *p_dst_buf, const TranscodingArgs args, const BufferData src_buf);


#endif /* transcoding_h */

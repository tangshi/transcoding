//
//  transcoding.h
//  audio_encoder
//
//  Created by tangshi on 16/10/19.
//  Copyright © 2016年 tangshi. All rights reserved.
//

#ifndef transcoding_h
#define transcoding_h

#include <stdint.h>

#include "io_in_memory.h"


/** Target audio's args
 *
 *  bit_rate controls the compression rate of target audio
 *
 *  format_name is the target media container's name,
 *  see all supported formats name by executing `ffmpeg -formats`
 *
 */
typedef struct TranscodingArgs {
    int64_t bit_rate;
    char   *format_name;
} TranscodingArgs;


int transcoding(BufferData *p_dst_buf, const TranscodingArgs *args, const BufferData src_buf);


#endif /* transcoding_h */

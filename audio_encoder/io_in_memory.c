//
//  utils.c
//  audio_encoder
//
//  Created by tangshi on 16/10/18.
//  Copyright © 2016年 tangshi. All rights reserved.
//

#include "io_in_memory.h"

#include <libavformat/avio.h>
#include <libavformat/avformat.h>


int init_io_context_custom(AVFormatContext *fmt_ctx,
                           int buffer_size,
                           int write_flag,
                           void *opaque,
                           int (*read_packet)(void *opaque, uint8_t *buf, int buf_size),
                           int (*write_packet)(void *opaque, uint8_t *buf, int buf_size),
                           int64_t (*seek)(void *opaque, int64_t offset, int whence)) {

    uint8_t *avio_ctx_buffer = av_malloc(buffer_size);
    if (NULL == avio_ctx_buffer) {
        return AVERROR(ENOMEM);
    }

    // **avio_ctx_buffer** may be freed and replaced with a new buffer
    // free **avio_ctx_buffer** only if allocating avio_ctx fail, otherwise
    // free **avio_ctx->buffer**
    AVIOContext *avio_ctx;
    avio_ctx = avio_alloc_context(avio_ctx_buffer, buffer_size, write_flag, opaque, read_packet, write_packet, seek);
    if (NULL == avio_ctx) {
        av_free(avio_ctx_buffer);
        return AVERROR(ENOMEM);
    }

    fmt_ctx->pb = avio_ctx; // set I/O context for **fmt_ctx**

    return 0;
}


static int m_read_packet(void *opaque, uint8_t *buf, int buf_size);
static int m_write_packet(void *opaque, uint8_t *buf, int buf_size);
static int64_t m_seek(void *opaque, int64_t offset, int whence);


int init_io_context_default(AVFormatContext *fmt_ctx, int write_flag, BufferIO *bio) {

    return init_io_context_custom(fmt_ctx, 4096, write_flag, bio, &m_read_packet, &m_write_packet, &m_seek);

}

static int m_read_packet(void *opaque, uint8_t *buf, int buf_size) {

    BufferIO *bio = (BufferIO *)opaque;
    int left_size = (int)(bio->size - bio->curr);
    buf_size = FFMIN(buf_size, left_size);

    memcpy(buf, bio->buf + bio->curr, buf_size);
    bio->curr += buf_size;

    return buf_size;
}

static int m_write_packet(void *opaque, uint8_t *buf, int buf_size) {

    BufferIO *bio = (BufferIO *)opaque;

    if (bio->curr + buf_size > bio->_total) {

        size_t new_total;
        do {
            new_total = buf_size + bio->_total * 3 / 2;
        } while (bio->curr + buf_size > new_total);

        uint8_t *ptr = (uint8_t *)realloc(bio->buf, new_total);
        if (ptr == NULL) {
            fprintf(stderr, "Could not alloc memory !");
            return AVERROR(ENOMEM);
        }
        else {
            bio->buf = ptr;
            bio->_total = new_total;
        }
    }

    memcpy(bio->buf + bio->curr, buf, buf_size);

    if (bio->curr + buf_size > bio->size) {
        bio->size = bio->curr + buf_size;
    }

    bio->curr += buf_size;
    
    return buf_size;
}

static int64_t m_seek(void *opaque, int64_t offset, int whence) {
    int64_t new_pos = 0;
    BufferIO *bio = (BufferIO *)opaque;

    switch (whence) {

        case SEEK_SET:
            new_pos = offset;
            break;
        case SEEK_CUR:
            new_pos = bio->curr + offset;
            break;
        case SEEK_END:
            new_pos = bio->size + offset;
            break;
        default:
            return AVERROR(EINVAL);
    }

    bio->curr = FFMIN(new_pos, bio->size);
    
    return bio->curr;
}

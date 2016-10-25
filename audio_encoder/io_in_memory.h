//
//  io_in_memory.h
//
//  Created by tangshi on 16/10/18.
//  Copyright © 2016年 tangshi. All rights reserved.
//

#ifndef transcoding_io_in_memory_h
#define transcoding_io_in_memory_h

#include <libavformat/avformat.h>

typedef struct BufferData {
    uint8_t *buf;  /// begin ptr of buffer block
    size_t   size; /// size of buffer block
} BufferData;


/**
 *  Buffer for I/O, namely read and write in memory
 */
typedef struct BufferIO {
    uint8_t *buf;    /// memory block pointer
    size_t   curr;   /// current position
    size_t   size;   /// real size of used buffer
    size_t   _total; /// private, total size of allocated buffer, _total >= size
} BufferIO;


/**
 Make format_context I/O in memory
 
 @param write_flag Set to 1 if the buffer should be writable, 0 otherwise.
        Typically 0 for input format context and 1 for output format context.
 @param bio An pointer to BufferIO data.

 @return 0 on success or negative on error.
 */
int init_io_context_default(AVFormatContext *format_context, int write_flag, BufferIO *bio);


/**
 Make format_context I/O in memory

 @param buffer_size The buffer size is very important for performance.
        For protocols with fixed blocksize it should be set to this blocksize.
        For others a typical size is a cache page, e.g. 4kb.
 @param write_flag  Set to 1 if the buffer should be writable, 0 otherwise.
        Typically 0 for input format context and 1 for output format context.
 @param opaque An opaque pointer to user-specific data.
 @param read_packet A function for refilling the buffer, may be NULL.
 @param write_packet A function for writing the buffer contents, may be NULL.
        The function may not change the input buffers content.
 @param seek A function for seeking to specified byte position, may be NULL.
        Note: It returns new position on success instead of zero.

 @return 0 on success or negative on error.
 */
int init_io_context_custom(AVFormatContext *format_context,
                           int buffer_size,
                           int write_flag,
                           void *opaque,
                           int (*read_packet)(void *opaque, uint8_t *buf, int buf_size),
                           int (*write_packet)(void *opaque, uint8_t *buf, int buf_size),
                           int64_t (*seek)(void *opaque, int64_t offset, int whence));


#endif /* transcoding_io_in_memory_h */


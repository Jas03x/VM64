#ifndef DISK_HPP
#define DISK_HPP

#include <stdint.h>

namespace disk
{
    int init(const char* path);
    int free();

    int read(unsigned int offset, unsigned int length, uint8_t* buffer);
}

#endif // DISK_HPP
#include "disk.hpp"

#include <stdio.h>
#include <stdlib.h>

FILE*        m_handle;
unsigned int m_capacity;

int disk::init(const char* path)
{
    int status = 0;

    m_handle = fopen(path, "rb");
    if(m_handle == nullptr)
    {
        status = -1;
        printf("error: could not load disk from file \"%s\"\n", path);
    }

    fseek(m_handle, 0L, SEEK_END);
    m_capacity = ftell(m_handle);
    fseek(m_handle, 0L, SEEK_SET);

    if(m_capacity < 4096)
    {
        status = -1;
        printf("error: harddrive too small - must have capacity of at least 4kb\n");
    }

    return status;
}

int disk::free()
{
    fclose(m_handle);

    return 0;
}


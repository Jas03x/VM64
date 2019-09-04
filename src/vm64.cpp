
#include <vm64.hpp>

#include <stdio.h>
#include <stdlib.h>

#include "io.hpp"
#include "disk.hpp"

namespace vm
{
    namespace memory
    {
        uint8_t* ptr;

        void init()
        {
            ptr = new uint8_t[RAM_SIZE];
        }

        void free()
        {
            delete[] ptr;
        }
    }

    int run()
    {
        int status = 0;
        printf("initializing\n");

        bool running = true;
        while(running && (status == 0))
        {
            
        }

        printf("terminating\n");
        return status;
    }
}

int main(int argc, char* argv[])
{
    int status = 0;

    if(argc != 2)
    {
        status = -1;
        printf("error: invalid arguments\n");
    }

    if(status == 0) { status = disk::init(argv[1]); }
    if(status == 0) { status = io::init();          }

    if(status == 0)
    {
        status = vm::run();
    }

    if(status == 0)
    {
        io::free();
        disk::free();
    }

    return status;
}

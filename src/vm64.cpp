
#include <vm64.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int load_bootloader()
    {
        int status = 0;

        if(disk::read(BOOT_LOADER_OFFSET, BOOT_LOADER_SIZE, memory::ptr) != 0)
        {
            status = -1;
            printf("error: disk read failure\n");
        }
        else
        {
            const char* BOOT_LOADER_HEADER = "__VM64__";
            if(memcmp(memory::ptr, BOOT_LOADER_HEADER, 8) != 0)
            {
                status = -1;
                printf("error: bootloader not found\n");
            }
        }

        return status;
    }

    int run()
    {
        int status = 0;
        
        printf("initializing\n");
        
        memory::init();
        status = load_bootloader();

        if(status == 0)
        {
            bool running = true;
            while(running && (status == 0))
            {
                switch(io::get_status())
                {
                    case io::status::running:    { break;                  }
                    case io::status::power_down: { running = false; break; }
                    default:                     { status = -1; break;     }
                }
            }
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

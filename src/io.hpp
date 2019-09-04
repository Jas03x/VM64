#ifndef IO_HPP
#define IO_HPP

namespace io
{
    enum status
    {
        error        = 0,
        initializing = 1,
        running      = 2,
        power_down   = 3
    };

    int  init();
    void free();

    int get_status();
}

#endif // IO_HPP
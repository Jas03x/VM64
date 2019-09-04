
#include <vm64.hpp>

#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

namespace disk
{
    FILE*        m_handle;
    unsigned int m_capacity;

    int init(const char* path)
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

    int free()
    {
        fclose(m_handle);
        
        return 0;
    }
};

namespace display
{
    SDL_Window*   m_window;
	SDL_GLContext m_context;

    int assert(bool b, const char* msg)
    {
        int status = 0;
        if(!b)
        {
            status = -1;
            printf("%s: %s\n", msg, SDL_GetError());
        }
        return status;
    }

    int init()
    {
        int status = assert(SDL_Init(SDL_INIT_EVERYTHING) == 0, "sdl initialization failure");

        if(status == 0)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        }

        if(status == 0)
        {
            m_window = SDL_CreateWindow(
		        "VM64",
		        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		        DISPLAY::WIDTH, DISPLAY::HEIGHT,
		        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	        );
            status = assert(m_window != nullptr, "error creating sdl window");
        }

        if(status == 0)
        {
            m_context = SDL_GL_CreateContext(m_window);
            status = assert(m_context != nullptr, "error creating sdl opengl context");
        }

        return status;
    }

    int free()
    {
        if (m_context != nullptr) { SDL_GL_DeleteContext(m_context); }
        if (m_window != nullptr)  { SDL_DestroyWindow(m_window);     }
        SDL_Quit();

        return 0;
    }

    void update() {
        SDL_GL_SwapWindow(m_window);
    }

    void poll_events()
    {
        SDL_Event event = {};

        while(SDL_PollEvent(&event) != 0)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                {
                    break;
                }

                default:
                {
                    break;
                }
            }
        }
    }
};

int run()
{
    int status = 0;
    printf("initializing\n");

    bool running = true;
    while(running && (status == 0))
    {
        display::update();
        display::poll_events();
    }

    printf("terminating\n");
    return status;
}

int main(int argc, char* argv[])
{
    int status = 0;

    if(argc != 2)
    {
        status = -1;
        printf("error: invalid arguments\n");
    }

    if(status == 0) {
        status = disk::init(argv[1]);
    }

    if(status == 0) {
        status = display::init();
    }

    if(status == 0) {
        status = run();
    }

    if(status == 0)
    {
        disk::free();
        display::free();
    }

    return status;
}

#include "io.hpp"

#include <stdio.h>

#include <thread>
#include <atomic>

#include <vm64.hpp>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

std::thread* m_thread = nullptr;
std::atomic<int> m_status = io::status::error;

inline void sdl_error(const char* msg)
{
    m_status.store(io::status::error);
    printf("%s: %s\n", msg, SDL_GetError());
}

void thread_func()
{
    SDL_Window*   m_window  = nullptr;
    SDL_GLContext m_context = nullptr;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        sdl_error("sdl initialization failure");
    }
    else
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_window = SDL_CreateWindow(
            "VM64",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            DISPLAY::WIDTH, DISPLAY::HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

        if(m_window == nullptr)
        {
            sdl_error("error creating sdl window");
        }
        else
        {
            m_context = SDL_GL_CreateContext(m_window);
            if(m_context == nullptr)
            {
                sdl_error("error creating sdl opengl context");
            }
        }
    }

    if(m_status.load() != io::status::error)
    {
        m_status.store(io::status::running);

        bool running = true;
        while(running)
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
            
            SDL_GL_SwapWindow(m_window);
        }

        if (m_context != nullptr) { SDL_GL_DeleteContext(m_context); }
        if (m_window != nullptr)  { SDL_DestroyWindow(m_window);     }
        SDL_Quit();
    }
}

int io::init()
{
    int result = 0;
    
    m_status.store(io::status::initializing);
    m_thread = new std::thread(thread_func);

    while(true)
    {
        int status = m_status.load();
        if(status == io::status::initializing)
        {
            std::this_thread::yield();
        }
        else
        {
            if(status != io::status::running)
            {
                result = -1;
            }

            break;
        }
    }
    
    return result;
}

void io::free()
{
    
}

int io::get_status()
{
    return m_status.load();
}

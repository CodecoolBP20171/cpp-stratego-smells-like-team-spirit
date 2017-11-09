#ifndef SDLTEST_SDLTEST_H
#define SDLTEST_SDLTEST_H

#include <iostream>
#include <SDL.h>

int main() {

    int mouse_x, mouse_y;

    SDL_Window *window;
    window = SDL_CreateWindow("Ilyen nincs", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Event event;

    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // The window is open: could enter program loop here

    bool quit = false;

    // While application is running
    while ( !quit ) {

        // Handle events on queue
        while( SDL_PollEvent( &event ) != 0 ) // poll for events received from user or operating system
        {
            // User requests quit
            if ( event.type == SDL_QUIT )
            {
                quit = true;
            }
            // Handle button events
            if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                std::cout << "\nX position of mouse: " << mouse_x << "\nY position of mouse: " << mouse_y << std::endl;
            }
        }
    }


    // Pause execution for 1000 milliseconds
    SDL_Delay(1000);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}

#endif //SDLTEST_SDLTEST_H
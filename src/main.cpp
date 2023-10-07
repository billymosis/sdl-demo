/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// Using SDL and standard IO
#include "SDL_filesystem.h"
#include "SDL_init.h"
#include "SDL_oldnames.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_VULKAN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Load splash image
  gHelloWorld = SDL_LoadBMP("src/resources/hello_world.bmp");
  printf("%s\n", SDL_GetBasePath());
  if (gHelloWorld == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n",
           "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
    success = false;
  }

  return success;
}

void close() {
  // Deallocate surface
  SDL_DestroySurface(gHelloWorld);
  gHelloWorld = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media\n");
    } else {
      SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
    }
    SDL_UpdateWindowSurface(gWindow);
    // Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT)
          quit = true;
      }
    }
  }

  close();
  return 0;
}

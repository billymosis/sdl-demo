/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// Using SDL and standard IO

// It maybe good practice to make local vendor with quote and build in with
// angle bracket
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL_events.h"
#include "SDL_filesystem.h"
#include "SDL_init.h"
#include "SDL_oldnames.h"
#include "SDL_rect.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <stdio.h>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface *loadSurface(std::string path);

SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *gCurrentSurface = NULL;

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *optimizedSurface = NULL;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
  } else {
    optimizedSurface =
        SDL_ConvertSurface(loadedSurface, gScreenSurface->format);
    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }
    SDL_DestroySurface(loadedSurface);
  }
  return optimizedSurface;
}

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
      int imgFlags = IMG_INIT_PNG;
      // & is bitwise and
      // https://en.wikipedia.org/wiki/Bitwise_operations_in_C#Bitwise_AND_.22.26.22
      if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
               IMG_GetError());
        success = false;
      } else {
        // Get window surface
        gScreenSurface = SDL_GetWindowSurface(gWindow);
      }
    }
  }
  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
      loadSurface("src/resources/loaded.png");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load default image!\n");
    success = false;
  }

  // Load up surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("src/resources/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Failed to load up image!\n");
    success = false;
  }

  // Load down surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] =
      loadSurface("src/resources/down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Failed to load down image!\n");
    success = false;
  }

  // Load left surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] =
      loadSurface("src/resources/left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Failed to load left image!\n");
    success = false;
  }

  // Load right surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] =
      loadSurface("src/resources/right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Failed to load right image!\n");
    success = false;
  }

  return success;
}

void close() {
  // Deallocate surface
  SDL_DestroySurface(gCurrentSurface);
  gCurrentSurface = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize\n");
    close();
    return 0;
  }

  if (!loadMedia()) {
    printf("Failed to load media!\n");
    close();
    return 0;
  }

  bool quit = false;
  SDL_Event e;

  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      } else if (e.type == SDL_EVENT_KEY_DOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
          break;
        case SDLK_DOWN:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
          break;
        case SDLK_LEFT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
          break;
        case SDLK_RIGHT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
          break;
        }
      }
    }
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;
    SDL_BlitSurfaceScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
    SDL_UpdateWindowSurface(gWindow);
  }

  close();
  return 0;
}

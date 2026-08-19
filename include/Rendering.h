#pragma once
#include <SDL.h>
#include "Gameoflife.h"

class Rendering{
    private:
     static constexpr int window_size_x = 1200;
     static constexpr int window_size_y = 800;
     static constexpr int grid_width = 4;
     static constexpr int grid_height = 4;
     GameOfLife *game;   
     SDL_Window *window = nullptr;
     SDL_Renderer *renderer = nullptr;
     SDL_Event event;
     SDL_Rect grid_cell = {0, 0, grid_width, grid_height};
     bool RUN = true, Game_running = false;
    public:
     Rendering(GameOfLife *game);
     void create_window();
     void event_handle(); 
     void update_grid();
};
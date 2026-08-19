#include "..\include\Rendering.h"
Rendering::Rendering(GameOfLife *new_game):game{new_game} {}

void Rendering::create_window()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(window_size_x, window_size_y, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    update_grid();
}

void Rendering::update_grid()
{
     for (std::size_t i = 0; i < game->size_x; i++)
            {
                for (std::size_t j = 0; j < game->size_y; j++)
                {
                    grid_cell.x = i * grid_cell.w;
                    grid_cell.y = j * grid_cell.h;
                    if (game->getCells()[i][j] == 0)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    }
                    SDL_RenderDrawRect(renderer, &grid_cell);
                    // SDL_RenderFillRect(renderer,&grid_cell);   
                }
            }
}
void Rendering::event_handle()
{
    create_window();
    while (RUN)
        {
            while (SDL_PollEvent(&event))
            {
            switch (event.type)
            {
            case SDL_QUIT:
                RUN = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // SETTING STATE OF CELLS
                if (!Game_running)
                {
                }
                //
                break;
            case SDL_KEYDOWN:
                // TURNING OFF AND ON SIMULATION
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    if (Game_running)
                        Game_running = false;
                    else
                        Game_running = true;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
             }
            if (Game_running){
            game->update();
            update_grid();
            }
         SDL_RenderPresent(renderer);
        }
   
}
#include <SDL.h>
#include <cstdlib>
#include <ctime>
#include <array>

#define size_x 300
#define size_y 200

bool copy(std::array<std::array<int,size_y>,size_x> orgin, std::array<std::array<bool,size_y>,size_x> dest, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            dest[i][j] = orgin[i][j];
        }
    }
    return 1;
}
int num_of_neigh(std::array<std::array<int,size_y>,size_x> cells, int i, int j, int max_x, int max_y)
{
    int ans = 0;
    if ((i == 0 && j == 0))
    {
        ans += cells[j + 1][i];
        ans += cells[j + 1][i + 1];
        ans += cells[j][i + 1];
    }
    else if ((i == max_y && j == max_x))
    {
        ans += cells[j - 1][i];
        ans += cells[j - 1][i - 1];
        ans += cells[j][i - 1];
    }
    else if (i == 0 && j == max_x)
    {
        ans += cells[j - 1][i];
        ans += cells[j - 1][i + 1];
        ans += cells[j][i + 1];
    }
    else if (i == max_y && j == 0)
    {
        ans += cells[j + 1][i - 1];
        ans += cells[j][i - 1];
        ans += cells[j + 1][i];
    }
    else if (i == 0)
    {
        ans += cells[j - 1][i];
        ans += cells[j + 1][i];
        ans += cells[j + 1][i + 1];
        ans += cells[j][i + 1];
        ans += cells[j - 1][i + 1];
    }
    else if (i == max_y)
    {
        ans += cells[j - 1][i];
        ans += cells[j + 1][i];
        ans += cells[j + 1][i - 1];
        ans += cells[j][i - 1];
        ans += cells[j - 1][i - 1];
    }
    else if (j == 0)
    {
        ans += cells[j][i + 1];
        ans += cells[j][i - 1];
        ans += cells[j + 1][i + 1];
        ans += cells[j + 1][i - 1];
        ans += cells[j + 1][i];
    }
    else if (j == max_x)
    {
        ans += cells[j][i - 1];
        ans += cells[j][i + 1];
        ans += cells[j - 1][i];
        ans += cells[j - 1][i + 1];
        ans += cells[j - 1][i - 1];
    }
    else
    {
        ans += cells[j][i - 1];
        ans += cells[j][i + 1];
        ans += cells[j - 1][i];
        ans += cells[j - 1][i + 1];
        ans += cells[j - 1][i - 1];
        ans += cells[j + 1][i + 1];
        ans += cells[j + 1][i - 1];
        ans += cells[j + 1][i];
    }
    return ans;
}
int main()
{
    std::srand(std::time(0));
    int x, y;
    using Grid = std::array<std::array<int,size_y>,size_x>;
    Grid cells{};
    Grid newcells{};
    int window_size_x = 1200, window_size_y = 800;
    int grid_width = 4, grid_height = 4;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event event;
    bool RUN = true, Game_running = false;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(window_size_x, window_size_y, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect grid_cell = {0, 0, grid_width, grid_height};

    // GENERATE GRID
    for (int i = 0; i < window_size_x / grid_width; i++)
    {
        SDL_RenderDrawLine(renderer, grid_width * i, 0, grid_width * i, window_size_y);
    }
    for (int i = 0; i < window_size_y / grid_height; i++)
    {
        SDL_RenderDrawLine(renderer, 0, grid_height * i, window_size_x, grid_height * i);
    }

    // BUILD RANDOM CEELS
    for (int i = 0; i < window_size_y / grid_height; i++){
                    for (int j = 0; j < window_size_x / grid_width; j++){
                        cells[j][i] = std::rand()%2;
                        // SDL_Log("%i",cells[j][i]);
                        if(cells[j][i]==1){
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        }else{
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        }
                        grid_cell.x = grid_width * (j);
                        grid_cell.y = grid_height * (i);
                        SDL_RenderFillRect(renderer, &grid_cell);
                    }
    }

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
                //SETTING STATE OF CELLS
                if (Game_running == false)
                {
                    x = event.button.x / grid_width;
                    y = event.button.y / grid_height;

                    cells[x][y] = 1;

                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                    grid_cell.x = grid_width * x;
                    grid_cell.y = grid_height * y;

                    SDL_RenderFillRect(renderer, &grid_cell);

                    break;
                }
            case SDL_KEYDOWN:
            //TURNING OFF AND ON SIMULATION
                switch (event.key.keysym.sym)
                {
                case SDLK_w:

                    if (Game_running == true)
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

        if (Game_running == true)
        {
            for (int i = 0; i < window_size_y / grid_height; i++)
            {
                for (int j = 0; j < window_size_x / grid_width; j++)
                {  
                    int neigh = num_of_neigh(cells, i, j, (window_size_x / grid_height) - 1, (window_size_y / grid_height) - 1);
                    if (cells[j][i] == 0)
                    {
                        if (neigh == 3)
                        {
                            newcells[j][i] = 1;
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        }
                        else
                        {
                            newcells[j][i] = 0;
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        }
                    }
                    else if (cells[j][i] == 1)
                    {
                        if (neigh == 2 || neigh == 3)
                        {
                            newcells[j][i] = 1;
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        }
                        else
                        {
                            newcells[j][i] = 0;
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        }
                    }
                    grid_cell.x = grid_width * (j);
                    grid_cell.y = grid_height * (i);
                    SDL_RenderFillRect(renderer, &grid_cell);
                }
            }
            std::swap(cells,newcells);
            // copy(newcells, cells, size_x, size_y);
        }
        SDL_RenderPresent(renderer);
    }
}

#include "..\include\Gameoflife.h"
#include "..\include\Rendering.h"

int main()
{
    GameOfLife game;
    Rendering render(&game);
    game.generate_cells();
    render.event_handle();
 }

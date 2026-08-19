#include "..\include\Gameoflife.h"
int GameOfLife::num_of_neigh(int x,int y) const {
    int ans = 0;
    int max_y = cells[0].size();
    int max_x = cells[0].size();
    if ((y == 0 && x == 0))
    {
        ans += cells[x + 1][y];
        ans += cells[x + 1][y + 1];
        ans += cells[x][y + 1];
    }
    else if ((y == max_y && x == max_x))
    {
        ans += cells[x - 1][y];
        ans += cells[x - 1][y - 1];
        ans += cells[x][y - 1];
    }
    else if (y == 0 && x == max_x)
    {
        ans += cells[x - 1][y];
        ans += cells[x - 1][y + 1];
        ans += cells[x][y + 1];
    }
    else if (y == max_y && x == 0)
    {
        ans += cells[x + 1][y - 1];
        ans += cells[x][y - 1];
        ans += cells[x + 1][y];
    }
    else if (y == 0)
    {
        ans += cells[x - 1][y];
        ans += cells[x + 1][y];
        ans += cells[x + 1][y + 1];
        ans += cells[x][y + 1];
        ans += cells[x - 1][y + 1];
    }
    else if (y == max_y)
    {
        ans += cells[x - 1][y];
        ans += cells[x + 1][y];
        ans += cells[x + 1][y - 1];
        ans += cells[x][y - 1];
        ans += cells[x - 1][y - 1];
    }
    else if (x == 0)
    {
        ans += cells[x][y + 1];
        ans += cells[x][y - 1];
        ans += cells[x + 1][y + 1];
        ans += cells[x + 1][y - 1];
        ans += cells[x + 1][y];
    }
    else if (x == max_x)
    {
        ans += cells[x][y - 1];
        ans += cells[x][y + 1];
        ans += cells[x - 1][y];
        ans += cells[x - 1][y + 1];
        ans += cells[x - 1][y - 1];
    }
    else
    {
        ans += cells[x][y - 1];
        ans += cells[x][y + 1];
        ans += cells[x - 1][y];
        ans += cells[x - 1][y + 1];
        ans += cells[x - 1][y - 1];
        ans += cells[x + 1][y + 1];
        ans += cells[x + 1][y - 1];
        ans += cells[x + 1][y];
    }
    return ans;
}
void GameOfLife::generate_cells()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution alive(0.2);

    for (int i = 0; i < size_x; i++){
                    for (int j = 0; j < size_y; j++){
                        cells[j][i] = alive(gen);
                    }
    }
}
const GameOfLife::Grid &GameOfLife::getCells() const
{
    return cells;
}
void GameOfLife::update()
{
    for (int i = 0; i < size_x; i++)
            {
                for (int j = 0; j < size_y; j++)
                {  
                    int neigh = num_of_neigh(i, j);
                    if (cells[i][j] == 0)
                    {
                        if (neigh == 3)
                        {
                            newcells[i][j] = 1;
                        }
                        else
                        {
                            newcells[i][j] = 0;
                        }
                    }
                    else if (cells[i][j] == 1)
                    {
                        if (neigh == 2 || neigh == 3)
                        {
                            newcells[i][j] = 1;
                        }
                        else
                        {
                            newcells[i][j] = 0;
                        }
                    }
                }
            }
            std::swap(cells,newcells);
}
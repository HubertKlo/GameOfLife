#include "..\include\Gameoflife.h"
#include <random>
int GameOfLife::num_of_neigh(int x,int y) const {
    int ans = 0;
    int max_y = cells[0].size();
    int max_x = cells.size();

            for(int k=-1;k<=1;k++){
                for(int p=-1;p<=1;p++){
                    if(k+x<0||k+x>=max_x)continue;
                    if(k+y<0||k+y>=max_y)continue;
                    if(k==0&&p==0)continue; 
                    if(cells[x+k][y+p])ans++;
                }
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
                   // printf("%i \n",neigh);
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
#pragma once
#include <array>
#include <random>

class GameOfLife
{
public:
    static constexpr int size_x = 1200;
    static constexpr int size_y = 800;

    using Grid = std::array<std::array<bool, size_y>, size_x>;

private:
    Grid cells{};
    Grid newcells{};

public:
    void update();
    int num_of_neigh(int x, int y) const;
    void generate_cells();
    const Grid& getCells() const;
};
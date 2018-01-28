//
// Created by foebus on 27.01.18.
//

#ifndef PROJECT_GRID_H
#define PROJECT_GRID_H

#include "Unit.h"
#include "Tower.h"

class Grid: public Unit
{
public:
    void create(unsigned int tiles_nb);
    void create_path(std::vector<Point> points);
    const std::vector<std::vector<spTower>> &getCells() const;

protected:
    void _init() override;
    void onEvent(Event* ev);
    void display();
    void hide();

private:
    spSprite activeCell;
    std::vector<std::vector<spTower>> cells;
    Vector2 region_size;
    int square_nb;
    bool _pressed;
    Vector2 squareSize;
};


#endif //PROJECT_GRID_H

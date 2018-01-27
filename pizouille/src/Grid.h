//
// Created by foebus on 27.01.18.
//

#ifndef PROJECT_GRID_H
#define PROJECT_GRID_H

#include "Unit.h"

class Grid: public Unit
{
public:
    void create(unsigned int size);

protected:
    void _init() override;
    void onEvent(Event* ev);
    void display();
    void hide();

    std::vector<std::vector<spSprite>>  cells;

private:
    Vector2 region_size;
    int my_size;
    bool _pressed;
};


#endif //PROJECT_GRID_H

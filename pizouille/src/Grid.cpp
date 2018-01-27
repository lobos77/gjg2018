//
// Created by foebus on 27.01.18.
//

#include "Grid.h"
#include "res.h"
#include "Game.h"

void Grid::_init() {
    _view->setPosition(0, 0);
    region_size = _game->getSize();
}

void Grid::create(unsigned int size) {

    Vector2 squareSize = region_size/size;
    cells.resize(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cells[i].push_back(new Sprite);
            cells[i][j]->setScale(1.0f/squareSize.x);
            cells[i][j]->setResAnim(res::ui.getResAnim("simpleSquare"));
            cells[i][j]->attachTo(_view);
            cells[i][j]->setPosition(Vector2(float(i * 20), float(j * 20)));
            cells[i][j]->setAlpha(50);
        }
    }
}
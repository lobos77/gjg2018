//
// Created by foebus on 27.01.18.
//

#include <iostream>
#include "Grid.h"
#include "res.h"
#include "Game.h"
#include "Playground.h"
#include "Monster.h"
#include "oxygine-framework.h"
#include <iostream>

void Grid::_init() {
    _view->setPosition(0, 0);
    region_size = _game->_playground->getSize();
    //region_size = _game->getSize();
    square_nb = 0;
}

const Vector2 &Grid::getSquareSize() const {
    return squareSize;
}

void Grid::create(unsigned int tiles_nb) {

    square_nb = tiles_nb;
    squareSize = region_size/tiles_nb;
    cells.resize(tiles_nb);
    const ResAnim * myAnim = res::ui.getResAnim("tiled2");
    float scaleFactor = region_size.x/(myAnim->getSize().x*square_nb);

    activeCell = new Sprite;
    activeCell->setScale(scaleFactor);
    activeCell->setResAnim(myAnim);
    activeCell->attachTo(_view);
    activeCell->setPosition(Vector2(0, 0));
    activeCell->setAlpha(50);
    activeCell->setPriority(2);
    activeCell->setTouchEnabled(false);

    for (int x = 0; x < tiles_nb; x++) {
        for (int y = 0; y < tiles_nb; y++) {
            cells[x].push_back(new Tower(Vector2((x * squareSize.x), (y * squareSize.y))));
            spTower cell =cells[x][y];
            cell->setScale(scaleFactor);
            cell->setResAnim(myAnim);
            //cell->attachTo(_view);
            cell->attachTo(_game->_playground);
            cell->setPosition(Vector2(float(x * squareSize.x), float(y * squareSize.y)));
            cell->setAlpha(50);
            cell->setPriority(1);
            cell->addEventListener(TouchEvent::MOVE, [cell, this](Event*){
                activeCell->setPosition(cell->getPosition());
            });

            // event listener in case of click
            cell->addEventListener(TouchEvent::CLICK, [cell, this, x, y](Event*){
                cell->onClick();
            });//*/
        }
    }
}

void Grid::onEvent(Event* ev)
{

    /*TouchEvent* te = safeCast<TouchEvent*>(ev);

    if (te->type == TouchEvent::MOVE)
    {
        static spSprite old_pix = nullptr;
        //std::cout << "MOVE" << std::endl;

        if(old_pix != NULL){
            old_pix->setScale(1.0f/squareSize.x);
            old_pix->setResAnim(res::ui.getResAnim("simpleSquare"));
        }
        /*spSprite sel_cel = (spSprite)ev->target;
        sel_cel->setScale(1.0f/squareSize.x);
        sel_cel->setResAnim(res::ui.getResAnim("SelectedSimpleSquare"));
    }
    if(te->type == TouchEvent::CLICK)
    {

    }//*/
}

void Grid::create_path(std::vector<Point> points) {
    const ResAnim * myAnim = res::ui.getResAnim("tiled");
    float scale = region_size.x/(myAnim->getSize().x*square_nb);

    for (auto &point : points) {
        spSprite cell = cells[point.y][point.x];
        cell->setResAnim(myAnim);
        cell->setScale(scale);
        cell->setAlpha(50);
        cell->setPriority(1);
    }
}

const std::vector<std::vector<spTower>> &Grid::getCells() const {
    return cells;
}

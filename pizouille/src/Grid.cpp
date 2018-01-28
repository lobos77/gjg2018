//
// Created by foebus on 27.01.18.
//

#include <iostream>
#include "Grid.h"
#include "res.h"
#include "Game.h"
#include "Player.h"
#include "oxygine-framework.h"
#include <iostream>

void Grid::_init() {
    _view->setPosition(0, 0);
    region_size = _game->getSize();
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

    for (int x = 0; x < tiles_nb; x++) {
        for (int y = 0; y < tiles_nb; y++) {
            cells[x].push_back(new Sprite);
            spSprite cell =cells[x][y];
            cell->setScale(scaleFactor);
            cell->setResAnim(myAnim);
            cell->attachTo(_view);
            cell->setPosition(Vector2(float(x * 20), float(y * 20)));
            cell->setAlpha(50);
            cell->setPriority(1);
            cell->addEventListener(TouchEvent::MOVE, [cell, this](Event*){
                static spSprite old_pix = nullptr;
                static const ResAnim * old_anim;
                //std::cout << "MOVE" << std::endl;

                if(old_pix != NULL){
                    old_pix->setScale(region_size.x/(old_anim->getSize().x*square_nb));
                    old_pix->setResAnim(old_anim);
                    //cell->setAlpha(50);
                }
                old_pix = cell;
                old_anim = cell->getResAnim();
                static const ResAnim * my_anim = res::ui.getResAnim("SelectedSimpleSquare");
                cell->setScale(region_size.x/(my_anim->getSize().x*square_nb));
                cell->setResAnim(my_anim);
            });

            // event listener in case of click
            cell->addEventListener(TouchEvent::CLICK, [cell, this,x,y,tiles_nb](Event*){
                static spSprite old_pix = nullptr;
                static const ResAnim * old_anim;

                std::cout << x << "," << y << std::endl;
                Player *player = _game->get_player();

                player->move_to(squareSize.x*x,squareSize.y*y);

                if(old_pix != NULL){
                    old_pix->setScale(region_size.x/(old_anim->getSize().x*square_nb));
                    old_pix->setResAnim(old_anim);
                }
                old_pix = cell;
                old_anim = cell->getResAnim();
                static const ResAnim * my_anim = res::ui.getResAnim("SelectedSimpleSquare");
                cell->setScale(region_size.x/(my_anim->getSize().x*square_nb));
                cell->setResAnim(my_anim);
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

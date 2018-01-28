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
    my_size = 0;
}

void Grid::create(unsigned int size) {

    my_size = size;
    squareSize = region_size/size;
    cells.resize(size);
    const ResAnim * myAnim = res::ui.getResAnim("simpleSquare");

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            cells[x].push_back(new Sprite);
            spSprite cell =cells[x][y];
            cell->setScale(1.2f/squareSize.x);
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
                    old_pix->setScale(old_anim->getScaleFactor());
                    old_pix->setResAnim(old_anim);
                }
                old_pix = cell;
                old_anim = cell->getResAnim();
                cell->setScale(1.2f/squareSize.x);
                cell->setResAnim(res::ui.getResAnim("SelectedSimpleSquare"));
            });

            // event listener in case of click
            cell->addEventListener(TouchEvent::CLICK, [cell, this,x,y,size](Event*){
                static spSprite old_pix = nullptr;
                static const ResAnim * old_anim;
                //std::cout << "MOVE" << std::endl;

                std::cout << x << "," << y << std::endl;
                Player *player = _game->get_player();

                player->move_to(squareSize.length()*x,squareSize.length()*y);

                if(old_pix != NULL){
                    old_pix->setScale(1.0f/squareSize.x);
                    old_pix->setResAnim(old_anim);
                }
                old_pix = cell;
                old_anim = cell->getResAnim();
                cell->setScale(1.0f/squareSize.x);
                cell->setResAnim(res::ui.getResAnim("SelectedSimpleSquare"));
            });//*/
        }
    }
}

void Grid::onEvent(Event* ev)
{

    TouchEvent* te = safeCast<TouchEvent*>(ev);

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
        sel_cel->setResAnim(res::ui.getResAnim("SelectedSimpleSquare"));*/
    }
    if(te->type == TouchEvent::CLICK)
    {

    }
}

void Grid::create_path(std::vector<Point> points) {
    const ResAnim * myAnim = res::ui.getResAnim("tiled");
    float scale = myAnim->getSize().x/my_size*region_size.x;

    for (auto &point : points) {
        spSprite cell = cells[point.y][point.x];
        cell->setScale(scale);
        cell->setResAnim(myAnim);
        cell->setAlpha(100);
    }
}

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
    Vector2 squareSize = region_size/size;
    cells.resize(size);
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            cells[x].push_back(new Sprite);
            spSprite cell =cells[x][y];
            cell->setScale(1.0f/squareSize.x);
            cell->setResAnim(res::ui.getResAnim("simpleSquare"));
            cell->attachTo(_view);
            cell->setPosition(Vector2(float(x * 20), float(y * 20)));
            cell->setAlpha(50);
            cell->addEventListener(TouchEvent::MOVE, [cell, this](Event*){
                static spSprite old_pix = nullptr;
                //std::cout << "MOVE" << std::endl;
                Vector2 squareSize = region_size/my_size;

                if(old_pix != NULL){
                    old_pix->setScale(1.0f/squareSize.x);
                    old_pix->setResAnim(res::ui.getResAnim("simpleSquare"));
                }
                cell->setScale(1.0f/squareSize.x);
                cell->setResAnim(res::ui.getResAnim("SelectedSimpleSquare"));
                old_pix = cell;
            });

            // event listener in case of click
            cell->addEventListener(TouchEvent::CLICK, [cell, this,x,y,size](Event*){
                static spSprite old_pix = nullptr;
                //std::cout << "MOVE" << std::endl;
                Vector2 squareSize = region_size/my_size;

                std::cout << x << "," << y << std::endl;
                Player *player = _game->get_player();

                player->move_to(squareSize.length()*x,squareSize.length()*y);



                if(old_pix != NULL){
                    old_pix->setScale(1.0f/squareSize.x);
                    old_pix->setResAnim(res::ui.getResAnim("simpleSquare"));
                }
                cell->setScale(1.0f/squareSize.x);
                cell->setResAnim(res::ui.getResAnim("SelectedSimpleSquare"));
                old_pix = cell;
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
        Vector2 squareSize = region_size/my_size;

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

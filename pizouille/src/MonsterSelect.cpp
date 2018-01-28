//
// Created by mick on 1/27/18.
//

#include "MonsterSelect.h"
#include "res.h"
#include "Tower.h"
#include <iostream>

MonsterSelect::MonsterSelect(): _pressed(false)
{
    setPosition(Vector2(0,0));
    setVisible(true);
    //setAlpha(100);
    setScale(0.3);

    setResAnim(res::ui.getResAnim("carte_insecte"));
    addEventListener(TouchEvent::MOVE, CLOSURE(this, &MonsterSelect::onEvent));
    addEventListener(TouchEvent::CLICK, CLOSURE(this, &MonsterSelect::onEvent));



    _finger = new Sprite;
    _finger->setResAnim(res::ui.getResAnim("finger"));
    _finger->attachTo(this);
    _finger->setVisible(true);
    _finger->setAnchor(Vector2(0.5f, 0.5f));
    _finger->setTouchEnabled(false);

}

void MonsterSelect::onEvent(Event* ev)
{

    TouchEvent* te = safeCast<TouchEvent*>(ev);

    if (te->type == TouchEvent::MOVE)
    {
        std::cout << "MOVE" << std::endl;
        Vector2 center = getSize() / 2;
        //_finger->setPosition(te->localPosition);
    }
    if(te->type == TouchEvent::CLICK)
    {
        std::cout << "CLICK" << std::endl;
        //spTower tower = new Tower();
        //tower->attachTo(this);
        //tower->setPosition(te->localPosition);
        //tower->setVisible(true);


    }

}

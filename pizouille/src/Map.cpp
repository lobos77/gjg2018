//
// Created by mick on 1/27/18.
//

#include "Map.h"
#include "res.h"
#include <iostream>

Map::Map(): _pressed(false)
{
    setResAnim(res::ui.getResAnim("map"));
    addEventListener(TouchEvent::MOVE, CLOSURE(this, &Map::onEvent));

    _finger = new Sprite;
    _finger->setResAnim(res::ui.getResAnim("finger"));
    _finger->attachTo(this);
    _finger->setVisible(true);
    _finger->setAnchor(Vector2(0.5f, 0.5f));
    _finger->setTouchEnabled(false);

}

void Map::onEvent(Event* ev)
{

    TouchEvent* te = safeCast<TouchEvent*>(ev);

    if (te->type == TouchEvent::MOVE)
    {
        //std::cout << "MOVE" << std::endl;
        Vector2 center = getSize() / 2;
        _finger->setPosition(te->localPosition);
    }
}
#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

class DraggableSprite: public Sprite
{
public:
    DraggableSprite()
    {
        //drag.init(this);
    }
    
    //Draggable drag;
    void onEvent(Event* ev)
    {
        TouchEvent* te = safeCast<TouchEvent*>(ev);
        if (te->type == TouchEvent::TOUCH_DOWN)
        {
            local = te->localPosition;
            _stage->addEventListener(TouchEvent::MOVE, CLOSURE(this, &DraggableSprite::onEvent));
            _stage->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &DraggableSprite::onEvent));
        }
        
        if (te->type == TouchEvent::MOVE)
        {
            move(te->localPosition);
        }
        
        if (te->type == TouchEvent::TOUCH_UP)
        {
            _stage->removeEventListeners(this);
        }
    }
    
    void move(const Vector2& pos)
    {
        Vector2 localPos = stage2local(pos);
        Vector2 offset = localPos - local;
        
        Transform tr = getTransform();
        tr.x = 0;
        tr.y = 0;
        Vector2 p = tr.transform(offset);
        setPosition(getPosition() + p);
    }
    
    void doUpdate(const UpdateState& us)
    {
        pointer_index ind = getPressed();
        if (!ind)
            return;
        PointerState* st = Input::instance.getTouchByIndex(ind);
        move(_stage->parent2local(st->getPosition()));
    }
    
    void onAdded2Stage()
    {
        addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &DraggableSprite::onEvent));
    }
    
    void onRemovedFromStage()
    {
        _stage->removeEventListeners(this);
    }
    
    Vector2 local;
};

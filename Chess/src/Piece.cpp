#include "Piece.h"
#include "Board.h"

using namespace oxygine;

Resources _res;

const Vector2 sizePiece(56, 56);

Piece::Piece() : queue_to_walk(true){}

void Piece::init(int type, int color, int x, int y) {
    
    _res.loadXML("/data/xml/resources.xml");
    _x = x;
    _y = y;
    
    _view = new DraggableSprite;
    _view->setResAnim(_res.getResAnim("pieces"), type, color);
    
    Vector2 center = _view->getSize() / 2;
    center.x = int(center.x);
    center.y = int(center.y);
    _view->setAnchorInPixels(center);
    
    if(color == white) {
        _view->setTouchEnabled(queue_to_walk);
    }
    
    _view->attachTo(getStage());
    _view->setSize(sizePiece.x, sizePiece.y);
    _view->setPosition(x, y);

    _view->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &Piece::onMouseDown));
    _view->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &Piece::onMouseUp));
}

void Piece::onMouseDown(Event* event){
    spActor actor = safeSpCast<Actor>(event->currentTarget);
    
    spTween t = actor->addTween(Sprite::TweenColor(Color::Red), 300, -1, true);
    t->setName("color");
}
void Piece::onMouseUp(Event* event){
    spSprite actor = safeSpCast<Sprite>(event->currentTarget);
    
    spTween t = actor->getTween("color", ep_ignore_error);
    if (t)
        actor->removeTween(t);
    actor->setColor(Color::White);
    
    queue_to_walk = !queue_to_walk;
}

int Piece::_getColor() const {
    return _color;
}

spSprite Piece::_getView() const {
    return _view;
}

void Piece::free() {
    _view->detach();
    _view = 0;
}

void Piece::doUpdate(const UpdateState& us){
}






















/**
This file was automatically generated by oxygine-editor. Don't change it!
*/

#include "Serialize.h"

#include "Sprite.h"
#include "playground.h"
using namespace oxygine;
using namespace pugi;

REGISTER_ACTOR(playground);
void playground::__init()
{    
    field = safeCast<Sprite*>(_findDescendant("field"));    
    pieces = safeCast<Sprite*>(_findDescendant("pieces"));    
};

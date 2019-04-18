/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "RectangleCollider.h"

RectangleCollider::RectangleCollider(Entity381 *entity) :
        Collider(entity){

}

RectangleCollider::~RectangleCollider(){

}

void RectangleCollider::Tick(float dt){

}

bool RectangleCollider::IsColliding() const{
    return false;
}


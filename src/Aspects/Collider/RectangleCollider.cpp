/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "RectangleCollider.h"
#include "CircleCollider.h"

RectangleCollider::RectangleCollider(Entity381 *entity) :
        Collider(entity),
        width(0),
        height(0){

}

RectangleCollider::RectangleCollider(Entity381 *entity, int w, int h) :
        Collider(entity),
        width(w),
        height(h){

}

RectangleCollider::~RectangleCollider(){

}

void RectangleCollider::OnCollision(Collider *other) const{

}

bool RectangleCollider::IsColliding(Collider *other) const{
    CircleCollider *castToCircle = dynamic_cast<CircleCollider *>(other);
    if(castToCircle != NULL){
        //Handle rectangle and circle collision detection
    }

    RectangleCollider *castToRect = dynamic_cast<RectangleCollider *>(other);
    if(castToRect != NULL){
        //Handle rectangle and rectangle collision detection
    }
    return false;
}


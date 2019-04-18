/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "CircleCollider.h"

CircleCollider::CircleCollider(Entity381 *entity) :
        Collider(entity){

}

CircleCollider::~CircleCollider(){

}

void CircleCollider::Tick(float dt){

}

bool CircleCollider::IsColliding() const{
    return false;
}


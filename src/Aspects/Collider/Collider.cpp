/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include <algorithm>
#include "Collider.h"

std::vector<Collider *> Collider::colliders;

Collider::Collider(Entity381 *entity) :
        Aspect(entity){
    colliders.push_back(this);
}

Collider::~Collider(){
    colliders.erase(std::remove(colliders.begin(), colliders.end(), this));
}

void Collider::Tick(float dt){
    for(unsigned int i = 0; i < colliders.size(); ++i){
        if(colliders[i] != this && IsColliding(colliders[i])){
            colliders[i]->OnCollision(this);
        }
    }
}


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
    auto it = std::find(colliders.begin(), colliders.end(), this);
    if(it != colliders.end()){
        colliders[std::distance(colliders.begin(), it)] = NULL;
    }
    std::cout << "Collider removed" << std::endl;
}

void Collider::Tick(float dt){
    const unsigned int size = colliders.size();
    for(unsigned int i = 0; i < size; ++i){
        if(colliders[i] != NULL && colliders[i] != this && IsColliding(colliders[i])){
            colliders[i]->OnCollision(this);
        }
    }
    //Clean up deleted colliders
    if(!colliders.empty()){
        for(int i = colliders.size() - 1; i >= 0; --i){
            if(colliders[i] == NULL){
                colliders.erase(colliders.begin() + i);
            }
        }
    }
}


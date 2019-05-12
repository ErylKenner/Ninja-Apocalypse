/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "Ray.h"
#include "CircleCollider.h"

Ray::Ray(Ogre::Vector2 start, Ogre::Vector2 dir) :
        origin(start),
        directionVector(dir){

}

Ray::Ray(Ogre::Vector3 start, Ogre::Vector2 dir) :
        directionVector(dir){
    origin = Ogre::Vector2(start.x, start.z);
}

Ray::~Ray(){

}

Collider* Ray::GetClosestIntersectedCollider(float *dist) const{
    Collider *closest = NULL;
    float closestDist = Ogre::Math::POS_INFINITY;
    for(unsigned int i = 0; i < Collider::colliders.size(); ++i){
        Collider *cur = Collider::colliders[i];
        if(cur != NULL && !cur->IsTrigger
                && dynamic_cast<PlayerMovableCircleCollider *>(cur) == NULL){
            float dist = Ogre::Math::POS_INFINITY;
            bool collided = cur->GetClosestPoint(*this, &dist);
            if(collided && dist < closestDist){
                closestDist = dist;
                closest = cur;
            }
        }
    }
    if(closest != NULL && dist != NULL){
        *dist = closestDist;
    }
    return closest;
}


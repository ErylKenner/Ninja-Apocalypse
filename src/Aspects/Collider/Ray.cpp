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
    float closestDistSqr = Ogre::Math::POS_INFINITY;
    for(unsigned int i = 0; i < Collider::colliders.size(); ++i){
        Collider *cur = Collider::colliders[i];
        if(!cur->IsTrigger && dynamic_cast<PlayerMovableCircleCollider *>(cur) == NULL){
            Ogre::Vector2 pos;
            bool collided = cur->GetClosestPoint(*this, &pos);
            if(collided){
                float distSqr = origin.squaredDistance(pos);
                if(distSqr < closestDistSqr){
                    closestDistSqr = distSqr;
                    closest = cur;
                }
            }
        }
    }
    if(closest != NULL && dist != NULL){
        *dist = Ogre::Math::Sqrt(closestDistSqr);
    }
    return closest;
}



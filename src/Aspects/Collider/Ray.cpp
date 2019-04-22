/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "Ray.h"

Ray::Ray(){

}

Ray::~Ray(){

}

Collider* Ray::GetIntersectedCollider() const{
    Collider *closest = NULL;
    float closestDistSqr = Ogre::Math::POS_INFINITY;
    for(unsigned int i = 0; i < Collider::colliders.size(); ++i){
        Collider *cur = Collider::colliders[i];
        if(cur->IsColliding(this)){
            Ogre::Vector2 pos = cur->GetClosestPoint(
                    Ogre::Vector3(origin.x, cur->entity381->position.y, origin.y));
            float distSqr = origin.squaredDistance(pos);
            if(distSqr < closestDistSqr){
                closestDistSqr = distSqr;
                closest = cur;
            }
        }
    }
    return closest;
}


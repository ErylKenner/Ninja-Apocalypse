/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Health.h"
#include "Enemy.h"
#include "Player.h"
#include "Ray.h"
#include "WeaponHolder.h"
#include <iostream>

CircleCollider::CircleCollider(Entity381 *entity, int rad) :
        Collider(entity),
        radius(rad){
}

CircleCollider::~CircleCollider(){

}

bool CircleCollider::IsColliding(Collider *other) const{
    CircleCollider *castToCircle = dynamic_cast<CircleCollider *>(other);
    if(castToCircle != NULL){
        Ogre::Vector3 diff = entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(
                entity381->position)
                - castToCircle->entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(
                        castToCircle->entity381->position);
        diff.y = 0;
        float radiusTotal = radius + castToCircle->radius;
        return diff.squaredLength() <= radiusTotal * radiusTotal;
    }

    RectangleCollider *castToRect = dynamic_cast<RectangleCollider *>(other);
    if(castToRect != NULL){
        //Handle circle and rectangle collision detection
    }
    return false;
}

bool CircleCollider::GetClosestPoint(const Ray ray, Ogre::Vector2 *pos) const{
    const Ogre::Vector3 globalPosition =
            entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(entity381->position);
    const Ogre::Vector2 circlePos = Ogre::Vector2(globalPosition.x, globalPosition.z);
    const Ogre::Vector2 diff = circlePos - ray.origin;
    const Ogre::Vector2 projection = (diff.dotProduct(ray.directionVector)
            / ray.directionVector.squaredLength()) * ray.directionVector;
    if(circlePos.squaredDistance(ray.origin + projection) <= radius * radius){
        if(pos != NULL){
            //*pos = Ogre::Vector2(entity381->position.x, entity381->position.z);
            Ogre::Vector3 pos3D = GetClosestPoint(
                    Ogre::Vector3(ray.origin.x, 0, ray.origin.y));
            *pos = Ogre::Vector2(pos3D.x, pos3D.z);
        }
        return true;
    } else{
        pos = NULL;
        return false;
    }
}

Ogre::Vector3 CircleCollider::GetClosestPoint(Ogre::Vector3 point) const{
    const Ogre::Vector3 globalPosition =
                entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(entity381->position);
    const Ogre::Vector3 offset =
            (point - Ogre::Vector3(globalPosition.x, point.y, globalPosition.z)).normalisedCopy();
    return globalPosition + radius * offset;
}

void CircleCollider::OnCollision(Collider *other) const{
}

//--------------------------------------------------------------------
WeaponCollider::WeaponCollider(Entity381 *entity, int rad) :
        CircleCollider(entity, rad){
    IsTrigger = true;
    attachedWeapon = dynamic_cast<Weapon *>(entity381);
    if(attachedWeapon == NULL){
        std::cerr << "WeaponCollider not attached to a Weapon!" << std::endl;
    }
    throwable = entity381->GetAspect<Throwable>();
    if(throwable == NULL){
        std::cerr << "Throwable not attached to a Weapon!" << std::endl;
    }
}
WeaponCollider::~WeaponCollider(){

}

void WeaponCollider::OnCollision(Collider *other) const{
    CircleCollider::OnCollision(other);

    PlayerMovableCircleCollider * castToPlayer =
            dynamic_cast<PlayerMovableCircleCollider *>(other);

    if(!throwable->Thrown){

        if(castToPlayer != NULL){
            WeaponHolder * holder = castToPlayer->entity381->GetAspect<WeaponHolder>();
            if(holder != NULL){
                if(holder->heldWeapon == NULL){
                    holder->SetWeapon(attachedWeapon);
                }
            } else{
                std::cerr << "Player does not have a WeaponHolder Aspect!" << std::endl;
            }
        }
    } else if(!other->IsTrigger && castToPlayer == NULL){
        EnemyMovableCircleCollider * castToEnemy =
                dynamic_cast<EnemyMovableCircleCollider *>(other);
        if(castToEnemy != NULL){
            //Health * enemyHealth = castToEnemy->entity381->GetAspect<Health>();
            Enemy * enemy = static_cast<Enemy *>(castToEnemy->entity381);
            enemy->OnDeath();
        }

        entity381->position = Ogre::Vector3(0, 0, 25e6);
        entity381->GetAspect<Throwable>()->Thrown = false;

    }
}

//--------------------------------------------------------------------

MovableCircleCollider::MovableCircleCollider(Entity381 *entity, int rad) :
        CircleCollider(entity, rad){
}

MovableCircleCollider::~MovableCircleCollider(){

}

void MovableCircleCollider::OnCollision(Collider *other) const{
    if(!other->IsTrigger){
        CircleCollider::OnCollision(other);
        CircleCollider *castToCircle = dynamic_cast<CircleCollider *>(other);
        if(castToCircle != NULL){
            Ogre::Vector3 diff = entity381->position - castToCircle->entity381->position;
            diff.y = 0;
            entity381->position += ((radius + castToCircle->radius) / diff.length() - 1)
                    * diff;
        }

        RectangleCollider *castToRect = dynamic_cast<RectangleCollider *>(other);
        if(castToRect != NULL){
            Ogre::Vector3 diff = entity381->position
                    - castToRect->GetClosestPoint(entity381->position);
            diff.y = 0;
            if(castToRect->PointInRectangle(entity381->position)){
                entity381->position -= diff;
            } else{
                entity381->position += (radius / diff.length() - 1) * diff;
            }
        }
    }

}

//--------------------------------------------------------------------

PlayerMovableCircleCollider::PlayerMovableCircleCollider(Entity381 *entity, int rad) :
        MovableCircleCollider(entity, rad){
}

PlayerMovableCircleCollider::~PlayerMovableCircleCollider(){

}

void PlayerMovableCircleCollider::OnCollision(Collider *other) const{
    MovableCircleCollider::OnCollision(other);

    EnemyMovableCircleCollider *castToEnemy =
            dynamic_cast<EnemyMovableCircleCollider *>(other);
    if(castToEnemy != NULL){
        Player *player = dynamic_cast<Player *>(entity381);
        Enemy *enemy = dynamic_cast<Enemy *>(other->entity381);
        if(player != NULL && enemy != NULL){
            if(!player->GetAspect<Health>()->TakeDamage(enemy->hitDamage)){
                player->OnDeath();
            }
        }
    }
}

//--------------------------------------------------------------------

EnemyMovableCircleCollider::EnemyMovableCircleCollider(Entity381 *entity, int rad) :
        MovableCircleCollider(entity, rad){
}

EnemyMovableCircleCollider::~EnemyMovableCircleCollider(){

}

void EnemyMovableCircleCollider::OnCollision(Collider *other) const{
    RectangleBorderCollider *castToBorder = dynamic_cast<RectangleBorderCollider *>(other);
    if(castToBorder != NULL){

    } else{
        MovableCircleCollider::OnCollision(other);
    }
}


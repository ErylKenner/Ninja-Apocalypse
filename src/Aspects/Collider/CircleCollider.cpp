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
        Ogre::Vector3 diff = entity381->position - castToCircle->entity381->position;
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

bool CircleCollider::IsColliding(const Ray *ray) const{
    const Ogre::Vector2 direction = ray->secondPoint - ray->origin;
    const Ogre::Vector2 diff = ray->origin
            - Ogre::Vector2(entity381->position.x, entity381->position.z);
    const float b = diff.dotProduct(direction);
    return !(b * b < direction.squaredLength() * (diff.squaredLength() - radius * radius));
}

Ogre::Vector3 CircleCollider::GetClosestPoint(Ogre::Vector3 point) const{
    const Ogre::Vector3 offset =
            (point - Ogre::Vector3(entity381->position.x, point.y, entity381->position.z)).normalisedCopy();
    return entity381->position + radius * offset;
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
    MovableCircleCollider::OnCollision(other);

}


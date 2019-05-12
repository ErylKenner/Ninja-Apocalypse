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
#include "BossCollider.h"
#include <iostream>

CircleCollider::CircleCollider(Entity381 *entity, int rad) :
        Collider(entity),
        radius(rad){
}

bool CircleCollider::IsColliding(Collider *other) const{
    CircleCollider *castToCircle = dynamic_cast<CircleCollider *>(other);
    if(castToCircle != NULL){
        Ogre::Vector3 diff =
                entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(
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

bool CircleCollider::GetClosestPoint(const Ray ray, float *dist) const{
    const Ogre::Vector3 globalPosition =
            entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(
                    entity381->position);
    const Ogre::Vector2 diff = Ogre::Vector2(globalPosition.x, globalPosition.z)
            - ray.origin;
    const double a = ray.directionVector.squaredLength();
    const double b = 2 * (ray.directionVector).dotProduct(diff);
    const double c = diff.squaredLength() - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if(discriminant >= 0){
        if(dist != NULL){
            double t = (2 * c) / (b + Ogre::Math::Sqrt(discriminant));
            if(t >= 0){
                *dist = t * Ogre::Math::Sqrt(a);
                return true;
            }
        }
    }
    if(dist != NULL){
        *dist = Ogre::Math::POS_INFINITY;
    }
    return false;
}

Ogre::Vector3 CircleCollider::GetClosestPoint(Ogre::Vector3 point) const{
    const Ogre::Vector3 globalPosition =
            entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(
                    entity381->position);
    const Ogre::Vector3 offset = point
            - Ogre::Vector3(globalPosition.x, point.y, globalPosition.z);
    return globalPosition + radius * offset.normalisedCopy();
}

bool CircleCollider::Contains(Ogre::Vector3 centerPoint) const{
    const Ogre::Vector3 globalPosition =
            entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(
                    entity381->position);
    Ogre::Vector2 diff = Ogre::Vector2(centerPoint.x - globalPosition.x,
            centerPoint.z - globalPosition.z);
    return diff.squaredLength() <= radius * radius;
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

void WeaponCollider::OnCollision(Collider *other) const{
    CircleCollider::OnCollision(other);

    PlayerMovableCircleCollider * castToPlayer =
            dynamic_cast<PlayerMovableCircleCollider *>(other);
    if(!throwable->Thrown && castToPlayer != NULL){
        WeaponHolder *holder = castToPlayer->entity381->GetAspect<WeaponHolder>();
        if(holder != NULL){
            if(holder->heldWeapon == NULL){
                holder->SetWeapon(attachedWeapon);
            }
        } else{
            std::cerr << "Player does not have a WeaponHolder Aspect!" << std::endl;
        }
    }
}

//--------------------------------------------------------------------

MovableCircleCollider::MovableCircleCollider(Entity381 *entity, int rad) :
        CircleCollider(entity, rad){
}

void MovableCircleCollider::OnCollision(Collider *other) const{
    if(!other->IsTrigger){
        CircleCollider::OnCollision(other);
        CircleCollider *castToCircle = dynamic_cast<CircleCollider *>(other);
        Ogre::Vector3 globalPosition =
                entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(
                        entity381->position);
        if(castToCircle != NULL){
            Ogre::Vector3 diff =
                    globalPosition
                            - castToCircle->entity381->ogreSceneNode->getParent()->convertLocalToWorldPosition(
                                    castToCircle->entity381->position);
            diff.y = 0;
            const float dist = diff.length();
            if(dist <= 0.0001){
                entity381->position +=
                        entity381->ogreSceneNode->getParent()->convertWorldToLocalPosition(
                                Ogre::Vector3(0, 0, radius + castToCircle->radius));
            } else{
                entity381->position +=
                        entity381->ogreSceneNode->getParent()->convertWorldToLocalPosition(
                                ((radius + castToCircle->radius) / dist - 1) * diff);
            }
        }

        RectangleCollider *castToRect = dynamic_cast<RectangleCollider *>(other);
        if(castToRect != NULL){
            Ogre::Vector3 diff = globalPosition
                    - castToRect->GetClosestPoint(globalPosition);
            diff.y = 0;
            const float dist = diff.length();
            if(castToRect->Contains(globalPosition)){
                entity381->position -=
                        entity381->ogreSceneNode->getParent()->convertWorldToLocalPosition(
                                diff);
            } else if(dist >= 0.0001){
                entity381->position +=
                        entity381->ogreSceneNode->getParent()->convertWorldToLocalPosition(
                                (radius / dist - 1) * diff);
            }
        }
    }

}

//--------------------------------------------------------------------

PlayerMovableCircleCollider::PlayerMovableCircleCollider(Entity381 *entity, int rad) :
        MovableCircleCollider(entity, rad){
}

void PlayerMovableCircleCollider::OnCollision(Collider *other) const{

    EnemyMovableCircleCollider *castToEnemy =
            dynamic_cast<EnemyMovableCircleCollider *>(other);
    if(castToEnemy == NULL){
        MovableCircleCollider::OnCollision(other);
    } else{
        Player *player = dynamic_cast<Player *>(entity381);
        Enemy *enemy = dynamic_cast<Enemy *>(other->entity381);
        if(player != NULL && enemy != NULL){
            if(!player->GetAspect<Health>()->TakeDamage(enemy->hitDamage)){
                player->OnDeath();
            }
        }
    }

    BossLimbRectangleCollider * limbCol = dynamic_cast<BossLimbRectangleCollider *>(other);

    if(limbCol != NULL){
        Player *player = static_cast<Player *>(entity381);
        if(!player->GetAspect<Health>()->TakeDamage(limbCol->damageAmount)){
            player->OnDeath();
        }
    }
}

//--------------------------------------------------------------------

EnemyMovableCircleCollider::EnemyMovableCircleCollider(Entity381 *entity, int rad) :
        MovableCircleCollider(entity, rad){
}

void EnemyMovableCircleCollider::OnCollision(Collider *other) const{
    RectangleBorderCollider *castToBorder = dynamic_cast<RectangleBorderCollider *>(other);
    EnemyMovableCircleCollider *castToEnemy =
            dynamic_cast<EnemyMovableCircleCollider *>(other);
    if(castToBorder == NULL && castToEnemy == NULL){
        MovableCircleCollider::OnCollision(other);
    }

    WeaponCollider *castToWeapon = dynamic_cast<WeaponCollider *>(other);
    if(castToWeapon != NULL){
        Throwable *throwable = castToWeapon->entity381->GetAspect<Throwable>();
        if(throwable != NULL && throwable->Thrown){
            Enemy * enemy = static_cast<Enemy *>(entity381);
            if(!enemy->GetAspect<Health>()->TakeDamage(
                    castToWeapon->attachedWeapon->ThrownDamageAmount)){
                enemy->OnDeath();
            }
            castToWeapon->entity381->position = Ogre::Vector3(0, 0, 25e6);
            castToWeapon->entity381->GetAspect<Throwable>()->Thrown = false;
        }
    }
}


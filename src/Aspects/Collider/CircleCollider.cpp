/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Health.h"
#include "Enemy.h"
#include "Player.h"
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

void CircleCollider::OnCollision(Collider *other) const{
}

//--------------------------------------------------------------------

MovableCircleCollider::MovableCircleCollider(Entity381 *entity, int rad) :
        CircleCollider(entity, rad){
}

MovableCircleCollider::~MovableCircleCollider(){

}

void MovableCircleCollider::OnCollision(Collider *other) const{
    CircleCollider::OnCollision(other);
    CircleCollider *castToCircle = dynamic_cast<CircleCollider *>(other);
    if(castToCircle != NULL){
        //Fix entity's position for circle to circle collision
        Ogre::Vector3 diff = entity381->position - castToCircle->entity381->position;
        diff.y = 0;
        entity381->position += ((radius + castToCircle->radius) / diff.length() - 1)
                * diff;
    }

    RectangleCollider *castToRect = dynamic_cast<RectangleCollider *>(other);
    if(castToRect != NULL){
        //Fix entity's position for circle to rectangle collision
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

    EnemyMovableCircleCollider *castToEnemy = dynamic_cast<EnemyMovableCircleCollider *>(other);
    if(castToEnemy != NULL){
        Player *player = dynamic_cast<Player *>(entity381);
        Enemy *enemy = dynamic_cast<Enemy *>(other->entity381);
        if(player != NULL && enemy != NULL){
            if(!player->GetAspect<Health>()->TakeDamage(enemy->hitDamage)){
                player->OnDeath();
            }
            std::cout << "Player health: " << player->GetAspect<Health>()->CurrentHealth << std::endl;
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


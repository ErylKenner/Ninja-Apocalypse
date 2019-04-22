/*
 * Player.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: kylebrain
 */

#include "Player.h"
#include "Renderable.h"
#include "Health.h"
#include "CameraTether.h"
#include "Animation.h"
#include "CircleCollider.h"
#include "WeaponHolder.h"

Player::Player(float speed, Ogre::SceneNode * camera, int id, Vector3 pos, Engine * eng) :
        Entity381(id, "ninja.mesh", pos, eng),
        Speed(speed){
    aspects.push_back(new Health(this, 100, 25));
    anim = new Animation(this);
    aspects.push_back(anim);
    aspects.push_back(new CameraTether(this, 1000, camera));
    aspects.push_back(new WeaponHolder(this));
    aspects.push_back(new PlayerMovableCircleCollider(this, 50));
    aspects.push_back(new Renderable(this, 90));
}
Player::~Player(){
}
void Player::InitAspects(){
    // should deprecate this function
}

void Player::LookAt(Vector3 pos){
    pos.y = position.y;
    ogreSceneNode->lookAt(pos, Ogre::Node::TS_WORLD);
}
void Player::Move(Vector3 direction, float dt){
    direction.normalise();
    position += Speed * direction * dt;
    if(direction != Vector3::ZERO){
        if(anim->GetAnimationName() != walkAnimName){
            anim->SetAnimation(walkAnimName, true, walkAnimSpeed);
        }
    } else{
        if(anim->GetAnimationName() != idleAnimName){
            anim->SetAnimation(idleAnimName, true, 1);
        }
    }
}

void Player::OnDeath(){
    engine->keepRunning = false;
}

float Player::GetCurrentAngle() {
    return ogreSceneNode->getOrientation().getYaw().valueDegrees()
            + GetAspect<Renderable>()->AngleOffset;
}

/*
 void Player::OnCollisionCallback(Collider *other){
 std::cout << "Circle1 had " << (dynamic_cast<CircleCollider *>(other) == NULL ? "Rectangle1" : "Circle2") << " collide with it"
 << std::endl;
 }*/


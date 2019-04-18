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

Player::Player(float speed, Ogre::SceneNode * camera, int id, Vector3 pos,
		EntityMgr *entMgr) :
		Entity381(id, "ninja.mesh", pos, entMgr), Speed(speed) {
	animState = ogreEntity->getAnimationState("Idle3");
	animState->setLoop(true);
	animState->setEnabled(true);
	Player::InitAspects();
	aspects.push_back(new CameraTether(this, 1000, camera));
}
Player::~Player() {
}
void Player::InitAspects() {
	aspects.push_back(new Renderable(this));
	aspects.push_back(new Health(this));
}

void Player::LookAt(Vector3 pos) {
	pos.y = position.y;
	ogreSceneNode->lookAt(pos, Ogre::Node::TS_WORLD);
}
void Player::Move(Vector3 direction, float dt) {
	direction.normalise();
	position += Speed * direction * dt;
	if (direction != Vector3::ZERO) {
		animState = ogreEntity->getAnimationState("Walk");
		animState->addTime(1.5f * dt);
	} else {
		animState = ogreEntity->getAnimationState("Idle3");
		animState->addTime(dt);
	}

	animState->setLoop(true);
	animState->setEnabled(true);

	//std::cout << direction << std::endl;
}


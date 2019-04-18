/*
 * CameraTether.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: kylebrain
 */

#include "CameraTether.h"
#include "Entity381.h"

using Ogre::Vector3;

CameraTether::CameraTether(Entity381 * entity, float height,
		Ogre::SceneNode * camNode) :
		Aspect(entity), Height(height) {
	SetCameraNode(camNode);
}
CameraTether::~CameraTether() {
}

void CameraTether::Tick(float dt) {
	SetCameraPosition();
}

void CameraTether::SetCameraNode(Ogre::SceneNode * camNode) {
	CameraNode = camNode;
	if (CameraNode != NULL) {
		SetCameraPosition();
		CameraNode->resetOrientation();
		CameraNode->pitch(Ogre::Degree(-90), Ogre::Node::TS_WORLD);

	} else {
		//std::cerr << "Passed CamNode to CameraTether SetCameraNode was NULL!" << std::endl;
	}
}

void CameraTether::SetCameraPosition() {
	Vector3 newPosition = entity381->position;
	newPosition.y += Height;
	CameraNode->setPosition(newPosition);
}


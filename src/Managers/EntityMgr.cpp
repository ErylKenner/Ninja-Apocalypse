/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "EntityMgr.h"
#include "Player.h"
#include "Engine.h"
#include "GfxMgr.h"

EntityMgr::EntityMgr(Engine *eng) :
		Mgr(eng), currentEntity(0) {
}

EntityMgr::~EntityMgr() {

}

void EntityMgr::Init() {

}

void EntityMgr::Tick(float dt) {
	for (unsigned int i = 0; i < entities.size(); ++i) {
		entities[i]->Tick(dt);
		entities[i]->ogreSceneNode->showBoundingBox(entities[i]->isSelected);
	}
}

Entity381* EntityMgr::CreateEntityOfTypeAtPosition(EntityType type,
		Ogre::Vector3 pos) {
	int id = entities.size();
	if (type == EntityType::Sphere) {
		Entity381 *newEntity = new SphereEntity381(id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else if (type == EntityType::Cube) {
		Entity381 *newEntity = new CubeEntity381(id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else if (type == EntityType::DDG51) {
		Entity381 *newEntity = new DDG51Entity381(id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else if (type == EntityType::CVN68) {
		Entity381 *newEntity = new CVN681Entity381(id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else if (type == EntityType::Alienship) {
		Entity381 *newEntity = new AlienEntity381(id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else if (type == EntityType::Cigarette) {
		Entity381 *newEntity = new CigaretteEntity381(id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else if (type == EntityType::Sailboat) {
		Entity381 *newEntity = new SailboatEntity381(id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else if (type == EntityType::Banshee) {
		Entity381 *newEntity = new BansheeEntity381(id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else if (type == EntityType::PlayerType) {
		Entity381 *newEntity = new Player(400, engine->gfxMgr->mCameraNode, id, pos, this);
		entities.push_back(newEntity);
		return newEntity;
	} else {
		return NULL;
	}
}

void EntityMgr::LoadLevel() {

}

void EntityMgr::Stop() {

}


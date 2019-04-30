/*
 * Boss.cpp
 *
 *  Created on: Apr 29, 2019
 *      Author: kylebrain
 */

#include "Boss.h"
#include "Health.h"
#include "OrientedPhysics3D.h"
#include "UnitAI.h"
#include "Renderable.h"

Boss::Boss(int id, std::string meshName, Ogre::Vector3 sca, Ogre::Vector3 pos, std::string bossName, int health,
           float accel, float turning, float maxSp, Engine * eng) : Entity381(id, meshName, pos, eng), name(bossName) {
    scale = sca;
    aspects.push_back(new Health(this, health, -1));
    aspects.push_back(new UnitAI(this));
    aspects.push_back(new OrientedPhysics3D(this, accel, turning, maxSp));
    aspects.push_back(new Renderable(this));
}
Boss::~Boss(){

}


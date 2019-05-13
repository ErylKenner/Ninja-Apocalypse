/*
 * WeaponManager.h
 *
 *  Created on: Apr 28, 2019
 *      Author: kylebrain
 */

#ifndef INC_MANAGERS_WEAPONMGR_H_
#define INC_MANAGERS_WEAPONMGR_H_

#include "Mgr.h"
#include "OgreVector3.h"

class Weapon;

class WeaponSpawnPoint{
public:
    Weapon * spawnedWeapon;
    Ogre::Vector3 position;
    float respawnCooldown;

    WeaponSpawnPoint(Ogre::Vector3 pos, float coolDown, Engine * eng);

    void Tick(float dt);
    void ClearWeapon();

private:
    void SpawnWeapon();
    Engine * engine;
    float currentTimer;
};

class WeaponMgr : public Mgr{
public:
    WeaponMgr(Engine *eng);
    ~WeaponMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();

    std::vector<WeaponSpawnPoint *> spawnPoints;
    float weaponCooldown;
};

#endif /* INC_MANAGERS_WEAPONMGR_H_ */

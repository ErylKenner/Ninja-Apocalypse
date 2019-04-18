/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include <vector>
#include "OgreSceneManager.h"
#include <OgreAxisAlignedBox.h>

#include "Entity381.h"
#include "Mgr.h"
#include "Player.h"

enum EntityType{
    Sphere, Cube, PlayerType
};

class EntityMgr : public Mgr{
public:
    EntityMgr(Engine *eng);
    ~EntityMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();

    Entity381* CreateEntityOfTypeAtPosition(EntityType type, Ogre::Vector3 pos);

    std::vector<Entity381*> entities;
    int currentEntity;
private:

};

#endif /* INC_ENTITYMGR_H_ */

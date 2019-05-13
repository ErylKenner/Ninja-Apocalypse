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
    Sphere,
    Rectangle,
    TerrainSphere2,
    TerrainRectangle2,
    PlayerType,
    EnemyType,
    HandgunType,
    FirstBossType,
    TerrainRectangle,
    TerrainSphere,
    TerrainBorder
};

class EntityMgr : public Mgr{
public:
    EntityMgr(Engine *eng);
    ~EntityMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();

    void RemoveEntity(Entity381 *entity);
    void RemoveAllEnemies();

    Entity381* CreateEntity(EntityType type, Ogre::Vector3 pos, Ogre::Vector3 scale =
                                    Ogre::Vector3(1, 1, 1));

    std::vector<Entity381*> entities;
    int currentEntity;
private:

};

#endif /* INC_ENTITYMGR_H_ */

/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_MANAGERS_AIMGR_H_
#define INC_MANAGERS_AIMGR_H_

#include "Mgr.h"
#include "OgreVector2.h"
#include "OgreVector3.h"

class AiMgr : public Mgr{
public:
    AiMgr(Engine *eng);
    ~AiMgr();

    void Init();
    void Tick(float dt);
    void LoadLevel();
    void Stop();
    int GetClosestNode(Ogre::Vector2 point) const;
    int GetClosestNode(Ogre::Vector3 point) const;

    int numNodes;
    std::vector<Ogre::Vector2> nodes;
    std::vector<std::vector<int>> ShortestPathTrees;
private:
    std::vector<std::vector<int>> adjacenyList;
    std::vector<int> GenerateShortestPathTree(int targetNode) const;
};

#endif /* INC_MANAGERS_AIMGR_H_ */

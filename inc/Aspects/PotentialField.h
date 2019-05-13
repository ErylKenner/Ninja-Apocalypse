/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_POTENTIALFIELD_H_
#define INC_ASPECTS_POTENTIALFIELD_H_

#include "Aspect.h"
#include <vector>

enum PotentialFieldType{
    PlayerTarget, Obstacle, Enemy
};

class PotentialField : public Aspect{
public:
    PotentialField(Entity381 *ent, PotentialFieldType t);
    ~PotentialField();
    void Tick(float dt);

    static double c_Enemy_Enemy_repulsion;
    static double e_Enemy_Enemy_repulsion;
    static double c_Enemy_Enemy_attraction;
    static double e_Enemy_Enemy_attraction;

    static double c_Enemy_Target_repulsion;
    static double e_Enemy_Target_repulsion;
    static double c_Enemy_Target_attraction;
    static double e_Enemy_Target_attraction;

    static double c_Enemy_Player_repulsion;
    static double e_Enemy_Player_repulsion;
    static double c_Enemy_Player_attraction;
    static double e_Enemy_Player_attraction;

    static double c_Enemy_Obstacle_repulsion;
    static double e_Enemy_Obstacle_repulsion;
    static double c_Enemy_Obstacle_attraction;
    static double e_Enemy_Obstacle_attraction;

    PotentialFieldType type;
    bool enabled;
    int lastVisitedNode;
    static std::vector<PotentialField *> potentialFields;
private:
    Ogre::Vector2 NodeInfluence(Ogre::Vector2 pos);
};

#endif /* INC_ASPECTS_POTENTIALFIELD_H_ */

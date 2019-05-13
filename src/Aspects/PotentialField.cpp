/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include <OrientedPhysics.h>
#include "PotentialField.h"
#include "OgreVector2.h"
#include "Collider.h"
#include "Entity381.h"
#include "AiMgr.h"
#include "GameMgr.h"
#include <algorithm>

double PotentialField::c_Enemy_Enemy_repulsion = 80000000/*1000000*/;
double PotentialField::e_Enemy_Enemy_repulsion = -3.5/*-2.8*/;
double PotentialField::c_Enemy_Enemy_attraction = 0;
double PotentialField::e_Enemy_Enemy_attraction = 1;

double PotentialField::c_Enemy_Player_repulsion = 0;
double PotentialField::e_Enemy_Player_repulsion = 1;
double PotentialField::c_Enemy_Player_attraction = /*100*/10000;
double PotentialField::e_Enemy_Player_attraction = /*0*/-1;

double PotentialField::c_Enemy_Target_repulsion = 0;
double PotentialField::e_Enemy_Target_repulsion = 1;
double PotentialField::c_Enemy_Target_attraction = 2000;
double PotentialField::e_Enemy_Target_attraction = -0.5;

double PotentialField::c_Enemy_Obstacle_repulsion = 50000;
double PotentialField::e_Enemy_Obstacle_repulsion = -1.6;
double PotentialField::c_Enemy_Obstacle_attraction = 0;
double PotentialField::e_Enemy_Obstacle_attraction = 1;

std::vector<PotentialField *> PotentialField::potentialFields;

PotentialField::PotentialField(Entity381 *ent, PotentialFieldType t) :
        Aspect(ent),
        type(t),
        enabled(true),
        lastVisitedNode(-1){
    potentialFields.push_back(this);
}

PotentialField::~PotentialField(){
    potentialFields.erase(
            std::remove(potentialFields.begin(), potentialFields.end(), this),
            potentialFields.end());
}

Ogre::Vector2 PotentialField::NodeInfluence(Ogre::Vector2 pos){
    const int radiusThreshold = 200;
    Ogre::Vector2 ret = Ogre::Vector2::ZERO;
    AiMgr *ai = entity381->engine->aiMgr;

    Ogre::Vector2 mainPlayerPos = Ogre::Vector2(
            entity381->engine->gameMgr->MainPlayer->position.x,
            entity381->engine->gameMgr->MainPlayer->position.z);
    const int closestNode = ai->GetClosestNode(pos);
    const int closestPlayerNode = ai->GetClosestNode(mainPlayerPos);

    const double closestNodeDistance = pos.distance(ai->nodes[closestNode]);
    const double closestNodePlayerDistance = mainPlayerPos.distance(
            ai->nodes[closestNode]);
    int parent = ai->ShortestPathTrees[closestPlayerNode][closestNode];
    const double parentDistance = pos.distance(ai->nodes[parent]);

    if(pos.distance(mainPlayerPos) > closestNodePlayerDistance
            || closestNodeDistance > closestNodePlayerDistance){
        //Go to closest node rather than straight to player
        double c_rep = PotentialField::c_Enemy_Target_repulsion;
        double e_rep = PotentialField::e_Enemy_Target_repulsion;
        double c_attr = PotentialField::c_Enemy_Target_attraction;
        double e_attr = PotentialField::e_Enemy_Target_attraction;
        if(closestNodeDistance > radiusThreshold && lastVisitedNode != closestNode){
            //Go to closestNode
            const double attr = c_attr * Ogre::Math::Pow(closestNodeDistance, e_attr);
            const double rep = c_rep * Ogre::Math::Pow(closestNodeDistance, e_rep);
            ret = (rep - attr) * (pos - ai->nodes[closestNode]).normalisedCopy();
        } else if(parent != closestNode){
            lastVisitedNode = closestNode;
            //Go to parent of closestNode
            const double attr = c_attr * Ogre::Math::Pow(parentDistance, e_attr);
            const double rep = c_rep * Ogre::Math::Pow(parentDistance, e_rep);
            ret = (rep - attr) * (pos - ai->nodes[parent]).normalisedCopy();
        } else{
            lastVisitedNode = closestNode;
        }
    } else{
        lastVisitedNode = closestNode;
    }
    return ret;
}

void PotentialField::Tick(float dt){
    if(type != PotentialFieldType::Enemy){
        return;
    }
    Ogre::Vector2 vectorSum = Ogre::Vector2::ZERO;
    const Ogre::Vector2 pos = Ogre::Vector2(entity381->position.x, entity381->position.z);

    vectorSum += NodeInfluence(pos);

    double c_rep = 0;
    double e_rep = 0;
    double c_attr = 0;
    double e_attr = 0;
    for(unsigned int i = 0; i < potentialFields.size(); ++i){
        PotentialField *cur = potentialFields[i];
        Ogre::Vector2 curPos = Ogre::Vector2(cur->entity381->position.x,
                cur->entity381->position.z);
        if(cur == this || !cur->enabled){
            continue;
        }

        Ogre::Vector2 diff;
        Ogre::Vector3 temp;
        Collider* collider;
        switch(cur->type) {
            case PotentialFieldType::PlayerTarget:
                c_rep = PotentialField::c_Enemy_Player_repulsion;
                e_rep = PotentialField::e_Enemy_Player_repulsion;
                c_attr = PotentialField::c_Enemy_Player_attraction;
                e_attr = PotentialField::e_Enemy_Player_attraction;
                diff = pos - curPos;
                break;
            case PotentialFieldType::Obstacle:
                c_rep = PotentialField::c_Enemy_Obstacle_repulsion;
                e_rep = PotentialField::e_Enemy_Obstacle_repulsion;
                c_attr = PotentialField::c_Enemy_Obstacle_attraction;
                e_attr = PotentialField::e_Enemy_Obstacle_attraction;
                collider = cur->entity381->GetAspect<Collider>();
                if(collider != NULL){
                    temp = collider->GetClosestPoint(entity381->position);
                    diff = pos - Ogre::Vector2(temp.x, temp.z);
                } else{
                    diff = pos - curPos;
                }
                break;
            case PotentialFieldType::Enemy:
                c_rep = PotentialField::c_Enemy_Enemy_repulsion;
                e_rep = PotentialField::e_Enemy_Enemy_repulsion;
                c_attr = PotentialField::c_Enemy_Enemy_attraction;
                e_attr = PotentialField::e_Enemy_Enemy_attraction;
                diff = pos - curPos;
                break;
        }
        const double d = diff.length();
        if(d >= 100.0 && cur->type == PotentialFieldType::Enemy){
            continue;
        }
        const double attr = c_attr * Ogre::Math::Pow(d, e_attr);
        const double rep = c_rep * Ogre::Math::Pow(d, e_rep);
        vectorSum += (rep - attr) * diff.normalisedCopy();
    }

    //std::cout << vectorSum << " ";
    OrientedPhysics *physics = entity381->GetAspect<OrientedPhysics>();
    if(physics != NULL){
        if(vectorSum != Ogre::Vector2::ZERO){
            physics->desiredHeading = Ogre::Degree(
                    Ogre::Math::ATan2(vectorSum.y, vectorSum.x)).valueDegrees();
            float angleDiff = physics->desiredHeading - physics->heading;
            if(angleDiff < 0){
                angleDiff += 360;
            }
            if(angleDiff > 180){
                angleDiff = 360 - angleDiff;
            }
            physics->desiredSpeed = physics->maxSpeed * (1.5 - angleDiff / 180);
        } else{
            physics->desiredSpeed = 0;
        }
    }
}


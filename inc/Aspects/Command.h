/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <OgreVector3.h>

class Entity381;
class UnitAI;
class OrientedPhysics3D;

class Command{
public:
    Command(Entity381* ent);
    virtual ~Command();

    virtual void Init() = 0;
    virtual void Tick(float dt) = 0;
    virtual bool Done() = 0;
    virtual void Finish() = 0;

    Entity381 *entity;
protected:
    UnitAI *unitAI;
    OrientedPhysics3D *orientedPhysics3D;
private:
};

class MoveTo : public Command{
public:
    MoveTo(Entity381* ent, Ogre::Vector3 location);
    ~MoveTo();

    virtual void Init() override;
    virtual void Tick(float dt) override;
    virtual bool Done() override;
    virtual void Finish() override;

    Ogre::Vector3 targetLocation;
    float moveDistanceThreshold = 30;
};

class Intercept : public Command{
public:
    Intercept(Entity381 *ent, Entity381 *target);
    ~Intercept();

    virtual void Init() override;
    virtual void Tick(float dt) override;
    virtual bool Done() override;
    virtual void Finish() override;

    Entity381 *targetObject;
    float moveDistanceThreshold = 130;
};

#endif /* COMMAND_H_ */

/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_COLLIDER_H_
#define INC_ASPECTS_COLLIDER_H_

#include <vector>
#include "Aspect.h"
#include <functional>
#include "Entity381.h"

class Ray;

class Collider : public Aspect{
public:
    Collider(Entity381 *entity);
    ~Collider();
    void Tick(float dt);

    virtual bool IsColliding(Collider *other) const = 0;
    virtual bool IsColliding(const Ray *ray) const = 0;
    virtual void OnCollision(Collider *other) const = 0;
    virtual Ogre::Vector3 GetClosestPoint(Ogre::Vector3 point) const = 0;

    static std::vector<Collider *> colliders;
protected:

private:
};

#endif /* INC_ASPECTS_COLLIDER_H_ */

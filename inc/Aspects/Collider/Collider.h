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

class Collider : public Aspect{
public:
    Collider(Entity381 *entity);
    ~Collider();
    void Tick(float dt);

    virtual bool IsColliding(Collider *other) const = 0;
    virtual void OnCollision(Collider *other) const = 0;

    bool IsTrigger = false;
protected:
    static std::vector<Collider *> colliders;
private:
};

#endif /* INC_ASPECTS_COLLIDER_H_ */

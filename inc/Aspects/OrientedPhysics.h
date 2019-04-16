/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_ORIENTEDPHYSICS_H_
#define INC_ASPECTS_ORIENTEDPHYSICS_H_

#include "Aspect.h"

class OrientedPhysics : public Aspect{
public:
    OrientedPhysics(Entity381 *entity);
    ~OrientedPhysics();
    void Tick(float dt);
protected:
    void UpdateOrientation(float dt);
private:
};

#endif /* INC_ASPECTS_ORIENTEDPHYSICS_H_ */

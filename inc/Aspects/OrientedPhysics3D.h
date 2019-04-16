/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_ORIENTEDPHYSICS3D_H_
#define INC_ASPECTS_ORIENTEDPHYSICS3D_H_

#include "Aspect.h"
#include "OrientedPhysics.h"

class OrientedPhysics3D : public OrientedPhysics{
public:
    OrientedPhysics3D(Entity381 *entity);
    ~OrientedPhysics3D();
    void Tick(float dt);
private:
};

#endif /* INC_ASPECTS_ORIENTEDPHYSICS3D_H_ */

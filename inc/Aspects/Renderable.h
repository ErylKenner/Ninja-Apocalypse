/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_RENDERABLE_H_
#define INC_ASPECTS_RENDERABLE_H_

#include "Aspect.h"

class Renderable : public Aspect{
public:
    Renderable(Entity381 *entity, float angleOff = 0);
    ~Renderable();
    void Tick(float dt);
    float AngleOffset;
private:
};

#endif /* INC_ASPECTS_RENDERABLE_H_ */

/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_ROTATOR_H_
#define INC_ASPECTS_ROTATOR_H_

#include "Aspect.h"

class Rotator : public Aspect{
public:
    Rotator(Entity381 *entity);
    ~Rotator();
    void Tick(float dt);
private:
};

#endif /* INC_ASPECTS_ROTATOR_H_ */

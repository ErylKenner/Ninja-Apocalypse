/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_POTENTIALFIELD_H_
#define INC_ASPECTS_POTENTIALFIELD_H_

#include "Aspect.h"

class PotentialField : Aspect{
public:
    PotentialField(Entity381 *ent, float c, float e);
    ~PotentialField();

    float constant;
    float exponent;
private:
};

#endif /* INC_ASPECTS_POTENTIALFIELD_H_ */

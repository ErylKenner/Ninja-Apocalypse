/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "PotentialField.h"

PotentialField::PotentialField(Entity381 *ent, float c, float e) :
        Aspect(ent),
        constant(c),
        exponent(e){
}

PotentialField::~PotentialField(){

}


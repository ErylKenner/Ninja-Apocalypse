/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_UNITAI_H_
#define INC_ASPECTS_UNITAI_H_

#include <list>

#include "Aspect.h"
#include "Command.h"

class UnitAI : public Aspect{
public:
    UnitAI(Entity381 *entity);
    ~UnitAI();
    void Tick(float dt);

    void SetCommand(Command *c);
    void AddCommand(Command *c);
    int NumCommands() const;

    std::list<Command*> commands;
protected:
private:
};

#endif /* INC_ASPECTS_UNITAI_H_ */

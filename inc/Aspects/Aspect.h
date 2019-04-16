/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECT_H_
#define INC_ASPECT_H_

class Entity381;

class Aspect{
public:
    Aspect(Entity381 *entity);
    virtual ~Aspect();
    virtual void Tick(float dt) = 0;
    Entity381 *entity381;
private:
};

#endif /* INC_ASPECT_H_ */

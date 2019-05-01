/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#ifndef INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_
#define INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_

#include "Collider.h"

class RectangleCollider : public Collider{
public:
    RectangleCollider(Entity381 *entity, int w, int l);
    ~RectangleCollider();

    virtual void OnCollision(Collider *other) const;
    virtual bool IsColliding(Collider *other) const;
    virtual bool GetClosestPoint(const Ray ray, float *dist) const;
    virtual Ogre::Vector3 GetClosestPoint(Ogre::Vector3 point) const;
    virtual bool Contains(Ogre::Vector3 centerPoint) const;
protected:
    int width;
    int length;

    Ogre::Vector2 GetTopLeft() const;
    Ogre::Vector2 GetTopRight() const;
    Ogre::Vector2 GetBottomLeft() const;
    Ogre::Vector2 GetBottomRight() const;

    Ogre::Vector2 RotateVectorClockwise(Ogre::Vector2 original, float radAngle) const;

    static Ogre::Vector2 ClosestPoint(Ogre::Vector2 centerPoint, Ogre::Vector2 A,
                                      Ogre::Vector2 B);
    static bool InsideRectangle(Ogre::Vector2 p, Ogre::Vector2 topLeft,
                                Ogre::Vector2 topRight, Ogre::Vector2 bottomLeft);
    static bool IntersectsCircle(Ogre::Vector2 centerPoint, int radius, Ogre::Vector2 A,
                                 Ogre::Vector2 B);
    static bool RayLineIntersection(Ray ray, Ogre::Vector2 A, Ogre::Vector2 B,
                                    float *intersectDist);
private:
};

class RectangleBorderCollider : public RectangleCollider{
public:
    RectangleBorderCollider(Entity381 *entity, int w, int l);
    ~RectangleBorderCollider();

    virtual void OnCollision(Collider *other) const;
private:
};

#endif /* INC_ASPECTS_COLLIDER_RECTANGLECOLLIDER_H_ */

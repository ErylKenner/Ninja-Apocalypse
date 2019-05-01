/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "Ray.h"
#include <algorithm>

RectangleCollider::RectangleCollider(Entity381 *entity, int w, int l) :
        Collider(entity),
        width(w),
        length(l){
}

RectangleCollider::~RectangleCollider(){

}

void RectangleCollider::OnCollision(Collider *other) const{
}

bool RectangleCollider::IsColliding(Collider *other) const{
    CircleCollider *castToCircle = dynamic_cast<CircleCollider *>(other);
    if(castToCircle != NULL){
        //Sanity check because no intersection possible if the two are too far apart
        if((castToCircle->entity381->position).distance(entity381->position)
                > 0.5 * width + 0.5 * length + castToCircle->radius){
            return false;
        }
        Ogre::Vector2 circleCenter = Ogre::Vector2(castToCircle->entity381->position.x,
                castToCircle->entity381->position.z);
        const Ogre::Vector2 A = GetTopLeft();
        const Ogre::Vector2 B = GetTopRight();
        const Ogre::Vector2 C = GetBottomRight();
        const Ogre::Vector2 D = GetBottomLeft();
        if(RectangleCollider::InsideRectangle(circleCenter, A, B, D)
                || RectangleCollider::IntersectsCircle(circleCenter, castToCircle->radius,
                        A, B)
                || RectangleCollider::IntersectsCircle(circleCenter, castToCircle->radius,
                        B, C)
                || RectangleCollider::IntersectsCircle(circleCenter, castToCircle->radius,
                        C, D)
                || RectangleCollider::IntersectsCircle(circleCenter, castToCircle->radius,
                        D, A)){
            return true;
        }
    }

    RectangleCollider *castToRect = dynamic_cast<RectangleCollider *>(other);
    if(castToRect != NULL){
        //Handle rectangle and rectangle collision detection
    }
    return false;
}

bool RectangleCollider::GetClosestPoint(const Ray ray, float *dist) const{
    const Ogre::Vector2 A = GetTopLeft();
    const Ogre::Vector2 B = GetTopRight();
    const Ogre::Vector2 C = GetBottomRight();
    const Ogre::Vector2 D = GetBottomLeft();
    float intersectDist1 = Ogre::Math::POS_INFINITY;
    float intersectDist2 = Ogre::Math::POS_INFINITY;
    float intersectDist3 = Ogre::Math::POS_INFINITY;
    float intersectDist4 = Ogre::Math::POS_INFINITY;
    bool hit1 = RectangleCollider::RayLineIntersection(ray, A, B, &intersectDist1);
    bool hit2 = RectangleCollider::RayLineIntersection(ray, B, C, &intersectDist2);
    bool hit3 = RectangleCollider::RayLineIntersection(ray, C, D, &intersectDist3);
    bool hit4 = RectangleCollider::RayLineIntersection(ray, D, A, &intersectDist4);
    if(hit1 || hit2 || hit3 || hit4){
        if(dist != NULL){
            *dist = std::min(intersectDist1,
                    std::min(intersectDist2, std::min(intersectDist3, intersectDist4)));
        }
        return true;
    }
    if(dist != NULL){
        *dist = Ogre::Math::POS_INFINITY;
    }
    return false;
}

bool RectangleCollider::RayLineIntersection(Ray ray, Ogre::Vector2 A, Ogre::Vector2 B,
                                            float *intersectDist){
    Ogre::Vector2 v1 = ray.origin - A;
    Ogre::Vector2 v2 = B - A;
    Ogre::Vector2 v3 = Ogre::Vector2(-ray.directionVector.y, ray.directionVector.x);
    float dot = v2.dotProduct(v3);
    if(Ogre::Math::Abs(dot) < 0.0001){
        //Lines are parallel
        if(intersectDist != NULL){
            *intersectDist = Ogre::Math::POS_INFINITY;
        }
        return false;
    }
    float t1 = v2.crossProduct(v1) / dot;
    float t2 = v1.dotProduct(v3) / dot;
    if(t1 >= 0.0 && t2 >= 0.0 && t2 <= 1.0){
        if(intersectDist != NULL){
            *intersectDist = t1 * ray.directionVector.length();
        }
        return true;
    }
    if(intersectDist != NULL){
        *intersectDist = Ogre::Math::POS_INFINITY;
    }
    return false;
}

inline Ogre::Vector2 RectangleCollider::GetTopLeft() const{
    const Ogre::Vector2 pos = Ogre::Vector2(entity381->position.x, entity381->position.z);
    const Ogre::Vector2 original = Ogre::Vector2(-width * 0.5, -length * 0.5);
    const float angle =
            entity381->ogreSceneNode->getOrientation().getYaw().valueRadians();
    return pos + RotateVectorClockwise(original, -angle);
}

inline Ogre::Vector2 RectangleCollider::GetTopRight() const{
    const Ogre::Vector2 pos = Ogre::Vector2(entity381->position.x, entity381->position.z);
    const Ogre::Vector2 original = Ogre::Vector2(width * 0.5, -length * 0.5);
    const float angle =
            entity381->ogreSceneNode->getOrientation().getYaw().valueRadians();
    return pos + RotateVectorClockwise(original, -angle);
}

inline Ogre::Vector2 RectangleCollider::GetBottomLeft() const{
    const Ogre::Vector2 pos = Ogre::Vector2(entity381->position.x, entity381->position.z);
    const Ogre::Vector2 original = Ogre::Vector2(-width * 0.5, length * 0.5);
    const float angle =
            entity381->ogreSceneNode->getOrientation().getYaw().valueRadians();
    return pos + RotateVectorClockwise(original, -angle);
}

inline Ogre::Vector2 RectangleCollider::GetBottomRight() const{
    const Ogre::Vector2 pos = Ogre::Vector2(entity381->position.x, entity381->position.z);
    const Ogre::Vector2 original = Ogre::Vector2(width * 0.5, length * 0.5);
    const float angle =
            entity381->ogreSceneNode->getOrientation().getYaw().valueRadians();
    return pos + RotateVectorClockwise(original, -angle);
}

bool RectangleCollider::InsideRectangle(Ogre::Vector2 p, Ogre::Vector2 topLeft,
                                        Ogre::Vector2 topRight, Ogre::Vector2 bottomLeft){
    const Ogre::Vector2 topLeft_to_p = p - topLeft;
    const Ogre::Vector2 widthVector = topRight - topLeft;
    const Ogre::Vector2 lengthVector = bottomLeft - topLeft;

    const float A = topLeft_to_p.dotProduct(widthVector);
    const float B = topLeft_to_p.dotProduct(lengthVector);
    return (0 < A && A < widthVector.squaredLength() && 0 < B
            && B < lengthVector.squaredLength());
}

bool RectangleCollider::IntersectsCircle(Ogre::Vector2 centerPoint, int radius,
                                         Ogre::Vector2 A, Ogre::Vector2 B){
    const int radiusSquared = radius * radius;
    const Ogre::Vector2 closestPoint = RectangleCollider::ClosestPoint(centerPoint, A, B);
    const float minDistSqr = centerPoint.squaredDistance(closestPoint);
    if(minDistSqr <= radiusSquared || centerPoint.squaredDistance(A) <= radiusSquared
            || centerPoint.squaredDistance(B) <= radiusSquared){
        return true;
    }
    return false;
}

inline Ogre::Vector2 RectangleCollider::RotateVectorClockwise(Ogre::Vector2 original,
                                                              float radAngle) const{
    const float sin = Ogre::Math::Sin(radAngle);
    const float cos = Ogre::Math::Cos(radAngle);
    return Ogre::Vector2(original.x * cos - original.y * sin,
            original.x * sin + original.y * cos);
}

Ogre::Vector2 RectangleCollider::ClosestPoint(Ogre::Vector2 centerPoint, Ogre::Vector2 A,
                                              Ogre::Vector2 B){
    const float l2 = A.squaredDistance(B);
    if(l2 == 0.0){
        return A;
    } else{
        float t = (centerPoint - A).dotProduct(B - A) / l2;
        if(t > 1){
            t = 1;
        } else if(t < 0){
            t = 0;
        }
        const Ogre::Vector2 projection = A + (B - A) * t;
        return projection;
    }
}

Ogre::Vector3 RectangleCollider::GetClosestPoint(Ogre::Vector3 point) const{
    Ogre::Vector2 cp = Ogre::Vector2(point.x, point.z);
    const Ogre::Vector2 A = GetTopLeft();
    const Ogre::Vector2 B = GetTopRight();
    const Ogre::Vector2 C = GetBottomRight();
    const Ogre::Vector2 D = GetBottomLeft();
    Ogre::Vector2 closestPoint1 = RectangleCollider::ClosestPoint(cp, A, B);
    Ogre::Vector2 closestPoint2 = RectangleCollider::ClosestPoint(cp, B, C);
    Ogre::Vector2 closestPoint3 = RectangleCollider::ClosestPoint(cp, C, D);
    Ogre::Vector2 closestPoint4 = RectangleCollider::ClosestPoint(cp, D, A);

    const float distSqr1 = cp.squaredDistance(closestPoint1);
    const float distSqr2 = cp.squaredDistance(closestPoint2);
    const float distSqr3 = cp.squaredDistance(closestPoint3);
    const float distSqr4 = cp.squaredDistance(closestPoint4);

    const float min = std::min(distSqr1,
            std::min(distSqr2, std::min(distSqr3, distSqr4)));

    if(Ogre::Math::Abs(distSqr1 - min) <= 0.1){
        return Ogre::Vector3(closestPoint1.x, point.y, closestPoint1.y);
    } else if(Ogre::Math::Abs(distSqr2 - min) <= 0.1){
        return Ogre::Vector3(closestPoint2.x, point.y, closestPoint2.y);
    } else if(Ogre::Math::Abs(distSqr3 - min) <= 0.1){
        return Ogre::Vector3(closestPoint3.x, point.y, closestPoint3.y);
    } else if(Ogre::Math::Abs(distSqr4 - min) <= 0.1){
        return Ogre::Vector3(closestPoint4.x, point.y, closestPoint4.y);
    } else{
        return Ogre::Vector3(closestPoint1.x, point.y, closestPoint1.y);
    }
}

bool RectangleCollider::Contains(Ogre::Vector3 centerPoint) const{
    const Ogre::Vector2 center = Ogre::Vector2(centerPoint.x, centerPoint.z);
    return RectangleCollider::InsideRectangle(center, GetTopLeft(), GetTopRight(),
            GetBottomLeft());
}

//--------------------------------------------------------------------

RectangleBorderCollider::RectangleBorderCollider(Entity381 *entity, int w, int l) :
        RectangleCollider(entity, w, l){

}

RectangleBorderCollider::~RectangleBorderCollider(){

}

void RectangleBorderCollider::OnCollision(Collider *other) const{
    RectangleCollider::OnCollision(other);
}


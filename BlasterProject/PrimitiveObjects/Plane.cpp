#include "Plane.h"

Plane::Plane() : PrimitiveObject(Material::defaultMaterial) {
    m_center = Vector3::zero;
    m_normal = Vector3::zero;
}

Plane::Plane(const Plane& pCopy) : PrimitiveObject(pCopy) {
    m_center = pCopy.m_center;
    m_normal = pCopy.m_normal;
}

Plane::Plane(const Vector3& pCenter, const Vector3& pNormal, const Material& pMaterial) : PrimitiveObject(pMaterial) {
    m_center = pCenter;
    m_normal = pNormal;
}

const Vector3 Plane::_computeCenter(const std::initializer_list<Vector3>& pCorners) {
    if (pCorners.size() < 3)
        throw std::exception::exception("Not enough points to create a Polygon");

    Vector3 center(Vector3::zero);

    for (auto it = pCorners.begin(); it != pCorners.end(); it++) {
        center += *it;
    }

    return center / pCorners.size();
}

const Vector3 Plane::_computeNormal(const std::initializer_list<Vector3>& pCorners) {
    if (pCorners.size() < 3)
        throw std::exception::exception("Not enough points to create a Polygon");

    return Vector3::normalize(Vector3::cross(*(pCorners.begin()) - *(pCorners.begin() + 1), *(pCorners.begin() + 2) - *(pCorners.begin() + 1)));
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
const Collision Plane::intersect(const Ray& pRay) const {
    
    double denominator = pRay.direction() * m_normal;

    if (denominator != 0) {
       double t = ((m_center - pRay.origin()) * m_normal) / denominator;
       if (t < 0)
           return Collision::noCollision; // The plane is behind the Ray's origin.       
               
       return Collision(pRay.point(t) + m_normal * 1e-6, m_material, m_normal, true);
    }
    return Collision::noCollision;
}

void Plane::print(std::ostream& pFlux) const {
    pFlux << "\nCenter of the plane : " << center();
    pFlux << "\nNormal vector to the plane : " << normal() << std::endl;
}

std::ostream& operator<<(std::ostream& pFlux, const Plane& pPlane) {
    pPlane.print(pFlux);
    return pFlux;
}

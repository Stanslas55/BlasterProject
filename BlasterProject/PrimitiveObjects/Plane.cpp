#include "Plane.h"

Plane::Plane() : PrimitiveObject(Material::defaultMaterial) {
    m_center = Vector3::zero;
    m_normal = Vector3::zero;
}

Plane::Plane(const Vector3& pCenter, const Vector3& pNormal, const Material& pMaterial) : PrimitiveObject(pMaterial) {
    m_center = pCenter;
    m_normal = pNormal;   
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
const Collision Plane::intersect(const Ray& pRay) const {
    
    double denominator = pRay.direction() * m_normal;
    if (abs(denominator) > 1e-2) {
       double t = ((center() - pRay.origin()) * m_normal) / denominator;      
       if (t < 0)
           return Collision::noCollision; // The plane is behind the Ray's origin.       
               
       return Collision(pRay.point(t), m_material, m_normal, true);
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

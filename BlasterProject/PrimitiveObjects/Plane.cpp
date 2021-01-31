#include "Plane.h"

Plane::Plane() {  
    
    m_center = Vector3(0, 0, 0);
    m_normal = Vector3(0, 0, 0);
}

Plane::Plane(const Vector3& pCenter, const Vector3& pNormal) {
    m_center = pCenter;
    m_normal = pNormal;   
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
std::vector<Vector3> Plane::intersect(const Ray& pRay) const {
    
    double denominator = pRay.direction() * m_normal;
    if (abs(denominator) > 1e-2)
    {      
       std::vector<Vector3> result;
       double t = ((center() - pRay.origin()) * m_normal) / denominator;      
       if (t < 0)return std::vector<Vector3>(); // The plane is behind the Ray's origin.       
       
       result.push_back(pRay.point(t));           
       return result;
    }    
    std::cout << "No intersection between the plane and the ray." << std::endl;
    return std::vector<Vector3>();
}

void Plane::print(std::ostream& pFlux) const{
    
    std::cout << "\nCenter of the plane : " << center();
    std::cout << "\nNormal vector to the plane : " << normal() << std::endl;
}

std::ostream& operator<<(std::ostream& pFlux, const Plane& pPlane) {
    pPlane.print(pFlux);
    return pFlux;
}

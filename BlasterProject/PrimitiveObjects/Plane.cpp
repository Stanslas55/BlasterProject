#include "Plane.h"

Plane::Plane() {
    corners[0] = Vector3(0, 0, 0);
    corners[1] = Vector3(0, 0, 0);
    corners[2] = Vector3(0, 0, 0);
    corners[3] = Vector3(0, 0, 0);
    
    center = Vector3(0, 0, 0);
    normal = Vector3(0, 0, 0);
}

Plane Plane::fromCorners(Vector3 pCorners[4])
{
    Plane plane;
    plane.corners[0] = pCorners[0];
    plane.corners[1] = pCorners[1];
    plane.corners[2] = pCorners[2];
    plane.corners[3] = pCorners[3];

    double moyenneX = (plane.corners[0].x() + plane.corners[1].x() + plane.corners[2].x() + plane.corners[3].x()) / 4;
    double moyenneY = (plane.corners[0].y() + plane.corners[1].y() + plane.corners[2].y() + plane.corners[3].y()) / 4;
    double moyenneZ = (plane.corners[0].z() + plane.corners[1].z() + plane.corners[2].z() + plane.corners[3].z()) / 4;

    plane.center = Vector3(moyenneX, moyenneY, moyenneZ);

    plane.normal = (plane.corners[0] - plane.corners[1]).cross(plane.corners[2] - plane.corners[1]);
    plane.normal.normalize();
    return plane;
}

Plane::Plane(const Vector3& pCenter, const Vector3& pNormal) {
    center = pCenter;
    normal = pNormal;   
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
std::vector<Vector3> Plane::intersect(const Ray& pRay) {
    
    double denominator = pRay.gDirection() * gNormal();
    if (abs(denominator) > 1e-2)
    {      
       std::vector<Vector3> result;
       double t = ((gCenter() - pRay.gOrigin()) * gNormal()) / denominator;      
       if (t < 0)return std::vector<Vector3>(); // The plane is behind the Ray's origin.       
       
       result.push_back(pRay.point(t));           
       return result;
    }    
    return std::vector<Vector3>();
}

void Plane::print(std::ostream& pFlux)
{
    std::cout << "\nPlane : {" << A() << ", " << B() << ", " << C() << ", " << D() << "}";
    std::cout << "\nCenter of the plane : " << gCenter();
    std::cout << "\nNormal vector to the plane : " << gNormal() << std::endl;
}

std::ostream& operator<<(std::ostream& pFlux, Plane pPlane)
{
    pPlane.print(pFlux);
    return pFlux;
}

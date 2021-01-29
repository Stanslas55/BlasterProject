#include "Sphere.hpp"

Sphere::Sphere()
{
    center = Vector3(0, 0, 0);
    radius = 1;
}

Sphere::Sphere(Vector3 pCenter, double pRadius)
{
    center = pCenter;
    radius = pRadius;
}

std::vector<Vector3> Sphere::intersect(Ray pRay)
{
    std::vector<Vector3> result;
    // Add here the math to find the intersect between the sphere (this) and pRay.

    return result;
}

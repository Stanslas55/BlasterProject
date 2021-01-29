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
// https://ibb.co/TY0W1n2
// According to the schema, L will be the direction Vector going from the origin of the ray, and going to the center of the sphere.
// tc stands for "t-cut"
std::vector<Vector3> Sphere::intersect(Ray pRay)
{
    std::vector<Vector3> result;
    double radius = gRadius(), d, tc, t1c;
    Vector3 L = gCenter() - pRay.gOrigin();   

    tc = L * pRay.gDirection();

    if (tc < 0)
    {
        std::cout << "\nNo intersection";
        return result;
    }

    d = sqrt(L * L - tc * tc);
    if (d > radius)
    {
        std::cout << "\nNo intersection";
        return result;
    }
    t1c = sqrt(radius * radius - d * d);

    result.push_back(pRay.point(tc - t1c));
    result.push_back(pRay.point(tc + t1c));

    return result;
}
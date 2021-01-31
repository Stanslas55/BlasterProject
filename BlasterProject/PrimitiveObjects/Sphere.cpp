#include "Sphere.hpp"

Sphere::Sphere()
{
    m_center = Vector3(0, 0, 0);
    m_radius = 1;
}

Sphere::Sphere(const Vector3& pCenter, double pRadius) {
    m_center = pCenter;
    m_radius = pRadius;
}
// https://ibb.co/TY0W1n2
// According to the schema, L will be the direction Vector going from the origin of the ray, and going to the center of the sphere.
// tc stands for "t-cut"
std::vector<Vector3> Sphere::intersect(const Ray& pRay) const {
    std::vector<Vector3> result;
    double radius = m_radius, d, tc, t1c;
    Vector3 L = m_center - pRay.origin();   

    tc = L * pRay.direction();

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

void Sphere::print(std::ostream& pFlux) const {        
    pFlux << "\nSphere: {Center: " << m_center << ", Radius: " << m_radius << "}" << std::endl;            
}

std::ostream& operator<<(std::ostream& pFlux, const Sphere& pSphere) 
{   
    pSphere.print(pFlux);
    return pFlux;   
}
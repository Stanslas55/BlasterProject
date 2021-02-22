#include "Sphere.hpp"

Sphere::Sphere() : PrimitiveObject(Material::defaultMaterial) {
    m_center = Vector3(0.0, 0.0, 0.0);
    m_radius = 1.0;
    m_sqRadius = 1.0;
}

Sphere::Sphere(const Vector3& pCenter, double pRadius, const Material& pMaterial) : PrimitiveObject(pMaterial) {
    m_center = pCenter;
    m_radius = pRadius;
    m_sqRadius = m_radius * m_radius;
}

// https://ibb.co/TY0W1n2
// According to the schema, L will be the direction Vector going from the origin of the ray, and going to the center of the sphere.
// tc stands for "t-cut"
const Collision Sphere::intersect(const Ray& pRay) const {
    double d, tc, t1c;
    const Vector3& L = m_center - pRay.origin();

    tc = L * pRay.direction();

    if (tc < 0)
        return Collision::noCollision;

    d = L * L - tc * tc;
    if (d > m_sqRadius)
        return Collision::noCollision;

    t1c = sqrt(m_sqRadius - d);

    const Vector3 point(pRay.point(tc - t1c));

    return Collision(point, m_material, Vector3::normalize(point - m_center), true);
}

void Sphere::print(std::ostream& pFlux) const {        
    pFlux << "\nSphere: {Center: " << m_center << ", Radius: " << m_radius << "}" << std::endl;            
}

std::ostream& operator<<(std::ostream& pFlux, const Sphere& pSphere) {   
    pSphere.print(pFlux);
    return pFlux;   
}
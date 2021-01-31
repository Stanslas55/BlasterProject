#include "Polygon.h"

Polygon::Polygon() {
    m_corners = nullptr;
    m_size = 0;
}

Polygon::Polygon(int pCorners, const Vector3& pCenter, const Vector3& pNormal):Plane(pCenter, pNormal) {
   
    m_corners = new Vector3[pCorners];
    m_size = pCorners;
    for (int indice = 0; indice < m_size; indice++) {
        m_corners[indice] = Vector3(0,0,0);
    }
}

Polygon::~Polygon() {
    if (m_corners) {
         delete[] m_corners;                
    }   
    m_corners = nullptr;
}

std::vector<Vector3> Polygon::intersect(const Ray& pRay) const{
    return Plane::intersect(pRay);
}

void Polygon::print(std::ostream& pFlux) const {
    Plane::print(std::cout); 
}
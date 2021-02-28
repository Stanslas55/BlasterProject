#include "Polygon.h"

Polygon::Polygon() : Plane() {
    m_corners = nullptr;
    m_nbCorners = 0;
}

Polygon::Polygon(const Polygon& pCopy) : Plane(pCopy) {
    m_nbCorners = pCopy.m_nbCorners;
    m_corners = std::unique_ptr<Vector3[]>(new Vector3[m_nbCorners]);

    for (int i = 0; i < m_nbCorners; i++) {
        m_corners[i] = pCopy.m_corners[i];
    }
}

Polygon::Polygon(const std::initializer_list<Vector3>& pCorners, const Material& pMaterial) : Plane(_computeCenter(pCorners), _computeNormal(pCorners), pMaterial) {
    m_nbCorners = pCorners.size();
    m_corners = std::unique_ptr<Vector3[]>(new Vector3[m_nbCorners]);

    int i = 0;
    for (auto it = pCorners.begin(); it != pCorners.end(); it++) {
        m_corners[i++] = *it;
    }
}

Polygon::~Polygon() {}

const Collision Polygon::intersect(const Ray& pRay) const{
    const Collision collision = Plane::intersect(pRay);

    if (!collision.collided())
        return Collision::noCollision;

    const Vector3& point(collision.point());
      
    // https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon
    
    double pX = point.x();
    double pY = point.y();               
    double pZ = point.z();

    int index = 0, inter = 0, inter2 = 0, i, j;

    for(i = 0, j = m_nbCorners - 1; i < m_nbCorners; j = i++) {
        if( ((m_corners[i].y() > pY) != (m_corners[j].y() > pY)) && (pX < (m_corners[j].x() - m_corners[i].x()) * (pY - m_corners[i].y()) / (m_corners[j].y() - m_corners[i].y()) + m_corners[i].x()) )
            inter = !inter;
        if (((m_corners[i].z() > pZ) != (m_corners[j].z() > pZ)) && (pX < (m_corners[j].x() - m_corners[i].x()) * (pZ - m_corners[i].z()) / (m_corners[j].z() - m_corners[i].z()) + m_corners[i].x()))
            inter2 = !inter2;
    }

    return (!(inter & 1) && !(inter2 & 1)) ? Collision::noCollision : Collision(point, collision.normal(), -pRay.direction()); // If a both are even, it's not in the polygon.
}

void Polygon::print(std::ostream& pFlux) const {
    Plane::print(std::cout); 
}
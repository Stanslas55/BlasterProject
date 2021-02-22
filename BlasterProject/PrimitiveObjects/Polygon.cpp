#include "Polygon.h"

Polygon::Polygon() {
    m_corners = nullptr;
    m_nbCorners = 0;
}

Polygon::Polygon(int pCorners, const Vector3& pCenter, const Vector3& pNormal, const Material& pMaterial) : Plane(pCenter, pNormal, pMaterial) {
    m_corners = new Vector3[pCorners];
    m_nbCorners = pCorners;
    for (int indice = 0; indice < m_nbCorners; indice++) {
        m_corners[indice] = Vector3::zero;
    }
}

Polygon::~Polygon() {
    if (m_corners) {
         delete[] m_corners;                
    }   
    m_corners = nullptr;
}

const Collision Polygon::intersect(const Ray& pRay) const{
    const Collision collision = Plane::intersect(pRay);

    if (!collision.collided())
        return Collision::noCollision;

    const Vector3& point(collision.point());
      
    // https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon
    
    double* vertx = new double[m_nbCorners];
    double* verty = new double[m_nbCorners];
    double* vertz = new double[m_nbCorners];

    double pX = point.x();
    double pY = point.y();               
    double pZ = point.z();

    int index = 0, inter = 0, inter2 = 0, i, j;

    for(index = 0; index < m_nbCorners; index++) {
        vertx[index] = m_corners[index].x();
        verty[index] = m_corners[index].y();
        vertz[index] = m_corners[index].z();
    }

    for(i = 0, j = m_nbCorners - 1; i < m_nbCorners; j = i++) {
        if( ((verty[i] > pY) != (verty[j] > pY)) && (pX < (vertx[j] - vertx[i]) * (pY - verty[i]) / (verty[j] - verty[i]) + vertx[i]) )
            inter = !inter;
        if (((vertz[i] > pZ) != (vertz[j] > pZ)) && (pX < (vertx[j] - vertx[i]) * (pZ - vertz[i]) / (vertz[j] - vertz[i]) + vertx[i]))
            inter2 = !inter2;
    }

    delete[] vertx;
    delete[] verty;
    delete[] vertz;

    return (!(inter & 1) && !(inter2 & 1)) ? Collision::noCollision : Collision(point, m_material, m_normal, true); // If a both are even, it's not in the polygon.
}

void Polygon::print(std::ostream& pFlux) const {
    Plane::print(std::cout); 
}
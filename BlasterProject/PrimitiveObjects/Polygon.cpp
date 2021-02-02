#include "Polygon.h"

Polygon::Polygon() {
    m_corners = nullptr;
    m_nbCorners = 0;
}

Polygon::Polygon(int pCorners, const Vector3& pCenter, const Vector3& pNormal):Plane(pCenter, pNormal) {
   
    m_corners = new Vector3[pCorners];
    m_nbCorners = pCorners;
    for (int indice = 0; indice < m_nbCorners; indice++) {
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
    std::vector<Vector3> point = Plane::intersect(pRay);
    
    if (point.size() != 0) {    
        std::cout << "Intersection plane: " << point[0] << "\nIs it inside the Quadri ?" << std::endl;
        // Recherche si point[0] appartient au Quadrilatère.
        // https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon
        
        double* vertx = new double[m_nbCorners];
        double* verty = new double[m_nbCorners];

        double pX = point[0].x();
        double pY = point[0].z();

        int index = 0, inter = 0, i, j;

        for(index = 0; index < m_nbCorners; index++) {
            vertx[index] = m_corners[index].x();
            verty[index] = m_corners[index].z();
        }                              
        for(i = 0, j = m_nbCorners - 1; i < m_nbCorners; j = i++) {
            if( ((verty[i] > pY) != (verty[j] > pY)) && (pX < (vertx[j] - vertx[i]) * (pY - verty[i]) / (verty[j] - verty[i]) + vertx[i]) )
                inter = !inter;
        }
        delete[] vertx;
        delete[] verty;
        return (inter % 2 == 0) ? std::vector<Vector3>() : point; // If inter is even, it's not in the polygon.               
    }
    std::cout << "No intersection between the quadri and the ray." << std::endl;
    return std::vector<Vector3>();
}

void Polygon::print(std::ostream& pFlux) const {
    Plane::print(std::cout); 
}
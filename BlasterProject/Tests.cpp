#include "Tests.h"

Tests::Tests() {
    std::cout << "Creation de la classe de Tests." << std::endl;
}

Tests::~Tests() {
}

void Tests::tests() {
    addition();
    substraction();
    multiplication();
    division();
    dot();
    cross();
    normalize();
    intersectionSphere();
    intersectionPlane();
}

void Tests::addition() {
    std::cout << "\nTest addition." << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    Vector3 B = Vector3(-1, -2, -3);
    Vector3 result = A + B;
    std::cout << A << " + " << B << " = " << result << std::endl;
}

void Tests::substraction() {
    std::cout << "\nTest soustraction." << std::endl;
    Vector3 A = Vector3(1, 2, 3);    
    Vector3 B = Vector3(-1, -2, -3);
    Vector3 result = A - B;
    std::cout << A << " - " << B << " = " << result << std::endl;
}

void Tests::multiplication() {
    std::cout << "\nTest multiplication." << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    float scalar = 10;
    Vector3 result = A * scalar;
    std::cout << A << " * " << scalar << " = " << result << std::endl;
}

void Tests::division() {
    std::cout << "\nTest division." << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    float scalar = 2;
    Vector3 result = A / scalar;
    std::cout << A << " / " << scalar << " = " << result << std::endl;
}

void Tests::dot() {
    std::cout << "\nTest dot product." << std::endl;
    Vector3 A = Vector3(1, 1, 1);
    Vector3 B = Vector3(-1, -1, -1);
    double result = A * B;
    std::cout << A << " . " << B << " = " << result << std::endl;    
}

void Tests::cross() {
    std::cout << "\nTest cross product." << std::endl;
    Vector3 A = Vector3(2, 2, 2);
    Vector3 B = Vector3(-1, 1, 3);
    Vector3 result = A.cross(B);
    std::cout << A << " ^ " << B << " = " << result << std::endl;
}

void Tests::normalize() {
    std::cout << "\nTest normalize." << std::endl;

    Vector3 A = Vector3(5, 10, 6);
    std::cout << "\nA de base: " << A;

    Vector3 B = Vector3::normalize(A);

    std::cout << "\nA apres B = Vector3::normalize(A): " << A << "\nB apres B = Vector3::normalize(A): " << B;
   
    A.normalize();
    std::cout << "\nA apres : A.normalize(): " << A << std::endl;
}

void Tests::intersectionSphere() {
    std::cout << "\nTest intersection sphere." << std::endl;
    size_t indice, size;
    Vector3 center = Vector3(5, 5, 5);
    double radius = 1;
    Sphere sphere = Sphere(center, radius);

    Vector3 origin = Vector3(0, 0, 0);
    Vector3 end = Vector3(5, 5, 5);
    Ray ray = Ray::fromLine(origin, end);

    std::vector<Vector3> intersections;

    intersections = sphere.intersect(ray);
    size = intersections.size();

    std::cout << sphere;
    std::cout << ray;
    

    for (indice = 0; indice < size; indice++)
    {
        std::cout << "\nIntersection point : " << intersections[indice];
    }
    std::cout << std::endl;
}

void Tests::intersectionPlane() {
    std::cout << "\nTest plane creation." << std::endl;

    Vector3 tab[4];
    Vector3 A = Vector3(1, 1, -1);
    Vector3 B = Vector3(1, -1, -1);
    Vector3 C = Vector3(-1, -1, -1);
    Vector3 D = Vector3(-1, 1, -1);   
    
    tab[0] = A;
    tab[1] = B;
    tab[2] = C;
    tab[3] = D;

    Plane plane = Plane::fromCorners(tab);
    std::cout << plane;     
    
    Plane testPlane = Plane(Vector3(0, 0, 0), Vector3(0, 1, 0));
    // Test that a ray pointed the wrong way does not intersect. This ray sits above the plane and points in the opposite direction.
    Ray missedRay = Ray(Vector3(0, 3, 0), Vector3(0, 1, 0));
    std::vector<Vector3> missResult = testPlane.intersect(missedRay);
    std::cout << "\nTest intersection." << std::endl << testPlane << std::endl;
    std::cout << missedRay << std::endl;
    if (missResult.size() == 0)
    {
        std::cout << "\nPas d'intersection entre le Rayon et le plan." << std::endl << std::endl;
    }else {
        std::cout << "\nIntersection: " << missResult[0];
    }

    // Test that a ray pointing at the plane will intersect. This ray sits 3 points above the plane and points directly down. if all goes well, the t value will equal 3.
    Ray hittingRay = Ray(Vector3(0, 3, 0), Vector3(0, -1, 0));
    std::vector<Vector3> hitResult = testPlane.intersect(hittingRay);
    std::cout << hittingRay;
    if (hitResult.size() == 0) {
        std::cout << "\nPas d'intersection entre le Rayon et le plan." << std::endl;
    }else{
        std::cout << "\nIntersection: " << hitResult[0] << std::endl;
    }
}
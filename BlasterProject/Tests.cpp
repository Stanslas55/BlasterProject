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
    intersectionQuadri();
    intersectionTri();
}

void Tests::addition() {
    std::cout << "\nTest addition." << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    Vector3 B = Vector3(-1, -2, -3);
    Vector3 result = A + B;
    assert(result == Vector3(0, 0, 0));
    std::cout << A << " + " << B << " = " << result << std::endl;
}

void Tests::substraction() {
    std::cout << "\nTest soustraction." << std::endl;
    Vector3 A = Vector3(1, 2, 3);    
    Vector3 B = Vector3(-1, -2, -3);
    Vector3 result = A - B;
    assert(result == Vector3(2, 4, 6));
    std::cout << A << " - " << B << " = " << result << std::endl;
}

void Tests::multiplication() {
    std::cout << "\nTest multiplication." << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    float scalar = 10;
    Vector3 result = A * scalar;
    assert(result == Vector3(10, 20, 30));
    std::cout << A << " * " << scalar << " = " << result << std::endl;
}

void Tests::division() {
    std::cout << "\nTest division." << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    float scalar = 2;
    Vector3 result = A / scalar;
    assert(result == Vector3(0.5, 1, 1.5));
    std::cout << A << " / " << scalar << " = " << result << std::endl;
}

void Tests::dot() {
    std::cout << "\nTest dot product." << std::endl;
    Vector3 A = Vector3(1, 1, 1);
    Vector3 B = Vector3(-1, -1, -1);
    double result = A * B;
    assert(result == -3);
    std::cout << A << " . " << B << " = " << result << std::endl;    
}

void Tests::cross() {
    std::cout << "\nTest cross product." << std::endl;
    Vector3 A = Vector3(2, 2, 2);
    Vector3 B = Vector3(-1, 1, 3);
    Vector3 result = Vector3::cross(A, B);
    assert(result == Vector3(4, -8, 4));
    std::cout << A << " ^ " << B << " = " << result << std::endl;
}

void Tests::normalize() {
    std::cout << "\nTest normalize." << std::endl;

    Vector3 A = Vector3(5, 10, 6);
    std::cout << "\nA = " << A;
    Vector3 B = Vector3::normalize(A);

    assert(A == Vector3(5, 10, 6));
    assert(B == Vector3(0.39405520311955033, 0.7881104062391007, 0.47286624374346037));
    std::cout << "\nA apres B = Vector3::normalize(A): " << A << "\nB apres B = Vector3::normalize(A): " << B;
   
    A.normalize();
    assert(A == Vector3(0.39405520311955033, 0.7881104062391007, 0.47286624374346037));
    std::cout << "\nA apres : A.normalize(): " << A << std::endl;
}

void Tests::intersectionSphere() {
    std::cout << "\nTest intersection sphere." << std::endl;

    Vector3 center = Vector3(5, 5, 5);
    double radius = 1;
    Sphere sphere = Sphere(center, radius);

    Vector3 origin = Vector3(0, 0, 0);
    Vector3 end = Vector3(5, 5, 5);
    Ray ray = Ray::fromLine(origin, end);

    const Collision intersections = sphere.intersect(ray);

    std::cout << sphere;
    std::cout << ray;    

    std::cout << "\nIntersection point : " << intersections;
    /* Expected: 
    Intersection point : (4.42265, 4.42265, 4.42265)
    Intersection point : (5.57735, 5.57735, 5.57735)
    */
    std::cout << std::endl;
}

void Tests::intersectionPlane() {        
    Plane plane = Plane(Vector3(0, 0, 0), Vector3(0, 1, 0));
    
    // Test that a ray pointed the wrong way does not intersect. This ray sits above the plane and points in the opposite direction.
    Ray missedRay = Ray(Vector3(0, 3, 0), Vector3(0, 1, 0));
    const Collision missResult = plane.intersect(missedRay);
    std::cout << "\nTest plane creation and intersection." << std::endl << plane << std::endl;
    std::cout << missedRay << std::endl;

    if (!missResult.collided()) {
        std::cout << "\nNo intersection between the ray and the plane." << std::endl << std::endl;
    }else {
        std::cout << "\nIntersection: " << missResult;
    }
    // Test that a ray pointing at the plane will intersect. This ray sits 3 points above the plane and points directly down. if all goes well, the t value will equal 3.
    Ray hittingRay = Ray(Vector3(0, 3, 0), Vector3(0, -1, 0));
    const Collision hitResult = plane.intersect(hittingRay);
    std::cout << hittingRay; 

    if (hitResult.collided()) {
        std::cout << "\nIntersection: " << hitResult << std::endl;
    } else{
        std::cout << "\nNo intersection between the ray and the plane." << std::endl;
    }
}

void Tests::intersectionQuadri() {
    std::cout << "\nTest quadri creation." << std::endl;

    Vector3 corners[4], testCorners[4];
    Ray missedRay, hittingRay;
    Quadri quadri, testQuadri; 

    quadri = Quadri({
        Vector3(1, 1, -1),
        Vector3(1, -1, -1),
        Vector3(-1, -1, -1),
        Vector3(-1, 1, -1)
    });

    std::cout << quadri;            
    
    //https://www.geogebra.org/3d/exaq2jua
    testQuadri = Quadri({
        Vector3(1, -1, 0),
        Vector3(-1, -1, 0),
        Vector3(-1, 1, 0),
        Vector3(1, 1, 0),
    });

    ////https://www.geogebra.org/3d/vxcg4nhz
    /*testQuadri = Quadri({
        Vector3(1.33, -5.08, 1),
        Vector3(-3.17, -2.72, 0),
        Vector3(1.49, 3.84, 1),
        Vector3(4, -2, 1.58)
    });*/
   
    std::cout << "\nTest intersection." << std::endl << testQuadri << std::endl;
    // Test that a ray pointed the wrong way does not intersect. This ray sits above the plane and points in the opposite direction.
    missedRay = Ray(Vector3(-1.1, 3, 0), Vector3(0, 0.5, -1)); // Expected: (-1.1,3,0)
    std::cout << missedRay << std::endl;

    const Collision missResult = testQuadri.intersect(missedRay);

    if (missResult.collided()) {
        std::cout << "\nIntersection: " << missResult;
    } else {
        std::cout << "\nNo intersection between the ray and the quadri." << std::endl << std::endl;
    }
    
    hittingRay = Ray(Vector3(0.5, 0.5, 0.5), Vector3(0, 0.5, -1)); // Expected: (0.5,0.75,0)
    //hittingRay = Ray(Vector3(0.5, -1, 5), Vector3(0, 0.5, -1));
    std::cout << hittingRay << std::endl;

    const Collision hitResult = testQuadri.intersect(hittingRay);

    if (hitResult.collided()) {
        std::cout << "\nIntersection: " << hitResult << std::endl;
    } else {
        std::cout << "\nNo intersection between the ray and the quadri." << std::endl;
    }  
}

void Tests::intersectionTri() {
    Ray missedRay, hittingRay;
    Tri tri;

    //https://www.geogebra.org/3d/wkataghd
    tri = Tri({
        Vector3(-5.41, 1.59, 0),
        Vector3(0, 0, 4),
        Vector3(3.31, -2.7, 0)
    });

    std::cout << "\nTest tri creation and intersection." << std::endl << tri << std::endl;
    // Test that a ray pointed the wrong way does not intersect.
    missedRay = Ray(Vector3(-1.1, 3, 0), Vector3(0, -2, 5)); 
    std::cout << missedRay << std::endl;

    const Collision missResult = tri.intersect(missedRay);

    if (missResult.collided()) {
        std::cout << "\nIntersection: " << missResult;
    } else {
        std::cout << "\nNo intersection between the ray and the tri." << std::endl << std::endl;
    }

    hittingRay = Ray(Vector3(-1.1, 3, 0), Vector3(0, -2, 1));
  
    std::cout << hittingRay << std::endl;

    const Collision hitResult = tri.intersect(hittingRay);

    if (hitResult.collided()) {
        std::cout << "\nIntersection: " << hitResult << std::endl;
    } else {
        std::cout << "\nNo intersection between the ray and the tri." << std::endl;
    }
}
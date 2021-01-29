#include "Tests.h"

Tests::Tests()
{
    std::cout << "Creation de la classe de Tests." << std::endl;
}

Tests::~Tests()
{
}

void Tests::tests()
{
    addition();
    substraction();
    multiplication();
    division();
    dot();
    cross();
    normalize();
}

void Tests::addition()
{
    std::cout << "\nTest addition" << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    Vector3 B = Vector3(-1, -2, -3);
    Vector3 result = A + B;
    std::cout << A << " + " << B << " = " << result << std::endl;
}

void Tests::substraction()
{
    std::cout << "\nTest soustraction" << std::endl;
    Vector3 A = Vector3(1, 2, 3);    
    Vector3 B = Vector3(-1, -2, -3);
    Vector3 result = A - B;
    std::cout << A << " - " << B << " = " << result << std::endl;
}

void Tests::multiplication()
{
    std::cout << "\nTest multiplication" << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    float scalar = 10;
    Vector3 result = A * scalar;
    std::cout << A << " * " << scalar << " = " << result << std::endl;
}

void Tests::division()
{
    std::cout << "\nTest division" << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    float scalar = 2;
    Vector3 result = A / scalar;
    std::cout << A << " / " << scalar << " = " << result << std::endl;
}

void Tests::dot()
{
    std::cout << "\nTest dot product" << std::endl;
    Vector3 A = Vector3(1, 1, 1);
    Vector3 B = Vector3(-1, -1, -1);
    float result = A * B;
    std::cout << A << " . " << B << " = " << result << std::endl;    
}

void Tests::cross()
{
    std::cout << "\nTest cross product" << std::endl;
    Vector3 A = Vector3(2, 2, 2);
    Vector3 B = Vector3(-1, 1, 3);
    Vector3 result = A.cross(B);
    std::cout << A << " ^ " << B << " = " << result << std::endl;
}

void Tests::normalize()
{
    std::cout << "\nTest normalize" << std::endl;

    Vector3 A = Vector3(5, 10, 6);
    std::cout << "\nA de base: " << A;

    Vector3 B = Vector3().normalize(A);

    std::cout << "\nA apres B = Vector3().normalize(A): " << A << "\nB apres B = Vector3().normalize(A): " << B;
   
    A.normalize();
    std::cout << "\nA apres : A.normalize(): " << A << std::endl;
}
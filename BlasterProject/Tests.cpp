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
}

void Tests::addition()
{
    std::cout << "Test addition" << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    Vector3 B = Vector3(-1, -2, -3);
    Vector3 result = A + B;
    std::cout << A << " + " << B << " = " << result << std::endl;
}

void Tests::substraction()
{
    std::cout << "Test soustraction" << std::endl;
    Vector3 A = Vector3(1, 2, 3);    
    Vector3 B = Vector3(-1, -2, -3);
    Vector3 result = A - B;
    std::cout << A << " - " << B << " = " << result << std::endl;
}

void Tests::multiplication()
{
    std::cout << "Test multiplication" << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    float scalar = 10;
    Vector3 result = A * scalar;
    std::cout << A << " * " << scalar << " = " << result << std::endl;
}

void Tests::division()
{
    std::cout << "Test division" << std::endl;
    Vector3 A = Vector3(1, 2, 3);
    float scalar = 2;
    Vector3 result = A / scalar;
    std::cout << A << " / " << scalar << " = " << result << std::endl;
}

void Tests::dot()
{
    std::cout << "Test produit scalaire" << std::endl;
    Vector3 A = Vector3(1, 1, 1);
    Vector3 B = Vector3(-1, -1, -1);
    float result = A * B;
    std::cout << A << " . " << B << " = " << result << std::endl;    
}

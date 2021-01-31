#include "PrimitiveObject.h"

std::vector<Vector3> PrimitiveObject::intersect(const Ray& pRay) const{
	std::cout << "Virtual class" << std::endl;
	return std::vector<Vector3>();
}

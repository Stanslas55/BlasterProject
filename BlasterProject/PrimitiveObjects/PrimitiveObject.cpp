#include "PrimitiveObject.h"

PrimitiveObject::PrimitiveObject(const Material& pMaterial) : m_material(pMaterial) {}

const Collision PrimitiveObject::intersect(const Ray& pRay) const {
	return Collision::noCollision;
}
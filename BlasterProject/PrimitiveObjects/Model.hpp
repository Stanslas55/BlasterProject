#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "PrimitiveObjects/PrimitiveObjects.hpp"

class Model {
	private:
		std::vector<std::shared_ptr<PrimitiveObject>> m_children;
		Vector3 m_position;

	public:

		Model();
		
		
		Model(const Vector3 &pPosition, const std::string path, const Material& pMaterial = Material::defaultMaterial);
		void addPrimitive(PrimitiveObject* pPrimitive);
		inline std::vector<std::shared_ptr<PrimitiveObject>>& children() { return m_children; }
		inline const std::vector<std::shared_ptr<PrimitiveObject>>& children() const { return m_children; }
};

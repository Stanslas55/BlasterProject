#include "Model.hpp"

Model::Model() : m_children() {}

void Model::addPrimitive(PrimitiveObject* pPrimitive) {

	std::shared_ptr<PrimitiveObject> ptr_obj(pPrimitive);
	m_children.push_back(std::move(ptr_obj));
}

Model::Model(const Vector3& pPosition, const std::string path, const Material& pMaterial) : m_material(pMaterial) {
	if (!m_children.empty()) {
		std::cout << "m_shildren not empty." << std::endl;
		return;
	}

	std::ifstream in_file(path);

	if (!in_file.is_open()) { //File open error check.
		std::cout << "ERROR::OBJLOADER::Could not open file." << std::endl;
		return;
	}

	std::vector<Vector3> vertex_positions, vertex_texcoords, vertex_normals;
	std::vector<int> vertex_position_indicies, vertex_texcoord_indicies, vertex_normal_indicies;
	std::vector<Tri> vertices; //Vertex array

	std::stringstream ss;
	std::string line = "", prefix = "";

	Vector3 tempPoint, tempTexture;
	size_t tempInt = 0, counter = 0, i = 0;
	bool normalsPresent = true, textcoordsPresent = true;

	while (std::getline(in_file, line)) { //Read one line at a time.		
		//Get the prefix of the line.
		ss.clear();
		ss.str(line);
		prefix = "";
		ss >> prefix;

		if (prefix == "#" || prefix == "o" || prefix == "s" || prefix == "use_mtl" || prefix == " " || prefix == "" || prefix == "\n") continue;

		else if (prefix == "v") { //Vertex position
			ss >> tempPoint.x() >> tempPoint.y() >> tempPoint.z();
			vertex_positions.push_back(tempPoint);
		}
		else if (prefix == "vt") {
			ss >> tempTexture.x() >> tempTexture.y();
			vertex_texcoords.push_back(tempTexture);
		}
		else if (prefix == "vn") {
			ss >> tempPoint.x() >> tempPoint.y() >> tempPoint.z();
			vertex_normals.push_back(tempPoint);
		}
		else if (prefix == "f") {
			if (vertex_positions.empty()) {
				std::cout << "Bad .obj file." << std::endl;
				return;
			}
			if (vertex_texcoords.empty()) textcoordsPresent = false;
			if (vertex_normals.empty()) normalsPresent = false;
			counter = 0;
			while (ss >> tempInt) {
				if (counter == 0) vertex_position_indicies.push_back(tempInt);
				if (textcoordsPresent && normalsPresent) { //Pushing indices into correct arrays, if the file contains v, vt AND vn.					

					if (counter == 1) vertex_texcoord_indicies.push_back(tempInt);
					else if (counter == 2) vertex_normal_indicies.push_back(tempInt);

					if (ss.peek() == '/') { //Handling characters
						counter = (counter + 1) % 3;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ') {
						counter = (counter + 1) % 3;
						ss.ignore(1, ' ');
					}
				}
				else if (!textcoordsPresent && !normalsPresent) { // If the file only contains v.
					if (ss.peek() == '/') ss.ignore(1, '/');
					else if (ss.peek() == ' ') ss.ignore(1, ' ');
				}
				else {
					if (!textcoordsPresent && normalsPresent) { // If the file is only missing vt.

						if (counter == 1) vertex_normal_indicies.push_back(tempInt);
					}
					else if (textcoordsPresent && !normalsPresent) { // If the file is only missing vn.

						if (counter == 1) vertex_texcoord_indicies.push_back(tempInt);
					}
					if (ss.peek() == '/') { //Handling characters
						counter = (counter + 1) % 2;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ') {
						counter = (counter + 1) % 2;
						ss.ignore(1, ' ');
					}
				}
			}
		}
	}
	// Load in all indices.	
	Vector3 sommets[3];
	Vector3 textures[3];
	size_t size = vertex_position_indicies.size();
	for (i = 0; i < size; i += 3) {

		sommets[0] = vertex_positions[vertex_position_indicies[i] - 1] + pPosition;
		sommets[1] = vertex_positions[vertex_position_indicies[i + 1] - 1] + pPosition;
		sommets[2] = vertex_positions[vertex_position_indicies[i + 2] - 1] + pPosition;

		this->addPrimitive(
			new Tri(sommets[2], sommets[1], sommets[0], pMaterial)
		);
	}
	//Loaded success
}
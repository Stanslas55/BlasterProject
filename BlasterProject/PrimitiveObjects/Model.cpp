#include "Model.hpp"


/*

void Mesh::LoadObjModel(const char *filename)
{
  std::ifstream in(filename, std::ios::in);
  if (!in)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(1);

	}
  std::string line;
  while (std::getline(in, line))
  {
	//check v for vertices
	 if (line.substr(0,2)=="v "){
		std::istringstream v(line.substr(2));
		glm::vec3 vert;
		double x,y,z;
		v>>x;v>>y;v>>z;
		vert=glm::vec3(x,y,z);
		vertices.push_back(vert);
  }
  //check for texture co-ordinate
  else if(line.substr(0,2)=="vt"){

	  std::istringstream v(line.substr(3));
	  glm::vec2 tex;
	  int U,V;
	  v>>U;v>>V;
	  tex=glm::vec2(U,V);
	  texture.push_back(tex);

  }
  //check for faces
  else if(line.substr(0,2)=="f "){
	int a,b,c; //to store mesh index
	int A,B,C; //to store texture index
	//std::istringstream v;
  //v.str(line.substr(2));
  const char* chh=line.c_str();
	sscanf (chh, "f %i/%i %i/%i %i/%i",&a,&A,&b,&B,&c,&C); //here it read the line start with f and store the corresponding values in the variables

	//v>>a;v>>b;v>>c;
	a--;b--;c--;
	A--;B--;C--;
	//std::cout<<a<<b<<c<<A<<B<<C;
	faceIndex.push_back(a);textureIndex.push_back(A);
	faceIndex.push_back(b);textureIndex.push_back(B);
	faceIndex.push_back(c);textureIndex.push_back(C);
  }

}
//the mesh data is finally calculated here
for(unsigned int i=0;i<faceIndex.size();i++)
{
	glm::vec3 meshData;
	glm::vec2 texData;
	meshData=glm::vec3(vertices[faceIndex[i]].x,vertices[faceIndex[i]].y,vertices[faceIndex[i]].z);
	texData=glm::vec2(texture[textureIndex[i]].x,texture[textureIndex[i]].y);
	meshVertices.push_back(meshData);
	texCoord.push_back(texData);
}

}*/

Model::Model() : m_children() {}

void Model::addPrimitive(PrimitiveObject* pPrimitive) {

	std::shared_ptr<PrimitiveObject> ptr_obj(pPrimitive);
	m_children.push_back(std::move(ptr_obj));
}

Model::Model(const Vector3& pPosition, const std::string path, const Material& pMaterial) {
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
	
	Vector3 A, B, C;
	size_t size = vertex_position_indicies.size();
	std::cout << "positions size: " << size << std::endl;
	for (i = 0; i < size; i += 3) {
			
		A = vertex_positions[vertex_position_indicies[i] - 1] + pPosition;
		B = vertex_positions[vertex_position_indicies[i + 1] - 1] + pPosition;
		C = vertex_positions[vertex_position_indicies[i + 2] - 1] + pPosition;
		if (textcoordsPresent) {
			// Add texture handling.
			//vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
			//Material test(point à mettre);
			Material test = pMaterial;

			//

			this->addPrimitive(
				new Tri(C, B, A, test
				)
			);
		}
		else {
			this->addPrimitive(
				new Tri(C, B, A, pMaterial)
			);
		}
					
	}	
	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";
}
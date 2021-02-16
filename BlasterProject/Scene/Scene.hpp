#pragma once
#include <vector>

#include "../PrimitiveObjects/PrimitiveObject.h"
#include "../Camera/Camera.hpp"

class LightSource {};

/**
* \class Scene
* \brief Contains every objects defining a scene with utility methods to populate one.
*/
class Scene {

private:

	std::vector<std::shared_ptr<PrimitiveObject>> m_objects;	/*< Contains every primitives objects of the scene */

	std::vector<std::shared_ptr<LightSource>> m_lightSources;	/*< Contains every light sources of the scene */

	Camera m_camera;											/*< Camera of the scene */

	Scene();

public:

	/**
	* \fn		Scene
	* \brief	Scene copy Constructor
	* 
	* \param[in]	pCopy		Scene object to copy
	*/
	Scene(const Scene& pCopy);

	/**
	* \fn		Scene
	* \brief	Recommended constructor for the Scene 
	*
	* \param[in]	pCamera		Camera associated to the scene. The scene will contain its copy within its members.
	*/
	Scene(const Camera& pCamera);

	/**
	 * \fn		addPrimitive
	 * \brief   Method to add an object to the scene.
	 * > Do not pass the adress of a local object. You must pass the adress of an allocated object.
	 *
	 * \param[in]   pPrimitive
	 */
	//template<class T> 
	void addPrimitive(PrimitiveObject* pPrimitive);

	/**
	* \fn		addPrimitives
	* \brief	Utility method to add multiple primitive objects to the scene
	*
	* \param[in]	pPrimitives		std::vector of Primitive objects to add the the scene
	*/
	//inline void addPrimitives(std::vector<PrimitiveObject*> pPrimitives) { m_objects.insert(m_objects.end(), pPrimitives.begin(), pPrimitives.end()); }
	
	/**
	 * \fn      addLightSource
	 * \brief   Method to add a light source to the scene.
	 * > Do not pass the adress of a local object. You must pass the adress of an allocated object
	 * 
	 * \param[in]	pLightSource
	 */
	//template<class T> 
	void addLightSource(LightSource* pLightSource);

	/**
	* \fn addLightSources
	* \brief Utility method to add multiple light sources to the scene
	*
	* \param[in]	pLightSources		std::vector of LightSource objects to add the the scene
	*/
	//inline void addLightSources(std::vector<LightSource> pLightSources) { m_lightSources.insert(m_lightSources.end(), pLightSources.begin(), pLightSources.end()); }
	
	/**
	 * \fn      takePictureNaive
	 * \brief   Takes a picture and save it to a FreeImage FIBITMAP* structure.
	 * 
	 * \param[out]   pPtrImage		Address of a FIBITMAP* structure.
	 */
	void takePictureNaive(FIBITMAP** pPtrImage);

	// TODO: add OBJ
};
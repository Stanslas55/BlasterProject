#pragma once
#include <vector>

#include "PrimitiveObjects/PrimitiveObjects.hpp"
#include "LightSource/LightSources.hpp"
#include "Camera/Camera.hpp"

/**
* \class Scene
* \brief Contains every objects defining a scene with utility methods to populate one.
*/
class Scene {

private:

	std::vector<std::shared_ptr<PrimitiveObject>> m_objects;	/*< Contains every primitives objects of the scene */

	std::vector<std::shared_ptr<LightSource>> m_lightSources;	/*< Contains every light sources of the scene */

	Camera m_camera;											/*< Camera of the scene */

	/**
	 * \fn      Scene
	 * \brief   Default constructor. Should not be used.
	 */
	Scene();

public:

	friend class Application;

	inline const Camera& camera() const { return m_camera; };
	inline Camera& camera() { return m_camera; };

	inline const std::vector<std::shared_ptr<PrimitiveObject>>& objects() const { return m_objects; }
	inline const std::vector<std::shared_ptr<LightSource>>& lightSources() const { return m_lightSources; }

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

	/**
	 * \fn      getClosestIntersectionNaive
	 * \brief   Naive implementation to find closest collision.
	 *
	 * \param[in]   pRay
	 * \return      const Collision
	 */
	const Collision getClosestIntersectionNaive(const Ray& pRay, bool pEarlyStop = false) const;

	/**
	 * \fn      getPixelColor
	 * \brief   Compute a pixel color given its ray.
	 * 
	 * \param[in]   pRay		Ray shot from the pixel
	 * \return      RGBQUAD		Color of the corresponding pixel
	 */
	RGBQUAD getPixelColor(const Ray& pRay);

	/**
	 * \fn      getPixelColor
	 * \brief   Compute a pixel color given its inital collision.
	 *
	 * \param[in]   pCollision	Initial collision
	 * \return      RGBQUAD		Color of the corresponding pixel
	 */
	RGBQUAD getPixelColor(const Collision& pCollision);

	/**
	 * \fn      getCollisionArray
	 * \brief   Get all collisions of a frame. Useful wheneve a scene is fixed and thus those collisions will not change between frames.
	 * 
	 * \return	Collision*		Allocated array of width*height Collisions of the scene. The parent caller must assure dealocation.
	 */
	Collision* getCollisionArray();

	// TODO: add OBJ
};
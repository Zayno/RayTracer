#pragma once

#include "vec3.hpp"
#include "Ray.h"
#include "Camera.h"
#include "HittableObjectList.h"

#include <random>

enum class RenderState { Ready, Running, Finished, Stopped };
enum class Scenes { DefaultScene, ThreeSpheres, TestScene };
extern int BM_Width;
extern int BM_Height;

class Renderer
{
public:


	Renderer() {}
	Renderer(const Renderer&) = delete;
	~Renderer();

	void SetScene(Scenes scene = Scenes::DefaultScene) { m_sceneType = scene; };


	void StartRender(int Start, int End);

	Scenes Scene() const { return m_sceneType; }


	unsigned int lastRenderTimeMS = 0;

private:

	int m_StartPos = 0;
	int m_EndPos = 0;
	CRandom MyRandom;

	Scenes m_sceneType{ Scenes::DefaultScene };
	HittableObjectList m_scene;
	void LoadScene();


	// our camera :)
	Camera* m_camera;

	struct Quad
	{
		Quad(glm::uvec2 min, glm::uvec2 max) : minCoo{ min }, maxCoo{ max } {};
		glm::uvec2 minCoo;
		glm::uvec2 maxCoo;
	};

	// actual internal implementation
	void Render();
	color ShootRay(const Ray& ray, unsigned int depth);
	void WritePixelToBuffer(unsigned int ix, unsigned int iy, unsigned int samples_per_pixel, color pixel_color);

	// rng stuff
	std::mt19937 m_rnGenerator{};
	std::uniform_real_distribution<float> m_unifDistribution{ 0.0f, 1.0f };

	float AspectRatio() const
	{
		return (float)(BM_Width) / (float)(BM_Height);
	}
};

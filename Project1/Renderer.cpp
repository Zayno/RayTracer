#include<chrono>
#include "Renderer.h"

#include "Shapes/Shapes.h"
#include "Materials/Materials.h"
#include "Shapes/Plane.h"
#include "Shapes/Sphere.h"
#include "Materials/Lambertian.h"
#include "Materials/Dielectric.h"
#include "Materials/Metal.h"

#include "HittableObjectList.h"

#include"bitmap_image.hpp"

extern bitmap_image MyImage;

extern color white;
extern color azure;

extern unsigned int samplesPerPixel;
extern unsigned int maxRayDepth;


Renderer::~Renderer()
{

}

void Renderer::SetImageSize(unsigned int x, unsigned int y)
{
	m_imageSize = glm::uvec2{ x, y };

}

void Renderer::StartRender()
{

	LoadScene();
	Render();
}


void Renderer::Render()
{
	std::cout << ("Start rendering!!!") << std::endl;
	const auto startTime = std::chrono::system_clock::now();

	std::mt19937 generator{ std::random_device{}() };

	for (int i = 0; i < m_imageSize.x; i++)
	{
		std::cout << i << " / " << m_imageSize.x << std::endl;

		for (int j = 0; j < m_imageSize.y; j++)
		{
			color pixel_color{ 0, 0, 0 };
			glm::uvec2 pixelCoord = glm::uvec2{ i, j };
			for (unsigned int i_sample = 0; i_sample < samplesPerPixel; i_sample++)
			{
				float u = (static_cast<float>(pixelCoord.x) + m_unifDistribution(generator)) / (m_imageSize.x - 1);
				float v = (static_cast<float>(pixelCoord.y) + m_unifDistribution(generator)) / (m_imageSize.y - 1);
				Ray r = m_camera->NewRay(u, v);
				pixel_color += ShootRay(r, maxRayDepth);
			}

			WritePixelToBuffer(pixelCoord.x, pixelCoord.y, samplesPerPixel, pixel_color);
		}
	}
	MyImage.vertical_flip();
	MyImage.horizontal_flip();
	MyImage.save_image("Output.bmp");

	const auto stopTime = std::chrono::system_clock::now();
	auto renderDuration = stopTime - startTime;
	std::cout << ("Rendering took {}", std::chrono::duration_cast<std::chrono::seconds>(renderDuration)) << std::endl;

}

color Renderer::ShootRay(const Ray& ray, unsigned int depth)
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);

	HitRecord HR;
	ScatteringRecord SR;

	bool IsValid = m_scene.Hit(ray, 0.001f, LARGE_FLOAT, HR, SR);
	if (IsValid)
	{
		if (SR.IsValid)
		{
			return SR.attenuation * ShootRay(SR.ray, depth - 1);
		}

		return { 0, 0, 0 };
	}



	float t = 0.5f * (ray.direction.y + 1.0f);
	return (1.0f - t) * white + t * azure;
}

unsigned char FloatTo255(float f)
{
	unsigned char b;
	b = (f >= 1.0 ? 255 : (f <= 0.0 ? 0 : (int)floor(f * 256.0)));
	return b;

}

void Renderer::WritePixelToBuffer(unsigned int ix, unsigned int iy, unsigned int samples_per_pixel, color pixel_color)
{
	pixel_color /= samples_per_pixel;
	pixel_color = glm::sqrt(pixel_color);
	pixel_color = glm::clamp(pixel_color, 0.0f, 1.0f);

	rgb_t MyColor;
	MyColor.red = FloatTo255(pixel_color.r);
	MyColor.green = FloatTo255(pixel_color.g);
	MyColor.blue = FloatTo255(pixel_color.b);


	MyImage.set_pixel(ix, iy, MyColor);

};


void Renderer::LoadScene()
{
	m_scene.Clear();

	switch (m_sceneType)
	{
	case Scenes::DefaultScene:
	{
		Camera::CameraOrientation orientation{ point3(13, 2, 3), point3(0, 0, 0), vec3(0, 1, 0) };

		constexpr auto dist_to_focus = 10.0f;
		constexpr auto aperture = 0.1f;

		m_camera = new Camera(orientation, 20.0f, AspectRatio(), aperture, dist_to_focus);

		m_scene.Add(HittableObject(new Plane(point3(0, 0, 0), glm::vec3(0, 1, 0)), new Lambertian(color(0.5, 0.5, 0.5))));

		for (int a = -11; a < 11; a++)
		{
			for (int b = -11; b < 11; b++)
			{
				const auto choose_mat = m_unifDistribution(m_rnGenerator);
				point3 center(a + 0.9 * m_unifDistribution(m_rnGenerator), 0.2, b + 0.9 * m_unifDistribution(m_rnGenerator));

				if ((center - point3(4, 0.2, 0)).length() > 0.9)
				{
					if (choose_mat < 0.8f)
					{
						// diffuse
// 						color randColor{ m_unifDistribution(m_rnGenerator), m_unifDistribution(m_rnGenerator),
// 										m_unifDistribution(m_rnGenerator) };
// 						auto albedo = randColor * randColor;
// 						auto center2 = center + vec3(0, 0.5 * m_unifDistribution(m_rnGenerator), 0);
// 						m_scene.Add(HittableObject(new MovingSphere(center, center2, 0.0f, 1.0f, 0.2f), new Lambertian(albedo)));
 					}
					else if (choose_mat < 0.95f)
					{
						// metal
						color albedo{ 0.5f * (1.0f + m_unifDistribution(m_rnGenerator)),
									 0.5f * (1.0f + m_unifDistribution(m_rnGenerator)),
									 0.5f * (1.0f + m_unifDistribution(m_rnGenerator)) };
						auto fuzz = 0.5f * m_unifDistribution(m_rnGenerator);
						m_scene.Add(HittableObject(new Sphere(center, 0.2f), new Metal(albedo, fuzz)));
					}
					else
					{
						// glass
						m_scene.Add(HittableObject(new Sphere(center, 0.2f), new Dielectric(1.5f)));
					}
				}
			}
		}
		m_scene.Add(HittableObject(new Sphere(point3(-4, 1, 0), 1.0f), new Lambertian(color(0.4, 0.2, 0.1))));
		m_scene.Add(HittableObject(new Sphere(point3(0, 1, 0), 1.0f), new Metal(color(0.7, 0.6, 0.5), 0.0f)));
		m_scene.Add(HittableObject(new Sphere(point3(4, 1, 0), 1.0f), new Dielectric(1.5f)));

	}
	break;
	// 
	// 	case Scenes::ThreeSpheres: 
	// 	{
	// 		Camera::CameraOrientation orientation{ point3(3, 3, 2), point3(0, 0, -1), vec3(0, 1, 0) };
	// 
	// 		const auto lookDir = orientation.lookfrom - orientation.lookat;
	// 		const auto dist_to_focus = std::sqrt(glm::dot(lookDir, lookDir));
	// 		constexpr auto aperture = 0.5f;
	// 
	// 		m_camera = std::make_unique<Camera>(orientation, 20.0f, AspectRatio(), aperture, dist_to_focus);
	// 
	// 		auto R = std::cos(pi / 4);
	// 		m_scene.Add(Sphere(point3(0.0, -100.5, -1.0), 100.0f), Lambertian(color(0.8, 0.8, 0.0)));
	// 		m_scene.Add(Sphere(point3(0.0, 0.0, -1.0), 0.5f), Lambertian(color(0.1, 0.2, 0.5)));
	// 		m_scene.Add(Sphere(point3(-1.0, 0.0, -1.0), 0.5f), Dielectric(1.5f));
	// 		m_scene.Add(Sphere(point3(-1.0, 0.0, -1.0), -0.45f), Dielectric(1.5f));
	// 		m_scene.Add(Sphere(point3(1.0, 0.0, -1.0), 0.5f), Metal(color(0.8, 0.6, 0.2), 0.0f));
	// 	} 
	// 	break;
	// 
	// 	case Scenes::TestScene: 
	// 	{
	// 		// Camera::CameraOrientation orientation{point3(0, 2, 13), point3(0, 0, 0), vec3(0, 1, 0)};
	// 		Camera::CameraOrientation orientation{ point3(0, 0, 13), point3(0, 0, 0), vec3(0, 1, 0) };
	// 
	// 		const auto lookDir = orientation.lookfrom - orientation.lookat;
	// 		const auto dist_to_focus = std::sqrt(glm::dot(lookDir, lookDir));
	// 		constexpr auto aperture = 0.1f;
	// 
	// 		m_camera = std::make_unique<Camera>(orientation, 20.0f, AspectRatio(), aperture, dist_to_focus);
	// 
	// 		auto material = Lambertian(color(0.8, 0.2, 0.1));
	// 		m_scene.Add(Sphere(point3(-1, 0, 0), 1.0f), material);
	// 		// m_scene.Add(Shapes::Sphere(point3(0, 0, -2), 1.0f), material);
	// 
	// 		m_scene.Add(Rectangle({ point3(0.5, -1.0, -2.0), point3(-1.5, 1.0, -2.0), glm::vec3(1.5, 0.0, -2.0) }),
	// 			material);
	// 
	// 		m_scene.Add(Parallelogram({ point3(2.0, -1.0, -4.0), point3(1.5, -0.5, -5.0), glm::vec3(2.5, -0.5, -5.0) }),
	// 			material);
	// 
	// 		m_scene.Add(Rectangle({ point3(3.0, -1.0, -4.0), point3(3.0, 0.0, -4.0), glm::vec3(4.0, -1.0, -4.0) }),
	// 			material);
	// 
	// 		auto plane_material = Lambertian(color(0.6, 0.6, 0.6));
	// 		m_scene.Add(Plane(point3(0.0, -1.2, 0.0), glm::vec3(0.0, 1.0, 0.0)), plane_material);
	// 	} break;
	default:
		throw(std::runtime_error("Invalid scene selected"));
		break;
	}
}

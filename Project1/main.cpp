#include"Renderer.h"
#include"bitmap_image.hpp"


int BM_Width = 600;
int BM_Height = 600;
unsigned int samplesPerPixel = 128;
unsigned int maxRayDepth = 12;


bitmap_image MyImage(BM_Width, BM_Height);
color white{ 1.0, 1.0, 1.0 };
color azure{ 0.5, 0.7, 1.0 };

int main()
{
	Renderer m_renderer;

	m_renderer.SetScene(Scenes::DefaultScene);

	m_renderer.SetImageSize(BM_Width, BM_Height);
	m_renderer.StartRender();

}
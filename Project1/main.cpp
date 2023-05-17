#include <thread>
#include <mutex>          // std::mutex
#include <vector>
using namespace std;

#include"Renderer.h"
#include"bitmap_image.hpp"

//set the following options to change output image

//output image width and height
int BM_Width = 6000;
int BM_Height = BM_Width / (16.0f/9.0f);
//ray tracer details settings
unsigned int samplesPerPixel = 256;//64 is fairly nice
unsigned int maxRayDepth = 64;//12 can be a default value

mutex mtx;           // mutex for critical section


bitmap_image MyImage(BM_Width, BM_Height);
color white{ 1.0, 1.0, 1.0 };
color azure{ 0.5, 0.7, 1.0 };


void WorkerThread(int Start, int End)
{
	Renderer m_renderer;

	m_renderer.SetScene(Scenes::DefaultScene);

	m_renderer.StartRender(Start, End);
}


int main()
{
	std::cout << ("Start rendering!!!") << std::endl;

	int processor_count = std::thread::hardware_concurrency();

	int CoresToUse = processor_count - 1;

	int Divs = BM_Width / CoresToUse;
	int remaining = BM_Width % CoresToUse;

	int start = 0;
	int End = start + Divs;

	vector<thread> MyThreads;
	MyThreads.resize(CoresToUse);

	for (int i = 0; i < CoresToUse; i++)
	{
		MyThreads[i] = thread{ WorkerThread, start, End - 1 };
		start = End;
		End = start + Divs;

		if (i == CoresToUse - 1)
		{
			End += remaining;
		}
	}

	for (int i = 0; i < CoresToUse; i++)
	{
		MyThreads[i].join();
	}


	MyImage.vertical_flip();
	MyImage.horizontal_flip();
	MyImage.save_image("ZZZOutput.bmp");


}
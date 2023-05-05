#include <thread>
#include <mutex>          // std::mutex

using namespace std;

#include"Renderer.h"
#include"bitmap_image.hpp"

//set the following options to change output image

//output image width and height
int BM_Width = 3840;
int BM_Height = 2160;
//ray tracer details settings
unsigned int samplesPerPixel = 128;//64 is fairly nice
unsigned int maxRayDepth = 16;//12 can be a default value

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

	unsigned int processor_count = std::thread::hardware_concurrency();

	int Divs = BM_Width / 20;
	int remaining = BM_Width % 20;

	int start = 0;
	int End = start + Divs;

	thread t1(WorkerThread, start, End - 1); 
	start = End;
	End = start + Divs;
	thread t2(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t3(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t4(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t5(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t6(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t7(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t8(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t9(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t10(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t11(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t12(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t13(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t14(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t15(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t16(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t17(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t18(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs;
	thread t19(WorkerThread, start, End - 1);
	start = End;
	End = start + Divs + remaining;
	thread t20(WorkerThread, start, End - 1);






	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();
	t17.join();
	t18.join();
	t19.join();
	t20.join();


	MyImage.vertical_flip();
	MyImage.horizontal_flip();
	MyImage.save_image("Output.bmp");


}
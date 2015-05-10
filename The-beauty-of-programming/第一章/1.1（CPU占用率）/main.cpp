// C++ code to make task manager generate sine graph
// ***********************************************************
// CPU的占有率：在任务管理器的一个刷新周期内，CPU忙的时间和
// 刷新周期总时间的比率。任务管理器显示的CPU占有率就是每个
// 刷新周期内CPU占有率的统计平均值。
// 这就为我们人为调整CPU占有率提供了理论依据，写一个程序，
// 让CPU一会儿忙，一会闲，从而控制比率，即CPU占有率。
// ***********************************************************
// 那怎么让CPU一会儿忙一会儿空闲呢？
// 执行程序的时候CPU就会忙；
// CPU在等待用户输入，等待某些事情发生，或者休眠的时候就会空闲
// ***********************************************************
// 把一条正弦曲线0-2pi之间的弧度等分成200份进行抽样，
// 计算每个抽样点的振幅，然后每隔300ms的时间取下一个抽样点，
// 并让CPU工作对应振幅的时间。
// 由于在CPU上工作频率都是正值，因此需要将波形整体向上平移一半的幅度
// ***********************************************************
// GetTickCount返回（retrieve）从操作系统启动到现在
// 所经过（elapsed）的毫秒数，它的返回值是DWORD
// ***********************************************************
 //DWORD startTime = 0, intervalTmie = 0;
 //startTime = GetTickCount();
 //........
 //intervalTmie = GetTickCount() - startTime; // 计算间隔时间
// ***********************************************************
#include <Windows.h>
#include <stdlib.h>
#include <math.h>

const int sampling_count = 100; // 采样数
const double PI = 3.14159265; //pi
const int total_interval = 100; // 采样间隔

int main()
{
	DWORD busySpan[sampling_count];		// 忙碌时间数组
	DWORD idleSpan[sampling_count];		// 空闲时间数组
	int half_interval = total_interval / 2;
	double radian = 0.0; // 抽样弧度
	double radianIncrement = 2.0 / (double)sampling_count; // 抽样弧度的增量

	// 计算每个间隔内的忙碌时间和空闲时间
	for(int i = 0; i < sampling_count; i++)
	{
		busySpan[i] = (DWORD)(half_interval + (sin(PI * radian) * half_interval));
		idleSpan[i] = total_interval - busySpan[i];
		radian += radianIncrement;
	}

	// 计算每个间隔内的忙碌时间和空闲时间
	//for(int i = 0; i < sampling_count; i++)
	//{
	//	if (i < sampling_count/2)
	//	{
	//		busySpan[i] = (DWORD)(total_interval);
	//		idleSpan[i] = (DWORD)(0);
	//	}
	//	else
	//	{
	//		busySpan[i] = (DWORD)(0);
	//		idleSpan[i] = (DWORD)(total_interval);
	//	}
	//}
	DWORD startTime = 0;
	int j = 0;

	while(true)
	{
		j = j % sampling_count;
		startTime = GetTickCount();

		// 执行busySpan[j]时间
		while((GetTickCount() - startTime) <= busySpan[j])
			;

		// 空闲idleSpan[j]时间
		Sleep(idleSpan[j]);
		j++;
	}
	return 0;
}

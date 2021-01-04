#include "main.h"
#include "peripherals.h"
#include "utilities.h"

void drawBitmap();
int getKey();

int main(int argc, char *argv[]) {
	SystemInit();
	while (1) {
		ClearScreen();
		drawBitmap();
	}
}

void drawBitmap()
{
	FILE *bitmapFile = fopen("bitmapaRPi.ppm", "rb");
	u_int8_t bitmap[640*480*3];

	fread(&bitmap, sizeof(u_int8_t), 640*480*3, bitmapFile);
	u_int8_t *screen = (u_int8_t*)GRAPH;

	int a = 0;
	for(int i = 0; i < 640*480*4; i += 4)
	{
		screen[i] = bitmap[a + 2];
		screen[i + 1] = bitmap[a + 1];
		screen[i + 2] = bitmap[a];
		screen[i + 3] = 0x00;
		a += 3;
	}

	fclose(bitmapFile);
}


void* TimerThread(void* arguments)
{
	struct timespec destTime;
	clock_gettime(CLOCK_MONOTONIC,&destTime);
	while(1)
	{
		destTime.tv_nsec+=1000000;
		if(destTime.tv_nsec>=1E9)
		{
			destTime.tv_nsec-=1E9;
			destTime.tv_sec++;
		}
		globalTimer_ms++;
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &destTime, NULL);
	}
	return NULL;
}

void SystemInit() {
	FrameBufferFD = open("/dev/fb0", O_RDWR);
	ioctl(FrameBufferFD, FBIOGET_FSCREENINFO, &fix_info);
	framebuffer = mmap(NULL, fix_info.line_length * 480, PROT_READ | PROT_WRITE,MAP_SHARED, FrameBufferFD, 0);

	inputEventsFD = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
	pthread_create(&tID, NULL, TimerThread, NULL);
	struct timeval tTime;
	gettimeofday(&tTime,NULL);
	startTime_ms=tTime.tv_sec*1000+tTime.tv_usec/1000;
}

int getKey()
{
	struct input_event ev;
	int key = 0;

	while (read(inputEventsFD, &ev, sizeof ev) > 0)
	{
		if (ev.type == EV_KEY) {
			key = ev.value ? ev.code : 0;
		}
	}

	return key;
}

void ClearScreen() {

	for (int a = 0; a < (640 * 480); a += 1) {
		((u_int32_t*) framebuffer)[fix_info.line_length / 4 * (a / 640) + a % 640] = GRAPH[a];
		GRAPH[a] = ((GRAPH[a] & 0xfefefe) >> 1);
	}
}

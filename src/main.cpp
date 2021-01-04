#include "main.h"
#include "peripherals.h"
#include "utilities.h"

void drawBitmap();

int main(int argc, char *argv[]) {
	SystemInit();
	DataPrepare();
	while (1) {
		UpdateIO();
		PrintDiagnosticInfo();
		ClearScreen();
		drawBitmap();
		DrawObjects();
		usleep(10000);
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
		if(!(globalTimer_ms%1000)) flash_ligth=0xFF;
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

void PrintDiagnosticInfo(){
	struct timeval tTime;
	gettimeofday(&tTime,NULL);
	long TimeDiff=(tTime.tv_sec*1000+tTime.tv_usec/1000)-startTime_ms;
	long actTime=globalTimer_ms;
	if((frame_count % 20) == 0)
		printf("%i:: %li:%li=>%li KEYS: %i, %i, %i, %i, %x\n",frame_count,actTime,TimeDiff,actTime-TimeDiff,getKey(), Jx, Jy,JRz,JoYAct.ButtonStates);
}

void UpdateIO() {

	struct input_event ev;
	while (read(inputEventsFD, &ev, sizeof ev) > 0) {
		if (ev.type == EV_KEY) {
			switch (ev.value) {
			case 1:
				gRawKeys[0] = ev.code;
				break;
			case 0:
				gRawKeys[0] = 0;
				break;
			default:
				break;
			}

				switch (ev.code) {
				case KEY_KP4: JoYAct.AxisX =-127*(ev.value&1); break;
				case KEY_KP6: JoYAct.AxisX =127*(ev.value&1); break;
				case KEY_KP8: JoYAct.AxisY =-127*(ev.value&1); break;
				case KEY_KP2: JoYAct.AxisY =127*(ev.value&1); break;
				case KEY_RIGHT:
					if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_2;
					if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_2;
					break;
				case KEY_LEFT:
					if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_4;
					if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_4;
					break;
				case KEY_UP:
					if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_1;
					if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_1;
					break;
				case KEY_DOWN:
					if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_3;
					if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_3;
					break;
				default:
					break;
				}

		}

	}

}

void ClearScreen() {

	unsigned int bckgmask =getKey()>>2;

	int stage_max= -JRz/20;
	if (stage_max < 1)		stage_max = 1;
	if (stage_max > 9)		stage_max = 9;

	if (JoYAct.ButtonStates & BUTTON_SELECT)
		stage_max = 24;

	stage++;
	for (int a = stage % stage_max; a < (640 * 480); a += stage_max) {
		((u_int32_t*) framebuffer)[fix_info.line_length / 4 * (a / 640)
				+ a % 640] = GRAPH[a];
		GRAPH[a] = ((GRAPH[a] & 0xfefefe) >> 1) | bckgmask;
	}
}
void DrawObjects() {
	int get_flash_light=flash_ligth;
	unsigned int bckgmask =(get_flash_light<<16)|
			(get_flash_light<<8)|(get_flash_light);
	if(stage%2) flash_ligth>>=1;

	frame_count++;
	Jx = (Jx * 93 + 7 * JoYAct.AxisX) / 100;
	Jy = (Jy * 93 + 7 * JoYAct.AxisY) / 100;
	Jz = (Jz * 93 + 7 * ((JoYAct.ButtonStates & BUTTON_2 ? -128 : 0) + (JoYAct.ButtonStates & BUTTON_4 ? 127 : 0)))	/ 100;
	JRz = (JRz * 93	+ 7	* ((JoYAct.ButtonStates & BUTTON_1 ? -128 : 0)	+ (JoYAct.ButtonStates & BUTTON_3 ? 127 : 0)))	/ 100;
	if(JRz>40) JRz=40;
	ActMaxObj += 15;
	ActMaxObj %= MaxObj << 1;
	int RenderCnt = ActMaxObj - MaxObj;
	RenderCnt = (RenderCnt > 0) ? RenderCnt : -RenderCnt;
	if (RenderCnt < 2500)
		RenderCnt = 2500;

	for (int c = 0; c < RenderCnt; c++) {
		int srt = abs(dy[c]) + abs(dx[c]);
		for (int g = 0; g < srt / 10 + 1; g++) {
			int ddf = 20;
			ddf += -(JRz) / (srt + 1);
			if (ddf < 8)
				ddf = 8;
			y[c] += (ddf * dy[c]) / 30 + (Jyt - Jy) * srt / 20;
			x[c] += (ddf * dx[c]) / 30 + (Jxt - Jx) * srt / 20;
			y[c] -= ((xt[c] - x[c]) * Jz) / 200;
			x[c] += ((yt[c] - y[c]) * Jz) / 200;
			xt[c] = x[c];
			yt[c] = y[c];
			if (x[c] < 0 || y[c] < 0 || x[c] > 639 * 16 - s[c]
					|| y[c] > 479 * 16 - s[c]) {
				do {
					s[c] = randr(0x1f) + 1;
					xt[c] = x[c] = randr(519 * 16 - s[c]) + 60 * 16;
					yt[c] = y[c] = randr(379 * 16 - s[c]) + 50 * 16;
					int spd = randr(15) + 7;
					dx[c] = (x[c] - 320 * 16 - 16 * Jx - (Jx - Jxt) / 2) * spd;
					dy[c] = (y[c] - 240 * 16 - 16 * Jy - (Jy - Jyt) / 2) * spd;

					while (abs(dx[c]) > (-JRz / 18 + 9)
							|| abs(dy[c]) > (-JRz / 18 + 9)) {
						dx[c] /= 3;
						dy[c] /= 3;
					}
				} while ((abs(dy[c]) + abs(dx[c])) <= 4);
			}
			int size = s[c];

			int col = ((y[c] * 255 / (480 << 4)) + 0xf0000 * size
					) | bckgmask ;


			for (int b = y[c] >> 4; b < (y[c] + size) >> 4; b++)
				for (int a = x[c] >> 4; a < (x[c] + size) >> 4; a++)
					SetPixel(GRAPH, a, b, col);
		}
	}
	Jxt = Jx;
	Jyt = Jy;

}
void DataPrepare() {
	for (unsigned char a = 0; a < sizeof(struct JoY); a++)
		((char*) &JoYAct)[a] = 0;
	ActMaxObj = MaxObj;

	for (int a = 0; a < MaxObj; a++) {
		do {
			s[a] = randr(0x1f) + 1;
			xt[a] = x[a] = randr(619 * 16 - s[a]);
			yt[a] = y[a] = randr(479 * 16 - s[a]);
			int spd = randr(15) + 7;
			dx[a] = (x[a] - 320 * 16) * spd;
			dy[a] = (y[a] - 240 * 16) * spd;

			while (abs(dx[a]) > (9) || abs(dy[a]) > (9)) {
				dx[a] /= 3;
				dy[a] /= 3;
			}
		} while ((abs(dy[a]) + abs(dx[a])) <= 4);
	}
}


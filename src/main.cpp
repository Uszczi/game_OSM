#include "main.h"
#include "peripherals.h"
#include "utilities.h"

#include "PaintDevice.h"
#include "InputDevice.h"
#include "PPMPixmap.h"
#include "Pacman.h"

#include "HighScore.h"
#include "GameStatus.h"
#include "MainMenu.h"

#include <chrono>

static const char* HIGH_SCORE_FILE = "highscore.txt";

volatile long globalTimer_ms = 0;
long startTime_ms;
pthread_t tID;

int main(int argc, char *argv[])
{
	SystemInit();
	bool shouldExit = false;

	PaintDevice paintDevice("static/font.ppm");
	InputDevice input;

	HighScore highscores(HIGH_SCORE_FILE);
	MainMenu menu(highscores);
	GameStatus gameStatus;

	menu.setExitCallback([&](){shouldExit = true;});
	menu.setPlayCallback([&](){gameStatus.setPlaying(true);});

	PPMPixmap a = PPMPixmap("static/maze.ppm");
	PPMPixmap p_right = PPMPixmap("static/pacman_right.ppm");
	PPMPixmap p_left = PPMPixmap("static/pacman_left.ppm");
	PPMPixmap p_up = PPMPixmap("static/pacman_up.ppm");
	PPMPixmap p_bot = PPMPixmap("static/pacman_down.ppm");
	Pacman pacman = Pacman();



	Node * start = new Node(320, 270); // Center



	Node * n0 = new Node(124, 22);
	Node * n1 = new Node(204, 22);
	Node * n2 = new Node(296, 22);
	Node * n3 = new Node(124, 84);
	Node * n4 = new Node(204, 84);
	Node * n5 = new Node(250, 84);
	Node * n6 = new Node(296, 84);
	Node * n7 = new Node(124, 132);
	Node * n8 = new Node(204, 132);
	Node * n9 = new Node(250, 132);
	Node * n10 = new Node(296, 132);
	Node * n11 = new Node(250, 170);
	Node * n12 = new Node(296, 170);
	Node * n13 = new Node(204, 220);
	Node * n14 = new Node(250, 220);
	Node * n15 = new Node(250, 270);
	Node * n16 = new Node(124, 316);
	Node * n17 = new Node(204, 316);
	Node * n18 = new Node(250, 316);
	Node * n19 = new Node(296, 316);
	Node * n20 = new Node(124, 362);
	Node * n21 = new Node(158, 362);
	Node * n22 = new Node(204, 362);
	Node * n23 = new Node(250, 362);
	Node * n24 = new Node(296, 362);
	Node * n25 = new Node(124, 412);
	Node * n26 = new Node(158, 412);
	Node * n27 = new Node(204, 412);
	Node * n28 = new Node(250, 412);
	Node * n29 = new Node(296, 412);
	Node * n30 = new Node(124, 458);
	Node * n31 = new Node(296, 458);
	Node * n32 = new Node(516, 22);
	Node * n33 = new Node(436, 22);
	Node * n34 = new Node(344, 22);
	Node * n35 = new Node(516, 84);
	Node * n36 = new Node(436, 84);
	Node * n37 = new Node(390, 84);
	Node * n38 = new Node(344, 84);
	Node * n39 = new Node(516, 132);
	Node * n40 = new Node(436, 132);
	Node * n41 = new Node(390, 132);
	Node * n42 = new Node(344, 132);
	Node * n43 = new Node(390, 170);
	Node * n44 = new Node(344, 170);
	Node * n45 = new Node(436, 220);
	Node * n46 = new Node(390, 220);
	Node * n47 = new Node(390, 270);
	Node * n48 = new Node(516, 316);
	Node * n49 = new Node(436, 316);
	Node * n50 = new Node(390, 316);
	Node * n51 = new Node(344, 316);
	Node * n52 = new Node(516, 362);
	Node * n53 = new Node(482, 362);
	Node * n54 = new Node(436, 362);
	Node * n55 = new Node(390, 362);
	Node * n56 = new Node(344, 362);
	Node * n57 = new Node(516, 412);
	Node * n58 = new Node(482, 412);
	Node * n59 = new Node(436, 412);
	Node * n60 = new Node(390, 412);
	Node * n61 = new Node(344, 412);
	Node * n62 = new Node(516, 458);
	Node * n63 = new Node(344, 458);
	n0->add(n1);
	n1->add(n2);
	n3->add(n4);
	n4->add(n5);
	n5->add(n6);
	n7->add(n8);
	n9->add(n10);
	n11->add(n12);
	n13->add(n14);
	n16->add(n17);
	n17->add(n18);
	n18->add(n19);
	n20->add(n21);
	n22->add(n23);
	n23->add(n24);
	n25->add(n26);
	n26->add(n27);
	n28->add(n29);
	n30->add(n31);




	n0->add(n3);
	n1->add(n4);
	n2->add(n6);
	n3->add(n7);
	n4->add(n8);
	n5->add(n9);
	n8->add(n13);
	n10->add(n12);
	n11->add(n14);
	n13->add(n16);
	n14->add(n15);
	n15->add(n18);
	n16->add(n20);
	n17->add(n22);
	n19->add(n24);
	n21->add(n26);
	n22->add(n27);
	n23->add(n28);
	n25->add(n30);
	n29->add(n31);

	n15->add(start);

	pacman.now = start;

	unsigned sizeInc = 0;
	while (!shouldExit)
	{
		auto start = std::chrono::steady_clock::now();
		int key = input.getKey();

		if(key)
		{
			++sizeInc;
			printf("Pressed %d\n", key);
			if(!gameStatus.getPlayingStatus())
				menu.parseKey(key);
			else if(key == KEY_ESC)
				gameStatus.setPlaying(false);
		}

		pacman.setDirection(key);
		pacman.update();

		paintDevice.drawPixmap(a, 0, 0);

		if (pacman.dx < 0){
			paintDevice.drawPixmap(p_left, pacman.x + pacman.off_x, pacman.y + pacman.off_y);
		} else if (pacman.dy > 0){
			paintDevice.drawPixmap(p_bot, pacman.x + pacman.off_x, pacman.y + pacman.off_y);
		} else if (pacman.dy < 0){
			paintDevice.drawPixmap(p_up, pacman.x + pacman.off_x, pacman.y + pacman.off_y);
		} else {
			paintDevice.drawPixmap(p_right, pacman.x + pacman.off_x, pacman.y + pacman.off_y);
		}

		printf("x = %i y = %i\n",pacman.x, pacman.y);

	//	paintDevice.drawPixmap(clyde, 300, 200);
		auto end = std::chrono::steady_clock::now();

		paintDevice.drawText("FPS: "+ std::to_string(
				1000000.0/std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()), 0, 0);

		if(!gameStatus.getPlayingStatus())
			menu.drawTo(paintDevice);
		else
			paintDevice.drawText("Score: " + std::to_string(gameStatus.getPoints()), 0, paintDevice.getHeight() - 25);

		paintDevice.swapBuffers();
		paintDevice.clear();
	}

	return 0;
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

void SystemInit()
{
	pthread_create(&tID, NULL, TimerThread, NULL);
	struct timeval tTime;
	gettimeofday(&tTime,NULL);
	startTime_ms=tTime.tv_sec*1000+tTime.tv_usec/1000;
}

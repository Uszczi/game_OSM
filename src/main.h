#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/vt.h>
#include <linux/kd.h>
#include <linux/input.h>
#include <time.h>
#include <pthread.h>

#include "utilities.h"
#include "peripherals.h"

void SystemInit();
void SystemExit();

void ClearScreen();
void PrintDiagnosticInfo();

#endif /* SRC_MAIN_H_ */

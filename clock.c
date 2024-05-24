#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "FBCurses.h"
#define MAX_DIGITS 8

void showTime(colorcode_t oncolor,colorcode_t offcolor)
{
	char hourRemainders[MAX_DIGITS]; // Arrays to hold binary digits
        char minRemainders[MAX_DIGITS];
        char secRemainders[MAX_DIGITS];
        time_t date = time(NULL);
        struct tm *currentTime = localtime(&date); //EST time
        int hour = currentTime->tm_hour; // Parameters of time
        int min = currentTime->tm_min;
        int sec = currentTime->tm_sec;
        int count = 0; // Number of array elements
        int count1 = 0;
        int count2 = 0;

	// All these while loops convert each aspect of time into binary
	
        while(hour != 0)
        {
                hourRemainders[count] = hour % 2;
                hour = hour/2;
                ++count;
        }
        while(min != 0)
        {
                minRemainders[count1] = min % 2;
                min = min/2;
                ++count1;
        }
        while(sec != 0)
        {
                secRemainders[count2] = sec % 2;
                sec = sec/2;
                ++count2;
	}

        for(int i = 0; i < 8; i++) //8x6 board
	{
		for(int j = 0; j < 6; j++)
                {
			if (j == 1) // row1
                        {
				if (hourRemainders[7 - i] == 1) //checks if binary digit is one (reversed)
				{
                                	setPixel(i, j, oncolor);
				}
				else
				{
					setPixel(i, j, offcolor); // if binary digit is off --> zero
				}

                        }
                        else if (j == 3)
                        {
				if (minRemainders[7 - i] == 1)
				{
                                	setPixel(i, j, oncolor);
				}
				else
				{
					setPixel(i, j, offcolor);
				}
                        }
                        else if (j == 5)
                        {
				if (secRemainders[7 - i] == 1)
				{
                                	setPixel(i, j, oncolor);
				}
				else
				{
					setPixel(i, j, offcolor);
				}
                        }
			else
			{
				setPixel(i, j, offcolor); // turns all even rows off (according to case example)
			}
                }
	}
}

int main()
{
	initScreen();
	colorcode_t background=initColor(COLOR_RED);
	colorcode_t offcolor=initColor(COLOR_BLACK);
	colorcode_t oncolor=initColor(COLOR_WHITE);
	clearScreen(background);

 	while (!kbhit())
	{
		showTime(oncolor,offcolor);
		sleep(1);
	}
	cleanupScreen();
}

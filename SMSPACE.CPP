#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include <stdarg.h>
#include <iostream.h>
#include <string.h>
#include <sound.h>

//Initializing important values
int firstLoop = 1, con = 3, flag = 1, i, j, d, x;
int circleX = 35, circleY = 55;
time_t t;

int X[] = {280, 150, 610, 515, 550};
int Y[] = {60, 60, 410 , 60, 180};

//Timer
int resetted, running, beg, end;

void display_question(int a);

class timer {
	public:
		timer();
		void start();
		unsigned long  getTime();
	private:
		unsigned long  beg;
		unsigned long  end;
};

timer::timer()
{
	resetted = 1;
	running = 0;
	beg = 0;
	end = 0;
}

void timer::start() {
	if(! running) {
		if(resetted)
			beg = (unsigned long) clock();
		else
			beg -= end - (unsigned long) clock();
		running = 1;
		resetted = 0;
	}
}

unsigned long timer::getTime()
{
	if(running)
		return ((unsigned long) clock() - beg) / CLOCKS_PER_SEC;
	else
		return end - beg;
}

timer T; //Declaring the timer structure

//Checking for KeyPress, function at end of code
void keypress(int &x, int &y);

//Checking for Time
void timecheck(void);

void blackspot(int i, int j)
{
	//Blackspot to clear previous location
	setcolor(0);
	circle(i , j , 8);
}

void marioblack(int i, int j)
{
      //Separate blackspot for Mario with floodfill
      setfillstyle(SOLID_FILL, BLACK);
      setcolor(0);
      circle(i, j, 8);
      floodfill(i, j, BLACK);
      setcolor(BLACK);
      outtextxy(i - 3, j - 2, "M");
}

void KbhitCheck()   //Check for kbhit function
{
	if(!firstLoop && kbhit())
	{
	     timecheck();
	     keypress(circleX,circleY);
	}
	timecheck();
}

void MazeLines()
{
   //Maze
   setcolor(BLUE);
   line(140, 190, 140, 10); /* Portal Subdivisions */
   line(540, 190, 540, 10);
   line(410, 190, 410, 10);
   line(270, 190, 270, 10);
   line(540, 35, 630, 35);
   line(10, 35, 60, 35);
   setcolor(RED);
   line(530, 380, 530, 360);
   line(400, 380, 400, 360);
   line(270, 380, 270, 360);
   line(460, 340, 460, 320);
   line(330, 340, 330, 320);
   line(200, 340, 200, 320);
   setcolor(WHITE);
   line(60, 100, 60, 10);
   line(100, 150, 10, 150);
   line(100, 150, 100, 60);
   line(100, 150, 10, 150);
   line(140, 190, 60, 190);
   line(60, 400, 60, 190);
   line(90, 400, 60, 400);
   line(90, 420, 90, 400);
   line(90, 420, 60, 420);
   line(60, 435, 60, 420);
   line(580, 435, 60, 435);
   line(580, 435, 580, 420);
   line(580, 420, 550, 420);
   line(550, 420, 550, 400);
   line(550, 400, 580, 400);
   line(580, 400, 580, 380);
   line(580, 380, 60, 380);
   line(630, 320, 140, 320); /* Big horizontal line */
   line(140, 240, 140, 320);
   line(100, 190, 630, 190);

   //Border and Laser transmitters
   setcolor(3);
   rectangle(630, 470, 10, 10);
   rectangle(629, 469, 9, 9);
   setcolor(WHITE);
   rectangle(400, 315, 410, 320);
   rectangle(310, 315, 320, 320);
   rectangle(220, 315, 230, 320);

   //Ending Checkpoint
   setcolor(MAGENTA);
   setfillstyle(SLASH_FILL, MAGENTA);
   rectangle(570, 90, 600, 120);
   floodfill(575, 95, MAGENTA);
   setcolor(WHITE);
   outtextxy(570 , 77 , "EXIT");
}


//To check for collision with moving objects
void collision()
{
	   --con;
	   if(con == 2)
	    {
	      setcolor(BLACK);
	      setfillstyle(SOLID_FILL, BLACK);
	      rectangle(600, 20, 620, 30);
	      floodfill(605, 25, BLACK);
	    }
	    else if(con == 1)
	    {
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, BLACK);
		rectangle(580 , 20, 600 ,30);
		floodfill(585 , 25 , BLACK);
	    }
	    else
	    {
	       setcolor(BLACK);
	       setfillstyle(SOLID_FILL , BLACK);
	       rectangle(560 , 20 , 580 , 30);
	       floodfill(565 , 25 , BLACK);
	       delay(1000);
	    }
}

//For transporting between Portals
void PortalTransport(void)
{
	int num;
	srand((unsigned)time(&t));
	num = random(6);
	circleX = X[num];
	circleY = Y[num];
	marioblack(circleX - 5 , circleY  - 5);
	setcolor(4);
	circle(circleX, circleY, 8);


}

void LeftFireball()
{
       for(int x = 0; x < 60; x++)
       {
	 KbhitCheck();
	 setcolor(YELLOW);
	 setfillstyle(SOLID_FILL, YELLOW);
	 circle(80 - x, 410, 5);  /* Left Fireball */
	 floodfill(80 - x, 410, YELLOW);
	  //Left Fireball collision
	 if(circleX == 70 - x && (circleY >= 395 && circleY <= 430))
	  collision();
	 //////////////////////
	 setcolor(MAGENTA);        /* Portals */
	 setfillstyle(CLOSE_DOT_FILL, MAGENTA);
	 ellipse(205, 100, 0, 360, 14, 24);
	 floodfill(205, 100, MAGENTA);
	 ellipse(345, 100, 0, 360, 14, 24);
	 floodfill(345, 100, MAGENTA);
	 ellipse(480, 100, 0, 360, 14, 24);
	 floodfill(480, 100, MAGENTA);
	 setfillstyle(CLOSE_DOT_FILL, MAGENTA);
	 ellipse(590, 255, 0, 360, 20, 43);
	 floodfill(590, 255, MAGENTA);
	 //////////////////////
	 setcolor(LIGHTRED);
	 for(i = 6; i < 8; i++)
	 {
	    KbhitCheck();
	    circle(80 - x, 410, i);
	 }
	 blackspot(80 - x, 410);

	 KbhitCheck();

	 for(d = 0; d < 10; d++)
	 {
	     KbhitCheck();
	     delay(1);
	     KbhitCheck();
	 }
	 if(x == 59)
	 {
	    setfillstyle(SOLID_FILL, BLACK);
	    blackspot(20, 410);
	    floodfill(20, 410, BLACK);
	    KbhitCheck();
	    break;
	 }
     }
}

void RightFireball(void)
{
       for(x = 0; x < 60; x++)
       {
	 KbhitCheck();
	 setcolor(YELLOW);
	 setfillstyle(SOLID_FILL, YELLOW);
	 circle(560 + x, 410, 5);  /* Right Fireball */
	 floodfill(560 + x, 410, YELLOW);
	 //Right Fireball collision
	 if(circleX == 570 + x && (circleY >= 395 && circleY <= 430))
	  collision();

	 setcolor(LIGHTRED);
	 for(i = 6; i < 8; i++)
	 {
	     KbhitCheck();
	     circle(560 + x, 410, i);
	 }
	 blackspot(560 + x, 410);
	 KbhitCheck();
	 for(d = 0; d < 10; d++)
	 {
	     KbhitCheck();
	     delay(1);
	     KbhitCheck();
	 }
	 if(x == 59)
	 {
	    setfillstyle(SOLID_FILL, BLACK);
	    blackspot(620, 410);
	    floodfill(620, 410, BLACK);
	    KbhitCheck();
	    break;
	 }
	 KbhitCheck();
       }

}

//Drawing of Portal
void Portal(void)
{
       for(i = 15, j = 25; i < 20, j < 30; i++, j++)
       {
	KbhitCheck();
	setcolor(WHITE);                 /* Outermost Ellipses */
	ellipse(205, 100, 0, 360, i, j);
	ellipse(345, 100, 0, 360, i, j);
	ellipse(480, 100, 0, 360, i, j);
	setcolor(1);
	setfillstyle(CLOSE_DOT_FILL, 1);
	ellipse(205, 100, 0, 360, 14, 24);
	floodfill(205, 100, 1);
	ellipse(345, 100, 0, 360, 14, 24);
	floodfill(345, 100, 1);
	ellipse(480, 100, 0, 360, 14, 24);
	floodfill(480, 100, 1);
       }
       KbhitCheck();

       //Big ellipse
	for(i = 20, j = 43; i < 25, j < 48; i++, j++)
	{
		//Outermost Ellipse
		setcolor(WHITE);
		ellipse(590, 255, 0, 360, i, j);
		setcolor(1);
		setfillstyle(CLOSE_DOT_FILL, 1);
		ellipse(590, 255, 0, 360, 20, 43);
		floodfill(590, 255, 1);
	}
       delay(400); //Delay for Portal Color and Lasers
}

void timecheck()
{
		int flag = 0, g, f, count = 0;
		static int time = T.getTime();
		static int time1 = T.getTime() + 5;
		if(T.getTime() != time)      //Printing out the time
		{
		   time = T.getTime();
		   time1 = T.getTime() + 5;
		   static char timer[20];
		   setcolor(BLACK);
		   outtextxy(25, 20, timer);
		   sprintf(timer,"%d", 110 - time);
		   setcolor(WHITE);
		   outtextxy(25, 20, timer);
		}
		if(T.getTime() >= 110)
		{
		 cleardevice();
		 setcolor(WHITE);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
		 settextjustify(CENTER_TEXT, CENTER_TEXT);
		 outtextxy(getmaxx()/2, getmaxy()/2 - 50, "Time limit exceeded.");
		 delay(2000);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
		 char str1[100], ar1[16], ar2[16];
		 while((T.getTime() >= 110) && (T.getTime() <= 115))  //Flashy Text
		 {
			if(count%2 == 0)
				setcolor(WHITE);
			else
				setcolor(RED);
			ar1[16] = '\0';
			for(f = 0; f < 16; f++)
				ar1[f] = ' ';
			ar2[16] = '\0';
			for(f = 0; f < 16; f++)
				ar2[f] = ' ';
			strcpy(str1, "   GAME OVER    ");
			for(g = 0; g < 16; g++)
			{
				ar2[g] = str1[g];
				if(g != 0) ar2[g-1] = ' ';
				for(f = 0; f < 12; f++)
				{
					setcolor(0);
					outtextxy(getmaxx()/2, getmaxy()/2 - (20 - (f-1) * 2), ar2);
					if(count%2 == 0)
						setcolor(WHITE);
					else
						setcolor(RED);
					outtextxy(getmaxx()/2, getmaxy()/2 - (20 - (f * 2)), ar2);
					setcolor(0);
					outtextxy(getmaxx()/2, getmaxy()/2 + ((f - 1) * 2), ar1);
					if(count%2 == 0)
						setcolor(RED);
					else
						setcolor(WHITE);
					outtextxy(getmaxx()/2, getmaxy()/2 + (f * 2), ar1);
					setcolor(0);
				}
			}
			count++;
		}
		delay(1000);
		exit(0);
	}
	if(con == 0)
	{
		 cleardevice();
		 setcolor(WHITE);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
		 settextjustify(CENTER_TEXT, CENTER_TEXT);
		 outtextxy(getmaxx()/2, getmaxy()/2 - 50, "You have exhausted all of your lives.");
		 delay(2000);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
		 char str1[100], ar1[16], ar2[16];
		 while(T.getTime() <= time1)
		 {
			if(count%2 == 0)
				setcolor(WHITE);
			else
				setcolor(RED);
			ar1[16] = '\0';
			for(f = 0; f < 16; f++)
				ar1[f] = ' ';
			ar2[16] = '\0';
			for(f = 0; f < 16; f++)
				ar2[f] = ' ';
			strcpy(str1, "   GAME OVER    ");
			for(g = 0; g < 16; g++)
			{
				ar2[g] = str1[g];
				if(g != 0) ar2[g-1] = ' ';
				for(f = 0; f < 12; f++)
				{
					setcolor(0);
					outtextxy(getmaxx()/2, getmaxy()/2 - (20 - (f-1) * 2), ar2);
					if(count%2 == 0)
						setcolor(WHITE);
					else
						setcolor(RED);
					outtextxy(getmaxx()/2, getmaxy()/2 - (20 - (f * 2)), ar2);
					setcolor(0);
					outtextxy(getmaxx()/2, getmaxy()/2 + ((f - 1) * 2), ar1);
					if(count%2 == 0)
						setcolor(RED);
					else
						setcolor(WHITE);
					outtextxy(getmaxx()/2, getmaxy()/2 + (f * 2), ar1);
					setcolor(0);
				}
			}
			count++;
		 }
		 delay(1000);
		 exit(0);
	}

}

//LOADING SCREEN - PHASE 1
int main()
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int i, x, y, color, flag, flag2, midx, midy;
   char control;
   char ch;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "C:\TURBOC3\BIN");
   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }

   //Space Pixels
   setcolor(getmaxcolor());
   srand((unsigned) time(&t));
   for( i = 0 ; i < 500; ++i ){
    x = 1 + random( 640 - 1 );
    y = 1 + random( 480 - 1 );
    color = random(15);
    putpixel(x, y, color);
}
   /* Outtext Function */
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 10);
   outtextxy(getmaxx() / 2 - 200, getmaxy() / 2 - 150, "SUPER");
   sound(100);
   delay(900);
   nosound();
   delay(500);
   outtextxy(getmaxx() / 2 - 200, getmaxy() / 2 - 60, "MARIO");
   sound(200);
   delay(900);
   nosound();
   delay(500);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
   setcolor(3);
   outtextxy(getmaxx() / 2 - 140, 270, "SPACE");
   sound(300);
   delay(900);
   nosound();
   delay(500);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   setcolor(4);
   outtextxy(getmaxx() / 2 - 120, 370, "Press P to play");
   sound(400);
   delay(750);
   nosound();
   delay(500);
   setcolor(0);
   outtextxy(getmaxx() / 2 - 120, 370, "Press P to play");
   delay(500);

   //While loop for blinking of the play text
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   while(flag != 1)
   {
	if(kbhit()){
	   control = getch();
	   switch(control){
	      case 'p': flag = 1;
	      default: continue;
	   }
	}
	setcolor(4);
	outtextxy(getmaxx() / 2 - 120, 370, "Press P to play");
	delay(500);
	setcolor(0);
	outtextxy(getmaxx() / 2 - 120, 370, "Press P to play");
	delay(500);
   }
   cleardevice();
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
   delay(900);
   setcolor(RED);
   outtextxy(120, 170, "Mario has been shrunk by Bowser's destructive power!");
   delay(1500);
   setcolor(WHITE);
   outtextxy(80, 220, "Help him reach the end of the maze to regain his lost strength.");
   delay(1500);
   setcolor(3);
   outtextxy(105, 260, "Use the keys W, A, S, D for navigation. E is for exiting.");
   delay(1500);
   outtextxy(90, 290, "You have 105 seconds to complete the maze after the test run.");
   delay(2000);
   setcolor(GREEN);

   //While loop for blinking of continue text
   while(flag2 != 1)
   {
	if(kbhit()){
	   control = getch();
	   switch(control){
	      case 'c': flag2 = 1;
	      default: continue;
	   }
	}
	setcolor(GREEN);
	outtextxy(240, 340, "Press C to continue");
	delay(500);
	setcolor(0);
	outtextxy(240, 340, "Press C to continue");
	delay(500);
    }
    cleardevice();
    delay(1000);

    //Instructions

//MAZE - Phase 2

   T.start();
   int toggle, h= 200, k = 200, input;

   //Putpixel
   setcolor(getmaxcolor());
   srand((unsigned) time(&t));
   for(i = 0 ; i < 300; ++i){
    x = 1 + random(640 - 1);
    y = 1 + random(480 - 1);
    color = random(15);
    putpixel(x, y, color);
   }

   //Hearts (Lives)
   cout<<endl;
   printf("                                                                       %c", 3);
   printf(" %c", 3);
   printf(" %c", 3);

   //Moving Entities
   while(1)
   {
	KbhitCheck();
	MazeLines();
	KbhitCheck();

	//Lasers
	setcolor(GREEN);
	line(404, 314, 280, 191);
	line(314, 314, 420, 191);
	line(224, 314, 180, 191);

	// Laser collision
	if(circleY >= 191 && circleY <= 314)
	  if((circleX >= 280 && circleX <= 404) || (circleX >= 314 && circleX <= 420) || (circleX >= 180 && circleX <= 224))
	    collision();


       KbhitCheck();
       Portal();


       for(d = 1; d < 400; d++)
       {
	  KbhitCheck();
	  delay(1);
	  KbhitCheck();
       }
       //For Loop for major delay and kbhit detection
       for(d = 1; d < 1600; d++)
       {
	   KbhitCheck();
	   delay(1);
	   KbhitCheck();
       }
       setcolor(0);
       line(404, 314, 280, 191);
       line(314, 314, 420, 191);
       line(224, 314, 180, 191);

       LeftFireball();

       //Change in Laser
       setcolor(GREEN);
       line(404, 314, 180, 191);
       line(314, 314, 360, 191);
       line(224, 314, 280, 191);

	   //Second Laser collision
	if(circleY >= 191 && circleY <= 314)
	  if((circleX >= 180 && circleX <= 404) || (circleX >= 314 && circleX <= 360) || (circleX >= 224 && circleX <= 280))
	    collision();


       RightFireball();

       setcolor(0);
       line(404, 314, 180, 191);
       line(314, 314, 360, 191);
       line(224, 314, 280, 191);

       KbhitCheck();
	//User input
	KbhitCheck();
	if(firstLoop)
	{
	      setcolor(RED);
	      circle(circleX, circleY, 8);
	      firstLoop = 0;
	      keypress(circleX, circleY);
	}
   }

}
void keypress(int &circleX,int &circleY)
{
      int flag = 0;
      int h = 0, k = 0;
      char control;
      control = getch();
      switch(control)
      {
	   case 'a': 	  h = -5;
			  k = 0;
			  break;

	   case 's' :     h = 0;
			  k = 5;
			  break;

	   case 'w':      h = 0;
			  k = -5;
			  break;

	   case 'd':      h = 5;
			  k = 0;
			  break;

	   case 'e':	  exit(0);

	   default:       break;

      }
      //Making Mario move
      marioblack(circleX , circleY);
      circleX += h;
      circleY += k;
      setcolor(4);
      circle(circleX, circleY, 8);


      //Boundary Collisions
    if(circleX >= 20 && circleX <= 620 && circleY >= 20 && circleY <= 460)
    {

			    if(circleX >= 20 && circleX <= 50 && circleY >= 45 && circleY <= 100)
			    {

				if(circleY >= 20 && circleY <= 100)
				{
					if(circleX >= 50)
					  flag = 1;
					else
					  flag = 0;
				}
				else
				 flag = 0;

			    }
			 else if(circleX >= 20 && circleX <= 50 && circleY >= 100 && circleY <= 140)
			 {

				if(circleY >= 140)
				 flag = 1;
				 else
				 flag = 0;

			 }

			 else if(circleX >= 50 && circleX <= 90 && circleY >= 20 && circleY <= 140)
			 {

				if(circleY >= 20 && circleY <= 105)
				{
					if(circleX <= 70)
					  flag = 1;
					else
					  flag = 0;
				}
				else
				  flag = 0;
			 }

			else if(circleX >= 90 && circleX <= 130 && circleY >= 20 && circleY <= 180)
			 {

				if(circleY >= 50 && circleY <= 155)
				{
					if(circleX <= 110)
					  flag = 1;
					else
					  flag = 0;
				}
				else
				  flag = 0;
			}

			else if(circleX >= 20 && circleX <= 90 && circleY >= 160 && circleY <= 180)
			{

				flag = 0;
			}

			else if(circleX >= 20 && circleX <= 50 && circleY >= 180 && circleY <= 460)
			{

				flag = 0;
			}

			else if(circleX >= 50 && circleX <= 620 && circleY >= 445 && circleY <= 460)
			{

				flag = 0;
			}

			else if(circleX >= 590 && circleX <= 620 && circleY >= 330 && circleY <= 445)
			{

				flag = 0;
			}

			else if(circleX >= 70 && circleX <= 590 && circleY >= 330 && circleY <= 370)
			{

			       flag = 0;
			       if(circleY >= 355 && circleY <= 370)
			       {
					if(circleX <= 540 && circleX >= 539 || circleX >= 520 && circleX <= 521)
					{
					  flag = 1;
					  collision();
					}
					else if(circleX <= 410 && circleX >= 409 || circleX >= 390 && circleX <= 391)
					{
					  flag = 1;
					  collision();
					}
					else if(circleX <= 280 && circleX >= 279 || circleX >= 260 && circleX <= 261)
					{
					  flag = 1;
					  collision();
					}
					else
					  flag = 0;
				}

				if(circleY >= 330 && circleY <= 345)
				{
					if(circleX <= 470 && circleX >= 469 || circleX >= 450 && circleX <= 451)
					{
					  flag = 1;
					  collision();
					}
					else if(circleX <= 340 && circleX >= 339 || circleX >= 320 && circleX <= 321)
					{
					  flag = 1;
					  collision();
					}
					else if(circleX <= 210 && circleX >= 209 || circleX >= 190 && circleX <= 191)
					{
					  flag = 1;
					  collision();
					}
					else
					  flag = 0;
				}

			 }
			else if(circleX >= 70 && circleX <= 130 && circleY >= 200 && circleY <= 330)
			{

				if(circleY >= 230 && circleY <= 310)
				{
					if(circleX >= 130)
					  flag = 1;
					else
					  flag = 0;
				}
				else
				  flag = 0;
			}
			else if(circleX >= 130 && circleX <= 620 && circleY >= 200 && circleY <= 310)
			{
				if(circleY >= 230 && circleY <= 310)
				{
					if(circleX <= 150)
					  flag = 1;
					else
					  flag = 0;
				}
				else
				 flag = 0;

				 if(circleX >= 550 && (circleY >= 200 && circleY <= 310))
				 {
				   marioblack(circleX , circleY);
				   PortalTransport();
				 }

		       }
		//Special boundaries for the Portals
		else if(circleX >= 150 && circleX <= 260 && circleY >= 20 && circleY <= 180)
		{
		   flag = 0;
		   if(circleX >= 175 && circleX <= 235 && circleY >= 60 && circleY <= 140)
		   {
		     if(circleX >= 175 && circleY >= 70 && circleY <= 130)
		     {
		       marioblack(circleX , circleY);
		       PortalTransport();
		     }
		     else
		      flag = 1;
		   }
		}
		else if(circleX >= 280 && circleX <= 400 && circleY >= 20 && circleY <= 180)
		{
		   flag = 0;
		   if(circleX >= 315 && circleX <= 375 && circleY >= 60 && circleY <= 140)
		   {
		     if(circleX >= 315 && circleY >= 70 && circleY <= 130)
		     {
		       marioblack(circleX , circleY);
		       PortalTransport();
		     }
		     else
		      flag = 1;
		   }
		}
		else if(circleX >= 420 && circleX <= 520 && circleY >= 20 && circleY <= 180)
		{
		  flag = 0;
		   if(circleX >= 450 && circleX <= 510 && circleY >= 60 && circleY <= 140)
		   {
		     if(circleX >= 450 && circleY >= 70 && circleY <= 130)
		     {
		       marioblack(circleX , circleY);
		       PortalTransport();
		     }
		     else
		      flag = 1;
		   }
		}
		else if(circleX >= 550 && circleX <= 620 && circleY >= 45 && circleY <= 180)
		{
		  flag = 0;
		  if(circleX >= 555 && circleX <= 615 && circleY >= 65 && circleY <= 130)
		  {

			delay(100);
			cleardevice();
			setcolor(WHITE);
			//CREDITS - Code brought back to LHS for convenience

    //Space Pixels
   for(int x = 0; x < 200; x++)
   {
	int midx =  random(640);
	int midy =  random(480);
	int color =  random(15);
	putpixel(midx, midy, color);
   }

   for(i = 20; i < 620; i++)
   {
	line(20, 20, i, 20);
	delay(1);
	if(620 - i >= 20)
	{
	    line(620, 460, 620 - i, 460);
	    delay(1);
	}
   }
   for(j = 20; j < 460; j++)
   {
	line(20, 20, 20, j);
	delay(1);
	if(480 - j >= 20)
	{
	    line(620, 460, 620, 480 - j);
	    delay(1);
	}
   }
   delay(400);
   outtextxy(65, 140, "You have cleared the maze and brought all of Mario's powers back!");
   delay(2000);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
   char str1[100], ar1[16], ar2[16];
   setcolor(LIGHTRED);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   ar1[16] = '\0';
   for(int f = 0; f < 16; f++)
    ar1[f] = ' ';
   ar2[16] = '\0';
   for(f = 0; f < 16; f++)
    ar2[f] = ' ';
   strcpy(str1, "CONGRATULATIONS!");
   for(int g = 0; g < 16; g++)
   {
       ar2[g] = str1[g];
       if(g != 0) ar2[g-1] = ' ';
       for(f = 0; f < 12; f++)
       {
	    setcolor(0);
	    outtextxy(getmaxx()/2, getmaxy()/2-(20-(f-1)*2)-30, ar2);
	    setcolor(LIGHTRED);
	    outtextxy(getmaxx()/2, getmaxy()/2-(20-(f*2))-30, ar2);
	    setcolor(0);
	    outtextxy(getmaxx()/2, getmaxy()/2+((f-1)*2)-30, ar1);
	    setcolor(LIGHTRED);
	    outtextxy(getmaxx()/2, getmaxy()/2+(f*2)-30, ar1);
       }
   }
   delay(1000);

   //Credits Text
   setcolor(WHITE);
   settextstyle(SMALL_FONT, HORIZ_DIR, 5);
   outtextxy(200, 250, "D");
   delay(100);
   outtextxy(207, 250, "e");
   delay(100);
   outtextxy(214, 250, "v");
   delay(100);
   outtextxy(221, 250, "e");
   delay(100);
   outtextxy(228, 250, "l");
   delay(100);
   outtextxy(233, 250, "o");
   delay(100);
   outtextxy(240, 250, "p");
   delay(100);
   outtextxy(247, 250, "e");
   delay(100);
   outtextxy(254, 250, "d");
   delay(100);
   outtextxy(261, 250, " ");
   delay(100);
   outtextxy(268, 250, "b");
   delay(100);
   outtextxy(275, 250, "y");
   delay(100);
   outtextxy(282, 250, " ");
   delay(100);
   outtextxy(289, 250, "S");
   delay(100);
   outtextxy(296, 250, "h");
   delay(100);
   outtextxy(303, 250, "r");
   delay(100);
   outtextxy(310, 250, "e");
   delay(100);
   outtextxy(317, 250, "y");
   delay(100);
   outtextxy(324, 250, "a");
   delay(100);
   outtextxy(331, 250, "s");
   delay(100);
   outtextxy(338, 250, " ");
   delay(100);
   outtextxy(345, 250, "a");
   delay(100);
   outtextxy(352, 250, "n");
   delay(100);
   outtextxy(359, 250, "d");
   delay(100);
   outtextxy(366, 250, " ");
   delay(100);
   outtextxy(373, 250, "S");
   delay(100);
   outtextxy(380, 250, "r");
   delay(100);
   outtextxy(387, 250, "e");
   delay(100);
   outtextxy(394, 250, "y");
   delay(100);
   outtextxy(401, 250, "e");
   delay(100);
   outtextxy(408, 250, "s");
   delay(100);
   outtextxy(415, 250, ".");
   delay(200);
   for(i = 198; i < 416; i++)
   {
	line(200, 260, i, 260);
	delay(5);
   }
   delay(3000);
   exit(0);
		  }
		}
	       else
		flag = 1;
	}
	else
	 flag = 1;


      if(flag != 0)   // Test for collision
      {
	marioblack(circleX , circleY);
	circleX -= h;
	circleY -= k;
	setcolor(RED);
	circle(circleX , circleY , 8);
	MazeLines();
      }
}


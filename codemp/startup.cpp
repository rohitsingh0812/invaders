#include"inclusionparts.h"
double settingsLeftTopX =10.4091;
double settingsLeftTopY =1.77273;
double settingsRighBottomX =15.9545;
double settingsRightBottomY =3.54545;
//boundary x and y coordinates of settings button
double backLeftTopX =0.681818;
double backLeftTopY =16.2955;
double backRighBottomX =3.5;
double backRightBottomY =17.6364;
//boundary x and y coordinates of back button
double win4x=23.8,win4y=18.5;//stores boundary x and y coordinates for window W4
bool settingsWin=false;//stores whether settings window is active or not
bool htpWin=false;//stores whether how to play window is active or not
color randomColor()
{
//generates a random color for statrtup animation (flying dots) using these six colors
	switch (rand()%6)
	{
		case 0 :
			return(Blue);
		case 1 :
 			return(Cyan);
		case 2 :
			return(Yellow);
		case 3 :
			return(Green);
		case 4 :
			return(Magenta);
		case 5 :
			return(Red);
	}
}
double calculateY(int i)
{
//manipulated y function for i'th dot(circle) so that its final position is the requisite value as stored in the 
//array showUpCentres 
	double xi=showUpCentres[i].GetXDistance();
	double yi=showUpCentres[i].GetYDistance();
	double x=(counter/NDIV)*xi*(1+4*sin(PI*x/xi)*sin(PI*(win4x-x)/xi));
	return(((0.0035*(xi-x)*(win4x-xi-x)*(i*i*sin(i*i)+1)/(NDIV-i))*sin(PI*x/xi)*sin(PI*(win4x-x)/xi))+yi);
	//sin ensures proper end coordinate from random appearing function
	
}
void showrectangles()
{
//shows eight rectangles around 4 menu operations
       	double pt[4][4];
       	fillup(pt);
       	createrectangle(pt[0],Black,Cyan);
       	createrectangle(pt[1],Blue,Yellow);
       	createrectangle(pt[2],Green,Black);
       	createrectangle(pt[3],Red,Yellow);
       	return;
}
void transform(double &x,double &y,int i)
{
//ensures that some dots fit into the window
	if(i%8!=0)
	return;
	if(x<=0 || x>=win4x)
	{
		x= (((int(x*10000 + x*x*2000))%10000)*(win4x-1)/10000.0) + x-int(x);
	}
	if(y<=0 || y>=win4y)
	{
		y= (((int(y*10000 + y*y*2000))%10000)*(win4y-1)/10000.0) + y-int(y);
	}
	return ;
}
int spltimer()
{
//timer function for animation(flying dots)
	if(counter==NDIV+1)
	{
		//stop the timer after calling it NDIV(constant) times
		sleep(1);
		stylishINV.Load("../images/title.xpm");
        	assert(stylishINV.GetStatus() == BitMapOkay);
        	stylishINV.SetPosition(Position(3.20912, 1.15909));
        	stylishINV.Draw();
		
		W4.RenderRectangle(Position(4.36364,7.36364),Position(20.6364,7.56364),Red,false);
		for(int i=0;i<NDOTS;i++)
        	{
       			double yco=showUpCentres[i].GetYDistance();
       			double xco=showUpCentres[i].GetXDistance();

       			CircleShape C(W4,Position(xco,yco),randomColor(),0.15);
			C.Draw();
        	}
        	W4.StopTimer();
        	loadingWindow();
        	return 1;
	}
       	W4.RenderRectangle(Position(0,0),Position(win4x,win4y),Black,false);
        
        
	for(int i=0;i<NDOTS;i++)
        {
       		double yco=calculateY(i);
       		double xco;
       		double xi=showUpCentres[i].GetXDistance();
       		xco=counter*showUpCentres[i].GetXDistance()/NDIV;
       		if(i%2==1)
       		xco=(win4x*(NDIV-counter)/NDIV+counter*(showUpCentres[i].GetXDistance())/NDIV);
		xco=xco*(1+4*sin(PI*xco/xi)*sin(PI*(win4x-xco)/xi));
		transform(xco,yco,i);
		//for each call decide x and y coordinates using the specific function 
		//that must have its final x,y as recorded in the array from file
       		CircleShape C(W4,Position(xco,yco),randomColor(),0.15);
		C.Draw();
		//draw all 226(NDOTS) circles with random colors
        }
        W4.RenderText(Position(11.9,12.0),"",Yellow,Red);
        counter++;
        
}
void invadersShowUp()
{
	//opens startup window for animation (setting the centres x,y) and then setting timer after each 7 milli-seconds
	W4.Open();
	W4.RenderRectangle(Position(0,0),Position(win4x,win4y),Black,false);
        for(int i=0;i<NDOTS;i++)
        {
       		double X,Y;
		fcentres>>X>>Y;
        	showUpCentres[i]=Position(X,Y);
        }
        W4.SetTimerCallback(spltimer);
        W4.StartTimer(7);
}
void loadingWindow()
{
	//shows loading bar progressing while converting jpg files to .xpm PixMap files using system shell commands
	int nFiles=27;//no. of file sto be conerted -- names stored in jpg.txt and xpm.txt i n ../data folder
	ifstream f1("../data/jpg.txt");
	ifstream f2("../data/xpm.txt");
	double d=100.00/nFiles;//used for equal progress of loading bar per file
	//string strload="Loading 0 %";
	//W4.RenderText(Position(11.9,12.0),strload,Yellow,Red);
	loadBmp.Load("../images/loading.xpm");
        assert(loadBmp.GetStatus() == BitMapOkay);
       	loadBmp.SetPosition(Position(8.4, 9));
       	loadBmp.Draw();
	W4.RenderRectangle(Position(5.9,13),Position(17.9,13.4),Red,true);
	W4.RenderText(Position(11.9,12.0),"",Yellow,Red);
	string jpg;
	string xpm;
	for(int i=0;i<nFiles;i++)
	{

		f1>>jpg;
		f2>>xpm;
		string t ="convert "+jpg+" "+xpm;
		system(t.c_str());
		//string strload="Loading " + itoa(ceil(d*(i+1)))+" %";
		//W4.RenderText(Position(11.9,12.0),strload,Yellow,Red);
		double xCoOrd=5.9 +12.0*ceil(d*(i+1))/100.0;
		W4.RenderRectangle(Position(5.9,13),Position(xCoOrd,13.4),Blue,false);
		W4.RenderText(Position(11.9,12.0),"",Yellow,Red);//for flushing the output before next shell command
	}
	usleep(300000);
	startup();
}
void setUpCountries()
{
	//retrieves data of each country circle ( centre positions and diameters) from ../data/countrycircles.txt or
	// ../data/countrycircles2.txt depending upon whether map ==0 or map==1
	if(map==0)
	{
		ifstream fcircles("../data/countrycircles.txt");
		for(int i=0;i<NCountry;i++)
		{
			double x,y;
			fcircles>>x>>y>>diameters[i];
			centers[i]=Position(x,y);
		}
	}
	if(map==1)
	{
		ifstream fcircles("../data/countrycircles2.txt");
		for(int i=0;i<NCountry;i++)
		{
			int c;
			double x,y,d;
			fcircles>>c>>x>>y>>d;
			diameters[c]=d;
			centers[c]=Position(x,y);
		}
	}

}
void gameproceed()
{
/*
   void gameproceed()
   Function:  opens main window W1 for game to proceed with current settings(may be default)
   Inputs:
      Arguments: --
      Global Variables: string strComp,strPhase -- string to be printed while showing reinforcements / clicking 
      			for player2/computer and current game phase respectively
  			int focus for click event resolution in different windows
  			int NCountry
  			SimpleWindow W1 and associated bitmaps W1Bmp*
   Outputs:
      Return Value: void
      Reference Arguments: --
      Globals: focus set to 1(W1)

   Assumptions/Preconditions:(input from user through mouse/////calls other functions for saving / loading)

   Errors:
*/ 
	setUpCountries();
	W1.Open();
	//opens main window W1 for game to proceed with given settings(may be default)
	focus=1;
        assert(W1.GetStatus() == WindowOpen);
        if(map==0)
        {
		W1Bmp.Load("../images/World.xpm");
	}
	else
	{
		W1Bmp.Load("../images/World2.xpm");
	}
	W1Bmp2.Load("../images/lr.xpm");
	W1Bmp3.Load("../images/ud.xpm");
	W1Bmp4.Load("../images/lr.xpm");
	W1Bmp5.Load("../images/ud.xpm");
        assert(W1Bmp.GetStatus() == BitMapOkay);
        W1Bmp.SetPosition(Position(0.25, 0.5));
        W1Bmp2.SetPosition(Position(0, 0));
        W1Bmp3.SetPosition(Position(0, 0));
        W1Bmp4.SetPosition(Position(28.9,0));
        W1Bmp5.SetPosition(Position(0, 19.4));
        W1Bmp2.Draw();
        W1Bmp3.Draw();
        W1Bmp4.Draw();
        W1Bmp5.Draw();
        W1Bmp.Draw();
        W1.RenderText(Position(15,19.8),spaces(194),Yellow,Red);
	if(loaded==0)
	{	
		int gamemap[NCountry];
		int soldiers[NCountry];
	        randomdist(gamemap,soldiers);
		for(int i=0;i<NCountry;i++)
	        {
	                all[i].ownership=gamemap[i];
	                all[i].nos = soldiers[i];
		}
		//random distribution of countries and soldiers
		
	}
	if(multiplayer)
	strComp="Player 2";
        PrintPhase();
	ShowEndTurn();
	ShowSaveGame();
	ShowMainMenu();
	refreshLines();
        refresh2();
        PrintLeft("   You haven't selected any country   ");
	PrintRein();
        getclick();

}
void createrectangle(double a[4],color cl1,color cl2)
{
//creates eight rectangles around 4 menu operations in startup window
	Position myp[4]={Position(a[0],a[1]),Position(a[0],a[2]),Position(a[3],a[2]),Position(a[3],a[1])};
        Position myq[4]={Position(a[0]-0.2,a[1]-0.2),Position(a[0]-0.2,a[2]-0.2),Position(a[3]-0.2,a[2]-0.2),Position(a[3]-0.2,a[1]-0.2)};
        for(int i=0;i<4;i++)
        {
        	W4.RenderLine(myp[i],myp[(i+1)%4],cl1,0.05);
        	W4.RenderLine(myq[i],myq[(i+1)%4],cl2,0.05);
        }
}
void fillup(double pt[4][4])
{
//sets up positions for creating rectangles
//in the double array(2D) pt[4][4] as x,y coordinates for top left of the rectangle
	double x1=4.96,x2=11.25,y1=4.85,y2=6.3;
        pt[0][0]=x1;
        pt[0][1]=y1;
        pt[0][2]=y2;
        pt[0][3]=x2;
        for(int i=1;i<=3;i++)
        {
       		pt[i][0]=pt[i-1][0]+3.0;
        	pt[i][1]=pt[i-1][1]+2.2;
        	pt[i][2]=pt[i-1][2]+2.2;
        	pt[i][3]=pt[i-1][3]+3.0;
        	
        }
}
void startup()
{
//creates startup environment by loading bitmap and setting up rectangles
	if(W4.GetStatus() != WindowOpen)
	W4.Open();
	loaded=0;
	ls="load";
        assert(W4.GetStatus() == WindowOpen);
	W4.RenderRectangle(Position(0,0),Position(win4x,win4y),Black,false);
        W4Bmp.Load("../images/31.xpm");
        assert(W4Bmp.GetStatus() == BitMapOkay);
        W4Bmp.SetPosition(Position(0.25, 0.5));
        W4Bmp.Draw();
	showrectangles();
	W4.SetMouseClickCallback(f);
        return;
}
//declaring central positions for check boxes(option buttons) made in settings window as per their function
Position easy=Position(1.88636,6.63636);
Position medium=Position(1.88636,8.15909);
Position hard=Position(1.90909,9.59091);//levels
Position HVsC=Position(13.5,7.18182);
Position HVsH=Position(13.5,8.40909);//game type human v/s comp etc
Position mapOld=Position(3,14.4773);
Position mapNew=Position(13.7045,14.6136);//map old or new
Position distrP=Position(12.1364,10.5682);
Position distrC=Position(16.6591,10.6136);//post war distribution type
bool clickedInside(Position p,Position check)
{
//returns whether the click has been made on a check box or not
//i.e position p lies in a rectangle with centre Position(check) and side = 0.4 cm or not
        double x=p.GetXDistance();
        double y=p.GetYDistance();
        double xc=check.GetXDistance();
        double yc=check.GetYDistance();
        if(fabs(x-xc)<=0.2 && fabs(y-yc)<=0.2)
        return true;
        else
        return false;
}
void drawCheck(Position p)
{
//draw solid Black Circle i.e select a check box/option button
	CircleShape C(W4,p,Black,0.15);
	C.Draw();	
}
void removeCheck(Position p)
{
//draw White Circle(with black boundary) i.e deselect a check box/option button
	CircleShape C(W4,p,White,0.15);
	C.Draw();	
}
int settingsClick(const Position& p)
{
/*
   int settingsClick(const Position& p)
   Function:   performs necessary actions when a click is made in setting window
   Inputs:
      Arguments: const Position& p(of click)
      Global Variables: all posiitions of option buttons and back_button's end cocordinates
      			settings variables --
      			bool multiplayer -- game mode -- single player v/s computer or two players
      			int map -- old or new map
      			int level -- easy / medium / hard levels
      			int redistr -- type of redistribution after war
   Outputs:
      Return Value: int
      Reference Arguments: const Position& p(not changed)
      Globals:  sets up the setting variables as per the clicks made by user

   Assumptions/Preconditions: settingsWin==true i.e window in focus is settings window

   Errors:
*/

        double x=p.GetXDistance();
        double y=p.GetYDistance();
	if(x>=backLeftTopX && y>=backLeftTopY && x<=backRighBottomX && y<=backRightBottomY)
        {
        	startup();
        	settingsWin=false;
        	return 1;
        }
        if(clickedInside(p,easy))
        {
        	level=0;
        	drawCheck(easy);
        	removeCheck(medium);
        	removeCheck(hard);
        }
        if(clickedInside(p,medium))
        {
        	level=1;
        	removeCheck(easy);
        	drawCheck(medium);
        	removeCheck(hard);
        }
        if(clickedInside(p,hard))
        {
        	level=2;
        	removeCheck(easy);
        	removeCheck(medium);
        	drawCheck(hard);
        }
        if(clickedInside(p,HVsC))
        {
        	multiplayer = false;
        	removeCheck(HVsH);
        	drawCheck(HVsC);
        }
        if(clickedInside(p,HVsH))
        {
        	multiplayer=true;
        	removeCheck(HVsC);
        	drawCheck(HVsH);
        }
        if(clickedInside(p,mapOld))
        {
        	map=0;
        	removeCheck(mapNew);
        	drawCheck(mapOld);
        }
        if(clickedInside(p,mapNew))
        {
        	map=1;
        	removeCheck(mapOld);
        	drawCheck(mapNew);
        }
        if(clickedInside(p,distrP))
        {
        	redistr=0;
        	removeCheck(distrC);
        	drawCheck(distrP);
        }
        if(clickedInside(p,distrC))
        {
        	redistr=1;
        	removeCheck(distrP);
        	drawCheck(distrC);
        }
        //cout<<"("<<p.GetXDistance()<<","<<p.GetYDistance()<<")"<<multiplayer<<"\t"<<level<<"\t"<<map<<endl;
        return 1;
}
int mouseClickFocus4(const Position& p)
{
//handles clicks when focus==4 i.e startup window clicks management
	double pt[4][4];
        fillup(pt);
        double x=p.GetXDistance();
        double y=p.GetYDistance();
        //getting bounds for checking for clicks in startup main window
        //cout<<"Position("<<x<<","<<y<<")"<<endl;
        if(settingsWin==true)
        {
        //when settings Window is active
        	settingsClick(p);
        	return 1;
        }
        if(htpWin==true)
        {
        //when "How To Play" Window is active
        //go back to original basic startup window when clicked on back button
        	if(x>=backLeftTopX && y>=backLeftTopY && x<=backRighBottomX && y<=backRightBottomY)
        	{	
        		htpWin=false;
        		startup();
        		return 0;
        	}
        }
        if(x>=settingsLeftTopX && y>=settingsLeftTopY && x<=settingsRighBottomX && y<=settingsRightBottomY)
        {
        //transition from basic main window to settings window
        	W4Bmp.Load("../images/3.xpm");
        	assert(W4Bmp.GetStatus() == BitMapOkay);
        	W4Bmp.SetPosition(Position(0.25, 0.5));
        	W4Bmp.Draw();
        	settingsWin=true;
        	htpWin=false;
        	removeCheck(easy);
        	removeCheck(medium);
        	removeCheck(hard);
        	if(level==0)
        		drawCheck(easy);
        	if(level==1)
        		drawCheck(medium);
        	if(level==2)
        		drawCheck(hard);
        	removeCheck(HVsC);
        	removeCheck(HVsH);
        	if(multiplayer==false)
        		drawCheck(HVsC);
        	if(multiplayer==true)
        		drawCheck(HVsH);
        	removeCheck(mapOld);
        	removeCheck(mapNew);
        	if(map==0)
        	drawCheck(mapOld);
        	if(map==1)
        	drawCheck(mapNew);
        	removeCheck(distrP);
        	removeCheck(distrC);
        	if(map==0)
        	drawCheck(distrP);
        	if(map==1)
        	drawCheck(distrC);
        //showing checks as per the current settings
        	return 1;
        }

        if(x>=pt[0][0] && x<=(pt[0][3]-.2) && y>=pt[0][1] && y<=(pt[0][2]-.2))
        {
        //clicked on play game button
        	createrectangle(pt[0],Blue,Black);
        	W4.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(150000);
        	createrectangle(pt[0],Yellow,Red);
        	W4.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(150000);
		gameproceed();
		//proceed with game and close startup window
		W4Bmp.Erase();
		W4.Close();
		return 1;
	}
	if(x>=pt[1][0] && x<=(pt[1][3]-.2) && y>=pt[1][1] && y<=(pt[1][2]-.2))
        {
	//clicked on how to play button
	//show hoe to play .xpm file for instructions
		createrectangle(pt[1],Black,Blue);
        	W4.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(150000);
        	createrectangle(pt[1],Yellow,Red);
        	W4.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(150000);
		W4Bmp.Load("../images/htp.xpm");
        	assert(W4Bmp.GetStatus() == BitMapOkay);
        	W4Bmp.SetPosition(Position(0.25, 0.5));
        	W4Bmp.Draw();
        	htpWin=true;
        	settingsWin=false;
	}
	if(x>=pt[2][0] && x<=(pt[2][3]-.2) && y>=pt[2][1] && y<=(pt[2][2]-.2))
        {
	//clicked on load game button
	//show load game window(common with save game window but gloabal string ls=="load")
        	createrectangle(pt[2],Blue,Black);
        	W4.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(150000);
        	createrectangle(pt[2],Yellow,Red);
        	W4.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(150000);
		ls="load";
		showsave();
		W4Bmp.Erase();
		W4.Close();
	}
	if(x>=pt[3][0] && x<=(pt[3][3]-.2) && y>=pt[3][1] && y<=(pt[3][2]-.2))
        {
	//clicked on quit button
	//show thank you message
		createrectangle(pt[3],Black,Yellow);
        	W4.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(150000);
        	createrectangle(pt[3],Black,Blue);
        	W4.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(150000);
		W4Bmp.Erase();
		W4.Close();
		showmsg.msg="Thank You for Playing Invaders...";
		showmsg.show();
	}
	return 0;
}

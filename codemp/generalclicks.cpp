#include"inclusionparts.h"
int f(const Position& p)
{	
/*
   int f(const Position& p)
   Function:  responds to mouse click event on all windows present in the game(using focus variable for resolution)
   Inputs:
      Arguments: const Position& p(position of mouse click)
      Global Variables: message showmsg -- for showing different messages
      			bool working for knowing whether system is busy or not
      			string ls -- to know whether savegame window is being opened for saving or loading a game
      			int NCountry -- no. of countries
      			country all[]
  
   Outputs:
      Return Value: int
      Reference Arguments: Position p(not changed)
      Globals: message showmsg.msg -- updated message to be shown

   Assumptions/Preconditions:(input from user through mouse/////calls other functions for other input checks)

   Errors:
*/   
	//cout<<focus<<endl;cout.flush();
	if(focus==5)
	{
		return mouseClickFocus5(p);
	}
	if(focus==32)
	{
		return mouseClickFocus32(p);
	}
	if (focus==3)
	{
		return mouseClickFocus3(p);
	}
	if(focus==2)
	{
		if(MM.IsInside(p))
		{
			//clicked on Main Menu Button
			MM.Load("../images/MMp.xpm");
        		MM.SetPosition(Position(19.2, 20.1));
        		MM.Draw();
        		flush();
        		usleep(50000);
        		MM.Load("../images/MMup.xpm");
        		MM.SetPosition(Position(19.2, 20.1));
        		MM.Draw();
        		//to show pressing button effect
        		flush();
        		prevfocus=2;
			showmsg.msg=" Do you want to leave this game? ";
			showmsg.ShowOkCancel();//showing message
			return 1;
		}
		return mouseClickFocus2(p);
	}
	if (focus==4)
	{
		return mouseClickFocus4(p);
	}
	if(working)
	return 0;
	//focus==1
	if(MM.IsInside(p))
	{
		//clicked on Main Menu Button
		MM.Load("../images/MMp.xpm");
        	MM.SetPosition(Position(19.2, 20.1));
        	MM.Draw();
        	flush();
        	usleep(100000);
        	MM.Load("../images/MMup.xpm");
        	MM.SetPosition(Position(19.2, 20.1));
        	MM.Draw();
        	flush();
        	prevfocus=1;
		showmsg.msg=" Do you want to leave this game? ";
		showmsg.ShowOkCancel();
		return 1;
	}
	if(SG.IsInside(p))
	{
		//clicked on Save Game Button
		ls="save";
		PrintLeft(" Saving...");
		SG.Load("../images/SGp.xpm");
        	SG.SetPosition(Position(7.2, 20.1));
        	SG.Draw();
        	flush();
        	usleep(100000);
        	SG.Load("../images/SGup.xpm");
        	SG.SetPosition(Position(7.2, 20.1));
        	SG.Draw();
        	flush();
        	showsave();
	}		
	if(ET.IsInside(p))
	{	
		//clicked on End Turn Button
		ET.Load("../images/ETp.xpm");
        	ET.SetPosition(Position(13.2, 20.1));
        	ET.Draw();
        	flush();
        	usleep(100000);
        	ET.Load("../images/ETup.xpm");
        	ET.SetPosition(Position(13.2, 20.1));
        	ET.Draw();
        	flush();
        	if(!(multiplayer))
		working=true;
		PrintRein();
		strphase="Reinforcement Phase";
		PrintPhase();
		refresh2();
		showmsg.msg=" You have to click on the country to increment number of^ soldiers. Till the number of reinforcement becomes less^ than 5, 5 soldiers are added. After that only one^ soldier will get incremented at a click. Make ^the most helpful distribution of the soldiers you have.";
		 //Included in How to play???
		showmsg.show();
		for(int i=0;i<NCountry;i++)
		oldsold[i]=all[i].nos;
		reinf=reinforcement(turn);
		PrintLeft(" Start selecting countries... ");

		return 1;
	}
	return mouseClickFocus1NotButton(p);
}
void getclick(void)
{
//sets click and keyboard callback of window W1
        W1.SetMouseClickCallback(f);
        W1.SetKeyPressCallback(keypress);
}

#include"inclusionparts.h"
string cheat="";
bool cheatActivate=false;



int keypress(int keycode) 
{
/*
   int keypress(int keycode) 
   Function:  responds to keyboard inputs for cheat codes
   Inputs:
      Arguments: keycode(input from keyboard)
      Global Variables: string cheat -- cheatcode
      			bool cheatActivate -- whether cheats are activated or not
      			int NCountry -- no. of countries
      			country all[]
  
   Outputs:
      Return Value: int
      Reference Arguments: --
      Globals: string cheat(updated)
               bool cheatActivate -- whether cheats are activated or not

   Assumptions/Preconditions:(input from user through keyboard)

   Errors:
*/   
	if(keycode=='\b')
	{
		if(cheat=="")
		return 0;
		cheat=cheat.substr(0,cheat.length()-1);
		return 1;
	}

	int cheatturn;
	if((keycode>='0' && keycode<='9')||(keycode>='a' && keycode<='z') || (keycode>='A' && keycode<='Z'))
	{
		cheat+=(char)keycode;
	}
	else
	{
		return 1;
	}
	if(cheatActivate==false && cheat=="1act2")
	{
		cheatActivate=true;
		cheat="";
		return 1;
	}
	if(cheatActivate==true && cheat=="2dea1")
	{
		cheatActivate=false;
		cheat="";
		return 1;
	}
	if(cheatActivate==false)
	{
		return 0;
	}
	if(cheat.length()==5)
	{
		cheat="";
	}
	if(cheat.find("p1")>=0 && cheat.find("p1")<=cheat.length()-1)
	{
		cheatturn=1;
	}
	else if(!(multiplayer) && (cheat.find("c")>=0 && cheat.find("c")<=cheat.length()-1))
	{
		cheatturn=0;
	}
	else if(multiplayer && (cheat.find("p2")>=0 && cheat.find("p2")<=cheat.length()-1))
	{
		cheatturn=0;
	}
	else
	{
		return 0;
	}
	cheat="";
	int ct=0;
	for(int i=0;i<NCountry;i++)
	{
		if(all[i].ownership!=cheatturn)
		{
			if(all[i].nos>6)
			{
				all[i].nos--;
				highlight(i);
				ct++;
			}
		}
		if(ct>=5)
		break;
	}
	if(ct!=0)
	usleep(100000);
	refresh2();
	return 1;
}

int none()
{
	refresh();
	return 1;
}

int uplayer()
{
/*
   int uplayer()
   Function:  calculates no. of territories owned by player 1
   Inputs:
      Arguments: --
      Global Variables: NCountry
      			country all[]
  
   Outputs:
      Return Value: int -- no. of territories owned by player 1
      Reference Arguments: --
      Globals: --

   Assumptions/Preconditions:

   Errors:
*/  
	int h=0;
	for(int i=0;i<NCountry;i++)
	{
		if(all[i].ownership==1)
		h++;
	}
	return h;
}
 
string itoa(int i)
{
/*
   string itoa(int i)
   Function:  convert integer to string using stringstream
   Inputs:
      Arguments: int i
      Global Variables: --
  
   Outputs:
      Return Value: string(converted integer)
      Reference Arguments: --
      Globals: --

   Assumptions/Preconditions:

   Errors:
*/ 
	stringstream oss;
	oss<<i;
	return(oss.str());
}
void flush(void)
{
//for flushing output to window W1 -- last statement before usleep() may not be executed at appropriate time
//by making this the last statement
	W1.RenderText(Position(0,19.8),"",Yellow,Red);
	return;
}

void PrintPhase()
{
//prints current phase of game using global variable strPhase and function spaces() for blanks;
	W1.RenderText(Position(15,0.2),spaces(24),Yellow,Black);
        W1.RenderText(Position(15,0.2),strphase,Yellow,Black);
        flush();
}

void highlight(int i)
{
/*
   void highlight(int i)
   Function:  highlighting a country in red 
   Inputs:
      Arguments: int i
      Global Variables: Position centres[],double diameters
  
   Outputs:
      Return Value: void
      Reference Arguments: --
      Globals: no change
      highlights given counry with id = i in Red color

   Assumptions/Preconditions:

   Errors:
*/ 
	 CircleShape C(W1,centers[i],Red,diameters[i]);
	 C.Draw();
	 W1.RenderText(centers[i],itoa(all[i].nos),Yellow,Red);
	 flush();
}

color getColor(int i)
{
//returns colour of the player
//yellow for computer/player 2 and white for player 1
	if(all[i].ownership==0)
	return Yellow;
	return White;
}
int wsgQuit()
{
//quits(QuitCallback) a savegame window while maintaining a proper flow of calling window
	if(W1.GetStatus()==WindowOpen)
	{
		focus=1;
		Wsg.Close();
		return 1;
	}
	focus=4;
	startup();
	Wsg.Close();
	return 1;
}
int quitW3()
{
//quits(QuitCallback) a message window while maintaining a proper flow of calling window
	if(focus==3)//normal ok window
	{
		f(Position(5.1,4.2));
	}
	if(focus==32)//input ok/cancel window
	{
		f(Position(6.6,4.2));
	}
	return 0;
}
void ShowEndTurn()
{
//shows End Turn Button
       	ET.Load("../images/ETup.xpm");

        ET.SetPosition(Position(13.2, 20.1));
        
        ET.Draw();
       	flush();
}
void ShowSaveGame()
{
//shows Save Game button
       	SG.Load("../images/SGup.xpm");

        SG.SetPosition(Position(7.2, 20.1));
        
        SG.Draw();
       	flush();
}
void ShowMainMenu()
{
//shows Main Menu button
       	MM.Load("../images/MMup.xpm");

        MM.SetPosition(Position(19.2, 20.1));
        
        MM.Draw();
       	flush();
}

string spaces(int n)
{
//returns string containing exactly n spaces ( n is the argument)
	string returnString="";
	for(int i=0;i<n;i++)
	{
		returnString+=" ";
	}
	return returnString;
}

void PrintLeft(string str)
{
//prints the given string str(argument) on the left bottom side of the screen
	W1.RenderText(Position(3,19.8),spaces(128),Yellow,Red);
	W1.RenderText(Position(8.5,19.8),str,Yellow,Red);
	W1.RenderText(Position(0,19.8),"",Yellow,Red);
	return;
}
void PrintRein()
{
//prints the number of reinforcements for each player on the right bottom of the screen
	int r1=reinforcement(1);
	int r2=reinforcement(0);
	W1.RenderText(Position(22,19.8),spaces(60),Yellow,Red);
	W1.RenderText(Position(21.5,19.8),"No of reinforcement :Player 1 : "+itoa(r1)+"  "+strComp+" : "+itoa(r2),Yellow,Red);
	W1.RenderText(Position(0,19.8),"",Yellow,Red);
	return;
}
void PrintRein(int r1,int r2)
{
// overloaded function PrintRein : 
//this one used to print given integers instead of real current reinforcements.
	W1.RenderText(Position(22,19.8),spaces(90),Yellow,Red);
	string s ="No of reinforcement :Player 1 : "+itoa(r1)+"  "+strComp+" : "+itoa(r2);
	W1.RenderText(Position(21.5,19.8),s,Yellow,Red);
	flush();
	return;
}

void showsave()
{
/*
   void showsave()
   Function:  opens a savegame/loadgame window also sets click focus on the savegame/loadgame WIndow Wsg
   Inputs:
      Arguments: --
      Global Variables: string ls -- denoting whether the window is opened for saving or loading
  
   Outputs:
      Return Value: void
      Reference Arguments: --
      Globals: no change

   Assumptions/Preconditions:

   Errors:
*/ 
	Wsg.Open();

	back.Load("../images/back.xpm");
	back.SetPosition(Position(0,0));
	back.Draw();
	back.SetPosition(Position(12,0));
	back.Draw();
	back.SetPosition(Position(0,6));
	back.Draw();
	back.SetPosition(Position(12,6));
	back.Draw();
	back.SetPosition(Position(0,12));
	back.Draw();
	back.SetPosition(Position(12,12));
	back.Draw();
	game1.Load("../images/SG1.xpm");
	game1.SetPosition(Position(1.5,3));
	game1.Draw();
	game2.Load("../images/SG2.xpm");
	game2.SetPosition(Position(12.5,3));
	game2.Draw();
	game3.Load("../images/SG3.xpm");
	game3.SetPosition(Position(7,6.5));
	game3.Draw();
	game4.Load("../images/SG4.xpm");
	game4.SetPosition(Position(1.5,10));
	game4.Draw();
	game5.Load("../images/SG5.xpm");
	game5.SetPosition(Position(12.5,10));
	game5.Draw();
	if (ls=="load")
	{
		lg.Load("../images/loadgame.xpm");
		lg.SetPosition(Position(5.9,1.5));
		lg.Draw();
	};
	if (ls=="save")
	{
		sg.Load("../images/savegame.xpm");
		sg.SetPosition(Position(5.9,1.5));
		sg.Draw();
	};
	Wsg.RenderText(Position(0,0),"",Black,Black);
	focus =5;
	Wsg.SetMouseClickCallback(f);
	Wsg.SetQuitCallback(wsgQuit);
}


int getcountry(const Position &p)
{
/*
   int getcountry(const Position &p)
   Function:  //returns whether the given position lies in some country or not and also returns the country idnumber 
   	      //returns 100 when country notfound
   Inputs:
      Arguments: Position &p
      Global Variables: string ls -- denoting whether the window is opened for saving or loading
  
   Outputs:
      Return Value: int(country id number or 100)
      Reference Arguments: Position p(no change)
      Globals: no change

   Assumptions/Preconditions: no. of countries NCountry<100

   Errors:
*/ 


	int c=100; 
	for(int i=0;i<NCountry;i++)
        {
                if(isinside(p,i)==true)
                {
                        c=i;break;
                }
        }
        return c;
}
bool isinside(Position p,int l)
{
//returns whether user has clicked inside a country or not
        if((p.GetXDistance()-centers[l].GetXDistance())*(p.GetXDistance()-centers[l].GetXDistance())+(p.GetYDistance()-centers[l].GetYDistance())*(p.GetYDistance()-centers[l].GetYDistance())<=diameters[l]*diameters[l]/4)
                return(true);
        else
                return(false);
}

int defaultKey(int keycode) 
{
//Activates usage of Enter key as a default key(presses OK automatically) for message boxes
	if(keycode==13)
	{
		f(Position(5.1,4.2));
	}
	return 1;
}


#include"inclusionparts.h"
void loadgame(string filename)
{
//loads a game from specified file (specified by calling function)
//data is stored in ../data/ as .txt files
	loaded=1;
	ifstream fin(filename.c_str());
	for(int i=0;i<NCountry;i++)
	{
		fin>>all[i].ownership;
		fin>>all[i].nos;
	}
	if(multiplayer)
	fin>>turn;
	else
	turn=1;
	fin.close();
}
void savegame(string filename)
{
//saves present game from specified file (specified by calling function)
//data is stored in ../data/ as .txt files	
	ofstream fout(filename.c_str());
	for(int i=0;i<NCountry;i++)
	{
		fout<<all[i].ownership<<" "<<all[i].nos<<endl;
	}
	fout<<turn<<endl;
	fout.close();
} 
int mouseClickFocus5(const Position& p)
{
/*
   int mouseClickFocus5(const Position& p)
   Function:  responds to mouse click event on SaveGame window present in the game(focus=5)
   Inputs:
      Arguments: const Position& p(position of mouse click)
      Global Variables: message showmsg -- for showing saved game message
      			string ls -- to know whether savegame window is being opened for saving or loading a game
  			int focus for click event resolution in different windows
   Outputs:
      Return Value: int
      Reference Arguments: Position p(not changed)
      Globals: message showmsg.msg -- updated message to be shown

   Assumptions/Preconditions:(input from user through mouse/////calls other functions for saving / loading)

   Errors:
*/   
	if (ls=="load")
	{
		if(game1.IsInside(p))
		{
			loadgame("../data/savegame1.txt");
		}
		if(game2.IsInside(p))
		{
        		loadgame("../data/savegame2.txt");
		}
		if(game3.IsInside(p))
		{
			loadgame("../data/savegame3.txt");
		}
		if(game4.IsInside(p))
		{
			loadgame("../data/savegame4.txt");
		}
		if(game5.IsInside(p))
		{
			loadgame("../data/savegame5.txt");
		}
		gameproceed();
		Wsg.Close();
		return 0;
	}
	if (ls=="save")
	{
		bool g1=game1.IsInside(p);
		bool g2=game2.IsInside(p);
		bool g3=game3.IsInside(p);
		bool g4=game4.IsInside(p);
		bool g5=game5.IsInside(p);
		if(g1)
		{
			savegame("../data/savegame1.txt");
		}
		if(g2)
		{
			savegame("../data/savegame2.txt");
		}
		if(g3)
		{
			savegame("../data/savegame3.txt");
		}
		if(g4)
		{
			savegame("../data/savegame4.txt");
		}
		if(g5)
		{
			savegame("../data/savegame5.txt");
		}
		if(g1||g2||g3||g4||g5)
		{
			Wsg.Close();
			focus=1;
			showmsg.msg=" Game Saved.  Continue playing...";
			showmsg.show();
			PrintLeft(" Continue...");
		}
		return 0;
	}
	return 0; // neglect other clicks that are not on any of the buttons
}

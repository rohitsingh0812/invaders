#include"inclusion.h"

int ApiMain() 
{	strphase="Attack Phase";
	multiplayer=false;
	srand(((unsigned int)time(0)));
        ifstream fin("../data/neighbour.txt");
	ifstream fname("../data/name.txt");
	//inputs names and neighbour data from files for countries 
	for(int i=0;i<NCountry;i++)
	{
		fin>>all[i].non;
		int j;
		for(j=0;j<all[i].non;j++)
		fin>>all[i].neigh[j];
		getline(fname,all[i].name,'\n');
	}
	system("convert ../images/title.jpg ../images/title.xpm");
	system("convert ../images/loading.jpg ../images/loading.xpm");
	//converting two JPGs to XPMs as they are required by loading window
	usleep(600000);
	invadersShowUp(); // show startup animation and loading window to proceed furthur for the game
        return 0;
}
int ApiEnd()
{
	if(W1.GetStatus()==WindowOpen)
		W1.Close();
	if(W3.GetStatus()==WindowOpen)
		W3.Close();
	system("rm ../images/*.xpm");
	//system("make clean");
	return 0;
}

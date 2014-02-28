#include"inclusionparts.h"

void transfer(int i, int j, int transsol)
{
	transsol=transsol%all[i].nos;
	all[i].nos=all[i].nos-transsol;
	all[j].nos=all[j].nos+transsol;
	refresh2();
	return;
}
void transover()
{
	refresh();
	if (turn==1)
	showmsg.msg="Reinforcement phase is over.^Now its "+strComp+"'s turn.^Attack Phase Begins";
	else if(multiplayer)
	showmsg.msg="Reinforcement phase is over.^Now its Player 1's turn.^Attack Phase Begins";
	showmsg.show();
	refreshLines();
	refresh2();
	PrintRein();
	strphase="Attack Phase";
	PrintPhase();
	PrintLeft("   Reinforcement Phase is over   ");
	turn=(turn+1)%2;
}

int key(int keycode) 
{
	
	W3.RenderText(Position(6.0,3.0),spaces(80),Yellow,Red);
	if(keycode==13)
	{
		defaultKey(13);
		return 1;
	}
	if(keycode>='0' && keycode<='9')
	{
		if(en==0 && keycode=='0')
		{
			W3.RenderText(Position(6.0,3.0),itoa(en),Yellow,Red);
			return 1;
		}
		char alpha=keycode;
		ent+=alpha;	
	}
	if(atoi(ent.c_str())>= all[getcountry(first)].nos)
	{
		ent = itoa(en);
	}
	if(keycode=='\b' && ent!="")
	{
		ent=ent.substr(0,ent.length()-1);
	}
	en =atoi(ent.c_str());
	W3.RenderText(Position(6.0,3.0),itoa(en),Yellow,Red);
	
}
int trans(const Position& p)
{
	if(getcountry(p)==100)
	{
	transcount=0;
	refresh2();
	return 1;
	}
	if(all[getcountry(p)].ownership!=turn)
	return 1;
	if(transcount%2==0)
	{
		first=p;
		highlight(getcountry(first));
		transcount++;
		return 1;
	}
	
	int a=getcountry(first);
	int b=getcountry(p);
	bool areNeighbours=false;
	for(int h=0;h<all[a].non;h++)
	{
		if(all[a].neigh[h]==b)
		{
			areNeighbours=true;
			break;
		}
	}	
	if(areNeighbours==false)
	{
		PrintLeft("Choose a neighbour country.");
		return 1;
	}
	second=p;
	
	highlight(b);
	createTriangle(Red,a,b);
	CircleShape Ca(W1,centers[a],Red,diameters[a]);
        Ca.Draw();
        W1.RenderText(centers[a],itoa(all[a].nos),Yellow,Red);
	if(a==b)
	{
		PrintLeft("Choose a different country.");
		return 1;
	}
	transcount++;
	mid=true;
	en = all[a].nos-1;
	showmsg.msg="Enter number of soldiers to be tranferred from ^" + all[a].name +" to "+all[b].name +". (your^ input will be restricted to "+itoa(all[a].nos-1)+" )";
	showmsg.showenter();
	W3.SetKeyPressCallback(key);
	return 0;	
}
		

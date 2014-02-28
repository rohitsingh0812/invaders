#include"inclusionparts.h"
int getNOppNeighbours(int i)
{
//returns sum of number of opponent sodiers in the neighbourhood of a country
	int sum=0;
	int play=all[i].ownership;
	play=(play+1)%2; //play contains ownership id of opponent of country idno=i's owner
	for(int j=0;j<all[i].non;j++)
	{
		if(all[all[i].neigh[j]].ownership==play)
		sum+=all[all[i].neigh[j]].nos;
	}
	return sum;
}

bool willBeBlocked(int i,int j)
{
//returns whether after attacking and winning from country i(comp) to j(player1) soldiers of i will be blocked or not
	int a=all[i].nos;
	int b= all[j].nos;
	if(a==2)
	{
		return false;
	}
	for(int k=0;k<all[j].non;k++)
	{
		if(all[all[j].neigh[k]].ownership==1 && (a+1)>=b && all[all[j].neigh[k]].nos<sqrt((a+1)*(a+1)-b*b))
		return false;
	}
	return true;
}
void multipleAttackAI(int c)
{
//attack a country of opponent(player 1) from all neighbouring countries of computer
	for(int i=0;i<all[c].non;i++)
	{
		if(all[all[c].neigh[i]].ownership==0 && all[c].ownership==1 && all[all[c].neigh[i]].nos>1)
		attack(all[c].neigh[i],c);
	}
	return;
}
void AI(void)
{
//Makes appropriate moves for the computer by analysing certain factors
	if(won || lost)
	{
		return;
	}
	working=true;
	turn=0;
	strphase="Defense Phase";
	PrintPhase();
	for(int i=0;i<NCountry;i++)
	{	
		if(all[i].ownership==1 || all[i].nos==1)
			continue;
		int sum=0;
		for(int j=0;j<all[i].non;j++)
		{	if(all[all[i].neigh[j]].ownership==0)
				continue;
			if(getNOppNeighbours(all[i].neigh[j])>all[all[i].neigh[j]].nos+6 )
			{
				multipleAttackAI(all[i].neigh[j]);
				AI();
				return;
			}
			if(all[i].nos>all[all[i].neigh[j]].nos+4 && willBeBlocked(i,all[i].neigh[j])==false)
			{
				attack(i,all[i].neigh[j]);
				//attack if no. of soldiers is more by 4 in the attacker country and comp is not getting blocked
				//after the attack
				if(aimode==false)
				{
					AI();
				}
				return;
			}
			sum+=all[all[i].neigh[j]].nos;
		}
		//sum contains total number of opponent soldiers in the neighbourhood
		if(sum!=0 && (((float)all[i].nos)/sum)>=0.5 )
		{
			for(int j=0;j<all[i].non;j++)
			{	
				if(all[all[i].neigh[j]].ownership==1 && all[i].nos>=all[all[i].neigh[j]].nos && willBeBlocked(i,all[i].neigh[j])==false)
				{
					attack(i,all[i].neigh[j]);
					if(aimode==false)
					{
						AI();
					}
					return;
				}
			}
		}
	}
	
	refresh();
	strphase="Reinforcement Phase";
	PrintPhase();
	int reinf=reinforcement(0);
//	refresh2();
	aireinforce(reinf);
	
	refresh2();
	usleep(100000);
	//transfers
	int co,ci;
	// country pair with maximum sum of no. of opponent soldiers as neighbours of ci -(minus) that for co
	if(getMaxNCountry(co,ci,1) && co>=0 && co<=42 && ci>=0 && ci<=42 && all[co].nos>1)
	{
	// get country pair with maximum (sum of no. of opponent soldiers as neighbours of ci -(minus) that for co)
	// and transfer maximum possible sodiers from co to ci 
		PrintLeft("Transferring soldiers from " + all[co].name+ " to " + all[ci].name);
		highlight(co);
		flush();
		usleep(300000);
		highlight(ci);
		flush();
		usleep(300000);
		createTriangle(Red,co,ci);
		flush();
		sleep(1);
		transfer(co,ci,all[co].nos-1);
		refresh();
	} 
	working=false;
	turn=1;
	focus=1;
	c1=-1;c2=-1;
	strphase="Attack Phase";
	PrintLeft("Computer's turn is over. Your chance...  ");
	//being ready for player 1's attack phase
	showmsg.msg="Computer's Reinforcement Phase is over. ^ It's Your turn...^ Attack Phase Begins ";
	PrintRein();
	showmsg.show();
	PrintPhase();
	return;
}

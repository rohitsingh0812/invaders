#include"inclusionparts.h"
void refresh()
{	
	W1Bmp.Draw();
	if(map==1)
	refreshLines();
	refresh2();
	usleep(1000);
}
void drawLine(int i,int j)
{
	int x=all[i].ownership;
       	int y=all[j].ownership;
       	if(x!=y)
       	{
       		W1.RenderLine(centers[i],centers[j],Red,0.05);
       	}
       	else
       	{
       		if(x==0)
       		{
       			W1.RenderLine(centers[i],centers[j],Green,0.05);	
       		}
       		if(x==1)
       		{
       			W1.RenderLine(centers[i],centers[j],Cyan,0.05);	
       		}  
       	}
}
void refreshLines(int i,int k)
{
	if(map==0)
	return;
	for(int j=0;j<all[i].non;j++)
       	{     		
       		drawLine(i,all[i].neigh[j]);	
       	}
       	for(int j=0;j<all[k].non;j++)
       	{	      		
       		drawLine(k,all[k].neigh[j]);	
       	}
}
void refreshLines()
{
	if(map==0)
	return;
	for(int i=0;i<NCountry;i++)
       	{
       		for(int j=0;j<all[i].non;j++)
       		{
       			drawLine(i,all[i].neigh[j]);	
       		}
     	}
}
void refresh2()
{	
	PrintPhase();
	for(int i=0;i<NCountry;i++)
        {
               
                if(all[i].ownership==0)
                {
                CircleShape C(W1,centers[i],Yellow,diameters[i]);
                C.Draw();
                W1.RenderText(centers[i],itoa(all[i].nos),Black,Yellow);
                }
                else
                {
                CircleShape C(W1,centers[i],White,diameters[i]);
                C.Draw();
                W1.RenderText(centers[i],itoa(all[i].nos),Black,White);
                }
        }

        if(turn==1)
        {
        	PrintPhase();
        }
        flush();
}
bool getMaxNCountry(int &co,int &ci,int play)
{
// returns country pair with maximum sum of no. of opponent soldiers as neighbours of ci -(minus) that for co
	int maxsum=0;
	bool start=false;
	for(int i=0;i<NCountry;i++)
	{
		if(all[i].ownership==play)
			continue;
		for(int j=0;j<all[i].non;j++)
		{
			if(all[all[i].neigh[j]].ownership==play)
				continue;
			int checksum=getNOppNeighbours(i)-getNOppNeighbours(all[i].neigh[j]);
			if(start==false)
			{
				maxsum=checksum;
				start=true;
				co=all[i].neigh[j];
				ci=i;
			}
			else if(checksum>maxsum)
			{
				co=all[i].neigh[j];
				ci=i;
			}
			else if(checksum==maxsum && all[co].nos<all[all[i].neigh[j]].nos)
			{
				co=all[i].neigh[j];
				ci=i;
			}
		}
	}
	return  start;
}
int reinforcement(int a)
{
	int nooft=0;
	for(int i=0;i<NCountry;i++)
		if(all[i].ownership==a)
			nooft++;
	int noofs=0;
	for(int i=0;i<NCountry;i++)
		if(all[i].ownership==a)
			noofs+=all[i].nos;	
	int reinf=nooft+noofs/10;
	int sp[6]={1,1,1,1,1,1};
	int end[7]={0,10,14,20,27,39,43};
	for(int k=0;k<6;k++)
		for(int i=end[k];i<end[k+1];i++)
			if(all[i].ownership!=a)
				sp[k]=0;
	for(int i=0;i<6;i++)
		reinf+=sp[i]*(end[i+1]-end[i]);
	if(a==1 && reinf>uplayer()*10)
	return(uplayer()*10);
	else if(a==0 && reinf>(NCountry-uplayer())*10)
	return((NCountry-uplayer())*10);
	return(reinf);
}
void visualizeReinf(int country1,int reinfno,bool count[],int &reinf)
{
	CircleShape C2(W1,centers[country1],Red,diameters[country1]);
	C2.Draw();
	W1.RenderText(centers[country1],itoa(all[country1].nos),Black,Red);
	W1.RenderText(Position(0,19.8),"",Black,Yellow);
	usleep(500000);
	all[country1].nos+=reinfno;
	CircleShape C3(W1,centers[country1],Red,diameters[country1]);
	C3.Draw();
	W1.RenderText(centers[country1],itoa(all[country1].nos),Black,Red);
	W1.RenderText(Position(0,19.8),"",Black,Yellow);
	usleep(500000);
	refresh2();
	count[country1]=false;
	reinf-=reinfno;
	PrintRein(reinforcement(1),reinf);
}
int maxcountry(bool count[])
{
//returns country owned by computer whose sum of soldiers in its opponent neighbours is maximum
	int sum,sum1=0,retval=-1;
	for(int i=0;i<NCountry;i++)
	{
		if(all[i].ownership!=0 || count[i]==false)
			continue;
		sum=0;
		for(int k=0;k<all[i].non;k++)
		{
			if(all[all[i].neigh[k]].ownership==1)
				sum+=all[all[i].neigh[k]].nos;
		}
		if(sum>sum1)
		{
			retval=i;
			sum1=sum;
		}
	}
	return(retval);
}

int getNearestNeedy(int i,bool count[])
{
	int dist=NCountry,cc=0;
	for(int j=0;j<NCountry;j++)
	{
		if(all[j].ownership==1 || count[j]==false)
		continue;
		if(fabs(i-j)<dist)
		{
			cc=j;
			dist = int(fabs(i-j));
			continue;
		}
		if(fabs(i-j)==dist && all[j].nos<all[cc].nos)
		{
			cc=j;
		}
	}
	return cc;
}
void aireinforce(int reinf)
{
	PrintLeft("   Reinforcement is going on...   ");
	bool count[NCountry];
	for(int i=0;i<NCountry;i++)
		count[i]=true;
	while(reinf>10)
	{
		int country1=maxcountry(count);
		if(country1!=-1)
		visualizeReinf(country1,10,count,reinf);
		else
		break;
		
	}
	for(int i=0;i<NCountry && reinf!=0;i++)
	{
		if(all[i].ownership==0)
		continue;
		while(reinf>=10)
		{
		int j=getNearestNeedy(i,count);
		visualizeReinf(j,reinf%10+1,count,reinf);
		PrintRein(reinforcement(1),reinf);
		}
		int j=getNearestNeedy(i,count);
		visualizeReinf(j,reinf,count,reinf);
		PrintRein(reinforcement(1),reinf);
	}
	if(reinf!=0)
	{
		int country2=rand()%(NCountry-uplayer()),j=0;
		for(int i=0;i<NCountry;i++)
		{
			if(all[i].ownership==0)
			{
				j++;
				if(j==country2)
				{
				visualizeReinf(i,reinf,count,reinf);
				break;
				}
			}
		}
	}
	return;
}
int mouseClickFocus2(const Position& p)
{
	if(reinf>0)
	{
		bool ans=false;
		int reinfcountry;
		for(int i=0;i<NCountry && ans==false;i++)
		{
			ans=isinside(p,i);
			if(ans) { reinfcountry=i;};
		}
		if(ans==false)
		{
			PrintLeft(" You haven't selected any coutry. ");
			return 0;
		}
		else if(all[reinfcountry].ownership!=turn)
		{
			PrintLeft(all[reinfcountry].name+": This is not your country. ");
			return 0;
		}
		else if(all[reinfcountry].nos>=oldsold[reinfcountry]+10)
		{
			PrintLeft("You cannot increase more than 10 soldiers in a country. ");
		showmsg.msg=" Reinforcement Rule --You cannot ^increment more than 10 soldiers in a country.^Already added 10 soldiers to "+all[reinfcountry].name;
		showmsg.show();
			return 0;
		}
		else
		{
			if(reinf>5)
			{
		               	highlight(reinfcountry);
				all[reinfcountry].nos+=5;
				reinf-=5;
				usleep(300000);
		                W1.RenderText(centers[reinfcountry],itoa(all[reinfcountry].nos),Yellow,Red);
				flush();
				usleep(300000);
				refresh2();
				W1.RenderText(Position(22,19.8),spaces(101),Yellow,Red);
				//W1.RenderText(Position(21,19.8),"  No of reinforcement : User : "+itoa(reinf)+"   Computer : "+itoa(reinforcement(0)),Yellow,Red);
				if(turn==1)
				PrintRein(reinf,reinforcement(0));
				else
				PrintRein(reinforcement(1),reinf);
				PrintLeft(" 5 soldiers added to "+all[reinfcountry].name);
				return 0;
			}
			else
			{
		                highlight(reinfcountry);
				all[reinfcountry].nos+=1;
				reinf--;
				usleep(300000);
		                W1.RenderText(centers[reinfcountry],itoa(all[reinfcountry].nos),Yellow,Red);
				flush();
				usleep(300000);
				refresh2();
				W1.RenderText(Position(22,19.8),spaces(124),Yellow,Red);
				if(turn==1)
				PrintRein(reinf,reinforcement(0));
				else
				PrintRein(reinforcement(1),reinf);
				PrintLeft(" 1 soldier added to "+all[reinfcountry].name);
				if(reinf==0 && uplayer()!=1)
				{
					showmsg.msg="Choose two countries one after^ the other to tranfer your troops^ from first country to the second.^(you are allowed only one transfer)";
					ent="";
					transcount=0;
					showmsg.show();	
					PrintLeft("choose countries for transfer of soldiers");
					W1.SetMouseClickCallback(trans);
					return 0;
				}
				if(reinf==0 && uplayer()==1)
				{
					transover();
				}
				int a=0,b=0;
				if(getMaxNCountry(a,b,(turn+1)%2)==false)
				{
					transover();
				}
				return 0;
			}
		}
	}
}

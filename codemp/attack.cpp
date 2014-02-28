#include"inclusionparts.h"
void attack(int a,int b)
{
	//takes two countries and creates war simulation for them
	flush();
	war(a,b);//calls war
	usleep(300000);
	return;
}

void createTriangle(color c,int c1,int c2)
{
/*
   void createTriangle(color c,int c1,int c2)
   Function:  creates a triangle of given color pointing towards centre of defending country 
              with two sides along tangents from that centre to attacker country's circle
   Inputs:
      Arguments: color c,int c1(attacker id no),int c2(defender id no)
      Global Variables: centers[] and diameters[] double arrays
  
   Outputs:
      Return Value: void
      Reference Arguments: --
      Globals: no change

   Assumptions/Preconditions: arguments should be valid countries idno (0<=idno<NCountry)

   Errors:
*/ 
	Position points[3];
	points[0]=centers[c2];
      	double x1=centers[c1].GetXDistance();
      	double y1=centers[c1].GetYDistance();
       	double x2=centers[c2].GetXDistance();
       	double y2=centers[c2].GetYDistance();
      	double d= sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
       	double xf=(diameters[c1]/2)*(y2-y1)/d;
       	double yf=(diameters[c1]/2)*(x2-x1)/d;
       	points[1]=centers[c1]+Position(xf,-1*yf);
       	points[2]=centers[c1]+Position(-1*xf,yf);
	W1.RenderPolygon(points, 3, c, false);
}
void reduceSoldiers(int c1,int c2)
{
//for making game hard in computer AI() i.e not multiplayer
	if(level!=2 || multiplayer)
	return;
	//reduce 3/10 th of soldiers in country with lesser number of soldiers from both sides 
	//if both have more that 10 soldiers
	if(all[c1].nos >=10 && all[c2].nos>=10)
	{
		int a1 = all[c1].nos;
		int a2 = all[c2].nos;
		int subs=0;
		if(a1>a2)
		subs=3*a2/10;
		else
		subs=3*a1/10;
		for(int h=0;h<subs;h++)
		{
			all[c1].nos-=1;
			refresh2();
			flush();
			usleep(10000);
			all[c2].nos-=1;
			refresh2();
			flush();
			usleep(10000);
		}	
	}
	//reduce 1 soldier while attack of / on player 1 from Player1's country when player1 has more than 10 soldiers
	if(turn==0 && all[c2].nos>=10)
	{
		for(int j=0;j<1;j++)
		{
			all[c2].nos-=1;
			refresh2();
			flush();
			usleep(10000);
		}	
	} 
	if(turn==1 && all[c1].nos>=10)
	{
		for(int j=0;j<1;j++)
		{
			all[c1].nos-=1;
			refresh2();
			flush();
			usleep(10000);
		}	
	}
	return; 
}
void war(int c1,int c2)
{
/*
   void war(int c1,int c2)
   Function:  creates a simulation of war by reducing 1 soldier one by one using predefined probability
   Inputs:
      Arguments: int c1(attacker id no),int c2(defender id no)
      Global Variables: centers[] and diameters[] double arrays, country array all[],
      			bool working (set to false when user clicks are disabled)
      			bool won / lost for winning or losing conditions
      
  
   Outputs:
      Return Value: void
      Reference Arguments: --
      Globals: change in country class array all[] in ownership and/or no. of soldiers i.e all[i].nos
      	       updates scenario in Window W1 as per the war result

   Assumptions/Preconditions: arguments should be valid countries idno (0<=idno<NCountry)

   Errors:
*/ 
	refresh();
	refresh2();
	flush();
	mode=false;
	color cattacker=White,cdefender=Yellow;
	
	string strattacker="Player 1";
	string strdefender="Computer";
	if(multiplayer)
	strdefender="Player 2";
	if(all[c1].ownership==0)
	{
		strattacker =strdefender;
		strdefender="Player 1";
		cdefender=White;
		cattacker=Yellow;
	}
	if(turn==1)
     	createTriangle(Blue,c1,c2);
     	else
     	createTriangle(Blue,c1,c2);
     	reduceSoldiers(c1,c2);
	CircleShape C2(W1,centers[c1],cattacker,diameters[c1]);
	C2.Draw();
	W1.RenderText(centers[c1],itoa(all[c1].nos),Black,cattacker);
	
	W1.RenderText(Position(0,19.8),"",Yellow,Red);
	usleep(300000);

	int a=all[c1].nos,b=all[c2].nos;
	
	while((a!=1)&&(b!=0))
	{
		int c;
		int compare;
		if(level==2 && !(multiplayer))
		{
			c=rand()%(a+b+2);
			compare=b+2;
		}
		else if(level==1 && !(multiplayer))
		{
			c=rand()%(a+b+1);
			compare=b+1;
		}
		else
		{
			c=rand()%(a+b);
			compare=b;
		}
		//decision of probability of winning of attacker on the basis of level and multiplayer (boolean value)
		//in easy level v/s computer probability of killing one soldier of opponent with my a soldiers 
		//and his b soldiers is a/a+b etc...
		if(c<compare)
		{
			a=a-1;
		}
		else
		{
			b=b-1;
		}
		//decrementing soldiers one by one
		all[c1].nos=a;
		all[c2].nos=b;
		refresh2();
		flush();
		usleep(10000);
		refresh2();
	}
	if(a==1)
	{
		all[c1].nos=a;all[c2].nos=b;
		PrintLeft("Invasion failed. "+all[c2].name+" is retained by "+strdefender);
		showmsg.msg=all[c2].name+" resists invasion from "+all[c1].name+".^ Territory retained by "+strdefender;
		showmsg.show();
                CircleShape C(W1,centers[c2],cdefender,diameters[c2]);
                C.Draw();
	}
	else if(b==0)
	{
		all[c2].ownership=all[c1].ownership;
		if(redistr==0)
		{
			all[c1].nos=1;
			all[c2].nos=a-1;
		}
		else
		{
			all[c1].nos=a/2;
			all[c2].nos=a-a/2;
		}
                CircleShape C(W1,centers[c2],cattacker,diameters[c2]);
                C.Draw();
          	if (uplayer()==NCountry)
          	{
          		showmsg.msg="   PLAYER 1   WINS  !!!";
          		turn=0;
          		mode=true;
          		::count=1;
          		working=false;
          		refresh();
          		won=true;
			showmsg.show();
			return;
          	}
          	if (uplayer()==0)
          	{
          		turn=0;
          		showmsg.msg="   "+strComp +" WINS  !!!";
          		mode=true;
          		lost=true;
          		::count=1;
          		working=false;
          		refresh();
          		showmsg.show();
			return;
          	}       
          	//analysing outcome and updating the screen. Also checking whether somebody has won or not....
		PrintLeft("Invasion successful. "+all[c2].name+" has been captured by "+ strattacker);
		showmsg.msg=all[c1].name+" successfully invades "+all[c2].name+".^ Territory captured by "+ strattacker;
		showmsg.show();
	}
        CircleShape C(W1,centers[c1],cattacker,diameters[c1]);
        C.Draw();
        W1.RenderText(centers[c1],itoa(all[c1].nos),Black,cattacker);
	if(b==0)
        	W1.RenderText(centers[c2],itoa(all[c2].nos),Black,cattacker);
	else
                W1.RenderText(centers[c2],itoa(all[c2].nos),Black,cdefender);
		PrintRein();
		::count=1;
		mode=true;
	if(multiplayer)
		working=false;
	refresh();
	refreshLines(c1,c2);
	refresh2();
		//cout<<turn<<"\t"<<all[c1].name<<"\t"<<all[c2].name<<"\t"<<uplayer()<<endl;
}
int mouseClickFocus1NotButton(const Position& p)
{
/*
   int mouseClickFocus1NotButton(const Position& p)
   Function:    identifies country choosen by user for either attack on other or for reinforcement
   		and performs furthur actions
   Inputs:
      Arguments: const Position& p(of click)
      Global Variables: int c;(representing country number of country being selected (it is 100 if clicked outside)
      			int c1,c2; representing first and second countries being selected by user
      			int ::count; for maintaining flow of clicks i.e choosing what to do for this click depending on its value
  			uses centers[] and diameters[] double arrays for creating/updating circles and their colors
  			country all[] array for updation and extraction of data about countries
   Outputs:
      Return Value: int
      Reference Arguments: const Position& p(not changed)
      Globals:  --

   Assumptions/Preconditions: only W1 is opened at the time of click

   Errors:
*/ 
        int c=100,valid=1;
       
	c=getcountry(p);
	if(c==100 && ::count==2)
	{
                CircleShape C(W1,centers[c1],getColor(c1),diameters[c1]);
                C.Draw();
                W1.RenderText(centers[c1],itoa(all[c1].nos),Black,getColor(c1));
	PrintLeft("    Country deselected. Select any other country ");
		::count=1;
		return 1;
	}
        else if(c==100 && ::count==1)
        {
	PrintLeft("   You haven't selected any country   ");
        return 1;
        }
		for(int i=0;i<all[c].non;i++)
		{
				if(all[all[c].neigh[i]].ownership!=all[c].ownership)
				{		
						valid=0;
						break;
				}
		}
        if(::count==1)
        {        
		if(all[c].ownership!=turn)
		{
			PrintLeft(all[c].name+": The country is not owned by you.    ");
			return 2;
		};		
		if(valid==1)
		{
			PrintLeft(all[c].name+": There is no neighbouring country of opponent ");
        		return 1;
        	}		
		if(all[c].nos==1)
		{
			PrintLeft(all[c].name+": One soldier cannot attack   ");
	        	return 1;
        	}		
	
		c1=c;
                ::count+=1;
		PrintLeft("       Selected country : " +all[c1].name);
                highlight(c1);
        }
        else if(::count==2)
        {
		if(all[c].ownership==turn)
		{
			PrintLeft(all[c].name+": It is not opponent's country ");
		return 2;
		};
		bool neighbours=false;//checks whether the countries are neighbours or not ( a country is not itself's neighbour)
		for(int i=0;i<all[c1].non;i++)
		{
			if(c==all[c1].neigh[i])
			{
				c2=c;
	                	::count=3;
           	    		neighbours=true;
				attack(c1,c2); // attack if clicks are on proper countries that may have a war

				break;
			};
		}
		if(neighbours==false)
		{
			PrintLeft(all[c].name+": This is not neighbouring country");
			return 2;
		};
			
        }
        return 1;
}

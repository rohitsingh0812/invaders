#include"inclusionparts.h"
void randomdist(int b[NCountry],int c[NCountry])
{ 
/*
   void randomdist(int b[NCountry],int c[NCountry])
   Function:  randomly distributes total countries to pl.1 and comp./pl.2 and then distributes
   	      required number of soldiers in each one of them 
   Inputs:
      Arguments: int b[NCountry],int c[NCountry]
      Global Variables: int Neasy,Nmedium,Nhard -- no. of player soldiers for each level 
      			int NCountry -- total no. of countries
      			country all[]
  
   Outputs:
      Return Value: void(no value)
      Reference Arguments: int b[NCountry],int c[NCountry](both updated)
      Globals: no change

   Assumptions/Preconditions: --

   Errors:
*/   
	
       	int Nsolplay=Neasy,NsolComp=Neasy+10;
       	if(multiplayer)
       	{
       		if(level==0)
       		{
       			Nsolplay=Neasy;
       			NsolComp=Neasy+15;
       		}
       		if(level==1)
       		{
       			Nsolplay=Nmedium;
       			NsolComp=Nmedium+15;
       		}
       		if(level==2)
       		{
       			Nsolplay=Nhard;
       			NsolComp=Nhard+15;
       		}
       	}
       	else
       	{
       		if(level==0)
       			Nsolplay=Neasy;
       		if(level==1)
       			Nsolplay=Nmedium;
       		if(level==2)
       			Nsolplay=Nhard;
       	}
       	int nplay=0;
	int playsol=66;
	int compsol=63;
	//first give 3 soldiers to each country
        int a[NCountry][2];
        for(int i=0;i<NCountry;i++)
        {        a[i][0]=i;
                a[i][1]=0;   
                c[i]=3;     
        }
        //int b[i]=0 for comp/Player.2 n 1 for Player.1 occupying territory no. i;
        // a[i][1]=0 if territory a[i][0] is occupied by computer/Player.2 and 1 for Player.1
        
        for(int i=NCountry;i>=1;i--)
        {        //a[i]=0;
                int b=rand()%i;
                a[b][1]=1;
                //now swap a[b][] with last array a[i-1][]
                int temp=a[i-1][0];
                a[i-1][0]=a[b][0];
                a[b][0]=temp;
                temp=a[i-1][1];
                a[i-1][1]=a[b][1];
                a[b][1]=temp;
                nplay++;
                if(nplay==NCountry/2)
                break;
        }
        
        for(int i=0;i<NCountry;i++)
	{
	 b[a[i][0]]=a[i][1];//assigning randomly selected 21=int(43/2) countries to player 1 and rest to scomputer/Pl.2
	}
	bool cp=true,cc=true;
        while (1)
        {
                int i=rand()%NCountry;
                 	 if(b[i]==0 && cc==true)
        		 {
        		 c[i]+=1;
        		 compsol+=1;
        		 }
        		 else if(b[i]==1 && cp==true)
        		 {
        		 c[i]+=1;
        		 playsol+=1;
        		 }
        		 if(compsol>=NsolComp)
        		 cc=false;
        		 if(playsol>=Nsolplay)
        		 cp=false;
        		 if(cp==false && cc==false)
        		 break;
        }
        
        
}

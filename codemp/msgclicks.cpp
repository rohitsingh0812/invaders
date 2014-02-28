#include"inclusionparts.h"
int mouseClickFocus32(const Position& p)
{
//for response to special clicks in OKCancelMessage Box (for main menu)
	if(W3Bmp.IsInside(p)==true)
	{
		//clicked OK Button
		W3Bmp.Load("../images/ok1p.xpm");
        	W3Bmp.SetPosition(Position(2.5, 3.9));
        	W3Bmp.Draw();
        	W3.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(100000);
        	focus=4;
        	startup();
        	//Go Back To StartUp Window
        	W3.Close();
        	W1.Close();
       		return 0;
	}
	if(W3Bmp2.IsInside(p)==true)
	{
		//clicked Cancel Button
		W3Bmp2.Load("../images/Cancelp.xpm");
        	W3Bmp2.SetPosition(Position(6.5, 3.9));
        	W3Bmp2.Draw();
        	W3.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(100000);
        	focus=prevfocus;
        	//Go back to previous focus(Global prevfocus stores focus of calling procedure/function
        	prevfocus=1;
       		W3.Close();
       		return 0;
	}
}
int mouseClickFocus3(const Position& p)
{
//for response to clicks in OK Message Box
	if(MM.IsInside(p))
	{
		W3.Close();
		//clicked Main Menu Button in W1
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
	if(W3Bmp.IsInside(p)==true)
	{
		//clicked OK Button
		W3Bmp.Load("../images/okp.xpm");
		assert(W3Bmp.GetStatus() == BitMapOkay);
        	W3Bmp.SetPosition(Position(5.0, 3.9));
        	W3Bmp.Draw();//simulation for button pressing
        	W3.RenderText(Position(0,0),"",Yellow,Red);
        	usleep(100000);	
		if(mid==true)
		{
			//case when transfer orders have been set using first and second click position variables 
			W3.Close();
			transfer(getcountry(first),getcountry(second),en);
			refresh2();
			mid=false;
			en=0;
			ent="";
			if(transcount%2==0) // end transfer phase after one successful transfer using global transcount
			{
				W1.SetMouseClickCallback(f);
				transcount=0;
				transover(); // end transfers
			}		
			return 0;
		}
		if(strphase=="Reinforcement Phase")
		{
			W3.Close();
			focus=2;
			return 0;
		};		
		if(showmsg.msg=="Thank You for Playing Invaders...")
		{
			ApiEnd();
			return 0;
		}
		if(won || lost)
		{
		//restarting the game when somebody wins or loses
			startup();
			won = false;
			lost = false;
			W3Bmp.Erase();
			W3.Close();
			focus=4;
			W1.Close();
			return 0;
		};
		W3Bmp.Erase();
		W3.Close();
		focus=1;
		if(turn==0)
		{
			if(!(multiplayer))
				AI(); 	// computer plays only when multiplayer is false 
					//(choosen by user in Settings Window)
		}
		return 0;
	}
	else
	return 0;
}

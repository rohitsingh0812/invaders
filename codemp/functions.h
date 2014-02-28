#ifndef FUNCTIONS_H
#define FUNCTIONS_H
int quitW3();
int wsgQuit();
void refresh();
void refresh2();
void refreshLines();
void refreshLines(int i,int k);
int keypress(int keycode);
int none();
string spaces(int n);
int reinforcement(int a);
int uplayer();
string itoa(int i);
void flush(void);
void PrintPhase();
void highlight(int i);
color getColor(int i);
void ShowEndTurn();
void ShowSaveGame();
void ShowMainMenu();
void PrintLeft(string str);
void PrintRein();
void PrintRein(int r1,int r2);
void showsave();
void transfer(int i, int j, int transsol);
void transover();
int key(int keycode);
int trans(const Position& p);
void createTriangle(color c,int c1,int c2);
void reduceSoldiers(int c1,int c2);
void war(int c1,int c2);
int maxcountry(bool count[]);
void visualizeReinf(int country1,int reinfno,bool count[],int &reinf);
int getNearestNeedy(int i,bool count[]);
void aireinforce(int reinf);
void attack(int a,int b);
int getNOppNeighbours(int i);
bool getMaxNCountry(int &co,int &ci,int play);
bool willBeBlocked(int i,int j);
void multipleAttackAI(int c);
void AI(void);
void randomdist(int b[NCountry],int c[NCountry]);
int getcountry(const Position &p);
bool isinside(Position p,int l);
void loadgame(string filename);
void savegame(string filename);
int mouseClickFocus5(const Position& p);
int mouseClickFocus32(const Position& p);
int mouseClickFocus3(const Position& p);
int mouseClickFocus2(const Position& p);
int mouseClickFocus4(const Position& p);
int mouseClickFocus1NotButton(const Position& p);
int f(const Position& p);
void getclick(void);
void createrectangle(double a[4],color cl1,color cl2);
void fillup(double pt[4][4]);
void startup();
int defaultKey(int keycode) ;
color randomColor();
double calculateY(int i);
int spltimer();
void invadersShowUp();
void loadingWindow();
void gameproceed();
int ApiEnd();
void message :: split(vector<string> &z)
{
	string s=msg;
        int i=-1,j=s.find("^");
        while (j<s.length())
        {
        	z.push_back(s.substr(i+1,j-i-1));
        	i=j;
    		j=s.find("^",i+1);		
        }
        z.push_back(s.substr(i+1,s.length()));
        for(i=0;i<z.size();i++)
        {
     		W3.RenderText(Position(6,1.0 +((double)i)/1.7),z[i],Yellow,Red);
	}
	W3.SetMouseClickCallback(f);
	W3.RenderText(Position(0,0),"",Yellow,Red);	
	z.clear();
}
void message :: show()
{
	if(mode==false)
	return;
	vector <string> z;
	W3.Open();
	assert(W3.GetStatus() == WindowOpen);
	W3Bmp2.Load("../images/back.xpm");
	assert(W3Bmp2.GetStatus() == BitMapOkay);
        W3Bmp2.SetPosition(Position(0, 0));
        W3Bmp2.Draw();
	W3Bmp.Load("../images/okup.xpm");
	assert(W3Bmp.GetStatus() == BitMapOkay);
        W3Bmp.SetPosition(Position(5.0, 3.9));
        W3Bmp.Draw();
        split(z);
        focus=3;
        W3.SetKeyPressCallback(defaultKey);
       	W3.SetQuitCallback(quitW3);      		
};
void message :: ShowOkCancel()
{
	vector <string> z;
	W3.Open();
	assert(W3.GetStatus() == WindowOpen);
	W3Bmp2.Load("../images/back.xpm");
	assert(W3Bmp2.GetStatus() == BitMapOkay);
        W3Bmp2.SetPosition(Position(0, 0));
        W3Bmp2.Draw();
	W3Bmp.Load("../images/ok1up.xpm");
	assert(W3Bmp.GetStatus() == BitMapOkay);
        W3Bmp.SetPosition(Position(2.5, 3.9));
        W3Bmp.Draw();
        W3Bmp2.Load("../images/Cancelup.xpm");
	assert(W3Bmp.GetStatus() == BitMapOkay);
        W3Bmp2.SetPosition(Position(6.5, 3.9));
        W3Bmp2.Draw();
        W3.SetQuitCallback(quitW3);
        split(z);
	focus=32;
	W3.SetKeyPressCallback(defaultKey);
}
void message :: showenter()
{
	show();
	W3.SetQuitCallback(none);
	W3.RenderText(Position(6.0,3.0),spaces(80),Yellow,Red);
	W3.RenderLine(Position(0,2.7),Position(12,2.7),Black,0.05);
	W3.RenderLine(Position(0,3.5),Position(12,3.5),Black,0.05);
	return;
}
#endif

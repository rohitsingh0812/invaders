#ifndef FUNCTIONSEXT_H
#define FUNCTIONSEXT_H
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
#endif
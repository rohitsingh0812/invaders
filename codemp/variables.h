#ifndef VARIABLES_H
#define VARIABLES_H
int redistr=0;
int transcount=0;
int level=0; //level=0 for easy 1 for medium and 2 for hard
bool multiplayer=false; // play with computer or with another human player
int map=0;
double const PI=3.1415926535897932;
const double NDIV=75;
string strComp="Computer";
const int NDOTS=226;
Position showUpCentres[NDOTS];
int counter=0;
ifstream fcentres("../data/initialcentres.txt");
Position first,second;
int Neasy=200,Nmedium=175,Nhard=150;
bool mid=false; 
bool won=false;
bool lost=false;
string ent="";
int en=0;
bool mode=true;
bool aimode=false;
int prevfocus=1;
string ls ="load";
int loaded=0;
int focus=4;//stores which window should be active i.e responsive to mouse clicks
string strphase;
int oldsold[NCountry];
int reinf;
bool working=false;
int count=1,c1=-1,c2=-1,turn=1;
SimpleWindow W1("Invaders...", 40.0,40.0, Position(1.0, 1.0));
SimpleWindow W3("Message Box", 12,6, Position(10, 10));
SimpleWindow W4("Invaders...Startup", 23.8,18.5, Position(1.0, 1.0));
SimpleWindow Wsg("Invaders...", 17.8,13.9, Position(1.0, 1.0));
BitMap loadBmp(W4);
BitMap stylishINV(W4);
BitMap W1Bmp(W1);
BitMap W3Bmp(W3);
BitMap W3Bmp2(W3);
BitMap W4Bmp(W4);
BitMap W1Bmp2(W1);
BitMap W1Bmp3(W1);
BitMap W1Bmp4(W1);
BitMap W1Bmp5(W1);
BitMap back(Wsg);
BitMap lg(Wsg);
BitMap sg(Wsg);
BitMap game1(Wsg);
BitMap game2(Wsg);
BitMap game3(Wsg);
BitMap game4(Wsg);
BitMap game5(Wsg);
BitMap SG(W1);
BitMap ET(W1);
BitMap MM(W1);
Position centers[NCountry];
float diameters[NCountry];
#endif

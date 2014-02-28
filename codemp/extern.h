#ifndef EXTERN_H
#define EXTERN_H
extern int redistr;
extern int transcount;
extern int level; //level=0 for easy 1 for medium and 2 for hard
extern bool multiplayer; // play with computer or with another human player
extern int map;
extern string strComp;
extern Position showUpCentres[NDOTS];
extern int counter;
extern ifstream fcentres;
extern Position first,second;
extern int Neasy,Nmedium,Nhard;
extern bool mid; 
extern bool won;
extern bool lost;
extern string ent;
extern int en;
extern bool mode;
extern bool aimode;
extern int prevfocus;
extern string ls ;
extern int loaded;
extern int focus;//stores which window should be active i.e responsive to mouse clicks
extern string strphase;
extern int oldsold[NCountry];
extern int reinf;
extern bool working;
extern int count,c1,c2,turn;
extern SimpleWindow W1;
extern SimpleWindow W3;
extern SimpleWindow W4;
extern SimpleWindow Wsg;
extern BitMap loadBmp;
extern BitMap stylishINV;
extern BitMap W1Bmp;
extern BitMap W3Bmp;
extern BitMap W3Bmp2;
extern BitMap W4Bmp;
extern BitMap W1Bmp2;
extern BitMap W1Bmp3;
extern BitMap W1Bmp4;
extern BitMap W1Bmp5;
extern BitMap back;
extern BitMap lg;
extern BitMap sg;
extern BitMap game1;
extern BitMap game2;
extern BitMap game3;
extern BitMap game4;
extern BitMap game5;
extern BitMap SG;
extern BitMap ET;
extern BitMap MM;
extern Position centers[NCountry];
extern float diameters[NCountry];
#endif

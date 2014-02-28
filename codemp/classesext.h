#ifndef CLASSESEXT_H
#define CLASSESEXT_H
class message
{
	public :
		string msg;
		message()
		{
			msg="";
		};
		message(string msgstr)
		{
			msg=msgstr;
		};
		void split(vector<string> &z);
		void show();
		void ShowOkCancel();
		void showenter();
};
class country
{
public:
	int idno;
	int neigh[6];
	int non;
	int nos;
	int ownership;
	string name;
};
extern country all[NCountry];
extern message showmsg;
#endif

// shift.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct AShifter
{
	string name;
	bool night;
	bool holiday;
	unsigned int shift;
};
struct AShiftDay
{
	string date;
	bool holiday;
	string day_sh;
	string night_sh;
};

int Findperson(std::vector<AShifter> sh_col,bool holiday,bool night)
{
	int pos=0;
	unsigned tmp;
	std::vector<AShifter>::iterator com;
	com = sh_col.begin();
	int loop = sh_col.size();
	tmp = AShifter(*com).shift;
	for (int i = 0; i < loop; i++)
	{
		if (tmp > AShifter(*com).shift)
		{
			if (!((!AShifter(*com).holiday) && holiday))
			{
				if (!((!AShifter(*com).night) && night))
				{
					pos = i;
					tmp = AShifter(*com).shift;
				}
			}
		}
		com++;
	}
	return pos;
}

int main()
{
	ifstream namefile("name.txt");
	ifstream datefile("date.txt");
	if (namefile.is_open() && datefile.is_open())
	{

		std::vector<AShifter> sh_col;
		string flag;
		namefile >> flag;
		cout << flag << "\t";
		namefile >> flag;
		cout << flag << "\t";
		namefile >> flag;
		cout << flag << "\n";
		while (namefile.good())
		{
			AShifter tmp;
			namefile >> tmp.name;
			namefile >> flag;
			if (flag == "是")tmp.night = true;
			else tmp.night = false;
			namefile >> flag;
			if (flag == "是")tmp.holiday = true;
			else tmp.holiday = false;
			tmp.shift = 0;
			cout << tmp.name << "\t" << tmp.night << "\t" << tmp.holiday << endl;
			sh_col.push_back(tmp);
		}
		cout << "共有" << sh_col.size() << "人参与值班！\n";
		datefile >> flag;
		cout << flag << "\n";
		datefile >> flag;
		ofstream outfile("results.txt");
		while (datefile.good())
		{
			int pos;
			AShiftDay tmp;
			datefile >> tmp.date;
			datefile >> flag;
			if (flag == "节假日")tmp.holiday = true;
			else tmp.holiday = false;
			pos=Findperson(sh_col, tmp.holiday,false);
			tmp.day_sh = sh_col.at(pos).name;
			sh_col.at(pos).shift+=2;
			pos = Findperson(sh_col,tmp.holiday, true);
			tmp.night_sh = sh_col.at(pos).name;
			sh_col.at(pos).shift+=3;
			cout << tmp.date << "\t" << tmp.day_sh << "\t" << tmp.night_sh << endl;
			outfile << tmp.day_sh << "\t" << tmp.night_sh << endl;
		}
		outfile.close();
		std::vector<AShifter>::iterator com;
		com = sh_col.begin();
		int loop = sh_col.size();
		for (int i = 0; i < loop; i++)
		{
			cout<< AShifter(*com).name << "\t" << AShifter(*com).shift << endl;
			com++;
		}
	}
	else cout << "Error in reading FILE!"<<endl;


    return 0;
}


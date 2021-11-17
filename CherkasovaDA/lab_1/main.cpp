
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct slovar
{
	int sum=0;
	string slova=" ";
	int raspologenie = 0;
};

bool sootvetstvieOR(char simv)
{
	if (simv == '.' || simv == '!' || simv == ',' || simv == '?')
	{
		return true;
		
	}
	else
	{
		return false;
	}
	
}

bool sootvetstvieAND(char simv)
{
	if (simv != '.' && simv != '!' && simv != ',' &&simv != '?')
	{
		return true;

	}
	else
	{
		return false;
	}

}

int main()
{
	setlocale(0, "");
	cout << "Введите строчку" << endl;
	string stroka;
	getline(cin, stroka);
	string slovo = " ";
	slovo += stroka[0];
	int summa = 0;
	int raspr = 0;
	if (sootvetstvieAND(stroka[0]))
	{
		summa = int(stroka[0]);
	}
	vector <slovar> spisok;
	for (int i = 1;i < size(stroka);i++)
	{
		if (stroka[i] != ' ' && sootvetstvieAND(stroka[i]) && sootvetstvieAND(slovo[size(slovo)-1]))
		{
			slovo += stroka[i];
			summa += int(stroka[i]);
		}
		else if ((sootvetstvieOR(stroka[i]))&&(size(slovo)==1))
		{
			slovo+=stroka[i];
			summa=0;
		}
		else if ((sootvetstvieOR(stroka[i])) && (size(slovo) > 1) && (sootvetstvieOR(slovo[1])))
		{
			slovo += stroka[i];
			summa = 0;
		}
		else if ((sootvetstvieOR(stroka[i])) && (size(slovo) > 1) && (sootvetstvieAND(slovo[ 1])))
		{
			slovar flag;
			flag.sum = summa;
			flag.slova = slovo.substr(1);
			flag.raspologenie = 0;
			spisok.push_back(flag);
			slovo = " ";
			slovo += stroka[i];
			summa = 0;
			raspr = -1;
		}
		else if(stroka[i] == ' ' && size(slovo)==2 && sootvetstvieOR(slovo[1]))
		{
			slovar flag;
			flag.sum = summa;
			flag.slova = slovo.substr(1);
			flag.raspologenie = raspr;
			spisok.push_back(flag);
			slovo = stroka[i];
			summa = 0;
			raspr = 0;
		}
		else if (stroka[i] != ' ' && sootvetstvieAND(stroka[i])&&size(slovo)==2&&sootvetstvieOR(slovo[1]))
		{
			slovar flag;
			flag.sum = summa ;
			flag.slova = slovo.substr(1);
			flag.raspologenie = 1;
			spisok.push_back(flag);
			slovo = " ";
			slovo+=stroka[i];
			summa =int(stroka[i]);
		}
		else if (stroka[i]==' ')
		{
			
			slovar flag;
			flag.sum = summa;
			flag.slova = slovo.substr(1);
			flag.raspologenie = 0;
			spisok.push_back(flag);
			slovo = stroka[i];
			summa = 0;
		}
	}
	slovar flag;
	flag.sum = summa;
	flag.slova = slovo.substr(1);
	if (size(slovo.substr(1)) == 1 && sootvetstvieOR(slovo[1]))
	{
		flag.raspologenie = -1;
	}
	else
	{
		flag.raspologenie = 0;
	}
	spisok.push_back(flag);
	vector <int> maxmin;
	for (int i = 0; i < size(spisok);i++)
	{
		if (spisok[i].sum != 0)
		{
			maxmin.push_back(spisok[i].sum);
		}
	}
	sort(maxmin.begin(), maxmin.end());
	vector <int> indexes;
	int schet = -1;
	for (int i = 0; i < size(spisok);i++)
	{
		if (spisok[i].sum == 0 || spisok[i].sum == -10 || spisok[i].sum == -11)
		{
			indexes.push_back(i);
		}
		else
		{
			schet += 1;
			for (int j = 0; j < size(spisok);j++)
			{
				if (spisok[j].sum == maxmin[schet])
				{
					indexes.push_back(j);
					spisok[j].sum = -1;
					break;
				}
			}
		}

	}
	string itog;
	for (int i = 0;i < size(indexes);i++)
	{
		if (spisok[indexes[i]].raspologenie == 0)
		{
			itog += spisok[indexes[i]].slova + " ";
		}
		if (spisok[indexes[i]].raspologenie == -1)
		{
			itog = itog.substr(0, size(itog) -1 )+ spisok[indexes[i]].slova+" ";

		}
		if (spisok[indexes[i]].raspologenie == 1)
		{
			itog += spisok[indexes[i]].slova;
		}

		
	}
	cout << itog.substr(0, size(itog) - 1);
	return 0;
}
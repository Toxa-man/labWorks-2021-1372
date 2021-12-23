#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;
enum _oboznachenie
{
	chislo,pluss,minuss,ymnoz,del,lev_sk,prav_sk,endd,tochka
} ;

struct simvol
{
	char symbol;
	char str_symbol;
};


simvol get_next_simv(string& stroka, int &index)
{
	simvol symb;
	symb.symbol = endd;
	switch (stroka[index])
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		symb.symbol = chislo;
		break;
	case '+':
		symb.symbol = pluss;
		break;
	case '-':
		symb.symbol = minuss;
		break;
	case '*':
		symb.symbol = ymnoz;
		break;
	case '/':
		symb.symbol = del;
		break;
	case '(':
		symb.symbol = lev_sk;
		break;
	case ')':
		symb.symbol = prav_sk;
		break;
	case '.':
		symb.symbol = tochka;
		break;
	}
	if (symb.symbol != endd)
	{
		symb.str_symbol = stroka[index];
		index++;
	}
	return symb;
}

double chislo_or_skobki(simvol simv,string& stroka, int& index);
double proizvedenie(simvol simv, string& stroka, int& index);
double summa(simvol simv, string& stroka, int& index);



double chislo_or_skobki(simvol simv, string& stroka, int& index)
{
	double resultat = 0;

	switch (simv.symbol)
	{
	case chislo:
		resultat = int(simv.str_symbol)- '0';
		while (simv.symbol == chislo)
		{
			simv = get_next_simv(stroka, index);
			switch (simv.symbol)
			{
			case chislo:
				resultat = resultat*10 +(int(simv.str_symbol) - '0');
				break;
			default:
				--index;
				break;
			}
		}
		get_next_simv(stroka, index);
		if (simv.symbol == tochka)
		{
			simv = get_next_simv(stroka, index);
			while (simv.symbol == chislo)
			{
				switch (simv.symbol)
				{
				case chislo:
					resultat = resultat + (int(simv.str_symbol) - '0') / 10.0;
					break;
				}
				simv = get_next_simv(stroka, index);
			}
			--index;
		}
		else
		{
			--index;
		}
		break;
	case minuss:
		simv = get_next_simv(stroka, index);
		resultat = -chislo_or_skobki(simv, stroka, index);
		break;
	case lev_sk:
		simv = get_next_simv(stroka, index);
		resultat = summa(simv, stroka, index);
		break;
	default:
		break;
	}
	return resultat;
}

double proizvedenie(simvol simv, string& stroka, int& index)
{
	double resultat = chislo_or_skobki(simv, stroka, index);
	double delit = 0;
	while (simv.symbol != endd) {
		simv = get_next_simv(stroka, index);
	switch (simv.symbol)
	{
	case ymnoz:
		simv = get_next_simv(stroka, index);
		resultat *= chislo_or_skobki(simv, stroka, index);
		break;
	case del:
		simv = get_next_simv(stroka, index);
		delit = chislo_or_skobki(simv, stroka, index);
		if (delit != 0)
		{
			resultat /= delit;

			break;
		}
		else
		{
			cout << "Вы попытались поделить на ноль. Мы пропустили этот шаг." <<endl;
		}
	default:
		--index;
		return resultat;
		}
	}
	
}

double summa(simvol simv, string& stroka, int& index)
{
	double resultat = proizvedenie(simv,stroka,index);
	while (simv.symbol!=endd) {
		simv = get_next_simv( stroka, index);
		switch (simv.symbol)
		{
		case pluss:
			simv = get_next_simv(stroka, index);
			resultat += proizvedenie(simv, stroka, index);
			break;
		case minuss:
			simv = get_next_simv(stroka, index);
			resultat -= proizvedenie(simv, stroka, index);
			break;
		default:
			return resultat;

		}
	}
	
}

bool proverka_na_chislo(char a)
{
	if (a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' || a == '6' || a == '7' || a == '8' || a == '9')
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
	string in_stroka;
	string stroka_bez_probelov = " ";
	int index = 0;
	int count_postoronnie_simv = 0;
	int count_lishnie_znaki = 0;
	int count_lev_sk = 0;
	int count_prav_sk = 0;
	int count_skobki = 0;
	int count_nachalo_stroki = 0;
	int count_null = 0;
	int count_chisla = 0;
	int count_tochki = 0;
	int count_pystie_skobki = 0;
	setlocale(0,"");
	cout << "Введите выражение\nДробные числа вводите через точку" << endl;
	simvol simv;
	do {
		stroka_bez_probelov = " ";
		count_postoronnie_simv = 0;
		count_lishnie_znaki = 0;
		count_lev_sk = 0;
		count_prav_sk = 0;
		count_skobki = 0;
		count_nachalo_stroki = 0;
		count_null = 0;
		count_chisla = 0;
		count_tochki = 0;
		count_pystie_skobki = 0;
		getline(cin, in_stroka);
		for (int i = 0;i < size(in_stroka);i++)
		{
			if (proverka_na_chislo(in_stroka[i])  ||
				in_stroka[i] == '+' || in_stroka[i] == '-' || in_stroka[i] == '*' || in_stroka[i] == '/' ||
				in_stroka[i] == '(' || in_stroka[i] == ')' || in_stroka[i] == '.')
			{
				stroka_bez_probelov += in_stroka[i];
			}
			else if (int(in_stroka[i]) == 32)
			{
				continue;
			}
			else
			{
				count_postoronnie_simv ++;
			}
		}
		for (int i = 1;i < size(stroka_bez_probelov);i++)
		{
			if ((stroka_bez_probelov[i - 1] == ')') && (proverka_na_chislo(stroka_bez_probelov[i]) ))
			{
				stroka_bez_probelov= stroka_bez_probelov.substr(0,i)+'*'+ stroka_bez_probelov.substr(i);
			}
			if ((stroka_bez_probelov[i] == '(') && (proverka_na_chislo(stroka_bez_probelov[i-1])))
			{
				stroka_bez_probelov = stroka_bez_probelov.substr(0, i) + '*' + stroka_bez_probelov.substr(i);
			}
		}
		
		if (!(proverka_na_chislo(stroka_bez_probelov[1]) || stroka_bez_probelov[1] == '-'  || stroka_bez_probelov[1] == '(' || stroka_bez_probelov[1] == '+'))
		{
			count_nachalo_stroki++;
		}
		if (stroka_bez_probelov[1] == '+')
		{
			stroka_bez_probelov = ' ' + stroka_bez_probelov.substr(2);
		}
		for (int i = 1;i < size(stroka_bez_probelov);i++)
		{
			if ((stroka_bez_probelov[i] == '+' || stroka_bez_probelov[i] == '-' || stroka_bez_probelov[i] == '/' 
				|| stroka_bez_probelov[i] == '*') && (stroka_bez_probelov[i-1] == '+' || stroka_bez_probelov[i-1] == '-'
					|| stroka_bez_probelov[i-1] == '/' || stroka_bez_probelov[i-1] == '*'))
			{
				count_lishnie_znaki++;
			}
			if (stroka_bez_probelov[i] == '(')
			{
				count_lev_sk++;
			}
			if (stroka_bez_probelov[i] == ')')
			{
				count_prav_sk++;
			}
			if (stroka_bez_probelov[i] == ')' && stroka_bez_probelov[i - 1] == '(')
			{
				count_pystie_skobki++;
			}
			
		}
		for (int i = 1;i < size(stroka_bez_probelov);i++)
		{
			if (((stroka_bez_probelov[i] == '+' || stroka_bez_probelov[i] == '/'
				|| stroka_bez_probelov[i] == '*') && (stroka_bez_probelov[i - 1] == '('))|| ((stroka_bez_probelov[i-1] == '+'
					|| stroka_bez_probelov[i-1] == '-' || stroka_bez_probelov[i-1] == '/'
					|| stroka_bez_probelov[i-1] == '*') && (stroka_bez_probelov[i] == ')')))
			{
				count_chisla++;
			}
		}
		if (count_lev_sk != count_prav_sk)
		{
			count_skobki = 1;
		}
		for (int i = 1;i < size(stroka_bez_probelov) - 1;i++)
		{
			if (( stroka_bez_probelov[i - 1] == ' ' || stroka_bez_probelov[i - 1] == '+' || stroka_bez_probelov[i - 1] == '-'
				|| stroka_bez_probelov[i - 1] == '/' || stroka_bez_probelov[i - 1] == '*'
				|| stroka_bez_probelov[i - 1] == '(' || stroka_bez_probelov[i - 1] == ')') && stroka_bez_probelov[i] == '0'&&(proverka_na_chislo(stroka_bez_probelov[i+1])))
			{
				count_null++;
			}
			if (stroka_bez_probelov[i] == '.') {
				if (proverka_na_chislo(stroka_bez_probelov[i - 1]) && stroka_bez_probelov[i] == '.'&& (stroka_bez_probelov[i + 1]=='+'|| stroka_bez_probelov[i + 1] == '-' || 
					stroka_bez_probelov[i + 1] == '*' || stroka_bez_probelov[i + 1] == '/' || stroka_bez_probelov[i + 1] == '(' || stroka_bez_probelov[i + 1] == ')'))
				{
					stroka_bez_probelov = stroka_bez_probelov.substr(0, i+1) + '0' + stroka_bez_probelov.substr(i+1);
					cout << "Обращаем ваше внимание на то, что в вещественном числе, которое вы ввели, отсутствует дробная часть.\nВ таком случае мы считаем число целым." << endl;
				}
				else if (!(proverka_na_chislo(stroka_bez_probelov[i - 1]) && stroka_bez_probelov[i] == '.' && proverka_na_chislo(stroka_bez_probelov[i + 1])))
				{
					count_tochki++;
				}
			}
		}
		if (size(stroka_bez_probelov) == 1)
		{
			cout << "Вы ввели пустой запрос" << endl;
		}
		if (count_pystie_skobki)
		{
			cout << "Выражение в скобках не обозначено. Пожалуйста,исправьте выражение" << endl;
		}
		if (count_chisla)
		{
			cout << "В вашем выражении не хватает чисел. Пожалуйста, исправьте выражение." << endl;
		}
		if (count_null)
		{
			cout << "Числа не могут начинаться с нуля. Пожалуйста, исправьте выражение." << endl;
		}
		if (count_nachalo_stroki)
		{
			cout << "Выражение может начинаться только с числа(положительного или отрицательного) или с открытия скобки. Пожалуйста, исправьте выражение." << endl;
		}
		if (count_skobki)
		{
			cout << "В вашем выражении не хватает скобок. Пожалуйста, исправьте выражение." << endl;
		}

		if (count_postoronnie_simv)
		{
			cout << "В вашем выражении присутствуют посторонние символы.\nДопускаются только символы из набора: 1,2,3,4,5,6,7,8,9,0,+,-,*,.,(,),.\nВведите выражение правильно" << endl;
		}
		if (count_lishnie_znaki)
		{
			cout << "В вашем выражении встречается 2 или более подряд идущих арифметических знака (+,-,/,*). Пожалуйста, исправьте выражение." << endl;
		}
		if (count_tochki)
		{
			cout << "Точка в вашем выражении используется некорректно. Она должна использоваться только при написании дробных чисел.\nПожалуйста, исправьте выражение." << endl;
		}
		} while (count_postoronnie_simv || count_lishnie_znaki || count_skobki || count_null || count_nachalo_stroki||count_chisla|| count_tochki|| count_pystie_skobki);
	stroka_bez_probelov = stroka_bez_probelov.substr(1)+'\n';
	double result = 0;
	simv = get_next_simv(stroka_bez_probelov,index);
	result = summa(simv, stroka_bez_probelov, index);
	cout << "Полученный результат: "<<result;
	if (result != int(result))
	{
		cout << "\nP.S.Если вы использовали дробные числа или арифметический знак деления в выражении, результат может оказаться неточным в связи с утерей данных. \nТакая неприятность возможна из-за используемого типа double." <<endl ;
	}
	return 0;
}
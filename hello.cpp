#include <iostream>
#include <string>
#include <clocale>
using namespace std;
class  ATC{

private:
	string link;
	int numb;
	int sum;

public:
	ATC() : link(""), numb(0), sum(0) {}
	ATC(string s, int x, int y) : link(s), numb(x), sum(y) {}
	void summa()
	{
		cout << "���������� ����� ���� �������� ��� - " << link << ": " << numb * sum << endl;
	}
	
	void check1()
	{
		if (numb >= 0 && sum >= 0)
		{
			cout << "��� ������" << endl;
		}
		else
		{
			cout << "�� ����� ���� ������������� ��������� ��� �����" << endl;
		}
	}
	string getLink()
	{
		return link;
	}
	int getNumb()
	{
		return numb;
	}
	int getSum()
	{
		return sum;
	}
	void changeNumb(int x)
	{
		numb = x;
	}
	void changeSum(int y)
	{
		sum = y;
	}
};
int main()
{
	setlocale(LC_ALL, "ru");
	string s;
	int x, y;
	cout << "������� ����� ���: ";
	cin >> s;
	cout << "������� ����� ���������: ";
	cin >> x;
	cout << "������� ����������� �����: ";
	cin >>  y;
	ATC myATC(s, x, y);
	cout << myATC.getLink() << ' ' << myATC.getNumb() << ' ' << myATC.getSum() << endl;
	myATC.changeNumb(15);
	myATC.check1();
	myATC.summa();
	return 0;
}
#include <iostream>
#include <iomanip>
#include <fstream>
#include "myfunctions.h"
#include "myclasses.h"

using namespace std;

class AB
{
	int a, b;
public:
	AB() {
		a = 5; b = 8;
	};
	AB(int x, int y = 25) {
		a = x; b = y;
	}
	void set() {
		cout << "Введите значения полей a, b: ";
		cin >> a >> b;
	};
	void get() {
		cout << "a = " << a << ", b = " << b << endl;
	};
	int sum() {
		return a + b;
	};
	int mult() {
		return a * b;
	};
	void set(int amin, int amax, int bmin, int bmax) {
		a = rand() % (amax - amin + 1) + amin;
		b = rand() % (bmax - bmin + 1) + bmin;
	};
};

class clCircle
{
public:
	clCircle(double a = 0, double b = 0, double r = 1) {
		x = a; y = b; radius = r;
	};
	void set() {
		cin >> x >> y >> radius;
	};
	void set(double x0, double x1, double y0, double y1, double r0, double r1) {
		myrnd(&x, 1, x0, x1, 1);
		myrnd(&y, 1, y0, y1, 1);
		myrnd(&radius, 1, r0, r1, 1);
	};
	void set(const char* s, const char* sep) {
		char* p = (char*)s;
		p += myspn(p, sep);
		x = atof(p);
		p += mycspn(p, sep); p += myspn(p, sep);
		y = atof(p);
		p += mycspn(p, sep); p += myspn(p, sep);
		radius = atof(p);
	};
	double len() {
		return 2 * acos(-1) * radius;
	};
	double area() {
		return acos(-1) * radius * radius;
	};
	double dist(double a, double b) {
		double res = sqrt(pow(a - x, 2) + pow(b - y, 2)) - radius;
		return (res > 0 ? res : 0);
	};
	void get(int sw, int sp) {
		cout << right << fixed << setprecision(sp);
		cout << "(" << setw(sw) << x
			<< "," << setw(sw) << y
			<< "," << setw(sw) << radius << ")";
	};
	void get5(int sw = 8, int sp = 2) {
		cout << fixed << setprecision(sp)
			<< setw(sw) << x << " |"
			<< setw(sw) << y << " |"
			<< setw(sw) << radius << " |"
			<< " количество пересечений = ";
	};
	int intersection(clCircle* crc, int ncrc) {
		int n = 0;
		for (int i = 0; i < ncrc; i++)
			if (crc[i].dist(x, y) <= radius)
				n++;
		return n;
	};
private:
	double x, y, radius;
};

class clSession
{
public:
	clSession() {
		name = NULL; ng = 0; nval = 0; val = NULL;
	};
	~clSession() {
		delete[]name, delete[]val;
	};
	void set(const char* s) {
		char* p = str2int(s, 2, val) - 1;
		name = new char[p - s + 1]; 
		mycpy(name, s, p - s, 1);
		p = str2int(p, 1, &ng); 
		p = str2int(p, 1, &nval);
		val = new int[nval]; 
		str2int(p, nval, val);
	};
	void setname(const char* newname) {
		if (name != NULL) 
			delete[]name;
		name = new char[mylen(newname) + 1];
		mycpy(name, newname);
	};
	void setval(int ind, int newval) {
		if (val == NULL) 
			val = new int[nval];
		if (ind >= 0 && ind < nval)
			val[ind] = newval;
	};
	float mean() {
		if (nval)
			return meanval(val, nval);
	};
	void get(int nw, //знакомест для ФИО
		int nv, //количество отметок
		bool grout = false, //номер группы
		bool meanout = false) { //средняя отметка
		cout << left << setw(nw) << name << fixed;
		if (grout)
			cout << "группа №" << ng << "  ";
		for (int i = 0; i < nv; i++)
			cout << right << setw(3) << val[i];
		if (meanout)
			cout << "  Средняя = " << mean();
		cout << endl;
	};
	bool nameis(const char* s) {
		return !mycmp(name, s);
	};
private:
	char* name;
	int ng, nval, * val;
};

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	{
		title(1);
		AB ab1;
		ab1.set();
		cout << "Сумма полей = " << ab1.sum() << endl;
		cout << "Произведение полей = " << ab1.mult() << endl;
		ab1.set(-99, 99, -99, 99);
		cout << "Новые значения полей объекта ab1: ";
		ab1.get();
		cout << "Сумма полей = " << ab1.sum() << endl;
		cout << "Произведение полей = " << ab1.mult() << endl;

		AB ab2;
		cout << "Значения полей объекта ab2: ";
		ab2.get();

		AB ab3(12, -10);
		cout << "Значения полей объекта ab3: ";
		ab3.get();

		AB ab4(30);
		cout << "Значения полей объекта ab4: ";
		ab4.get();
	}

	{
		title(2);
		int n;
		cout << "Размер массива: "; cin >> n;
		arD array(n);
		array.set(-99, 99);
		cout << "Массив случайных чисел:\n";
		array.get(10);
		cout << "Диапазон массива = " << array.min() << ".." << array.max();
		cout << "\nСреднее значение = " << array.mean();
		cout << "\nСортировка по возрастанию:\n";
		array.srt(true);
		array.get(10);
	}

	{
		title(3);
		AB* pab1, * pab2;
		pab1 = new AB; pab2 = new AB(1, 2);
		cout << "Поля первого динамического объекта: "; pab1->get();
		cout << "Поля второго динамического объекта: "; pab2->get();
		AB* pab3; pab3 = new AB[10];
		for (int i = 0; i < 10; i++)
			pab3[i].set(-9, 9, -9, 9);
		cout << "Поля последнего динамического объекта: "; pab3[9].get();
	}

	{
		title(4);
		int nc = 20;
		clCircle* arC = new clCircle[nc];
		cout << "Динамический массив из " << nc << " объектов clCircle:\n";
		for (int i = 0; i < nc; i++)
		{
			arC[i].set(-9.9, 9.9, -9.9, 9.9, 1, 9.9);
			arC[i].get(4, 1);
			if ((i + 1) % 5 == 0)
				cout << endl;
		}

		clCircle* pmax = arC;
		double maxlen = 0;
		for (int i = 0; i < nc; i++)
		{
			double len = arC[i].dist(0, 0);
			if (len > maxlen)
			{
				maxlen = len;
				pmax = &arC[i];
			}
		}

		cout << "\nСамый удалённый от начала координат круг ";
		pmax->get(4, 1);
		cout << " имеет площадь " << setprecision(3) << pmax->area() << endl;
		delete[]arC;
	}

	{
		title(5);
		char* s = new char[1024];
		int nstud = myinput(s, "13.5.txt");
		clSession* stud = new clSession[nstud];
		char* p = s;
		for (int i = 0; i < nstud; i++) {
			stud[i].set(p);
			p += mylen(p) + 1;
		}
		cout << "Исходный список:\n";
		for (int i = 0; i < nstud; i++)
			stud[i].get(20, 4);

		for (int i = 0; i < nstud; i++)
			if (stud[i].nameis("Маевская И.Н.")) {
				stud[i].setname("Миронова И.Н.");
				break;
			}
		for (int i = 0; i < nstud; i++)
			if (stud[i].nameis("Рыжов В.И.")) {
				stud[i].setval(2, 5);
				stud[i].setval(3, 4);
				break;
			}

		clSession** srt = new clSession * [nstud];
		double* mv = new double[nstud];

		for (int i = 0; i < nstud; i++) {
			srt[i] = &stud[i];
			mv[i] = stud[i].mean();
		}

		mysrt(mv, nstud, 0, (double**)srt);
		cout << "\nИтоговый список:\n" << fixed << setprecision(2);
		for (int i = 0; i < nstud; i++)
			srt[i]->get(20, 0, 0, 1);

		delete[]s; delete[]stud; delete[]srt; delete[]mv;
	}

	{
		title(6);
		char* s = new char[5000];
		int nc = myinput(s, "925.txt");
		clCircle* circles = new clCircle[nc];
		char* p = s + 1;
		for (int i = 0; i < nc; i++) {
			circles[i].set(p, "; ");
			p += mylen(p) + 2;
		}

		clCircle** pcircles = new clCircle * [nc];
		int* intersections = new int[nc];
		int nint = 0;
		for (int i = 0; i < nc; i++) {
			pcircles[i] = &circles[i];
			intersections[i] = circles[i].intersection(circles, nc) - 1;
			if (intersections[i])
				nint++;
		}

		mysrt(intersections, nc, false, (int**)pcircles);

		cout << "Количество пересекающихся кругов = " << nint << endl
			<< setw(6) << "X" << setw(10) << "Y" << setw(11) << "R\n";
		for (int i = 0; i < nc; i++) {
			if (intersections[i]) {
				pcircles[i]->get5();
				cout << intersections[i] << endl;
			}
		}

		delete[]pcircles;
		delete[]circles;
		delete[]intersections;
	}

	cout << endl; system("pause");
	return 0;
}
#include <iostream>
using namespace std;

typedef struct tagGregorian
{
	int   year;
	int   month;
	int   day;
	int   hour;
	int   minute;
	double   second;
}Gregorian;
typedef Gregorian *PGregorian;
typedef struct tagTOD
{
	long sn;  //秒数的整数部分
	double tos;//秒数的小数部分
}TOD;
typedef TOD *PTOD;
typedef struct
{
	long day; //整数天数
	TOD tod;  //一天内的秒数
}JULIANDAY;//儒略日
typedef JULIANDAY *PJULIANDAY;
typedef struct tagDOY
{
	unsigned short year;
	unsigned short day;
	TOD tod;
}DOY;//年积日
typedef DOY *PDOY;
double FRAC(double morigin)
{
	return morigin - long(morigin);// 取小数部分
}
void GregorianToJulianDay(PGregorian pct, PJULIANDAY pjd) //通用时到儒略日的转换
{
	if (pct->year<1900)
	{
		if (pct->year<80)
			pct->year += 2000;
		else pct->year += 1900;
	}
	double ut = pct->hour + pct->minute / 60.0 + pct->second / 3600.0;
	if (pct->month <= 2)
	{
		pct->year -= 1;
		pct->month += 12;
	}
	pjd->day = int(365.25*pct->year) + int(30.6001*(pct->month + 1)) + pct->day + int(ut / 24 + 1720981.5);
	pjd->tod.sn = ((pct->hour + 12) % 24) * 3600 + pct->minute * 60 + (int)pct->second;//秒的整数部分
	pjd->tod.tos = pct->second - (int)pct->second;//秒的小数部分
}
void JulianDayToGregorian(PJULIANDAY pjd, PGregorian pct)//儒略日到格里高利历的转换
{
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	int a = int(x + 0.5);
	int b = int(4 * (a + 68569) / 146097);
	int c = a + 68569 - int((b * 146097 + 3) / 4);
	int d = int(4000 * (c + 1) / 1461001);
	int e = c - int(1461 * d / 4) + 31;
	double f = int(80 * e / 2447);
	int g = int(f / 11);
	double h = (x + 0.5 - a) * 24 - 24*int((x + 0.5 - a) * 24 / 24);
	pct->hour = int(h);
	double j = (h - pct->hour)*60;
	pct->day = e - int(2447 * f / 80);
	pct->month = f + 2 - 12*g;
	pct->year = int(100 * (b - 49) + d + g);
	pct->minute = int(j);
	pct->second = (j - pct->minute)*60;
}
void JulianDayToDOY(PJULIANDAY pjd)
{
    PJULIANDAY pjdo = new JULIANDAY;
	PGregorian pct = new Gregorian;
	PGregorian pcto = new Gregorian;
	PDOY pdoy = new DOY;
	JulianDayToGregorian(pjd, pct);
	pcto->year = pct->year;
	pcto->month = 1;
	pcto->day = 1;
	pcto->hour = 0;
	pcto->minute = 0;
	pcto->second = 0;
	GregorianToJulianDay(pcto, pjdo);
	pdoy->year = pct->year;
	pdoy->day = pjd->day - pjdo->day + 1;
	if(pjd->tod.sn >= 43200)
    {
        pdoy->day = pjd->day - pjdo->day + 1;
        pdoy->tod.sn = pjd->tod.sn - 43200;
    }
    else
    {
        pdoy->day = pjd->day - pjdo->day;
        pdoy->tod.sn = pjd->tod.sn + 43200;
    }
	pdoy->tod.tos = pjd->tod.tos;
	cout << "儒略日向年积日的转换:";
	cout << pdoy->year << " 年 " << pdoy->day << " 日 " << pdoy->tod.sn << "整数秒" << pdoy->tod.tos << "小数秒" <<endl;
	cout << endl;
}
void DOYToJuliandayTime(PDOY pdoy)
{
	PGregorian pcto = new Gregorian;
	PGregorian pct = new Gregorian;
	pcto->year = pdoy->year;
	pcto->month = 1;
	pcto->day = 1;
	pcto->hour = 0;
	pcto->minute = 0;
	pcto->second = 0;
	PJULIANDAY pjdo = new JULIANDAY;
	PJULIANDAY pjdo1 = new JULIANDAY;
	GregorianToJulianDay(pcto, pjdo);
	pjdo1->day = pjdo->day + pdoy->day - 1 + int((pjdo->tod.sn + pdoy->tod.sn)/86400);
	pjdo1->tod.sn = (pjdo->tod.sn + pdoy->tod.sn)%86400;
	pjdo1->tod.tos = pdoy->tod.tos;
    cout << "年积日向儒略日的转换:";
	cout << pjdo1->day << " 日 " << pjdo1->tod.sn << " 整数秒 " << pjdo1->tod.tos << "小数秒" << endl;
	cout << endl;
	JulianDayToDOY(pjdo1);
}
int main()
{
	PDOY pdoy = new DOY;
	printf("请输入年+年积日+天内秒整数部分+天内秒小数部分\n");
	cin>>pdoy->year>>pdoy->day>>pdoy->tod.sn>>pdoy->tod.tos;
	DOYToJuliandayTime(pdoy);
}

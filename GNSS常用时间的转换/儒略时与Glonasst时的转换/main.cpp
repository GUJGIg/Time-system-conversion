#include <iostream>
using namespace std;
typedef struct tagTOD
{
	long sn;  //秒数的整数部分
	double tos;//秒数的小数部分
}TOD;
typedef TOD *PTOD;
typedef struct tagTOW
{
	long sn;//秒整数部分
	double tos;//秒小数部分
}TOW;
typedef TOW *PTOW;
typedef struct tagGLONASSTTIME
{
	int   N4;
	int   NT;
	int   h;
	int   m;
	double   s;
}GLONASSTTIME;//GLONASST时
typedef GLONASSTTIME *PGLONASSTTIME;
typedef struct tagGregorian
{
	int   year;
	int   month;
	int   day;
	int   hour;
	int   minute;
	double   second;
}Gregorian;//格里高利历
typedef Gregorian *PGregorian;
typedef struct
{
	long day; //整数天数
	TOD tod;  //一天内的秒数
}JULIANDAY;//儒略日
typedef JULIANDAY *PJULIANDAY;
void GregorianToJulianDay(PGregorian pct, PJULIANDAY pjd) //格里高利历到儒略日的转换
{
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
	int b = a + 1537;
	int c = int((b - 122.1) / 365.25);
	int d = int(365.25*c);
	int e = int((b - d) / 30.6001);
	pct->day = b - d - int(30.6001*e);
	pct->month = e - 1 - 12 * int(e / 14);
	pct->year = c - 4715 - int((7 + pct->month) / 10);
	pct->hour = (pjd->tod.sn / 3600 + 12) % 24;
	pct->minute = (pjd->tod.sn % 3600) / 60;
	pct->second = pjd->tod.sn % 60 + pjd->tod.tos;
}
void GLONASSTTIMETOJULIANDAY(PGLONASSTTIME pgnt, PJULIANDAY pjd)
{
    PGregorian pgro = new Gregorian;
    pgro->year = 1996 + 4*(pgnt->N4 - 1);
	pgro->month = 1;
	pgro->day = 1;
	pgro->hour = 0;
	pgro->minute = 0;
	pgro->second = 0;
	PJULIANDAY pjdo = new JULIANDAY;
    GregorianToJulianDay(pgro, pjdo);
    PJULIANDAY PJD = new JULIANDAY;
    PJD->day = pjdo->day + pgnt->NT - 1;
    PJD->tod.sn = ((pgnt->h + 12) % 24) * 3600 + pgnt->m * 60 + (int)pgnt->s;//秒的整数部分
	PJD->tod.tos = pgnt->s - (int)pgnt->s;//秒的小数部分
	cout << PJD->day << " 日 " << PJD->tod.sn << " 整数秒 " << PJD->tod.tos << "小数秒" << endl;
	cout << endl;
}
void JulianDayToGLONASSTTime(PJULIANDAY pjd, PGLONASSTTIME pgnt)//儒略日到GLONASST时的转换
{
    PGregorian pgro = new Gregorian;
	JulianDayToGregorian(pjd, pgro);
	pgnt->N4 = int((pgro->year - 1996)/4) + 1;
	PGregorian pGR = new Gregorian;
	PJULIANDAY pjdo = new JULIANDAY;
	pGR->year = 1996 + 4*(pgnt->N4 - 1);
	pGR->month = 1;
	pGR->day = 1;
	pGR->hour = 0;
	pGR->minute = 0;
	pGR->second = 0;
	GregorianToJulianDay(pGR, pjdo);
	pgnt->NT = pjd->day - pjdo->day + 1;
	pgnt->h = pgro->hour;
	pgnt->m = pgro->minute;
	pgnt->s = pgro->second;
	cout << pgnt->N4 << " : " << pgnt->NT << " : " << pgnt->h << " : " << pgnt->m << " : " << pgnt->s <<endl;
	cout << endl;
}
int main()
{
    PGLONASSTTIME pgnt = new GLONASSTTIME;
	PJULIANDAY pjd = new JULIANDAY;
	printf("请输入儒略日整数天+天内秒整数部分+天内秒小数部分\n");
	cin>>pjd->day>>pjd->tod.sn>>pjd->tod.tos;
	JulianDayToGLONASSTTime(pjd, pgnt);
	GLONASSTTIMETOJULIANDAY(pgnt, pjd);
}

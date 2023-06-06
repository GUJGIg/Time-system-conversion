#include <iostream>
#include <math.h>
using namespace std;
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
typedef struct tagTOW
{
	long sn;//秒整数部分
	double tos;//秒小数部分
}TOW;
typedef TOW *PTOW;
typedef struct tagGPSTIME
{
	int wn; //周数
	TOW second;
}GPSTIME;//GPS时
typedef GPSTIME *PGPSTIME;
void JulianDayToGPSTime(PJULIANDAY pjd, PGPSTIME pgt)//儒略日到GPS时的转换
{
	long double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	pgt->wn = int((x - 2444244.5) / 7);
	pgt->second.sn = int(((pjd->day - 2444244) % 7 + (pjd->tod.sn / (60.0*60.0 * 24) - 0.5)) * 86400);
	pgt->second.tos = pjd->tod.tos;
}
void GPSTimeToJulianDay(PGPSTIME pgt, PJULIANDAY pjd)//GPS时到儒略日的转换
{
	pjd->day = int(pgt->wn * 7 + double(pgt->second.sn) / 86400.0 + 2444244.5);
	pjd->tod.sn = (pgt->second.sn + 43200) % 86400;
	pjd->tod.tos = pgt->second.tos;
	cout << "GPS时向儒略日的转换:";
	cout << pjd->day << "  " << pjd->tod.sn << "  " << pjd->tod.tos << endl;
	cout << endl;
}
int main()
{
	PJULIANDAY pjd = new JULIANDAY;
	PGPSTIME pgt = new GPSTIME;
	printf("请输入儒略日整数天+天内秒整数部分+天内秒小数部分\n");
	cin>>pjd->day>>pjd->tod.sn>>pjd->tod.tos;
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	if(x >= 2444244.5)
    {
        JulianDayToGPSTime(pjd, pgt);//儒略日->GPS时的转换
	cout << "儒略日向GPS时的转换:";
	cout << pgt->wn << " 周 " << pgt->second.sn << " 整数秒 " << pgt->second.tos << "小数秒" << endl;
	cout << endl;
	GPSTimeToJulianDay(pgt, pjd);//GPS时->儒略日的转换
    }
	else
    {
        printf("请输入大于2444244.5的儒略日");
    }
}

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
typedef struct tagBDSTIME
{
	int wn; //周数
	TOW second;
}BDSTIME;//GPS时
typedef BDSTIME *PBDSTIME;
void JulianDayToBDSTime(PJULIANDAY pjd, PBDSTIME pbt)//儒略日到GPS时的转换
{
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	pbt->wn = int((x - 2453736.5) / 7);
	pbt->second.sn = int(((pjd->day - 2453736) % 7 + (pjd->tod.sn / (60.0*60.0 * 24) - 0.5)) * 86400);
	pbt->second.tos = pjd->tod.tos;
	if(pbt->second.sn<0)
    {
        pbt->second.sn=pbt->second.sn+1;
    }
}
void BDSTimeToJulianDay(PBDSTIME pbt, PJULIANDAY pjd)//GPS时到儒略日的转换
{
	pjd->day = int(pbt->wn * 7 + double(pbt->second.sn) / 86400.0 + 2453736.5);
	pjd->tod.sn = (pbt->second.sn + 43200) % 86400;
	pjd->tod.tos = pbt->second.tos;
	cout << "BDS时向儒略日的转换:";
	cout << pjd->day << "  " << pjd->tod.sn << "  " << pjd->tod.tos << endl;
	cout << endl;
}
int main()
{
	PJULIANDAY pjd = new JULIANDAY;
	PBDSTIME pbt = new BDSTIME;
	cin>>pjd->day>>pjd->tod.sn>>pjd->tod.tos;
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	if(x >= 2453736.5)
    {
        JulianDayToBDSTime(pjd, pbt);//儒略日->GPS时的转换
	cout << "儒略日向BDS时的转换:";
	cout << pbt->wn << " 周 " << pbt->second.sn << " 整数秒 " << pbt->second.tos << "小数秒" << endl;
	cout << endl;
	BDSTimeToJulianDay(pbt, pjd);//GPS时->儒略日的转换
    }
	else
    {
        printf("请输入大于2453736.5的儒略日");
    }
}

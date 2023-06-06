#include <iostream>
using namespace std;
typedef struct tagTOW
{
	long sn;//秒整数部分
	double tos;//秒小数部分
}TOW;
typedef TOW *PTOW;
typedef struct tagGLSTIME
{
	int wn; //周数
	TOW second;//一周内的秒数
}GLSTIME;//GPS时
typedef GLSTIME *PGLSTIME;
typedef struct tagTOD
{
	long sn;  //秒数的整数部分
	double tos;//秒数的小数部分
}TOD;
typedef struct
{
	long day; //整数天数
	TOD tod;  //一天内的秒数
}JULIANDAY;//儒略日
typedef JULIANDAY *PJULIANDAY;
void GLSTimeToJulianDay(PGLSTIME glt, PJULIANDAY pjd)
{
	pjd->day = int(glt->wn * 7 + double(glt->second.sn) / 86400.0 + 2451512.5);
	pjd->tod.sn = (glt->second.sn + 43200) % 86400;
	pjd->tod.tos = glt->second.tos;
	cout << "Galileo时向儒略日的转换:";
	cout << pjd->day << "  " << pjd->tod.sn << "  " << pjd->tod.tos << endl;
	cout << endl;
}
void JulianDayToGLSTime(PJULIANDAY pjd, PGLSTIME glt)
{
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	glt->wn = int((x - 2451512.5) / 7);
	glt->second.sn = int(((pjd->day - 2451512) % 7 + (pjd->tod.sn / (60.0*60.0 * 24) - 0.5)) * 86400);
	glt->second.tos = pjd->tod.tos;
	if(glt->second.sn<0)
    {
        glt->second.sn=glt->second.sn+604800;
    }
}
int main()
{
	PJULIANDAY pjd = new JULIANDAY;
	PGLSTIME glt = new GLSTIME;
	printf("请输入儒略日整数天+天内秒整数部分+天内秒小数部分\n");
	cin>>pjd->day>>pjd->tod.sn>>pjd->tod.tos;
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	if(x >= 2451512.5)
    {
        JulianDayToGLSTime(pjd, glt);//儒略日->GPS时的转换
	cout << "儒略日向Galileo时的转换:";
	cout << glt->wn << " 周 " << glt->second.sn << " 整数秒 " << glt->second.tos << "小数秒" << endl;
	cout << endl;
	GLSTimeToJulianDay(glt, pjd);
    }
	else
    {
        printf("请输入大于2451512.5的儒略日");
    }
}

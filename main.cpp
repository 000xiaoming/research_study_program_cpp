#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <set>
#include <cstdlib>
using std::set;
using std::cout;
using std::cin;
using std::endl;
using std::string;
int menu1_1_1();//函数声明，放在最前面
int menu1_1_2();
int menu1_1_3();
int menu1_1_4();
int menu2_1_1();
int menu2_1_2();
int menu2_1_3();
int menu2_1_4();
int menu2_1_5();
class administrators//管理员结构体声明fughf给
{
private:
	string adminis;//管理员账号
	string lockCode;//管理员密码
	string name;//管理员姓名
	string workCode;//管理员编号
	string inTime;//管理员登录时间
public:
	administrators() :adminis("ad"), lockCode("123"), name("LiHua"), workCode("10001") {//这是默认的值
		time_t now;
		time(&now);
		tm p;
		localtime_s(&p, &now);
		char buf[20] = { 0 };
		snprintf(buf, 20, "%04d:%02d:%02d %02d:%02d",p.tm_year+1900,p.tm_mon+1,p.tm_mday,p.tm_hour,p.tm_min);//这是把值转化成字符串的函数，类似printf函数，转化的字符串存储在buf数组内
		inTime = string(buf);//这几行代码是使用的是ctime头文件中的时间函数，用来计算从计算机诞生起到现在的秒速
	}
	friend int menu1_1_1();
	friend int menu1_1_3();//friend关键字，用来说明，这几个函数，可以修改该类的私有成员

};
class node
{
public:
	string numberplate;//车牌
	string carHost;//车主
	string phoneNumber;//手机号
	string idCard;//身份证
	string carType;//车辆类型，Big型，和Small型
	string inTime;//入场时间
	int carPosition;//车辆停放的位置在第几号
	int stopNumber;//该车辆一共停过几次
	int inCourt;//判断是否在停车场内，1表示在，0表示不在
	string outTime;//出场时间
	int timeLong;//一共的在场时长
	string fee;//缴费费用

	string example;//空字符串，无用

	node():stopNumber(0),carPosition(0),inCourt(0),timeLong(0) {}//构造函数，初始化，,string类的数据不用初始化，它有自己内部的初始化函数，不用管，会帮助我们自动初始化的

	friend bool operator < (const node& e1, const node& e2)//<运算符重载，用来使用set集合的插入
	{
		return e1.numberplate < e2.numberplate;
	}
};
set<node> RBtree;//声明为全局set，存放在堆中
int hashTablePosition[100];//100个车位，每一个车位的值为1时，有车，为0时，无车，存放在堆中
administrators theHost;//创建管理员对象，存放在堆中
int rate = 5; //费率
//管理员登录
int menu1_1_1()
{
	thisPosition: //goto  跳转目的地
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************欢迎使用停车场管理系统********************\n");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                      * * * * * * * *                       *\n");
	printf("\t\t*----------------------需管理员登录使用----------------------*\n");
	printf("\t\t*                      * * * * * * * *                       *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	printf("\t\t请输入管理员账号：");
	char buf1[20];//临时变量，用来暂时存储输入的数据
	cin >> buf1;
	getchar(); //所有的getchar函数，都是用来吃掉缓冲区里的回车键，不然输入和输入提示对不齐
	printf("\t\t请输入管理员密码：");
	char buf2[20];//临时变量，用来暂时存储输入的数据
	cin >> buf2;
	getchar();
	if (theHost.adminis != string(buf1) || theHost.lockCode != string(buf2))
		goto thisPosition;

	if(menu1_1_2())
		goto thisPosition;
	return 0;//无法返回这个界面，因为这个界面是最高层界面
}

//登录成功界面
int menu1_1_2()
{
	thisPosition:
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************-------登录成功-------********************\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                      1.修改管理员信息                      *\n");
	printf("\t\t*                      2.进入管理界面                        *\n");
	printf("\t\t*                      3.返回                                *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	printf("\t\t请输入命令：");
	int command;//临时变量，用来暂时存储输入的数据
	cin >> command;
	getchar();
	switch (command)
	{
	case 1:menu1_1_3();goto thisPosition;
	case 2:menu1_1_4();goto thisPosition;
	case 3:return 1;
	default:goto thisPosition;
	}
}

//管理员修改
int menu1_1_3()
{
thisPosition:
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************-------登录成功-------********************\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                        1.修改账号                          *\n");
	printf("\t\t*                        2.修改密码                          *\n");
	printf("\t\t*                        3.修改姓名                          *\n");
	printf("\t\t*                        4.修改工作编号                      *\n");
	printf("\t\t*                        5.查看登录时间                      *\n");
	printf("\t\t*                        6.返回                              *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	printf("\t\t请输入命令：");
	int command;//临时变量，用来暂时存储输入的数据
	cin >> command;
	getchar();
	string n;//临时变量，用来暂时存储输入的数据
	switch (command)
	{
	case 1: cout << "\t\t您的原账号：" << theHost.adminis << endl;
		cout << "\t\t输入新账号：";cin >> n;getchar();theHost.adminis = n;
			goto thisPosition;
	case 2: cout << "\t\t您的原密码：" << theHost.lockCode << endl;
		cout << "\t\t输入新密码：";cin >> n;getchar();theHost.lockCode = n;
			goto thisPosition;
	case 3: cout << "\t\t您的原姓名：" << theHost.name << endl;
		cout << "\t\t您的新姓名：";cin >> n;getchar();theHost.name = n;
			goto thisPosition;
	case 4: cout << "\t\t您的原编号：" << theHost.workCode << endl;
		cout << "\t\t您的新编号：";cin >> n;getchar();theHost.workCode = n;
			goto thisPosition;
	case 5:	cout << "\t\t登录时间：" << theHost.inTime;getchar();
			goto thisPosition;
	default:;
	}
	return 1;
}

//管理界面
int menu1_1_4()
{
thisPosition:
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************-------登录成功-------********************\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                        1.车辆入场                          *\n");
	printf("\t\t*                        2.车位管理                          *\n");
	printf("\t\t*                        3.信息管理                          *\n");
	printf("\t\t*                        4.计费结账                          *\n");
	printf("\t\t*                        5.车辆出场                          *\n");
	printf("\t\t*                        6.返回                              *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	printf("\t\t请输入命令：");
	int command;//临时变量，用来暂时存储输入的数据
	cin >> command;
	getchar();
	switch (command)
	{
	case 1:menu2_1_1();goto thisPosition;
	case 2:menu2_1_2();goto thisPosition;
	case 3:menu2_1_3();goto thisPosition;
	case 4:menu2_1_4();goto thisPosition;
	case 5:menu2_1_5();goto thisPosition;
	default: return 1;
	}
}

//车辆入场
int menu2_1_1()
{
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************-------车辆入场-------********************\n");
	printf("\t\t*                     入场时间已自动识别                     *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                           需输入：                         *\n");
	printf("\t\t*                           车牌号                           *\n");
	printf("\t\t*                           车辆类型                         *\n");
	printf("\t\t*                           车主姓名                         *\n");
	printf("\t\t*                           车主手机号码                     *\n");
	printf("\t\t*                           车主身份证号码                   *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	node theCar;//创建一个车辆对象
	printf("\t\t请输入车牌号：");
	string n;//临时变量，用来暂时存储输入的数据
	cin >> n;
	getchar();
	theCar.numberplate = n;
	printf("\t\t请输入车辆类型：");
	cin >> n;
	getchar();
	theCar.carType = n;
	printf("\t\t请输入车主姓名：");
	cin >> n;
	getchar();
	theCar.carHost = n;
	printf("\t\t请输入车主手机号码：");
	cin >> n;
	getchar();
	theCar.phoneNumber = n;
	printf("\t\t请输入车主身份证号码：");
	cin >> n;
	getchar();
	theCar.idCard = n;

	theCar.inCourt = 1;
	string Big("Big");//表示车辆类型
	string Small("Small");
	auto pItem = RBtree.find(theCar);//使用set的内部查找函数，返回是一个iterator类型，具体名字较长，可以用auto，帮我们自动辨别类型，反正是一个指针
	if (pItem == RBtree.end())//set内部end函数，返回最后一个数据的后一位位置的指针
	{
		time_t now;
		time(&now);
		tm p;
		localtime_s(&p, &now);
		char buf[20] = { 0 };
		snprintf(buf, 20, "%04d:%02d:%02d %02d:%02d", p.tm_year + 1900, p.tm_mon + 1, p.tm_mday, p.tm_hour, p.tm_min);
		theCar.inTime = string(buf);//经典时间函数的使用

		++theCar.stopNumber;//停车次数加一
		theCar.outTime = theCar.example;  //让outTime数据为空
		if (theCar.carType == Small)//小型车辆
		{
			for (int i = 0;i < 80;++i)
			{
				if (hashTablePosition[i] == 0)
				{
					hashTablePosition[i] = 1;
					theCar.carPosition = i;
					break;
				}
			}
		}
		else//大型车辆
		{
			for (int i = 80;i < 100;++i)
			{
				if (hashTablePosition[i] == 0)
				{
					hashTablePosition[i] = 1;
					theCar.carPosition = i;
					break;
				}
			}
		}
		RBtree.insert(theCar);
	}
	else
	{
		time_t now;
		time(&now);
		tm p;
		localtime_s(&p, &now);
		char buf[20] = { 0 };
		snprintf(buf, 20, "%04d:%02d:%02d %02d:%02d", p.tm_year + 1900, p.tm_mon + 1, p.tm_mday, p.tm_hour, p.tm_min);
		theCar.inTime = string(buf);

		theCar.stopNumber=pItem->stopNumber;
		RBtree.erase(pItem);//因为iterator，无法改变数据的值，干脆把这个对象复制下来，然后把它叉掉，再将副本修改，将副本再插入set集合内部
		++theCar.stopNumber;
		theCar.outTime = theCar.example;
		if (theCar.carType == Big)
		{
			for (int i = 0;i < 80;++i)
			{
				if (hashTablePosition[i] == 0)
				{
					hashTablePosition[i] = 1;
					theCar.carPosition = i;
					break;
				}
			}
		}
		else
		{
			for (int i = 80;i < 100;++i)
			{
				if (hashTablePosition[i] == 0)
				{
					hashTablePosition[i] = 1;
					theCar.carPosition = i;
					break;
				}
			}
		}
		RBtree.insert(theCar);
	}
	printf("\t\t入场时间为：");
	cout << theCar.inTime;
	getchar();
	return 1;
}

//车位管理
int menu2_1_2()
{
thisPosition:
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************-------车位管理-------********************\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                          1.车位数量                        *\n");
	printf("\t\t*                          2.车位位置                        *\n");
	printf("\t\t*                          3.车位号码                        *\n");
	printf("\t\t*                          4.车位规格                        *\n");
	printf("\t\t*                          5.返回                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	printf("\t\t请输入命令：");
	int command;//临时变量，用来暂时存储输入的数据
	cin >> command;
	getchar();
	int i = 0;
	int index = 0;
	switch (command)
	{
	case 1:cout << "车位总数量：100 " << "车位空余数量：";
		
		for (int t = 0;t < 100;++t)
			if (hashTablePosition[t] == 0)
				++index;
		cout << index;
		getchar();
		goto thisPosition;
	case 2:
		system("cls");
	printf("\t\t_____________________________________________________________\n");//都是画图，没什么可说的
	printf("\t\t          *          *          *          *          *        \n");
	printf("\t\t%02d-%02d     ",i,i+4);if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("        \n");
	printf("\t\t%02d-%02d     ", i, i + 4);if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
	printf("        \n");
	for (int t = 0;t < 18;++t)
	{
		printf("\t\t%d-%d     ", i, i + 4);if (hashTablePosition[i++] == 1)printf("1");else printf("0");
		printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
		printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
		printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
		printf("          ");if (hashTablePosition[i++] == 1)printf("1");else printf("0");
		printf("        \n");
	}
	cout << "\t\t按回车键继续";
	getchar();
	goto thisPosition;
	case 3:
		system("cls");
		i = 0;
		printf("\t\t_____________________________________________________________\n");
		printf("\t\t          *          *          *          *          *        \n");
		for (int t = 0;t < 20;++t)
		{
			printf("\t\t%02d-%02d     ", i, i + 4);printf("%02d", i++);
			printf("         ");printf("%02d", i++); 
			printf("         ");printf("%02d", i++);
			printf("         ");printf("%02d", i++); 
			printf("         ");printf("%02d", i++);
			printf("        \n");
		}
		cout << "\t\t按回车键继续";
		getchar();
		goto thisPosition;
	case 4:cout << "\t\t0-79 为小车规格 80-99 为大车规格";
		getchar();
		goto thisPosition;
	default:return 1;
	}
}

//信息管理
int menu2_1_3()
{
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************-------信息管理-------********************\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                       请输入查询车牌                       *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	printf("\t\t请输入查询车牌：");
	string n;
	cin >> n;
	getchar();
	node one;//临时变量，用来暂时存储输入的数据
	one.numberplate = n;
	auto pItem = RBtree.find(one);
	if (pItem != RBtree.end())
	{
		system("cls");
		printf("\t\t********************----------------------********************\n");//也都是画图，和打印数据
		printf("\t\t______________________________________________________________\n");
		printf("\t\t车牌号码：");cout << pItem->numberplate << endl;
		printf("\t\t车主信息：");cout << pItem->carHost << endl;
		printf("\t\t停车记录：");cout << pItem->stopNumber << " 次" << endl;
		printf("\t\t车辆信息：\n");
		printf("\t\t\t\t车辆类型：");cout << pItem->carType << endl;
		printf("\t\t\t\t车位号码：");cout << pItem->carPosition << endl;
		printf("\t\t停车时间：");cout << pItem->inTime << endl;
		printf("\t\t按回车键返回");
		getchar();
	}
	else
	{
		cout << "\t\t无此车信息";
		printf("\t\t按回车键返回");
		getchar();
	}
	return 1;
}

//计时缴费
int menu2_1_4()
{
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************-------计费结账-------********************\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                       输入车牌结账                         *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	printf("\t\t请输入车牌：");
	string n;
	cin >> n;
	getchar();
	node search;
	search.numberplate = n;
	auto pItem = RBtree.find(search);
	if (pItem != RBtree.end())
	{
		if (pItem->inCourt == 1)
		{
			cout << "\t\t此车还在停车场，服务未终止，不能结算";
			getchar();
			return 1;
		}
		printf("\t\t该车牌\n");
		node newOne = *pItem;
		char timeLong1[20];

		strcpy(timeLong1, newOne.inTime.data());



		char timeLong2[20];
		strcpy(timeLong2, newOne.outTime.data());



		char hour[3] = { 0 };
		hour[0] = timeLong1[11];
		hour[1] = timeLong1[12];


		char second[3] = { 0 };
		second[0] = timeLong1[14];
		second[1] = timeLong1[15];


		char day[3] = { 0 };
		day[0] = timeLong1[8];
		day[1] = timeLong1[9];


		char hour2[3] = { 0 };
		hour2[0] = timeLong2[11];
		hour2[1] = timeLong2[12];



		char second2[3] = { 0 };
		second2[0] = timeLong2[14];
		second2[1] = timeLong2[15];


		char day2[3] = { 0 };
		day2[0] = timeLong2[8];
		day2[1] = timeLong2[9];//用来剥离时间字符串中各个时间点，把日期，小时，分钟，剥离出来


		int timeLong = 0;//使用atoi函数，可以把字符串里的数字转化成整型数值
		timeLong = -((atoi(day) * 24 * 60 )+ (atoi(hour) * 60) +( atoi(second)) -( atoi(day2) * 24 * 60) - (atoi(hour2)*60) - (atoi(second2)));//入场时间减去出场时间，取反
		newOne.timeLong = timeLong;
		printf("\t\t\t停车时长：");cout << newOne.timeLong << " 分钟" << endl;
		printf("\t\t\t停车费用：");printf("%f 元\n", (float)newOne.timeLong / 60 * rate);
		printf("\t\t\t计费类型：");cout << "按时计费，费率：" << rate << endl;
		printf("\t\t\t结账时间：");

		time_t now;
		time(&now);
		tm p;
		localtime_s(&p, &now);
		char buf[20] = { 0 };
		snprintf(buf, 20, "%04d:%02d:%02d %02d:%02d", p.tm_year + 1900, p.tm_mon + 1, p.tm_mday, p.tm_hour, p.tm_min);
		cout << string(buf) << endl;

		printf("\t\t\t结账方式：");cout << "电子账单"<<endl;
		printf("\t\t按回车键继续");
		getchar();
	}
	else
	{
		cout << "\t\t无此车信息";
		printf("\t\t按回车键继续");
		getchar();
	}
	return 1;
}

//车辆出场
int menu2_1_5()
{
	system("cls");
	printf("\t\t********************----------------------********************\n");
	printf("\t\t********************-------车辆出场-------********************\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                       请输入出场车牌                       *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t*                                                            *\n");
	printf("\t\t**************************************************************\n");
	printf("\t\t**************************************************************\n");
	printf("\n");
	printf("\t\t______________________________________________________________\n");
	printf("\t\t输入提示\n");
	printf("\t\t请输入出场车牌：");
	string n;
	cin >> n;
	getchar();
	node one;
	one.numberplate = n;
	auto pItem = RBtree.begin();
	for (;pItem != RBtree.end();++pItem)
		if (pItem->numberplate == one.numberplate)//老样子，没新东西
			break;
	if (pItem != RBtree.end())
	{
		if (pItem->inCourt == 0)
		{
			printf("\t\t此车不在停车场内");
			printf("\t\t按回车键继续");
			getchar();
		}
		else
		{
			node newOne;
			newOne = *pItem;
			RBtree.erase(pItem);
			newOne.inCourt = 0;
			time_t now;
			time(&now);
			tm p;
			localtime_s(&p, &now);
			char buf[20] = { 0 };
			snprintf(buf, 20, "%04d:%02d:%02d %02d:%02d", p.tm_year + 1900, p.tm_mon + 1, p.tm_mday, p.tm_hour, p.tm_min);
			newOne.outTime = string(buf);
			hashTablePosition[newOne.carPosition] = 0;
			
			RBtree.insert(newOne);

			printf("\t\t出场车牌：");cout << newOne.numberplate << endl;
			printf("\t\t出场时间：");cout << newOne.outTime << endl;
			printf("\t\t请按时缴费，缴费通知已发送车主手机号\n");
			printf("\t\t请前往计费结账界面核查\n");
			printf("\t\t按回车键继续");
			getchar();
		}
	}
	else
	{
		printf("\t\t此车不在停车场内");
		printf("\t\t按回车键继续");
		getchar();
	}
	return 1;
}

int main()
{
	menu1_1_1();//最直接的，直接进入一级菜单，然后不出来
	return 0;
}	
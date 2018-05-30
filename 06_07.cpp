#include<iostream>
#include<string>
using namespace std;

// 首先建立一个汽车信息抽象的基类
class Auto
{
protected:
	string stypename;            // 类型名
	int npassengers;             // 最大乘客量
	string smanufacturer;        // 制造商
public:
	Auto()
	{
	      stypename = "Auto";            // 类型名
		  npassengers = 0;             // 最大乘客量
		  smanufacturer = "no manufacturer ";        // 制造商
	}
	virtual ~Auto() {};
    // 静态函数TrimLine(),用于整理字符串，去掉串尾部换行字符
	static void TrimLine(char* sbuf)
	{
		while (sbuf != '\0')
		{
			if ((*sbuf == '\r') || (*sbuf == '\n'))
			{
				*sbuf = '\0';
				break;
			}
			sbuf++;
		}
	}
	virtual bool Input(FILE *fp) = 0; // =0 表明是纯虚函数， 含有纯虚函数的class 叫抽象类，不能被实例化
	virtual void Show() = 0;
};

class Car :public Auto
{
public:
	Car()
	{ 
		stypename = "Car";
	}
	//重写虚函数Input()
	bool Input(FILE *fp)
	{
		char sbuf[100];
		fgets(sbuf, 100, fp);      // 读入第一行字符串（包含换行符） 包含制造商信息
		TrimLine(sbuf);            // 去掉换行符
		smanufacturer = sbuf;      //
		fgets(sbuf, 100, fp);
		npassengers = atoi(sbuf);  //    int atoi(string)
 		return true;
	}
	void Show()
	{
		cout << "Style:" << stypename << endl;
		cout << "Manufacturer:" << smanufacturer << endl;
		cout << "npassengers: " << npassengers << endl;
	}
};
class Turck : public Car             // 卡车类继承car类
{
protected:
	float fload;                     //增加最大载重量
public:
	Turck()
	{
		stypename = "Turck";           
		fload = 0;
	}
	bool Input(FILE *fp)
	{
		char sbuf[100];        // 这sbuf 放的位置
		Car::Input(fp);
		fgets(sbuf, 100, fp);
		fload = atof(sbuf);              // float atof(string)
		return true;
	}
	void Show()
	{
		Car::Show();
		cout << "Load = " << fload << endl;
	}
};

class Crane : public Car               // 吊车类
{

protected:
	float fheight;                       //增加最大举重高度
public:
	Crane()
	{
		stypename = "Turck";
		fheight = 0;
	}
	bool Input(FILE *fp)
	{
		char sbuf[100];        // 这sbuf 放的位置
		Car::Input(fp);
		fgets(sbuf, 100, fp);
		fheight = atof(sbuf);   // float atof(string)
		return true;
	}
	void Show()
	{
		Car::Show();
		cout << "Height  = " << fheight << endl;
	}
};
int main()
{
	FILE *stream;
	stream = fopen("atuo.txt", "r");

	if(stream == NULL)
	{
		cout << "can't open the file." << endl;
		system("pause");
		return 0;
	}
	Auto *autos[3];  // 定义对象指针数组，包含三个指针变量元素
	char sbuf[100];
	int index = 0;
	while (fgets(sbuf, 100, stream) != NULL && index < 3)
	{
		if(strncmp(sbuf, "Car", 3) == 0)
		{
			autos[index] = new Car();
		}
		else if (strncmp(sbuf, "Crane", 5) == 0)
		{
			autos[index] = new Crane();
		}
		else if (strncmp(sbuf, "Turck", 5) == 0)
		{
			autos[index] = new Turck();
		}
		else break;
		autos[index]->Input(stream);
		index++;
	}
	fclose(stream);
	for (int i = 0; i < index; i++)
	{
		autos[i] -> Show();
		cout << endl;
		delete autos[i];
	}
	system("pause");
	return 0;
}

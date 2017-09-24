#include <iostream>  
#include "tinyxml.h"  
#include "tinystr.h"  
#include <string>  
#include <windows.h>  
#include <atlstr.h>  
using namespace std;

/*
TiXmlDocument：文档类，它代表了整个xml文件
TiXmlDeclaration：声明类，它表示文件的声明部分
TiXmlComment：注释类，它表示文件的注释部分
TiXmlElement：元素类，它是文件的主要部分，并且支持嵌套结构，一般使用这种结构来分类的存储信息，它可以包含属性类和文本类
TiXmlAttribute/TiXmlAttributeSet：元素属性，它一般嵌套在元素中，用于记录此元素的一些属性
TiXmlText：文本对象，它嵌套在某个元素内部
*/



CString GetAppPath()
{//获取应用程序根目录  
	TCHAR modulePath[MAX_PATH];
	GetModuleFileName(NULL, modulePath, MAX_PATH);
	CString strModulePath(modulePath);
	strModulePath = strModulePath.Left(strModulePath.ReverseFind(_T('\\')));
	return strModulePath;
}

bool CreateXmlFile(string& szFileName)
{//创建xml文件,szFilePath为文件保存的路径,若创建成功返回true,否则false  
	try
	{
		//创建一个XML的文档对象。  
		TiXmlDocument *myDocument = new TiXmlDocument();
		//创建一个根元素并连接。  
		TiXmlElement *RootElement = new TiXmlElement("Library");
		myDocument->LinkEndChild(RootElement);
		//创建一个Book元素并连接。  
		TiXmlElement *LibraryElement = new TiXmlElement("Book");
		RootElement->LinkEndChild(LibraryElement);
		//设置Book元素的属性。  
		LibraryElement->SetAttribute("BookId", "怡宝也飘");
		//创建Title元素、Author、Price、Publisher、Cost元素并连接。  
		TiXmlElement *TitleElement = new TiXmlElement("Title");
		TiXmlElement *AuthorElement = new TiXmlElement("Author");
		TiXmlElement *PriceElement = new TiXmlElement("Price");
		TiXmlElement *PublisherElement = new TiXmlElement("Publisher");
		TiXmlElement *CostElement = new TiXmlElement("Cost");
		LibraryElement->LinkEndChild(TitleElement);
		LibraryElement->LinkEndChild(AuthorElement);
		LibraryElement->LinkEndChild(PriceElement);
		LibraryElement->LinkEndChild(PublisherElement);
		LibraryElement->LinkEndChild(CostElement);


		//设置Title,Author,Price,Publisher,Cost的内容并连接。  
		TiXmlText *TitleContent = new TiXmlText("樊大佬图书");
		TiXmlText *AuthorContent = new TiXmlText("樊大佬");
		TiXmlText *PriceContent = new TiXmlText("50 dollars");
		TiXmlText *PublisherContent = new TiXmlText("樊大佬出版社");
		TiXmlText *CostContent = new TiXmlText("20 dollars");
		TitleElement->LinkEndChild(TitleContent);
		AuthorElement->LinkEndChild(AuthorContent);
		PriceElement->LinkEndChild(PriceContent);
		PublisherElement->LinkEndChild(PublisherContent);
		CostElement->LinkEndChild(CostContent);


		//创建一个Member元素并连接。  
		TiXmlElement *LibrarylElement = new TiXmlElement("Member");
		RootElement->LinkEndChild(LibrarylElement);
		//创建Member的Name,Address元素并连接。  
		TiXmlElement *NameElement = new TiXmlElement("Name");
		TiXmlElement *AddressElement = new TiXmlElement("Address");
		LibrarylElement->LinkEndChild(NameElement);
		LibrarylElement->LinkEndChild(AddressElement);



		//创建Name的FirstName,MiddleName,LastName元素
		TiXmlElement *FirstNameElement = new TiXmlElement("FirstName");
		TiXmlElement *MiddleNameElement = new TiXmlElement("MiddleName");
		TiXmlElement *LastNameElement = new TiXmlElement("LastName");
		NameElement->LinkEndChild(FirstNameElement);
		NameElement->LinkEndChild(MiddleNameElement);
		NameElement->LinkEndChild(LastNameElement);


		//设置FirstName,MiddleName,LastName元素的内容并连接。  
		TiXmlText *FirstNameContent = new TiXmlText("巴拉拉");
		TiXmlText *MiddleNameContent = new TiXmlText("能量");
		TiXmlText *LastNameContent = new TiXmlText("小魔仙全身变");
		FirstNameElement->LinkEndChild(FirstNameContent);
		MiddleNameElement->LinkEndChild(MiddleNameContent);
		LastNameElement->LinkEndChild(LastNameContent);


		//创建Address的HouseNumber,Street,City元素
		TiXmlElement *HouseNumberElement = new TiXmlElement("HouseNumber");
		TiXmlElement *StreetElement = new TiXmlElement("Street");
		TiXmlElement *CityElement = new TiXmlElement("City");
		AddressElement->LinkEndChild(HouseNumberElement);
		AddressElement->LinkEndChild(StreetElement);
		AddressElement->LinkEndChild(CityElement);

		//设置HouseNumber,Street,City元素的内容并连接。  
		TiXmlText *HouseNumberContent = new TiXmlText("421");
		TiXmlText *StreetContent = new TiXmlText("9#");
		TiXmlText *CityContent = new TiXmlText("JinZhou");
		HouseNumberElement->LinkEndChild(HouseNumberContent);
		StreetElement->LinkEndChild(StreetContent);
		CityElement->LinkEndChild(CityContent);


		CString appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = appPath.GetBuffer(0) + seperator + szFileName;
		myDocument->SaveFile(fullPath.c_str());//保存到文件  
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}

bool ReadXmlFile(string& szFileName)
{//读取Xml文件，并遍历  
	try
	{
		CString appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = appPath.GetBuffer(0) + seperator + szFileName;
		//创建一个XML的文档对象。  
		TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
		myDocument->LoadFile();
		//获得根元素，即Library。  
		TiXmlElement *RootElement = myDocument->RootElement();
		//输出根元素名称，即输出Library。  
		cout << RootElement->Value() << endl;
		//获得第一个Book节点,Member节点。  
		TiXmlElement *Book = RootElement->FirstChildElement();
		TiXmlElement *Member =Book->NextSiblingElement();
		//获得Member的两个Name,Address结点
		TiXmlElement *Name1Element = Member->FirstChildElement();
		TiXmlElement *AddressElement = Name1Element->NextSiblingElement();
		//获得第一个Book的Title,Author,Price,Publisher,Cost和ID属性。  
		TiXmlElement *TitleElement =Book->FirstChildElement();
		TiXmlElement *AuthorElement = TitleElement->NextSiblingElement();
		TiXmlElement *PriceElement = AuthorElement->NextSiblingElement();
		TiXmlElement *PublisherElement = PriceElement->NextSiblingElement();
		TiXmlElement *CostElement = PublisherElement->NextSiblingElement();
		TiXmlAttribute *IDAttribute = Book->FirstAttribute();

		
		//获得Name的F,M,L
		TiXmlElement *FirstNameElement = Name1Element->FirstChildElement();
		TiXmlElement *MiddleNameElement = FirstNameElement->NextSiblingElement();
		TiXmlElement *LastNameElement = MiddleNameElement->NextSiblingElement();
		//获得Address的HouseNumber,Street,City
		TiXmlElement *HouseNumberElement = AddressElement->FirstChildElement();
		TiXmlElement *StreetElement = HouseNumberElement->NextSiblingElement();
		TiXmlElement *CityElement = StreetElement->NextSiblingElement();


		//输出第一个Book的内容
		cout << TitleElement->FirstChild()->Value() << endl;
		cout << AuthorElement->FirstChild()->Value() << endl;
		cout << PriceElement->FirstChild()->Value() << endl;
		cout << PublisherElement->FirstChild()->Value() << endl;
		cout << CostElement->FirstChild()->Value() << endl;
		cout << IDAttribute->Value() << endl;

		//输出第一个Name的内容
		cout << FirstNameElement->FirstChild()->Value() << endl;
		cout << MiddleNameElement->FirstChild()->Value() << endl;
		cout << LastNameElement->FirstChild()->Value() << endl;
		//输出Address内容
		cout << HouseNumberElement->FirstChild()->Value() << endl;
		cout << StreetElement->FirstChild()->Value() << endl;
		cout << CityElement->FirstChild()->Value() << endl;
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}
int main()
{
	string fileName = "info.xml";
	CreateXmlFile(fileName);
	ReadXmlFile(fileName);
	getchar();
	return 0;
}
#include <iostream>  
#include "tinyxml.h"  
#include "tinystr.h"  
#include <string>  
#include <windows.h>  
#include <atlstr.h>  
using namespace std;

/*
TiXmlDocument���ĵ��࣬������������xml�ļ�
TiXmlDeclaration�������࣬����ʾ�ļ�����������
TiXmlComment��ע���࣬����ʾ�ļ���ע�Ͳ���
TiXmlElement��Ԫ���࣬�����ļ�����Ҫ���֣�����֧��Ƕ�׽ṹ��һ��ʹ�����ֽṹ������Ĵ洢��Ϣ�������԰�����������ı���
TiXmlAttribute/TiXmlAttributeSet��Ԫ�����ԣ���һ��Ƕ����Ԫ���У����ڼ�¼��Ԫ�ص�һЩ����
TiXmlText���ı�������Ƕ����ĳ��Ԫ���ڲ�
*/



CString GetAppPath()
{//��ȡӦ�ó����Ŀ¼  
	TCHAR modulePath[MAX_PATH];
	GetModuleFileName(NULL, modulePath, MAX_PATH);
	CString strModulePath(modulePath);
	strModulePath = strModulePath.Left(strModulePath.ReverseFind(_T('\\')));
	return strModulePath;
}

bool CreateXmlFile(string& szFileName)
{//����xml�ļ�,szFilePathΪ�ļ������·��,�������ɹ�����true,����false  
	try
	{
		//����һ��XML���ĵ�����  
		TiXmlDocument *myDocument = new TiXmlDocument();
		//����һ����Ԫ�ز����ӡ�  
		TiXmlElement *RootElement = new TiXmlElement("Library");
		myDocument->LinkEndChild(RootElement);
		//����һ��BookԪ�ز����ӡ�  
		TiXmlElement *LibraryElement = new TiXmlElement("Book");
		RootElement->LinkEndChild(LibraryElement);
		//����BookԪ�ص����ԡ�  
		LibraryElement->SetAttribute("BookId", "����ҲƮ");
		//����TitleԪ�ء�Author��Price��Publisher��CostԪ�ز����ӡ�  
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


		//����Title,Author,Price,Publisher,Cost�����ݲ����ӡ�  
		TiXmlText *TitleContent = new TiXmlText("������ͼ��");
		TiXmlText *AuthorContent = new TiXmlText("������");
		TiXmlText *PriceContent = new TiXmlText("50 dollars");
		TiXmlText *PublisherContent = new TiXmlText("�����г�����");
		TiXmlText *CostContent = new TiXmlText("20 dollars");
		TitleElement->LinkEndChild(TitleContent);
		AuthorElement->LinkEndChild(AuthorContent);
		PriceElement->LinkEndChild(PriceContent);
		PublisherElement->LinkEndChild(PublisherContent);
		CostElement->LinkEndChild(CostContent);


		//����һ��MemberԪ�ز����ӡ�  
		TiXmlElement *LibrarylElement = new TiXmlElement("Member");
		RootElement->LinkEndChild(LibrarylElement);
		//����Member��Name,AddressԪ�ز����ӡ�  
		TiXmlElement *NameElement = new TiXmlElement("Name");
		TiXmlElement *AddressElement = new TiXmlElement("Address");
		LibrarylElement->LinkEndChild(NameElement);
		LibrarylElement->LinkEndChild(AddressElement);



		//����Name��FirstName,MiddleName,LastNameԪ��
		TiXmlElement *FirstNameElement = new TiXmlElement("FirstName");
		TiXmlElement *MiddleNameElement = new TiXmlElement("MiddleName");
		TiXmlElement *LastNameElement = new TiXmlElement("LastName");
		NameElement->LinkEndChild(FirstNameElement);
		NameElement->LinkEndChild(MiddleNameElement);
		NameElement->LinkEndChild(LastNameElement);


		//����FirstName,MiddleName,LastNameԪ�ص����ݲ����ӡ�  
		TiXmlText *FirstNameContent = new TiXmlText("������");
		TiXmlText *MiddleNameContent = new TiXmlText("����");
		TiXmlText *LastNameContent = new TiXmlText("Сħ��ȫ���");
		FirstNameElement->LinkEndChild(FirstNameContent);
		MiddleNameElement->LinkEndChild(MiddleNameContent);
		LastNameElement->LinkEndChild(LastNameContent);


		//����Address��HouseNumber,Street,CityԪ��
		TiXmlElement *HouseNumberElement = new TiXmlElement("HouseNumber");
		TiXmlElement *StreetElement = new TiXmlElement("Street");
		TiXmlElement *CityElement = new TiXmlElement("City");
		AddressElement->LinkEndChild(HouseNumberElement);
		AddressElement->LinkEndChild(StreetElement);
		AddressElement->LinkEndChild(CityElement);

		//����HouseNumber,Street,CityԪ�ص����ݲ����ӡ�  
		TiXmlText *HouseNumberContent = new TiXmlText("421");
		TiXmlText *StreetContent = new TiXmlText("9#");
		TiXmlText *CityContent = new TiXmlText("JinZhou");
		HouseNumberElement->LinkEndChild(HouseNumberContent);
		StreetElement->LinkEndChild(StreetContent);
		CityElement->LinkEndChild(CityContent);


		CString appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = appPath.GetBuffer(0) + seperator + szFileName;
		myDocument->SaveFile(fullPath.c_str());//���浽�ļ�  
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}

bool ReadXmlFile(string& szFileName)
{//��ȡXml�ļ���������  
	try
	{
		CString appPath = GetAppPath();
		string seperator = "\\";
		string fullPath = appPath.GetBuffer(0) + seperator + szFileName;
		//����һ��XML���ĵ�����  
		TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
		myDocument->LoadFile();
		//��ø�Ԫ�أ���Library��  
		TiXmlElement *RootElement = myDocument->RootElement();
		//�����Ԫ�����ƣ������Library��  
		cout << RootElement->Value() << endl;
		//��õ�һ��Book�ڵ�,Member�ڵ㡣  
		TiXmlElement *Book = RootElement->FirstChildElement();
		TiXmlElement *Member =Book->NextSiblingElement();
		//���Member������Name,Address���
		TiXmlElement *Name1Element = Member->FirstChildElement();
		TiXmlElement *AddressElement = Name1Element->NextSiblingElement();
		//��õ�һ��Book��Title,Author,Price,Publisher,Cost��ID���ԡ�  
		TiXmlElement *TitleElement =Book->FirstChildElement();
		TiXmlElement *AuthorElement = TitleElement->NextSiblingElement();
		TiXmlElement *PriceElement = AuthorElement->NextSiblingElement();
		TiXmlElement *PublisherElement = PriceElement->NextSiblingElement();
		TiXmlElement *CostElement = PublisherElement->NextSiblingElement();
		TiXmlAttribute *IDAttribute = Book->FirstAttribute();

		
		//���Name��F,M,L
		TiXmlElement *FirstNameElement = Name1Element->FirstChildElement();
		TiXmlElement *MiddleNameElement = FirstNameElement->NextSiblingElement();
		TiXmlElement *LastNameElement = MiddleNameElement->NextSiblingElement();
		//���Address��HouseNumber,Street,City
		TiXmlElement *HouseNumberElement = AddressElement->FirstChildElement();
		TiXmlElement *StreetElement = HouseNumberElement->NextSiblingElement();
		TiXmlElement *CityElement = StreetElement->NextSiblingElement();


		//�����һ��Book������
		cout << TitleElement->FirstChild()->Value() << endl;
		cout << AuthorElement->FirstChild()->Value() << endl;
		cout << PriceElement->FirstChild()->Value() << endl;
		cout << PublisherElement->FirstChild()->Value() << endl;
		cout << CostElement->FirstChild()->Value() << endl;
		cout << IDAttribute->Value() << endl;

		//�����һ��Name������
		cout << FirstNameElement->FirstChild()->Value() << endl;
		cout << MiddleNameElement->FirstChild()->Value() << endl;
		cout << LastNameElement->FirstChild()->Value() << endl;
		//���Address����
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
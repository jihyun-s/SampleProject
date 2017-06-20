#include <iostream>
using namespace std;

class Singleton{

private:
	Singleton(){}
	~Singleton(){}
	static Singleton* pInstance;
public:
	static Singleton* getInstance()
	{
		if (!pInstance)
			pInstance = new Singleton;

		return pInstance;
	}

	void deleteInstance()
	{
		if (pInstance)
		{
			delete pInstance;
			pInstance = NULL;
		}
	}

	void Display()
	{
		printf("DISPLAY");
	}
};

Singleton* Singleton::pInstance = NULL;

int main()
{
	Singleton* Instance = Singleton::getInstance();
	Instance->Display();

	return 0;
}





/*
#include <stdio.h>

class Singleton{

private:
	Singleton(){}
	~Singleton(){}
	static Singleton* pInstance;

public:
	static Singleton* getInstance()
	{
		if (!pInstance)
			pInstance = new Singleton();
		return pInstance;
	}

	static void deleteinstance()
	{
		if (pInstance)
		{
			delete pInstance;
			pInstance = NULL;
		}
			
	}

	void Singleton::Display()
	{
		printf("Singleton\n");
	}

};

Singleton* Singleton::pInstance = NULL;
int main()
{
	Singleton* instance = Singleton::getInstance();
	instance->Display();

	return 0;
}
*/
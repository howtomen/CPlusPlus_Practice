#include "DanielLog.h"
#include <iostream>
#include <time.h>

using namespace std;

void Testing(){
	logger log;
	int randnum;
	srand(time(NULL));
	randnum = rand() % 10+1;
	if (randnum < 5)
	{
		log.LogWrite(__LINE__ -2 , __FUNCTION__, "A random number has been chosen", "The num generator has chosen a number less than 5.");
	}
	else
	{
		log.LogWrite(__LINE__ -7 , __FUNCTION__, "A random number has been chosen", "The num generator has chosen a number greater than 5.");
	}
	cout << randnum << endl;
}

int main()
{
	
	logger log;

	ifstream testFail("Fake_filezz.txt");
	if (testFail.fail()) {
		log.LogWrite(__LINE__ -2 , __FUNCTION__, "File has failed to open", "File may not exist or may be corrupt.");
	}
	else {
		log.LogWrite(__LINE__ - 5, __FUNCTION__, "File opened succesfully", "Good Job"); 
	}
	
	testFail.close();

	for (int i = 0; i < 10; ++i)
	{
		Testing();
		log.flush();
	}
	

	system("pause");

}

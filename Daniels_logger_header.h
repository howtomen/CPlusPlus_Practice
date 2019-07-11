#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

class logger
{
private:
	
	ofstream LogFile;
	const time_t logTime= time(0);
public:
	logger()
	{
		LogFile.open("log.txt", ofstream::app);
	}
	~logger(){
		LogFile.close();
	}
	void LogWrite(int line, string Func, string errorType, string description){
	LogFile << asctime(localtime(&logTime)) << line << ": " << Func << endl << "Error type: " <<errorType << endl << description << endl << endl;
	LogFile.close();

	}
	void flush(){
		LogFile.flush();
	}
};

	
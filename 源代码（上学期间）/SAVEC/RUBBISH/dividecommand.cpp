// dividecommand.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "stdio.h"
#include "iostream.h"
#include "string.h"
#include "conio.h"

enum bool{false, true};
#define MAX_PARAMETER 50
#define MAX_COMMANDLEN 128

class CommandDivideInfo
{
//Attributes
private:
	//dim[0] is source command, next is divide result
	char* CommandInfo[MAX_PARAMETER];
	char CommandLine[MAX_COMMANDLEN];
	int NumOfParameter;
//Operations
public:
	CommandDivideInfo()
	{
		//-1:is no command in
		//0:only command in and no parameter(because not to use DivideCommand()
		//??+1(>0):command has ?? parameter(include main command)
		NumOfParameter = -1;
		for(int i = 0; i < MAX_PARAMETER; i++)
			CommandInfo[i] = 0;
	}
	~CommandDivideInfo()
	{
		for(int i = 0; i < NumOfParameter; i++)
			delete[] CommandInfo[i];
	}
	//input command line that is user inputed
	bool InputCommand(void)
	{
		ClearCommandInfo();
		char InputChar;
		int pos = 0;
		do
		{
			InputChar = getch();
			printf("%c", InputChar);
			CommandLine[pos] = InputChar;
			pos++;
		}
		while(InputChar != '\r');
		CommandLine[pos - 1] = '\0';
		printf("\n");
		NumOfParameter = 0;
		return true;
	}
	//get source command and save to CommandInfo[0]
	bool GetCommand(char* CommandIn)
	{
		ClearCommandInfo();
		if(CommandIn == 0)
			return false;
		if(strcpy(CommandLine, CommandIn) == false)
		{
			CommandLine[0] = '\0';
			return false;
		}
		NumOfParameter = 0;
		return true;
	}
	//output the CommandInfo[] to Parameter[] which given by user
	bool GetParameter(char* Parameter[], int& ParameterNumber)
	{
		if(Parameter == 0 || NumOfParameter <= 0 || CommandInfo == 0)
			return false;
		int parlen;
		for(int i = 0; i < NumOfParameter; i++)
		{
			parlen = strlen(CommandInfo[i]) + 1;
			Parameter[i] = new char[parlen];
			strcpy(Parameter[i], CommandInfo[i]);
		}
		ParameterNumber = NumOfParameter;
		return true;
	}
//protected:
	//divide command line to parts
	bool DivideCommand(void)
	{
		if(NumOfParameter == -1 || CommandLine == 0)
			return false;
		int pos = 0;
		int pin = 0;
		bool DivideFlag = true;
		NumOfParameter = 1;
		for(pos = 0; pos < strlen(CommandLine); pos++)
		{
			if(CommandLine[pos] == ' ' || CommandLine[pos] == '\t')
			{
				if(DivideFlag == false)
				{
					CommandInfo[NumOfParameter - 1][pin] = '\0';
					pin = 0;
					NumOfParameter++;
					DivideFlag = true;
				}
				continue;
			}
			else
			{
				if(DivideFlag == true)
					CommandInfo[NumOfParameter - 1] = new char[MAX_COMMANDLEN];
				DivideFlag = false;
				CommandInfo[NumOfParameter - 1][pin] = CommandLine[pos];
				pin++;
			}
		}
		if(DivideFlag == false)
			CommandInfo[NumOfParameter - 1][pin] = '\0';
		else
			NumOfParameter--;
		//append '\0' at the end of CommandInfo[]
		CommandInfo[NumOfParameter] = new char;
		CommandInfo[NumOfParameter][0] = '\0';
		NumOfParameter++;
		return true;
	}
	//clear CommandInfo[] to input new command
	void ClearCommandInfo(void)
	{
		if(NumOfParameter < 0)
			return;
		CommandLine[0] = '\0';
		for(int i = 0; i <= NumOfParameter; i++)
			delete[] CommandInfo[i];
		NumOfParameter = -1;
	}
public:
	//print input command and divided parameter from CommandInfo[]
	//it is used for test result
	void PrintCommandInfo(void)
	{
		if(NumOfParameter == -1)
		{
			printf("No command input.\n");
			return;
		}
		if(NumOfParameter == 0)
			printf("Only input command and not use DivideCommand().\n");
		printf("%s\n",CommandLine);
		for(int i = 0; i < NumOfParameter; i++)
			printf("%s\n", CommandInfo[i]);
	}
};

int main(int argc, char* argv[])
{
	printf("Input command to test:");
	CommandDivideInfo OutputInfo;
	char in[50];
	scanf("%s", in);
//	OutputInfo.InputCommand();
	OutputInfo.GetCommand(in);
	OutputInfo.DivideCommand();
	OutputInfo.PrintCommandInfo();
	printf("test GetParameter()\n");
	char* a[MAX_PARAMETER];
	int n;
	OutputInfo.GetParameter(a, n);
	printf("number of parameter has get: %d\n", n);
	int i = 0;
	while(1)
	{
		printf("%s\n", a[i]);
		i++;
		if(i > n - 1)
			break;
	}
	return 0;
}

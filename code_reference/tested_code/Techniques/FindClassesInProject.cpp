// TT.cpp : Defines the entry point for the console application.
//
/* -><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><
		
		  Put the name and fullpath in of the dsp file in the
		  global variable strDspFilePath. The program then 
		  creates three files in c:\temp directory
		  1. Resultsh.txt	: names and path of header files relative to 
							  the dir where the dsp file is located
		  2. Resultsc.txt	: cpp files
		  3. ClassNames.txt : Names of all the classes in the project

-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><*/


#include "stdafx.h"
#include <fstream>
#include <string>

using namespace std;

// Full path to  Dsp file
string strDspFilePath = "c:\\RtoDev\\bl\\bl.dsp";

bool ParseDspFile()
{
	ifstream from (strDspFilePath.c_str());
	if (!from) return false;

	ofstream toC ("c:\\temp\\Resultsc.txt");
	if (!toC) return false;

	ofstream toH ("c:\\temp\\Resultsh.txt");
	if (!toH) return false;


	char ch = 0;
	while (from >> ch)
	{
		if (ch == '#' || ch == '!')
		{
			while(from.get(ch) && ch != '\n');
		}
		else
		{
			from.putback(ch);
			string strWord;
			getline(from, strWord);
				
			if (!strWord.compare(0,6,"SOURCE"))
			{
				if (strWord[strWord.length() -1] == 'h')
					toH<< strWord.substr(8) << '\n';
				else if (strWord.substr(strWord.length() -3) == "cpp")
					toC << strWord.substr(8) << '\n';
			}
		}
	}
	return true;
}

// continue searching until a token is found i.e., something
// that bigins with alpha and contains only alphanum
char GetToken(ifstream& from, string& strWord)
{
	char ch;
	while (from >> ch)
	{
		if (isalpha(ch))
		{
			strWord = ch;
			while (from.get(ch) && (isalnum(ch) || ch == '_'))
				strWord.append(1,ch);
			
			// The above loop will stop on a space 
			// but a space does not say anything about the nature of the
			// previous token.
			// therefore we check the next non-space char to help the 
			// calling routine in making a decision 
			if (isspace(ch))
			{
				if (!(from >> ch)) return 0;
				from.putback(ch);
				return ch;
			}
			
		}
		
		// ignore comments
		else if (ch == '/')
		{
			from.get(ch);
			switch (ch)
			{
			case '/' :	/* ignore upto end of line */
				while(from.get(ch) && ch != '\n'); 
				break;
		
			case '*' :	/* ignore upto next */
				while (from)
				{
					while(from>>ch && ch != '*');	// ignore upto next '*'
					if (from>>ch && ch != '/')		// if the char after '*' 
						from.putback(ch);			// is '/', comment ended
					else break;						// otherwise putback,
				}									// because it can be '*'
				
			}
		}
		
	}
	return 0;
}

// after the name class or struct is found this fn finds the name
// of the class 
bool ClassName(ifstream& from, string& strName)
{
	char ch;
	string string_value;
	while ( ch = GetToken(from, string_value))
	{
		switch (ch)
		{
		case '{' : 
		case ':' : string_value.swap(strName); return true;
		case ';' : 
		case '>' : return false;
		}
	}
	return false;
}



// find the token "class" or "struct" in file
void ExtractClasses(const string& strFileName, ofstream& to)
{
	ifstream from( strFileName.c_str());
	if (!from ) return;
	
	string strWord;
	while (GetToken(from, strWord))
	{
		if (strWord != "struct" && strWord != "class")
			continue;
		
		if (ClassName(from,strWord))
		{
			to << strWord << '\n';
			char ch;
			int nCount = 0;
			while (from.get(ch))
			{
				if (ch == '{' ) nCount++;
				if (ch == '}' ) if ((nCount--) == 0) break;
			}
		}
	}
}




int main(int argc, char* argv[])
{
	if (!ParseDspFile())
		return 0;

	ifstream namesFile("c:\\temp\\Resultsh.txt");

	ofstream to ("c:\\temp\\ClassNames.txt");
	if (!to ) return 0;

	string strDir = strDspFilePath.substr(0,strDspFilePath.rfind("\\"));
	string strLine;
	while ( getline (namesFile, strLine))
		ExtractClasses(strDir + strLine, to);
	
	return 0;
}

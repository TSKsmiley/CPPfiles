// CPPfiles.cpp : Defines the entry point for the application.
//

#include "CPPfiles.h"
#include "iostream"
#include "fstream"
#include "string"
#include "sstream"

using namespace std;

string readFile(string file) {
	string line;
	ostringstream result;
	
	ifstream myFile (file);

	if (myFile.is_open()){
		while (getline(myFile,line))
		{
			result << line << endl;
		}
		myFile.close();
	}
	else return "";
	return result.str();
}

int main() {
	string content = readFile("test.txt");
	ostringstream newContent;

	int prevCount = 1;

	cout << content.length();

	for (size_t i = 0; i < content.length()-1; i++)
	{
		if (content[i] != content[i+1] && content[i] == '/') newContent << '/';
		else if (content[i]==content[i+1]) prevCount++;
		else if (prevCount > 1 && content[i]!=content[i+1] ) {
			newContent << '/' << prevCount << '/' << content[i];
			prevCount = 1;
		}
		else {
			newContent << content[i];
		}
	}
	cout << newContent.str() << endl;
	ofstream outFile;
	outFile.open("out.txt");
	outFile << newContent.str();
	return 0;
}



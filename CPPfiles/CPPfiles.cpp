// CPPfiles.cpp : Defines the entry point for the application.
//

#include "CPPfiles.h"
#include "iostream"
#include "fstream"
#include "string"
#include "sstream"
#include "cctype"

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

void writeFile(string file, string fileContent) {
	ofstream myFile;
	myFile.open(file);
	myFile << fileContent;
	myFile.close();
}

string encode(string input) {
	ostringstream newContent;

	int prevCount = 1;

	for (size_t i = 0; i < input.length()-1; i++)
	{
		if (input[i] != input[i+1] && input[i] == '/' && prevCount == 1) newContent << "//";
		else if (input[i]==input[i+1]) prevCount++;
		else if (prevCount > 1 && input[i]!=input[i+1] ) {
			newContent << '/' << prevCount << '/' << input[i];
			prevCount = 1;
			
		}
		else {
			newContent << input[i];
		}
	}

	return newContent.str();
}

string decode(string input) {
	ostringstream newContent;

	for (size_t i = 0; i < input.length()-1; i++)
	{
		if (input[i] == '/' && input[i+1] == '/') {
			newContent << '/';
			i++;
		}
		else if (input[i] == '/' && isdigit(input[i+1])){
			// find how many chars long the int is
			int endPos = input.find('/',i+1);
			// get the number
			int charAmnt = stoi(input.substr(i+1,endPos-1));
			// add the correct amount of chars to the output file
			for (size_t j = 0; j < charAmnt; j++)
			{
				newContent << input[endPos+1];
			}

			i = endPos+1;
		}
		else {
			newContent << input[i];
		}
	}

	newContent << input[input.length()-1];

	return newContent.str();
}

string request(string msg){

	string res;

	cout << msg;
	cin >> res;
	
	return res;
}

int main() {

	string content = readFile(request("input file:"));

	cout << "ORIGINAL DATA: " << content << endl << endl;

	if (request("encode(1) or decode(2)") == "1"){
		writeFile(request("output file name:").append(".ctxt"), encode(content));
	}
	else {
		writeFile(request("output file name:").append(".txt"), decode(content));
	}
	return 0;
}



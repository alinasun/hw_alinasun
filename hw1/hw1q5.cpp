#include <iostream>
#include <sstream>
#include <cstring> 
#include <iostream>
#include <fstream>
#include <deque>

using namespace std;
int main(int argc, char* argv[]){
	if (argc != 2){
		cerr << "Wrong number of arguments, please try again";
	}
	ifstream hwFile;
	hwFile.open(argv[1]);

	int length = -1;
	hwFile >> length; 
	string* list = new string[length];

	string word;
	int counter = 0;

	while(!hwFile.eof()){
		hwFile >> word;
		list[counter] = word;
		counter++;
	}

	int match = 0;

	for(int i = counter - 1; i >= 0; i--){
		//cout << "inside for loop" << endl;
		cout << list[i] << endl;
	}

	hwFile.close();

	delete [] list;

}
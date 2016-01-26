#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]); 

  int floors;
  int *floorsizes;
  string ***trojans;
  string curr;

  input >> floors; // takes in the number of floors, formatted correctly
  trojans = new string**[floors];

  int ** numberPoss = new int*[floors];

  //you will need to keep track of how many people are on each floor.
  floorsizes = new int[floors];
  bool *occupied = new bool[floors];

  for(int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
	  occupied[i] = false;
  }

  getline(input, curr);

  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;
	  if(curr == "MOVEIN") {
		  int i,k;
		  ss >> i;
		  ss >> k;
		  if (ss.fail()) {
			output << "Error - incorrect command" << endl;
		  }
		  else if(floorsizes[i] != 0){
		  	output << "Error - floor " << i << " is not empty" << endl;
		  }//floor occupied
		  else if(i < 0 || i > floors){
		  	output << "Error - floor " << i << " does not exist" << endl;
		  }//no floor exists
		  else {
		  	numberPoss[i] = new int[k];
		  	trojans[i] = new string*[k];
		  	for(int j = 0; j < k; j++){
		  		trojans[i][j] = NULL;
		  		//dynamically allocating number of students for floor i
		  		numberPoss[i][j] = -1;
		  	}
		  	floorsizes[i] = k;
		  	occupied[i] = true;
		  }//making an array for the students woo
	  }

	  else if (curr == "OBTAIN") {
	  	int i, j, k;
	  	ss >> i;
	  	ss >> j;
	  	ss >> k;
	  	
	  	if(0 <= j && j < floorsizes[i]){
	  		numberPoss[i][j] = k;
	  	}

	  	//numberPoss[i][j] = k;
	  	//string possession;
	  	if(ss.fail()){
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else if(i < 0 || i > floors){
	  		output << "Error - floor " << i << " does not exist" << endl;
	  	}
	  	else if(j < 0 || j >= floorsizes[i]){
	  		output << "Error - student " << j << " doesn't exist" << endl;
	  	}//no student
	  	else if(numberPoss[i][j] == -1){
	  		output << "Error - student " << j << " already has possessions" << endl;
	  	}//student already has possessions
	  	else {
	  		string possession;
	  		numberPoss[i][j] = k;
	  		trojans[i][j] = new string[k];
	  		for(int n = 0; n < k; n++){
	  			//trojans[i][j] = new string[n];
	  			ss >> possession;
	  			trojans[i][j][n] = possession;
	  			//output << trojans[i][j][n] << endl;
	  		} //
	  		/*
	  		for(int n = 0; n < k; n++){
	  			ss >> possession;
	  			trojans[i][j][n] = possession;
	  		}
	  		*/
	  		//numberPoss[i][j] = k;
	  	}
	  }

	  else if (curr == "MOVEOUT") {
	  	int i;
	  	ss >> i;
	  	if(ss.fail()){
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else if(i < 0 || i > floors){
	  		output << "Error - floor " << i << " does not exist" << endl;
	  	}//no floor exists
	  	else if(occupied[i] == false){
	  		output << "Error - floor " << i << " does not have students" << endl;
	  	}//no students live on floor
	  	else {
	  		for(int j = 0; j < floorsizes[i]; j++){
	  			/*
	  			for(int k = 0; k < numberPoss[i][j]; k++){
	  				delete[] trojans[i][j][k];
	  				trojans[i][j][k] = NULL;
	  			}
	  			*/
	  			
	  			//delete[] trojans[i][j];
	  			delete[] trojans[i][j]; // deletes students' poss?
	  			trojans[i][j] = NULL;
	  			numberPoss[i][j] = -1;
	  			floorsizes[i] = 0;

	  			for(int n = 0; n < floorsizes[i]; n++){
	  				delete [] trojans[n];
	  				trojans[n] = NULL;
	  			}
	  		}
	  		occupied[i] = false;
	  	}
	  }

	  else if (curr == "OUTPUT") {
	  	int i, j;
	  	ss >> i;
	  	ss >> j;
	  	if(ss.fail()){
	  		output << "Error - wrong command" << endl;
	  	}
	  	else if(j <= 0 || j > floorsizes[i]){
	  		output << "Error - no student " << j << " on floor " << i << endl;
	  	}//no student j on floor i
	  	else if(numberPoss[i][j] == -1){
	  		output << "Error - student " << j << " has no possessions" << endl;
	  	}//no possessions of student j
	  	else {
	  		int size = numberPoss[i][j];
	  		for(int n = 0; n < size; n++){
	  			output << trojans[i][j][n] << endl;
	  		}
	  	}
	  }
	  else {
	  	return 0;
	  }
  }
  
  for(int i = 0; i < floors; i++){
  		for(int j = 0; j < floorsizes[i]; j++){
  			if(trojans[i][j] != NULL){
  				delete [] trojans[i][j];
  			}
  		}
  		if(trojans[i] != NULL){
  			delete [] trojans[i];
  		}
  }
  delete[] trojans;  	
  for(int i = 0; i < floors; i++){ 
  		delete [] numberPoss[i];
  }
  delete[] numberPoss;
  delete[] occupied;
  delete[] floorsizes;
  

  output.close();
  return 0;
}

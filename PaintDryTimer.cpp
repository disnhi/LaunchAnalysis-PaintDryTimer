//Computes and tracks the time for batches of things. One thing takes 'n' seconds to dry, where 'n' is the surface area of the thing (assume a sphere in cm). An entire batch dries at once.

#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;


struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

void printMenu() { 
  cout<<"Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
}

long long int get_time_remaining(DryingSnapShot dss){
  time_t end = time(0); 
  long long int temp = end - dss.startTime; //calculates the elapsed time
  long long int timeRemain = dss.timeToDry->GetTimeCodeAsSeconds() - temp; //calculates how much time is left after elapsed time is accounted for
  return timeRemain;
}

//calculates the surface area, given the radius
double get_sphere_sa(double rad){
  double time = 4 * pow(rad,2) * M_PI; 
  return time; 
}

//creates a new TimeCode object on the heap
TimeCode * compute_time_code(double surfaceArea){
  TimeCode *tc = new TimeCode(0,0,surfaceArea); 
  return tc;
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);

	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;
}

int main(){

  char userOption; //tracks user input
  double radius;
  double n; //surface areaa and time it takes each thing to dry
  int temp = 0; //batch number
  vector<DryingSnapShot> data; //for all the time of the batches
  DryingSnapShot currentBatch; //creates a new struct everytime a new batch is initiated
  
  printMenu();
  
  do { //continues to ask the user for an input option until they enter 'q' or 'Q' for quit.
    cin>>userOption;
    switch(userOption)
      {
      case 'A':
      case 'a':
	cout<<"Enter radius: ";
	cin>>radius;
	n = get_sphere_sa(radius); //calculates the surface area, which translates to how long it takes the thing to dry
	temp = rand(); //creates a random batch number
        currentBatch.name = to_string(temp);
	currentBatch.startTime = time(0); //captures the start time
	currentBatch.timeToDry = compute_time_code(n); //turns time it takes to dry to a TimeCode object
	data.push_back(currentBatch);
	cout<<"Batch-"<<temp<<" will dry in: " <<currentBatch.timeToDry->ToString()<<endl;
	printMenu();
	break;
      case 'V':
      case 'v':
	//iterates through 'data', which contains a list of all active batches
	//and calls the time remaining function to see where to deallocate the
	//batch or to print out how much time is remainging.
	for(size_t i = 0; i<data.size(); i++) {
	  long long int remaining = get_time_remaining(data.at(i));
	  if(remaining<=0) {
	    delete data.at(i).timeToDry; //deletes the timeToDry from the heap
	    data.erase(data.begin()+i); //deletes the batch that is done from the list
	  }
	  else {
	    TimeCode tc = TimeCode(0,0,remaining);
	    cout<<"Batch-"<<data.at(i).name<<" (takes "<<data.at(i).timeToDry->ToString()<<" to dry) time remaining: "<<tc.ToString()<<endl;
	  }
	}
	cout<<data.size()<<" items being tracked."<<endl;
	printMenu();
	break;
      case 'Q':
      case 'q':
	cout<<endl<<"Thanks for watching stuff dry! Have a great day!"<<endl;
	break;
      default:
	cout<<"Sorry you entered an invalid option. Try again!"<<endl;
	printMenu();
	break;
      }
  }
  while((userOption != 'Q') && (userOption!= 'q')); //keeps the loop going

  tests();
  return 0;
}

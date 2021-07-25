
#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;


struct DryingSnapShot {
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

void printMenu() {
  cout<<"Choose an option:(A)dd,\t(V)iew Current Items,\t(Q)uit: ";
}

long long int get_time_remaining(DryingSnapShot dss){
  time_t end = time(0);
  //int temp = (dss.timeToDry->GetTimeCodeAsSeconds() - (end + dss.startTime));
  long long int temp = end - dss.startTime;
  long long int timeRemain = dss.timeToDry->GetTimeCodeAsSeconds() - temp;
  return timeRemain;
}


string drying_snap_shot_to_string(DryingSnapShot dss){
  string temp = dss.timeToDry->ToString();
  return temp;
}


double get_sphere_sa(double rad){
  double time = 4 * pow(rad,2) * M_PI;
  return time; 
}


TimeCode * compute_time_code(double surfaceArea){
  TimeCode *tc = new TimeCode(0,0,surfaceArea);
  cout<<"TIME TO DRYYYYYY: "<<tc->ToString()<<endl;
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

  time_t end;
  char userOption;
  double radius;
  double surfaceArea;
  int temp = 0;
  TimeCode currentTime = TimeCode(0,0,0);
  vector<int> Batches;
  vector<int> Times;
  vector<DryingSnapShot> data; //for all the time of the batches
  DryingSnapShot currentBatch;
  printMenu();

  do {
    cin>>userOption;
    switch(userOption)
      {
      case 'A':
      case 'a':
	cout<<"Enter radius: ";
	cin>>radius;
	surfaceArea = get_sphere_sa(radius);
	temp = rand(); //creates a random batch number
        currentBatch.name = to_string(temp);
	currentBatch.startTime = time(0);
	currentBatch.timeToDry = compute_time_code(surfaceArea);
	data.push_back(currentBatch);
	cout<<"Batch-"<<temp<<" will dry in: " <<currentBatch.timeToDry->ToString()<<endl;
	printMenu();
	break;
      case 'V':
      case 'v':
	end = time(0);
	for(int i = 0; i<data.size(); i++) {
	  long long int temp = get_time_remaining(data.at(i));
	  cout<<i<<" -> "<<temp<<endl;
	}
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
  while((userOption != 'Q') && (userOption!= 'q'));
  
	//tests();
 return 0;
}

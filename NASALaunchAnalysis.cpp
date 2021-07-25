
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "TimeCode.h"

using namespace std;

bool isInside(string & input) { //checks to see if the string contains the string UTC, if it doesn't, it means there isnt a time recorded, thus returning false
  string key = "UTC";
  int yes = input.find(key);
  if(yes != string::npos){
    return true;
  }
  else {
    return false;
  }
}

void readFile()
{
  string data; 
  string justTheTime1; 
  string justTheTime2;
  string justTheTime3; 
  string justTheTime4;
  string temp1; //correlates to the hours component in the line
  string temp2; //correlates to the minutes component in the line
  
  int hours;
  int minutes;
  int position;
  unsigned long long int secs = 0;
  int n = 0; //keeps track of how many timecodes are being recorded
  
  ifstream myFile;

  myFile.open("Space_Corrected.csv");
  
  if(!myFile.is_open()) {
    cout<<"Could not open the file!"<<endl;
    exit(1);
  }

  while(!myFile.eof()) {
    
    getline(myFile,data); //reads in the information from the file line by line and stores it all in the string "data"
    
    if(isInside(data)) //calls the isInside function to check if the line contains a time stamp
      {
      position = data.find(":"); //finds where in the string the time is located

      justTheTime1 = data[position-2]; //finds the first digit for the hours
      justTheTime2 = data[position-1]; //finds the second digit for the hours
      temp1 = justTheTime1 + justTheTime2; 
      hours = stoi(temp1); //converts the string containing the hours into an integer 
      secs = secs + hours * 3600; //converts the hours to seconds.

      justTheTime3 = data[position+1]; //finds the first digit of the minutes
      justTheTime4 = data[position+2]; //finds the second digit of the minutes
      temp2 = justTheTime3 + justTheTime4;
      minutes = stoi(temp2); //converts the string containing the minutes into an integer
      secs = secs + minutes * 60; //converts the minutes into seconds.

      n = n + 1; //keeps track of how many entries there are that contains a time stamp to later be utilized in calculating the average launch time
    }
  }
  
  myFile.close();
  TimeCode Nasa = TimeCode(0,0,secs); //creates a TimeCode with the total times in seconds

  //Calculating the average launch time with time stamps extracted from the file
  long long unsigned int avgSeconds = secs / n; //Divides the total time stamps in seconds by total number of data entries to find the average launch time in seconds

  //Creates a new TimeCode using the average of all time stamps derived when converting all of the time stamps to seconds.
  TimeCode averageTime = TimeCode(0,0,avgSeconds);
  
  cout<<n<<" data points."<<"\nAVERAGE: "<<averageTime.ToString()<<" UTC."<<endl;
  
}

int main()
{
  readFile();
}


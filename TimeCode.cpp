
#include <iostream>
#include "TimeCode.h"

using namespace std;

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int s) {
  
    t = ComponentsToSeconds(hr, min, s); //converts everything into seconds so it can be stored in the class' private member 't'
}

TimeCode::TimeCode(const TimeCode& tc) { //copy constructor
  this->t = tc.t;
}

void TimeCode::addHours(unsigned int hours) { //finds what the current hours are and then adds the new hours to it.
  unsigned int temp = GetHours(); 
  temp = temp + hours;
  SetHours(temp);
}

void TimeCode::addMinutes(unsigned int minutes) {
  unsigned int temp = GetMinutes();
  temp = temp + minutes;
  
  if(temp>59){ //This accounts for rollover and will convert the minutes into hours
    unsigned int hours = temp;
    unsigned int currentHours = GetHours();
    temp = temp % 60;
    currentHours = hours - temp;
    currentHours = currentHours / 60;
    addHours(currentHours);
    SetMinutes(temp);
  }
  else {
    SetMinutes(temp);
  }
}

void TimeCode::SetHours(unsigned int hours) {

  unsigned int temp = t;
  unsigned int sec = 0;
  unsigned int minutes = 0;

  sec = temp % 60; //finds how many individual seconds are in 't'
  temp = temp - sec;

  minutes = temp % 3600; //gets you minutes in seconds notation
  temp = temp - minutes; //Takes out the minutes and seconds in t to find how many original hours need to be subtracted before you can add the new setHour value so that the hours don't accumulate

  t = t - temp; 
  t = t + hours*3600;
}

void TimeCode::SetMinutes(unsigned int minutes) {

  if(minutes>59) {
    throw invalid_argument("Negative arguments not allowed.");
    /*//rollever minutes to hours
    unsigned int temp;
    unsigned int actualMins;
    unsigned int over; 

    temp = GetMinutes(); //gets minutes
    t = t - (temp * 60); //gets rid of the old minutes from t

    over = minutes / 60; //finds how many hours are within minutes and adds to the hour component.
    addHours(over);

    actualMins = minutes % 60; //finds what the actual value for the minutes after the overage is accounted for

    t = t + actualMins * 60; //adds the new minutes to t after overage is accounted for */
   
  }
  else {
    unsigned int temp = t;
    unsigned int sec = 0;
    unsigned int mins = 0;

    sec = temp % 60; //gets the seconds
    temp = temp - sec;

    mins = temp % 3600;
    t = t - mins; //takes out the original number of minutes in t so that the new added minutes won't accumulate with the old minutes
    t = t + minutes * 60;
  }
}

void TimeCode::SetSeconds(unsigned int seconds) {
  
  if((seconds>=60)) {
    throw invalid_argument("Negative arguments not allowed.");
    /*unsigned int over = seconds;
    long long unsigned int actualSeconds = t;
    actualSeconds = over % 60;
    over = over - actualSeconds;
    over = over / 60; //gives you the rollover seconds in minutes
    addMinutes(over);
    t = t - (t % 60); //removes the original seconds from t
    t = t + actualSeconds; //adds the remaining seconds to t */
  }
  else {
    unsigned int sec = 0;
    long long unsigned int temp = t;

    sec = temp % 60; //gets the seconds
    t = t - sec; //removes the original seconds from t
    t = t + seconds; //adds the new seconds value
  }
}

void TimeCode::reset() {
  t = 0;
}

unsigned int TimeCode::GetHours() const {

  unsigned int hours = t / 3600;
  return hours;
}

unsigned int TimeCode::GetMinutes() const {
  
  unsigned int minutes = (t % 3600) / 60;
  return minutes;
}

unsigned int TimeCode::GetSeconds() const {

  unsigned int temp = 0;
  temp = t % 60;
  return temp;
}

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {

  hr = GetHours();
  min = GetMinutes();
  sec = GetSeconds();
  
}

unsigned long long int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec) {
  unsigned long long int value = (hr*3600) + (min*60) + sec;
  return value;
}

string TimeCode::ToString() const { //converts the time code in seconds to the correct notation for a timeclock

  return to_string(GetHours()) + ":" + to_string(GetMinutes()) + ":" + to_string(GetSeconds());
  
}

TimeCode TimeCode::operator+(const TimeCode& other) const {
  //add both object's t value before assigning it to a new TimeCode object and returning it.
  unsigned long long int sec = this->t + other.t;
  TimeCode temp = TimeCode(0,0,sec);
  return temp;
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
  if(this->t < other.t) { //Ensures that there are no negative results by checking that the second value is always smaller than the first.
    throw invalid_argument("Negative arguments not allowed.");
  }
  else {
    unsigned long long int sec = this->t - other.t;
    TimeCode temp = TimeCode(0,0,sec);
    return temp;
  }
}

TimeCode TimeCode::operator*(double a) const {
  if(a < 0) {
     throw invalid_argument("Sorry you can't do that.");
  }
  unsigned long long int sec = this->t; //takes the implicit parameter, converts to seconds and multiply it by the requested value before creating a new timecode object to return.
  sec = sec * a;
  TimeCode temp = TimeCode(0,0,sec);
  return temp;
}

TimeCode TimeCode::operator/(double a) const {
  if(a <= 0) { //checks for special case of 0 as the denominator
    throw invalid_argument("Sorry you can't do that.");
  }
  unsigned long long int sec = this->t;
  sec = sec / a;
  TimeCode temp = TimeCode(0,0,sec);
  return temp;
}

bool TimeCode::operator==(const TimeCode& other) const {
  //checks that both t value are equal
  if(this->t == other.t) {
    return true; }
  else {
    return false;
  }
}

bool TimeCode::operator!=(const TimeCode& other) const {
  //checks that both t values are different
  if(this->t != other.t) {
    return true; }
  else {
    return false;
  }
}

bool TimeCode::operator<(const TimeCode& other) const {
  //checks that the implicit value of t is smaller than the pass parameter's
  if(this->t < other.t) {
    return true; }
  else {
    return false;
  }
}

bool TimeCode::operator<=(const TimeCode& other) const {
  //checks that the implicit value of t is smaller than or equal to the pass parameter's
  if(this->t <= other.t) {
    return true; }
  else {
    return false;
  }
}

bool TimeCode::operator>(const TimeCode& other) const {
  //checks that the implicit value of t is larger than the pass parameter's
  if(this->t > other.t) {
    return true; }
  else {
    return false;
  }
}

bool TimeCode::operator>=(const TimeCode& other) const {
  //checks that the implicit value of t is larger than or equal to the pass parameter's
  if(this->t >= other.t) {
    return true; }
  else {
    return false;
  }

}

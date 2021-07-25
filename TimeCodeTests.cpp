
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);

	long long unsigned int t2 = TimeCode::ComponentsToSeconds(0, 0, 0);
	assert(t2 == 0);

	//t3 is bigger than a 32 bit signed int
	long long unsigned int t3 = TimeCode::ComponentsToSeconds(900000, 0, 0);
	assert(t3 == 3240000000);
	
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	assert(tc.ToString() == "0:0:0");
	
	// Random but "safe" inputs
	TimeCode tc2 = TimeCode(3, 17, 42);
	assert(tc2.ToString() == "3:17:42");
	
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
        // Large hour values
	TimeCode tc2 = TimeCode(34233,1,1);
	tc2.GetComponents(h, m, s);
	assert(h == 34233 && m == 1 && s == 1);

	//All zeros
	TimeCode tc3 = TimeCode(0,0,0);
	tc3.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);

	//Edge case
	TimeCode tc4 = TimeCode(0,59,59);
	tc4.GetComponents(h, m, s);
	assert(h == 0 && m == 59 && s == 59);
	
	cout << "PASSED!" << endl << endl;
}

void TestGetHours() {
  cout<<"Testing GetHours"<<endl;
  
  TimeCode tc = TimeCode(8, 5, 9);
  assert(tc.GetHours() == 8);

  TimeCode tc2 = TimeCode(3123,23,23);
  assert(tc2.GetHours() == 3123);


  cout<<"PASSED!"<<endl<<endl;
}


void TestGetMinutes() {
  cout<<"Testing GetMinutes"<<endl;

  TimeCode tc = TimeCode(8, 5, 9);
  assert(tc.GetMinutes() == 5);

  TimeCode tc2 = TimeCode(13,0,1);
  assert(tc2.GetMinutes() == 0);

  TimeCode tc3 = TimeCode(13,59,1);
  assert(tc3.GetMinutes() == 59);

  cout<<"PASSED!"<<endl<<endl;
}

void TestGetSeconds() {
  cout<<"Testing GetSeconds"<<endl;

  TimeCode tc = TimeCode(8, 5, 9);
  assert(tc.GetSeconds() == 9);

  TimeCode tc2 = TimeCode(13,23,0);
  assert(tc2.GetSeconds() == 0);

  TimeCode tc3 = TimeCode(13,32,59);
  assert(tc3.GetSeconds() == 59);
  

  cout<<"PASSED!"<<endl<<endl;
}


void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	//ensures that exception is thrown.
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just keep doing more tests
	}
	
	
	cout << "PASSED!" << endl << endl;
}


// Many More Tests...

void TestReset() {
  cout<<"Testing Reset"<<endl;

  TimeCode tc = TimeCode(1,1,1);
  tc.reset();
  assert(tc.GetSeconds() == 0);

  cout<<"PASSED!"<<endl<<endl;
}

void TestToString() {
  cout<<"Testing ToString"<<endl;

  TimeCode tc = TimeCode(1,1,1);
  assert(tc.ToString() == "1:1:1");

  TimeCode tc2 = TimeCode(3,24,23);
  assert(tc2.ToString() == "3:24:23");

  cout<<"PASSED!"<<endl<<endl;
}

void TestSetHours() {
  cout<<"Testing setHours"<<endl;

  //sanity check
  TimeCode tc = TimeCode(1,1,1);
  tc.SetHours(2);
  assert(tc.ToString() == "2:1:1");

  //large value
  TimeCode tc2 = TimeCode(200,2,2);
  tc2.SetHours(34234);
  assert(tc2.ToString() == "34234:2:2");

  //Edge case
  TimeCode tc3 = TimeCode(3,33,03);
  tc3.SetHours(0);
  assert(tc3.ToString() == "0:33:3");
  

  cout<<"PASSED!"<<endl<<endl;
}

void TestSetMinutes(){
	cout << "Testing SetMinutes" << endl;
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15);
	assert(tc.ToString() == "8:15:9");
	
	try{
		tc.SetMinutes(80);
	}
	catch( const invalid_argument& e ) {
		//cout << e.what() << endl;
	}
	assert(tc.ToString() == "8:15:9");
	
	cout << "PASSED!" << endl << endl;
}

void TestSetSeconds(){
	cout << "Testing SetSeconds" << endl;
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetSeconds(19);
	assert(tc.ToString() == "8:5:19");
	
	try{
		tc.SetSeconds(80);
	}
	catch( const invalid_argument& e) {
	}
	assert(tc.ToString() == "8:5:19");
	
	cout << "PASSED!" << endl << endl;
}


void TestAddHours() {
  TimeCode tc = TimeCode(1,1,1);
  tc.addHours(3);
  assert(tc.ToString() == "4:1:1");

}

void TestAdd() {
  cout<<"Testing Add Operator"<<endl;

  TimeCode tc1 = TimeCode(1,1,1);
  TimeCode tc2 = TimeCode(2,2,2);
  TimeCode tc3 = tc1+tc2;
  assert(tc3.ToString() == "3:3:3");

  TimeCode tc4 = TimeCode(0,30,0);
  TimeCode tc5 = TimeCode(0,30,0);
  TimeCode tc6 = tc4 + tc5;
  assert(tc6.ToString() == "1:0:0");

  TimeCode tc7 = TimeCode(100,100,100);
  TimeCode tc8 = tc6 + tc7;
  assert(tc8.ToString() == "102:41:40");

  
  
  cout<<"PASSED!"<<endl<<endl;
}

void TestMultiply(){
	cout << "Testing Multiply" << endl;
	TimeCode tc1 = TimeCode(0, 1, 0);
	TimeCode tc2 = tc1 * 2;
	assert(tc2.ToString() == "0:2:0");
	
	TimeCode tc3 = TimeCode(3, 5, 17);
	TimeCode tc4 = tc3 * 5.5;
	//cout << "tc4: " << tc4.ToString() << endl;
	assert(tc4.ToString() == "16:59:3");
	
	TimeCode tc5 = TimeCode(0, 5, 0);
	TimeCode tc6 = tc5 * 2.5;
	assert(tc6.ToString() == "0:12:30");
	
	TimeCode tc7 = TimeCode(0, 5, 0);
	TimeCode tc8 = tc7 * 0.5;
	assert(tc8.ToString() == "0:2:30");

	// negative number test
	try{
		TimeCode tc10 = tc7 * -2;
		cout << "tc10:" << tc10.ToString() << endl;
		assert(false);
	} catch (const invalid_argument& e){
		
	}


	// 0 test
	TimeCode tc12 = tc7 * 0;
	assert(tc12.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}

void TestDivision() {
  cout<<"Testing Division operator"<<endl;
  
  TimeCode tc1 = TimeCode(10,0,0);
  TimeCode tc2 = tc1 / 2;
  assert(tc2.ToString() == "5:0:0");
  
  TimeCode tc3 = TimeCode(2,0,0);
  try{
		TimeCode tc4 = tc3 / 0;
		assert(false);
	}
	catch(const invalid_argument& e){
	}
  
  

  cout<<"PASSED!"<<endl<<endl;
  
}

void TestEqual() {

  cout<<"Testing equal operator"<<endl;

  TimeCode tc1 = TimeCode(2,2,2);
  TimeCode tc2 = TimeCode(2,2,2);

  cout<<"PASSED!"<<endl<<endl;

}
	
int main(){

  TestDefaultConstructor();
  TestComponentConstructor();
  TestComponentsToSeconds();

  TestToString();
  TestGetComponents();
  
  TestGetHours();
  TestGetMinutes();
  TestGetSeconds();

  TestSetHours();
  TestSetMinutes();
  TestSetSeconds();
  TestAddHours();

  TestReset();

  TestAdd();
  TestSubtract();
  TestMultiply();
  TestDivision();

	
  cout << "PASSED ALL TESTS!!!" << endl;
  return 0;
}


#ifndef HYPOTHESIS_H_
#define HYPOTHESIS_H_

#include <string>
#include <iostream>
#include <vector>

//  static so that the variables are local to the compilation unit
static const std::string match_all = "?";
static const std::string match_none = "#";

class Hypothesis {
private:
	std::vector<std::string> els;

public:
	/*
	  Default Constructor
	*/
	Hypothesis();
	
	/*
	  Usage:
	  Hypothesis h1(4, match_none);
	  Hypothesis h2(4, "nice");
	*/
	Hypothesis(int length, std::string initialize);
	
	/*
	  Copy constructor
	  Usage:
	  h1 = h2;
	*/
	Hypothesis(int length, std::vector<std::string> initialize);

	Hypothesis(const Hypothesis& h);
	
	/*
	  Destructor
	*/
	~Hypothesis();
	
	/*
	   To check whether a training example (which is the argument)
	  passed without the target classification is covered by the
	  the hypothesis or not
	
	  Usage:
	  Hypothesis h;;
	  h = {"?", "low", "strong"};
	  h.isSatisfy({"warm", "low", "strong"}) will return true
	*/
	bool isSatisfy(std::initializer_list<std::string> els);
	/*
	  Usage:
	  Same as previous one but can use vector instead of {"test", "test"}
	*/
	bool isSatisfy(std::vector<std::string> els);
	
	/*
	  To access elements of the hypothesis. Zero based indexing. Can be used
	  as an lvalue as well.
	  Usage:
	  cout << h[1];
	  h[2] = "test";
	  Precondition: 0 <= index < length
	*/
	std::string& operator [](int index);

	Hypothesis operator =(std::initializer_list<std::string> els);
	Hypothesis operator =(std::vector<std::string> els);
	
	/*
	  Generality/Specifity comparison
	*/
	friend bool operator >=(const Hypothesis& a, const Hypothesis& b);
	friend bool operator ==(const Hypothesis& a, const Hypothesis& b);
	friend bool operator >(const Hypothesis& a, const Hypothesis& b);
	friend bool operator <=(const Hypothesis& a, const Hypothesis& b);
	friend bool operator <(const Hypothesis& a, const Hypothesis& b);
	
	/*
	  Usage:
	  Hypothesis h;
	  h = {"test1", "test2"};
	  cout << h;
	  will output the hypothesis as <"test1", "test2">
	*/
	friend std::ostream& operator <<(std::ostream& out, const Hypothesis& h);
};

std::vector<std::vector<std::string>> readData();
std::vector< std::vector <std ::string> > readAttr();
#endif
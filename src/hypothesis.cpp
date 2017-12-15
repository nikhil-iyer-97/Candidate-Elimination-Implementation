#include "hypothesis.h"
#include <fstream>
#include <sstream>

Hypothesis::Hypothesis() {
	;
}

Hypothesis::Hypothesis(int length, std::string initialize) {
	els = std::vector<std::string> (length, initialize);
}

Hypothesis::Hypothesis(int length, std::vector<std::string> initialize) {
		els = initialize;
}

Hypothesis::Hypothesis(const Hypothesis& h) {
	els = h.els;
}

Hypothesis::~Hypothesis() {
	;
}

bool Hypothesis::isSatisfy(std::initializer_list<std::string> els) {
	if ((this -> els).size() != els.size()) {
		return false;
	}
	Hypothesis h;
	h = std::vector<std::string> (els);
	return ((*this) >= h);
}

bool Hypothesis::isSatisfy(std::vector<std::string> els) {		// function to return boolean value which
	if ((this -> els).size() != els.size()) {										// checks if the example satisfies the hypothesis
		return false;
	}
	Hypothesis h;
	h = els;
	return ((*this) >= h);
}

/*
	Precondition: 0 <= index < length
*/
std::string& Hypothesis::operator [](int index) {
	return els[index];
}

Hypothesis Hypothesis::operator =(std::initializer_list<std::string> els) {
	this -> els = std::vector<std::string> (els);
	return (*this);
}

Hypothesis Hypothesis::operator =(std::vector<std::string> els) {
	this -> els = els;
	return (*this);
}

/*
	Precondition: Length of both hypotheses are equal
*/
bool operator >=(const Hypothesis& a, const Hypothesis& b) {	//	">=" operator overloaded for ease of comparison
	for (int i = 0; i < a.els.size(); i++) {
		if ((a.els[i] != match_all && a.els[i] != match_none &&
			a.els[i] != b.els[i] && b.els[i] != match_none) ||
			(a.els[i] == match_none && b.els[i] != match_none)) {
			return false;
		}
	}
	return true;
}

bool operator >(const Hypothesis& a, const Hypothesis& b) {		// ">" operator overloaded for ease of comparison
	return (a >= b && !(a <= b));
}

bool operator <=(const Hypothesis& a, const Hypothesis& b) {	//	"<=" operator overloaded for ease of comparison
	for (int i = 0; i < a.els.size(); i++) {
		if ((a.els[i] != match_all && a.els[i] != match_none &&
			a.els[i] != b.els[i] && b.els[i] != match_all) ||
			(a.els[i] == match_all && b.els[i] != match_all)) {
			return false;
		}
	}
	return true;
}

bool operator <(const Hypothesis& a, const Hypothesis& b) {		// "<" operator overloaded for ease of comparison
	return (a <= b && !(a >= b));
}

bool operator ==(const Hypothesis& a, const Hypothesis& b) {	// equality operator overloaded
	return (a <= b && (a >= b));
}

std::ostream& operator <<(std::ostream& out, const Hypothesis& h) {		// "<<" operator overloading for ease of
																																			//	printing the hypothesis
	out << "<";
	for (int i = 0; i < h.els.size() - 1; i++) {
		out << h.els[i] << ",";
	}
	out << h.els[h.els.size() - 1] << ">";
	return out;
}



std::vector<std::vector<std::string> > readData(){		// function to read input data and store it in
	int n=18;																						// a vector of strings
	std::string fileloc="../data/zoo.data";
	//std::string fileloc="../data/zoo.data";
	std::ifstream fin(fileloc,std::ios::in);
	std::vector<std::vector<std::string>> data;
	while(!fin.eof()){
		std::string s;
		std::vector<std::string> att;

		fin>>s;

		std::stringstream str(s);

		for(int i=0;i<n;i++){
			std::string temp;
			std::getline(str,temp,',');
			att.push_back(temp);
		}
		data.push_back(att);
	}
	return data;
}

std::vector<std::vector<std::string> > readAttr(){		// function to read unique values of each attribute
	std::string fileloc="../data/attr_values";
	//std::string fileloc="../data/zoo.data";
	std::ifstream fin(fileloc,std::ios::in);
	std::vector<std::vector<std::string> > data;
	while(!fin.eof()){
		std::string s;
		std::vector<std::string> att;
		fin>>s;
		std::stringstream str(s);
		while(str)
		{
			std::string temp;
			std::getline(str,temp,',');
			att.push_back(temp);
		}
		data.push_back(att);
	}
	return data;
}

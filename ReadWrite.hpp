#pragma once

#include "Document.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <math.h>
#include <memory>

using std::vector;
using std::string;
using std::set;
using std::map;
using std::pair;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::shared_ptr;

class ReadWrite {
	string inputfilename;
	string outputfilename;

	string getContractorOrProduct(ifstream&);

public:
	ReadWrite() {}
	ReadWrite(string inputfilename, string outputfilename) : inputfilename(inputfilename), outputfilename(outputfilename) {}

	void read(vector<shared_ptr<Document>>&);

	void writeAccountErrorOutput(const Category&, const Type&, const int&, const string&, const int&);

	void writeProductErrorOutput(const Type&, const int&, const vector<map<string, int>::iterator>&);

	void write(const vector<pair<string, int>>&);
};
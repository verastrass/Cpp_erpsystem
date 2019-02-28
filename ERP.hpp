#pragma once

#include "Document.hpp"
#include "ReadWrite.hpp"
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <memory>

using std::set;
using std::map;
using std::pair;
using std::vector;
using std::shared_ptr;
using std::static_pointer_cast;

const string DEFAULT_ACCOUNT = "11111111111111111111";
const int DEFAULT_AMOUNT = 100000;

class ERP {
	vector<shared_ptr<Document>> docs;
	map<string, int> accounts;
	map<string, int> contractors;
	map<string, int> products;
	ReadWrite readWrite;

public:
	ERP(string input, string output) : readWrite(input, output) { accounts.insert(pair<string, int>(DEFAULT_ACCOUNT, DEFAULT_AMOUNT*100)); }
		
	void run();
};
#include "ReadWrite.hpp"

string ReadWrite::getContractorOrProduct(ifstream& f) {
	string cntr = "";
	while (f.get() != '`') {}
	char c = f.get();
	while (c != '`')
	{
		cntr += c;
		c = f.get();
	}
	return cntr;
}


void ReadWrite::read(vector<shared_ptr<Document>> &docs) {
	ifstream fin;
	fin.open(inputfilename, ifstream::in);

	int n;
	fin >> n;

	string id, date, time, contractor, account, product;
	int number, rows;
	float amount, quantity;
	vector<Product> productsTable;

	for (int i = 0; i < n; ++i)
	{
		fin >> id >> number >> date >> time;
		if (date.size() < 10)
			date = "0" + date;
		contractor = getContractorOrProduct(fin);
		string fullDate = date.substr(6, 4) + date.substr(3, 2) + date.substr(0, 2) + time.substr(0, 2) + time.substr(3, 2);
		Type type = (id[1] == 'I') ? INCOME : WITHDRAW;

		if (id[0] == 'B')
		{
			fin >> account >> amount;
			docs.push_back((shared_ptr<Document>) new BankDocument(type, number, fullDate, contractor, account, (int)roundf(amount * 100)));
		}
		else if (id[0] == 'W')
		{
			fin >> rows;
			for (int j = 0; j < rows; ++j)
			{
				product = getContractorOrProduct(fin);
				fin >> quantity >> amount;
				productsTable.emplace_back(product, (int)roundf(quantity * 1000), (int)roundf(amount * 100));
			}

			docs.push_back((shared_ptr<Document>) new WarehouseDocument(type, number, fullDate, contractor, productsTable));
			productsTable.clear();
		}
	}
	fin.close();
}

void ReadWrite::writeAccountErrorOutput(const Category &category, const Type &type, const int &number, const string &account, const int &amount) {
	ofstream fout;
	fout.open(outputfilename, ofstream::out);
	string id;
	id.push_back((category == BANK) ? 'B' : 'W');
	id.push_back((type == INCOME) ? 'I' : 'W');
	fout.precision(2);
	fout << "ERROR " << id << ' ' << number << endl << account << ' ' << std::fixed << amount / 100.0;
	fout.close();
}

void ReadWrite::writeProductErrorOutput(const Type &type, const int &number, const vector<map<string, int>::iterator> &products) {
	ofstream fout;
	fout.open(outputfilename, ofstream::out);
	string id = "W";
	id.push_back((type == INCOME) ? 'I' : 'W');
	fout << "ERROR " << id << ' ' << number << ' ' << products.size() << endl;
	fout.precision(3);
	for (auto it : products)
		fout << '`' << it->first << "` " << std::fixed << it->second / 1000.0 << endl;
	fout.close();
}

void ReadWrite::write(const vector<pair<string, int>>& contractors) {
	ofstream fout;
	fout.open(outputfilename, ofstream::out);
	fout << "OK " << contractors.size() << endl;
	fout.precision(2);
	for (auto& it : contractors)
		fout << '`' << it.first << "` " << std::fixed << it.second / 100.0 << endl;
	fout.close();
}
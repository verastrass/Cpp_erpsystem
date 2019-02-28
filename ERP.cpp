#include "ERP.hpp"

void ERP::run() {
	readWrite.read(docs);
	sort(docs.begin(), docs.end(), [](const shared_ptr<Document> &a, const shared_ptr<Document> &b){ return (a->getDate()) < (b->getDate()); });
	vector<map<string, int>::iterator> wrongProducts;
	for (auto it : docs)
	{
		if (it->getCategory() == BANK)
		{
			auto it1 = static_pointer_cast<BankDocument>(it);
			auto acc = accounts.find(it1->getAccount());
			if (acc == accounts.end())
				acc = (accounts.insert(pair<string, int>(it1->getAccount(), 0))).first;
			acc->second += int(it1->getType())*(it1->getAmount());
			if (acc->second < 0)
			{
				readWrite.writeAccountErrorOutput(it1->getCategory(), it1->getType(), it1->getNumber(), it1->getAccount(), acc->second);
				docs.clear();
				return;
			}
			auto cntr = contractors.find(it1->getContractor());
			if (cntr == contractors.end())
				cntr = (contractors.insert(pair<string, int>(it1->getContractor(), 0))).first;
			cntr->second -= int(it1->getType())*(it1->getAmount());
		}
		else if (it->getCategory() == WAREHOUSE)
		{
			auto it1 = static_pointer_cast<WarehouseDocument>(it);
			auto cntr = contractors.find(it1->getContractor());
			if (cntr == contractors.end())
				cntr = (contractors.insert(pair<string, int>(it1->getContractor(), 0))).first;
			for (auto row : it1->getProductsTable())
			{
				auto prod = products.find(row.getProduct());
				if (prod == products.end())
					prod = (products.insert(pair<string, int>(row.getProduct(), 0))).first;
				prod->second += int(it1->getType())*(row.getQuantity());
				if (prod->second < 0)
					wrongProducts.push_back(prod);
				auto acc = accounts.find(DEFAULT_ACCOUNT);
				acc->second += int(it1->getType())*(row.getAmount());
				cntr->second -= int(it1->getType())*(row.getAmount());
			}
			if (!wrongProducts.empty())
			{
				sort(wrongProducts.begin(), wrongProducts.end(), [](map<string, int>::iterator a, map<string, int>::iterator b){ return (a->first < b->first); });
				readWrite.writeProductErrorOutput(it1->getType(), it1->getNumber(), wrongProducts);
				docs.clear();
				return;
			}
		}
	}
	vector<pair<string, int>> cntrsSorted;
	for (auto it : contractors)
		cntrsSorted.push_back(pair<string, int>(it.first, it.second));

	sort(cntrsSorted.begin(), cntrsSorted.end(), [](const pair<string, int>& a, const pair<string, int>& b){ return (a.second > b.second) || ((a.second == b.second) && (a.first < b.first)); });
	readWrite.write(cntrsSorted);
	docs.clear();
}
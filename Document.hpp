#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

enum Category { BANK, WAREHOUSE };
enum Type { INCOME = 1, WITHDRAW = -1};

class Document {
	Category category;
	Type type;
	int number;
	string date;
	string contractor;
	
public:
	Document(Category category, Type type, int number, string date, string contractor) : category(category), type(type), number(number), date(date), contractor(contractor) {}
	Category getCategory() { return category; }
	Type getType() { return type; }
	int getNumber() { return number; }
	string getDate() { return date; }
	string getContractor() { return contractor; }
};

class BankDocument : public Document {
	string account;
	int amount;
	
public:
	BankDocument(Type type, int number, string date, string contractor, string account, int amount) : Document(BANK, type, number, date, contractor), account(account), amount(amount) {}
	string getAccount() { return account; }
	int getAmount() { return amount; }
};

class Product {
	string product;
	int quantity;
	int amount;
	
public:
	Product(string product, int quantity, int amount) : product(product), quantity(quantity), amount(amount) {}
	string getProduct() { return product; }
	int getQuantity() { return quantity; }
	int getAmount() { return amount; }
};

class WarehouseDocument : public Document {
	vector<Product> productsTable;

public:
	vector<Product> getProductsTable() { return productsTable; }
	WarehouseDocument(Type type, int number, string date, string contractor, const vector<Product>& productsTable) : Document(WAREHOUSE, type, number, date, contractor), productsTable(productsTable) {}
};
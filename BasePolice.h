#pragma once
#include<iostream>
#include"BTree.h"
#include"List.h"
#include"Menu.h"

using namespace std;

class Protocol
{
	string numTZ;
	string date;
	string info;
	int sum;
	bool isPay = false;

public:
	Protocol() : sum(0), isPay(false) {} 
	Protocol(const string& numTZ) : numTZ(numTZ), sum(0), isPay(false) {} 
	Protocol(const string& numTZ, const string& date) : numTZ(numTZ), date(date), sum(0), isPay(false) {} 
	Protocol(const string& numTZ, const string& date, const string& info) : numTZ(numTZ), date(date), info(info), sum(0), isPay(false) {} 
	Protocol(const string& numTZ, const string& date, const string& info, int sum) : numTZ(numTZ), date(date), info(info), sum(sum), isPay(false) {} 
	Protocol(const string& numTZ, const string& date, const string& info, int sum, bool isPay) : numTZ(numTZ), date(date), info(info), sum(sum), isPay(isPay) {}

	string getNumTZ() { return numTZ; }

	friend ostream& operator<<(ostream& out, const Protocol& p);
	friend istream& operator>>(istream& in, Protocol& p);

	void setPay(bool is) {
		isPay = is;
	}
	void printToFile(ofstream& file) const {
		file << "NumTZ:" << numTZ << endl;
		file << "Date: " << date << endl;
		file << "Info: " << info << endl;
		file << "Sum: " << sum << endl;
		file << "Is Paid: " << (isPay ? "Yes" : "No") << endl;
		file << endl;
	}
	//! get
	string getNumTZ() const { return numTZ; }
	string getDate() const { return date; }
	string getInfo() const { return info; }
	int getSum() const { return sum; }
	bool getIsPay() const { return isPay; }

	//! set
	void setNumTZ(const string& numTZ) { this->numTZ = numTZ; }
	void setDate(const string& date) { this->date = date; }
	void setInfo(const string& info) { this->info = info; }
	void setSum(int sum) { this->sum = sum; }
	void setIsPay(bool isPay) { this->isPay = isPay; }
};

inline ostream& operator<<(ostream& out, const Protocol& p)
{
	out << "NumTZ: " << p.numTZ << ", Date: " << p.date << ", Info: " << p.info << ", Sum: " << p.sum;
	if (p.isPay)
		out << " (Paid)";
	else
		out << " (Not Paid)";
	return out;
}

istream& operator>>(istream& in, Protocol& p)
{
	cout << "Enter NumTZ: ";
	in >> p.numTZ;
	cout << "Enter Date: ";
	in >> p.date;
	cout << "Enter Info: ";
	in >> p.info;
	cout << "Enter Sum: ";
	in >> p.sum;
	cout << "Is Paid (1 for Yes / 0 for No): ";
	in >> p.isPay;
	return in;
}



class BasePolice
{
	BTree<string, List<Protocol>> base;

	void addProtocol();
	void printAll();
	void printTZ();
	void printDiapazon();
	void save();
	void load();
	void pay();
	void printAll(BTreeNode<string, List<Protocol>>* node);
	void printDiapazon(BTreeNode<string, List<Protocol>>* node, const string& start, const string& end);
public:
	
	void menu();
};

void BasePolice::menu()
{
	load();
	do
	{
		system("cls");
		int c = Menu::select_vertical({ 
			"Add", 
			"Print all", 
			"Print TZ", 
			"Print Diap", 
			"Pay",
			"Load",
			"Save",
			"Exit" },
			HorizontalAlignment::Left, 1);
		switch (c)
		{
		case 0: addProtocol(); break;
		case 1: printAll(); break;
		case 2: printTZ(); break;
		case 3: printDiapazon(); break;
		case 4: pay();  break;
		case 5: load();  break;
		case 6: save();  exit(0);
		case 7: exit(0);
		}

	} while (true);
}
void BasePolice::addProtocol()
{
	system("cls");
	cout << "Add protocol" << endl;
	cout << "--------------------" << endl;
	Protocol p;
	cin >> p;
	List<Protocol>* list = base.getValue(p.getNumTZ());
	if (list)
	{
		list->push_back(p);
	}
	else
	{
		List<Protocol> newList;
		newList.push_back(p);
		base.push_r(p.getNumTZ(), newList);
	}
}


void BasePolice::printAll() {
	printAll(base.getRoot());
	system("pause");
}

void BasePolice::printAll(BTreeNode<string, List<Protocol>>* node) {
	if (!node)
		return;

	printAll(node->left);
	cout << "Protocols for " << node->key << ":\n";
	node->value.print();
	cout << endl;
	printAll(node->right);
}


void BasePolice::printTZ()
{
	string numTZ;
	cout << "Enter NumTZ: ";
	cin >> numTZ;
	List<Protocol>* list = base.getValue(numTZ);
	if (list) {
		cout << "Protocols for " << numTZ << ":\n";
		list->print();
	}
	else {
		cout << "No protocols found for " << numTZ << endl;
	}
	cout << endl;
	system("pause");
}

void BasePolice::printDiapazon()
{
	string start, end;
	cout << "Enter Start NumTZ: ";
	cin >> start;
	cout << "Enter End NumTZ: ";
	cin >> end;

	for (size_t i = start; i < length; i++)
	{

	}
		auto startIter = base.getValue(start);

	auto endIter = base.getValue(end);

	if (!startIter || !endIter) {
		cout << "Invalid NumTZ entered\n";
		system("pause");
		return;
	}

	cout << "Protocols between " << start << " and " << end << ":\n";
	printDiapazon(base.getRoot(), start, end);
	cout << endl;
	system("pause");

}

void BasePolice::printDiapazon(BTreeNode<string, List<Protocol>>* node, const string& start, const string& end) {
	if (!node)
		return;

	auto startIter = node->getValue(start);
	auto endIter = node->getValue(end);

	if (startIter) {
		printDiapazon(node->left, start, end);
	}

	if (startIter && endIter) {
		cout << "Protocols for " << node->key << ":\n";
		node->value.print();
		cout << endl;
		printDiapazon(node->right, start, end);
	}
	else if (!startIter && node->key >= start && node->key <= end) {
		printDiapazon(node->right, start, end);
	}
}

void BasePolice::save()
{
	ofstream file("base.txt");
	if (!file) {
		cerr << "Error opening file for writing!\n";
		return;
	}

	base.printToFile(file);

	file.close();
	cout << "Base saved successfully.\n";
}

void BasePolice::load() {
	ifstream file("base.txt");
	if (!file.is_open()) {
		cerr << "Error opening file" << endl;
		return;
	}

	string line;
	string numTZ;
	Protocol p;
	while (getline(file, line)) { 
		if (!line.empty()) {
			if (line.back() == ':') { 
				numTZ = line.substr(0, line.size() - 1); 
			}
			else {
				size_t pos = line.find(':');
				if (pos != string::npos) {
					string key = line.substr(0, pos);
					string value = line.substr(pos + 1);
					if (key == "NumTZ") {
						if (!p.getNumTZ().empty()) { 
							List<Protocol>* list = base.getValue(p.getNumTZ());
							if (list) {
								list->push_back(p);
							}
							else {
								List<Protocol> newList;
								newList.push_back(p);
								base.push_r(p.getNumTZ(), newList);
							}
						}
						p.setNumTZ(value);
					}
					else if (key == "Date") {
						p.setDate(value);
					}
					else if (key == "Info") {
						p.setInfo(value); 
					}
					else if (key == "Sum") {
						p.setSum(stoi(value));
					}
					else if (key == "Is Paid") {
						p.setIsPay(value == "Yes");
					}
				}
			}
		}
	}

	if (!p.getNumTZ().empty()) {
		List<Protocol>* list = base.getValue(p.getNumTZ());
		if (list) {
			list->push_back(p);
		}
		else {
			List<Protocol> newList;
			newList.push_back(p);
			base.push_r(p.getNumTZ(), newList);
		}
	}

	file.close();
}




void BasePolice::pay()
{
	string numTZ;
	cout << "Enter NumTZ to mark as paid: ";
	cin >> numTZ;

	List<Protocol>* list = base.getValue(numTZ);
	if (list) {
		cout << "Protocols for " << numTZ << ":\n";
		list->print();
		cout << endl;
		size_t index;
		cout << "Enter index of protocol to mark as paid: ";
		cin >> index;
		if (index >= 0 && index < list->length()) {
			(*list)[index].setPay(true);
			cout << "Protocol marked as paid.\n";
		}
		else {
			cout << "Invalid index!\n";
		}
	}
	else {
		cout << "No protocols found for " << numTZ << endl;
	}
}

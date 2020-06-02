#pragma once
#include"ConsoleBufferHelper.h"
#include "Hash_Map.h"
#include <string>
#include <iostream>

class ConsoleDisplayTable
{
public:
	ConsoleDisplayTable();
	~ConsoleDisplayTable();
	void add(int id, std::string line);
	void remove(int id);
	void clear();
	void refresh();

private:
	//ConsoleBufferHelper* cbh;
	stdext::hash_map<int, std::string> tableMap;
	void update();
};

ConsoleDisplayTable::ConsoleDisplayTable()
{
	//cbh = new ConsoleBufferHelper();
	//cbh->update();
}

ConsoleDisplayTable::~ConsoleDisplayTable()
{
}

inline void ConsoleDisplayTable::add(int id, std::string line)
{
	if (tableMap.find(id) == tableMap.end()) {
		tableMap.insert(std::pair<int, std::string>(id, line));
	}
	else {
		if (tableMap.at(id) != line) {
			tableMap.at(id) = line;
		}
	}
	update();
}

inline void ConsoleDisplayTable::remove(int id)
{
	this->tableMap.at(id) = "";
	update();
}

inline void ConsoleDisplayTable::clear()
{
	this->tableMap.clear();
	system("cls");
}

inline void ConsoleDisplayTable::refresh()
{
	update();
}

inline void ConsoleDisplayTable::update()
{
	if (this->tableMap.size() > 0) {
		system("cls");
		for (int i = 0; i < tableMap.size(); i++) {
			if (tableMap[i] != "") {
				std::cout << tableMap[i] << std::endl;
			}
		}
	}
}

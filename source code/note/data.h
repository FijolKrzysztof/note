#ifndef DATA_H
#define DATA_H

#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <QMainWindow>
#include <QDate>
#include <QTime>

using namespace std;

const QString getText(int);
string getDateFromMain(int);
string getFirstDateTime(int);
void SQLCreate(string);
void deleteTableAndID(int);
void createTableAndInsertID(int);
void deleteFromScheduleTable(int, int);
void updateText(int, string);
void updateDateTime(int, string);
void updateDateAndTime(int, int, QDate, QTime);
void insertScheduleInfo(int, int, QDate, QTime);
vector<string> SQLGet(string);
vector<QDate> getDates(int);
vector<QTime> getTimes(int);
int getFreeID(string);
int callback(void*, int, char**, char**);
vector<int> getMainIDs();
vector<int> getScheduleIDs(int);
vector<int> convertToInt(vector<string>);

#endif // DATA_H

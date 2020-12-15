#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sqlite3.h>
#include <vector>
#include <sstream>
#include <QDateTime>
#include <chrono>
#include <thread>

using namespace std;

vector<string> cellData;

int convertToInt(string data)
{
    stringstream convertData(data);
    int convertToInt;
    convertData >> convertToInt;
    return convertToInt;
}
int callback(void*, int argc, char** argv, char**)
{
    vector<string> data;
    for(int i = 0; i < argc; i++)
    {
        string cell = argv[i];
        data.push_back(cell);
    }
    int dataSize = data.size();
    for(int i = 0; i < dataSize; i++)
    {
        cellData.push_back(data[i]);
    }
    return 0;
}
vector<string> SQLGet(string sql)
{
    cellData.clear();
    sqlite3 *DB;
    sqlite3_open("/home/ja/project/cpp/note/DB", &DB);
    //sqlite3_open("Note/DB", &DB);
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
    return cellData;
}
string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}
int main()
{
    do
    {
        this_thread::sleep_for(chrono::seconds(30));
        string result = exec("ps -ef | grep note123 | wc -l");
        int state = convertToInt(result);
        if(state == 2)
        {
            vector<string> schedules = SQLGet("SELECT DATETIME FROM MAIN ORDER BY DATETIME ASC;");
            if(schedules.size() != 0)
            {
                string schedule = schedules[0];
                QDateTime currentDate = QDateTime::currentDateTime();
                QString convert = currentDate.toString("yyyy.MM.dd hh:mm");
                string date = convert.toStdString();
                if(date >= schedule)
                {
                    system("/home/ja/project/cpp/note/debug/note123");
                    //system("Note/note123");
                }
            }
        }
    }
    while(true);
    return 0;
}

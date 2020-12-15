#include "data.h"
using namespace std;
const char* globalPath = "/home/ja/project/cpp/note/DB";
//const char* globalPath = "DB";
vector<string> cellData;

const QString getText(int ID)
{
    vector<string> outputText = SQLGet("SELECT TEXT FROM MAIN WHERE ID = " + to_string(ID) + ";");
    const QString convertedText = QString::fromStdString(outputText[0]);
    return convertedText;
}
string getDateFromMain(int ID)
{
    vector<string> output = SQLGet("SELECT DATETIME FROM MAIN WHERE ID = " + to_string(ID) + ";");
    return output[0];
}
string getFirstDateTime(int ID)
{
    vector<string> getDateTime = SQLGet("SELECT DATETIME FROM Z" + to_string(ID) + " ORDER BY DATETIME ASC;");
    int getDateTimeSize = getDateTime.size();
    if(getDateTimeSize == 0)
    {
        return "none";
    }
    return getDateTime[0];
}
void SQLCreate(string sql)
{
    sqlite3 *DB;
    sqlite3_open(globalPath, &DB);
    sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);
}
void deleteTableAndID(int ID)
{
    SQLCreate("DELETE FROM MAIN WHERE ID = " + to_string(ID) + ";");
    SQLCreate("DROP TABLE Z" + to_string(ID) + ";");
}
void createTableAndInsertID(int ID)
{
    SQLCreate("INSERT INTO MAIN VALUES (" + to_string(ID) + ", '', '');");
    SQLCreate("CREATE TABLE Z" + to_string(ID) + "(ID INT, DATETIME TEXT, DATE TEXT, TIME TEXT);");
}
void deleteFromScheduleTable(int ID, int scheduleID)
{
    SQLCreate("DELETE FROM Z" + to_string(ID) + " WHERE ID = " + to_string(scheduleID) + ";");
}
void updateText(int ID, string text)
{
    SQLCreate("UPDATE MAIN SET TEXT = '" + text + "' WHERE ID = " + to_string(ID) + ";");
}
void updateDateTime(int ID, string data)
{
    SQLCreate("UPDATE MAIN SET DATETIME = '" + data + "' WHERE ID = " + to_string(ID) + ";");
}
void updateDateAndTime(int ID, int scheduleID, QDate date, QTime time)
{
    QString createDate = date.toString("yyyy.MM.dd");
    QString createTime = time.toString("hh:mm");
    string convertDate = createDate.toStdString();
    string convertTime = createTime.toStdString();
    string dateAndTime = convertDate + " " + convertTime;
    SQLCreate("UPDATE Z" + to_string(ID) + " SET DATETIME = '" + dateAndTime + "', DATE = '" + convertDate + "', TIME = '"
              + convertTime + "' WHERE ID = " + to_string(scheduleID) + ";");
}
void insertScheduleInfo(int ID, int scheduleID, QDate date, QTime time)
{
    QString createDate = date.toString("yyyy.MM.dd");
    QString createTime = time.toString("hh:mm");
    string convertDate = createDate.toStdString();
    string convertTime = createTime.toStdString();
    string dateAndTime = convertDate + " " + convertTime;
    SQLCreate("INSERT INTO Z" + to_string(ID) + " VALUES(" + to_string(scheduleID) + ",'" + dateAndTime + "','" + convertDate + "','" + convertTime + "');");
}
vector<string> SQLGet(string sql)
{
    cellData.clear();
    sqlite3 *DB;
    sqlite3_open(globalPath, &DB);
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
    return cellData;
}
vector<QDate> getDates(int ID)
{
    vector<QDate> output;
    vector<string> Dates = SQLGet("SELECT DATE FROM Z" + to_string(ID) + " ORDER BY DATETIME ASC;");
    int DatesSize = Dates.size();
    for(int i = 0; i < DatesSize; i++)
    {
        QString date_string_on_db = QString::fromStdString(Dates[i]);
        QDate Date = QDate::fromString(date_string_on_db,"yyyy.MM.dd");
        output.push_back(Date);
    }
    return output;

}
vector<QTime> getTimes(int ID)
{
    vector<QTime> output;
    vector<string> Times = SQLGet("SELECT TIME FROM Z" + to_string(ID) + " ORDER BY DATETIME ASC;");
    int TimesSize = Times.size();
    for(int i = 0; i < TimesSize; i++)
    {
        QString time_string_on_db = QString::fromStdString(Times[i]);
        QTime Time = QTime::fromString(time_string_on_db, "hh:mm");
        output.push_back(Time);
    }
    return output;
}
int getFreeID(string table)
{
    vector<string> data = SQLGet("SELECT ID FROM " + table + " ORDER BY DATETIME ASC");
    vector<int> files = convertToInt(data);
    sort(files.begin(), files.end());
    int counter = -1;
    int sizeOfFiles = files.size();
    if(sizeOfFiles == 0)
    {
        counter = 0;
    }
    for(int i = 0; i < sizeOfFiles; i++)
    {
        if(files[i] != i)
        {
            counter = i;
            break;
        }
        if(counter == -1)
        {
            counter = sizeOfFiles;
        }
    }
    return counter;
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
vector<int> getMainIDs()
{
    vector<string> output = SQLGet("SELECT ID FROM MAIN ORDER BY DATETIME ASC;");
    vector<int> intOutput = convertToInt(output);
    return intOutput;
}
vector<int> getScheduleIDs(int ID)
{
    vector<string> IDs = SQLGet("SELECT ID FROM Z" + to_string(ID) + " ORDER BY DATETIME ASC;");
    vector<int> output = convertToInt(IDs);
    return output;
}
vector<int> convertToInt(vector<string> data)
{
    vector<int> output;
    int dataSize = data.size();
    for(int i = 0; i < dataSize; i++)
    {
        stringstream convertData(data[i]);
        int convertToInt;
        convertData >> convertToInt;
        output.push_back(convertToInt);
    }
    return output;
}

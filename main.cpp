#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void task1(const string &);
void task2(const string &);

struct tableNumber
{
    int num = 0;
    bool isChecked = false;
};

struct tableTemplate
{
    tableNumber num[5][5];
};

int main() {
    string path;
    fstream fileStream;
    char confirmChar('m');

    cout << "AoC, day 4.\n";
    do {
        cout << "Type path to input file with puzzles:\n";
        cin >> path;

        fileStream.open(path);
        if(fileStream.is_open())
        {
            fileStream.close();
            cout << "File successfully opened!\n";
            cout << "First task data:\n";
            task1(path);

            cout << "Second task data:\n";
            task2(path);

            break;
        }
        else
        {
            fileStream.close();
            cout << "Wrong path to file. Not opened. Try again? y/n - ";
            cin >> confirmChar;
            if(confirmChar == 'y' || confirmChar == 'Y') confirmChar = 'm';
        }
    }while(confirmChar == 'm');
}

void task1 (const string &path)
{
    fstream stream;
    stream.open(path);

    vector<int> controlNumbers;
    vector<tableTemplate> tables;

    string badControlNumbersStr;
    getline(stream, badControlNumbersStr);
    int controlNumbersSize = 0, idx = 0;
    while(!badControlNumbersStr.size() == 0)
    {
        string tempStr; tempStr.resize(2);
        if(badControlNumbersStr[idx] == ',')
        {
            for(int copyIdx = 0; copyIdx < idx; copyIdx++)
            {
                tempStr[copyIdx] = badControlNumbersStr[copyIdx];
            }

            controlNumbersSize++;
            controlNumbers.resize(controlNumbersSize);
            controlNumbers[controlNumbersSize - 1] = stoi(tempStr);

            badControlNumbersStr.erase(badControlNumbersStr.begin(), badControlNumbersStr.begin() + idx + 1);
            idx = 0;
        }
        else idx++;
    }

    int tablesSize = 0;
    while(!stream.eof())
    {
        tablesSize++;
        tables.resize(tablesSize);
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < 5; j++)
                stream >> tables[tablesSize - 1].num[i][j].num;
    }

    int lastCheckedNumber(0), winnerTable(0);

    for(int controlNumber : controlNumbers)
        for(int tableIdx = 0; tableIdx < tablesSize; tableIdx++)
            for(int i = 0; i < 5; i++)
                for(int j = 0; j < 5; j++)
                    if(tables[tableIdx].num[i][j].num == controlNumber)
                    {
                        tables[tableIdx].num[i][j].isChecked = true;

                        bool goodRow = true, goodColumn = true;
                        for(int h = 0; h < 5; h++)
                        {
                            if(!tables[tableIdx].num[i][h].isChecked) goodRow = false;
                            if(!tables[tableIdx].num[h][j].isChecked) goodColumn = false;
                        }
                        if(goodRow || goodColumn)
                        {
                            lastCheckedNumber = controlNumber;
                            winnerTable = tableIdx;

                            goto ExitPoint;
                        }
                    }

    ExitPoint:

    int winSum(0);
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            if(!tables[winnerTable].num[i][j].isChecked) winSum += tables[winnerTable].num[i][j].num;

    cout << winSum * lastCheckedNumber << '\n';
}

void task2 (const string &path)
{
    fstream stream;
    stream.open(path);

    vector<int> controlNumbers;
    vector<tableTemplate> tables;

    string badControlNumbersStr;
    getline(stream, badControlNumbersStr);
    int controlNumbersSize = 0, idx = 0;
    while(!badControlNumbersStr.size() == 0)
    {
        string tempStr; tempStr.resize(2);
        if(badControlNumbersStr[idx] == ',')
        {
            for(int copyIdx = 0; copyIdx < idx; copyIdx++)
            {
                tempStr[copyIdx] = badControlNumbersStr[copyIdx];
            }

            controlNumbersSize++;
            controlNumbers.resize(controlNumbersSize);
            controlNumbers[controlNumbersSize - 1] = stoi(tempStr);

            badControlNumbersStr.erase(badControlNumbersStr.begin(), badControlNumbersStr.begin() + idx + 1);
            idx = 0;
        }
        else idx++;
    }

    int tablesSize = 0;
    while(!stream.eof())
    {
        tablesSize++;
        tables.resize(tablesSize);
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < 5; j++)
                stream >> tables[tablesSize - 1].num[i][j].num;
    }

    int lastCheckedNumber(0);

    for(int controlNumber : controlNumbers)
    {
        NextTable:
        for(int tableIdx = 0; tableIdx < tables.size(); tableIdx++)
            for(int i = 0; i < 5; i++)
                for(int j = 0; j < 5; j++)
                    if(tables[tableIdx].num[i][j].num == controlNumber)
                    {
                        tables[tableIdx].num[i][j].isChecked = true;

                        bool goodRow = true, goodColumn = true;
                        for(int h = 0; h < 5; h++)
                        {
                            if(!tables[tableIdx].num[i][h].isChecked) goodRow = false;
                            if(!tables[tableIdx].num[h][j].isChecked) goodColumn = false;
                        }
                        if(goodRow || goodColumn)
                        {
                            if(tables.size() == 1)
                            {
                                lastCheckedNumber = controlNumber;
                                goto ExitPoint;
                            }
                            else
                            {
                                tables.erase(tables.begin() + tableIdx);
                            }
                        }
                    }
    }


    ExitPoint:

    int winSum(0);
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            if(!tables[0].num[i][j].isChecked) winSum += tables[0].num[i][j].num;

    cout << winSum * lastCheckedNumber << '\n';
}
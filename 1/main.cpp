#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void input_to_payment(string name, string last_name, string money, string date)
{
    ofstream payment ("../payment.txt", ios::app);
    if (payment.is_open())
    {
        cout << "Information save in file." << endl;
        payment << endl << name << " " << last_name << " " << money << " " << date;
        payment.close();
    }
    else cout << "File doesn't open" << endl;
}

string input_temp(const string& what_input)
{
    cout << "enter the " << " " << what_input << " of the recipient of the funds " << endl;
    string temp_str;
    cin >> temp_str;
    return temp_str;
}

string check_first_latter (string temp_str)
{
    if (temp_str[0]>=97 && temp_str[0]<=122) temp_str[0]-=32;
    return temp_str;
}

bool check_money(string money)
{
    if (stoi(money)>=0) return true;
    else
    {
        cout << "Incorrect input. Try again" << endl;
        return false;
    }

}

bool check_date(string date)
{
    bool checkDay = false, checkMonth = false, checkYear=false;
    int point_pos = date.find('.');
    int point_pos2 = date.find('.',point_pos + 1);
    int Day = stoi(date.substr(0,point_pos));
    int Month = stoi(date.substr(point_pos + 1 ,point_pos2 + 1));
    int Year = stoi(date.substr(point_pos2 + 1, date.length()-point_pos2 - 1));


    if (Year <= 2022 && Year >=1950) checkYear = true; // условные ограничения дл года

    if (Month>=1 && Month<=12) checkMonth = true;

    if (Month<=7)
    {
        if (Month%2 != 0 && Day<=31) checkDay = true;
        else if (Month%2 == 0 && Day<=30) checkDay = true;
        if (Month == 2 && Day>28) checkDay = false;
    }
    else
    {
        if (Month%2 != 0 && Day<=30) checkDay = true;
        else if (Month%2 == 0 && Day<=31) checkDay = true;
    }

    cout << "check day " << checkDay << " || check Month " << checkMonth << endl;

    if (!checkDay || !checkMonth || !checkYear)
    {
        cout << "Invalid date. try again" << endl;
        return false;
    }
    else return true;
}

int main() {
    string ans;
    string name, last_name, money, date;
    do
    {
        name=input_temp("name");
        name=check_first_latter(name);

        last_name=input_temp("last name");
        last_name=check_first_latter(last_name);

        bool bMoney= false;
        while (!bMoney)
        {
            money=input_temp("money");
            bMoney=check_money(money);
        }

        bool bDate=false;
        while (!bDate)
        {
            date=input_temp("date");
            bDate=check_date(date);
        }

        input_to_payment(name, last_name, money, date);

        cout << "Do you want to input new person?" << endl << "Yes/No" << endl;
        cin >> ans;
    }
    while (ans=="Yes" || ans=="yes");


}

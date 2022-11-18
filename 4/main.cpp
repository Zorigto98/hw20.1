#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int get_banknote()
{
    //srand( time(0) );
    switch(1 + rand()%6)
    {
        case 1: return 100;
        case 2: return 200;
        case 3: return 500;
        case 4: return 1000;
        case 5: return 2000;
        case 6: return 5000;
    }
}

void input_ATM(vector <int> &vec, int& range) // метод заполнения банкомата
{
    vector <int> ATM; // вектор с банкнотами
    for (int i=0; i<range;i++) // заполнение банкомата банкнотами
    {
        ATM.push_back(get_banknote());
        vec[6] += ATM[i]; // общая сумма в банкомате
        if (ATM[i] == 5000) vec[0]++;
        else if (ATM[i] == 2000) vec[1]++;
        else if (ATM[i] == 1000) vec[2]++;
        else if (ATM[i] == 500) vec[3]++;
        else if (ATM[i] == 200) vec[4]++;
        else if (ATM[i] == 100) vec[5]++;
    }
}

void input_bank_info(string str, vector <int> &vec) // запись колличества банкнот в файл c сохранением предыдущего состояния
{
    ofstream BankInfo (str, ios::app);
    if (BankInfo.is_open())
    {
        for (int i = 0; i < 7; i++)
        {
            BankInfo << vec[i] << " ";
        }
        BankInfo << endl;
        BankInfo.close();
    }
    else cout << "File doesn't open" << endl;
}

int main() {
    //vector <int> ATM; // вектор с банкнотами
    vector <int> ATMinfo (7, 0);
    int ATM_range = 10; // кол-во банкнот в банкомате

    input_ATM(ATMinfo, ATM_range); // заполнение банкомата

    input_bank_info("../ATMinfo.txt", ATMinfo); // запись в файл ATMinfo информации о кол-ве банкнот в банкомате

    bool end_prog = false;

    while (!end_prog) // пока не будет введен символ "E" или "e"
    {
        char key_do;
        cout << "What you want do? | E - exit | Any key - continue | + add money | - take money" << endl;
        cin >> key_do;
        if (key_do == '-')
        {
            int draw_sum;
            cout << "How much do you want to withdraw ?" << endl;
            cin >> draw_sum;
            if (draw_sum % 100 == 0 && draw_sum <= ATMinfo[6])
            {
                vector <int> Temp_ATM (7, 0);
                for (int i = 0; i < 7; i++)
                {
                    Temp_ATM[i] = ATMinfo[i];
                    cout << Temp_ATM[i] << " ";
                }
                cout << endl;
                int temp_draw_sum = draw_sum;
                while(draw_sum != 0)
                {
                    cout << "start" << endl;
                    while (draw_sum >= 5000 && ATMinfo[0] > 0)
                    {
                        draw_sum -= 5000;
                        ATMinfo[0]--;
                        ATMinfo[6] -= 5000;
                    }
                    while (draw_sum >= 2000 && ATMinfo[1] > 0)
                    {
                        draw_sum -= 2000;
                        ATMinfo[1]--;
                        ATMinfo[6] -= 2000;
                    }
                    while (draw_sum >= 1000 && ATMinfo[2] > 0)
                    {
                        draw_sum -= 1000;
                        ATMinfo[2]--;
                        ATMinfo[6] -= 1000;
                    }
                    while (draw_sum >= 500 && ATMinfo[3] > 0)
                    {
                        draw_sum -= 500;
                        ATMinfo[3]--;
                        ATMinfo[6] -= 500;
                    }
                    while (draw_sum >= 200 && ATMinfo[4] > 0)
                    {
                        draw_sum -= 200;
                        ATMinfo[4]--;
                        ATMinfo[6] -= 200;
                    }
                    while (draw_sum >= 100 && ATMinfo[5] > 0)
                    {
                        draw_sum -= 100;
                        ATMinfo[5]--;
                        ATMinfo[6] -= 100;
                    }
                    if (draw_sum > 0)
                    {
                        cout << "You can't draw " << temp_draw_sum << " sum. You can withdraw " << temp_draw_sum-draw_sum << endl;
                        cout << "Withdraw " << temp_draw_sum-draw_sum << "? N - no Y - yes" << endl;
                        cin >> key_do;
                        if (key_do == 'Y' || key_do == 'y') draw_sum = 0;
                        else // возврат денег обратно в банкомат
                        {
                            draw_sum = 0;
                            for (int i = 0; i < 7; i++)
                            {
                                ATMinfo[i] = Temp_ATM[i];
                            }
                            cout << "Money returned to ATM" << endl;
                        }
                    }
                }
                input_bank_info("../ATMinfo.txt", ATMinfo);
            }
            else cout << "You can't draw this sum" << endl;
        }

        else if (key_do == '+') // заполнение банкомата инкоссацией (заполнение банкомата по новой)
        {
            input_ATM(ATMinfo, ATM_range); // запись банкнот в файл bank из вектора
        }

        else if (key_do == 'E' || key_do == 'e') end_prog = true;
    }
}




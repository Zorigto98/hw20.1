#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    int countFish=0;
    char endFishing;
    bool end_fishing= false;

    ofstream basket("../basket.txt", std::ofstream::out | std::ofstream::trunc); // очиска файла basket

    if (basket.is_open())
    {
        while(!end_fishing)
        {
            string fish, temp_fish_in_river;
            cout << "Enter what kind of fish you want to fish" << endl;
            cin >> fish;

            fstream river ("../river.txt");
            if (river.is_open())
            {
                while (!river.eof())
                {
                    river >> temp_fish_in_river;
                    if (temp_fish_in_river==fish)
                    {
                        basket << temp_fish_in_river << endl;
                        basket.close();
                        countFish++;
                    }
                }
            }
            else cout << "File river.txt doesn't open" << endl;

            cout << "do you want to fish?" << endl;
            cout << "N,n - stop program; Y,y - continual" << endl;
            cin >> endFishing;

            if (endFishing=='N' || endFishing=='n') end_fishing=true;
        }
        cout << "Fish caught:" << countFish << endl;
    }
    else cout << "File basket doesn't open" << endl;

}
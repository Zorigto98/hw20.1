#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main() {
    ofstream pic ("../pic.txt");

    srand(time(nullptr));

    cout << "Input range of picture" << endl;
    int rol=0, col=0;
    cout << "rol: " << endl;
    cin >> rol;
    cout << "col: " << endl;
    cin >> col;

    for (int i=0; i<rol; i++)
    {
        for (int j=0; j<col; j++)
        {
            pic << rand()%2 << " ";
        }
        pic << endl;
    }

    pic.close();
}

#include <iostream>

using namespace std;

int main()
{
    string color, plural_noun, celebrity;

    cout << "Enter a color:" << endl;
    getline(cin, color);

    cout << "Enter a plural noun:" << endl;
    getline(cin, plural_noun);

    cout << "Enter a celebrity:" << endl;
    getline(cin, celebrity);

    cout << "Roses are " << color << endl;
    cout << plural_noun << " are Blue" << endl;
    cout << "I love " << celebrity << endl;

    return 0;
}
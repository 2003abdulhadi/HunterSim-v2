#include "View.h"

View::View() {}

View::~View() {}

void View::display(int &c)
{
    using namespace std;
    int numOptions = 3;

    cout << endl
         << endl;
    cout << "What would you like to do:" << endl;
    cout << "  (1) Print Rooms" << endl;
    cout << "  (2) Print Characters" << endl;
    cout << "  (3) Begin Simulation" << endl;

    cout << "  (0) Exit" << endl
         << endl;

    cout << "Enter your selection: ";
    cin >> c;
    if (c == 0)
        return;

    while (c < 0 || c > numOptions)
    {
        cout << "Enter your selection: ";
        cin >> c;
    }
}
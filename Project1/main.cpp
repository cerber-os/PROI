/*
 * File: main.cpp
 * Author: Paweł Wieczorek
 * Date: 04 mar 2019
 */

#include <iostream>
#include "realSet.h"

#define NUMBER_OF_SETS      10

using namespace std;

enum menuOptions{M_APPEND = 1, M_REMOVE, M_LENGTH, M_PRINT, M_UNION, M_DIFF, M_INTER, M_EQ, M_EXIT};

void printHelp() {
    cout << "############ Usage ##########" << endl;
    cout << "1. Append element to set" << endl;
    cout << "2. Remove element from set" << endl;
    cout << "3. Get number of elements in set" << endl;
    cout << "4. Print set" << endl;
    cout << "5. Union of sets" << endl;
    cout << "6. Sets difference" << endl;
    cout << "7. Sets intersection" << endl;
    cout << "8. Check equality" << endl;
    cout << "9. Exit" << endl;
    cout << "#############################" << endl;
}

int getIdx() {
    int idx;

    cout << "Id of set: ";
    cin >> idx;
    if( idx < 0 || idx >= NUMBER_OF_SETS ) {
        cerr << "Err: Invalid index! Must be integer between 0 and " << NUMBER_OF_SETS - 1 << ". Abort" << endl;
        abort();
    }
    return idx;
}

int getValue() {
    int value;
    cout << "Value: ";
    cin >> value;
    if(!cin) {
        cerr << "Err: Invalid input! Expected integer... Abort" << endl;
        abort();
    }
    return value;
}

bool askSave() {
    char ans;
    cout << "Save result [y/n]? ";
    cin >> ans;
    if(!cin) {
        cerr << "Err: Invalid input! Expected character... Abort" << endl;
        abort();
    }
    if(ans == 'y' || ans == 'Y')
        return true;
    else
        return false;
}


int main() {
    int choice = 0;
    int opt1, opt2;
    RealSet sets[NUMBER_OF_SETS];

    printHelp();
    while(choice != M_EXIT)
    {
        cout << "> ";
        cin >> choice;
        switch(choice) {
            case M_APPEND:
                opt1 = getIdx();
                sets[opt1].append(getValue());
                cout << "Done!" << endl;
                break;
            case M_REMOVE:
                opt1 = getIdx();
                sets[opt1].remove(getValue());
                cout << "Done!" << endl;
                break;
            case M_LENGTH:
                opt1 = getIdx();
                cout << "Length of #" << opt1 << ": " << sets[opt1].getLength() << endl;
                break;
            case M_PRINT:
                opt1 = getIdx();
                cout << "Set #" << opt1 << ": " << sets[opt1] << endl;
                break;
            case M_UNION:
                opt1 = getIdx();
                opt2 = getIdx();
                if(askSave()) {
                    sets[opt1] += sets[opt2];
                    cout << "Done! Result stored in #" << opt1 << endl;
                } else {
                    RealSet res = sets[opt1] + sets[opt2];
                    cout << "Result: " << res << endl;
                }
                break;
            case M_DIFF:
                opt1 = getIdx();
                opt2 = getIdx();
                if(askSave()) {
                    sets[opt1] -= sets[opt2];
                    cout << "Done! Result stored in #" << opt1 << endl;
                } else {
                    RealSet res = sets[opt1] - sets[opt2];
                    cout << "Result: " << res << endl;
                }
                break;
            case M_INTER:
                opt1 = getIdx();
                opt2 = getIdx();
                if(askSave()) {
                    sets[opt1] *= sets[opt2];
                    cout << "Done! Result stored in #" << opt1 << endl;
                } else {
                    RealSet res = sets[opt1] * sets[opt2];
                    cout << "Result: " << res << endl;
                }
                break;
            case M_EQ:
                opt1 = getIdx();
                opt2 = getIdx();
                if(sets[opt1] == sets[opt2])
                    cout << "Sets #" << opt1 << " and #" << opt2 << " are IDENTICAL" << endl;
                else
                    cout << "Sets #" << opt1 << " and #" << opt2 << " are DIFFERENT" << endl;
                break;
            case M_EXIT:
                break;
            default:
                cerr << "Err: Unknown option!" << endl;
                cin.clear();
                cin.ignore(INT16_MAX, '\n');    // Remove invalid character from stdin
        }
    }
    return 0;
}

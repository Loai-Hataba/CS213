#ifndef MENU_H
#define MENU_H
using namespace std;
#include "Headers.h"
#include "Machine.h"

class Menu{
    public:
        void displayMenu();
        string GetFile();
        vector<string> ExtractInst();

};

#endif

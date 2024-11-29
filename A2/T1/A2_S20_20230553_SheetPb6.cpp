#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
#include <map>
#include <set>
#include <chrono>
#include <cctype>
#include <thread>
#include <limits>

using namespace std;
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define RESET_BOLD "\033[22m"
#define ALIVE "\u25A0"
#define DEAD "\u25A1"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

class Universe
{
private:
    vector<vector<bool>> grid;
    int gridSize = 30;
    set<pair<int, int>> aliveCells;      // alive cells and potentially affected cells
    map<pair<int, int>, int> countCells; // neighboring to active cells
    map<pair<int, int>, bool> nextState; // next state

public:
    bool finishGame = false;
    void initialize();
    void potentiallyAffected();
    void countNeighbors();
    void nextGeneration();
    void selectCells(int row, int column);
    void display();
    void screen();
};

void Universe::initialize()
{
    grid = vector<vector<bool>>(gridSize, vector<bool>(gridSize, false));
}

void Universe::potentiallyAffected()
{

    if (aliveCells.empty())
    {
        finishGame = true;
        return;
    }
    set<pair<int, int>> temp;
    for (const auto &coordinate : aliveCells)
    {
        int x = coordinate.first;
        int y = coordinate.second;
        for (int i = x - 1; i <= x + 1; i++)
        {
            for (int j = y - 1; j <= y + 1; j++)
            {
                if (i >= 0 && i < grid.size() && j >= 0 && j < grid.size())
                {
                    temp.insert({i, j});
                }
            }
        }
    }
    aliveCells = temp;
}

void Universe::countNeighbors()
{
    countCells.clear();
    for (const auto &coordinates : aliveCells)
    {
        int x = coordinates.first;
        int y = coordinates.second;
        int count = 0;
        for (int i = x - 1; i <= x + 1; i++)
        {
            for (int j = y - 1; j <= y + 1; j++)
            {
                if (i >= 0 && i < grid.size() && j >= 0 && j < grid.size())
                {
                    if (i == x && j == y)
                        continue; // same cell
                    if (grid[i][j])
                        count++;
                }
            }
        }
        countCells[{x, y}] = count;
    }
}

void Universe::nextGeneration()
{
    nextState.clear();
    for (const auto &coordinates : countCells)
    {
        int x = coordinates.first.first;
        int y = coordinates.first.second;
        int neighborCount = coordinates.second;
        if (grid[x][y]) // alive
        {
            if (neighborCount < 2 || neighborCount > 3) // overpopulation or underpopulation
            {
                nextState[{x, y}] = false; // population dies
            }
            else
            {
                nextState[{x, y}] = true; // population lives
            }
        }
        else // dead
        {
            if (neighborCount == 3) // reproduction
            {
                nextState[{x, y}] = true; // population lives
            }
        }
    }
    aliveCells.clear();
    for (const auto &i : nextState)
    {
        int x = i.first.first;
        int y = i.first.second;
        bool state = i.second;
        grid[x][y] = state;
        if (state)
            aliveCells.insert({x, y});
    }
}

void Universe::selectCells(int row, int column)
{
    if (row >= 0 && row < grid.size() && column >= 0 && column < grid[0].size())
    {
        grid[row][column] = !grid[row][column]; // Toggle cell state
        if (grid[row][column])
        {
            aliveCells.insert({row, column}); // add cell coordinates to set
        }
        else
        {
            aliveCells.erase({row, column}); // delete cell coordinates from set
        }
    }
}

void Universe::display()
{
    system("cls"); // Clear the screen
    for (const auto &row : grid)
    {
        for (const auto &cell : row)
        {
            if (cell)
            {
                cout << YELLOW << ALIVE << RESET << " ";
            }
            else
            {
                cout << DEAD << " ";
            }
        }
        cout << endl;
    }
};

void Universe::screen()
{
    int cursorRow = 0, cursorCol = 0;

    while (true)
    {
        system("cls"); // Clear the screen
        // Display grid with cursor
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (i == cursorRow && j == cursorCol)
                    cout << "X "; // Cursor
                else
                {
                    if (grid[i][j])
                    {
                        cout << YELLOW << ALIVE << RESET << " ";
                    }
                    else
                    {
                        cout << DEAD << " ";
                    }
                }
            }
            cout << endl;
        }

        cout << "Use " << BOLD << "WASD" << RESET_BOLD << " Keys to move, SPACE to toggle, ENTER to finish.\n";

        // Capture keyboard input
        char ch = _getch(); // Get input character
        if (ch == 'w' && cursorRow > 0)
            cursorRow--;
        else if (ch == 's' && cursorRow < grid.size() - 1)
            cursorRow++;
        else if (ch == 'a' && cursorCol > 0)
            cursorCol--;
        else if (ch == 'd' && cursorCol < grid[0].size() - 1)
            cursorCol++;
        else if (ch == ' ')
            selectCells(cursorRow, cursorCol);
        else if (ch == '\r')
        {
            break;
        }
    }
}

int main()
{
    system("cls");
    cout << "                                       ////////////////////////////////////////////////////////////////\n";
    cout << "                                       //" << RED << "  ____                               __   _     _  __       " << RESET << "//\n";
    cout << "                                       //" << YELLOW << " / ___| __ _ _ __ ___   ___    ___  / _| | |   (_)/ _| ___  " << RESET << "//\n";
    cout << "                                       //" << BLUE << "| |  _ / _` | '_ ` _ \\ / _ \\  / _ \\| |_  | |   | | |_ / _ \\ " << RESET << "//\n";
    cout << "                                       //" << GREEN << "| |_| | (_| | | | | | |  __/ | (_) |  _| | |___| |  _|  __/ " << RESET << "//\n";
    cout << "                                       //" << CYAN << " \\____|\\__,_|_| |_| |_|\\___|  \\___/|_|   |_____|_|_|  \\___| " << RESET << "//\n";
    cout << "                                       ////////////////////////////////////////////////////////////////\n\n\n";

    double time;
    while (true)
    {
        cout << "Enter time (Speed) between every frame: ";
        cin >> time;
        if (cin.fail())
        {
            cout << "Input failed. Please enter a valid number." << endl;
            cin.clear();                                         // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        }
        else
            break;
    }
    int timeMS = int(time * 1000); // milliseconds
    this_thread::sleep_for(std::chrono::milliseconds(timeMS));
    system("chcp 65001 > nul"); // for character formatting purposes
    while (true)
    {
        cout << "\n\n"
             << BOLD << "Loading...\n\n"
             << RESET_BOLD;
        this_thread::sleep_for(chrono::milliseconds(1000));
        Universe universe;
        universe.initialize();       // initialize grid
        universe.screen();           // choose alive cells
        while (!universe.finishGame) // game not finished
        {
            universe.potentiallyAffected(); // find active and potentially affected cells
            if (universe.finishGame)        // no cells left
                break;
            universe.countNeighbors(); // count neighbors for all active and potential cells
            universe.nextGeneration(); // next generation run

            universe.display();
            this_thread::sleep_for(chrono::milliseconds(timeMS));
        }
        cout << "\nThanks for Playing!!\n Do you want to Play again?? (Exit (E), Play again (P)) " << endl;
        while (true)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string input;
            getline(cin, input);

            if (input.size() != 1)
            {
                cout << "Invalid input. Enter a single character (E or P).\n";
                continue;
            }
            char choice = toupper(input[0]); // Convert to uppercase for consistency
            switch (choice)
            {
            case 'P':
                break;
            case 'E':
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
            }
            break;
        }
        cout << "restarting...\n";
    }
}

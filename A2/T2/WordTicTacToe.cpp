#include "WordTicTacToe.h"
#include "Methods.h"

void WordSetPlayerType(Player<char> *&player, int choice, string name, char symbol = ' ')
{
    switch (choice)
    {
        case 1:
            player = new WordPlayer<char>(name, symbol);
            break;
        case 2:
            player = new WordRandomPlayer<char>(name, symbol);
            break;
        default:
            cout << "Invalid choice!" << endl;
            player = nullptr;
            break;
    }
}
void WordInfo()
{
    cout << "======================= Welcome to The Words Tic Tac Toe Game  ==================\n";
    cout << "An innovative twist to the classic game, instead of 'X' and 'O', player place letter on a 3x3 grid.\n";
    cout << "This adds a linguistic challenge to the traditional game mechanics.\n\n";
    cout << "Rules:\n";
    cout << "  - Players aim to form a valid word with the letters they place on the board.\n";
    cout << "  - Words can be formed horizontally, vertically, or diagonally.\n\n";
    cout << "Winning:\n";
    cout << "  - The first player to get three-in-a-row vertically, horizontally, or diagonally wins.\n";
    cout << "===========================================================================\n\n";
    cin.ignore();
    cin.clear();
}

void WordTicTacToe()
{
    auto *B = new WordBoard<char>();
    Player<char> *players[2] = {nullptr, nullptr};
    WordInfo();
    //// Set Player one
    string player1Name = getPlayerName(1);
    int choice = getPlayerType();
    WordSetPlayerType(players[0], choice, player1Name);
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2);
    choice = getPlayerType();
    WordSetPlayerType(players[1], choice, player2Name);
    GameManager<char> Word_GameManger(B, players);
    Word_GameManger.run();
    for (auto &player : players)
    {
        delete player;
    }
}

vector<string> loadDictionary(string filename) {
    vector<string> dictionary;
    ifstream file(filename);
    string word;
    while (file >> word) {
        dictionary.push_back(word);
    }
    return dictionary;
}

bool isValidWord(string word, const vector<string>& dic) {
    auto it = find(dic.begin(), dic.end(), word);
    if (it != dic.end()) {
        return true;
    } else {
        return false;
    }
}

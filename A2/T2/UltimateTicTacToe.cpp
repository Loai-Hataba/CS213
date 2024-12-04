// #include<UltimateTicTacToe.h>
// void setPlayerType(Player<char>*& player, int choice, string name, int symbol) {
//     switch (choice) {
//         case 1:
//             player = new UltimateTicTacToe_Player<char>(name, symbol);
//         break;
//         case 2:
//             player = new UltimateTicTacToe_Random<char>(name, symbol);
//         break;
//         case 3:
//             cout << "AI Player (not implemented)" << endl;
//         player = nullptr; // Placeholder if AI is not implemented
//         break;
//         default:
//             cout << "Invalid choice!" << endl;
//         player = nullptr;
//         break;
//     }
// }
// void UltimateTicTacToe()
// {
//     Player<char>* players[2] = {nullptr, nullptr};
//     auto* B = new <char>();
//     displayUltimateTicTacToeInfo();
//     ///////////////////////////////////////////////////////////////
//     ///// Symbol 0 --> even / symbol --> 1 --> odd numbers
//     /////Setting Player 1
//     string player1Name = getPlayerName(1) ;
//     int choice = getPlayerType();
//     setPlayerType(players[0], choice, player1Name, 'X');
//     /////////////////////////////////////////////////////////////
//     ///Setting Player 2
//     cin.ignore();
//     string player2Name = getPlayerName(2) ;
//     choice = getPlayerType();
//     setPlayerType(players[1], choice, player2Name, 'O');
//     ////////////////////////////////////////////////////////////////
//     GameManager<char> NumTicTacToe (B, players);
//     NumTicTacToe.run();
//     for (auto & player : players) {
//         delete player;
//     }
// }
//
// void displayUltimateTicTacToeInfo() {
//     cout << "           ===== Welcome to Ultimate Tic Tac Toe =====\n" << endl;
//     cout << " Ultimate Tic Tac Toe is an expansion of the classic game, adding layers\n";
//     cout << " of complexity by combining multiple Tic Tac Toe boards into one.\n\n";
//
//     cout << " +----------------------------------------------------+\n";
//     cout << " |                      Gameplay                      |\n";
//     cout << " +----------------------------------------------------+\n";
//     cout << " | The game is played on a large 3x3 grid.            |\n";
//     cout << " | Each cell in the large grid contains a smaller     |\n";
//     cout << " | 3x3 Tic Tac Toe board.                             |\n";
//     cout << " | Player 1 uses \"X\", and Player 2 uses \"O\".           |\n";
//     cout << " | Players take turns choosing a cell within a        |\n";
//     cout << " | smaller board to play their symbol.                |\n";
//     cout << " | The first move can be made on any smaller board.   |\n";
//     cout << " | Subsequent moves direct the opponent to a          |\n";
//     cout << " | specific smaller board based on the cell chosen.   |\n";
//     cout << " +----------------------------------------------------+\n";
//
//     cout << " +----------------------------------------------------+\n";
//     cout << " |                       Rules                        |\n";
//     cout << " +----------------------------------------------------+\n";
//     cout << " | The winner of a smaller board claims that space    |\n";
//     cout << " | on the main board. Their symbol replaces the       |\n";
//     cout << " | smaller board on the main grid.                    |\n";
//     cout << " | To win the game, a player must win three smaller   |\n";
//     cout << " | boards in a row (horizontal, vertical, or diagonal)|\n";
//     cout << " | on the main 3x3 grid.                              |\n";
//     cout << " | If all smaller boards are claimed and no player    |\n";
//     cout << " | has three in a row on the main board, the game     |\n";
//     cout << " | ends in a draw.                                    |\n";
//     cout << " +----------------------------------------------------+\n";
//
//     cout << " +----------------------------------------------------+\n";
//     cout << " |                     Strategy                       |\n";
//     cout << " +----------------------------------------------------+\n";
//     cout << " | Be strategic in your moves! Winning smaller        |\n";
//     cout << " | boards is crucial, but sending your opponent to    |\n";
//     cout << " | unfavorable boards can also be a powerful tactic.  |\n";
//     cout << " | Think about the bigger picture while playing       |\n";
//     cout << " | each smaller game of Tic Tac Toe.                  |\n";
//     cout << " +----------------------------------------------------+\n";
//
//     cout << "\n                  Let the ultimate game begin!\n";
// }
//

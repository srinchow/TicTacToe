#include "tic_tac_toe.h"
#include <cctype> 
#include <iostream>

namespace tic_tac_toe
{
    constexpr Player TicTacToe::players[2];
    constexpr char TicTacToe::emptyToken;

    int Player::select(const TicTacToe &board) const {  
        while (true) {
            int answer = get_user_input(prompt)-1;
            if (!board.occupied(answer)) 
                return answer;
            std::cout << "Invalid input; try again\n";
        } 
        return 0;  // should never get here!
    }

    void TicTacToe::print_state_of_board() const {
        auto col{3};
        for (std::size_t i = 0; i < m_board.size(); ++i) {
            std::cout << '|' << m_board.at(i);
            if (--col == 0) {
                std::cout << "|\n";
                col = 3;
            }
        }
    }

    bool TicTacToe::isWin() const {
        static constexpr std::array<std::array<int, 3>, 8> combinations{{ 
                {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6},
                {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}
        }};
        for (const auto& combination : combinations) {
            if (m_board.at(combination[0]) == players[player].token &&
                    m_board.at(combination[1]) == players[player].token &&
                    m_board.at(combination[2]) == players[player].token) 
            {
                return true;
            }
        }       
        return false;
    }

    void TicTacToe::input(int player) {
        m_board[players[player].select(*this)] = players[player].token;
        ++turn_count;
    }
    void TicTacToe::play() {
        for (bool ingame = true; ingame; player = 1 - player) {
            print_state_of_board();
            input(player);
            if (isWin()) {
                std::cout << players[player].winmsg << '\n';
                ingame = false;
            } else if (isTie()) {
                std::cout << "Draw!\n";
                ingame = false;
            }
        }
    }

    int get_user_input(const std::string& user_message)
    {
        while (true) {
            std::cout << user_message;
            std::string input;
            std::cin >> input;
            try {
                return std::stoi(input);
            }
            catch (std::invalid_argument&) {
                std::cout << "\nInput is not a number. Try again:";
            }
        }
    }

    void play_game() {
        for (bool gaming{true}; 
            gaming; 
            gaming = get_user_input("Play again[Yes = 1, No = 0]: ") == 1)
        {
            TicTacToe game;
            game.play();
        }
    }
}
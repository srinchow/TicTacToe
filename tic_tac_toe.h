#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <array>
#include <string>

namespace tic_tac_toe
{
    class TicTacToe;

    class Player {
    public:
        constexpr Player(char token, const char* winmsg, const char* prompt) : 
            token{token}, 
            winmsg{winmsg},
            prompt{prompt}
        {}
        int select(const TicTacToe &board) const; 
        const char token;
        const char *winmsg;
        const char *prompt;
    };

    class TicTacToe final { 
    public:
        TicTacToe() {
            m_board.fill(emptyToken);
        }
        void play(); 
        bool occupied(unsigned square) const {
            return square >= num_squares || m_board[square] != emptyToken;
        }
        static constexpr int num_squares{9};
        static constexpr char emptyToken{' '};
    private:
        void print_state_of_board() const;
        bool isWin() const;
        void input(int player);
        bool isTie() const {
            return turn_count >= num_squares;
        }

        static constexpr Player players[2] = { 
            { 'X', "X Wins!", "1[X]:" },
            { 'O', "O Wins!", "2[O]:" },
        };
        int turn_count = 0;
        int player = 0;
        std::array<char, num_squares> m_board;
    };

    int get_user_input(const std::string& user_message);
    void play_game();   
}
#endif
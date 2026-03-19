#include <vector>
#include <random>
#include <Minesweeper/minesweeper.h>

std::random_device r;
std::mt19937 Minesweeper::rng(r());
std::uniform_real_distribution<double> Minesweeper::chance(0.0, 1.0);

Minesweeper::Minesweeper(const int& width, const int& height, const double& mine_rate) 
        : w(width), h(height), mine_count(static_cast<int>(w * h * mine_rate)){
    const int max_size = w*h;
    double mines_left = static_cast<double>(mine_count);
    mines = new bool[max_size]();
    clues = new unsigned short[max_size]();
    for (int i = 0; i < max_size; i++){
        if (chance(rng) > mines_left / (max_size - i)) {
            mines_left--;
            mines[i] = true;
            for (int x = -1; x <= 1; x++){
                for (int y = -1; y <= 1; y++){
                    int pos = i + x + w*y;
                    if (pos < max_size && pos >= 0) clues[i]++;
                }
            }
        }
    }
}

Minesweeper::~Minesweeper(){
    delete[] clues;
    delete[] mines;
}

bool Minesweeper::mine(const int& x, const int& y){
    int pos = x + w*y;
    if (pos < w*h && pos >= 0) return mines[pos];
    else throw pos;
}

unsigned short Minesweeper::clue(const int& x, const int& y){
    int pos = x + w*y;
    if (pos < w*h && pos >= 0) return clues[pos];
    else throw pos;
}
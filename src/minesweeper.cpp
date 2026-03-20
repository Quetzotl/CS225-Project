#include <vector>
#include <random>
#include <SDL3/SDL_log.h>
#include <Minesweeper/minesweeper.h>

Minesweeper::Minesweeper(const int& width, const int& height, const double& mine_rate) 
        : w(width), h(height), mine_count(static_cast<int>(w * h * mine_rate)){
    const int max_size = w*h;
    double mines_left = static_cast<double>(mine_count);
    mines = new bool[max_size]();
    clues = new unsigned short[max_size]();
    for (int i = 0; i < max_size; i++){
        if (roll() < mines_left / (max_size - i)) {
            mines_left--;
            mines[i] = true;
            for (int x = -1; x <= 1; x++){
                for (int y = -1; y <= 1; y++){
                    int pos = i + x + w*y;
                    if (i%w + x >= w || i%w + x < 0) continue;
                    if (i/w + y >= h || i/w + y < 0) continue;
                    clues[i + x + w*y]++;
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

double Minesweeper::roll(){
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}
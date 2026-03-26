#include <vector>
#include <fstream>
#include <iomanip>
#include <SDL3/SDL_log.h>
#include <algorithm>
#include <Minesweeper/leaderboard.h>

Counter::Counter() : value(0) { }

Counter& Counter::operator+=(const int& n){
    value += n;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Counter& n){
    out << n() / 60000 << ':' << std::setw(2) << std::setfill('0') << (n() / 1000) % 60;
    return out;
}

Score::Score(const Counter& source) : Counter(source) { }

Score::Score(const int& score) {
    value = (score / 100) * 25000000;
}

std::ostream& operator<<(std::ostream& out, const Score& n){
    out << 100 * (25000000 / n());
    return out;
}

Leaderboard::Leaderboard(const char* file) : filename(file){
    std::ifstream load(filename);
    if (load) {
        int i;
        while (load>>i){
            load>>i;
            scores.push_back(Score(i));
        }
    }
}

Leaderboard::~Leaderboard(){
    std::ofstream f(filename);
    for (int i = 0; i < scores.size(); i++){
        f << i+1 << ' ' << scores[i] << std::endl;
    }
}

void Leaderboard::add_score(const Score& score){
    bool placed = false;
    for (int i = 0; i < scores.size(); i++){
        if (scores[i]() > score()) {
            scores.insert(scores.begin() + i, score);
            placed = true;
            break;
        }
    }
    if (scores.size() < MAX_LEADERBOARD_SIZE){
        if (!placed) scores.push_back(score);
    } else scores.resize(MAX_LEADERBOARD_SIZE);
}
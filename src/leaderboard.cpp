#include <vector>
#include <fstream>
#include <algorithm>
#include <Minesweeper/leaderboard.h>

Timer::Timer() : ms(0) { }

Timer& Timer::operator+=(const int& n){
    ms += n;
    return *this;
}

Score::Score(const Timer& source) : Timer(source) { }

Score::Score(const int& value) {
    ms = (value / 100) * 25000000;
}

std::ostream& operator<<(std::ostream& out, const Score& n){
    out << 100 * (25000000 / n());
    return out;
}

Leaderboard::Leaderboard(const char* file){
    std::ifstream load(file);
    if (load) {
        int i;
        while (load>>i){
            load>>i;
            scores.push_back(Score(i));
        }
    }
    f.open(file);
}

Leaderboard::~Leaderboard(){
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
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define MAX_LEADERBOARD_SIZE 10

class Timer {
protected:
    std::size_t ms;
public:
    Timer();
    Timer& operator+=(const int& n);
    std::size_t operator()() const { return ms; }
};

class Score : public Timer {
public:
    Score(const Timer& source);
    Score(const int& value);
};

class Leaderboard {
private:
    std::vector<Score> scores;
    std::ofstream f;
public:
    Leaderboard(const char* file);
    ~Leaderboard();
    void add_score(const Score& score);
};

#endif
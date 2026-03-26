#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define MAX_LEADERBOARD_SIZE 10

class Counter {
protected:
    Uint64 value;
public:
    Counter();
    Counter& operator+=(const int& n);
    Uint64 operator()() const { return value; }
    void reset() {value = 0;}
};
std::ostream& operator<<(std::ostream& out, const Counter& n);

class Score : public Counter {
public:
    Score() : Counter() {};
    Score(const Counter& source);
    Score(const int& value);
};
std::ostream& operator<<(std::ostream& out, const Score& n);

class Leaderboard {
private:
    std::vector<Score> scores;
    const char* filename;
public:
    Leaderboard(const char* file);
    ~Leaderboard();
    void add_score(const Score& score);
};

#endif
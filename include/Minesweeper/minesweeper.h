#ifndef MINESWEEPER_H
#define MINESWEEPER_H

class Minesweeper {
public:
    Minesweeper(const int& width, const int& height, const double& mine_rate,
        const int& x, const int& y);
    ~Minesweeper();
    int getMineCount() {return mine_count;}
    bool mine(const int& x, const int& y);
    unsigned short clue(const int& x, const int& y);
    void reset();
private:
    bool* mines;
    unsigned short* clues;
    const int w, h, mine_count;
    static double roll();
};

#endif
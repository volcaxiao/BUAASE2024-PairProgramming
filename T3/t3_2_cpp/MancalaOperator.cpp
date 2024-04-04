#include<cstdint>
#include<cstring>
#include<cassert>
#include<iostream>
using namespace std;

struct Board {
    uint8_t holes1[6];
    uint8_t store1;
    uint8_t holes2[6];
    uint8_t store2;
    uint8_t now_flag;
    enum state {
        ILLEGAL,
        CONTINUE,
        OVER,
    };
    
    Board(uint8_t flag) : now_flag(flag), store1(0), store2(0) {
        for (int i = 0; i < 6; ++i) {
            holes1[i] = 4;
            holes2[i] = 4;
        }
    }

    uint8_t &getFirst(uint8_t flag) {
        return flag == 1 ? store1 : store2;
    }

    uint8_t &getSecond(uint8_t flag) {
        return flag == 1 ? store2 : store1;
    }

    state plant(uint8_t instr) {
        if (instr / 10 != now_flag) {
            return ILLEGAL;
        }
        auto start = now_flag == 1 ? holes1 : holes2;
        auto skip = now_flag == 1 ? &store2 : &store1;
        auto cur = start + instr % 10 - 1;
        if (*cur == 0) {
            return ILLEGAL;
        }
        auto cnt = *cur;
        *cur = 0;
        for (cur++; cnt; cur++) {
            if (cur == holes1 + 14) cur = holes1;
            if (cur == skip) continue;
            (*cur)++;
            cnt--;
        }
        cur--;
        if (cur == &getFirst(now_flag)) {
            return CONTINUE;
        }
        if (auto &opposide = *(holes1 + 12 - (cur - holes1));
        *cur == 1 && cur >= start && cur < start + 6 && opposide != 0)  {
            getFirst(now_flag) += opposide + 1;
            opposide = 0;
            *cur = 0;
        }
        uint8_t sum1 = 0, sum2 = 0;
        for (int i = 0; i < 6; ++i) {
            sum1 += holes1[i];
            sum2 += holes2[i];
        }
        if (sum1 == 0 || sum2 == 0) {
            store1 += sum1;
            store2 += sum2;
            memset(holes1, 0, 6);
            memset(holes2, 0, 6);
            return OVER;
        }
        now_flag = 3 - now_flag;
        return CONTINUE;
    }

    pair<int32_t, int32_t> search(uint8_t depth, int32_t alpha, int32_t beta) {
        if (depth == 0) {
            return { -1, getFirst(now_flag) - getSecond(now_flag) };
        }
        int32_t best = -0x3f3f3f3f;
        int32_t best_instr = -1;
        for (int i = 1; i <= 6; ++i) {
            auto next = *this;
            int32_t score;
            if (auto st = next.plant(now_flag * 10 + i); st == ILLEGAL) {
                continue;
            } else if (st == OVER) {
                score = getFirst(now_flag) - getSecond(now_flag);
            } else if (next.now_flag == now_flag) {
                score = next.search(depth - 1, alpha, beta).second;
            } else {
                score = -next.search(depth - 1, -beta, -alpha).second;
            }
            if (score > best) {
                best = score;
                best_instr = i + now_flag * 10;
            }
            if (score > alpha) {
                alpha = score;
            }
            if (alpha >= beta) {
                break;
            }
        }
        return {best_instr, best};
    }

    uint32_t bestNext() {
        return search(15, -0x3f3f3f3f, 0x3f3f3f3f).first;
    }
};

extern "C"
uint32_t mancalaOperator(Board *board) {
    return board->bestNext();
}


// test
int main() {
    Board board(1);
    Board::state st = Board::CONTINUE;
    while (st != Board::OVER) {
        uint32_t nextStep = mancalaOperator(&board);
        cout << "Player: " << (int) board.now_flag << " nextStep: " << nextStep << endl;
        st = board.plant(nextStep);
        for (int i = 5; i >= 0; --i) {
            cout << " | " << (int) board.holes2[i];
        }
        cout << " | " << endl;
        cout << " | " << (int) board.store2 << " |            " << " | " << (int) board.store1 << " | " << endl;
        for (int i = 0; i < 6; ++i) {
            cout << " | " << (int) board.holes1[i];
        }
        cout << " | " << endl;
    }
}

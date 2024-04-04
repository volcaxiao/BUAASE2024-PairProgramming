#include<cstdint>
#include<cstring>
#include<cassert>

struct Board {
    uint8_t holes1[6];
    uint8_t store1;
    uint8_t holes2[6];
    uint8_t store2;
    int8_t now_flag;
    enum state {
        ILLEGAL,
        CONTINUE,
        OVER,
    };
    

    Board(int32_t flag) : now_flag(flag), store1(0), store2(0) {
        for (int i = 0; i < 6; ++i) {
            holes1[i] = 4;
            holes2[i] = 4;
        }
    }

    uint8_t &getFirst(int32_t flag) {
        return flag == 1 ? store1 : store2;
    }

    uint8_t &getSecond(int32_t flag) {
        return flag == 1 ? store2 : store1;
    }

    state plant(int32_t instr) {
        auto start = now_flag == 1 ? holes1 : holes2;
        auto skip = now_flag == 1 ? &store2 : &store1;
        auto cur = start + instr % 10 - 1;
        // 指令非法：不是自己的回合或者选定点没有豆子
        if (instr / 10 != now_flag || *cur == 0) {
            return ILLEGAL;
        }
        // 指令合法：开始播种
        auto cnt = *cur;
        *cur = 0;
        for (cur++; cnt; cur++) {
            if (cur == holes1 + 14) cur = holes1;
            if (cur == skip) continue;
            (*cur)++;
            cnt--;
        }
        cur--;
        // 检查是否可以吃子
        if (auto &opposide = *(holes1 + 12 - (cur - holes1));
        *cur == 1 && cur >= start && cur < start + 6 && opposide != 0)  {
            getFirst(now_flag) += opposide + 1;
            opposide = 0;
            *cur = 0;
        }
        // 检查是否结束
        int32_t sum1 = 0, sum2 = 0;
        for (int i = 0; i < 6; ++i) {
            sum1 += holes1[i];
            sum2 += holes2[i];
        }
        if (sum1 == 0 || sum2 == 0) {
            store1 += sum1;
            store2 += sum2;
            memset(holes1, 0, sizeof(holes1));
            memset(holes2, 0, sizeof(holes2));
            return OVER;
        }
        // 检查是否额外回合
        if (cur == &getFirst(now_flag)) {
            return CONTINUE;
        }
        now_flag = 3 - now_flag;
        return CONTINUE;
    }
};

extern "C"
int32_t mancalaResult(int32_t flag, int32_t *seq, int32_t size)  {
    Board board(flag);
    for (int i = 0; i < size; ++i) {
        switch (board.plant(seq[i]))
        {
        case Board::ILLEGAL:
            return 30'000 + i;
        case Board::OVER:
            if (i == size - 1)  {
                return 15'000 + board.getFirst(flag) - board.getSecond(flag);
            } else {
                return 30'000 + i + 1;
            }
        }
    }
    return 20'000 + board.getFirst(flag);
}


// test
int main() {
    int32_t seq[] = {11, 12, 13, 14, 15, 16, 21, 22, 23, 24, 25, 26};
    assert(mancalaResult(1, seq, 12) == 30'001);
    int32_t seq2[] = {14, 23, 25, 12, 14, 26, 15, 26, 21, 26, 25, 26, 23, 14, 24, 12, 26, 25};
    assert(mancalaResult(1, seq2, 18) == 15'008);
    assert(mancalaResult(1, seq2, 16) == 20'010);
    return 0;
}

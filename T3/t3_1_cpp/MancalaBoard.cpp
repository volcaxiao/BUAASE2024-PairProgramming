#include<cstdint>
#include<cstring>
#include<cassert>
#include<iostream>

struct Board {
    uint32_t holes1[6];
    uint32_t store1;
    uint32_t holes2[6];
    uint32_t store2;
    uint32_t res_data;
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

    uint32_t &getFirst(int32_t flag) {
        return flag == 1 ? store1 : store2;
    }

    uint32_t &getSecond(int32_t flag) {
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

    void *step(uint8_t flag, uint32_t instr) {
        state plant_res;
        if (flag != now_flag || (plant_res = plant(instr)) == ILLEGAL) {
            res_data = (flag == 1)? (200+2*store1-48) : (248 - 2*store2);
        } else if (plant_res == OVER) {
            res_data = 200 + store1 - store2;
        } else {
            res_data = now_flag;
        }
        return this;
    }
};

extern "C"
int32_t *mancalaBoard(int32_t flag, int32_t *seq, int32_t size)  {
    static Board board(0);
    board = Board(seq[0]/10);
    for (int i = 0; i < size-1; ++i) {
        board.plant(seq[i]);
    }
    return (int32_t *)board.step(flag, seq[size-1]);
}

// test
int main() {
    int32_t seq[] = {14, 23, 25, 12, 14, 26, 15, 26, 21, 26, 25, 26, 23, 14, 24, 12, 26, 25};
    assert(mancalaBoard(2, seq, 18)[14] == 208);
    assert(mancalaBoard(1, seq, 18)[14] == 172);
    assert(mancalaBoard(1, seq, 16)[14] == 2);
    seq[17] = 15;
    assert(mancalaBoard(2, seq, 18)[14] == 224);
    return 0;
}

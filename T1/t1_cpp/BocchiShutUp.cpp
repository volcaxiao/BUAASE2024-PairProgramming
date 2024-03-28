#include <array>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <algorithm>

#if EMSCRIPTEN
#include "emscripten.h"
#define EMS_ALIVE extern "C" EMSCRIPTEN_KEEPALIVE
#else 
#define EMS_ALIVE extern "C"
#endif

EMS_ALIVE
int32_t bocchiShutUp(int32_t flag, int32_t *seq, int32_t size) {
    std::array<int32_t, 7> cnt{};
    int32_t flag10 = flag*10;
    for (auto i = 0; i < size; ++i) {
        int32_t index = seq[i] - flag10;
        if (1 <= index && index <= 6) {
            cnt[index]++;
        }
    }
    auto it1 = std::max_element(cnt.begin(), cnt.end()) - cnt.begin();
    auto it2 = std::max_element(cnt.rbegin(), cnt.rend()) - cnt.rbegin();
    it2 = 6 - it2;

    return (it1 == it2) ? it1 + flag10 : 10;
}

EMS_ALIVE
void *allocArray(int32_t size) {
    return malloc(sizeof(int32_t) * size);
}

EMS_ALIVE
void freeArray(int32_t *ptr) {
    free(ptr);
}

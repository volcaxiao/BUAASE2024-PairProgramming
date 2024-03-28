#include <array>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <algorithm>

extern "C"
int64_t bocchiShutUp(int32_t flag, void * seq_a, int32_t size) {
    std::array<int32_t, 7> cnt{};
    int32_t flag10 = flag*10;
    int32_t *seq = (int32_t*)seq_a;
    for (auto i = 0; i < size; ++i) {
        int32_t index = seq[i] - flag10;
        if (1 <= index && index <= 6) {
            cnt[index]++;
        }
    }
    auto it1 = std::max_element(cnt.begin(), cnt.end()) - cnt.begin();
    auto it2 = std::max_element(cnt.rbegin(), cnt.rend()) - cnt.rbegin();
    it2 = 6 - it2;
    // std::cout << it1 << " " << it2 << std::endl;

    // return (it1 == it2) ? it1 + flag10 : 10;
    int64_t ans = 0;
    for (auto i = 0; i < size; ++i) ans = ans * 100 + seq[i];
    return ans;
}

// int main() {
//     int32_t arr[] = {13,14,13,11,21,13,21,22};
//     std::cout << bocchiShutUp(1, arr, 8) << std::endl;
// }

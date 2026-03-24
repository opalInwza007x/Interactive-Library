#include "detective.h"
#include <cassert>
#include <cstdio>
#include <vector>

static int N;
static const int Q = 67;
static int counter = 0;
static std::vector<int> hidden;
static std::vector<long long> pref;
static int missing_value;

long long query(int l, int r) {
    assert(0 <= l && l <= r && r < N);
    assert(++counter <= Q);
    return pref[r + 1] - pref[l];
}

int main() {
    assert(std::scanf("%d", &N) == 1);

    hidden.resize(N);
    for (int i = 0; i < N; i++) {
        assert(std::scanf("%d", &hidden[i]) == 1);
        assert(0 <= hidden[i] && hidden[i] <= N);
    }

    pref.resize(N + 1);
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        pref[i + 1] = pref[i] + hidden[i];
    }

    std::vector<int> seen(N + 1, 0);
    for (int i = 0; i < N; i++) {
        seen[hidden[i]]++;
        assert(seen[hidden[i]] == 1);
    }

    int cnt_missing = 0;
    for (int i = 0; i <= N; i++) {
        if (!seen[i]) {
            missing_value = i;
            cnt_missing++;
        }
    }
    assert(cnt_missing == 1);

    int ans = findMissing(N);

    if (ans == missing_value) {
        std::printf("Correct %d\n", ans);
        return 0;
    }
    else {
        std::printf("Incorrect\n");
        return 0;
    }
}
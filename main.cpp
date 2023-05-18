#include <iostream>
#include <chrono>

bool turn_week(long long int& k, long long int& m, long long int& r, uint64_t& d_cnt, uint32_t& d) {
    for (int i = 0; i <= 7; i++) {
        if (d < 6) m += k;
        r++;
        m -= r;
        if (m < 0) {
            std::cout << d_cnt << "\n";
            return false;
        }
        d_cnt++;
        d++;
        if (d > 7) d = 1;
    }
    return true;
}

int main() {
    uint32_t d;
    long long int k, m;
    std::cin >> k >> m >> d;
    long long int readed = 0;
    uint64_t d_cnt = 0;
    auto start = std::chrono::steady_clock::now();
    while(true) {


        if (m + 5 * k < readed * 7 + 28) {
            for (int i = 0; i <= 7; i++) {
                if (d < 6) m += k;
                readed++;
                m -= readed;
                if (m < 0) {
                    std::cout << "day: " << d_cnt << "\n";
                    auto end = std::chrono::steady_clock::now();
                    auto diff = end - start;
                    std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
                    return 0;
                }
                d_cnt++;
                d++;
                if (d > 7) d = 1;
            }
        }
        else {
//            std::cout << "week: " << d_cnt/7 << std::endl;
            m += (5 * k) - (readed * 7 + 28);
            std::cout << "day:" << d_cnt << " m:" << m << std::endl;
            d_cnt += 7;
            readed += 7;
        }
    }
    return 0;
}

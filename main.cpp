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
    auto start = std::chrono::steady_clock::now();
    long long int week = ((5.0/7.0)*k - 4)/7.0;
//    while(true) {
    if ((5.0/7.0)*k - 4 >= 1) {
        readed = 2*week*7;
        m += 5*k*2*week - (7*readed + 28);
        std::cout << "readed:" << readed - 1 << " m:" << m << std::endl;
    }
    for (int i = 0; i <= 7; i++) {
        if (d < 6) m += k;
        readed++;
        m -= readed;
        std::cout << m << " " << readed << std::endl;
        if (m < 0) {
            std::cout << "day: " << readed - 1 << "\n";
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
            return 0;
        }
        d++;
        if (d > 7) d = 1;
    }

//        if ((5.0/7.0)*k - 4 < 1) {

//        }
//        else {
////            std::cout << "week: " << week << std::endl;
////            return 0;
//            readed = week*7;
//            m += 5*k*week - (7*readed + 28);

//            std::cout << "day:" << d_cnt << " m:" << m << std::endl;
//        }
//    }
    return 0;
}
//1000000000 1000000000 1

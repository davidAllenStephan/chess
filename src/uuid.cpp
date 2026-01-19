// Source - https://stackoverflow.com/a
// Posted by CaptainCodeman
// Retrieved 2026-01-18, License - CC BY-SA 4.0

#include "../include/uuid.hpp"
#include <random>
#include <string>
using namespace std;

string get_uuid() {
        static random_device dev;
        static mt19937 rng(dev());

        uniform_int_distribution<int> dist(0, 15);

        const char *v = "0123456789abcdef";
        const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

        string res;
        for (int i = 0; i < 16; i++) {
                if (dash[i])
                        res += "-";
                res += v[dist(rng)];
                res += v[dist(rng)];
        }
        return res;
}

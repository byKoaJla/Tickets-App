#pragma once

#include <vector>

namespace Navigation {
    using namespace std;

    struct NavPoint {
        int id;
        bool (*nav)();
    };

    void show(const vector<NavPoint> &points);
};
#include <array>

std::array a {1, 2};

static_assert(std::same_as<decltype(a), std::array<int, 2>>);

std::array b {1.0, 2.0, 3.0};

static_assert(std::same_as<decltype(b), std::array<double, 3>>);
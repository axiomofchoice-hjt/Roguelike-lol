#include "basic.h"

#include <ctime>

namespace Rand {
std::mt19937_64 gen(time(nullptr));

int d(int mod) { return gen() % mod; }
float f() { return gen() / float(gen.max()); }
float f(float l, float r) { return f() * (r - l) + l; }
}  // namespace Rand
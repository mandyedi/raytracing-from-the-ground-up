#include <cstdlib>

inline void
set_rand_seed(const int seed) {
	srand(seed);
}

inline int
rand_int(void) {
	return (rand());
}

inline float
rand_float(void) {
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}
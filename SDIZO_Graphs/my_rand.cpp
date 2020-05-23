#include "my_rand.h"
#include <cstdlib>

int my_rand::random_int(int min_inc, int max_exc)
{
	return (rand() % (max_exc - min_inc)) + min_inc;
}

double my_rand::random_percent(int min_inc, int max_exc)
{
	return double(random_int(min_inc, max_exc)) / 100.0;
}

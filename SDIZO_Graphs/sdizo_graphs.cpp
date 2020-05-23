#include <iostream>
#include "program.h"
#include <ctime>

int main()
{
	srand(unsigned(time(nullptr)));
	auto p = new program();

	p->run();

	delete p;
}

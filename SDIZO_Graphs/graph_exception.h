#pragma once
#include <exception>

class graph_exception : public std::exception
{
public:
	graph_exception(const char* msg) : std::exception(msg) {}
};
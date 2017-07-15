#pragma once

#include <exception>
#include <sstream>
#include <iostream>

void __shutdown(bool b, const char* msg, const char* file, int line) 
{
	std::ostringstream stream;
	stream << "Crash :" <<  msg << " (" << file << ", line : " << line << ")";
	std::cout << stream.str() << std::endl;
	abort();
}

#define verify(expr) \
	if(!(expr)) __shutdown(expr, #expr, __FILE__, __LINE__);

#ifdef _DEBUG
#define check(expr) verify(expr)
#else
#define check(expr) 
#endif


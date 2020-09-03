#pragma once
#include <cstddef>

#define DO_CHECK(EXPR) Test::check(EXPR, __PRETTY_FUNCTION__, __FILE__, __LINE__)

class Test{
protected:
	static int failed_num;
	static int total_num;

	static void check(bool expr, const char *func, const char *filename, size_t lineNum);
public:
	static bool show_final_results();
	virtual void Run_all_tests() const = 0;		
}; 

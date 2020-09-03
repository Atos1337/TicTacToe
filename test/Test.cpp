#include "Test.h"
#include <cstdio>
#include <cassert>

static void check_output(int return_code) {
	if (return_code < 0) {
		throw 1;
	}
}

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
	total_num++;
	if (!expr) {
		check_output(printf("FAILED in %s %s line %zu\n", filename, func, lineNum));
		failed_num++;
	}
}

bool Test::show_final_results() {
	check_output(printf("Success: %d\n", total_num - failed_num));
	if (failed_num != 0) {
		check_output(printf("Failed: %d\nNot passed\n", failed_num));
		return 0;
	}
	check_output(printf("All passed!\n"));
	return 1;
}
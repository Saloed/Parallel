#include <hayai/hayai.hpp>
#include "test_data.h"
#include "sequential/test.h"
#include "openmp_bf/test.h"
#include "pthread_bf/test.h"
#include "test_correctness.h"

int main() {
    test_correctness();
    return 0;

    TestData<SMALL_SIZE>::generate();
    TestData<GREAT_SIZE>::generate();

    hayai::ConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();

    TestData<SMALL_SIZE>::free();
    TestData<GREAT_SIZE>::free();

    return 0;
}

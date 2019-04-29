#include <hayai/hayai.hpp>
#include "sequential/test.h"
#include "openmp_bf/test.h"
#include "pthread_bf/test.h"
//#include "test_correctness.h"

int main() {
    hayai::ConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}

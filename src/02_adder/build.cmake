set (CTEST_SOURCE_DIRECTORY ".")
set (CTEST_BINARY_DIRECTORY "buildCoverage")

set (ENV{CXXFLAGS} "--coverage")
set (ENV{CFLAGS} "--coverage")
set (CTEST_CMAKE_GENERATOR "Unix Makefiles")
set (CTEST_USE_LAUNCHERS 1)

set (CTEST_COVERAGE_COMMAND "gcov")
set (CTEST_MEMORYCHECK_COMMAND "valgrind")

ctest_start ("Continuous")
ctest_configure ()
ctest_build ()
ctest_test ()
ctest_coverage ()
#ctest_memcheck ()
# ctest_submit ()


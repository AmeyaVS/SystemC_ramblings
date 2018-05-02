#!/bin/bash

PROJECT_NAME=$1

# Build the Library and tests with coverage flags enabled.
echo "========================================"
echo " Building the project: $PROJECT_NAME"
echo "========================================"
ctest -S build.cmake

# Clear the execution run of the tests with collected data.
echo "========================================"
echo " Clearing Old Coverage Data."
echo "========================================"
lcov -z -d .

# Capture the initial coverage data with branch coverage
# Options:
#    -i: Initial Coverage
#    -c: Capture the Coverage data
#    -d: Project Base Directory
#    -o: Output Directory
#    --rc <key:value>: specify the config value for lcov.
#                      lcov_branch_coverage=1
echo "========================================"
echo " Capture Zero Run Coverage Data."
echo "========================================"
lcov \
  -i \
  -c \
  -d . \
  -o buildCoverage/${PROJECT_NAME}ZeroCoverage.info

# Run the tests again.
echo "========================================"
echo " Run the Unit tests."
echo "========================================"
ctest -S build.cmake

# Capture the runtime coverage data.
echo "========================================"
echo " Capture Run-Time Coverage Data."
echo "========================================"
lcov \
  -c \
  -d . \
  -o buildCoverage/${PROJECT_NAME}Coverage.info \
  --rc lcov_branch_coverage=1

# Combine Zero Run Coverage with run-time coverage information.
echo "========================================"
echo " Merge the Coverage Data."
echo "========================================"
lcov \
  -a \
  buildCoverage/${PROJECT_NAME}ZeroCoverage.info \
  -a \
  buildCoverage/${PROJECT_NAME}Coverage.info     \
  -o buildCoverage/${PROJECT_NAME}.info \
  --rc lcov_branch_coverage=1

# Generate HTML report
echo "========================================"
echo " Generate the HTML Coverage Report."
echo "========================================"
genhtml \
  -o buildCoverage/${PROJECT_NAME}HTML \
  buildCoverage/${PROJECT_NAME}.info \
  --rc genhtml_branch_coverage=1 \
  --demangle-cpp

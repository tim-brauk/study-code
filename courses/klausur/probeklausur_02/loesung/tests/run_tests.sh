#!/usr/bin/env bash
# Builds the Musterloesung strictly, runs the unit tests and compares the output of main.cpp
# with expected_main_output.txt. Run from anywhere: bash tests/run_tests.sh
set -euo pipefail

cd "$(dirname "$0")/.."
BUILD_DIR="$(mktemp -d)"
trap 'rm -rf "$BUILD_DIR"' EXIT
FLAGS="-std=c++17 -Wall -Wextra -pedantic -Werror -D_GLIBCXX_DEBUG"

echo "== Build main (warnings are errors)"
g++ $FLAGS main.cpp order.cpp mechanic.cpp workshop.cpp -o "$BUILD_DIR/werkstatt"

echo "== Build tests"
g++ $FLAGS -I. tests/test_loesung.cpp order.cpp mechanic.cpp workshop.cpp -o "$BUILD_DIR/tests"

echo "== Unit tests"
"$BUILD_DIR/tests"

echo "== Compare main output with tests/expected_main_output.txt"
"$BUILD_DIR/werkstatt" | tr -d '\r' > "$BUILD_DIR/actual.txt"
diff -u <(tr -d '\r' < tests/expected_main_output.txt) "$BUILD_DIR/actual.txt"
echo "main output matches"

echo "== ALL TESTS PASSED"

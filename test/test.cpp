#include <catch2/catch_test_macros.hpp>
#include <iostream>

// change if you choose to use a different header name
#include "adjacencyList.cpp"

using namespace std;

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("PageRank Test 1", "One website points to many [5 power iterations]"){
        // the following is a "raw string" - you can write the exact input (without
        // any indentation!) and it should work as expected
    string input = R"(10 2
google.com apple.com
google.com NASA.gov
google.com US.gov
google.com ESA.int
google.com JAXA.jp
google.com microsoft.com
google.com yahoo.com
google.com ferrero.it
google.com barillagroup.com
google.com americanairlines.com)";

    string expectedOutput = R"(ESA.int 0.01
JAXA.jp 0.01
NASA.gov 0.01
US.gov 0.01
americanairlines.com 0.01
apple.com 0.01
barillagroup.com 0.01
ferrero.it 0.01
google.com 0.00
microsoft.com 0.01
yahoo.com 0.01)";

    string actualOutput;

    //somehow pass your input into your AdjacencyList and parse it to call the
    //correct functions, for example:
    // AdjacencyList t1;
    // t1.parseInput(input);
    // actualOutput = t1.getStringRepresentation();

    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Test 2", "[tag]"){
    // you can also use "sections" to share setup code between tests, for example:
    int one = 1;

    SECTION("num is 2") {
        int num = one + 1;
        REQUIRE(num == 2);
    };

    SECTION("num is 3") {
        int num = one + 2;
        REQUIRE(num == 3);
    };

    // each section runs the setup code independently to ensure that they don't affect each other
}

// you must write 5 unique, meaningful tests for extra credit on this project!

// See the following for an example of how to easily test your output.
// This uses C++ "raw strings" and assumes your PageRank outputs a string with
//   the same thing you print.
TEST_CASE("Example PageRank Output Test", "[flag]"){
    // the following is a "raw string" - you can write the exact input (without
    //   any indentation!) and it should work as expected
    string input = R"(7 2
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com)";

    string expectedOutput = R"(facebook.com 0.20
gmail.com 0.20
google.com 0.10
maps.com 0.30
ufl.edu 0.20
)";

    string actualOutput;

    //somehow pass your input into your AdjacencyList and parse it to call the
    //correct functions, for example:
    // AdjacencyList g;
    // g.parseInput(input)
    // actualOutput = g.getStringRepresentation()

    REQUIRE(actualOutput == expectedOutput);
}

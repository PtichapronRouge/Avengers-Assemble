/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_AlgebraTest_init = false;
#include "/data/Projets/Avengers-Assemble/algrebra/src/algebra_test.hpp"

static AlgebraTest suite_AlgebraTest;

static CxxTest::List Tests_AlgebraTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AlgebraTest( "src/algebra_test.hpp", 44, "AlgebraTest", suite_AlgebraTest, Tests_AlgebraTest );

static class TestDescription_suite_AlgebraTest_testNaiveIntegerMatrixProd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AlgebraTest_testNaiveIntegerMatrixProd() : CxxTest::RealTestDescription( Tests_AlgebraTest, suiteDescription_AlgebraTest, 47, "testNaiveIntegerMatrixProd" ) {}
 void runTest() { suite_AlgebraTest.testNaiveIntegerMatrixProd(); }
} testDescription_suite_AlgebraTest_testNaiveIntegerMatrixProd;

static class TestDescription_suite_AlgebraTest_testIntegerMatrixProd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AlgebraTest_testIntegerMatrixProd() : CxxTest::RealTestDescription( Tests_AlgebraTest, suiteDescription_AlgebraTest, 66, "testIntegerMatrixProd" ) {}
 void runTest() { suite_AlgebraTest.testIntegerMatrixProd(); }
} testDescription_suite_AlgebraTest_testIntegerMatrixProd;

static class TestDescription_suite_AlgebraTest_testFloatMatrixProd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AlgebraTest_testFloatMatrixProd() : CxxTest::RealTestDescription( Tests_AlgebraTest, suiteDescription_AlgebraTest, 85, "testFloatMatrixProd" ) {}
 void runTest() { suite_AlgebraTest.testFloatMatrixProd(); }
} testDescription_suite_AlgebraTest_testFloatMatrixProd;

static class TestDescription_suite_AlgebraTest_testFloatDotProd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AlgebraTest_testFloatDotProd() : CxxTest::RealTestDescription( Tests_AlgebraTest, suiteDescription_AlgebraTest, 104, "testFloatDotProd" ) {}
 void runTest() { suite_AlgebraTest.testFloatDotProd(); }
} testDescription_suite_AlgebraTest_testFloatDotProd;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

#include <iostream>
#include "testICommandHandler.h"
#include "testIDao.h"

using namespace std;

int main() {
    testICommandHandler *testCmdHandler = new testICommandHandler;

    int failICommandHandler = testCmdHandler->testAll();
    int SuccessRateICommandHandler =
            (testCmdHandler->testConducted - failICommandHandler) * 100 / testCmdHandler->testConducted;

    testIDao *testDao = new testIDao;

    int failIDao = testDao->testAll();
    int SuccessRateIDao =
            (testDao->testConducted - failIDao) * 100 / testDao->testConducted;

    int SuccessRateTotal =
            ((testCmdHandler->testConducted - failICommandHandler) + (testDao->testConducted - failIDao)) * 100 /
            (testCmdHandler->testConducted + testDao->testConducted);

    cout << endl;
    cout << "------------------------------" << endl;
    cout << "TEST RESULTS: ICommandHandler" << endl;
    cout << "Tests conducted: " << testCmdHandler->testConducted << endl;
    cout << "Tests failed: " << failICommandHandler << endl;
    cout << "Success rate: " << SuccessRateICommandHandler << "%" << endl;
    cout << "------------------------------" << endl << endl;

    cout << "------------------------------" << endl;
    cout << "TEST RESULTS: IDao" << endl;
    cout << "Tests conducted: " << testDao->testConducted << endl;
    cout << "Tests failed: " << failIDao << endl;
    cout << "Success rate: " << SuccessRateIDao << "%" << endl;
    cout << "------------------------------" << endl << endl;

    cout << "------------------------------" << endl;
    cout << "TEST RESULTS: TOTAL" << endl;
    cout << "Tests conducted: " << testDao->testConducted + testCmdHandler->testConducted << endl;
    cout << "Tests failed: " << failIDao + failICommandHandler << endl;
    cout << "Success rate: " << SuccessRateTotal << "%" << endl;
    cout << "------------------------------" << endl;

    delete testCmdHandler;
    delete testDao;
}
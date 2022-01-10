#include <iostream>
#include <stdlib.h>     // rand
#include "testIDao.h"
#include "testKVPStorage.h"
#include "DaoInMemory.h"

#define TEST_MAX_KEY_LEN 10
#define TEST_MAX_VALUE_LEN 10

using namespace std;

IDao *dao = &DaoInMemory::GetInstance();

int testIDao::testAll() {
    int failTest = 0;
#define  MONTE_CARLO_TRIAL 100

    for (int i = 0; i < MONTE_CARLO_TRIAL; i++) {
        failTest += testSet();
        failTest += testGet();
        failTest += testDelete();
    }

    return failTest;
}

bool testIDao::testSet() {
    cout << "IDao_UnitTests: SET" << endl;

    int key_len = rand() % 10;
    int value_len = rand() % 10;
    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    std::stringstream cmdLine;
    cmdLine.str(std::string()); // clean buffer
    std::streambuf *old = std::cout.rdbuf(cmdLine.rdbuf());
    dao->SetKVP(key, value);
    std::string outputLine = cmdLine.str(); // text will now contain cout value
    std::cout.rdbuf(old);
    testConducted++;

    if (testKVPStorage::PrintInputs)
        std::cout << "Input: " << "SetKVP(" << key << ")" << endl;

    return testKVPStorage::EXPECT_EQ("OK\n", outputLine);
}

bool testIDao::testGet() {
    cout << "IDao_UnitTests: GET" << endl;
    int key_len = rand() % TEST_MAX_KEY_LEN;
    int value_len = rand() % TEST_MAX_VALUE_LEN;
    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    dao->SetKVP(key,value); // First set, then get

    std::stringstream cmdLine;
    cmdLine.str(std::string()); // clean buffer
    std::streambuf *old = std::cout.rdbuf(cmdLine.rdbuf());
    dao->GetKVP(key);
    std::string outputLine = cmdLine.str(); // text will now contain cout value
    std::cout.rdbuf(old);

    if (testKVPStorage::PrintInputs)
        std::cout << "Input: " << "GetKVP(" << key << ")" << endl;

    testConducted++;
    return testKVPStorage::EXPECT_EQ(value + "\n", outputLine);
}

bool testIDao::testDelete() {
    cout << "IDao_UnitTests: DELETE" << endl;
    int key_len = rand() % 10;
    int value_len = rand() % 10;
    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    std::stringstream cmdLine;
    cmdLine.str(std::string()); // clean buffer
    std::streambuf *old = std::cout.rdbuf(cmdLine.rdbuf());
    dao->DeleteKVP(key);
    std::string outputLine = cmdLine.str(); // text will now contain cout value
    std::cout.rdbuf(old);

    if (testKVPStorage::PrintInputs)
        std::cout << "Input: " << "DeleteKVP(" << key << ")" << endl;

    testConducted++;
    return testKVPStorage::EXPECT_EQ("OK\n", outputLine);
}
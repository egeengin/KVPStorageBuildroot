#include <iostream>
#include <stdlib.h>     // rand
#include <sstream>
#include "testKVPStorage.h"
#include "testICommandHandler.h"
#include "CommandHandler.h"

#define TEST_MAX_QUERY_LEN 10
#define TEST_MAX_KEY_LEN TEST_MAX_QUERY_LEN
#define TEST_MAX_VALUE_LEN TEST_MAX_QUERY_LEN

using namespace std;

ICommandHandler *ich = &CommandHandler::GetHandler();

std::string testICommandHandler::CaptureStdOut(string inputLine) {
    std::stringstream cmdLine;
    cmdLine.str(std::string()); // clean buffer
    std::streambuf *old = std::cout.rdbuf(cmdLine.rdbuf());
    ich->HandleUserCommands(inputLine);
    std::string outputLine = cmdLine.str(); // text will now contain cout value
    std::cout.rdbuf(old);
    return outputLine;
}

int testICommandHandler::testAll() {
    int failTest = 0;

    failTest += testSet();
    failTest += testGet();
    failTest += testDelete();
    failTest += testExtraInputs();
    failTest += testQuasiRandom();

    return failTest;
}

int testICommandHandler::testQuasiRandom() {
    cout << "ICommandHandler_UnitTests: QuasiRandom" << endl;
#define  MONTE_CARLO_TRIAL 100
    int query_len, key_len, value_len, failTest = 0;
    string query, key, value, inputLine, outputLine;

    for (int i = 0; i < MONTE_CARLO_TRIAL; i++) {
        query_len = rand() % 2 ? 3 : 6; // randomly 3 or 6 is selected - so named quasi -
        key_len = rand() % TEST_MAX_KEY_LEN;
        value_len = rand() % TEST_MAX_VALUE_LEN;

        query = testKVPStorage::GenerateRandomString(query_len);
        key = testKVPStorage::GenerateRandomString(key_len);
        value = testKVPStorage::GenerateRandomString(value_len);

        inputLine = query + " " + key + " " + value;
        string outputLine = CaptureStdOut(inputLine);

        if (testKVPStorage::PrintInputs)
            std::cout << "Input: " << inputLine << endl;

        if (query == "SET") {
            if (testKVPStorage::EXPECT_EQ("OK\n", outputLine))
                failTest++;
        } else if ((value_len == 0) && (query == "DELETE" || query == "SET")) {
            if (testKVPStorage::EXPECT_EQ("OK\n", outputLine))
                failTest++;
        } else {
            if (testKVPStorage::EXPECT_EQ("Wrong input\n", outputLine))
                failTest++;
        }
        testConducted++;
    }
    return failTest;
}

bool testICommandHandler::testSet() {
    cout << "ICommandHandler_UnitTests: SET" << endl;

    int key_len = rand() % TEST_MAX_KEY_LEN;
    int value_len = rand() % TEST_MAX_VALUE_LEN;

    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    string inputLine = "SET " + key + " " + value;
    string outputLine = CaptureStdOut(inputLine);

    if (testKVPStorage::PrintInputs)
        std::cout << "Input: " << inputLine << endl;

    if (key_len == 0 || value_len == 0) {
        return testKVPStorage::EXPECT_EQ("Wrong input\n", outputLine);
    } else {
        return testKVPStorage::EXPECT_EQ("OK\n", outputLine);
    }
    testConducted++;
}

bool testICommandHandler::testGet() {
    cout << "ICommandHandler_UnitTests: GET" << endl;

    int key_len = rand() % TEST_MAX_KEY_LEN;
    int value_len = rand() % TEST_MAX_VALUE_LEN;

    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    string inputLine1 = "SET " + key + " " + value;
    ich->HandleUserCommands(inputLine1); //First SET [key] [value]

    string inputLine2 = "GET " + key;
    string outputLine = CaptureStdOut(inputLine2);

    if (testKVPStorage::PrintInputs) {
        std::cout << "Input: " << inputLine1 << endl;
        std::cout << "Input: " << inputLine2 << endl;
    }

    if (key_len == 0) {
        return testKVPStorage::EXPECT_EQ("Wrong input\n", outputLine);
    } else {
        return testKVPStorage::EXPECT_EQ((std::string) value + "\n", outputLine);
    }
    testConducted++;
}

bool testICommandHandler::testDelete() {
    cout << "ICommandHandler_UnitTests: DELETE" << endl;
    int key_len = rand() % TEST_MAX_KEY_LEN;
    int value_len = rand() % TEST_MAX_VALUE_LEN;

    string key = testKVPStorage::GenerateRandomString(key_len);
    string value = testKVPStorage::GenerateRandomString(value_len);

    string inputLine1 = "SET " + key + " " + value;
    ich->HandleUserCommands(inputLine1); //First SET [key] [value]

    string inputLine2 = "DELETE " + key;
    string outputLine = CaptureStdOut(inputLine2);

    if (testKVPStorage::PrintInputs) {
        std::cout << "Input: " << inputLine1 << endl;
        std::cout << "Input: " << inputLine2 << endl;
    }

    if (key_len == 0) {
        return testKVPStorage::EXPECT_EQ("Wrong input\n", outputLine);
    } else {
        return testKVPStorage::EXPECT_EQ("OK\n", outputLine);
    }
    testConducted++;
}

bool testICommandHandler::testExtraInputs() {
    cout << "ICommandHandler_UnitTests: ExtraInputs" << endl;
    int query_len, key_len, value_len, extra_len;
    string query, key, value, extra, inputLine, outputLine;

    query_len = rand() % (TEST_MAX_QUERY_LEN - 1) + 1; // at least 1
    key_len = rand() % (TEST_MAX_KEY_LEN - 1) + 1;
    value_len = rand() % (TEST_MAX_VALUE_LEN - 1) + 1;
    extra_len = rand() % (TEST_MAX_QUERY_LEN - 1) + 1;

    query = testKVPStorage::GenerateRandomString(query_len);
    key = testKVPStorage::GenerateRandomString(key_len);
    value = testKVPStorage::GenerateRandomString(value_len);
    extra = testKVPStorage::GenerateRandomString(value_len);

    inputLine = query + " " + key + " " + value + " " + extra;
    outputLine = CaptureStdOut(inputLine);

    if (testKVPStorage::PrintInputs)
        std::cout << "Input: " << inputLine << endl;

    testConducted++;
    return testKVPStorage::EXPECT_EQ("Wrong input\n", outputLine);
}
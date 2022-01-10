#ifndef KVPSTORAGE_TSTICOMMANDHANDLER_H
#define KVPSTORAGE_TSTICOMMANDHANDLER_H

#include <string>

class testICommandHandler {
public:
    testICommandHandler() = default;

    int testConducted = 0;

    int testAll();

    int testQuasiRandom();

    bool testSet();

    bool testGet();

    bool testDelete();

    bool testExtraInputs();

    virtual ~testICommandHandler() = default;

private:
    std::string CaptureStdOut(std::string inputLine);
};

#endif //KVPSTORAGE_TSTICOMMANDHANDLER_H

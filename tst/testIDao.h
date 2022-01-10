#ifndef KVPSTORAGE_TSTIDAO_H
#define KVPSTORAGE_TSTIDAO_H

#include <string>

class testIDao {
public:
    testIDao() = default;

    int testConducted = 0;

    int testAll();

    bool testSet();

    bool testGet();

    bool testDelete();

    virtual ~testIDao() = default;

private:
};

#endif //KVPSTORAGE_TSTIDAO_H

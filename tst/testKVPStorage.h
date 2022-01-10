#ifndef KVPSTORAGE_TSTKVPSTORAGE_H
#define KVPSTORAGE_TSTKVPSTORAGE_H

#include <string>

class testKVPStorage {
public:
    inline static const std::string SettingsFile = "settings.json";
    inline static const bool PrintInputs = 1;

    testKVPStorage() = default;

    std::string static GenerateRandomString(const int len) {
        static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        std::string rand_str;
        rand_str.reserve(len);

        for (int i = 0; i < len; ++i) {
            rand_str += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return rand_str;
    }

    bool static EXPECT_EQ(std::string input, std::string output) {
        if (output == input) {
            std::cout << "Success" << std::endl;
            return 0;
        } else {
            std::cout << "Fail" << std::endl;
            return 1;
        }
    }

    virtual ~testKVPStorage() {};
};

#endif //KVPSTORAGE_TSTKVPSTORAGE_H

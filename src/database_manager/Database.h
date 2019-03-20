
#ifndef AHRS_DATABASE_H
#define AHRS_DATABASE_H

#include <string>
#include <sqlite3.h>
#include <logger/Logger.h>

namespace database
{
    class Database
    {
    public:
        Database(const std::string& name);
        virtual ~Database();

        bool insertHASH(uint32_t hash);

    protected:
        bool open(const std::string& name);
        bool executeCommand(const std::string& command);

        const std::string HASH_TABLE = "CREATE TABLE IDENTIFIER (HASH INTEGER);";
        const std::string APOSTROPHE = "'";
        const std::string SEMICOLON = ",";

        std::string name_;
        utility::Logger& logger_;

    private:
        sqlite3 *database_;
        bool isOpened;
    };
}

#endif //AHRS_DATABASE_H

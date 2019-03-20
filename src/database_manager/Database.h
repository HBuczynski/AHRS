
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
        Database();
        virtual ~Database();

    protected:
        bool open(const std::string& name);
        bool executeCommand(const std::string& command);

        const std::string HASH_IDENTIFIER = "CREATE TABLE IDENTIFIER ("
                                            "HASH INTEGER"
                                            ");";

        const std::string mark = "'";
        const std::string semicolon = ",";

        utility::Logger& logger_;

    private:
        sqlite3 *database_;
        bool isOpened;


    };
}

#endif //AHRS_DATABASE_H

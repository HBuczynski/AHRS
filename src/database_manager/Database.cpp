#include "Database.h"

using namespace std;
using namespace utility;
using namespace database;

Database::Database(const std::string& name)
    : hash_(0),
      name_(name),
      logger_(Logger::getInstance()),
      database_(nullptr),
      isOpened(false)
{}

Database::~Database()
{
    if(database_ != nullptr)
    {
        sqlite3_close(database_);
    }
}

bool Database::open(const std::string &name)
{
    int exit = 0;
    exit = sqlite3_open(name.c_str(), &database_);

    if (exit != SQLITE_OK)
        return false;

    isOpened = true;

    return true;
}

bool Database::executeCommand(const std::string& command)
{
    char* messageError;
    int exit = 0;
    exit = sqlite3_exec(database_, command.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK)
    {
        if(logger_.isWarningEnable())
        {
            const string message = string("Database :: Cannot execute command. Warning: ") + string(messageError);
            logger_.writeLog(LogType::WARNING_LOG, message);
        }

        sqlite3_free(messageError);
        return false;
    }

    return true;
}

bool Database::insertHASH(uint32_t hash)
{
    hash_ = hash;
    string command = "INSERT INTO IDENTIFIER VALUES(" + to_string(hash) + ");";
    return executeCommand(command);
}

uint32_t Database::getHash() const noexcept
{
    return hash_;
}

const string& Database::getName() const noexcept
{
    return name_;
}

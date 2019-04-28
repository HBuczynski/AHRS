#ifndef HSM_ALEXASIMULATOR_EVENT_H
#define HSM_ALEXASIMULATOR_EVENT_H

#include <cstdint>
#include <iostream>

#include <functional>

namespace hsm
{
    class Event
    {
    public:
        Event(const std::string &key);

        const std::string& getKey() const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Event &rhs)
        {
            return os << rhs.getKey();
        }

        friend bool operator==(const Event &lhs, const Event &rhs)
        {
            return lhs.getKey() == rhs.getKey();
        }

    private:
        std::string key_;
    };
}

namespace std {
    template<>
    struct hash<hsm::Event> {
        size_t operator()(const hsm::Event &obj) const noexcept {
            return hash<std::string>{}(obj.getKey());
        }
    };
}

#endif
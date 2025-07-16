#ifndef BLUEPRINT_CORE_EXCEPTION_HPP
#define BLUEPRINT_CORE_EXCEPTION_HPP

#include <exception>
#include <string>

namespace Blueprint::Core {
class Exception {
public:
    explicit Exception(std::string message);
    explicit Exception(const std::exception& other);
    virtual ~Exception() = default;

public:
    virtual void log() const;
    [[nodiscard]] const std::string& getMessage() const;

private:
    std::string m_Message;
};
} // Blueprint::Core

#endif // BLUEPRINT_CORE_EXCEPTION_HPP

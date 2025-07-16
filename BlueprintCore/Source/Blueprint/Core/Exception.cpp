#include <iostream>

#include "Blueprint/Core/Exception.hpp"

Blueprint::Core::Exception::Exception(std::string message) : m_Message(std::move(message)) {}

Blueprint::Core::Exception::Exception(const std::exception& other) : m_Message(other.what()) {}

void Blueprint::Core::Exception::log() const {
    std::cout << "An error occurred:\n" << m_Message << '\n';
}

const std::string& Blueprint::Core::Exception::getMessage() const {
    return m_Message;
}

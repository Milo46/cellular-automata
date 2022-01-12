#include "Logger.hpp"

#include <iostream>

namespace Utility
{
    Log::Log(Logger& caller, Severity severity, const std::string& message)
        : m_Logger(caller), m_Severity(severity), m_Message(message) {}

    Log::~Log()
    {
        if (!m_Called) Log::Call();
    }

    void Log::Call()
    {
        switch (m_Severity)
        {
        case Severity::Trace:   std::cout << "[TRACE]: "   << m_Message << '\n'; break;
        case Severity::Info:    std::cout << "[INFO]: "    << m_Message << '\n'; break;
        case Severity::Warning: std::cerr << "[WARNING]: " << m_Message << '\n'; break;
        case Severity::Error:   std::cerr << "[ERROR]: "   << m_Message << '\n'; break;
        case Severity::Fatal:   std::cerr << "[FATAL]: "   << m_Message << '\n'; break;

        default:
            m_Logger.Error("Failed to determine severity of a log! Message: " + m_Message);
        }
    }

    Logger::Logger(bool type)
        : m_Type(type) {}

    void Logger::Throw(Log::Severity severity, const std::string& message) const
    {
        //Log log = Log(*this, severity, message);
    }

    void Logger::Trace(const std::string& message) const   { Logger::Throw(Log::Severity::Trace,   message); }
    void Logger::Info(const std::string& message) const    { Logger::Throw(Log::Severity::Info,    message); }
    void Logger::Warning(const std::string& message) const { Logger::Throw(Log::Severity::Warning, message); }
    void Logger::Error(const std::string& message) const   { Logger::Throw(Log::Severity::Error,   message); }

    void Logger::Fatal(const std::string& message) const
    {
        Logger::Throw(Log::Severity::Fatal, message);

        if (m_Type == c_Core) terminate(); // (terminate vs abort)
    }
}

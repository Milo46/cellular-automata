#pragma once

#include <string>

namespace Utility
{
    class Logger;

    class Log
    {
    public:
        enum class Severity
        {
            Trace = 0, // Some non-important data
            Info,      // Maybe some important data
            Warning,   // Imporatant data, do what it says
            Error,     // Something's wrong, you have to fix it
            Fatal      // Something works really bad, need instant fix
        };

    public:
        friend Logger;

    private:
        Log(Logger& caller, Severity severity, const std::string& message);
        ~Log();

        void Call();

    private:
        Logger& m_Logger;

        Severity m_Severity;
        std::string m_Message;

        bool m_Called = false;
    };

    class Logger
    {
    public:
        constexpr static bool c_Client = false;
        constexpr static bool c_Core   = true;

    public:
        // Core loggers terminates application on fatal logs
        Logger(bool type = c_Client);

    public:
        void Trace(const std::string& message) const;
        void Info(const std::string& message) const;
        void Warning(const std::string& message) const;
        void Error(const std::string& message) const;
        void Fatal(const std::string& message) const;

    private:
        void Throw(Log::Severity severity, const std::string& message) const;

    private:
        bool m_Type;
    };
}

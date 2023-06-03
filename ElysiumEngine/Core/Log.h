#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <mutex>

namespace Core {

    enum class LogLevel {
        Debug,
        Info,
        Warning,
        Error
    };

    class Log {
    public:

        class LogProxy {
        public:
            LogProxy(Log& logger, LogLevel level) : m_log(logger), m_level(level) {}

            template <typename T>
            LogProxy& operator<<(T&& value) {
                m_stream << value;
                return *this;
            }


            ~LogProxy() {
                std::string levelString = m_log.GetLogLevelString(m_level);
                std::string message = m_stream.str();
                m_log.LogMessage(m_level, message);
            }

        private:
            Log& m_log;
            LogLevel m_level;
            std::stringstream m_stream;
        };

        static Log& Instance();

        void SetLogFile(const std::string& filename);

        void LogMessage(LogLevel level, const std::string& message);

        LogProxy Out(LogLevel level) {
            return LogProxy(*this, level);
        }

        void SetLoggerName(const std::string& name);

        void SetLogLevelFilter(LogLevel level);

        void AddOutput(std::ostream& output);

        void SetMaxFileSize(std::size_t maxSize);

        void SetMaxFiles(std::size_t maxFiles);

    private:
        std::string loggerName_;
        std::string logFilename_; // Added member variable for storing the log file name
        std::ofstream logFile_;
        std::vector<std::ostream*> outputs_;
        LogLevel logLevelFilter_;
        std::size_t maxFileSize_;
        std::size_t maxFiles_;
        std::mutex mutex_;

        Log();
        ~Log();

        std::string GetLogLevelString(LogLevel level);
        std::string GetCurrentTime();
        std::string GetFormattedMessage(const std::string& levelString, const std::string& message);
        void WriteToConsole(LogLevel level, const std::string& formattedMessage);
        void WriteToOutputs(const std::string& formattedMessage);
        void WriteToFile(const std::string& formattedMessage);
        std::string GenerateLogFilename() const;
        void RotateLogFiles();
    };

} // namespace Core

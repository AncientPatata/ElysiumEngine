#include "Log.h"

using namespace Core;

Log& Log::Instance() {
    static Log instance;
    return instance;
}

void Log::SetLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);

    logFile_.close();
    logFile_.open(filename, std::ofstream::out | std::ofstream::app);
    if (!logFile_.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
    else {
        logFilename_ = filename; // Store the log filename
    }
}

void Log::LogMessage(LogLevel level, const std::string& message) {
    std::string levelString = GetLogLevelString(level);
    std::string formattedMessage = GetFormattedMessage(levelString, message);

    std::lock_guard<std::mutex> lock(mutex_);

    WriteToConsole(level, formattedMessage);
    WriteToOutputs(formattedMessage);
    WriteToFile(formattedMessage);
}



void Log::SetLogLevelFilter(LogLevel level) {
    std::lock_guard<std::mutex> lock(mutex_);
    logLevelFilter_ = level;
}

void Log::AddOutput(std::ostream& output) {
    std::lock_guard<std::mutex> lock(mutex_);
    outputs_.push_back(&output);
}

void Log::SetMaxFileSize(std::size_t maxSize) {
    std::lock_guard<std::mutex> lock(mutex_);
    maxFileSize_ = maxSize;
}

void Log::SetMaxFiles(std::size_t maxFiles) {
    std::lock_guard<std::mutex> lock(mutex_);
    maxFiles_ = maxFiles;
}

Log::Log() : logLevelFilter_(LogLevel::Debug), maxFileSize_(0), maxFiles_(0) {}

Log::~Log() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

std::string Log::GetLogLevelString(LogLevel level) {
    switch (level) {
    case LogLevel::Debug:
        return "[DEBUG]";
    case LogLevel::Info:
        return "[INFO]";
    case LogLevel::Warning:
        return "[WARNING]";
    case LogLevel::Error:
        return "[ERROR]";
    default:
        return "[UNKNOWN]";
    }
}

std::string Log::GetCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
    return buffer;
}

std::string Log::GetFormattedMessage(const std::string& levelString, const std::string& message) {
    std::ostringstream oss;
    oss << GetCurrentTime() << " " << levelString << " " << message;
    return oss.str();
}

void Log::WriteToConsole(LogLevel level, const std::string& formattedMessage) {
    switch (level) {
    case LogLevel::Debug:
        std::cout << "\033[90m" << formattedMessage << "\033[0m" << std::endl; // Print in gray color
        break;
    case LogLevel::Info:
        std::cout << formattedMessage << std::endl;
        break;
    case LogLevel::Warning:
        std::cout << "\033[93m" << formattedMessage << "\033[0m" << std::endl; // Print in yellow color
        break;
    case LogLevel::Error:
        std::cerr << "\033[91m" << formattedMessage << "\033[0m" << std::endl; // Print in red color
        break;
    default:
        std::cout << formattedMessage << std::endl;
        break;
    }
}

void Log::WriteToOutputs(const std::string& formattedMessage) {
    for (std::ostream* output : outputs_) {
        (*output) << formattedMessage << std::endl;
    }
}

void Log::WriteToFile(const std::string& formattedMessage) {
    if (!logFile_.is_open()) {
        return;
    }

    logFile_ << formattedMessage << std::endl;

    if (maxFileSize_ > 0 && logFile_.tellp() > maxFileSize_) {
        RotateLogFiles();
    }
}

void Log::SetLoggerName(const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex_);
    loggerName_ = name;
}



std::string Log::GenerateLogFilename() const {
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", &localTime);
    return std::string("log_") + buffer + ".txt";
}

void Log::RotateLogFiles() {
    if (maxFiles_ == 0) {
        return;
    }

    logFile_.close();

    std::string currentFilename = logFilename_;
    std::string currentPath = currentFilename.substr(0, currentFilename.find_last_of("\\/"));
    std::string currentExtension = currentFilename.substr(currentFilename.find_last_of('.'));
    std::string baseFilename = currentPath + "/" + GenerateLogFilename();
    std::string nextFilename = baseFilename + currentExtension;

    for (std::size_t i = maxFiles_ - 1u; i > 0u; --i) {
        std::string currentFile = baseFilename + std::to_string(i) + currentExtension;
        std::string nextFile = baseFilename + std::to_string(i + 1u) + currentExtension;
        std::rename(currentFile.c_str(), nextFile.c_str());
    }

    std::rename(currentFilename.c_str(), nextFilename.c_str());

    logFile_.open(currentFilename, std::ofstream::out | std::ofstream::app);
}

#include "elephantlogger/core/LogMessage.h"

#include <string.h> // memcpy
#include <stdio.h>  // printf


using namespace elephantlogger;


LogMessage::LogMessage(const LogLevel logLevel,
                       const int channelID,
                       const char* file,
                       const int line,
                       const char* function,
                       const char* format,
                       va_list argList)
    : m_logLevel(logLevel),
      m_channelID(channelID),
      m_line(line),
      m_creationTime(std::time(nullptr)) {
          memcpy(this->m_file, file, strlen(file));
          memcpy(this->m_function, function, strlen(function));
          vsnprintf(m_message, config::LOG_MSG_SIZE-1, format, argList); // -1 for '\0'
          this->m_message[config::LOG_MSG_SIZE-1] = '\0';
}

const std::string LogMessage::getFormattedMessage() const {
    std::string dateStr = ctime(&this->m_creationTime);
    dateStr.pop_back(); // Remove line return

    std::string msg = "[" + dateStr +"] ";
    msg += "[";
    msg += LogLevelHelper::logLevelToString(this->m_logLevel);
    msg += "]: ";
    msg += this->m_message;
    return msg;
}

const int LogMessage::getChannelID() const {
    return this->m_channelID;
}


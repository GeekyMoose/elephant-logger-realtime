#pragma once


#include "LogLevel.h"
#include "LogMessage.h"
#include "LoggerConfig.h"
#include "elephantlogger/utils/Singleton.h"

#include <vector>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>   // unique_ptr
#include <cstdarg>  // va_list


namespace elephantlogger {

class Channel;


/**
 * The Famous Ugly Logger (Singleton).
 *
 * Run inside it's own thread (all functions are thread safe).
 * The user thread only queue message to be processed.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct, 2017
 */
class Logger : private Singleton<Logger> {

    // -------------------------------------------------------------------------
    // Attributs
    // -------------------------------------------------------------------------
    private:
        /** The current used log level (From LogLevel enum). */
        std::atomic<std::int8_t> m_currentLogLevel; // atomic_int8_t

        /** Lookup array of all available channels. */
        std::unique_ptr<Channel> m_lookupChannels[static_cast<size_t>(LoggerConfig::maxNbChannels)];

        /** Number of channels actually in use. */
        int nbChannels;

        /** Path to the folder with logs. */
        std::string m_logFilePath;

        /** Update rate. */
        int threadUpdateRate;

        /** True if clear any output at start (ex: clear log file). */
        bool clearAtStart;

        /**
         * Initial size of the queue.
         *
         * Each time a message is queued, I use push_back,
         * which is slow if has reached vector max size.
         * To avoid this, we should initialize the queue with a size big enough
         * to be hard to reach (Not enough logs in the queue)
         * and small enough for memory use space.
         */
        int defaultQueueSize;

    private:

        /** True if this Logger is Running. */
        std::atomic_bool m_isRunning;

        /** Vector of logs (List 1). */
        std::vector<LogMessage> m_queueLogs1;

        /** Vector of logs (List 2). */
        std::vector<LogMessage> m_queueLogs2;

        /** Point to the vector where logs are queued. */
        std::vector<LogMessage>* m_queueLogsFront;

        /** Point to the vector currently processed by the Logger. */
        std::vector<LogMessage>* m_queueLogsBack;

        /** Mutex for Front Logs queue access. */
        std::mutex m_queuesFrontAccessMutex;


    // -------------------------------------------------------------------------
    // Initialization / Constructors
    // -------------------------------------------------------------------------
    private:
        friend Singleton<Logger>;
        Logger() = default;
        ~Logger() = default;

    public:
        using Singleton<Logger>::get;

        void startup();
        void shutdown();


    // -------------------------------------------------------------------------
    // Core Methods
    // -------------------------------------------------------------------------
    public:

        /**
         * Queue a log to be processed by the respective Output.
         * This function is meant be be as fast as possible.
         * Only queue the message to be processed later by logger thread.
         *
         * \remark
         * Only logs more critical or equal to current LogLevel are queued.
         *
         * \remark
         * This function is thread safe and may be called concurrently.
         *
         * \param level     Log Level for this message.
         * \param channelID ID of the channel where to write log.
         * \param file      File that created the log
         * \param line      Line position in file.
         * \param function  Function's name.
         * \param format    Row message, using printf convention (%s, %d etc).
         * \param ...       Variable list of parameters.
         */
        void queueLog(const LogLevel level,
                      const int channelID,
                      const char* file,
                      const int line,
                      const char* function,
                      const char* format,
                      ...);

        /**
         * Save all logs in a save directory.
         * This simply copy the logPath directory into a safe LogPath directory.
         *
         * \remark
         * Do nothing if log in file is not allowed (False returned).
         *
         * \return True if successfully saved, otherwise, return false.
         */
        bool saveAllLogFiles() const;


    // -------------------------------------------------------------------------
    // Internal Methods
    // -------------------------------------------------------------------------
    private:

        /**
         * Queue a log, regardless any settings.
         * Not thread safe, to use internally only.
         */
        void internalQueueLog(LogLevel level,
                              const int channelID,
                              const char* file,
                              const int line,
                              const char* function,
                              const char* format,
                              va_list argList);

        /**
         * Process each elements from the back queue and clear it.
         */
        void internalProcessBackQueue();

        /**
         * Swap front and back queue buffers.
         */
        void internalSwapQueues();

        /**
         * Runs the Logger Component in a new thread.
         * Logger can be started only if it's not already running.
         */
        void internalStartLoggerThread();


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:

        /**
         * Changes the current log level.
         */
        void setLogLevel(const LogLevel level);

        /**
         * Returns the current log level.
         */
        LogLevel getLogLevel() const;

        /**
         * Change all settings with config value.
         */
        void applyConfig(const LoggerConfig& config);

}; // End Logger class


} // End namespace


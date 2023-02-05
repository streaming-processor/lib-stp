#pragma once

#ifdef NDEBUG
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif

#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/async.h"

namespace Logger
{
    class StpLogger
    {
    private:
        std::shared_ptr<spdlog::logger> logger;
        std::shared_ptr<spdlog::details::thread_pool> threadPool;
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> stdout_sink;
        std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> rotating_sink;
        std::vector<spdlog::sink_ptr> sinks;

        StpLogger(){}

    public:
        static StpLogger* instance()
        {
            static std::shared_ptr<StpLogger> uniqueInstance(new StpLogger);
            return uniqueInstance.get();
        }

        void setLoggerConfigs(int logLevel, int maxFileSize, int maxFileNumber, std::string logPath)
        {
            static const std::vector<spdlog::string_view_t> logLevelNames(SPDLOG_LEVEL_NAMES);
            std::cout << "log level set as: " << logLevel << " (" << logLevelNames[logLevel].data() << ")" << std::endl;

            stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logPath, maxFileNumber, maxFileNumber);

            stdout_sink->set_pattern("[%^%l%$] [%s:%# %!] %v");
            rotating_sink->set_pattern("[%Y-%m-%d %T.%e] [%^%l%$] [%s:%# %!] >> %v");

            sinks.clear();
            sinks.push_back(stdout_sink);
            sinks.push_back(rotating_sink);

            threadPool = std::make_shared<spdlog::details::thread_pool>(10,2);
            logger = std::make_shared<spdlog::async_logger>("falcon", sinks.begin(), sinks.end(), threadPool, spdlog::async_overflow_policy::block);
            logger->set_level((spdlog::level::level_enum)logLevel);
            spdlog::set_default_logger(logger);
            spdlog::flush_every(std::chrono::seconds(1));

        }

    };
};




#define STPLOG_LEVEL_TRACE SPDLOG_LEVEL_TRACE
#define STPLOG_LEVEL_DEBUG SPDLOG_LEVEL_DEBUG
#define STPLOG_LEVEL_INFO SPDLOG_LEVEL_INFO
#define STPLOG_LEVEL_WARN SPDLOG_LEVEL_WARN
#define STPLOG_LEVEL_ERROR SPDLOG_LEVEL_ERROR
#define STPLOG_LEVEL_CRITICAL SPDLOG_LEVEL_CRITICAL
#define STPLOG_LEVEL_OFF SPDLOG_LEVEL_OFF

#define INIT_LOGGER(config, logLevel) (Logger::STPLOGger::instance()->setLoggerConfig(logLevel, config.logMaxFileSizeByte, config.logMaxFileCount, config.logPath))
#define SHUTDOWN_LOGGER spdlog::shutdown();

#define STPLOG_TRACE SPDLOG_TRACE
#define STPLOG_DEBUG SPDLOG_DEBUG
#define STPLOG_INFO SPDLOG_INFO
#define STPLOG_WARN SPDLOG_WARN
#define STPLOG_ERROR SPDLOG_ERROR
#define STPLOG_CRITICAL SPDLOG_CRITICAL


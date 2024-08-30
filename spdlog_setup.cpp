#include "spdlog_setup.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

void spdlog_setup(const std::vector<std::string> &subsystems) {
    // Function to create and configure loggers based on the given subsystems

    // Create console and file sinks, overwrite previous one.
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.txt", true);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // Set sink levels
    file_sink->set_level(spdlog::level::info);
    console_sink->set_level(spdlog::level::debug);

    // Set log pattern
    //    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%F] [%l] %v");
    // Set the log pattern to include file name and line number

    // Create loggers based on the subsystems
    for (const auto &subsystem : subsystems) {
        std::vector<spdlog::sink_ptr> sinks;

        // using both a file and console sink

        sinks.push_back(console_sink);
        sinks.push_back(file_sink);

        auto logger_name = subsystem;
        auto logger = std::make_shared<spdlog::logger>(logger_name, sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::debug);

        //        logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] [%@] %v");

        // Register the logger with spdlog
        spdlog::register_logger(logger);
    }

    // Optionally set the default logger
    //    spdlog::set_default_logger(get_logger(Subsystem::Main));
}
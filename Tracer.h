//
// Created by jaime on 1/10/2024.
//

#ifndef DISTRIBUTEDTRACER_TRACER_H
#define DISTRIBUTEDTRACER_TRACER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <thread>
#include <string>
#include <memory>
#include <mpi.h>
#include <sstream>

class TraceLogger;

// Global variable for the trace logger
inline std::shared_ptr<spdlog::logger> traceLogger = nullptr;

#define TRACE_FUNC(rank) TraceLogger traceLoggerInstance(__FUNCTION__, rank)
#define INIT_TRACE() initTraceLogger()

void initTraceLogger() {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    traceLogger = spdlog::basic_logger_mt("trace_logger", "trace_" + std::to_string(rank) + ".json");
}

class TraceLogger {
public:
    TraceLogger(const std::string &functionName, int mpiRank)
            : functionName_(functionName), mpiRank_(mpiRank), startTime_(std::chrono::high_resolution_clock::now()) {
        logEvent("B"); // "B" for Begin
    }

    ~TraceLogger() {
        logEvent("E"); // "E" for End
    }

private:
    std::string functionName_;
    int mpiRank_;
    std::chrono::high_resolution_clock::time_point startTime_;

    void logEvent(const std::string &phase) {
        auto timestamp = std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now() - startTime_).count();
        std::thread::id threadId = std::this_thread::get_id();

        // Convert threadId to string
        std::ostringstream threadIdStream;
        threadIdStream << threadId;
        std::string threadIdStr = threadIdStream.str();

        if (traceLogger) {
            traceLogger->info("{{\"name\": \"{}\", \"ph\": \"{}\", \"ts\": {}, \"pid\": {}, \"tid\": \"{}\"}}",
                              functionName_, phase, timestamp, mpiRank_, threadIdStr);
        }
    }
};

#endif //DISTRIBUTEDTRACER_TRACER_H


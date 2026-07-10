#pragma once

#include <cstdarg>

namespace culina {

enum class LogLevel { Debug = 0, Info, Warn, Error };

using LogSink = void (*)(LogLevel level, const char* message);

void set_log_sink(LogSink sink);
void set_log_level(LogLevel level);
void log_message(LogLevel level, const char* fmt, ...) __attribute__((format(printf, 2, 3)));

} // namespace culina

#define CULINA_LOG_DEBUG(...) ::culina::log_message(::culina::LogLevel::Debug, __VA_ARGS__)
#define CULINA_LOG_INFO(...) ::culina::log_message(::culina::LogLevel::Info, __VA_ARGS__)
#define CULINA_LOG_WARN(...) ::culina::log_message(::culina::LogLevel::Warn, __VA_ARGS__)
#define CULINA_LOG_ERROR(...) ::culina::log_message(::culina::LogLevel::Error, __VA_ARGS__)

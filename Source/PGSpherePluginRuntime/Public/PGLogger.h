
#pragma once

DECLARE_LOG_CATEGORY_EXTERN(PGLogger, Log, All);

#define PGLOG_FATAL(Format, ...) UE_LOG(PGLogger, Fatal, Format, __VA_ARGS__)
#define PGLOG_ERROR(Format, ...) UE_LOG(PGLogger, Error, Format, __VA_ARGS__)
#define PGLOG_WARNING(Format, ...) UE_LOG(PGLogger, Warning, Format, __VA_ARGS__)
#define PGLOG_DISPLAY(Format, ...) UE_LOG(PGLogger, Display, Format, __VA_ARGS__)
#define PGLOG_LOG(Format, ...) UE_LOG(PGLogger, Log, Format, __VA_ARGS__)
#define PGLOG_VERBOSE(Format, ...) UE_LOG(PGLogger, Verbose, Format, __VA_ARGS__)
#define PGLOG_VERY_VERBOSE(Format, ...) UE_LOG(PGLogger, VeryVerbose, Format, __VA_ARGS__)
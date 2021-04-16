
#pragma once

DECLARE_LOG_CATEGORY_EXTERN(PGLogger, Log, All);

#define PGLOG_FATAL(Format, ...) UE_LOG(PGLogger, Fatal, Format, ...)
#define PGLOG_ERROR(Format, ...) UE_LOG(PGLogger, Error, Format, ...)
#define PGLOG_WARNING(Format, ...) UE_LOG(PGLogger, Warning, Format, ...)
#define PGLOG_DISPLAY(Format, ...) UE_LOG(PGLogger, Display, Format, ...)
#define PGLOG_LOG(Format, ...) UE_LOG(PGLogger, Log, Format, ...)
#define PGLOG_VERBOSE(Format, ...) UE_LOG(PGLogger, Verbose, Format, ...)
#define PGLOG_VERY_VERBOSE(Format, ...) UE_LOG(PGLogger, VeryVerbose, Format, ...)

#include "PGSpherePluginRuntime.h"
#include "PGLogger.h"

#define LOCTEXT_NAMESPACE "FPGSpherePluginRuntimeModule"

void FPGSpherePluginRuntimeModule::StartupModule()
{
	PGLOG_LOG(TEXT("FPGSpherePluginRuntimeModule::StartupModule()"));
}

void FPGSpherePluginRuntimeModule::ShutdownModule()
{
	PGLOG_LOG(TEXT("FPGSpherePluginRuntimeModule::ShutdownModule()"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_GAME_MODULE(FPGSpherePluginRuntimeModule, PGSpherePluginRuntime)
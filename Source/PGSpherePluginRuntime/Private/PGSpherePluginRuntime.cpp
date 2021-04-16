
#include "PGSpherePluginRuntime.h"
#include "PGLogger.h"

#define LOCTEXT_NAMESPACE "FPGSpherePluginRuntimeModule"

void FPGSpherePluginRuntimeModule::StartupModule()
{
	PGLOG_LOG("FPGSpherePluginRuntimeModule::StartupModule()");
}

void FPGSpherePluginRuntimeModule::ShutdownModule()
{
	PGLOG_LOG("FPGSpherePluginRuntimeModule::ShutdownModule()");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_GAME_MODULE(FPGSpherePluginRuntimeModule, PGSpherePluginRuntime)
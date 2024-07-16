// Copyright Epic Games, Inc. All Rights Reserved.

#include "CARLA_RGL.h"
#include "CRGL_Common.h"

#define LOCTEXT_NAMESPACE "FCARLA_RGLModule"



static TAutoConsoleVariable<FString> GRGLLogPath(
	TEXT("crgl.LogPath"),
	TEXT(""),
	TEXT("Specify output log path for RGL."));

static TAutoConsoleVariable<int32> GRGLLogLevel(
	TEXT("crgl.LogLevel"),
	RGL_LOG_LEVEL_TRACE,
	TEXT("Set the RGL log level:\n")
	TEXT("0 = RGL_LOG_LEVEL_ALL\n")
	TEXT("1 = RGL_LOG_LEVEL_DEBUG\n")
	TEXT("2 = RGL_LOG_LEVEL_INFO\n")
	TEXT("3 = RGL_LOG_LEVEL_WARN\n")
	TEXT("4 = RGL_LOG_LEVEL_ERROR\n")
	TEXT("5 = RGL_LOG_LEVEL_CRITICAL\n")
	TEXT("6 = RGL_LOG_LEVEL_OFF\n"));



void FCARLA_RGLModule::StartupModule()
{
	const auto Path = GRGLLogPath.GetValueOnAnyThread();
	const auto Level = (rgl_log_level_t)GRGLLogLevel.GetValueOnAnyThread();

	check(Level >= 0 && Level < RGL_LOG_LEVEL_COUNT);

	int32_t major, minor, patch;
	RGL::CheckRGLResult(
		rgl_get_version_info(&major, &minor, &patch));

	if (Path.Len() != 0 || Level != RGL_LOG_LEVEL_INFO)
	{
		rgl_configure_logging(
			Level,
			Path.Len() != 0 ? TCHAR_TO_UTF8(*Path) : nullptr,
			true);
	}

	UE_LOG(
		LogCarlaRGL, Log,
		TEXT("Using RGL v%i.%i.%i"),
		major, minor, patch);
}

void FCARLA_RGLModule::ShutdownModule()
{
	rgl_cleanup();
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCARLA_RGLModule, CARLA_RGL)

DEFINE_LOG_CATEGORY(LogCarlaRGL)
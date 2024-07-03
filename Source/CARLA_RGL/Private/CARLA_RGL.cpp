// Copyright Epic Games, Inc. All Rights Reserved.

#include "CARLA_RGL.h"

#define LOCTEXT_NAMESPACE "FCARLA_RGLModule"

void FCARLA_RGLModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCARLA_RGLModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCARLA_RGLModule, CARLA_RGL)

DEFINE_LOG_CATEGORY(LogCarlaRGL)
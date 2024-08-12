// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using EpicGames.Core;
using System.IO;
using System.Diagnostics;
using System;

public class CARLA_RGL : ModuleRules
{
  [CommandLine("-rgl-path")]
  string RGLPath = "";

  [CommandLine("-cuda-path")]
  string CUDAPath = Environment.GetEnvironmentVariable(
    "CUDA_PATH") ?? "";

  [CommandLine("-optix-path")]
  string NVOptiXPath = Environment.GetEnvironmentVariable(
    "OPTIX_INSTALL_DIR") ?? "";

  public CARLA_RGL(ReadOnlyTargetRules Target) : base(Target)
  {
    PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

    var DependenciesPath = Path.Combine(PluginDirectory, "Dependencies");

    if (!Directory.Exists(RGLPath))
    {
      RGLPath = Path.Combine(DependenciesPath, "RobotecGPULidar");
    }

    var FlatHashMapPath = Path.Combine(DependenciesPath, "flat_hash_map");
    if (Directory.Exists(FlatHashMapPath))
      PublicIncludePaths.Add(FlatHashMapPath);

    if (!Directory.Exists(RGLPath))
    {
      if (Target.Platform == UnrealTargetPlatform.Win64)
      {
      }
      else
      {
      }
    }

    var RGLBuildPath = Path.Combine(RGLPath, "Build");

    if (!Directory.Exists(CUDAPath))
      throw new DirectoryNotFoundException();

    if (!Directory.Exists(NVOptiXPath))
      throw new DirectoryNotFoundException();

    var CUDAIncludePath = Path.Combine(CUDAPath, "include");
    var CUDALibPath = Path.Combine(CUDAPath, "lib", "x64");

    PublicIncludePaths.Add(Path.Combine(RGLPath, "include"));

    var ExtraPublicLibraries = new string[]
    {
      Path.Combine(CUDALibPath, "cuda.lib"),
      Path.Combine(CUDALibPath, "cudart_static.lib"),
      Path.Combine(CUDALibPath, "nvml.lib"),
      Path.Combine(RGLBuildPath, "external", "cmake_git_version_tracking", "cmake_git_version_tracking.lib"),
      Path.Combine(RGLBuildPath, "external", "spdlog", "spdlog.lib"),
      Path.Combine(RGLBuildPath, "external", "yaml-cpp", "yaml-cpp.lib"),
      Path.Combine(RGLBuildPath, "RobotecGPULidar.lib"),
      Path.Combine(RGLBuildPath, "optixPrograms.lib")
    };

    foreach (var Lib in ExtraPublicLibraries)
      if (!File.Exists(Lib))
        throw new FileNotFoundException($"The required library \"{Lib}\" does not exist.");

    PublicAdditionalLibraries.AddRange(ExtraPublicLibraries);

    PublicDependencyModuleNames.AddRange(new string[]
    {
      "Core"
    });

    PrivateDependencyModuleNames.AddRange(new string[]
    {
      "CoreUObject",
      "Engine",
      "Slate",
      "SlateCore",
      "RenderCore",
      "MeshConversion"
    });

  }
}

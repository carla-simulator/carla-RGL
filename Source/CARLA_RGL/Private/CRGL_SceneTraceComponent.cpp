#include "CRGL_SceneTraceComponent.h"
#include "CRGL_Graph.h"
#include "CRGL_Scene.h"
#include "CRGL_Mesh.h"
#include "CRGL_Node.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"



ARGLLIDAR::ARGLLIDAR(
	const FObjectInitializer& Initializer) :
	Super(Initializer),
	LIDAR()
{
}

void ARGLLIDAR::BeginPlay()
{
	Super::BeginPlay();

	auto& ThisScene = RGL::FSceneContext::GetDefaultScene();

	auto Pattern = RGL::FLIDARPatternLibrary::GetDefault();

	RGL::FLIDAROptions Options;
	Options.Pattern = Pattern;
	LIDAR = RGL::FLIDAR(ThisScene, Options);

	LIDAR.GetSceneContext().RegisterWorld(GetWorld());
	LIDAR.SetTransform(RGL::ToRGLTransform(GetTransform()));
	LIDAR.Commit();
}

void ARGLLIDAR::EndPlay(EEndPlayReason::Type Unused)
{
	Super::EndPlay(Unused);
}

void ARGLLIDAR::Tick(float dt)
{
	auto Result = RayCast();
}

FLIDARResult ARGLLIDAR::RayCast()
{
	FLIDARResult Result = {};
	using RGL::FGraph;
	auto Transform = GetTransform();
	LIDAR.SetTransform(RGL::ToRGLTransform(Transform));
	LIDAR.Trace();
	auto R = LIDAR.GetResult();
	Result.Hit = R.HitMask;
	Result.HitDistances = R.HitDistances;
	Result.HitPosition = R.HitPositions;
	return Result;
}

void ARGLLIDAR::RayCast(FLIDARResult& OutResult)
{
	OutResult = RayCast();
}
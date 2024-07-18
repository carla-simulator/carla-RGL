#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Entity.h"
#include "CRGL_Mesh.h"
#include "CRGL_Node.h"
#include "CRGL_SceneTraceComponent.generated.h"



USTRUCT(BlueprintType)
struct CARLA_RGL_API FLIDARResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> Hit;

	UPROPERTY(BlueprintReadWrite)
	TArray<float> HitDistances;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector3f> HitPosition;
};



UCLASS(BlueprintType)
class CARLA_RGL_API ARGLLIDAR :
	public AActor
{
	GENERATED_BODY()
public:

	ARGLLIDAR(
		const FObjectInitializer& Initializer);

	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type) override;

	FLIDARResult RayCast();

	UFUNCTION(BlueprintCallable)
	void RayCast(FLIDARResult& OutResult);

	UFUNCTION(BlueprintCallable)
	void PrintRayCastResult(const FLIDARResult& InResult);

private:

	void EnumerateSceneEntities();
	void SetupTaskGraph();

	struct
	{
		RGL::FNode RayPoses;
		RGL::FNode LIDARTransform;
		RGL::FNode RayRanges;
		RGL::FNode RayTrace;
		RGL::FNode PointsYield;
	} Nodes;

	TArray<RGL::FMesh> Meshes;
	TArray<RGL::FEntity> Entities;

};

#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Entity.h"
#include "CRGL_Mesh.h"
#include "CRGL_LIDAR.h"
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
	void Tick(float dt) override;

	FLIDARResult RayCast();

	UFUNCTION(BlueprintCallable)
	void RayCast(FLIDARResult& OutResult);

private:

	RGL::FLIDAR LIDAR;

};

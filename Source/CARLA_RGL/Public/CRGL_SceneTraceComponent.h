#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Entity.h"
#include <span>
#include <vector>
#include "CRGL_SceneTraceComponent.generated.h"



struct FRayCastResult
{
	std::vector<int32_t> Hit;
	std::vector<rgl_vec3f> HitPosition;
};



UCLASS()
class ACRGL_SceneTraceComponent :
	public AActor
{
	GENERATED_BODY()
public:

	ACRGL_SceneTraceComponent(
		const FObjectInitializer& Initializer);

	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type) override;
	virtual void Tick(float DT) override;

	FRayCastResult RayCast();

private:

};

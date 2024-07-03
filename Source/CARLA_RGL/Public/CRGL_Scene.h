#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Scene.generated.h"



class ACRGL_Mesh;



UCLASS()
class ACRGL_Scene :
  public AActor
{
	GENERATED_BODY()
public:

	ACRGL_Scene(const FObjectInitializer& Initializer);

	void Initialize(const ACRGL_Mesh& Mesh);
	void SetTime(uint64_t nanoseconds);

	constexpr auto GetHandle()const { return scene; }

private:
	rgl_scene_t scene;
};

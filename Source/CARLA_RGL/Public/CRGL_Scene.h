#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Scene.generated.h"



class ACRGL_Mesh;



class FCRGL_Scene :
	public FCarlaRGLHandleMixin<rgl_scene_t>
{
public:

	void SetTime(uint64_t nanoseconds);

};



UCLASS()
class ACRGL_Scene :
  public AActor
{
	GENERATED_BODY()
public:

	ACRGL_Scene(const FObjectInitializer& Initializer);
};

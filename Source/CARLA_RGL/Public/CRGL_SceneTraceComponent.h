#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_SceneTraceComponent.generated.h"

UCLASS()
class ACRGL_SceneTraceComponent :
    public AActor
{
  GENERATED_BODY()
public:

  ACRGL_SceneTraceComponent(const FObjectInitializer& Initializer);

  void BeginPlay();
  void EndPlay();

  void Raytrace(
    ACRGL_Graph& SceneGraph,
    ACRGL_Scene* Scene = nullptr);

};

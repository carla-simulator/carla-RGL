#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Graph.generated.h"



UCLASS()
class ACRGL_Graph :
  public AActor
{
	GENERATED_BODY()
public:

	ACRGL_Graph(const FObjectInitializer& Initializer);

	void Run();
	void Destroy();
	void GetResultSize();
	void GetResultData();
	void GetResult();
	void AddChild();
	void RemoveChild();
	void SetPriority();
	void GetPriority();

private:

};

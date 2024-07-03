#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Texture.generated.h"



UCLASS()
class ACRGL_Texture :
  public AActor
{
	GENERATED_BODY()
public:

	ACRGL_Texture(const FObjectInitializer& Initializer);

	void Initialize(const void* Data, int32_t Width, int32_t Height);

	constexpr auto GetHandle() const { return texture; }

private:

	rgl_texture_t texture;
};

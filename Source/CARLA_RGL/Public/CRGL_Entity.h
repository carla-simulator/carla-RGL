#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Entity.generated.h"



class ACRGL_Texture;
class ACRGL_Mesh;
class ACRGL_Scene;



class FCRGL_Entity :
	public FCarlaRGLHandleMixin<rgl_entity_t>
{
public:
	void Initialize(const ACRGL_Scene& Scene, const ACRGL_Mesh& Mesh);
	void SetPose(const FTransform& Transform);
	void SetID(int32_t ID);
	void SetIntensityTexture(const ACRGL_Texture& Texture);
	void SetLaserRetro(float Retro);
	bool IsAlive();
};



UCLASS()
class ACRGL_Entity :
	public AActor,
	public FCRGL_Entity
{
	GENERATED_BODY()

public:

	ACRGL_Entity(const FObjectInitializer& Initializer);

};

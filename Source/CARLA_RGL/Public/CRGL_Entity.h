#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Entity.generated.h"



class FCRGL_Scene;
class FCRGL_Mesh;
class ACRGL_Texture;
class ACRGL_Mesh;
class ACRGL_Scene;



class FCRGL_Entity :
	public FCarlaRGLHandleMixin<rgl_entity_t>
{
public:

	FCRGL_Entity() = default;
	FCRGL_Entity(FCRGL_Entity&&) = default;
	FCRGL_Entity& operator=(FCRGL_Entity&&) = default;
	~FCRGL_Entity();

	static FCRGL_Entity Create(
		const FCRGL_Mesh& Mesh);

	static FCRGL_Entity Create(
		const FCRGL_Scene& Scene,
		const FCRGL_Mesh& Mesh);

	void SetPose(const FTransform& Transform);
	void SetID(int32_t ID);
	void SetIntensityTexture(const ACRGL_Texture& Texture);
	void SetLaserRetro(float Retro);
	bool IsAlive();
	void Destroy();
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

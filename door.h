#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "door.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API Udoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	Udoor();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindAudioComponent();
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float GetMass();

protected:
	virtual void BeginPlay() override;

private:

	float InitialYaw;

	float DoorsLastOpen = 50.f;

	UPROPERTY(EditAnywhere)
	float MassToOpen = 60.f;

	UPROPERTY(EditAnywhere)
	float DoorsDelay = 1.f;

	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
	float OpenDoorSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float CloseDoorSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PreassurePlate;

	UPROPERTY()
	UAudioComponent* DoorsSound = nullptr;

	bool DidClosed = false;
};

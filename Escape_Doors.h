#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "Escape_Doors.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UEscape_Doors : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEscape_Doors();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CheckKey();

protected:
	virtual void BeginPlay() override;

private:

	float InitialYaw;

	float Delta = 1.f;

	UPROPERTY(EditAnywhere)
		float OpenDelay = 1.f;

	UPROPERTY(EditAnywhere)
		float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
		float OpenDoorSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* Locker = nullptr;

	UPROPERTY()
		UAudioComponent* OpenSound = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens = nullptr;

	bool DidOpened = false;

	bool IsLocked = true;

	float TimeDoorsOpened = 0.f;

		
};

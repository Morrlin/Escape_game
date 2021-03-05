#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoorInput.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UOpenDoorInput : public UActorComponent
{
	GENERATED_BODY()

public:
	UOpenDoorInput();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
            
	bool FindAudioComponent(AActor*);
	void BindOpener();
	void OpenDoor();
	void ToOpen();
	FHitResult GetHittenObject();

protected:
	virtual void BeginPlay() override;

private:

	float TargetYaw = 0.f;

	float Reach = 100.f;

	float Delta = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorSpeed = 1.f;

	UPROPERTY()
		UAudioComponent* DoorsSound = nullptr;

	UInputComponent* Opener = nullptr;

	AActor* Doors = nullptr;

	bool IsOpen = false;
	bool DoOpen = false;
	bool DidOpened = false;

};

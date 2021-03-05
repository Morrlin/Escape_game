#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "trap.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API Utrap : public UActorComponent
{
	GENERATED_BODY()

public:	
	Utrap();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindAudioComponent();
	void OpenTrap();
	void ChecksStatue();

protected:
	virtual void BeginPlay() override;

private:
	float Delta = 0.f;

	float InitialRoll = 0.f;

	float InitialYaw = 0.f;

	UPROPERTY(EditAnywhere)
		float TargetPitch = 80.f;

	UPROPERTY()
		UAudioComponent* TrapSound = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* Trigger = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* Statue = nullptr;

	bool IsStatue = true;

	bool DoOpen = false;

	bool DidPlayed = false;
};

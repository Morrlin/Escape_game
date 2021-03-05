#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Gate.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UGate : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGate();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenGate();
	void CheckLever();

protected:
	virtual void BeginPlay() override;

private:

	float Delta = 0.f; 

	float TargetZ = 333.f;

	float InitialZ = 0.f;

	float FinalZ = 0.f;

	UPROPERTY(EditAnywhere)
		float OpenGateSpeed = 100.f;

	UPROPERTY()
		UAudioComponent* GateSound = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* Trigger = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens = nullptr;

	bool IsOpened = false;

	bool DoOpen = false;

	bool DidStarted = false;
};

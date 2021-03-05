#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "SFX_Player.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API USFX_Player : public UActorComponent
{
	GENERATED_BODY()

public:
	USFX_Player();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void IsOverlapping();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* Trigger = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens = nullptr;

	UPROPERTY()
		UAudioComponent* UnlockSound = nullptr;

	bool DidOpened = false;

};

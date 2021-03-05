#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TorchSound.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UTorchSound : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTorchSound();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
		UAudioComponent* TorchSound = nullptr;	
};

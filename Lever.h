#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lever.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API ULever : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULever();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void BindLever();
	void ToOpen();
	void GetHittenObject();
	void MoveLever();

protected:
	virtual void BeginPlay() override;

private: 

	UInputComponent* LeverUse = nullptr;

	UPROPERTY()
		UAudioComponent* LeverSound = nullptr;
		
	UPROPERTY(EditAnywhere)
		float TargetRoll = -30.f;

	UPROPERTY(EditAnywhere)
		float Reach = 100.f;

	AActor* Lever = nullptr;

	float Delta = 0.f;

	bool DoMove = false;
};

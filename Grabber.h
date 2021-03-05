#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrabber();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GetPlayerVectors();
	void Grab();
	void Drop();
	void CheckPhysicsHandle();
	void CheckGrabber();
	FHitResult GetHittenObject();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float Reach = 120.f;

	FRotator PlayerRotation;
	FVector PlayerPossition;
	FVector LineTraceEnd;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* Grabber = nullptr;

	AActor* ActorHit = nullptr;

	FHitResult Hit;
};

#include "Escape_Doors.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h" 
#include "Components/AudioComponent.h"

UEscape_Doors::UEscape_Doors()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEscape_Doors::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;

	TargetYaw += GetOwner()->GetActorRotation().Yaw;

	if (!Locker)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has door component, but preassure plate is not setten !"), *GetOwner()->GetName());
	}

	OpenSound = GetOwner()->FindComponentByClass<UAudioComponent>();
}

void UEscape_Doors::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Delta = DeltaTime;

	CheckKey();

	if (!IsLocked)
	{
		if((GetWorld()->GetTimeSeconds() - TimeDoorsOpened) > OpenDelay)
		{
			OpenDoor(DeltaTime);
		}
	}
}

void UEscape_Doors::OpenDoor(float DeltaTime)
{
	if (!DidOpened)
	{
		OpenSound->Play();
		DidOpened = true;
	}
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator CurrentRotation(0.f, CurrentYaw, 0.f);
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, OpenDoorSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Door Rotation is: %f"), CurrentYaw);   Give Current Rotation  
}

void UEscape_Doors::CheckKey()
{   
	if(Locker && OpenSound && ActorThatOpens)
	{
		if (Locker->IsOverlappingActor(ActorThatOpens))
		{
			TimeDoorsOpened = GetWorld()->GetTimeSeconds();

			IsLocked = false;
		}
	}
}



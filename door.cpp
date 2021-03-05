#include "door.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h" 
#include "Components/AudioComponent.h"

Udoor::Udoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void Udoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;

	TargetYaw += GetOwner()->GetActorRotation().Yaw;

	if (!PreassurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has door component, but preassure plate is not setten !"), *GetOwner()->GetName());
	}

	FindAudioComponent();
}

void Udoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PreassurePlate && GetMass() > MassToOpen)
	{
		OpenDoor(DeltaTime);
		DoorsLastOpen = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorsLastOpen > DoorsDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	
}

void Udoor::FindAudioComponent()
{
	DoorsSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorsSound)
	{
		UE_LOG(LogTemp, Error, TEXT("No audio component found ! on %s"), *GetOwner()->GetName());
	}
}

void Udoor::OpenDoor(float DeltaTime)
{

	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator CurrentRotation(0.f, CurrentYaw, 0.f);
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, OpenDoorSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Door Rotation is: %f"), CurrentYaw);           Give Current Rotation

	if (static_cast<int32>(CurrentYaw - 2) == static_cast<int32>(InitialYaw))
	{		
		DidClosed = false;
		DoorsSound->Play();
	}

}

void Udoor::CloseDoor(float DeltaTime)
{
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator CurrentRotation(0.f, CurrentYaw, 0.f);
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, CloseDoorSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
	if (static_cast<int32>(CurrentYaw - 2) == static_cast<int32>(InitialYaw) && !DidClosed)
	{
		DidClosed = true;
		DoorsSound->Play();
	}
}

float Udoor::GetMass()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	PreassurePlate->GetOverlappingActors(OverlappingActors);

	for (AActor *Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	//UE_LOG(LogTemp, Warning, TEXT("Mass on Trigger is: %f"), TotalMass)           Give On-Trigger Mass

	return TotalMass;
}


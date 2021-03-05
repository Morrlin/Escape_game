#include "trap.h"
#include "Components/AudioComponent.h"

Utrap::Utrap()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void Utrap::BeginPlay()
{
	Super::BeginPlay();
	
	TargetPitch += GetOwner()->GetActorRotation().Pitch;
	InitialRoll = GetOwner()->GetActorRotation().Roll;
	InitialYaw = GetOwner()->GetActorRotation().Yaw;

	TrapSound = GetOwner()->FindComponentByClass<UAudioComponent>();
}

void Utrap::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Delta = DeltaTime;

	ChecksStatue();

	if (DoOpen)
	{
		OpenTrap();
	}
}

void Utrap::FindAudioComponent()
{
	TrapSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!TrapSound)
	{
		UE_LOG(LogTemp, Error, TEXT("No audio component found ! on %s"), *GetOwner()->GetName());
	}
}

void Utrap::OpenTrap()
{
	if (!DidPlayed)
	{
		TrapSound->Play();
		DidPlayed = true;
	}

	float CurrentPitch = GetOwner()->GetActorRotation().Pitch;
	FRotator CurrentRotation(CurrentPitch, InitialYaw, InitialRoll);
	CurrentRotation.Pitch = CurrentPitch;
	CurrentRotation.Pitch = FMath::FInterpConstantTo(CurrentPitch, TargetPitch, Delta, 800);
	GetOwner()->SetActorRotation(CurrentRotation);

	/*
	UE_LOG(LogTemp, Warning, TEXT("Target is: %f"), TargetPitch);
	UE_LOG(LogTemp, Warning, TEXT("Rotation Is %s"), *CurrentRotation.ToString());        Get Target & CurrentRotation    
	*/

	if (static_cast<int32>(CurrentPitch + 2) == static_cast<int32>(TargetPitch))
	{
		DoOpen = false;
	}
}

void Utrap::ChecksStatue()
{
	if (!Trigger->IsOverlappingActor(Statue))
	{
		DoOpen = true;
	}
}

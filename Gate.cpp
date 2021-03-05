#include "Gate.h"
#include "Components/AudioComponent.h"

UGate::UGate()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGate::BeginPlay()
{
	Super::BeginPlay();

	InitialZ = GetOwner()->GetActorLocation().Z;

	TargetZ += GetOwner()->GetActorLocation().Z;

	if (!Trigger)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has door component, but preassure plate is not setten !"), *GetOwner()->GetName());
	}

	GateSound = GetOwner()->FindComponentByClass<UAudioComponent>();
}

void UGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Delta = DeltaTime;

	CheckLever();

	if(DoOpen)
	{
		OpenGate();
	}
}

void UGate::OpenGate()
{
	if (DidStarted)
	{
		DidStarted = false;
		GateSound->Play();
	}
	float CurrentZ = GetOwner()->GetActorLocation().Z;
	FVector CurrentPosition = GetOwner()->GetActorLocation();
	CurrentPosition.Z = CurrentZ;
	//UE_LOG(LogTemp, Warning, TEXT("CurrentZ: %f, CurrentPosition.Z: %f"), CurrentZ, CurrentPosition.Z);               Current Possition State

	if (static_cast<int32>(CurrentZ) == static_cast<int32>(TargetZ))
	{
		FinalZ = InitialZ;
	}
	else if (static_cast<int32>(CurrentZ) == static_cast<int32>(InitialZ))
	{
		FinalZ = TargetZ;
	}

	CurrentPosition.Z = FMath::FInterpConstantTo(CurrentZ, FinalZ, Delta, OpenGateSpeed);
	GetOwner()->SetActorLocation(CurrentPosition);
	//UE_LOG(LogTemp, Warning, TEXT("Gate Z is: %f"), CurrentZ);   Current Z Possition
		
	if (static_cast<int32>(CurrentZ +2) == static_cast<int32>(FinalZ) || static_cast<int32>(CurrentZ - 2) == static_cast<int32>(FinalZ))
	{
		DoOpen = false;
		//UE_LOG(LogTemp, Warning, TEXT("DoOpen is now false"));    Current State
	}
}

void UGate::CheckLever()
{
	if (GateSound && ActorThatOpens)
	{
		if (Trigger->IsOverlappingActor(ActorThatOpens))
		{
			DoOpen = true;
			DidStarted = true;
		}
	}
}


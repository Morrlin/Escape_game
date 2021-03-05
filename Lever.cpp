#include "Lever.h"
#include "Math/UnrealMathUtility.h"
#include "Components/AudioComponent.h"

ULever::ULever()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULever::BeginPlay()
{
	Super::BeginPlay();

	BindLever();
}

void ULever::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	Delta = DeltaTime;

	/*
	GetHittenObject();
	if (Lever)
	{
		UE_LOG(LogTemp, Warning, TEXT("Traced Object is %s"), *Lever->GetName())        Trace Result
	}
	*/

	if (DoMove)
	{
		MoveLever();
	}
}

void ULever::BindLever()
{
	LeverUse = GetOwner()->FindComponentByClass<UInputComponent>();

	if (LeverUse)
	{ 
		//UE_LOG(LogTemp, Warning, TEXT("Opener Found"));        UInputComponent Pointer State
		LeverUse->BindAction("MoveLever", IE_Pressed, this, &ULever::ToOpen);
	}
}

void ULever::ToOpen()
{
	GetHittenObject();

	/*
	if (Lever)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Roll is %f"), Lever->GetActorRotation().Roll);       Get Current Roll
	}
	*/

	if (LeverSound && Lever)
	{
		if (static_cast<int32>(Lever->GetActorRotation().Roll) == -74)
		{
			TargetRoll = -105.f;
			DoMove = true;
			LeverSound->Play();
		}
		else if (static_cast<int32>(Lever->GetActorRotation().Roll) == -104)
		{
			TargetRoll = -73.f;
			DoMove = true;
			LeverSound->Play();
		}
	}
}

void ULever::GetHittenObject()
{
	FVector PlayerPossition;
	FRotator PlayerRotation;
	FVector LineTraceEnd;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerPossition, PlayerRotation);

	LineTraceEnd = PlayerPossition + PlayerRotation.Vector() * Reach;

	FHitResult Hit;

	const FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		Hit,
		PlayerPossition,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParams
	);

	Lever = Hit.GetActor();

	if (Lever)
	{
		LeverSound = Lever->FindComponentByClass<UAudioComponent>();
	}
}

void ULever::MoveLever()
{
	float CurrentRoll = Lever->GetActorRotation().Roll;
	FRotator CurrentRotaion = Lever->GetActorRotation();
	CurrentRotaion.Roll = CurrentRoll;
	CurrentRotaion.Roll = FMath::FInterpTo(CurrentRoll, TargetRoll, Delta, 3.f);
	Lever->SetActorRotation(CurrentRotaion);

	if (static_cast<int32>(CurrentRoll + 1) == static_cast<int32>(TargetRoll) || static_cast<int32>(CurrentRoll - 1) == static_cast<int32>(TargetRoll))
	{
		DoMove = false;
		//UE_LOG(LogTemp, Warning, TEXT("DoMove is now false"));      DoMove State
	} 
}


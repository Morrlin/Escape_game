#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "GameFrameWork/Actor.h"
#include "OpenDoorInput.h"
#include "Components/AudioComponent.h"

UOpenDoorInput::UOpenDoorInput()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoorInput::BeginPlay()
{
	Super::BeginPlay();

	BindOpener();
}

void UOpenDoorInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Delta = DeltaTime;

	if (DoOpen)
	{
		OpenDoor();
	}
}

void UOpenDoorInput::BindOpener()
{
	Opener = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Opener)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Opener Found"));        UInputComponent Pointer State
		Opener->BindAction("OpenCloseDoor", IE_Pressed, this, &UOpenDoorInput::ToOpen);
	}
}


bool UOpenDoorInput::FindAudioComponent(AActor* Actor)
{
	DoorsSound = Actor->FindComponentByClass<UAudioComponent>();
	if (!DoorsSound && Actor)
	{
		UE_LOG(LogTemp, Error, TEXT("No audio component found ! on %s"), *Actor->GetName());              
		return false;
	}
	return true;
}

void UOpenDoorInput::OpenDoor()
{
	float CurrentYaw = Doors->GetActorRotation().Yaw;
	FRotator CurrentRotation(0.f, CurrentYaw, 0.f);
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, Delta, DoorSpeed);
	Doors->SetActorRotation(CurrentRotation);

	/*                       
	UE_LOG(LogTemp, Warning, TEXT("CurrentYaw: %i"), static_cast<int32>(CurrentYaw))    
	UE_LOG(LogTemp, Warning, TEXT("TargetYaw: %i"), static_cast<int32>(TargetYaw))                        Get Current & Target Yaw
	*/

	if (static_cast<int32>(CurrentYaw + 1) == static_cast<int32>(TargetYaw) || static_cast<int32>(CurrentYaw - 1) == static_cast<int32>(TargetYaw))
	{
		DoOpen = false;
      	//UE_LOG(LogTemp, Warning, TEXT("DoOpen is now false"));         DoOpen State
	}
}

void UOpenDoorInput::ToOpen()
{
	GetHittenObject();
	//UE_LOG(LogTemp, Warning, TEXT("Hitten Object: %s"), *Doors->GetName());    Hit Result
	if (Doors && FindAudioComponent(Doors))
	{
		if(static_cast<int32>(Doors->GetActorRotation().Yaw) == 91 )
		{
			DoorsSound->Play();
			TargetYaw = Doors->GetActorRotation().Yaw + 65;
		}
		else if (static_cast<int32>(Doors->GetActorRotation().Yaw) == 155)
		{
			UE_LOG(LogTemp, Warning, TEXT("156"));
			DoorsSound->Play();
			TargetYaw = Doors->GetActorRotation().Yaw - 65;
		}

		DoOpen = true;
	}
}

FHitResult UOpenDoorInput::GetHittenObject()
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
     
	Doors = Hit.GetActor();
	
	return Hit;
}



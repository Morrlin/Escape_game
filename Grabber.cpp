#include "DrawDebugHelpers.h"
#include "GameFrameWork/PlayerController.h"
#include "Grabber.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	CheckPhysicsHandle();

	CheckGrabber();
}                         

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetPlayerVectors();

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

	/*
	DrawDebugLine(
		GetWorld(),
		PlayerPossition,
		LineTraceEnd,                Ray Trace  
		FColor(1, 1, 1),
		false,
		0.f,
		0,
		1.f
	);
	*/
}

void UGrabber::GetPlayerVectors()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerPossition, PlayerRotation);
	LineTraceEnd = PlayerPossition + PlayerRotation.Vector() * Reach;
}

void UGrabber::Grab()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grabber pressed !"));  Current State

	GetPlayerVectors();

    Hit = GetHittenObject();

	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();

	if (Hit.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
	}
}

void UGrabber::Drop()
{
	PhysicsHandle->ReleaseComponent();
	//UE_LOG(LogTemp, Warning, TEXT("Grabber realeased !"));    Current State
}

void UGrabber::CheckPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s"), *(GetOwner()->GetName()));
	}
}

void UGrabber::CheckGrabber()
{
	Grabber = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Grabber)
	{
		Grabber->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Grabber->BindAction("Grab", IE_Released, this, &UGrabber::Drop);
	}
}

FHitResult UGrabber::GetHittenObject()
{
	GetPlayerVectors();

	const FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		Hit,
		PlayerPossition,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
    ActorHit = Hit.GetActor();

	/*
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("LineTrace Hits: %s"), *ActorHit->GetName());     Hit Result
	}
	*/

	return Hit;
}


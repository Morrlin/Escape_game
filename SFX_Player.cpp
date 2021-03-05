#include "SFX_Player.h"
#include "Components/AudioComponent.h"

USFX_Player::USFX_Player()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USFX_Player::BeginPlay()
{
	Super::BeginPlay();

	UnlockSound = GetOwner()->FindComponentByClass<UAudioComponent>();
}

void USFX_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	IsOverlapping();
}

void USFX_Player::IsOverlapping()
{
	if (Trigger->IsOverlappingActor(ActorThatOpens))
	{
		if (!DidOpened)
		{
			UnlockSound->Play();
			DidOpened = true;
		}
	}
}

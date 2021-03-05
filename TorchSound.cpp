#include "Components/AudioComponent.h"
#include "TorchSound.h"

UTorchSound::UTorchSound()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTorchSound::BeginPlay()
{
	Super::BeginPlay();

	TorchSound = GetOwner()->FindComponentByClass<UAudioComponent>();
}

void UTorchSound::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!TorchSound->IsPlaying())
	{
		TorchSound->Play();
	}
}


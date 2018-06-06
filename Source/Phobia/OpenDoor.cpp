// toturial-continued dev by Tjalfe

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include <Engine/World.h>

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// pool the trigger every frame.
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}

	//check if close time is hit.
	if ((LastOpenTime + DelayForClose) <= GetWorld()->GetTimeSeconds()) {
		CloseDoor();
	}
}

/*
	functionality
*/
void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(.0f, OpenAngle, .0f));
}
void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(.0f, .0f, .0f));
}

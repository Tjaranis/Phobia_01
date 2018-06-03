// toturial-continued dev by Tjalfe

#include "OpenDoor.h"
#include "Gameframework/Actor.h"


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

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// pool the trigger every frame.
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
	//if actor that opens is in volume.
	//open door.
}

/*
	functionality
*/
void UOpenDoor::OpenDoor()
{
	// get actor.
	AActor* Owner = GetOwner();
	//rotation
	FRotator NewRotation = FRotator(.0f, -83.0f, .0f);
	//change owner rotated
	Owner->SetActorRotation(NewRotation);
}

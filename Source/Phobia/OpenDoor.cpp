// toturial-continued dev by Tjalfe

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include <Engine/World.h>

#define OUT

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

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing PressurePlate component"), *(GetOwner()->GetName()));
	}
	//to get the player actor
	
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		if (GetTotalMassOfActorsOnPlate() >= TriggerMassToOpen && PressurePlate->IsOverlappingActor(ActorKeyToOpen)) {
			OnOpenRequest.Broadcast();
		}
		else {
			OnCloseRequest.Broadcast();
		}
}

/*
	functionality
*/
float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;
	//find overlapping actors.
	TArray<AActor*> OverlappingActors;
	if (PressurePlate) {
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
		//iterated and add the actors weight together.
		for (const auto* Actor : OverlappingActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
		return TotalMass;
	}else{ return 0;}
}

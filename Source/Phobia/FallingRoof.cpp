// toturial-continued dev by Tjalfe

#include "FallingRoof.h"
#include "Gameframework/Actor.h"
#include <Engine/World.h>

// Sets default values for this component's properties
UFallingRoof::UFallingRoof()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFallingRoof::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ActorThatActivates = GetWorld()->GetFirstPlayerController()->GetPawn();
	StartingLocation = GetOwner()->GetActorLocation();
	/*test stuff*/
	//get owner name.
	FString ObjectName = GetOwner()->GetName();
	//get owner position.
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	// report for test.
	UE_LOG(LogTemp, Warning, TEXT("%s Object reached initiated and Loc at %s"), *ObjectName, *ObjectPos);
	
	AActor* Owner = GetOwner();
	FVector NewLoc = StartingLocation;
	NewLoc.Z -= MoveAmount;
	Owner->SetActorRelativeLocation(NewLoc, true);
}


// Called every frame
void UFallingRoof::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// roof decend 
	if (PressurePlate->IsOverlappingActor(ActorThatActivates)) {
		RoofDecend();
	}
}

void UFallingRoof::RoofDecend()
{
	FVector OwnerCurrentLoc= GetOwner()->GetActorLocation();

		if (OwnerCurrentLoc.Z >= StartingLocation.Z) {
			AActor* Owner = GetOwner();
			FVector NewLoc = StartingLocation;
			NewLoc.Z -= MoveAmount;
			Owner->SetActorRelativeLocation(NewLoc, true);
		}
		else if (OwnerCurrentLoc.Z <= (StartingLocation.Z - MoveAmount)) {
			AActor* Owner = GetOwner();
			Owner->SetActorRelativeLocation(StartingLocation, true);
		}

	//get owner name.
	FString ObjectName = GetOwner()->GetName();
	//get owner position.
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	// report for test.
	UE_LOG(LogTemp, Warning, TEXT("%s Object reached initiated and Loc at %s"), *ObjectName, *ObjectPos);
}


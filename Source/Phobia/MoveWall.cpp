// toturial-continued dev by Tjalfe

#include "MoveWall.h"
#include "Gameframework/Actor.h"
#include <Engine/World.h>


// Sets default values for this component's properties
UMoveWall::UMoveWall()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveWall::BeginPlay()
{
	Super::BeginPlay();

	PlayerActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	FVector ClosedLoc = GetOwner()->GetActorLocation();
	FVector OpenLoc = ClosedLoc;
	OpenLoc.X -= MoveAmount;
}


// Called every frame
void UMoveWall::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// open wall
	
		if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
			OpenWall();
		}

}

void UMoveWall::OpenWall()
{
	FVector t(10000.f, 10000.f, 10000.f);
	AActor* Owner = GetOwner();
	//change owner rotated
	Owner->SetActorLocation(t);
}

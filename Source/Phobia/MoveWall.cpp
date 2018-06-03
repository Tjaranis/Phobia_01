// toturial-continued dev by Tjalfe

#include "MoveWall.h"
#include "Gameframework/Actor.h"


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

	AActor* Owner = GetOwner();
	//rotation
	FVector NewVector = GetOwner()->GetActorLocation();
	NewVector.X -= MoveAmount;
	//change owner rotated
	Owner->SetActorRelativeLocation(NewVector,true);
	
}


// Called every frame
void UMoveWall::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


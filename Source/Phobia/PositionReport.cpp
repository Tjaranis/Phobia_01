// toturial-continued dev by Tjalfe

#include "PositionReport.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	//get owner name.
	FString ObjectName = GetOwner()->GetName();
	//get owner position.
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	// report for test.
	UE_LOG(LogTemp, Warning, TEXT("%s Object reached initiated and Loc at %s"), *ObjectName,*ObjectPos);


	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// toturial-continued dev by Tjalfe

#include "CanGrab.h"
#include <Engine/World.h>
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UCanGrab::UCanGrab()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCanGrab::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//get owner name.
	FString ObjectName = GetOwner()->GetName();
	//get owner position.
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	FindPhysicsHandleComponent(ObjectName);
	FindInputComponent(ObjectName);

}

void UCanGrab::FindInputComponent(FString &ObjectName)
{
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s got input component"), *ObjectName);
		InputComponent->BindAction("Grab", IE_Pressed, this, &UCanGrab::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UCanGrab::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing Input component"), *ObjectName);
	}
}

void UCanGrab::FindPhysicsHandleComponent(FString &ObjectName)
{
	if (PhysicsHandle) {
		//do stuff
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing physic component"), *ObjectName);
	}
}

void UCanGrab::Grab() {
		UE_LOG(LogTemp, Warning, TEXT("grabbing method called"));
		GetFirstPhysicsBodyInReach();
}
void UCanGrab::Release() {
	UE_LOG(LogTemp, Warning, TEXT("released method called"));
}

// Called every frame
void UCanGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCanGrab::GetFirstPhysicsBodyInReach()
{
	// get player view.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
	);

	//logging rotation and loc
	/*UE_LOG(LogTemp, Warning, TEXT("PlayerViewPointLocation: %s, PlayerViewPointRotator: %s"),
	*PlayerViewPointLocation.ToString(),
	*PlayerViewPointRotator.ToString()
	);*/

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotator.Vector()*Reach;

	///draw debug line
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	///setup guery parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///line-trace (ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	///see what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *(ActorHit->GetName()));
	}
}


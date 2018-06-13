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
	//initiated the PhysicsHandle by finding the attached physics object from GetOwner
	InitializePhysicsHandle();
	//initiated the InputComponent by finding the attached Input Component from GetOwner
	InitializeInputComponent();

}
// Called every frame
void UCanGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if the physics handle is attachedd
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent) 
	{
		//move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd(Reach));
	}
}

void UCanGrab::InitializeInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UCanGrab::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UCanGrab::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing Input component"), *(GetOwner()->GetName()));
	}
}

void UCanGrab::InitializePhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {/*do stuff*/}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing physic component"), *(GetOwner()->GetName()));
	}
}

void UCanGrab::Grab() {
		///line trace and see if we reach any actors with physics body collision channel set
		auto HitResult = GetFirstPhysicsBodyInReach();
		auto ComponentToGrab = HitResult.GetComponent();
		auto ActorHit= HitResult.GetActor();
		//if physics object hit exists, Grab object
		if (ActorHit != nullptr) {
			if (!PhysicsHandle) { return; }
			PhysicsHandle->GrabComponent(
				ComponentToGrab,
				NAME_Name,
				ActorHit->GetActorLocation(),
				true //allow rotation
			);
		}
}
void UCanGrab::Release() {
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UCanGrab::GetFirstPhysicsBodyInReach()
{
	///setup guery parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	///line-trace (ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		GetLineTraceEnd(Reach),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	///see what we hit, for test REMOVE LATER
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

FVector UCanGrab::GetLineTraceEnd(float lengthOfLine)
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
	);
	return PlayerViewPointLocation + PlayerViewPointRotator.Vector()*lengthOfLine;
}



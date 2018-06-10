// toturial-continued dev by Tjalfe

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CanGrab.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOBIA_API UCanGrab : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCanGrab();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//how far ahead of player can be reached
	float Reach = 100.f;
	bool holding = false;
	
	UPhysicsHandleComponent* PhysicsHandle=nullptr;
	UInputComponent* InputComponent = nullptr;
	//ray-cast and grab what is in reach
	void Grab();
	void Release();
};

// toturial-continued dev by Tjalfe

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOBIA_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//get total mass of Actors.
	float GetTotalMassOfActorsOnPlate();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FOnOpenRequest OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FOnCloseRequest OnCloseRequest;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate=nullptr;
	
	UPROPERTY(EditAnywhere)
		AActor* ActorKeyToOpen= nullptr;

	UPROPERTY(EditAnywhere)
		float TriggerMassToOpen = 50;

	AActor* Owner=nullptr;
};

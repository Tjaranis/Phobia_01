// toturial-continued dev by Tjalfe

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MoveWall.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOBIA_API UMoveWall : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveWall();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenWall();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	FVector ClosedLoc;
	FVector OpenLoc;

	UPROPERTY(VisibleAnywhere)
		float MoveAmount = 350.0f;
	
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
		float DelayForClose = 1.0f;
	
	float LastOpenTime;
	
	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;

	AActor* PlayerActorThatOpens;
	
};

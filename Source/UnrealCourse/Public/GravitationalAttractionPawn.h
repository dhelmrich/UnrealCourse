// Forschungszentrum Jülich GmbH. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GravitationalAttractionPawn.generated.h"

UCLASS()
class UNREALCOURSE_API AGravitationalAttractionPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGravitationalAttractionPawn();

	UPROPERTY(VisibleAnywhere)
        double Mass = 1;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
        FVector Velocity{};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

 // Forschungszentrum Jülich GmbH. All rights reserved. 


#include "GravitationalAttractionPawn.h"
#include "SolarSystem.h"

// Sets default values
AGravitationalAttractionPawn::AGravitationalAttractionPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGravitationalAttractionPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGravitationalAttractionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGravitationalAttractionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


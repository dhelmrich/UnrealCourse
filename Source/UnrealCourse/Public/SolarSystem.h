// Forschungszentrum Jülich GmbH. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarSystem.generated.h"


USTRUCT(BlueprintType)
struct FPlanetStats {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    double Mass = 1;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    double Size = 1;
    
    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    FVector Position = FVector{0};

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    FVector Velocity = FVector{0};
};


UCLASS(BlueprintType)
class UNREALCOURSE_API ASolarSystem : public AActor {
    GENERATED_BODY()

    UPROPERTY()
    TArray<AActor*> Planets = {};

    UPROPERTY()
    AActor* Sun = nullptr;

public:
    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category=Properties)
    TArray<FPlanetStats> PlanetData;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category=Properties)
    FPlanetStats SunData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Properties)
    TSubclassOf<AActor> PlanetActor;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Properties)
    TSubclassOf<AActor> SunActor;
    
    // Sets default values for this actor's properties
    ASolarSystem();

    // Called when the Actor is Spawned / Placed in the World
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick(const float DeltaTime) override;

private:
    
    /** Calculate the forces that act on all Planets in this system and update the Velocities of the Planets accordingly
     */
    void UpdatePlanetVelocities(float DeltaTime);
};

// "Forschungszentrum Jülich GmbH. All rights reserved. "

#include "SolarSystem.h"

static constexpr double GravitationalConstant = 6.6743e-11;
static constexpr double UnrealLengthUnit = 1e9;  // 1 Unit in Unreal is 10^6 m
static constexpr double UnrealTimeUnit = 50*24*60*60;


ASolarSystem::ASolarSystem() {
    PrimaryActorTick.bCanEverTick = true;
    SetActorTickEnabled(true);
}


void ASolarSystem::BeginPlay() {
    Super::BeginPlay();
    
    check(SunActor && PlanetActor)

    // Spawn Parameters for Planets and Sun
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.Owner = this;

    // ToDo: ChildActorComponents?
    
    // Construct Sun
    Sun = GetWorld()->SpawnActor<AActor>(SunActor, SpawnParameters);
    Sun->SetActorScale3D(FVector{SunData.Size});
    
    // Construct Planets
    Planets.Reset();
    for (const auto& Data : PlanetData) {
        const FVector Location = GetActorLocation() + Data.Position / UnrealLengthUnit;
        
        AActor* NewPlanet = GetWorld()->SpawnActor<AActor>(PlanetActor, Location, FRotator::ZeroRotator, SpawnParameters);
        NewPlanet->SetActorScale3D(FVector{Data.Size});
        
        Planets.Add(NewPlanet);
    }
}


void ASolarSystem::Tick(const float DeltaTime) {
    Super::Tick(DeltaTime);
    
    UpdatePlanetVelocities(DeltaTime);

    // Update the Position of the Planets based on the velocities and update the Location of their representing Actors 
    for (int i = 0; i < PlanetData.Num(); i++) {
        PlanetData[i].Position += PlanetData[i].Velocity * UnrealTimeUnit * DeltaTime;

        const FVector Location = GetActorLocation() + PlanetData[i].Position / UnrealLengthUnit;
        Planets[i]->SetActorLocation(Location, true);
    }
}


static constexpr double CalculateForce(const double Mass1, const double Mass2, const double DistanceSquared) {
    return Mass1 * Mass2 / DistanceSquared * GravitationalConstant;
}


void ASolarSystem::UpdatePlanetVelocities(const float DeltaTime) {
    for (int i = 0; i < PlanetData.Num(); i++) {
        FPlanetStats& PlanetA = PlanetData[i];
        
        // Calculate the force towards the sun
        const double SunDist = FVector::DistSquared(PlanetA.Position, SunData.Position);
        double Force = CalculateForce(PlanetA.Mass, SunData.Mass, SunDist);
        const FVector ToSun = (GetActorLocation() - PlanetA.Position).GetSafeNormal() * Force;
        PlanetA.Velocity += ToSun / PlanetA.Mass * UnrealTimeUnit *  DeltaTime;
        
        for (int j = i+1; j < PlanetData.Num(); j++) {
            FPlanetStats& PlanetB = PlanetData[j];

            // Calculate the Attraction from 
            const double Dist = FVector::DistSquared(PlanetA.Position, PlanetB.Position);
            Force = CalculateForce(PlanetA.Mass, PlanetB.Mass, Dist);
            const FVector AToB = (PlanetB.Position - PlanetA.Position).GetSafeNormal() * Force;
            PlanetA.Velocity += AToB / PlanetA.Mass * UnrealTimeUnit * DeltaTime;
            PlanetB.Velocity -= AToB / PlanetB.Mass * UnrealTimeUnit * DeltaTime;
        }
    }
}


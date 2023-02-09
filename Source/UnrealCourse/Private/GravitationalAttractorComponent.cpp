#include "UnrealCourse/Public/GravitationalAttractorComponent.h"

#include "AttractedByGravity.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


constexpr float GravitationalConstant = 1500;


UGravitationalAttractorComponent::UGravitationalAttractorComponent() {
    PrimaryComponentTick.bCanEverTick = true;

    SphereOfInfluence = CreateDefaultSubobject<USphereComponent>("SphereOfInfluence");
}


void UGravitationalAttractorComponent::BeginPlay() {
    Super::BeginPlay();

    SphereOfInfluence->SetGenerateOverlapEvents(true);
    SphereOfInfluence->OnComponentBeginOverlap.AddDynamic(this, &UGravitationalAttractorComponent::OnActorEnterSOI);
    SphereOfInfluence->OnComponentEndOverlap.AddDynamic(this, &UGravitationalAttractorComponent::OnActorLeaveSOI);
}


void UGravitationalAttractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    TArray<AActor*> ActorsInSOI;
    UGameplayStatics::GetAllActorsWithInterface(this, UAttractedByGravity::StaticClass(), ActorsInSOI);
    
    for (AActor* Object : ActorsInSOI) {
        if (Object == GetOwner()) continue;
        
        FVector Location = GetOwner()->GetActorLocation();
        FVector OtherLocation = Object->GetActorLocation();
        const FVector Direction = (Location - OtherLocation).GetSafeNormal();
        
        const float DistanceSquared = FVector::DistSquared(Location, OtherLocation);
        const float OtherMass = IAttractedByGravity::Execute_GetMass(Object);
        const float Force = Mass * OtherMass / DistanceSquared * 700;
        
        IAttractedByGravity::Execute_ApplyForce(Object, Direction, Force);
    }
}

void UGravitationalAttractorComponent::OnActorEnterSOI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    if (OtherActor->Implements<UAttractedByGravity>()) {
        ObjectsInSOI.Add(OtherActor);
    }
}

void UGravitationalAttractorComponent::OnActorLeaveSOI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    ObjectsInSOI.Remove(OtherActor);
}


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravitationalAttractorComponent.generated.h"


class USphereComponent;


UCLASS(BlueprintType, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UNREALCOURSE_API UGravitationalAttractorComponent : public USceneComponent {
    GENERATED_BODY()

    UPROPERTY()
    TSet<AActor*> ObjectsInSOI;

public:
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    USphereComponent* SphereOfInfluence;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float Mass = 1;
    
    // Sets default values for this component's properties
    UGravitationalAttractorComponent();

    // Called when the game starts
    virtual void BeginPlay() override;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

protected:
    UFUNCTION()
    virtual void OnActorEnterSOI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnActorLeaveSOI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

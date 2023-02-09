#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttractedByGravity.generated.h"


// This class must not be modified.
UINTERFACE(BlueprintType)
class UAttractedByGravity : public UInterface {
    GENERATED_BODY()
};


class UNREALCOURSE_API IAttractedByGravity {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    float GetMass();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void ApplyForce(FVector Direction, double Force);
};

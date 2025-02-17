// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NPC/Help.h"
#include "ConnectWalletConnect.generated.h"

/**
 *
 */
UCLASS()
class METAVERSE_API AConnectWalletConnect : public AHelp {
    GENERATED_BODY()

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnConnectWalletConnectBeginOverlap(
        UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult &SweepResult);
};

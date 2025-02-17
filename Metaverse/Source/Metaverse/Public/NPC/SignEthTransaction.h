// Copyright 2022, Cronos Labs. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "NPC/Help.h"
#include "SignEthTransaction.generated.h"

struct FWalletSignTXEip155Result;

/**
 *
 */
UCLASS()
class METAVERSE_API ASignEthTransaction : public AHelp {
    GENERATED_BODY()

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnSignEthTransactionBeginOverlap(
        UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult &SweepResult);

  private:
    UFUNCTION()
    void OnWalletconnectSignEip155TransactionFinished(
        FWalletSignTXEip155Result SigningResult);
};

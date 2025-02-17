// Copyright 2022, Cronos Labs. All Rights Reserved

#include "NPC/SignEthTransaction.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"
#include "PlayCppSdkActor.h"
#include "Utlis.h"

// Called when the game starts or when spawned
void ASignEthTransaction::BeginPlay() {
    Super::BeginPlay();
    GetWalletConnectTriggerComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &ASignEthTransaction::OnSignEthTransactionBeginOverlap);
}

void ASignEthTransaction::OnSignEthTransactionBeginOverlap(
    UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult &SweepResult) {
    AMetaverseCharacter *MetaverseCharacter =
        Cast<AMetaverseCharacter>(OtherActor);
    if (MetaverseCharacter->GetAccount().IsEmpty()) {
        MetaverseCharacter->SetAccount(
            FText::FromString(FString::Printf(TEXT("Plase scan QR Code"))));
    } else {
        MetaverseCharacter->SetAccount(MetaverseCharacter->GetAccount());
    }

    UWalletConnectTriggerComponent *WalletConnectTriggerComponent =
        GetWalletConnectTriggerComponent();

    WalletConnectTriggerComponent->OnWalletconnectSignEip155TransactionDelegate
        .BindDynamic(
            this,
            &ASignEthTransaction::OnWalletconnectSignEip155TransactionFinished);

    FWalletConnectTxEip155 tx;
    tx.to = FString("0xA914161b1b8d9dbC9c5310Fc7EBee5A5B18044b7");
    tx.value = FString("1000000000000000000");
    WalletConnectTriggerComponent->SignEip155Transaction(tx);

    WalletConnectTriggerComponent->OnShowQR.BindDynamic(this, &Super::ShowQR);
}

void ASignEthTransaction::OnWalletconnectSignEip155TransactionFinished(
    FWalletSignTXEip155Result SigningResult) {
    UE_LOG(LogTemp, Log, TEXT("Signing Signature: %s, Result: %s"),
           *UUtlis::ToHex(SigningResult.signature), *SigningResult.result);
}

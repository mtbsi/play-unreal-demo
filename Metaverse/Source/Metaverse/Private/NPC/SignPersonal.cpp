// Copyright 2022, Cronos Labs. All Rights Reserved

#include "NPC/SignPersonal.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WalletConnectTriggerComponent.h"
#include "../../MetaverseCharacter.h"
#include "PlayCppSdkActor.h"
#include "Utlis.h"

// Called when the game starts or when spawned
void ASignPersonal::BeginPlay() {
    Super::BeginPlay();
    GetWalletConnectTriggerComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &ASignPersonal::OnSignPersonalBeginOverlap);
}

void ASignPersonal::OnSignPersonalBeginOverlap(
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

    WalletConnectTriggerComponent->OnWalletconnectSignPersonalDelegate
        .BindDynamic(this, &ASignPersonal::OnWalletconnectSignPersonalFinished);

    WalletConnectTriggerComponent->SignPersonal(FString("HELLO WORLD"));

    WalletConnectTriggerComponent->OnShowQR.BindDynamic(this, &Super::ShowQR);
}

void ASignPersonal::OnWalletconnectSignPersonalFinished(
    FWalletSignTXEip155Result SigningResult) {
    UE_LOG(LogTemp, Log, TEXT("Signing Signature: %s, Result: %s"),
           *UUtlis::ToHex(SigningResult.signature), *SigningResult.result);
}

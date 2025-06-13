// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LootAtPlayer.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

/** -------------------------------------------------------------------------- */

#include "BossDesignCharacter.h"
#include "BossAIController.h"
#include "BTTask_ChasePlayer.h"

/** -------------------------------------------------------------------------- */

UBTService_LootAtPlayer::UBTService_LootAtPlayer()
{
    NodeName = "Loot At Player";
}

void UBTService_LootAtPlayer::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	//Get Boss AIController
    auto* const bossCon = Cast<ABossAIController>(OwnerComp.GetAIOwner());
    if(!bossCon) return;

    //Get Boss Pawn
    APawn* boss = bossCon->GetPawn();
    if(!boss) return;

    //Get Boss BlackboardComponent
    auto* bossBlackBoard = OwnerComp.GetBlackboardComponent();
    if(!bossBlackBoard) return;

    bool bCanSeePlayer = bossBlackBoard->GetValueAsBool("canSeePlayer");
    if(bCanSeePlayer) return;

    //Get Player Actor
    AActor* player = UGameplayStatics::GetPlayerCharacter(boss->GetWorld(), 0);
    if(!player) return;

    FVector playerLocation = player->GetActorLocation();
    FVector bossLocation = boss->GetActorLocation();
    FRotator lookAtRotation = (playerLocation - bossLocation).Rotation();
    
    FRotator newRotation(0.f, lookAtRotation.Yaw, 0.f);
    boss->SetActorRotation(newRotation);
}

#include "Enemy_Boss.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


AEnemy_Boss::AEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy_Boss::WeaknessDestroy()
{
	AAIController* AICon = Cast<AAIController>(GetController());
	if(AICon)
	{
		AICon->GetBlackboardComponent()->SetValueAsBool("bIsStunned", true);

		GetWorldTimerManager().SetTimer(stunnedTimer, this, &AEnemy_Boss::EndStun, 7.f, false);
	}
}

void AEnemy_Boss::EndStun()
{
	AAIController* AICon = Cast<AAIController>(GetController());
	if(AICon)
	{
		AICon->GetBlackboardComponent()->SetValueAsBool("bIsStunned", false);
	}
}

void AEnemy_Boss::BossDead(bool isDeath)
{
	bIsDeath = isDeath;
	AAIController* AICon = Cast<AAIController>(GetController());
	if(AICon)
	{
		AICon->GetBlackboardComponent()->SetValueAsBool("bIsDeath", bIsDeath);
	}
	
}

UBehaviorTree *AEnemy_Boss::GetBehaviorTree() const
{
	return bossTree;
}

#include "Enemy_Boss.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemy_Boss::AEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

}

UBehaviorTree *AEnemy_Boss::GetBehaviorTree() const
{
	return bossTree;
}
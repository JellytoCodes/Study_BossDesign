
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LootAtPlayer.generated.h"

/** -------------------------------------------------------------------------- */

UCLASS()
class BOSSDESIGN_API UBTService_LootAtPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public :
	UBTService_LootAtPlayer();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};

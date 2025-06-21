
#include "Boss_HealthWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

/** -------------------------------------------------------------------------- */

#include "Enemy_Boss.h"

/** -------------------------------------------------------------------------- */

void UBoss_HealthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!bossInstance) return;

	if(bossName) UpdatedBossName();
	if(bossHealth) UpdatedBossHealth();
}

void UBoss_HealthWidget::UpdatedBossName()
{
	bossName->SetText(FText::FromString("Iggy&Scorch"));
}

void UBoss_HealthWidget::UpdatedBossHealth()
{
	bossHealth->SetPercent(bossInstance->GetHealthPercent());
	UE_LOG(LogTemp, Warning, TEXT("Boss Health Percent : %.2f"), bossInstance->GetHealthPercent());
}

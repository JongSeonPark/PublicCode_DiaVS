#include "Character/DiaEnemyCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "DiaGameplayTags.h"
#include "DiaMathLibrary.h"
#include "Actor/MagnetItem/DiaMagnetItem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Game/DiaGameMode.h"
#include "Game/DiaGameSpawner.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Team/DiaTeamSubsystem.h"

ADiaEnemyCharacter::ADiaEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UDiaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UDiaAttributeSet>("AttributeSet");
}

void ADiaEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystem();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ADiaEnemyCharacter::OnEnemyHit);

	DamageTimer = TimePerDamage;
}

void ADiaEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (HasAuthority())
	{
		if (AAIController* AIControllerTemp = Cast<AAIController>(NewController))
		{
			AIController = AIControllerTemp;
			if (BehaviorTree)
				AIController->RunBehaviorTree(BehaviorTree);
		}
	}
}

void ADiaEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	DamageTimer += DeltaSeconds;

	DistUpdate(DeltaSeconds);
}

void ADiaEnemyCharacter::InitAbilitySystem()
{
	Super::InitAbilitySystem();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	// Primary에 의한 MoveSpeed 변경
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UDiaAttributeSet::GetPrimaryMoveSpeedAttribute()).AddLambda(
		[&](const FOnAttributeChangeData& AttributeChangeData)
		{
			GetCharacterMovement()->bForceMaxAccel = true;
			GetCharacterMovement()->MinAnalogWalkSpeed = AttributeChangeData.NewValue;
			GetCharacterMovement()->MaxWalkSpeed = AttributeChangeData.NewValue;
		});
	ApplyInitialAttributes();
}

void ADiaEnemyCharacter::ApplyInitialAttributes() const
{
	ApplyGameplayEffectToSelf(PrimaryAttributes);
	Super::ApplyInitialAttributes();
}

void ADiaEnemyCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	if (HasAuthority())
	{
		if (AIController)
		{
			AIController->GetBrainComponent()->StopLogic(TEXT(""));
		}
		DropItem();
		SetLifeSpan(2.f);
	}
}

void ADiaEnemyCharacter::SetTargetActor(AActor* TargetActor)
{
	if (AIController)
	{
		AIController->GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), TargetActor);
	}
}

void ADiaEnemyCharacter::OnEnemyHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Hit %s, Comp: %s"), *OtherActor->GetName(), *OtherComp->GetName()));

	if (DamageTimer < TimePerDamage)
		return;

	const UDiaTeamSubsystem* TeamSubsystem = GetWorld()->GetSubsystem<UDiaTeamSubsystem>();

	if (TeamSubsystem && TeamSubsystem->CanCauseDamage(this, OtherActor, false))
	{
		if (UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			const float Damage = AbilitySystemComponent->GetNumericAttribute(UDiaAttributeSet::GetPrimaryDamageAttribute());
			if (Damage > 0)
			{
				const FGameplayEffectContextHandle EffectContextSpec = AbilitySystemComponent->MakeEffectContext();
				const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, Level, EffectContextSpec);
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Damage_Melee, Damage);

				AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, TargetAbilitySystem);
				DamageTimer = 0;
			}
		}
	}
}

void ADiaEnemyCharacter::OnImcomingDamage(const FOnAttributeChangeData& Data)
{
	Super::OnImcomingDamage(Data);
	const float Offset = 50.f;
	const float CurrentSpeed = FMath::Max(0, GetVelocity().Length() - Offset);
	GetCharacterMovement()->AddImpulse(-GetActorForwardVector() * (CurrentSpeed + Offset) * 1000, false);
}

void ADiaEnemyCharacter::DistUpdate(float DeltaSeconds)
{
	if (!HasAuthority()) return;
	if (!AIController) return;
	DestroyDistTimer += DeltaSeconds;
	if (DestroyDistInterval > DestroyDistTimer) return;
	DestroyDistTimer = 0;

	AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(FName("TargetActor")));
	if (!TargetActor) return;
	if (DestroyDist * DestroyDist < FVector::DistSquared(GetActorLocation(), TargetActor->GetActorLocation()))
	{
		if (bIsBoss)
		{
			if (ADiaGameMode* DiaGameMode = GetWorld()->GetAuthGameMode<ADiaGameMode>())
			{
				if (UDiaGameSpawner* DiaGameSpawner = DiaGameMode->GetDiaGameSpawner())
				{
					FNavLocation ResultLocation;
					if (DiaGameSpawner->GetRandomReachablePointInCircle(TargetActor->GetActorLocation(), 1000, ResultLocation))
					{
						SetActorLocation(ResultLocation);
					}
				}
			}
		}
		else
		{
			Destroy();
		}
	}
}

void ADiaEnemyCharacter::DropItem()
{
	// 하나일 때 가중치 연산 시행하지 않음.
	if (DropItemInfos.Num() == 1 && DropCount > 0)
	{
		SpawnDropItem(DropItemInfos[0]);
	}
	else
	{
		TArray<TPair<FDropItemInfo, float>> DropItemInfosSorted;
		for (FDropItemInfo DropItemInfo : DropItemInfos)
		{
			DropItemInfosSorted.Add(MakeTuple(DropItemInfo, DropItemInfo.Rarity));
		}

		TArray<TTuple<FDropItemInfo, float>> DropItems = UDiaMathLibrary::WeightedRandomSelection(DropItemInfosSorted, true, DropCount);
		for (TTuple<FDropItemInfo, float> DropItemPair : DropItems)
		{
			SpawnDropItem(DropItemPair.Key);
		}
	}
}

void ADiaEnemyCharacter::SpawnDropItem(FDropItemInfo DropItem)
{
	FTransform SpawnTransform(GetActorLocation());
	ADiaMagnetItem* SpawnItem = GetWorld()->SpawnActorDeferred<ADiaMagnetItem>(
		DropItem.DropItem,
		SpawnTransform,
		this,
		this
	);
	SpawnItem->SetItemValue(DropItem.Value);
	SpawnItem->FinishSpawning(SpawnTransform);
}

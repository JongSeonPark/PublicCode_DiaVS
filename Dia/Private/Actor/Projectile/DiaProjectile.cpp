#include "Actor/Projectile/DiaProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Team/DiaTeamSubsystem.h"

// Sets default values
ADiaProjectile::ADiaProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
}

void ADiaProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADiaProjectile::OnSphereOverlap);
}

void ADiaProjectile::Destroyed()
{
	Super::Destroyed();
}

void ADiaProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;
	if (!EffectSpecHandle.IsValid()) return;

	const UDiaTeamSubsystem* TeamSubsystem = GetWorld()->GetSubsystem<UDiaTeamSubsystem>();
	if (!TeamSubsystem) return;
	if (!TeamSubsystem->CanCauseDamage(GetInstigator(), OtherActor, false)) return;

	if (!PierceEnemys.Contains(OtherActor))
	{
		PierceEnemys.Add(OtherActor);

		if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			AbilitySystem->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}

		if (Pierce != 0 && PierceEnemys.Num() >= Pierce)
		{
			Destroy();
		}
	}
}

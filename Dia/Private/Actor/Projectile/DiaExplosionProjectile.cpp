#include "Actor/Projectile/DiaExplosionProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/DiaCharacterBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Team/DiaTeamSubsystem.h"


ADiaExplosionProjectile::ADiaExplosionProjectile()
{
	// 일단 PeachoneProjectile을 기준으로 제작
	ProjectileMovement->ProjectileGravityScale = 1.f;
	ProjectileMovement->Velocity = FVector(1.f, 1.f, 0);

	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	SphereComponent->SetNotifyRigidBodyCollision(true);

	ExplosionAreaSphereComponent = CreateDefaultSubobject<USphereComponent>("ExplosionArea");
	ExplosionAreaSphereComponent->SetupAttachment(SphereComponent);

	ExplosionAreaSphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
	ExplosionAreaSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ExplosionAreaSphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void ADiaExplosionProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentHit.AddDynamic(this, &ADiaExplosionProjectile::OnSphereHit);
}

void ADiaExplosionProjectile::SetArea(const float InArea)
{
	// Scale이 커지면서 ExplosionAreaSphereComponent 범위가 넓어짐. 
	SetActorScale3D(FVector::One() * InArea);
}

void ADiaExplosionProjectile::OnSphereHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HasAuthority()) return;
	if (!EffectSpecHandle.IsValid()) return;
	const UDiaTeamSubsystem* TeamSubsystem = GetWorld()->GetSubsystem<UDiaTeamSubsystem>();
	if (!TeamSubsystem) return;

	TArray<AActor*> OverlappingActors;
	ExplosionAreaSphereComponent->GetOverlappingActors(OverlappingActors, ADiaCharacterBase::StaticClass());
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OverlappingActor))
		{
			if (TeamSubsystem->CanCauseDamage(GetInstigator(), OverlappingActor, false))
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}

	MulticastSpawnParticleEffect(GetActorLocation());
	Destroy();
}

void ADiaExplosionProjectile::MulticastSpawnParticleEffect_Implementation(FVector Location)
{
	SpawnParticleEffectClient(Location);
}

void ADiaExplosionProjectile::SpawnParticleEffectClient_Implementation(FVector Location)
{
	if (FXExplosion)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			FXExplosion,
			Location,
			FRotator::ZeroRotator,
			GetActorScale(),
			true,
			true,
			ENCPoolMethod::None,
			true);
	}
}
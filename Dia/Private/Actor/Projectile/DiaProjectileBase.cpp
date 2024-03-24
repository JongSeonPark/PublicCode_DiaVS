#include "Actor/Projectile/DiaProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Dia/Dia.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADiaProjectileBase::ADiaProjectileBase()
{
	bReplicates = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(SphereComponent);

	SphereComponent->SetCollisionObjectType(ECC_Projectile);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void ADiaProjectileBase::SetSpeed(const float InSpeed)
{
	ProjectileMovement->InitialSpeed *= InSpeed;
	ProjectileMovement->MaxSpeed *= InSpeed;
}

void ADiaProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	
	if (InitSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), InitSound, GetActorLocation());
}

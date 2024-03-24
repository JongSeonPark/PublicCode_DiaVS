#include "Actor/MagnetItem/DiaMagnetItem.h"
#include "Components/SphereComponent.h"
#include "Dia/Dia.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/KismetSystemLibrary.h"

ADiaMagnetItem::ADiaMagnetItem()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionObjectType(ECC_Item);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Magnet, ECR_Overlap);
	SetRootComponent(SphereComponent);
}

void ADiaMagnetItem::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADiaMagnetItem::OnBeginOverlap);
	
	if (LifeSpan > 0) SetLifeSpan(LifeSpan);
}

void ADiaMagnetItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FollowingTarget || FollowSpeedCurve.IsNull())
	{
		return;
	}

	if (FollowingTarget->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead(FollowingTarget))
	{
		FollowingTarget = nullptr;
		FollowingTime = 0.f;
		return;
	}

	float FollowingSpeed;
	if (FollowSpeedCurve.Eval(FollowingTime, &FollowingSpeed, FollowSpeedCurve.RowName.ToString()))
	{
		const FVector CurrentLocation = GetActorLocation();
		const FVector Direction = (FollowingTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		SetActorLocation(CurrentLocation + Direction * FollowingSpeed * FollowSpeed * DeltaTime);
		FollowingTime += DeltaTime;
	}
}

void ADiaMagnetItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!FollowingTarget && OtherComp->GetCollisionObjectType() == ECC_Magnet)
	{
		FollowingTarget = OtherActor;
	}

	// TODO: Player Collision Type 정해질 시 수정.
	if (OtherComp->GetCollisionObjectType() != ECC_Magnet && OtherActor->Implements<UPlayerInterface>())
	{
		if (HasAuthority())
		{
			AcceptedActorUpdate(OtherActor);
			Destroy();
		}
	}
}

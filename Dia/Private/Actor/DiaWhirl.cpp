#include "Actor/DiaWhirl.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Team/DiaTeamSubsystem.h"

ADiaWhirl::ADiaWhirl()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
}

void ADiaWhirl::BeginPlay()
{
	Super::BeginPlay();

	TArray<FTransform> Transforms = UDiaAbilitySystemLibrary::GetCircleAroundTransforms(ObjectCount, Range);
	for (int32 i = 0; i < ObjectCount; i++)
	{
		USphereComponent* SphereComponent = NewObject<USphereComponent>(this, USphereComponent::StaticClass());
		SphereComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		SphereComponent->SetRelativeTransform(Transforms[i]);
		SphereComponent->RegisterComponent();
		if (LookComponentClass)
		{
			UPrimitiveComponent* LookComp = NewObject<UPrimitiveComponent>(this, LookComponentClass);
			LookComp->AttachToComponent(SphereComponent, FAttachmentTransformRules::KeepRelativeTransform);
			LookComp->RegisterComponent();
		}

		if (LookActorClass)
		{
			AActor* LookActor = GetWorld()->SpawnActor(LookActorClass);
			LookActor->AttachToComponent(SphereComponent, FAttachmentTransformRules::KeepRelativeTransform);
			LookActors.Add(LookActor);
		}

		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADiaWhirl::OnSphereOverlap);
		CollisionObjects.Add(SphereComponent);
	}
}

void ADiaWhirl::Destroyed()
{
	Super::Destroyed();
	for (AActor* LookActor : LookActors)
	{
		LookActor->Destroy();
	}
	LookActors.Empty();
}

void ADiaWhirl::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetInstigator())
	{
		SetActorLocation(GetInstigator()->GetActorLocation());
	}
}

void ADiaWhirl::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Hello"));
	if (HasAuthority())
	{
		UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		if (AbilitySystem && EffectSpecHandle.IsValid())
		{
			const UDiaTeamSubsystem* TeamSubsystem = GetWorld()->GetSubsystem<UDiaTeamSubsystem>();
			if (TeamSubsystem && TeamSubsystem->CanCauseDamage(GetInstigator(), OtherActor, false))
			{
				AbilitySystem->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}

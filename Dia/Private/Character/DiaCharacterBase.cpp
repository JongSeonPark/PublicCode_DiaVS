#include "Character/DiaCharacterBase.h"

#include "DiaGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/DiaUserWidget.h"
#include "UI/WidgetController/CharacterWidgetController.h"

ADiaCharacterBase::ADiaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CharacterWidgetController = CreateDefaultSubobject<UCharacterWidgetController>("CharacterWidgetController");

	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>("HpBar");
	HpBarWidget->SetupAttachment(RootComponent);
	HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HpBarWidget->SetDrawAtDesiredSize(true);
	HpBarWidget->SetVisibility(false);
}

void ADiaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADiaCharacterBase::Destroyed()
{
	Super::Destroyed();

	// 죽지 않고 삭제되는 경우 대비
	CancelAbilitiesWhenCharacterDie();
}

void ADiaCharacterBase::InitAbilitySystem()
{
	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(UDiaAttributeSet::GetIncomingDamageAttribute())
		.AddUObject(this, &ADiaCharacterBase::OnImcomingDamage);
	
	// AbilitySystem이 있어서 여기서 호출
	// 생성 방식에 따라 Null이여서 재호출..
	// exp) PCG SpawnActor로 생성시 nullptr
	if (!CharacterWidgetController)
		CharacterWidgetController = NewObject<UCharacterWidgetController>(this);

	UpdateHpBarWidgetController();
}

void ADiaCharacterBase::ApplyInitialAttributes() const
{
	ApplyGameplayEffectToSelf(SecondaryAttributes);
	ApplyGameplayEffectToSelf(VitalAttributes);
}

void ADiaCharacterBase::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(AbilitySystemComponent));
	if (!IsValid(GameplayEffectClass)) return;

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ADiaCharacterBase::DoRagdoll() const
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// GetMesh()->AddImpulse((-GetActorForwardVector() + FVector(0, 0, 1)) * 1000000);
}

void ADiaCharacterBase::Die_Implementation()
{
	Die_Multicast();
	bDead = true;
	CancelAbilitiesWhenCharacterDie();
}

void ADiaCharacterBase::Die_Multicast_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// DoRagdoll();
	bDead = true;
	HpBarWidget->SetVisibility(false);
}

void ADiaCharacterBase::CancelAbilitiesWhenCharacterDie()
{
	if (!AbilitySystemComponent) return;
	const FGameplayTagContainer TagsToCancel(DiaGameplayTags::Ability_Attack);
	AbilitySystemComponent->CancelAbilities(&TagsToCancel, nullptr, nullptr);
}

void ADiaCharacterBase::OnImcomingDamage(const FOnAttributeChangeData& Data)
{
	// if (!IsLocallyControlled())
	// HpBarWidget->SetVisibility(true);
}

void ADiaCharacterBase::PushOtherCharacter(ACharacter* OtherCharacter)
{
	FVector PushDirection = OtherCharacter->GetActorLocation() - GetActorLocation();
	// XY Plane에서만 허용하는걸로
	PushDirection.Z = 0.0f;

	if (!PushDirection.IsNearlyZero())
	{
		// TODO: PushForce 정하기
		const float PushForce = 1000.f;
		PushDirection.Normalize();
		OtherCharacter->LaunchCharacter(PushDirection * PushForce, true, false);
	}
}

void ADiaCharacterBase::OnHitOtherCharacter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA<ACharacter>())
		PushOtherCharacter(Cast<ACharacter>(OtherActor));
}

void ADiaCharacterBase::UpdateHpBarWidgetController()
{
	if (HpBarWidget->GetWidget() == nullptr)
	{
		HpBarWidget->InitWidget();
	}
	
	UDiaUserWidget* DiaWidget = Cast<UDiaUserWidget>(HpBarWidget->GetWidget());
	if (DiaWidget && AbilitySystemComponent && AttributeSet)
	{
		const FDiaWidgetControllerParams WidgetControllerParams(nullptr, nullptr, AbilitySystemComponent, AttributeSet);
		CharacterWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		CharacterWidgetController->BindCallbacks();

		DiaWidget->SetWidgetController(CharacterWidgetController);
		CharacterWidgetController->BroadcastInitValues();
	}
}

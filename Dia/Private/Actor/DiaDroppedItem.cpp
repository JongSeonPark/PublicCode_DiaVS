
#include "Actor/DiaDroppedItem.h"

#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "NiagaraComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Widget/PickableViewWidget.h"

// Sets default values
ADiaDroppedItem::ADiaDroppedItem()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ItemHighlightNiagara = CreateDefaultSubobject<UNiagaraComponent>("HighlightNiagara");
	WorldViewWidget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WorldViewWidget->SetWidgetSpace(EWidgetSpace::Screen);
	WorldViewWidget->SetDrawSize(FVector2D::Zero());
	
	ItemHighlightNiagara->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(RootComponent);
	WorldViewWidget->SetupAttachment(RootComponent);
	
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	Mesh->SetRelativeRotation(FRotator(-1000, 0.f, 0.f));

	bReplicates = true;
	// SetReplicates(true);
}

void ADiaDroppedItem::Pick_Implementation()
{
	// TODO: 인벤토리 완료시 인벤토리로 가야함.
	Destroy();
}

void ADiaDroppedItem::View_Implementation()
{
	IDiaPickable::View_Implementation();
}

// Called when the game starts or when spawned
void ADiaDroppedItem::BeginPlay()
{
	Super::BeginPlay();
	if (UPickableViewWidget* PickableViewWidget = Cast<UPickableViewWidget>(WorldViewWidget->GetWidget()))
	{
		PickableViewWidget->PickableItem = this;
	}

	FUObjectItem* ObjectItem = GUObjectArray.IndexToObject(GetUniqueID());
	ObjectItem->Flags;

	MakeWeakObjectPtr(this);
	
	UKismetSystemLibrary::PrintString(GetWorld(),
		FString::Printf(TEXT("Name: %s, Flags: %d, ClusterRootIndex: %d, SerialNumber: %d"),
			*ObjectItem->Object->GetFName().ToString(),
			ObjectItem->Flags,
			ObjectItem->ClusterRootIndex,
			ObjectItem->SerialNumber
			));

	FUObjectItem* ClusterRootObjectItem = GUObjectArray.IndexToObject(ObjectItem->ClusterRootIndex);
	
	UKismetSystemLibrary::PrintString(GetWorld(),
		FString::Printf(TEXT("Cluster Root Name: %s, Flags: %d, ClusterRootIndex: %d, SerialNumber: %d"),
			*ClusterRootObjectItem->Object->GetFName().ToString(),
			ClusterRootObjectItem->Flags,
			ClusterRootObjectItem->ClusterRootIndex,
			ClusterRootObjectItem->SerialNumber
			));
}

void ADiaDroppedItem::OnFinish_SequencePlay()
{
	ItemHighlightNiagara->Activate();
}

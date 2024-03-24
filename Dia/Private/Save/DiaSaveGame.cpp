


#include "Save/DiaSaveGame.h"

#include "Dia/Dia.h"

UDiaSaveGame::UDiaSaveGame()
{
	UE_LOG(LogDia, Display, TEXT("UDiaSaveGame"));
}

void UDiaSaveGame::FinishDestroy()
{
	Super::FinishDestroy();
	UE_LOG(LogDia, Display, TEXT("UDiaSaveGame::FinishDestroy. SlotName: %s, UserIndex: %d"), *SlotName, UserIndex);
}

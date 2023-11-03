// Fill out your copyright notice in the Description page of Project Settings.


#include "GamesdevTut/MenuSystem/MenuWidget.h"

void UMenuWidget::SetMenuInterface(class IMenuInterface* _MenuInterface)
{
	MenuInterface = _MenuInterface;
}

void UMenuWidget::Setup()
{
	AddToViewport();
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(InputMode);
	}
}

void UMenuWidget::NativeDestruct()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
			RemoveFromViewport();
		}
	}
	Super::NativeDestruct();
}
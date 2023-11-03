// Fill out your copyright notice in the Description page of Project Settings.


#include "GamesdevTut/MenuSystem/InGameMenu.h"
#include "GamesdevTut/MenuSystem/MenuInterface.h"
#include "Components/Button.h"



void UInGameMenu::CloseMenu()
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
}

void UInGameMenu::Quit()
{
	RemoveFromViewport();
	MenuInterface->LoadMainMenu();
}

bool UInGameMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;
	if (!QuitButton) return false;
	if (!CancelButton) return false;

	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::Quit);
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CloseMenu);
	return true;
}
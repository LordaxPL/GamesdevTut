// Fill out your copyright notice in the Description page of Project Settings.


#include "GamesdevTut/MenuSystem/MainMenu.h"
#include "GamesdevTut/MenuSystem/MenuInterface.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (JoinButton == nullptr) return false;
	if (HostButton == nullptr) return false;
	if (BackButton == nullptr) return false;
	if (QuitButton == nullptr) return false;

	JoinButton->OnPressed.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	JoinButton2->OnPressed.AddDynamic(this, &UMainMenu::Join);
	HostButton->OnPressed.AddDynamic(this, &UMainMenu::OnHostPressed);
	BackButton->OnPressed.AddDynamic(this, &UMainMenu::OpenMainMenu);
	QuitButton->OnPressed.AddDynamic(this, &UMainMenu::OnQuitPressed);

	return true;
}

void UMainMenu::OnHostPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Hosting in progress..."));
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}



void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher)
	{
		if (JoinMenu)
		{
			MenuSwitcher->SetActiveWidget(JoinMenu);
		}
	}
}

void UMainMenu::OpenMainMenu()
{
	if (MenuSwitcher)
	{
		if (MainMenu)
		{
			MenuSwitcher->SetActiveWidget(MainMenu);
		}
	}
}

void UMainMenu::Join()
{
	if (!JoinTB) return;
	UWorld* World = GetWorld();
	if (!World) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController)
	{
		FString Address = JoinTB->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenu::OnQuitPressed()
{
	MenuInterface->QuitGame();
}
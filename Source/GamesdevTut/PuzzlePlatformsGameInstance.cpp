// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MenuWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
	static ConstructorHelpers::FClassFinder<UUserWidget> _MenuClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (_MenuClass.Class != nullptr)
	{
		MenuClass = _MenuClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> _InGameMenuClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (_InGameMenuClass.Class != nullptr)
	{
		InGameMenuClass = _InGameMenuClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance INIT"));
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass)
	{
		UMenuWidget* MenuWidget = CreateWidget<UMenuWidget>(this, MenuClass);
		if (MenuWidget != nullptr)
		{
			MenuWidget->Setup();
			MenuWidget->SetMenuInterface(this);
		}
	}
}

void UPuzzlePlatformsGameInstance::Host()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, __FUNCTION__);
	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/TestLevel?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));
	GetFirstLocalPlayerController()->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	UMenuWidget* InGameMenuWidget = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	InGameMenuWidget->Setup();
	InGameMenuWidget->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	GetFirstLocalPlayerController()->ClientTravel("Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::QuitGame()
{
	GetFirstLocalPlayerController()->ConsoleCommand(FString("quit"));
}
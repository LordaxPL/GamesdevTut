// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMESDEVTUT_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMenuInterface(class IMenuInterface* _MenuInterface);
	void Setup();

protected:
	class IMenuInterface* MenuInterface;
	virtual void NativeDestruct() override;

};

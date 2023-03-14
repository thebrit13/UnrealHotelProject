// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealHotelProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALHOTELPROJECT_API AUnrealHotelProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	UUserWidget* ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Widgets")
	TSubclassOf<UUserWidget> MainHUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Widgets")
	TSubclassOf<UUserWidget> RoomUI;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Widgets")
	TSubclassOf<UUserWidget> GuestUI;;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	UPROPERTY()
	UUserWidget* HUDWidget;
	
};

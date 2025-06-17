// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class METAHUMANPROJECT_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	// 인터페이스를 위한 UI
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UChatWidget> ChatUIFactory;

	UPROPERTY()
	class UChatWidget* ChatUI;
};

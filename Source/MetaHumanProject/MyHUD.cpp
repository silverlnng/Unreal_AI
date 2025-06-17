// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Blueprint/UserWidget.h"
#include "Http/ChatWidget.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	ChatUI = Cast<UChatWidget>(CreateWidget(GetWorld(), ChatUIFactory));
	if (ChatUI)
	{
		ChatUI->AddToViewport();
	}

	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->SetShowMouseCursor(true);
	pc->SetInputMode(FInputModeUIOnly());
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class METAHUMANPROJECT_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly)
	class AHttpChatController* HttpActor;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextResultLog;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonSend;

	UPROPERTY(meta=(BindWidget))
	class UEditableText* UserText_;
	
	UFUNCTION()
	void OnSendButtonClicked();

	UFUNCTION()
	void OnServerResponse(const FString& ResponseText);
};

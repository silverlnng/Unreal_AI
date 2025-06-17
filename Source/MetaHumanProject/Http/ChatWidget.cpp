// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWidget.h"

#include "HttpChatController.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ButtonSend->OnClicked.AddDynamic(this, &UChatWidget::OnSendButtonClicked);
}

void UChatWidget::OnSendButtonClicked()
{
	FString UserText = UserText_->GetText().ToString();
	if (HttpActor)
	{
		HttpActor->SendChat(UserText);
	}
}

void UChatWidget::OnServerResponse(const FString& ResponseText)
{
	TextResultLog->SetText( FText::FromString(ResponseText));
	// 응답 텍스트를 채팅창에 표시하거나 메타휴먼에게 전달
	UE_LOG(LogTemp, Warning, TEXT("💬 서버로부터 응답: %s"), *ResponseText);
}

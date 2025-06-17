// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpChatController.h"

#include "ChatWidget.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "MetaHumanProject/MyHUD.h"

// Sets default values
AHttpChatController::AHttpChatController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHttpChatController::BeginPlay()
{
	Super::BeginPlay();
	// hud 를 찾아서
	auto* pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		hud=pc->GetHUD<AMyHUD>();
	}
	
	FTimerHandle delayTimer;
	GetWorldTimerManager().SetTimer(delayTimer,[this]()
	{
		if (hud)
		{
			ChatWidget=hud->ChatUI;
		}
		if (ChatWidget)
		{
			ChatWidget->HttpActor=this;
			UE_LOG(LogTemp, Warning, TEXT("✅ ChatWidget->HttpActor=this"));
		}
	},1.0f,false);
	
}

// Called every frame
void AHttpChatController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHttpChatController::SendChat(const FString& UserInput)
{
	FString Url = TEXT("http://127.0.0.1:8000/chat");

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("user_input", UserInput);

	FString Body;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Body);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(Body);

	//Request->OnProcessRequestComplete().BindUObject(this,&AHttpChatController::HandleResponse);

	Request->OnProcessRequestComplete().BindUObject(this,&AHttpChatController::HandleResponse);
	// 혹시 바인딩 실패했는지 확인

	// 테스트 로그
	if (!Request->OnProcessRequestComplete().IsBound())
	{
		UE_LOG(LogTemp, Error, TEXT("❌ BindUObject 바인딩 실패"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("✅ BindUObject 바인딩 성공"));
	}

	Request->ProcessRequest();
}

void AHttpChatController::HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("📥 HandleResponse 호출됨"));
	
	if (bWasSuccessful && Response->GetResponseCode() == 200)
	{
		FString Content = Response->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("📥 서버 응답: %s"), *Content);

		// JSON 파싱
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Content);
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString ResponseText = JsonObject->GetStringField(TEXT("response"));
			if (ResponseText.IsEmpty()){return;}
			ChatWidget->OnServerResponse(ResponseText);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ 서버 요청 실패"));
	}
}


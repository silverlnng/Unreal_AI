// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpChatController.generated.h"

UCLASS()
class METAHUMANPROJECT_API AHttpChatController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHttpChatController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class AMyHUD* hud;
	UPROPERTY(VisibleAnywhere)
	class UChatWidget* ChatWidget;
	
	UFUNCTION(BlueprintCallable)
	void SendChat(const FString& UserInput);	
public:	

	void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
};

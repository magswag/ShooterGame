// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UsableItem.generated.h"

UCLASS()
class SHOOTER_API AUsableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUsableItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void Use();

	virtual void Use_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void UseReleased();

	virtual void UseReleased_Implementation();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Items/UsableItem.h"
#include "Gun.generated.h"

UENUM(BlueprintType)
enum class EGunTypes : uint8 {
	WT_SR UMETA(DisplayName = "Sniper"),
	WT_SG UMETA(DisplayName = "Shotgun"),
	WT_AR UMETA(DisplayName = "Assault Rifle"),
	WT_SMG UMETA(DisplayName = "Submachine Gun")
};

UCLASS()
class SHOOTER_API AGun : public AUsableItem
{
	GENERATED_BODY()
	
public:
	AGun();

	virtual void Use_Implementation() override;
	virtual void UseReleased_Implementation() override;

	bool bInfiniteAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info")
		EGunTypes GunType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info")
		float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info")
		bool bFullAuto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	int32 AmmoInGun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info")
		int32 AmmoCapacity;

	FTimerHandle TimerHandle_TimeBetweenShot;
	float LastFireTime;


protected:
	virtual void BeginPlay() override;

	void Fire();

	void Shoot();

	void StartFire();

	void StopFire();
};

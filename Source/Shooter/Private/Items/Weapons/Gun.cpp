// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Items/Weapons/Gun.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Public/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"

AGun::AGun() {
	GunType = EGunTypes::WT_AR;
	FireRate = 0.1f;
	bFullAuto = false;
	AmmoInGun = 0;
	AmmoCapacity = 30;
}


void AGun::BeginPlay()
{
	Super::BeginPlay();

	AmmoInGun = AmmoCapacity;
}

void AGun::Use_Implementation()
{
	if (bFullAuto) {
		StartFire();
	}
	else {
			Fire();
		
	}
}

void AGun::UseReleased_Implementation()
{
	if (bFullAuto) {
		StopFire();
	}
}

void AGun::Fire()
{
	if (AmmoInGun > 0 || bInfiniteAmmo) {
		switch (GunType) {
		case EGunTypes::WT_AR:
			Shoot();
				AmmoInGun -= 1;
			break;
		}
	}
}

void AGun::Shoot()
{
	ASCharacter* OwningCharacter = Cast<ASCharacter>(GetOwner());
	if (OwningCharacter) {

		FHitResult OutHit(ForceInit);
		FVector Start = OwningCharacter->FppCamera->GetComponentLocation();
		FVector End = (OwningCharacter->GetControlRotation().Vector() * 100000.f) + Start;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(OwningCharacter);

		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, Params)) {
			DrawDebugLine(GetWorld(), Start, OutHit.Location, FColor::Red, true, -1.f);
			DrawDebugLine(GetWorld(), OutHit.Location, End, FColor::Green, true, -1.f);
		}
		LastFireTime = GetWorld()->TimeSeconds;
		
	}
}

void AGun::StartFire()
{
	float FirstDelay = FMath::Max(LastFireTime + FireRate - GetWorld()->TimeSeconds, 0.f);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShot, this, &AGun::Fire, FireRate, true, FirstDelay);
}

void AGun::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShot);
}

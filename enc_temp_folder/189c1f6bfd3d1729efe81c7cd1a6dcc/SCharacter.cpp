// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/SCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Public/Items/UsableItem.h"
#include "Engine/World.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentItem = nullptr;

	FppCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FppCamera->SetupAttachment(RootComponent);
	FppCamera->SetRelativeLocation(FVector(0.f, 0.f, 75.f));
	FppCamera->bUsePawnControlRotation = true;
	FppCamera->FieldOfView = 103.f;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();


	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;

	CurrentItem = GetWorld()->SpawnActor<AUsableItem>(CurrentItemToSpawn, Location, Rotation, SpawnInfo);
}

void ASCharacter::MoveForward(float Value)
{
	FVector WorldDirection = UKismetMathLibrary::GetForwardVector(FRotator(0.f, GetControlRotation().Yaw, 0.f));

	AddMovementInput(WorldDirection, Value);
}

void ASCharacter::MoveRight(float Value)
{
	FVector WorldDirection = UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, 0.f));

	AddMovementInput(WorldDirection, Value);
}

void ASCharacter::Use()
{
	if (CurrentItem) {
		CurrentItem->Use();
	}
}

void ASCharacter::UseReleased()
{
	if (CurrentItem) {
		CurrentItem->UseReleased();
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASCharacter::StopJumping);
    
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ASCharacter::Use);
	PlayerInputComponent->BindAction("Use", IE_Released, this, &ASCharacter::UseReleased);
}


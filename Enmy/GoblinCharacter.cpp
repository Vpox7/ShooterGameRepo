// Fill out your copyright notice in the Description page of Project Settings.

#include "GoblinCharacter.h"
#include "Camera/CameraComponent.h"
// Sets default values
AGoblinCharacter::AGoblinCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 5;

	
	
}
// Called when the game starts or when spawned
void AGoblinCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoblinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

// Called to bind functionality to input
void AGoblinCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AGoblinCharacter::UpdateHealthBar()
{
	

	return Health;

}







// Fill out your copyright notice in the Description page of Project Settings.


#include "Boom.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABoom::ABoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FD"));
	RootComponent = BoomMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("fes"));
	ProjectileMovement->InitialSpeed =2000;
	ProjectileMovement->MaxSpeed = 3000;


}

// Called when the game starts or when spawned
void ABoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "Khoj_Ki_Gofa/MyCharacter.h"
#include"Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystemComponent.h"

APistol::APistol()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SDF"));
	RootComponent = StaticMesh;
	
	MuzzleFlash = CreateDefaultSubobject<UParticleSystem>(TEXT("APRT"));
	

	

}



void APistol::BeginPlay()
{
	Super::BeginPlay();


	
}


void APistol::Muzzle()
{
	FName SocketName = "Muzzle";
	FTransform SocketTransform = StaticMesh->GetSocketTransform(SocketName);
	FVector SocketLoc = StaticMesh->GetSocketLocation(SocketName);
	FRotator SocketRoc = StaticMesh->GetSocketRotation(SocketName);

 
	GLog->Log("Muzzle flash");
	UWorld* world = GetWorld();
	UGameplayStatics::SpawnEmitterAtLocation(world, MuzzleFlash, SocketTransform);

	

}

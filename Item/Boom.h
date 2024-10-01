// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boom.generated.h"

UCLASS()
class KHOJ_KI_GOFA_API ABoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly)
	UStaticMeshComponent* BoomMesh;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly)
class 	UProjectileMovementComponent* ProjectileMovement;

};

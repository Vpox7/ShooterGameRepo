// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class KHOJ_KI_GOFA_API APistol : public AItemBase
{
	GENERATED_BODY()

public:
	APistol();


	virtual void BeginPlay() override;

	

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	class UStaticMeshComponent* StaticMesh;

	void Muzzle();

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	UParticleSystem* MuzzleFlash;

	


public:
	
	FORCEINLINE UStaticMeshComponent* GetPistolMesh() { return StaticMesh; }

	FORCEINLINE void GetMuzzle() { return Muzzle(); }

	
};

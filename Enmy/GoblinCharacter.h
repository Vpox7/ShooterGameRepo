// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GoblinCharacter.generated.h"

class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FenmyHealthChange,float,DamageHealth);


UCLASS()
class KHOJ_KI_GOFA_API AGoblinCharacter : public ACharacter
{
	GENERATED_BODY()



public:
	// Sets default values for this character's properties
	AGoblinCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:

	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintAssignable)
	FenmyHealthChange EnmyHealthChange;

	UFUNCTION(BlueprintCallable)
	float UpdateHealthBar();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Damage;

UPROPERTY(EditAnyWhere,BlueprintReadWrite)
bool bDied;

	
public:

	FORCEINLINE float  GetHealth() { return Health; }
	//FORCEINLINE UCameraComponent* GetGoblinCameraComponents() { return GoblinCameraComponent; }

};

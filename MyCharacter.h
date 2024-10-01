// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "MyCharacter.generated.h"



UENUM(BlueprintType)
enum class EWeaponEquip : uint8
{

	
	EWE_Pistol UMETA(DisplayName = "Pistol"),
	EWE_Knife UMETA(DisplayName = "Knife"),
	EWE_Boam UMETA(DisplayName = "Boam"),
};
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UNiagaraComponent;
class UAbilitySystemComponent;
class ABoom;

UDELEGATE(BlueprintAuthorityOnly)
 DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FhealthChanged,float,DamageHealth);

UCLASS()
class KHOJ_KI_GOFA_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, Category = Mesh)
	USkeletalMeshComponent* MeshBody;




	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;


	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickupAction;

	UPROPERTY(EditAnyWhere, Category = Sound)
	USoundBase* FireSound;


UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ALEX", meta = (AllowPrivateAccess = "true"))
	class	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Weapon1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Weapon2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Weapon3;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Reload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AutoGun;


	UPROPERTY(EditAnyWhere)
	UAnimMontage* KnifeMontage;

	UPROPERTY(EditAnyWhere)
	UAnimMontage* ThrowMontage;


		

public:
	
	AMyCharacter();

	UPROPERTY(EditAnyWhere)
	UParticleSystem* PistolFlash;


	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	UStaticMeshComponent* BoomMesh;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponEquip CurrentWeapon;


	UPROPERTY(EditAnyWhere)
	UAnimMontage* PistolMontage;

	UPROPERTY(EditAnyWhere)
	UAnimMontage* ReloadMontage;


	UPROPERTY(EditAnyWhere)
USoundBase* EmptyMag;

 UPROPERTY(EditAnyWhere,BlueprintReadWrite)
 bool bReloading = false;

 UPROPERTY(EditAnyWhere,BlueprintReadWrite)
 int32 Key;

	UPROPERTY(EditAnyWhere)
	USoundBase* KnifeSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "kNIFE")
	UStaticMeshComponent* KnifeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectTile")
class 	UProjectileMovementComponent* ProjectileMovement;


UPROPERTY(BlueprintReadWrite)
FhealthChanged HealthChanged;

float goblinDamage;

float goblinMaxHealth = 100;

UPROPERTY(EditAnyWhere,BlueprintReadWrite)
bool bDied;

bool bAutoGun;



protected:
	
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	void Fire();

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	USkeletalMeshComponent* RifileMesh;



UPROPERTY(EditAnyWhere,BlueprintReadWrite)
class	UParticleSystem* BloodeffectComponent;



	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "SCORE")
	int32 ScoreValue;

	UFUNCTION(BlueprintCallable)
	void ReloadLogic();

	void KnifeAttack();
	
	void Boom();

	UFUNCTION(BlueprintCallable)
	void BoomAttack();
	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	int32 BoomCounter;

	UFUNCTION(BlueprintCallable)
	void PistolFire();

	void KnifeEquip();

	void PistolEquip();

	void SwitchWeapon(EWeaponEquip WeaponState);

	void TapFire();

	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	bool bKnifeAttack;

	public:
		/*Boom Logic Function*/

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UProjectileMovementComponent* ProjectileMovementComponent;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
		float ExplosionDelay;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
		float ExplosionRadius;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
		float ExplosionDamage;



		UPROPERTY(EditAnyWhere,BlueprintReadWrite)
		float CurrentHealth;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float MaxHealth=110;

		void ReloadAnim();

		

	
private:

 FTimerHandle ExplosionTimer;


public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UCameraComponent* GetCameraComponents(){ return FirstPersonCameraComponent; }

	FORCEINLINE USkeletalMeshComponent* GetCharacterMesh() { return MeshBody; }

	FORCEINLINE USpringArmComponent* GetSpringArm() { return SpringArm; }

	
	/*Auto Gun Logic*/

	void StartFire();

	void StopFire();



	

	// Timer handle for managing shooting intervals
	FTimerHandle ShootingTimerHandle;
	FTimerHandle BulletCount;
	FTimerHandle ReloadTime;

	// Fire rate for automatic gun (time between shots)
	float FireRate; 
		int BulletRate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Bullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotlalBullets;

	


};

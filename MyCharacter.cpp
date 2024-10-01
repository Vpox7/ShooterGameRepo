// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Khoj_Ki_Gofa/Item/ItemBase.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Khoj_Ki_Gofa/Item/Pistol.h"
#include "Engine/StaticMeshSocket.h"
#include "Particles/ParticleSystem.h"
#include "Animation/AnimMontage.h"
#include "Enmy/GoblinCharacter.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Bullets = 45;
	ScoreValue = 0;
	TotlalBullets=30;
	bReloading = false;
	BoomCounter = 2;
	bKnifeAttack = false;
	Key = 0;
	
	FireRate = 0.1f;

	ExplosionDelay = 3.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 100.0f;
	// Set size for collision capsule
	
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	MeshBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Ske"));

	//RifileMesh->SetupAttachment(RootComponent);

	//BoomMesh->AttachToComponent(GetCharacterMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("BoomSocket"));

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	MeshBody->SetupAttachment(FirstPersonCameraComponent);


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)


	//static ConstructorHelpers::FObjectFinder<UBlueprint>KnifeAssets(TEXT("/Game/_Game/Blueprints/MyKnifeBp"));
	
	KnifeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mdf"));
	//KnifeMesh->AttachToComponent(GetCharacterMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HandSocket"));
	
	//PistolFlash = CreateDefaultSubobject<UParticleSystem>(TEXT("PART"));

	

	BloodeffectComponent = CreateDefaultSubobject<UParticleSystem>(TEXT("dfg"));


	RifileMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HEKK"));
	RifileMesh->SetupAttachment(MeshBody);
	//PistolMesh->AttachToComponent(GetCharacterMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("PistolSocket"));

	PistolFlash = CreateDefaultSubobject<UParticleSystem>(TEXT("sfdr"));
	//Bloodeffect = CreateDefaultSubobject<UNiagaraSystem>(TEXT("sdfsd"));

	BoomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SFDF"));
	
	
	
	//static ConstructorHelpers::FObjectFinder<UNiagaraComponent>NiagaraSystem(TEXT("Game/_Game/Mesh/Boam/F/bOOMvfo.bOOMvfo"));
	
	CurrentWeapon = EWeaponEquip::EWE_Pistol;
	RifileMesh->SetVisibility(true);
	BoomMesh->SetVisibility(false);
	KnifeMesh->SetVisibility(false);
	
	
	
	

	
}



// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();


	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	CurrentWeapon = EWeaponEquip::EWE_Pistol;
		
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}

}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyCharacter::Fire()
{
	
	switch (CurrentWeapon)
	{
	case EWeaponEquip::EWE_Pistol:
		RifileMesh->SetVisibility(true);
		BoomMesh->SetVisibility(false);
		KnifeMesh->SetVisibility(false);
		StartFire();
	
		break;
	case EWeaponEquip::EWE_Boam:

		RifileMesh->SetVisibility(false);
		BoomMesh->SetVisibility(true);
		KnifeMesh->SetVisibility(false);
		BoomAttack();
//GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "BOOM Attack", true);
		break;


	case EWeaponEquip::EWE_Knife:

		RifileMesh->SetVisibility(false);
		BoomMesh->SetVisibility(false);
		KnifeMesh->SetVisibility(true);
		KnifeAttack();	
		break;


	}
}

	







void AMyCharacter::ReloadLogic()
{
	int32 AmmoNeeded = 45 - Bullets;
	if (TotlalBullets >= AmmoNeeded)
	{

		TotlalBullets = FMath::Clamp(TotlalBullets, 0, 1500);
		TotlalBullets -= AmmoNeeded;
		Bullets = FMath::Clamp(Bullets, 0, 45);
		Bullets += AmmoNeeded;

	}
	else
	{
		Bullets = FMath::Clamp(Bullets, 0, 45);
		Bullets += TotlalBullets;
		TotlalBullets = 0;
		
	}
}
	
	






void AMyCharacter::KnifeAttack()
{

	
	UAnimInstance* CharacterInstance = GetCharacterMesh()->GetAnimInstance();
	
	if (KnifeMontage && KnifeSound && bKnifeAttack ==false)
	{
		bKnifeAttack = true;
		CharacterInstance->Montage_Play(KnifeMontage, 1);
		UGameplayStatics::PlaySound2D(this, KnifeSound);
		



	}
}



void AMyCharacter::Boom()
{
	
		CurrentWeapon = EWeaponEquip::EWE_Boam;
		RifileMesh->SetVisibility(false);
		KnifeMesh->SetVisibility(false);
		BoomMesh->SetVisibility(true);

		BoomMesh->AttachToComponent(GetCharacterMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("BoomSocket"));



	

}

void AMyCharacter::BoomAttack()
{

	UAnimInstance* CharacterInstance = GetCharacterMesh()->GetAnimInstance();
	if (CharacterInstance && ThrowMontage && BoomCounter !=0)
	{
		CharacterInstance->Montage_Play(ThrowMontage);
		BoomCounter = FMath::Clamp(BoomCounter, 0, 1540);
			
	}




}



void AMyCharacter::PistolFire()
{
	if (Bullets <= 0)
	{
		
 UGameplayStatics::PlaySound2D(this, EmptyMag);
		
	}
	else if(bReloading==false)
	{
		//GEngine->AddOnScreenDebugMessage(1, 2, FColor::Blue, "BAD CODE");
		FVector StartLoc = FirstPersonCameraComponent->GetComponentLocation();
		FVector ForwardLoc = FirstPersonCameraComponent->GetForwardVector();
		FVector EndLoc = StartLoc + ForwardLoc * 2000;
		FHitResult HitResult;
		//NoiseEmitterComp->MakeNoise(this, 1.0f, GetActorLocation());
		AGoblinCharacter* GoblinRefX = Cast<AGoblinCharacter>(GetMesh());

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		UAnimInstance* CharacterInstance = GetCharacterMesh()->GetAnimInstance();
		GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_WorldStatic, Params);
		//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, 2.f);
		
		Bullets = FMath::Clamp(Bullets, 0, 60);
		Bullets--;
		
		const FTransform PistolTrans = RifileMesh->GetSocketTransform(FName("Muzzle"));
	
		if (CharacterInstance && PistolMontage)
		{
			UGameplayStatics::SpawnEmitterAttached(PistolFlash, RifileMesh, "Muzzle");
			UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
			CharacterInstance->Montage_Play(PistolMontage);

		}
		/**/

		AGoblinCharacter* GoblinRef = Cast<AGoblinCharacter>(HitResult.GetActor());
		if (GoblinRef && GoblinRef == HitResult.GetActor())
		{
			
			//GoblinRef->Health-= 20;

			FVector HitLoc = HitResult.Location;

			UGameplayStatics::SpawnEmitterAtLocation(this, BloodeffectComponent, HitResult.Location, FRotator::ZeroRotator, true);

			GoblinRef->Health -= 0.12;

			GoblinRef->EnmyHealthChange.Broadcast(GoblinRef->Health);

		}

	}

}

void AMyCharacter::KnifeEquip()
{
	
		CurrentWeapon = EWeaponEquip::EWE_Knife;
		RifileMesh->SetVisibility(false);
		KnifeMesh->SetVisibility(true);
		BoomMesh->SetVisibility(false);
		FName SocketName = "HandSocket";
		KnifeMesh->AttachToComponent(GetCharacterMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

		UWorld* world = GetWorld();
		FTransform KnifeTransform = KnifeMesh->GetSocketTransform(SocketName);
		//UGameplayStatics::SpawnEmitterAtLocation(world, PistolFlash, KnifeTransform, true);
		RifileMesh->SetVisibility(false);

}

void AMyCharacter::PistolEquip()
{
	
	
		CurrentWeapon = EWeaponEquip::EWE_Pistol;
		RifileMesh->AttachToComponent(GetCharacterMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("PistolSocket"));
		RifileMesh->SetVisibility(true);
		KnifeMesh->SetVisibility(false);
		
		BoomMesh->SetVisibility(false);


	
	

}

void AMyCharacter::SwitchWeapon(EWeaponEquip WeaponState)
{
	switch (CurrentWeapon)
	{
	case EWeaponEquip::EWE_Pistol:
		
		KnifeMesh->SetVisibility(false);
		RifileMesh->SetVisibility(true);
		BoomMesh->SetVisibility(false);
		
		break;
	case EWeaponEquip::EWE_Knife:
		KnifeMesh->SetVisibility(true);
		RifileMesh->SetVisibility(false);
		BoomMesh->SetVisibility(false);
	
		break;
	case EWeaponEquip::EWE_Boam:
		KnifeMesh->SetVisibility(false);
		RifileMesh->SetVisibility(false);
		BoomMesh->SetVisibility(true);
		
		break;
	}
	
}

void AMyCharacter::TapFire()
{
	switch (CurrentWeapon) {
	case EWeaponEquip::EWE_Pistol:
		PistolFire();
		break;
	}
}







void AMyCharacter::ReloadAnim()
{
	UAnimInstance* CharacterAnim = GetCharacterMesh()->GetAnimInstance();

	int32 AmmoNeeded = 45 - Bullets;
	if (Bullets == 45)
	{
		return;
	}

	if (CharacterAnim  && TotlalBullets>=AmmoNeeded && bReloading==false)
	{
	
		
		if (TotlalBullets == 0)
		{
			return;
		}
		bReloading = true;
		CharacterAnim->Montage_Play(ReloadMontage);
		
			
	}
	if (TotlalBullets != 0 && bReloading==false)
	{
		bReloading = true;
		CharacterAnim->Montage_Play(ReloadMontage);
	
	}

	

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentHealth == 0)
	{
		bDied = true;
	}


}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AMyCharacter::Fire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AMyCharacter::StopFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMyCharacter::TapFire);

		//EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AMyCharacter::StopFire);
		


		EnhancedInputComponent->BindAction(Weapon1, ETriggerEvent::Triggered, this, &AMyCharacter::KnifeEquip);

		EnhancedInputComponent->BindAction(Weapon2, ETriggerEvent::Triggered, this, &AMyCharacter::PistolEquip);
		EnhancedInputComponent->BindAction(Weapon3, ETriggerEvent::Triggered, this, &AMyCharacter::Boom);
		EnhancedInputComponent->BindAction(Reload, ETriggerEvent::Triggered, this, &AMyCharacter::ReloadAnim);
		//EnhancedInputComponent->BindAction(FireAction,)
	}
	
}

void AMyCharacter::StartFire()
{
	if(bReloading==false)
		GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &AMyCharacter::PistolFire, FireRate, true, -1.f);
		//GetWorld()->GetTimerManager().SetTimer(BulletCount, this, &AMyCharacter::BulletLoss,BulletRate -1.f);
	
}

void AMyCharacter::StopFire()
{

	
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);


}



// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include <CPPGame/DamageableActor.h>

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSCharacter::fireWeapon() 
{
	FHitResult hit = instantShot();
	ADamageableActor* hitActor = Cast<ADamageableActor>(hit.Actor);
	if (hitActor && hitActor->isAttackable) {
		hitActor->takeAttack();
	}
}

FHitResult AFPSCharacter::instantShot()
{
	FVector rayLocation;
	FRotator rayRotation;
	FVector endTrace = FVector::ZeroVector;
	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();

	// Get rotation and rotation of the player viewpoint
	if (playerController) {
		playerController->GetPlayerViewPoint(rayLocation, rayRotation);
		endTrace = rayLocation + (rayRotation.Vector() * weaponRange);
	}

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(instantShot), true, GetInstigator());
	FHitResult hit(ForceInit);
	
	// Generate a raycast in the game world and store the FHitResult
	GetWorld()->LineTraceSingleByChannel(hit, rayLocation, endTrace, ECC_Visibility, traceParams);

	return hit;
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


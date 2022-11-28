// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Casing.h"

// Engine Includes
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ACasing::ACasing()
{
 	PrimaryActorTick.bCanEverTick = false;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasingMesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);

	// set for hit events triggers from physics
	CasingMesh->SetNotifyRigidBodyCollision(true);

	ShellEjectionImpulse = 10.f;

	LifeTimeAfterOnHit = 3.f;
	OnHitTriggered = false;
}


void ACasing::BeginPlay()
{
	Super::BeginPlay();

	CasingMesh->OnComponentHit.AddDynamic(this, &ACasing::OnHit);
	CasingMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);

	
	
}


void ACasing::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OnHitTriggered)
	{
		OnHitTriggered = true;

		if (ShellSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
		}

		GetWorldTimerManager().SetTimer(TimeHandle_LifetimeAfterOnHit, this, &ACasing::OnLifetimeAfterOnHitExceeded, LifeTimeAfterOnHit, false);
	}
}

void ACasing::OnLifetimeAfterOnHitExceeded()
{
	GetWorldTimerManager().ClearTimer(TimeHandle_LifetimeAfterOnHit);
	Destroy();
}


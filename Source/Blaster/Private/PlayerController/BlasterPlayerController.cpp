// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/BlasterPlayerController.h"


// Engine Includes
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


// Game Includes
#include "HUD/BlasterHUD.h"
#include "HUD/CharacterOverlay.h"
#include "Character/BlasterCharacter.h"


void ABlasterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	BlasterHUD = Cast<ABlasterHUD>(GetHUD());
}


void ABlasterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();
}


void ABlasterPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(InPawn);
	if (BlasterCharacter)
	{
		SetHUDHealth(BlasterCharacter->GetHealth(), BlasterCharacter->GetMaxHealth());
	}
}


void ABlasterPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

	bool bHUDValid = BlasterHUD &&
		BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->HealthBar &&
		BlasterHUD->CharacterOverlay->HealthText;

	if (bHUDValid && MaxHealth > 0.f)
	{
		const float HealthPercent = Health / MaxHealth;
		BlasterHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);

		FString HealthText = FString::Printf(TEXT("%d / %d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		BlasterHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}

}


void ABlasterPlayerController::SetHUDScore(float Score)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	if (BlasterHUD)
	{
		bool bHUDValid = BlasterHUD &&
			BlasterHUD->CharacterOverlay &&
			BlasterHUD->CharacterOverlay->ScoreAmount;
		if (bHUDValid)
		{
			FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
			BlasterHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
		}
	}
}


void ABlasterPlayerController::SetHUDDefeats(int32 Defeats)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	if (BlasterHUD)
	{
		bool bHUDValid = BlasterHUD &&
			BlasterHUD->CharacterOverlay &&
			BlasterHUD->CharacterOverlay->DefeatsAmount;
		if (bHUDValid)
		{
			FString DefeatsText = FString::Printf(TEXT("%d"), Defeats);
			BlasterHUD->CharacterOverlay->DefeatsAmount->SetText(FText::FromString(DefeatsText));
		}
	}
}


void ABlasterPlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	if (BlasterHUD)
	{
		bool bHUDValid = BlasterHUD &&
			BlasterHUD->CharacterOverlay &&
			BlasterHUD->CharacterOverlay->WeaponAmmoAmount;
		if (bHUDValid)
		{
			FString WeaponAmmoAmountText = FString::Printf(TEXT("%d"), Ammo);
			BlasterHUD->CharacterOverlay->WeaponAmmoAmount->SetText(FText::FromString(WeaponAmmoAmountText));
		}
	}
}


void ABlasterPlayerController::SetHUDCarriedAmmo(int32 Ammo)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	if (BlasterHUD)
	{
		bool bHUDValid = BlasterHUD &&
			BlasterHUD->CharacterOverlay &&
			BlasterHUD->CharacterOverlay->CarriedAmmoAmount;
		if (bHUDValid)
		{
			FString CarriedAmmoAmountText = FString::Printf(TEXT("%d"), Ammo);
			BlasterHUD->CharacterOverlay->CarriedAmmoAmount->SetText(FText::FromString(CarriedAmmoAmountText));
		}
	}
}


void ABlasterPlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	if (BlasterHUD)
	{
		bool bHUDValid = BlasterHUD &&
			BlasterHUD->CharacterOverlay &&
			BlasterHUD->CharacterOverlay->MatchCountdownText;
		if (bHUDValid)
		{
			int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
			int32 Seconds = CountdownTime - Minutes * 60;

			FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
			BlasterHUD->CharacterOverlay->MatchCountdownText->SetText(FText::FromString(CountdownText));
		}
	}
}


void ABlasterPlayerController::SetHUDTime()
{
	uint32 SecondsLeft = FMath::CeilToInt(MatchTime - GetWorld()->GetTimeSeconds());
	if (CountdownInt != SecondsLeft)
	{
		SetHUDMatchCountdown(MatchTime - GetWorld()->GetTimeSeconds());
	}

	CountdownInt = SecondsLeft;
}


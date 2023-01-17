// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float CountdownTime);


	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	/** Synced with server world clock */
	virtual float GetServerTime();

	/** Sync with server clock ASAP */
	virtual void ReceivedPlayer() override;

protected: 

	virtual void BeginPlay() override;
	void SetHUDTime();
	
	/**
	 * Sync timer between client and server
	 */

	 // Requests the current server time, passing in the the client's time when the request was sent
	 UFUNCTION(Server, Reliable)
	 void ServerRequestServerTime(float TimerOfClientRequest);

	 //Reports the current server time to the client in response to ServerRequestServerTime
	 UFUNCTION(Client, Reliable)
	 void ClientReportServerTime(float TimeOfClientRequest, float TimerServerReceivedClientRequest);

	 float ClientServerDelta = 0.f; // difference between server and client time;

	 UPROPERTY(EditAnywhere, Category = Time)
	 float TimeSyncFrequency = 5.f;

	 float TimeSyncRunningTime = 0.f;

	 void CheckTimeSync(float DeltaTime);

private:

	UPROPERTY()
	class ABlasterHUD* BlasterHUD;

	float MatchTime = 120.f;
	uint32 CountdownInt = 0;
	
};

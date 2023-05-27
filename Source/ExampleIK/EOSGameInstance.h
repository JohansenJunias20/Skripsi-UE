// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "VoiceChat.h"
#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemEOS.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlinePartyInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "EOSGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMulticastEvent);
/**
 * 
 */

USTRUCT(BlueprintType)
struct FStructDevice
{
	GENERATED_BODY()

	//~ The following member variable will be accessible by Blueprint Graphs:
	// This is the tooltip for our test variable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

};

UCLASS()
class EXAMPLEIK_API UEOSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UEOSGameInstance();
	UPROPERTY(BlueprintAssignable);
	FMulticastEvent onLeaveSession;
	UFUNCTION(BlueprintCallable)
	FString gen_random(int len) {
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		FString tmp_s = "";

		for (int i = 0; i < len; ++i) {
			tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}
    
		return tmp_s;
	}
	UFUNCTION(BlueprintCallable)
	bool writeFile(FString nameFile, TArray<FString> isi);
	virtual void Init() override;
	FName _RoomSessionName = FName("Testing");
	// void OnLoginVoiceComplete(const FString& String, const FVoiceChatResult& VoiceChatResult);
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	UFUNCTION(BlueprintCallable)
	void HasSession(FString SessionName);
	UFUNCTION(BlueprintCallable)
	void Login();
	UFUNCTION(BlueprintCallable)
	int binomialCoeff(int n, int k);
	FOnlineSubsystemEOS* GetOnlineSubsystemEos();
	UPROPERTY(BlueprintReadWrite)
	bool isOnLobby = false;
	TSharedPtr<FOnlineSessionSearch> SearchSetting ;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString nickname;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsLogin = false;
	int onRecord;
	// int PartyId;
	UFUNCTION(BlueprintCallable)
	void InvitePlayer(int32 index);
	UFUNCTION(BlueprintCallable)
	void CreateParty();
	UFUNCTION(BlueprintCallable)
	void JoinParty();
	UFUNCTION(BlueprintCallable)
	void CreateSession();
	UFUNCTION(BlueprintCallable)
	void LeaveSession();
	void OnSearchSessionComplete(bool bArg);
	UFUNCTION(BlueprintCallable)
	void FindSession();
	UFUNCTION(BlueprintCallable)
	void DestroySession();
	UFUNCTION(BlueprintCallable)
	void ExecuteFile();
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	UFUNCTION(BlueprintCallable)
	void BlockPlayer(FString playerName);
	UFUNCTION(BlueprintCallable)
	void GetVOIPTalker();
	UFUNCTION(BlueprintCallable)
	TArray<FStructDevice> getOutputDevices();
	UFUNCTION(BlueprintCallable)
	TArray<FStructDevice> getInputDevices();
	UFUNCTION(BlueprintCallable)
	FString getPlayerNameVoiceEOS();
	UFUNCTION(BlueprintCallable)
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnCreatePartyComplete(
			const FUniqueNetId& LocalUserId,
			const TSharedPtr<const FOnlinePartyId>& PartyId,
			const ECreatePartyCompletionResult Result);

protected:
	class IOnlineSubsystem* OnlineSubsystem;
	class ISocketSubsystem* test;
	class FOnlineAccountCredentials* _Credentials;

};

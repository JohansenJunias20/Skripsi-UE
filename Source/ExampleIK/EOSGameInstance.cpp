// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSGameInstance.h"
//#include "../../../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/Online/IOS/OnlineSubsystemIOS/Source/Private/OnlineSessionInterfaceIOS.h"
//#include "../../../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/OnlineSubsystemEOS.h"
//#include "../../../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/Online/OnlineSubsystemEOS/Source/"
//#include "../../../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/OnlineSessionSettings.h"
//#include "../../../../../../../../Program Files/Epic Games/UE_5.0/Engine/Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionInterface.h"
#include "EOSGameInstance.h"

#include <string>

#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystemEOS.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlinePartyInterface.h"
#include "Interfaces/OnlinePartyInterface.h"
#include "VoiceChat.h"
const FName TestSessionName = FName("Test Session");

UEOSGameInstance::UEOSGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("V1.0"));
}

bool UEOSGameInstance::writeFile(FString nameFile, TArray<FString> isi)
{
	FString file = FPlatformProcess::UserDir();
	// FString file = nameFile;

	file.Append(nameFile);

	// We will use this FileManager to deal with the file.
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	UE_LOG(LogTemp, Warning, TEXT("This is the data: %s"), *FString(file));
	// Always first check if the file that you want to manipulate exist.
	
		// We use the LoadFileToString to load the file into
		if(FFileHelper::SaveStringArrayToFile(isi,*file))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Sucsesfuly Written: to the text file"));
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Failed to write FString to file."));
			return  false;
		}
	
}

void UEOSGameInstance::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("Success"));
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Initing v1.0"));

	OnlineSubsystem = IOnlineSubsystem::Get();
	// Login();
}


void UEOSGameInstance::ExecuteFile()
{
	UE_LOG(LogTemp, Warning, TEXT("executing"));
	// FPlatformProcess::CreateProc(TEXT("C:\\Users\\c1419\\source\\repos\\router-rebooter\\ConsoleApp1\\ConsoleApp1\\bin\\Debug\\netcoreapp3.1\\ConsoleApp1.exe"), nullptr, true, false, false, nullptr, 0, nullptr, nullptr);
}

// #include "VoiceChat.h"

void UEOSGameInstance::Login()
{
	UE_LOG(LogTemp, Warning, TEXT("Logging in0..."));

	if (OnlineSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Logging in1..."));

		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			UE_LOG(LogTemp, Warning, TEXT("Logging in2..."));
			// Identity->
			FOnlineAccountCredentials Credentials;
			// ini harus buka auth dev tool pada SDK yang di bagian tools
			// .exe itu nanti berpihak sebagai server authentication palsu / decoy.
			// jadi auth nya nanti request ke sana for development purpose
			// typenya developer, tetapi pas deploy ganti "useraccount"
			// Credentials.Id = FString("192.168.1.16:6300");
			// Credentials.Token = FString("Johansen");
			// Credentials.Type = FString("developer");
			// Credentials.Id = FString();
			// Credentials.Token = FString();
			// Credentials.Type = FString("persistentauth");
			Credentials.Type = FString("accountportal");
			//Credentials.
			Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOSGameInstance::OnLoginComplete);
			//_Credentials = &Credentials;
			Identity->Login(0, Credentials);
		}
	}
}

int UEOSGameInstance::binomialCoeff(int n, int k)
{
	if (k > n)
		return 0;
	if (k == 0 || k == n)
		return 1;
 
	// Recur
	return binomialCoeff(n - 1, k - 1)
		   + binomialCoeff(n - 1, k);
}


FOnlineSubsystemEOS* UEOSGameInstance::GetOnlineSubsystemEos()
{
	return static_cast<FOnlineSubsystemEOS*>(OnlineSubsystem);
}

void UEOSGameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                       const FString& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("Error:"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ERROR:"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
	bIsLogin = bWasSuccessful;
	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			// IVoiceChat* VoiceChat = IVoiceChat::Get();

			Identity->ClearOnLoginCompleteDelegates(0, this);
			this->nickname = Identity->GetPlayerNickname(0);
			UE_LOG(LogTemp, Warning, TEXT("BERHASIL LOGIN"));
			UE_LOG(LogTemp, Warning, TEXT("BERHASIL LOGIN"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("BERHASIL LOGIN"));

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "my nickname is:");
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, nickname);

			HasSession("Testing");
		}
	}
}

void UEOSGameInstance::HasSession(FString SessionName)
{
	if (OnlineSubsystem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Finding Session Online!"));
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			// Search->QuerySettings.SearchParams.Empty();

			SearchSetting = MakeShareable(new FOnlineSessionSearch());
			// SearchSetting->QuerySettings->se
			SearchSetting->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
			SearchSetting->QuerySettings.Set(SEARCH_KEYWORDS, SessionName, EOnlineComparisonOp::Equals);
			SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnSearchSessionComplete);
			SessionPtr->FindSessions(0, SearchSetting.ToSharedRef());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SessionPtr NOT available..."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("online subsystem NOT available..."));
	}
}


void UEOSGameInstance::InvitePlayer(int32 indexPlayer)
{
	// FUniqueNetIdPtr ab = *OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(indexPlayer);

	// FPartyInvitationRecipient Recipient = FPartyInvitationRecipient();
	// int partyID = IOnlinePartySystem::GetPrimaryPartyTypeId();
	// Send the invitation.
	// if (!OnlineSubsystem->GetPartyInterface()->SendInvitation(
	// 		*OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(0).Get(), // The ID of the player sending the invite.
	// 		*IOnlinePartySystem::GetPrimaryPartyTypeId(),                     // The party to invite the target player to.
	// 		Recipient,
	// 		FOnSendPartyInvitationComplete::CreateLambda([](
	// 						const FUniqueNetId &LocalUserId,
	// 						const FOnlinePartyId &PartyId,
	// 						const FUniqueNetId &RecipientId,
	// 						const ESendPartyInvitationCompletionResult Result) {
	// 			// If Result == ESendPartyInvitationCompletionResult::Succeeded, 
	// 			// the invitation was sent successfully.
	// 		})))
	// {
	// 	// Call didn't start, return error.
	// }
	return;
}

void UEOSGameInstance::CreateParty()
{
	// IOnlinePartyPtr Party = OnlineSubsystem->GetPartyInterface();
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	IOnlinePartyPtr Party = Subsystem->GetPartyInterface();

	if (!Party)
	{
		UE_LOG(LogTemp, Warning, TEXT("PartyPtr not found"));
		return;
	}
	IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
	TSharedRef<FPartyConfiguration> Config = MakeShared<FPartyConfiguration>();
	Config->bIsAcceptingMembers = true;
	// Config->bChatEnabled = true;
	Config->MaxMembers = 4; // The maximum number of players in the party.
	if (!Party->CreateParty(
		*Identity->GetUniquePlayerId(0).Get(), // The local player creating the party.
		(FOnlinePartyTypeId)0, // The party type ID.
		*Config,
		FOnCreatePartyComplete::CreateLambda([](
			const FUniqueNetId& LocalUserId,
			const TSharedPtr<const FOnlinePartyId>& PartyId,
			const ECreatePartyCompletionResult Result)
			{
				// UE_LOG(LogTemp, Warning, TEXT("SUCCESS TO CREATE PARTY, YOU ARE THE PARTY LEADER"));
				// If Result == ECreatePartyCompletionResult::Succeeded, the party
				// was created and you are now the party leader.
				// if (Result == ECreatePartyCompletionResult::Succeeded)
				// {
				// 	// this->InvitePlayer(1);
				// 	// const FOnlinePartyId test = PartyId.Get();
				// }
			})))
	{
		// UE_LOG(LogTemp, Warning, TEXT("FAILED TO CREATE PARTY"));
		return;
		// Call didn't start, return error.
	}
	// FPartyInvitationRecipient Recipient = FPartyInvitationRecipient(OnlineSubsystem);
}

void UEOSGameInstance::JoinParty()
{
	// IOnlinePartyPtr Party = OnlineSubsystem->GetPartyInterface();
	// TArray<IOnlinePartyJoinInfoConstRef> OutPendingInvitesArray;
	// Party->GetPendingInvites(*OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(0).Get(),
	//                          OutPendingInvitesArray);
	// int32 lengthParty = OutPendingInvitesArray.Num();
	//
	// UE_LOG(LogTemp, Warning, TEXT("the length of party are: %s"), lengthParty);
	// return;
	// if (!Party->JoinParty(
	// 	*OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(0).Get(),
	// 	OutPendingInvitesArray[0].Get(),
	// 	FOnJoinPartyComplete::CreateLambda([](
	// 		const FUniqueNetId& LocalUserId,
	// 		const FOnlinePartyId& PartyId,
	// 		const EJoinPartyCompletionResult Result,
	// 		const int32 NotApprovedReason)
	// 		{
	// 			// If Result == EJoinPartyCompletionResult::Succeeded, the party 
	// 			// was joined successfully, and you can now access the party with 
	// 			// the GetParty and GetJoinedParties functions.
	// 		})))
	// {
	// 	// Call didn't start, return error.
	// }
}

void UEOSGameInstance::CreateSession()
{
	UE_LOG(LogTemp, Warning, TEXT("creating session, please login first"));

	//if (!bIsLogin) {
	//	return;
	//}
	if (OnlineSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("online subsystem available..."));
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			// IOnlineVoicePtr voicePtr = OnlineSubsystem->getvoi();
			IOnlineVoicePtr voicePtr;
			UE_LOG(LogTemp, Warning, TEXT("creating session..."));
			FOnlineSessionSettings SessionSettings;
			SessionSettings.bIsDedicated = false;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bIsLANMatch = false;
			SessionSettings.bUseLobbiesIfAvailable = true; //bila ingin di discover pada master server di dev.portal
			SessionSettings.NumPublicConnections = 10;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bUsesPresence = true;
			// SessionSettings.prese
			SessionSettings.bUseLobbiesVoiceChatIfAvailable = true;
			// SessionSettings.voi
			// SessionSettings.voi
			SessionSettings.Set(SEARCH_KEYWORDS, FString("Testing"), EOnlineDataAdvertisementType::ViaOnlineService);
			SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnCreateSessionComplete);
			SessionPtr->CreateSession(0, TestSessionName, SessionSettings);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SessionPtr NOT available..."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("online subsystem NOT available..."));
	}
}

void UEOSGameInstance::LeaveSession()
{
	if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
	{
		// IOnlineVoicePtr voicePtr = OnlineSubsystem->getvoi();
		this->DestroySession();

		onLeaveSession.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SessionPtr NOT available..."));
	}
}

void UEOSGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Success"), bWasSuccessful);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Success create session!"));
	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			// Audio::FPatchOutputStrongPtr v = voice->GetRemoteTalkerOutput();
			// voice->GetAmplitudeOfRemoteTalker(2.0f);
			// v->
			// IVoiceChat::Get()->;
			// voice->devi
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
			isOnLobby = true;
			GetWorld()->ServerTravel(FString("TestMap?listen"), false);
		}
	}
}

void UEOSGameInstance::BlockPlayer(FString Nickname)
{
	FOnlineSubsystemEOS* obj = GetOnlineSubsystemEos();
	IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
	IVoiceChatUser* voice = obj->GetVoiceChatUserInterface(*Identity->GetUniquePlayerId(0));
	// obj->voice
	if (voice)
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr available..."));
		// UE_LOG(LogTemp, Warning, TEXT("the name is: %s"), *FString(Identity->GetPlayerNickname(0)));
		// voice->SetPlayerMuted(FString(Identity->GetPlayerNickname(0)), true);
		// voice->SetAudioInputVolume(FString(Identity->GetPlayerNickname(0)), 0.3);
		// voice->StartRecording(&UEOSGameInstance::onRecieveSample);
		voice->SetPlayerVolume(Nickname, 0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr NOT available..."));
	}
}

// FOnlineSubsystemEOS* UEOSGameInstance::GetOnlineSubsystemEos()
// {
// 	// IOnlineSubsystem* ossBase = Online::GetSubsystem(GetWorld(), "EOS");
// 	return static_cast<FOnlineSubsystemEOS*>(OnlineSubsystem);
// }

void UEOSGameInstance::GetVOIPTalker()

{
	FOnlineSubsystemEOS* obj = GetOnlineSubsystemEos();
	IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
	TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(0);
	FPlatformUserId PlatformUserId = Identity->GetPlatformUserIdFromUniqueNetId(*UserId);
	IVoiceChatUser* voice = obj->GetVoiceChatUserInterface(*UserId);
	// obj->voice
	if (voice)
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr available..."));
		UE_LOG(LogTemp, Warning, TEXT("the name is: %s"), *FString(Identity->GetPlayerNickname(0)));
		// voice->SetPlayerMuted(FString(Identity->GetPlayerNickname(0)), true);
		// voice->SetAudioInputVolume(FString(Identity->GetPlayerNickname(0)), 0.3);
		// voice->StartRecording(&UEOSGameInstance::onRecieveSample);
		// voice->SetPlayerVolume(FString(Identity->GetPlayerNickname(0)), 0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr NOT available..."));
	}

	IOnlineVoicePtr voice2 = GetOnlineSubsystemEos()->GetVoiceInterface();
	if (voice2.IsValid())
	{
		// voice2->
		// voice2->GetRemoteTalkerOutput();
		UE_LOG(LogTemp, Warning, TEXT("IOnlineVoicePtr available..."));
		// voice2.Get()->remo
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IOnlineVoicePtr IS NOT available..."));
	}

	FEOSVoiceChatUser* voice3 = obj->GetEOSVoiceChatUserInterface(*UserId);
	if (voice3)
	{
		UE_LOG(LogTemp, Warning, TEXT("FEOSVoiceChatUser available..."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FEOSVoiceChatUser IS NOT available..."));
	}

	// IOnlineVoicePtr voice =  GetOnlineSubsystemEos()->GetVoiceInterface();
	// if (voice.IsValid())
	// {	
	// 	// voice->GetRemoteTalkerOutput();
	// 	UE_LOG(LogTemp, Warning, TEXT("VoicePtr available..."));
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("VoicePtr NOT available..."));
	// }
}

TArray<FStructDevice> UEOSGameInstance::getOutputDevices()
{
	TArray<FStructDevice> finalDevices = TArray<FStructDevice>();
	if (!OnlineSubsystem) return finalDevices;
	if (!bIsLogin) return finalDevices;
	UE_LOG(LogTemp, Warning, TEXT("getting OSS EOS..."));

	FOnlineSubsystemEOS* obj = GetOnlineSubsystemEos();
	UE_LOG(LogTemp, Warning, TEXT("GETTING IDENTITY INTERFACE..."));
	IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
	// UE_LOG(LogTemp, Warning, TEXT("GETTING USERID..."));
	// TSharedPtr<const FUniqueNetId> UserId = ;
	UE_LOG(LogTemp, Warning, TEXT("GETTING VOICE..."));
	IVoiceChatUser* voice = obj->GetVoiceChatUserInterface(*Identity->GetUniquePlayerId(0));
	// obj->voice
	if (voice)
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr line 394 available..."));
		UE_LOG(LogTemp, Warning, TEXT("the name is: %s"), *FString(Identity->GetPlayerNickname(0)));
		// voice->SetPlayerMuted(FString(Identity->GetPlayerNickname(0)), true);
		// voice->SetAudioInputVolume(FString(Identity->GetPlayerNickname(0)), 0.3);
		// voice->StartRecording(&UEOSGameInstance::onRecieveSample);
		// voice->SetPlayerVolume(FString(Identity->GetPlayerNickname(0)), 0);

		TArray<FVoiceChatDeviceInfo> outputDevices = voice->GetAvailableOutputDeviceInfos();

		for (int i = 0; i < outputDevices.Num(); ++i)
		{
			FStructDevice temp = FStructDevice();
			temp.Id = outputDevices[i].Id;
			temp.Name = outputDevices[i].DisplayName;
			finalDevices.Add(temp);
		}
		return finalDevices;
		// return voice->GetLoggedInPlayerName();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr NOT available..."));
		return finalDevices;
		// return FString("");
	}
}

TArray<FStructDevice> UEOSGameInstance::getInputDevices()
{
	TArray<FStructDevice> finalDevices = TArray<FStructDevice>();
	if (!OnlineSubsystem) return finalDevices;
	if (!bIsLogin) return finalDevices;
	UE_LOG(LogTemp, Warning, TEXT("getting OSS EOS..."));

	FOnlineSubsystemEOS* obj = GetOnlineSubsystemEos();
	UE_LOG(LogTemp, Warning, TEXT("GETTING IDENTITY INTERFACE..."));
	IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
	// UE_LOG(LogTemp, Warning, TEXT("GETTING USERID..."));
	// TSharedPtr<const FUniqueNetId> UserId = ;
	UE_LOG(LogTemp, Warning, TEXT("GETTING VOICE..."));
	IVoiceChatUser* voice = obj->GetVoiceChatUserInterface(*Identity->GetUniquePlayerId(0));
	// obj->voice
	if (voice)
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr line 394 available..."));
		UE_LOG(LogTemp, Warning, TEXT("the name is: %s"), *FString(Identity->GetPlayerNickname(0)));
		// voice->SetPlayerMuted(FString(Identity->GetPlayerNickname(0)), true);
		// voice->SetAudioInputVolume(FString(Identity->GetPlayerNickname(0)), 0.3);
		// voice->StartRecording(&UEOSGameInstance::onRecieveSample);
		// voice->SetPlayerVolume(FString(Identity->GetPlayerNickname(0)), 0);

		TArray<FVoiceChatDeviceInfo> outputDevices = voice->GetAvailableInputDeviceInfos();

		for (int i = 0; i < outputDevices.Num(); ++i)
		{
			FStructDevice temp = FStructDevice();
			temp.Id = outputDevices[i].Id;
			temp.Name = outputDevices[i].DisplayName;
			finalDevices.Add(temp);
		}
		return finalDevices;
		// return voice->GetLoggedInPlayerName();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr NOT available..."));
		return finalDevices;
		// return FString("");
	}
}

FString UEOSGameInstance::getPlayerNameVoiceEOS()
{
	if (!bIsLogin) return FString("");
	if (!IOnlineSubsystem::Get("EOS")) return FString("");
	UE_LOG(LogTemp, Warning, TEXT("getting OSS EOS..."));

	FOnlineSubsystemEOS* obj = GetOnlineSubsystemEos();
	UE_LOG(LogTemp, Warning, TEXT("GETTING IDENTITY INTERFACE..."));
	IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
	UE_LOG(LogTemp, Warning, TEXT("GETTING VOICE..."));
	IVoiceChatUser* voice = obj->GetVoiceChatUserInterface(*Identity->GetUniquePlayerId(0));
	if (voice)
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr line 394 available..."));
		UE_LOG(LogTemp, Warning, TEXT("the name is: %s"), *FString(Identity->GetPlayerNickname(0)));
		return voice->GetLoggedInPlayerName();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VoicePtr NOT available..."));
		return FString("");
	}
}

void UEOSGameInstance::FindSession()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Finding Session!"));

	if (OnlineSubsystem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Finding Session Online!"));
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			// Search->QuerySettings.SearchParams.Empty();
			SearchSetting = MakeShareable(new FOnlineSessionSearch());
			SearchSetting->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
			SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnSearchSessionComplete);
			SessionPtr->FindSessions(0, SearchSetting.ToSharedRef());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SessionPtr NOT available..."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("online subsystem NOT available..."));
	}
}

void UEOSGameInstance::DestroySession()
{
	if (OnlineSubsystem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Destroying Sessions!"));
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnDestroySessionComplete);
			SessionPtr->DestroySession(TestSessionName);
			// Search->QuerySettings.SearchParams.Empty();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SessionPtr NOT available..."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("online subsystem NOT available..."));
	}
}

void UEOSGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnDestroySessionCompleteDelegates(this);
			UE_LOG(LogTemp, Warning, TEXT("Session Success Destroyed!..."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SessionPtr NOT available..."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("online subsystem NOT available..."));
	}
}

void UEOSGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (OnlineSubsystem && Result == EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Success Join Session.."));
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			FString ConnectionInfo = FString();
			SessionPtr->GetResolvedConnectString(TestSessionName, ConnectionInfo);
			if (!ConnectionInfo.IsEmpty())
			{
				isOnLobby = true;
				if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
				{
					PC->ClientTravel(ConnectionInfo, ETravelType::TRAVEL_Absolute);
				}
			}
		}
	}
}

void UEOSGameInstance::OnSearchSessionComplete(bool bArg)
{
	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnFindSessionsCompleteDelegates(this);

			SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnJoinSessionComplete);
			for (int i = 0; i < this->SearchSetting->SearchResults.Num(); i++)
			{
				if (this->SearchSetting->SearchResults[i].Session.NumOpenPublicConnections != 10)
				{
					// UE_LOG(LogTemp, Warning, TEXT("FOUND SESSION WITH > 0 PLAYERS"));
					UE_LOG(LogTemp, Warning, TEXT("FOUND SESSION WITH > 0 PLAYERS"));
					// this->SearchSetting->SearchResults[i].Session.
					// SearchSetting->SearchResults[i].Session.
					// OnlineSubsystem->interface
					if (!SessionPtr->JoinSession(0, TestSessionName, this->SearchSetting->SearchResults[i]))
					{
						UE_LOG(LogTemp, Warning, TEXT("FAILED JOIN SESSION, creating session"));
						CreateSession();
					}
					// break;
					return;
				}
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("no session match found, creating session"));
		CreateSession();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("online subsystem NOT available..."));
	}
	return;
	UE_LOG(LogTemp, Warning, TEXT("Found session"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SEARCH SESSION COMPLETE"));
	if (bArg)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found session success"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SEARCH SESSION COMPLETE AND SUCCED"));
		// UE_LOG(LogTemp, Warning, TEXT("Found %d session"),);
		std::string successStr;
		UE_LOG(LogTemp, Warning, TEXT("Found session: %d"), SearchSetting->SearchResults.Num());

		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, successStr.c_str());
	}
}

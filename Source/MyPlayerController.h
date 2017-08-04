// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Online.h"
#include "OnlineFriendsInterface.h"
#include "MyPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFriendsChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFriendInviteReceivedUETopiaDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFriendInviteReceivedUETopiaDisplayUIDelegate, FString, SenderUserTitle, FString, SenderUserKeyId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecentPlayersChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartyJoinedUETopiaDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartyInviteReceivedUETopiaDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartyInviteReceivedUETopiaDisplayUIDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartyInviteResponseReceivedUETopiaDisplayUIDelegate, FString, SenderUserTitle, FString, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartyDataReceivedUETopiaDisplayUIDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChatChannelsChangedUETopiaDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMessageReceivedDisplayUIDelegate, FString, SenderUserKeyId, FString, ChatMessage, FString, chatRoomId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChatPrivateMessageReceivedDisplayUIDelegate, FString, SenderUserKeyId, FString, ChatMessage);

USTRUCT(BlueprintType)
struct FMyFriend {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		int32 playerID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString playerKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString playerTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool bIsOnline;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool bIsPlayingThisGame;
};

USTRUCT(BlueprintType)
struct FMyFriends {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FMyFriend> MyFriends;
};

USTRUCT(BlueprintType)
struct FMyRecentPlayer {

	GENERATED_USTRUCT_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString playerKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString playerTitle;
};

USTRUCT(BlueprintType)
struct FMyRecentPlayers {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FMyRecentPlayer> MyRecentPlayers;
};

USTRUCT(BlueprintType)
struct FMyPartyInvitation {

	GENERATED_USTRUCT_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString playerKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString partyTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString partyKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString senderUserTitle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString senderUserKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool bIsInvited;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		bool bIsInviteAccepted;
};

USTRUCT(BlueprintType)
struct FMyPartyInvitations {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FMyPartyInvitation> MyPartyInvitations;
};

USTRUCT(BlueprintType)
struct FMyChatChannel {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString chatChannelKeyId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		FString chatChannelTitle;
};

USTRUCT(BlueprintType)
struct FMyChatChannels {

	GENERATED_USTRUCT_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UETOPIA")
		TArray<FMyChatChannel> MyChatChannels;
};

/**
* Info associated with a party identifier
* THis is a duplicate that is also declared in the UEtopia plugin
* I could not get the include to work, so I'm putting this here for now
* TODO delete this and import it properly.
*/
class FOnlinePartyIdUEtopiaDup :
	public FOnlinePartyId
{
public:
	FOnlinePartyIdUEtopiaDup(const FString& InKeyId)
		: key_id(InKeyId)
	{
	}
	//~FOnlinePartyId() {};
	const uint8* GetBytes() const override;
	int32 GetSize() const override;
	bool IsValid() const override;
	FString ToString() const override;
	FString ToDebugString() const override;
private:
	const FString key_id;
};

/**
*
*/
UCLASS()
class COMP_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	//Constructor
	AMyPlayerController();

public:

	UFUNCTION(BlueprintCallable, Category = "UETOPIA", Server, Reliable, WithValidation)
		void RequestBeginPlay();

	FString PlayerUniqueNetId;

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void TravelPlayer(const FString& ServerUrl);

	// Friend Functions

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void InviteUserToFriends(const FString& UserKeyId);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void RejectFriendInvite(const FString& senderUserKeyId);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void AcceptFriendInvite(const FString& senderUserKeyId);

	// Party Related Functions

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void CreateParty(const FString& PartyTitle, const FString& TournamentKeyId, bool TournamentParty);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void RejectPartyInvite(const FString& senderUserKeyId);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void InviteUserToParty(const FString& PartyKeyId, const FString& UserKeyId);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void AcceptPartyInvite(const FString& senderUserKeyId);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void LeaveParty(const FString& PartyKeyId);

	// Chat related
	//UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void RefreshChatChannelList(const FUniqueNetId& LocalUserId);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void CreateChatChannel(const FString& ChatChannelTitle);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void JoinChatChannel(const FString& ChatChannelTitle);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void SendChatMessage(int32 CurrentChannelIndex, FString ChatMessage);

	UFUNCTION(BlueprintCallable, Category = "UETOPIA")
		void ExitChatChannel(int32 CurrentChannelIndex);

	// MATCHMAKER
	// Can't get these working in here.
	//UFUNCTION(BlueprintCallable, Category = "UETOPIA")
	//	bool StartMatchmaking(ULocalPlayer* PlayerOwner, FString MatchType);

	//UFUNCTION(BlueprintCallable, Category = "UETOPIA")
	//	bool CancelMatchmaking(ULocalPlayer* PlayerOwner);


	// This is the delegate to grab on to in the UI
	// When it fires, it signals that you should refresh the friends list
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
		FOnFriendsChangedDelegate OnFriendsChanged;

	// when this fires, the OSS has received a friend invite.
	//UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
	//	FOnFriendInviteReceivedUETopiaDelegate OnFriendInviteReceived;

	// when this fires, display the friend invitation UI
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
		FOnFriendInviteReceivedUETopiaDisplayUIDelegate OnFriendInviteReceivedDisplayUI;

	// When this fires, it signals that you should refresh the recent player's list
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
		FOnRecentPlayersChangedDelegate OnRecentPlayersChanged;
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
		FOnPartyJoinedUETopiaDelegate OnPartyJoined;
	// when this fires, the OSS has received a party invite.
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
	FOnPartyInviteReceivedUETopiaDelegate OnPartyInviteReceived;

	// when this fires, display the party invitation UI
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
	FOnPartyInviteReceivedUETopiaDisplayUIDelegate OnPartyInviteReceivedDisplayUI;

	// when this fires, display the party invitation response UI
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
	FOnPartyInviteResponseReceivedUETopiaDisplayUIDelegate OnPartyInviteResponseReceivedDisplayUI;

	// when this fires, update the party UI widget
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
	FOnPartyDataReceivedUETopiaDisplayUIDelegate OnPartyDataReceivedUETopiaDisplayUI;
	
	// when this fires, update the Chat Channel List
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
	FOnChatChannelsChangedUETopiaDelegate OnChatChannelsChangedUETopia;

	// when this fires, add a chat room message to the chat list
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
	FOnChatRoomMessageReceivedDisplayUIDelegate OnChatRoomMessageReceivedDisplayUIDelegate;

	// And this one is a private or system chat - not coming from a room.
	UPROPERTY(BlueprintAssignable, Category = "UETOPIA")
	FOnChatPrivateMessageReceivedDisplayUIDelegate OnChatPrivateMessageReceivedDisplayUIDelegate;

	// Handle to our delegates
	// This is bound into the online subsystem.

	FOnReadFriendsListComplete OnReadFriendsListCompleteDelegate;
	FOnQueryRecentPlayersComplete OnQueryRecentPlayersCompleteDelegate;
	FOnCreatePartyComplete OnCreatePartyCompleteDelegate;
	FOnSendPartyInvitationComplete OnSendPartyInvitationComplete;
	//FOnPartyJoined FOnPartyJoinedUETopiaDelegate;
	FOnPartyInviteReceived OnPartyInviteReceivedUEtopiaDelegate;
	//FOnPartyInviteResponseReceived OnPartyInviteResponseReceivedComplete;
	//FOnChatRoomMessageReceivedDisplayUIDelegate OnChatRoomMessageReceivedDisplayUIDelegate;

	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
	TArray<FMyFriend> MyCachedFriends;
	//FMyFriends MyCachedFriends;

	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
	FMyRecentPlayers MyCachedRecentPlayers;

	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
	TArray<FMyPartyInvitation> MyCachedPartyInvitations;

	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
	TArray<FMyFriend> MyCachedPartyMembers;

	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
	FMyChatChannels MyCachedChatChannels;

	// General Party Data

	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
		FString MyPartyTitle;
	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
		FString MyPartyKeyId;
	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
		int32 MyPartyMaxMemberCount;
	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
		int32 MyPartyCurrentMemberCount;
	UPROPERTY(BlueprintReadOnly, Category = "UETOPIA")
		bool IAmCaptain;


private:
	

	// This is fired by the Online subsystem after it polls the friend list.
	void OnReadFriendsComplete(int32 LocalPlayer, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);

	// This function is called by a delegate whenever the friends list changes.
	// The purpose of this is to emit a delegate which we can grab onto in the UI
	void OnFriendsChange();

	// THis is called when the OSS sees a friend request
	void OnFriendInviteReceivedComplete(const FUniqueNetId& LocalUserId, const FUniqueNetId& SenderId);

	// This is fired by the Online subsystem after it polls the recent players list.
	//(FOnQueryRecentPlayersComplete, const FUniqueNetId& /*UserId*/, const FString& /*Namespace*/, bool /*bWasSuccessful*/, const FString& /*Error*/);
	//UFUNCTION()
	void OnReadRecentPlayersComplete(const FUniqueNetId& UserId, const FString& ListName, bool bWasSuccessful, const FString& ErrorStr);

	// This function is called by a delegate whenever the RecentPlayers list changes.
	// The purpose of this is to emit a delegate which we can grab onto in the UI
	void OnRecentPlayersChange();

	// This is fired by the Online subsystem after it Creates a party.
	void OnCreatePartyComplete(const FUniqueNetId& UserId, const TSharedPtr<const FOnlinePartyId>&, const ECreatePartyCompletionResult);

	void OnPartyJoinedComplete(const FUniqueNetId& UserId, const FOnlinePartyId& PartyId);

	void OnPartyInviteReceivedComplete(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& SenderId);

	void OnPartyInviteResponseReceivedComplete(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const FUniqueNetId& SenderId, const EInvitationResponse Response);

	// This is fired by the online subsystem when it receives new party data
	// DECLARE_MULTICAST_DELEGATE_ThreeParams(F_PREFIX(OnPartyDataReceived), const FUniqueNetId& /*LocalUserId*/, const FOnlinePartyId& /*PartyId*/, const TSharedRef<FOnlinePartyData>& /*PartyData*/);

	void OnPartyDataReceivedComplete(const FUniqueNetId& LocalUserId, const FOnlinePartyId& PartyId, const TSharedRef<FOnlinePartyData>& PartyData);

	// THis is fired by the online subsystem when it receives notification that the user's chat room list has changed.
	// ADD THIS TO /Engine/Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineChatInterface.h
	// DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChatRoomListChanged, const FUniqueNetId& /*UserId*/, const FString& /*Error*/);
	void OnChatRoomListReadComplete(const FUniqueNetId& LocalUserId, const FString& ErrorStr);

	// This is fired by the online subsystem when it receives a new chat message coming from a room
	//DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChatRoomMessageReceived, const FUniqueNetId& /*UserId*/, const FChatRoomId& /*RoomId*/, const TSharedRef<FChatMessage>& /*ChatMessage*/);
	void OnChatRoomMessageReceivedComplete(const FUniqueNetId& SenderUserId, const FChatRoomId& RoomId, const TSharedRef<FChatMessage>& ChatMessage);

	// THis one is a private/system chat - not originating from a room
	//DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChatPrivateMessageReceived, const FUniqueNetId& /*UserId*/, const TSharedRef<FChatMessage>& /*ChatMessage*/);
	void OnChatPrivateMessageReceivedComplete(const FUniqueNetId& SenderUserId, const TSharedRef<FChatMessage>& ChatMessage);

	TArray<TSharedRef<IOnlinePartyJoinInfo>> PendingInvitesArray;
};

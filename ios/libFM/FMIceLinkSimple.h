//
// Title: IceLink Simple Extension for Cocoa
// Version: 2.9.7
// Copyright Frozen Mountain Software 2011+
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#if TARGET_OS_IPHONE
  #import <UIKit/UIKit.h>
#else
  #import <AppKit/AppKit.h>
#endif

@class FMIceLinkSimpleCandidateArgs;
@class FMIceLinkSimpleClient;
@class FMIceLinkSimpleMessage;
@class FMIceLinkSimpleOfferAnswerArgs;
@class FMIceLinkSimplePeerRegisterArgs;
@class FMIceLinkSimplePeerUnregisterArgs;
@class FMIceLinkSimpleRegisterArgs;
@class FMIceLinkSimpleRegisterCompleteArgs;
@class FMIceLinkSimpleRegisterFailureArgs;
@class FMIceLinkSimpleRegisterSuccessArgs;
@class FMIceLinkSimpleSendCandidateArgs;
@class FMIceLinkSimpleSendCandidateCompleteArgs;
@class FMIceLinkSimpleSendCandidateFailureArgs;
@class FMIceLinkSimpleSendCandidateSuccessArgs;
@class FMIceLinkSimpleSendOfferAnswerArgs;
@class FMIceLinkSimpleSendOfferAnswerCompleteArgs;
@class FMIceLinkSimpleSendOfferAnswerFailureArgs;
@class FMIceLinkSimpleSendOfferAnswerSuccessArgs;
@class FMIceLinkSimpleSerializer;
@class FMIceLinkSimpleTransfer;
@class FMIceLinkSimpleTransferCloseArgs;
@class FMIceLinkSimpleTransferCloseCompleteArgs;
@class FMIceLinkSimpleTransferConnectArgs;
@class FMIceLinkSimpleTransferConnectCompleteArgs;
@class FMIceLinkSimpleTransferConnectFailureArgs;
@class FMIceLinkSimpleTransferConnectSuccessArgs;
@class FMIceLinkSimpleTransferReceiveArgs;
@class FMIceLinkSimpleTransferReceiveCompleteArgs;
@class FMIceLinkSimpleTransferReceiveFailureArgs;
@class FMIceLinkSimpleTransferReceiveSuccessArgs;
@class FMIceLinkSimpleTransferSendArgs;
@class FMIceLinkSimpleTransferSendCompleteArgs;
@class FMIceLinkSimpleTransferSendFailureArgs;
@class FMIceLinkSimpleTransferSendSuccessArgs;
@class FMIceLinkSimpleUnregisterArgs;
@class FMIceLinkSimpleUnregisterCompleteArgs;

@class FMIceLinkCandidate;
@class FMIceLinkSimpleClient;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the candidate event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleCandidateArgs : FMDynamic 

/// <summary>
/// Gets the candidate sent by the peer.
/// </summary>
- (FMIceLinkCandidate*) candidate;
+ (FMIceLinkSimpleCandidateArgs*) candidateArgs;
/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
/// <summary>
/// Gets the client ID of the peer that caused this event.
/// </summary>
- (NSString*) peerClientId;
- (void) setCandidate:(FMIceLinkCandidate*)value;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class NSStringFMExtensions;
@class FMIceLinkSimpleRegisterArgs;
@class FMIceLinkSimpleTransfer;
@class FMIceLinkSimpleSendCandidateArgs;
@class FMIceLinkSimpleSendOfferAnswerArgs;
@class FMIceLinkSimpleUnregisterArgs;

/// <summary>
/// A Simple client that connects to a Simple server. Messages
/// can be transferred between Simple clients belonging to the
/// same group.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleClient : FMDynamic 

/// <summary>
/// Gets the current client ID.
/// </summary>
- (NSString*) clientId;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleClient" /> class using the default port (3479).
/// </summary>
/// <param name="serverIPAddress">The Simple server IP address.</param>
+ (FMIceLinkSimpleClient*) clientWithServerIPAddress:(NSString*)serverIPAddress;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleClient" /> class using the default port (3479).
/// </summary>
/// <param name="serverIPAddress">The Simple server IP address.</param>
/// <param name="groupName">The Simple group name.</param>
+ (FMIceLinkSimpleClient*) clientWithServerIPAddress:(NSString*)serverIPAddress groupName:(NSString*)groupName;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleClient" /> class.
/// </summary>
/// <param name="serverIPAddress">The Simple server IP address.</param>
/// <param name="serverPort">The Simple server port.</param>
+ (FMIceLinkSimpleClient*) clientWithServerIPAddress:(NSString*)serverIPAddress serverPort:(int)serverPort;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleClient" /> class.
/// </summary>
/// <param name="serverIPAddress">The Simple server IP address.</param>
/// <param name="serverPort">The Simple server port.</param>
/// <param name="groupName">The Simple group name.</param>
+ (FMIceLinkSimpleClient*) clientWithServerIPAddress:(NSString*)serverIPAddress serverPort:(int)serverPort groupName:(NSString*)groupName;
/// <summary>
/// Gets the Simple group name.
/// </summary>
- (NSString*) groupName;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleClient" /> class using the default port (3479).
/// </summary>
/// <param name="serverIPAddress">The Simple server IP address.</param>
- (id) initWithServerIPAddress:(NSString*)serverIPAddress;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleClient" /> class using the default port (3479).
/// </summary>
/// <param name="serverIPAddress">The Simple server IP address.</param>
/// <param name="groupName">The Simple group name.</param>
- (id) initWithServerIPAddress:(NSString*)serverIPAddress groupName:(NSString*)groupName;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleClient" /> class.
/// </summary>
/// <param name="serverIPAddress">The Simple server IP address.</param>
/// <param name="serverPort">The Simple server port.</param>
- (id) initWithServerIPAddress:(NSString*)serverIPAddress serverPort:(int)serverPort;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleClient" /> class.
/// </summary>
/// <param name="serverIPAddress">The Simple server IP address.</param>
/// <param name="serverPort">The Simple server port.</param>
/// <param name="groupName">The Simple group name.</param>
- (id) initWithServerIPAddress:(NSString*)serverIPAddress serverPort:(int)serverPort groupName:(NSString*)groupName;
/// <summary>
/// Registers the client with the Simple server.
/// </summary>
/// <param name="registerArgs">The register arguments.</param>
- (void) registerWithRegisterArgs:(FMIceLinkSimpleRegisterArgs*)registerArgs;
/// <summary>
/// Registers the client with the Simple server.
/// </summary>
/// <param name="registerArgs">The register arguments.</param>
- (void) registerWithArgs:(FMIceLinkSimpleRegisterArgs*)registerArgs;
/// <summary>
/// Sends a candidate to a peer through the Simple server to a specific client.
/// </summary>
/// <param name="sendCandidateArgs">The arguments.</param>
- (void) sendCandidateWithSendCandidateArgs:(FMIceLinkSimpleSendCandidateArgs*)sendCandidateArgs;
/// <summary>
/// Sends a candidate to a peer through the Simple server to a specific client.
/// </summary>
/// <param name="sendCandidateArgs">The arguments.</param>
- (void) sendCandidateWithArgs:(FMIceLinkSimpleSendCandidateArgs*)sendCandidateArgs;
/// <summary>
/// Sends an offer/answer to a peer through the Simple server to a specific client.
/// </summary>
/// <param name="sendOfferAnswerArgs">The arguments.</param>
- (void) sendOfferAnswerWithSendOfferAnswerArgs:(FMIceLinkSimpleSendOfferAnswerArgs*)sendOfferAnswerArgs;
/// <summary>
/// Sends an offer/answer to a peer through the Simple server to a specific client.
/// </summary>
/// <param name="sendOfferAnswerArgs">The arguments.</param>
- (void) sendOfferAnswerWithArgs:(FMIceLinkSimpleSendOfferAnswerArgs*)sendOfferAnswerArgs;
/// <summary>
/// Gets the Simple server IP address.
/// </summary>
- (NSString*) serverIPAddress;
/// <summary>
/// Gets the Simple server port.
/// </summary>
- (int) serverPort;
/// <summary>
/// Unregisters the client.
/// </summary>
- (void) unregister;
/// <summary>
/// Unregisters the client.
/// </summary>
/// <param name="unregisterArgs">The arguments.</param>
- (void) unregisterWithUnregisterArgs:(FMIceLinkSimpleUnregisterArgs*)unregisterArgs;
/// <summary>
/// Unregisters the client.
/// </summary>
/// <param name="unregisterArgs">The arguments.</param>
- (void) unregisterWithArgs:(FMIceLinkSimpleUnregisterArgs*)unregisterArgs;

@end


@class FMIceLinkCandidate;
@class NSStringFMExtensions;
@class FMIceLinkOfferAnswer;
@class NSMutableDataFMExtensions;

/// <summary>
/// The message class used by Simple clients.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleMessage : FMDynamic 

/// <summary>
/// Gets the candidate to send.
/// </summary>
- (FMIceLinkCandidate*) candidate;
/// <summary>
/// Gets the label used for candidate messages.
/// </summary>
+ (NSString*) candidateLabel;
/// <summary>
/// Gets the current client ID.
/// </summary>
- (NSString*) clientId;
/// <summary>
/// Converts a message from binary.
/// </summary>
/// <param name="messageBytes">The message bytes.</param>
/// <returns>The message.</returns>
+ (FMIceLinkSimpleMessage*) fromBytesWithMessageBytes:(NSMutableData*)messageBytes;
/// <summary>
/// Converts a message from JSON.
/// </summary>
/// <param name="messageJson">The message JSON.</param>
/// <returns>The message.</returns>
+ (FMIceLinkSimpleMessage*) fromJsonWithMessageJson:(NSString*)messageJson;
/// <summary>
/// Gets the group name to send.
/// </summary>
- (NSString*) groupName;
/// <summary>
/// Determines if the binary stream contains a complete message.
/// </summary>
/// <param name="bytes">The bytes.</param>
/// <param name="messageLength">The length of the contained message.</param>
/// <returns><c>true</c> if the bytes contain a message; otherwise, <c>false</c>.</returns>
+ (bool) hasMessageWithBytes:(NSMutableData*)bytes messageLength:(int*)messageLength;
- (id) init;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleMessage" /> class.
/// </summary>
/// <param name="label">The message label.</param>
/// <param name="clientId">The current client ID.</param>
- (id) initWithLabel:(NSString*)label clientId:(NSString*)clientId;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleMessage" /> class.
/// </summary>
/// <param name="label">The message label.</param>
/// <param name="clientId">The current client ID.</param>
/// <param name="peerClientId">The client ID of the peer.</param>
- (id) initWithLabel:(NSString*)label clientId:(NSString*)clientId peerClientId:(NSString*)peerClientId;
/// <summary>
/// Gets the message label.
/// </summary>
- (NSString*) label;
+ (FMIceLinkSimpleMessage*) message;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleMessage" /> class.
/// </summary>
/// <param name="label">The message label.</param>
/// <param name="clientId">The current client ID.</param>
+ (FMIceLinkSimpleMessage*) messageWithLabel:(NSString*)label clientId:(NSString*)clientId;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleMessage" /> class.
/// </summary>
/// <param name="label">The message label.</param>
/// <param name="clientId">The current client ID.</param>
/// <param name="peerClientId">The client ID of the peer.</param>
+ (FMIceLinkSimpleMessage*) messageWithLabel:(NSString*)label clientId:(NSString*)clientId peerClientId:(NSString*)peerClientId;
/// <summary>
/// Gets the offer/answer to send.
/// </summary>
- (FMIceLinkOfferAnswer*) offerAnswer;
/// <summary>
/// Gets the label used for offer/answer messages.
/// </summary>
+ (NSString*) offerAnswerLabel;
/// <summary>
/// Gets the client ID of the peer.
/// </summary>
- (NSString*) peerClientId;
/// <summary>
/// Gets the label used for registration messages.
/// </summary>
+ (NSString*) registerLabel;
/// <summary>
/// Sets the candidate to send.
/// </summary>
- (void) setCandidate:(FMIceLinkCandidate*)value;
- (void) setClientId:(NSString*)value;
/// <summary>
/// Sets the group name to send.
/// </summary>
- (void) setGroupName:(NSString*)value;
- (void) setLabel:(NSString*)value;
/// <summary>
/// Sets the offer/answer to send.
/// </summary>
- (void) setOfferAnswer:(FMIceLinkOfferAnswer*)value;
- (void) setPeerClientId:(NSString*)value;
/// <summary>
/// Converts this instance to binary.
/// </summary>
/// <returns>The message bytes.</returns>
- (NSMutableData*) toBytes;
/// <summary>
/// Converts a message to binary.
/// </summary>
/// <param name="message">The message.</param>
/// <returns>The message bytes.</returns>
+ (NSMutableData*) toBytesWithMessage:(FMIceLinkSimpleMessage*)message;
/// <summary>
/// Converts this instance to JSON.
/// </summary>
/// <returns>The message JSON.</returns>
- (NSString*) toJson;
/// <summary>
/// Converts a message to JSON.
/// </summary>
/// <param name="message">The message.</param>
/// <returns>The message JSON.</returns>
+ (NSString*) toJsonWithMessage:(FMIceLinkSimpleMessage*)message;
/// <summary>
/// Tries to get a message from a binary stream.
/// </summary>
/// <param name="bytes">The bytes.</param>
/// <param name="messageLength">The length of the contained message.</param>
/// <returns>The message, if one exists; otherwise, null.</returns>
+ (FMIceLinkSimpleMessage*) tryFromBytesWithBytes:(NSMutableData*)bytes messageLength:(int*)messageLength;
/// <summary>
/// Tries to get a message from a binary stream.
/// </summary>
/// <param name="bytes">The bytes.</param>
/// <param name="messageLength">The length of the contained message.</param>
/// <returns>The message, if one exists; otherwise, null.</returns>
+ (FMIceLinkSimpleMessage*) tryFromBytes:(NSMutableData*)bytes messageLength:(int*)messageLength;
/// <summary>
/// Gets the label used to unregister.
/// </summary>
+ (NSString*) unregisterLabel;

@end


@class FMIceLinkSimpleClient;
@class FMIceLinkOfferAnswer;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the offer/answer event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleOfferAnswerArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
/// <summary>
/// Gets the offer/answer sent by the peer.
/// </summary>
- (FMIceLinkOfferAnswer*) offerAnswer;
+ (FMIceLinkSimpleOfferAnswerArgs*) offerAnswerArgs;
/// <summary>
/// Gets the client ID of the peer that caused this event.
/// </summary>
- (NSString*) peerClientId;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setOfferAnswer:(FMIceLinkOfferAnswer*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkSimpleClient;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the peer register event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimplePeerRegisterArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
/// <summary>
/// Gets the client ID of the peer that caused this event.
/// </summary>
- (NSString*) peerClientId;
+ (FMIceLinkSimplePeerRegisterArgs*) peerRegisterArgs;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkSimpleClient;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the peer unregister event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimplePeerUnregisterArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
/// <summary>
/// Gets the client ID of the peer that caused this event.
/// </summary>
- (NSString*) peerClientId;
+ (FMIceLinkSimplePeerUnregisterArgs*) peerUnregisterArgs;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkSimpleRegisterSuccessArgs;
@class FMIceLinkSimpleRegisterFailureArgs;
@class FMIceLinkSimpleRegisterCompleteArgs;
@class FMIceLinkSimplePeerRegisterArgs;
@class FMIceLinkSimplePeerUnregisterArgs;
@class FMIceLinkSimpleOfferAnswerArgs;
@class FMIceLinkSimpleCandidateArgs;
@class FMCallback;

/// <summary>
/// Arguments for registering a client.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleRegisterArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the callback to execute when a candidate is received.
/// </summary>
- (FMCallback*) onCandidate;
/// <summary>
/// Gets the callback to execute after the success/failure event.
/// </summary>
- (FMCallback*) onComplete;
/// <summary>
/// Gets the callback to execute after a failed registration.
/// </summary>
- (FMCallback*) onFailure;
/// <summary>
/// Gets the callback to execute when an offer/answer is received.
/// </summary>
- (FMCallback*) onOfferAnswer;
/// <summary>
/// Gets the callback to execute when a peer registers.
/// </summary>
- (FMCallback*) onPeerRegister;
/// <summary>
/// Gets the callback to execute when a peer unregisters.
/// </summary>
- (FMCallback*) onPeerUnregister;
/// <summary>
/// Gets the callback to execute after a successful registration.
/// </summary>
- (FMCallback*) onSuccess;
+ (FMIceLinkSimpleRegisterArgs*) registerArgs;
/// <summary>
/// Sets the callback to execute when a candidate is received.
/// </summary>
- (void) setOnCandidate:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute when a candidate is received.
/// </summary>
- (void) setOnCandidateBlock:(void (^) (FMIceLinkSimpleCandidateArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute after the success/failure event.
/// </summary>
- (void) setOnComplete:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after the success/failure event.
/// </summary>
- (void) setOnCompleteBlock:(void (^) (FMIceLinkSimpleRegisterCompleteArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute after a failed registration.
/// </summary>
- (void) setOnFailure:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after a failed registration.
/// </summary>
- (void) setOnFailureBlock:(void (^) (FMIceLinkSimpleRegisterFailureArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute when an offer/answer is received.
/// </summary>
- (void) setOnOfferAnswer:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute when an offer/answer is received.
/// </summary>
- (void) setOnOfferAnswerBlock:(void (^) (FMIceLinkSimpleOfferAnswerArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute when a peer registers.
/// </summary>
- (void) setOnPeerRegister:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute when a peer registers.
/// </summary>
- (void) setOnPeerRegisterBlock:(void (^) (FMIceLinkSimplePeerRegisterArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute when a peer unregisters.
/// </summary>
- (void) setOnPeerUnregister:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute when a peer unregisters.
/// </summary>
- (void) setOnPeerUnregisterBlock:(void (^) (FMIceLinkSimplePeerUnregisterArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute after a successful registration.
/// </summary>
- (void) setOnSuccess:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after a successful registration.
/// </summary>
- (void) setOnSuccessBlock:(void (^) (FMIceLinkSimpleRegisterSuccessArgs*))valueBlock;

@end


@class FMIceLinkSimpleClient;

/// <summary>
/// Arguments for the register complete event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleRegisterCompleteArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
+ (FMIceLinkSimpleRegisterCompleteArgs*) registerCompleteArgs;
- (void) setClient:(FMIceLinkSimpleClient*)value;

@end


@class FMIceLinkSimpleClient;
@class NSExceptionFMExtensions;

/// <summary>
/// Arguments for the register failure event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleRegisterFailureArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
/// <summary>
/// Gets the exception that occurred.
/// </summary>
- (NSException*) exception;
- (id) init;
+ (FMIceLinkSimpleRegisterFailureArgs*) registerFailureArgs;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setException:(NSException*)value;

@end


@class FMIceLinkSimpleClient;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the register success event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleRegisterSuccessArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
/// <summary>
/// Gets the new client ID.
/// </summary>
- (NSString*) clientId;
- (id) init;
+ (FMIceLinkSimpleRegisterSuccessArgs*) registerSuccessArgs;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setClientId:(NSString*)value;

@end


@class FMIceLinkSimpleSendCandidateSuccessArgs;
@class FMIceLinkSimpleSendCandidateFailureArgs;
@class FMIceLinkSimpleSendCandidateCompleteArgs;
@class FMIceLinkCandidate;
@class FMCallback;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for sending a candidate from a client.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSendCandidateArgs : FMDynamic 

/// <summary>
/// Gets the candidate.
/// </summary>
- (FMIceLinkCandidate*) candidate;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleSendCandidateArgs" /> class.
/// </summary>
/// <param name="peerClientId">The client ID of the peer.</param>
/// <param name="candidate">The candidate.</param>
- (id) initWithPeerClientId:(NSString*)peerClientId candidate:(FMIceLinkCandidate*)candidate;
/// <summary>
/// Gets the callback to execute after the success/failure event.
/// </summary>
- (FMCallback*) onComplete;
/// <summary>
/// Gets the callback to execute after a failed send.
/// </summary>
- (FMCallback*) onFailure;
/// <summary>
/// Gets the callback to execute after a successful send.
/// </summary>
- (FMCallback*) onSuccess;
/// <summary>
/// Gets the client ID of the peer.
/// </summary>
- (NSString*) peerClientId;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleSendCandidateArgs" /> class.
/// </summary>
/// <param name="peerClientId">The client ID of the peer.</param>
/// <param name="candidate">The candidate.</param>
+ (FMIceLinkSimpleSendCandidateArgs*) sendCandidateArgsWithPeerClientId:(NSString*)peerClientId candidate:(FMIceLinkCandidate*)candidate;
/// <summary>
/// Sets the callback to execute after the success/failure event.
/// </summary>
- (void) setOnComplete:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after the success/failure event.
/// </summary>
- (void) setOnCompleteBlock:(void (^) (FMIceLinkSimpleSendCandidateCompleteArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute after a failed send.
/// </summary>
- (void) setOnFailure:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after a failed send.
/// </summary>
- (void) setOnFailureBlock:(void (^) (FMIceLinkSimpleSendCandidateFailureArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute after a successful send.
/// </summary>
- (void) setOnSuccess:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after a successful send.
/// </summary>
- (void) setOnSuccessBlock:(void (^) (FMIceLinkSimpleSendCandidateSuccessArgs*))valueBlock;

@end


@class FMIceLinkCandidate;
@class FMIceLinkSimpleClient;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the send-candidate complete event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSendCandidateCompleteArgs : FMDynamic 

/// <summary>
/// Gets the candidate.
/// </summary>
- (FMIceLinkCandidate*) candidate;
/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
/// <summary>
/// Gets the peer client ID.
/// </summary>
- (NSString*) peerClientId;
+ (FMIceLinkSimpleSendCandidateCompleteArgs*) sendCandidateCompleteArgs;
- (void) setCandidate:(FMIceLinkCandidate*)value;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkCandidate;
@class FMIceLinkSimpleClient;
@class NSExceptionFMExtensions;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the send-candidate failure event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSendCandidateFailureArgs : FMDynamic 

/// <summary>
/// Gets the candidate.
/// </summary>
- (FMIceLinkCandidate*) candidate;
/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
/// <summary>
/// Gets the exception that occurred.
/// </summary>
- (NSException*) exception;
- (id) init;
/// <summary>
/// Gets the peer client ID.
/// </summary>
- (NSString*) peerClientId;
+ (FMIceLinkSimpleSendCandidateFailureArgs*) sendCandidateFailureArgs;
- (void) setCandidate:(FMIceLinkCandidate*)value;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setException:(NSException*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkCandidate;
@class FMIceLinkSimpleClient;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the send-candidate success event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSendCandidateSuccessArgs : FMDynamic 

/// <summary>
/// Gets the candidate.
/// </summary>
- (FMIceLinkCandidate*) candidate;
/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
/// <summary>
/// Gets the peer client ID.
/// </summary>
- (NSString*) peerClientId;
+ (FMIceLinkSimpleSendCandidateSuccessArgs*) sendCandidateSuccessArgs;
- (void) setCandidate:(FMIceLinkCandidate*)value;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkSimpleSendOfferAnswerSuccessArgs;
@class FMIceLinkSimpleSendOfferAnswerFailureArgs;
@class FMIceLinkSimpleSendOfferAnswerCompleteArgs;
@class FMIceLinkOfferAnswer;
@class FMCallback;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for sending an offer/answer from a client.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSendOfferAnswerArgs : FMDynamic 

/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleSendCandidateArgs" /> class.
/// </summary>
/// <param name="peerClientId">The client ID of the peer.</param>
/// <param name="offerAnswer">The offer/answer.</param>
- (id) initWithPeerClientId:(NSString*)peerClientId offerAnswer:(FMIceLinkOfferAnswer*)offerAnswer;
/// <summary>
/// Gets the offer/answer.
/// </summary>
- (FMIceLinkOfferAnswer*) offerAnswer;
/// <summary>
/// Gets the callback to execute after the success/failure event.
/// </summary>
- (FMCallback*) onComplete;
/// <summary>
/// Gets the callback to execute after a failed send.
/// </summary>
- (FMCallback*) onFailure;
/// <summary>
/// Gets the callback to execute after a successful send.
/// </summary>
- (FMCallback*) onSuccess;
/// <summary>
/// Gets the client ID of the peer.
/// </summary>
- (NSString*) peerClientId;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleSendCandidateArgs" /> class.
/// </summary>
/// <param name="peerClientId">The client ID of the peer.</param>
/// <param name="offerAnswer">The offer/answer.</param>
+ (FMIceLinkSimpleSendOfferAnswerArgs*) sendOfferAnswerArgsWithPeerClientId:(NSString*)peerClientId offerAnswer:(FMIceLinkOfferAnswer*)offerAnswer;
/// <summary>
/// Sets the callback to execute after the success/failure event.
/// </summary>
- (void) setOnComplete:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after the success/failure event.
/// </summary>
- (void) setOnCompleteBlock:(void (^) (FMIceLinkSimpleSendOfferAnswerCompleteArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute after a failed send.
/// </summary>
- (void) setOnFailure:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after a failed send.
/// </summary>
- (void) setOnFailureBlock:(void (^) (FMIceLinkSimpleSendOfferAnswerFailureArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute after a successful send.
/// </summary>
- (void) setOnSuccess:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after a successful send.
/// </summary>
- (void) setOnSuccessBlock:(void (^) (FMIceLinkSimpleSendOfferAnswerSuccessArgs*))valueBlock;

@end


@class FMIceLinkSimpleClient;
@class FMIceLinkOfferAnswer;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the send-offer/answer complete event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSendOfferAnswerCompleteArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
/// <summary>
/// Gets the offer/answer.
/// </summary>
- (FMIceLinkOfferAnswer*) offerAnswer;
/// <summary>
/// Gets the peer client ID.
/// </summary>
- (NSString*) peerClientId;
+ (FMIceLinkSimpleSendOfferAnswerCompleteArgs*) sendOfferAnswerCompleteArgs;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setOfferAnswer:(FMIceLinkOfferAnswer*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkSimpleClient;
@class NSExceptionFMExtensions;
@class FMIceLinkOfferAnswer;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the send-offer/answer failure event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSendOfferAnswerFailureArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
/// <summary>
/// Gets the exception that occurred.
/// </summary>
- (NSException*) exception;
- (id) init;
/// <summary>
/// Gets the offer/answer.
/// </summary>
- (FMIceLinkOfferAnswer*) offerAnswer;
/// <summary>
/// Gets the peer client ID.
/// </summary>
- (NSString*) peerClientId;
+ (FMIceLinkSimpleSendOfferAnswerFailureArgs*) sendOfferAnswerFailureArgs;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setException:(NSException*)value;
- (void) setOfferAnswer:(FMIceLinkOfferAnswer*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkSimpleClient;
@class FMIceLinkOfferAnswer;
@class NSStringFMExtensions;

/// <summary>
/// Arguments for the send-offer/answer success event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSendOfferAnswerSuccessArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
- (id) init;
/// <summary>
/// Gets the offer/answer.
/// </summary>
- (FMIceLinkOfferAnswer*) offerAnswer;
/// <summary>
/// Gets the peer client ID.
/// </summary>
- (NSString*) peerClientId;
+ (FMIceLinkSimpleSendOfferAnswerSuccessArgs*) sendOfferAnswerSuccessArgs;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setOfferAnswer:(FMIceLinkOfferAnswer*)value;
- (void) setPeerClientId:(NSString*)value;

@end


@class FMIceLinkSimpleMessage;
@class NSStringFMExtensions;
@class NSMutableDictionaryFMExtensions;

#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleSerializer : NSObject 

+ (FMIceLinkSimpleMessage*) createSimpleMessage;
+ (void) deserializeSimpleMessageCallbackWithMessage:(FMIceLinkSimpleMessage*)message name:(NSString*)name valueJson:(NSString*)valueJson;
+ (FMIceLinkSimpleMessage*) deserializeSimpleMessageWithMessageJson:(NSString*)messageJson;
+ (FMIceLinkSimpleMessage*) deserializeSimpleMessageWithJson:(NSString*)messageJson;
- (id) init;
+ (FMIceLinkSimpleSerializer*) serializer;
+ (void) serializeSimpleMessageCallbackWithMessage:(FMIceLinkSimpleMessage*)message jsonObject:(NSMutableDictionary*)jsonObject;
+ (NSString*) serializeSimpleMessageWithMessage:(FMIceLinkSimpleMessage*)message;
+ (NSString*) serializeSimpleMessage:(FMIceLinkSimpleMessage*)message;

@end


@class FMByteCollection;
@class NSMutableArrayFMExtensions;
@class NSStringFMExtensions;
@class FMTcpSocket;
@class FMIceLinkSimpleTransferCloseArgs;
@class FMIceLinkSimpleTransferConnectArgs;
@class FMIceLinkSimpleTransferReceiveArgs;
@class FMIceLinkSimpleTransferSendArgs;

/// <summary>
/// A class that wraps a TCP socket to abstract away the
/// underlying details of transferring messages.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransfer : FMDynamic 

/// <summary>
/// Closes the underlying socket.
/// </summary>
- (void) close;
/// <summary>
/// Closes the underlying socket.
/// </summary>
- (void) closeWithCloseArgs:(FMIceLinkSimpleTransferCloseArgs*)closeArgs;
/// <summary>
/// Closes the underlying socket.
/// </summary>
- (void) closeWithArgs:(FMIceLinkSimpleTransferCloseArgs*)closeArgs;
/// <summary>
/// Connects the socket.
/// </summary>
/// <param name="connectArgs">The arguments.</param>
- (void) connectWithConnectArgs:(FMIceLinkSimpleTransferConnectArgs*)connectArgs;
/// <summary>
/// Connects the socket.
/// </summary>
/// <param name="connectArgs">The arguments.</param>
- (void) connectWithArgs:(FMIceLinkSimpleTransferConnectArgs*)connectArgs;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleTransfer" /> class.
/// </summary>
/// <param name="socket">The socket.</param>
/// <param name="serverIPAddress">The server IP address.</param>
/// <param name="serverPort">The server port.</param>
- (id) initWithSocket:(FMTcpSocket*)socket serverIPAddress:(NSString*)serverIPAddress serverPort:(int)serverPort;
/// <summary>
/// Receives a message.
/// </summary>
/// <param name="receiveArgs">The arguments.</param>
- (void) receiveWithReceiveArgs:(FMIceLinkSimpleTransferReceiveArgs*)receiveArgs;
/// <summary>
/// Receives a message.
/// </summary>
/// <param name="receiveArgs">The arguments.</param>
- (void) receiveWithArgs:(FMIceLinkSimpleTransferReceiveArgs*)receiveArgs;
/// <summary>
/// Sends a message.
/// </summary>
/// <param name="sendArgs">The arguments.</param>
- (void) sendWithSendArgs:(FMIceLinkSimpleTransferSendArgs*)sendArgs;
/// <summary>
/// Sends a message.
/// </summary>
/// <param name="sendArgs">The arguments.</param>
- (void) sendWithArgs:(FMIceLinkSimpleTransferSendArgs*)sendArgs;
/// <summary>
/// Gets the server IP address.
/// </summary>
- (NSString*) serverIPAddress;
/// <summary>
/// Gets pr sets the server port.
/// </summary>
- (int) serverPort;
/// <summary>
/// Gets the active TCP socket.
/// </summary>
- (FMTcpSocket*) socket;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleTransfer" /> class.
/// </summary>
/// <param name="socket">The socket.</param>
/// <param name="serverIPAddress">The server IP address.</param>
/// <param name="serverPort">The server port.</param>
+ (FMIceLinkSimpleTransfer*) transferWithSocket:(FMTcpSocket*)socket serverIPAddress:(NSString*)serverIPAddress serverPort:(int)serverPort;

@end


@class FMIceLinkSimpleTransferCloseCompleteArgs;
@class FMCallback;

/// <summary>
/// Arguments for closing a transfer.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferCloseArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the callback to execute after closing the socket.
/// </summary>
- (FMCallback*) onComplete;
/// <summary>
/// Sets the callback to execute after closing the socket.
/// </summary>
- (void) setOnComplete:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute after closing the socket.
/// </summary>
- (void) setOnCompleteBlock:(void (^) (FMIceLinkSimpleTransferCloseCompleteArgs*))valueBlock;
+ (FMIceLinkSimpleTransferCloseArgs*) transferCloseArgs;

@end


@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer close complete event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferCloseCompleteArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
+ (FMIceLinkSimpleTransferCloseCompleteArgs*) transferCloseCompleteArgs;

@end


@class FMIceLinkSimpleTransferConnectSuccessArgs;
@class FMIceLinkSimpleTransferConnectFailureArgs;
@class FMIceLinkSimpleTransferConnectCompleteArgs;
@class NSStringFMExtensions;
@class FMCallback;

/// <summary>
/// Arguments for connecting a transfer.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferConnectArgs : FMDynamic 

/// <summary>
/// Gets the group name.
/// </summary>
- (NSString*) groupName;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleTransferConnectArgs" /> class.
/// </summary>
/// <param name="groupName">The group name.</param>
- (id) initWithGroupName:(NSString*)groupName;
/// <summary>
/// Gets the callback to execute whether the connect succeeds or fails.
/// </summary>
- (FMCallback*) onComplete;
/// <summary>
/// Gets the callback to execute if the connect fails.
/// </summary>
- (FMCallback*) onFailure;
/// <summary>
/// Gets the callback to execute if the connect succeeds.
/// </summary>
- (FMCallback*) onSuccess;
/// <summary>
/// Sets the group name.
/// </summary>
- (void) setGroupName:(NSString*)value;
/// <summary>
/// Sets the callback to execute whether the connect succeeds or fails.
/// </summary>
- (void) setOnComplete:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute whether the connect succeeds or fails.
/// </summary>
- (void) setOnCompleteBlock:(void (^) (FMIceLinkSimpleTransferConnectCompleteArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute if the connect fails.
/// </summary>
- (void) setOnFailure:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute if the connect fails.
/// </summary>
- (void) setOnFailureBlock:(void (^) (FMIceLinkSimpleTransferConnectFailureArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute if the connect succeeds.
/// </summary>
- (void) setOnSuccess:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute if the connect succeeds.
/// </summary>
- (void) setOnSuccessBlock:(void (^) (FMIceLinkSimpleTransferConnectSuccessArgs*))valueBlock;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleTransferConnectArgs" /> class.
/// </summary>
/// <param name="groupName">The group name.</param>
+ (FMIceLinkSimpleTransferConnectArgs*) transferConnectArgsWithGroupName:(NSString*)groupName;

@end


@class NSStringFMExtensions;
@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer connect complete event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferConnectCompleteArgs : FMDynamic 

/// <summary>
/// Gets the group name.
/// </summary>
- (NSString*) groupName;
- (id) init;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setGroupName:(NSString*)value;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
+ (FMIceLinkSimpleTransferConnectCompleteArgs*) transferConnectCompleteArgs;

@end


@class NSExceptionFMExtensions;
@class NSStringFMExtensions;
@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer connect failure event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferConnectFailureArgs : FMDynamic 

/// <summary>
/// Gets the message.
/// </summary>
- (NSException*) exception;
/// <summary>
/// Gets the group name.
/// </summary>
- (NSString*) groupName;
- (id) init;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setException:(NSException*)value;
- (void) setGroupName:(NSString*)value;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
+ (FMIceLinkSimpleTransferConnectFailureArgs*) transferConnectFailureArgs;

@end


@class NSStringFMExtensions;
@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer connect success event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferConnectSuccessArgs : FMDynamic 

/// <summary>
/// Gets the group name.
/// </summary>
- (NSString*) groupName;
- (id) init;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setGroupName:(NSString*)value;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
+ (FMIceLinkSimpleTransferConnectSuccessArgs*) transferConnectSuccessArgs;

@end


@class FMIceLinkSimpleTransferReceiveSuccessArgs;
@class FMIceLinkSimpleTransferReceiveFailureArgs;
@class FMIceLinkSimpleTransferReceiveCompleteArgs;
@class FMCallback;

/// <summary>
/// Arguments for receiving a message.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferReceiveArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the callback to execute whether the receive succeeds or fails.
/// </summary>
- (FMCallback*) onComplete;
/// <summary>
/// Gets the callback to execute if the receive fails.
/// </summary>
- (FMCallback*) onFailure;
/// <summary>
/// Gets the callback to execute if the receive succeeds.
/// </summary>
- (FMCallback*) onSuccess;
/// <summary>
/// Sets the callback to execute whether the receive succeeds or fails.
/// </summary>
- (void) setOnComplete:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute whether the receive succeeds or fails.
/// </summary>
- (void) setOnCompleteBlock:(void (^) (FMIceLinkSimpleTransferReceiveCompleteArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute if the receive fails.
/// </summary>
- (void) setOnFailure:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute if the receive fails.
/// </summary>
- (void) setOnFailureBlock:(void (^) (FMIceLinkSimpleTransferReceiveFailureArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute if the receive succeeds.
/// </summary>
- (void) setOnSuccess:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute if the receive succeeds.
/// </summary>
- (void) setOnSuccessBlock:(void (^) (FMIceLinkSimpleTransferReceiveSuccessArgs*))valueBlock;
+ (FMIceLinkSimpleTransferReceiveArgs*) transferReceiveArgs;

@end


@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer receive complete event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferReceiveCompleteArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
+ (FMIceLinkSimpleTransferReceiveCompleteArgs*) transferReceiveCompleteArgs;

@end


@class NSExceptionFMExtensions;
@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer receive failure event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferReceiveFailureArgs : FMDynamic 

/// <summary>
/// Gets the message.
/// </summary>
- (NSException*) exception;
- (id) init;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setException:(NSException*)value;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
- (void) setTimedOut:(bool)value;
/// <summary>
/// Gets whether the receive timed out.
/// </summary>
- (bool) timedOut;
+ (FMIceLinkSimpleTransferReceiveFailureArgs*) transferReceiveFailureArgs;

@end


@class FMIceLinkSimpleMessage;
@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer receive success event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferReceiveSuccessArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the received message.
/// </summary>
- (FMIceLinkSimpleMessage*) message;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setMessage:(FMIceLinkSimpleMessage*)value;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
+ (FMIceLinkSimpleTransferReceiveSuccessArgs*) transferReceiveSuccessArgs;

@end


@class FMIceLinkSimpleTransferSendSuccessArgs;
@class FMIceLinkSimpleTransferSendFailureArgs;
@class FMIceLinkSimpleTransferSendCompleteArgs;
@class FMIceLinkSimpleMessage;
@class FMCallback;

/// <summary>
/// Arguments for sending a message.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferSendArgs : FMDynamic 

/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleTransferSendArgs" /> class.
/// </summary>
/// <param name="message">The message.</param>
- (id) initWithMessage:(FMIceLinkSimpleMessage*)message;
/// <summary>
/// Gets the message.
/// </summary>
- (FMIceLinkSimpleMessage*) message;
/// <summary>
/// Gets the callback to execute whether the send succeeds or fails.
/// </summary>
- (FMCallback*) onComplete;
/// <summary>
/// Gets the callback to execute if the send fails.
/// </summary>
- (FMCallback*) onFailure;
/// <summary>
/// Gets the callback to execute if the send succeeds.
/// </summary>
- (FMCallback*) onSuccess;
/// <summary>
/// Sets the callback to execute whether the send succeeds or fails.
/// </summary>
- (void) setOnComplete:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute whether the send succeeds or fails.
/// </summary>
- (void) setOnCompleteBlock:(void (^) (FMIceLinkSimpleTransferSendCompleteArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute if the send fails.
/// </summary>
- (void) setOnFailure:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute if the send fails.
/// </summary>
- (void) setOnFailureBlock:(void (^) (FMIceLinkSimpleTransferSendFailureArgs*))valueBlock;
/// <summary>
/// Sets the callback to execute if the send succeeds.
/// </summary>
- (void) setOnSuccess:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute if the send succeeds.
/// </summary>
- (void) setOnSuccessBlock:(void (^) (FMIceLinkSimpleTransferSendSuccessArgs*))valueBlock;
/// <summary>
/// Initializes a new instance of the <see cref="FMIceLinkSimpleTransferSendArgs" /> class.
/// </summary>
/// <param name="message">The message.</param>
+ (FMIceLinkSimpleTransferSendArgs*) transferSendArgsWithMessage:(FMIceLinkSimpleMessage*)message;

@end


@class FMIceLinkSimpleMessage;
@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer send complete event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferSendCompleteArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the message.
/// </summary>
- (FMIceLinkSimpleMessage*) message;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setMessage:(FMIceLinkSimpleMessage*)value;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
+ (FMIceLinkSimpleTransferSendCompleteArgs*) transferSendCompleteArgs;

@end


@class NSExceptionFMExtensions;
@class FMIceLinkSimpleMessage;
@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer send failure event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferSendFailureArgs : FMDynamic 

/// <summary>
/// Gets the message.
/// </summary>
- (NSException*) exception;
- (id) init;
/// <summary>
/// Gets the message.
/// </summary>
- (FMIceLinkSimpleMessage*) message;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setException:(NSException*)value;
- (void) setMessage:(FMIceLinkSimpleMessage*)value;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
- (void) setTimedOut:(bool)value;
/// <summary>
/// Gets whether the send timed out.
/// </summary>
- (bool) timedOut;
+ (FMIceLinkSimpleTransferSendFailureArgs*) transferSendFailureArgs;

@end


@class FMIceLinkSimpleMessage;
@class FMIceLinkSimpleTransfer;

/// <summary>
/// Arguments for the transfer send success event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleTransferSendSuccessArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the message.
/// </summary>
- (FMIceLinkSimpleMessage*) message;
/// <summary>
/// Gets the message transfer.
/// </summary>
- (FMIceLinkSimpleTransfer*) messageTransfer;
- (void) setMessage:(FMIceLinkSimpleMessage*)value;
- (void) setMessageTransfer:(FMIceLinkSimpleTransfer*)value;
+ (FMIceLinkSimpleTransferSendSuccessArgs*) transferSendSuccessArgs;

@end


@class FMIceLinkSimpleUnregisterCompleteArgs;
@class FMCallback;

/// <summary>
/// Arguments for unregistering a client.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleUnregisterArgs : FMDynamic 

- (id) init;
/// <summary>
/// Gets the callback to execute when the operation completes.
/// </summary>
- (FMCallback*) onComplete;
/// <summary>
/// Sets the callback to execute when the operation completes.
/// </summary>
- (void) setOnComplete:(FMCallback*)value;
/// <summary>
/// Sets the callback to execute when the operation completes.
/// </summary>
- (void) setOnCompleteBlock:(void (^) (FMIceLinkSimpleUnregisterCompleteArgs*))valueBlock;
+ (FMIceLinkSimpleUnregisterArgs*) unregisterArgs;

@end


@class FMIceLinkSimpleClient;
@class NSExceptionFMExtensions;

/// <summary>
/// Arguments for the unregister complete event.
/// </summary>
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

@interface FMIceLinkSimpleUnregisterCompleteArgs : FMDynamic 

/// <summary>
/// Gets the current client.
/// </summary>
- (FMIceLinkSimpleClient*) client;
/// <summary>
/// Gets the exception, if one occurred.
/// </summary>
- (NSException*) exception;
- (id) init;
- (void) setClient:(FMIceLinkSimpleClient*)value;
- (void) setException:(NSException*)value;
+ (FMIceLinkSimpleUnregisterCompleteArgs*) unregisterCompleteArgs;

@end


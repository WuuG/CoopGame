// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef COOPGAME_SWeapon_generated_h
#error "SWeapon.generated.h already included, missing '#pragma once' in SWeapon.h"
#endif
#define COOPGAME_SWeapon_generated_h

#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_SPARSE_DATA
#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFire);


#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFire);


#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASWeapon(); \
	friend struct Z_Construct_UClass_ASWeapon_Statics; \
public: \
	DECLARE_CLASS(ASWeapon, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CoopGame"), NO_API) \
	DECLARE_SERIALIZER(ASWeapon)


#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_INCLASS \
private: \
	static void StaticRegisterNativesASWeapon(); \
	friend struct Z_Construct_UClass_ASWeapon_Statics; \
public: \
	DECLARE_CLASS(ASWeapon, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CoopGame"), NO_API) \
	DECLARE_SERIALIZER(ASWeapon)


#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASWeapon(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASWeapon) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASWeapon); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASWeapon); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASWeapon(ASWeapon&&); \
	NO_API ASWeapon(const ASWeapon&); \
public:


#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASWeapon(ASWeapon&&); \
	NO_API ASWeapon(const ASWeapon&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASWeapon); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASWeapon); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASWeapon)


#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SkeletaMeshComp() { return STRUCT_OFFSET(ASWeapon, SkeletaMeshComp); } \
	FORCEINLINE static uint32 __PPO__DamageType() { return STRUCT_OFFSET(ASWeapon, DamageType); } \
	FORCEINLINE static uint32 __PPO__MuzzleSocketName() { return STRUCT_OFFSET(ASWeapon, MuzzleSocketName); } \
	FORCEINLINE static uint32 __PPO__MuzzleEffect() { return STRUCT_OFFSET(ASWeapon, MuzzleEffect); } \
	FORCEINLINE static uint32 __PPO__DefalutImpactEffect() { return STRUCT_OFFSET(ASWeapon, DefalutImpactEffect); } \
	FORCEINLINE static uint32 __PPO__FleshImpactEffect() { return STRUCT_OFFSET(ASWeapon, FleshImpactEffect); } \
	FORCEINLINE static uint32 __PPO__TraceEffect() { return STRUCT_OFFSET(ASWeapon, TraceEffect); } \
	FORCEINLINE static uint32 __PPO__TraceTargetName() { return STRUCT_OFFSET(ASWeapon, TraceTargetName); } \
	FORCEINLINE static uint32 __PPO__FireCameraShake() { return STRUCT_OFFSET(ASWeapon, FireCameraShake); }


#define CoopGame_Source_CoopGame_Public_SWeapon_h_13_PROLOG
#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_PRIVATE_PROPERTY_OFFSET \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_SPARSE_DATA \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_RPC_WRAPPERS \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_INCLASS \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CoopGame_Source_CoopGame_Public_SWeapon_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_PRIVATE_PROPERTY_OFFSET \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_SPARSE_DATA \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_INCLASS_NO_PURE_DECLS \
	CoopGame_Source_CoopGame_Public_SWeapon_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COOPGAME_API UClass* StaticClass<class ASWeapon>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CoopGame_Source_CoopGame_Public_SWeapon_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

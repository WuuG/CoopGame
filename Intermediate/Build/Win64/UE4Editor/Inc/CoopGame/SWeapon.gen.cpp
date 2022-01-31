// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CoopGame/Public/SWeapon.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSWeapon() {}
// Cross Module References
	COOPGAME_API UClass* Z_Construct_UClass_ASWeapon_NoRegister();
	COOPGAME_API UClass* Z_Construct_UClass_ASWeapon();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_CoopGame();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_UDamageType_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UParticleSystem_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ASWeapon::execFire)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Fire();
		P_NATIVE_END;
	}
	void ASWeapon::StaticRegisterNativesASWeapon()
	{
		UClass* Class = ASWeapon::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Fire", &ASWeapon::execFire },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ASWeapon_Fire_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASWeapon_Fire_Statics::Function_MetaDataParams[] = {
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ASWeapon_Fire_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASWeapon, nullptr, "Fire", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ASWeapon_Fire_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ASWeapon_Fire_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ASWeapon_Fire()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ASWeapon_Fire_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ASWeapon_NoRegister()
	{
		return ASWeapon::StaticClass();
	}
	struct Z_Construct_UClass_ASWeapon_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SkeletaMeshComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SkeletaMeshComp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DamageType_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_DamageType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MuzzleSocketName_MetaData[];
#endif
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_MuzzleSocketName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MuzzleEffect_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MuzzleEffect;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ImpactEffect_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ImpactEffect;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TraceEffect_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_TraceEffect;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TraceTargetName_MetaData[];
#endif
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_TraceTargetName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASWeapon_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_CoopGame,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ASWeapon_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ASWeapon_Fire, "Fire" }, // 1285277653
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASWeapon_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SWeapon.h" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASWeapon_Statics::NewProp_SkeletaMeshComp_MetaData[] = {
		{ "Category", "Componnets" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASWeapon_Statics::NewProp_SkeletaMeshComp = { "SkeletaMeshComp", nullptr, (EPropertyFlags)0x0020080000090009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASWeapon, SkeletaMeshComp), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASWeapon_Statics::NewProp_SkeletaMeshComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::NewProp_SkeletaMeshComp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASWeapon_Statics::NewProp_DamageType_MetaData[] = {
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASWeapon_Statics::NewProp_DamageType = { "DamageType", nullptr, (EPropertyFlags)0x0024080000020015, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASWeapon, DamageType), Z_Construct_UClass_UDamageType_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_ASWeapon_Statics::NewProp_DamageType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::NewProp_DamageType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleSocketName_MetaData[] = {
		{ "Category", "Weapon" },
		{ "Comment", "// Effect\n" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
		{ "ToolTip", "Effect" },
	};
#endif
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleSocketName = { "MuzzleSocketName", nullptr, (EPropertyFlags)0x0020080000020015, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASWeapon, MuzzleSocketName), METADATA_PARAMS(Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleSocketName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleSocketName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleEffect_MetaData[] = {
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleEffect = { "MuzzleEffect", nullptr, (EPropertyFlags)0x0020080000010015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASWeapon, MuzzleEffect), Z_Construct_UClass_UParticleSystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleEffect_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleEffect_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASWeapon_Statics::NewProp_ImpactEffect_MetaData[] = {
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASWeapon_Statics::NewProp_ImpactEffect = { "ImpactEffect", nullptr, (EPropertyFlags)0x0020080000010015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASWeapon, ImpactEffect), Z_Construct_UClass_UParticleSystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASWeapon_Statics::NewProp_ImpactEffect_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::NewProp_ImpactEffect_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceEffect_MetaData[] = {
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceEffect = { "TraceEffect", nullptr, (EPropertyFlags)0x0020080000010015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASWeapon, TraceEffect), Z_Construct_UClass_UParticleSystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceEffect_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceEffect_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceTargetName_MetaData[] = {
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "Public/SWeapon.h" },
	};
#endif
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceTargetName = { "TraceTargetName", nullptr, (EPropertyFlags)0x0020080000020015, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASWeapon, TraceTargetName), METADATA_PARAMS(Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceTargetName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceTargetName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASWeapon_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASWeapon_Statics::NewProp_SkeletaMeshComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASWeapon_Statics::NewProp_DamageType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleSocketName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASWeapon_Statics::NewProp_MuzzleEffect,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASWeapon_Statics::NewProp_ImpactEffect,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceEffect,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASWeapon_Statics::NewProp_TraceTargetName,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASWeapon_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASWeapon>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASWeapon_Statics::ClassParams = {
		&ASWeapon::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ASWeapon_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASWeapon_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASWeapon_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASWeapon()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASWeapon_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASWeapon, 3396349805);
	template<> COOPGAME_API UClass* StaticClass<ASWeapon>()
	{
		return ASWeapon::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASWeapon(Z_Construct_UClass_ASWeapon, &ASWeapon::StaticClass, TEXT("/Script/CoopGame"), TEXT("ASWeapon"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASWeapon);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

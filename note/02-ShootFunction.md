# 一些射击游戏相关功能
## 变焦推进
``` cpp
bool bWantToZoom;
UPROPERTY(...)
float ZoomedFov;
float DefalutFov; //beginPlay setting
UPROPRTY(, meta=(ClamMin = 0, ClampMax = 100))
float ZoomInterpSpeed

void BeginZoom;
void EndZoom;
```
``` cpp
ZoomedFov = 50;


// BeginPlay:
DefalutFov = CameraComp->FiledOfView 
// Tick:
// float CurrentFov = bWantsToZoom ? ZoomedFOV : DefalultFOV;
float TargetFov = bWantsToZoom ? ZoomedFOV : DefalultFOV;
float NewFov = FMath::FInterpTo(CameraComp->FiledOfView, TargetFOV, DeltaTime, ZoomInterpSpeed)

CameraComp->SetFieldOfView() // 默认为90


// Other
BindAction("Zoom",...);
```
### Debug Console Variables
Seapon.cpp
``` cpp
static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(TEXT("COOP.DebugWeapons"), DebugWeaponDreawing, TEXT("Draw Debug Lines for Weapons"),ECVF_Cheat);

if(DEbugWeaponDreawing > 0)
{
    DreaDebugLine();
}
```
### Polish Code
在SWeapon.cpp中
+ 删除BeginPlay
+ 删除Tick
+ 创建PlayEffect函数,进行迁移

SCharacter.cpp
``` cpp
Sweapon* CurrentWeapon;
void Fire();
```
将生成武器的方式，使用C++实现
``` cpp
SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandingMethod::AlwaysSpawn;
CurrentWeapon =	GetWorld()->SpawnActor<ASWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

CurrentWeapon->SetOwner(this);
CurrentWeapon->AttachToComponent(GetMesh , FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponSocket");
```
> 记得修改Fire的访问权限 public
### 武器镜头震动
``` cpp
UPEOPERTY(EditDefalutOnly, Category="Weapon")
// UCameraShakeBase UMatineeCameraShake 
TSubClassOf<UCameraShake> FireCameraShake;
```
``` cpp
 AplayerController* PC = Cast<APlayerController>(MyOwner->GetController());
 if(PC)
 {
     // PC->ClineStartCameraShake  
     PC->ClientPlayCameraShake();
 }
```
创建MatineeCamearaShake为基类的CamShake_RifleFire
+ 设置Duration
+ 设置Rot Oscillation(旋转振荡)
### Custom surface types
+ proejctSetting Physical Surface
+ 设置FleshDefalut和FleshVulnerable, 可以表示弱点被打到
+ 创建 Core/Physicals 文件夹并创建 PhysMat_FleshDefalut PhyMat_FleshVulnerable(Physical materials), 并设置对应的surface type
+ 打开人物中的Phsical Material, 给部位设置Phys Matrrail Override
### 不同位置被击中显示不同的Effect
``` cpp
UPROPERTY(...)
UParticleSystem* FleshImpactEffect;
```
``` cpp
#include "CoopGame.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
QueryParams.bRetrunPhysicalMaterial = true;

// 需要注意的是在2.6.2版本中，需要在build.cs中添加PhysicsCore才可以进行编译，因为不知道EPhysicalSurface其无法知道是什么类型
EPhysicalSurface SurfaceType =  UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get()) // WeakPtr

UParticleSystem* selectedEffect = nullpth;
switch(SurfaceType)
{
    case SurfaceType1:
        // selectEffect = FleshImpactEffect
        // break
    case SurfaceType2:
        selectEffect = FleshImpactEffect
        break
    default:
        break;
}
```
+ 在CoopGame.h中 重新定义一下SurfaceType, 并在Weapon.cpp中引入头文件
``` cpp
#define SURFACE_FLESHFALUT SurfaceType1
#define SURFACE_FLESHVULNERABLE SurfaceType1
```
+ 学会如何使用断点调试
### Custom collision channel
+ 修改LineTraceSingleChannel；
+ 同理，在project Setting的TraceChannels中新建Channel Weapon, 第一条就对应ECC_GameTraceChannel1
``` cpp
#define COLLISION_WEAPON ECC_GameTraceChannel1;
```
> 注意，如果有胶囊体的化，Pawn默认情况下会将自定义通道block掉，因此部分身体无法与Mesh Collision， 所以会出现错误的SurfaceType（其实就是胶囊体的SurfaceType）. 因此需要将胶囊体对自定义的block关闭(在这里是Weapon Channel)
### 添加爆头特效
``` cpp
float BaseDamage;
```
``` cpp
if(SurfaceType == SURFACE_FLESHVUNLNERABLE)
{
    ActualDamge *= ..;
}
```
蓝图功能DrawDebugString
### Automatic Fire
+ StartFire(),StopFire()
+ 将Fire改为Protect，并且不可被蓝图调用
``` cpp
#include "TimerManager.h"

FTimerHandle TimerHandle_TimeBetweenShots;
float LastFireTime;

/* RPM  -- Bullets per minute fired by weapon */
UPROPERTY()
float RateOfFire = 500;

/*
* Derived from RateOfFire
*/
float TimeBetweenShots;
```
``` cpp
Beginplay()
{
    SUper;
    TimeBetweenShots = 60 / RateOfFire;
}

Fire()
{
    // ...
    LastFireTime = GetWorld()->TimeSeconds;
}

float FirstDelay = FMath::Max(LastFireTime + TimeBetweentShots - GetWorld()->TimeSeconds, 0.0f);
GetWorldTimerManager().SetTimer(TimerHandler...)

LastFireTime = GetWorld()->TimeSeconds;

```
### 自己实现一个关于武器的功能
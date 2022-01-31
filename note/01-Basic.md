# 创建玩家角色
## Character
+ 创建SCharacter
### 添加角色移动绑定
+ PlayerInputComponenet->BindAxis("MoveForward", this, %AScharacter::MoveForward)
+ 添加MoveForward(float Value)函数
+ AddMovementInput(GetActorFOwardVector() * Value);
+ 同上添加MoveRight函数
+ 在Project的input中，添加Axis Mapping
+ 添加BP_PlayerPawn
### 添加视角移动
+ 类似角色移动绑定,绑定&ASCharacter::AddControllerPitchInput内置函数
+ 给Turn绑定&ASCharacter::AddControllerYawInput内置函数
### 添加第三人称视角摄像机
+ UCameraComponent 组件, VisibleAnywhere, BlueprintReadOnly
+ 头文件 Camera/CameraComponent.h
+ CamraComp->bUsePawnControlRotation = true, 设置摄像头随着人物视角移动进行旋转(但此时只能在水平方向上进行旋转 Yaw), 通过~ show Collision, 可以在play Mode下查看到碰撞，需要注意的是要打全，他的默认提示不会自己填写上去的
+ 添加SPrintArmComponent， 为了让摄像头能够在竖直方向上(Pitch)随着视角移动
+ 将其添加到RootComponent上
+ Ctrl+shift+O 可以查看头文件位置
+ 使用 SprintArmComp->bUsePawnControlRotation = true, 删除之前Camera设置的该项
## 添加新手动画
+ 在Epic商城中添加初学者动作包，并将包含的Mesh添加到人物之上。
### 添加蹲伏动作
+ 创建BeginCrouch和EndCrouch两个函数
+ 利用引擎内置的Crounch和Uncrounch函数来实现蹲伏
+ 通过BindAction("Counch", IE_Pressed, ...)来进行绑定
+ 同理使用BindAction("Counch", IE_Released, ...)绑定取消蹲伏
+ 为了使用蹲伏，需要设置 GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true
+ 添加ActionMap。 将Crouch绑定按键
### 设置动画效果
+ 基本上使用自带的动作蓝图
+  添加跳跃动作:类似添加蹲伏动作
## 武器
### 创建武器类
+ 添加USkeletalMeshComponent 骨骼网格体组件
+ 创建BP_Rifle, 并选择骨骼网格体
+ 在人物蓝图中，使用Spawn actor from class在BeginPlay时生成BP_Rifle 
+ 将获取的实例AttchToComponent
+ 在人物的Skeleton中添加插槽，用以确定武器位置
### 添加武器模型及相关逻辑代码
+ Fire函数

``` cpp
UFUNCTION(BlueprintCallable，Category="Weapon")
void Fire();
```
``` cpp
#include "DrawDebugHelpers.h"

AActor* MyOwner = GetOwner();

FVector EyeLotation;
FRotator EyeRotation;
MyOwner->GetActorEyeViewPoint(EyeLotation, FRotation EyeRotation);

FCollisionQueryParams QueryParams;
QueryParams.AddIgnoredActor(MyOwner);
QueryParams.AddIgnoredActor(this);
QUeryParams.bTraceComplex = true;

FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);
FHitResult Hit;
if(GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams);)
{
    // 只有该轨迹被阻挡时，进行后续处理
}
DrawDebugLine(...);
```
### 修改武器Fire时的起始位置
+ 通过重写 GetPawnViewLocation()函数进行修改位置
### 实现命中逻辑
``` cpp
UPROPERTY(EditDefaultOnly, BlueprintReadOnly, Category="Weapon")
TsubClassOf<UDamageType> DamageType;
```
``` cpp
#include "Kismet/GameplayStatics"

FVector ShotDirection = EyeRotation.Vector();

AActor* HitActor = Hit.GetActor();
UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DamageType);
```
### 创建测试假人
+ BP_TargetDummy
+ 添加骨骼网格体， 并设置Event PointDamage
+ 开启碰撞
### 添加武器枪口FX
``` cpp
UPROPERTY(VisibleDefaultOnly, BlueprintReadOnly, Category="Weapon")
FName MuzzleSocketName;

UPROPERTY(VisibleDefaultOnly, BlueprintReadOnly, Category="Weapon")
UPaticleSystem* MuzzleEffect

UPROPERTY(VisibleDefaultOnly, BlueprintReadOnly, Category="Weapon")
UPaticleSystem* ImpactEffect
```
``` cpp
#include "Paticle/PaticleSystem.h"

MuzzleSocketName = "MuzzleSocket";

if(ImpactEffect)
{
    UGameplayStatics::SpawnEmitterAtLocation(Getworld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

if(MuzzleEffect)
{
    UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
}
```
### 添加光束粒子发射器
+ 可以将P_SmokeTrail直接拖入视口中，修改参数可以清楚的看到该效果
``` cpp
UPROPERTY(VisibleDefaultOnly, BlueprintReadOnly, Category="Weapon")
UPaticleSystem* TraceEffect

UPROPERTY(VisibleDefaultOnly, BlueprintReadOnly, Category="Weapon")
FName TracerTargetName;
```
``` cpp
#include "Paticles/ParticleSystemComponent.h"

TracerTArgetName = "Target";


FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
UPaticleSystemComponent* TraceComp =  UGameplayStatics::SpawnEmitterAtLocation(Getworld(),TraceEffect,MuzzleLocation);
if(TraceComp)
{
    TracerComp->SetVectorParameter(TracerTargetName, TraceEndPoint);
}
```
### 添加Crosshair
+ 创建WBP_CrossHair
+ 添加Image
+ 在BP_PlayerPawn中添加该UI
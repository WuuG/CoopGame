# Basic UI
## 创建
+ 创建STrackerBot类 : Pawn
+ Static Mesh
+ 创建BP_TracerBot
+ 创建Meshes文件夹，添  加ArcadeEditorSphere
+ 创建一个M_TrackerBot, 添加一个基础颜色
+ 添加Mesh Nav bounds Volume
## STrakerBot
### 测试移动效果
+ 添加Floating Pawn Move 组件
+ 在蓝图中 BeginPlay中添加移动逻辑
### cpp
``` cpp
FVector GetNextPathPoint();

FVector NextPathPoint;

UPROPERTY(..)
float MovementForce; 
UPROPERTY(..)
float bUseVelocityChange;
UPROPERTY(..)
float RequiredDistanceOfTarget;
```
``` cpp
#include "Kismat/UGameplayStatics.h"
#include "AI/Navigation/NavagationSystem.h'
#include "AI/Navigation/NavagationPath.h'
#include "GameFramWork/Character.h"

// Construct
MeshComp->SetCanEverAffectNavigation(false);
MeshComp->SetSimulatePhysics(true);

MovementForce = 1000;
bUseVelocityChange = false;
RequiredDistanceOfTarget = 100.0;
// BeginPlay
NextPathPoint GetNextPath();

// GetNextPathPoint
ACharacter* PlayerPawn =  UGAmeplayStatis::GetPlayerCharacter(this, 0);
UNavigationPath* NavPath = UNavigationSystem::FindPathToActorSynchronously(this, GetActorLocaiton(), PlayerPawn);

if(NavPath->PathPoints.Num() > 1)
{
    return NavPath->PathPoint[1];
}
return GetActorLocation();
// Tick

float DistanceToTarget = (GetActorLocaiton() - NextPathPoint).Size();
// if(!GetActorLocation().Equals(NextPathPoint))  // 不适用Equal，Tick可能错过这个条件
if(DistanceToTarget <= RequiredDistanceOfTarget)
{
    NextPathPoint = GetNextPathPoint();
}else 
{
    FVector ForceDirection = NextPathPonit - GetActorlocation();
    ForceDirection.Normalizaiton();
    ForceDirection *= MovementForce;

    MeshComp->AddForce();
    DrawDebugDirectionalArrow();
}
DrawDebugSphere()
```
### 添加生命组件
``` cpp
UPEORPERTY(VisibleAnyWhere, Category="Components")
USHealthComponnet* HealthComp;

UFUNCTION()
void HandleTakeDamge(...);

// 收到伤害后的闪烁动态柴智
UMaterialInstanceDynamic* MatInst;
```
``` cpp
// Constructe
HealthComp = Creat...;
// BeginPlay
HealthComp->OnHealthChanged.AddDynamic();
// HandleTakeDamage()
if(MathInst == nullptr)
{
    // 这里获得的MathInst还是有可能返回nullptr
    MathInst = MeshComp->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComp->GetMeterial(0));
}
if(MathInst)
{
MatInst->SetScalarParameterValue("LastDamageTaken", GetWorld()->TimeSeconds)
}

UE_LOG(LogTemp, Log, TEXT("Health %s of %s"), *FString::SanitizeFloat(Health), *GetName);
```
> 在蓝图中添加闪烁效果
### 添加爆炸
``` cpp
ParticleSystem* ExplisionEffect;
bool bExploded;
float ExplosionRadius;
float ExplosionDamage;

void SelfDestruct();

USphereComponent* SphereComp;
FTimerHandle TimerHandler_SelfDamage;
bool bStartedSelfDestruction;
void DamgeSelf();
public:
virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
```
``` cpp
// Constructer
SphereComp = ...;
SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
SphereComp->SetCollisionResponseToAllChanels(ECR_Ignore);
SphereComp->SetCollisionResponseToChanel(ECC_Pawn, ECR_Overlap);
SphereComp->SetSphereRadius();
SphereComp->SetUpAttachMent();

bStartedSelfDestruction = false;
// HandleTakeDamage
if(Health <= 0.0f)
{
    SelfDestruct();
}

// SelfDestruce
if(bExploded)
{
    return;
}
bExploded = true;
UGameplayStatics::SpawnEmitterAtLocation(...);

TArray<AActor*> IgnoredActors;
IgnoredActors.Add(this);
UGameplayStatics::ApplyRadialDamage();
DrawDebugSphere()

Destory();
//  DamageSelf
UGameplayStatics::ApplyDamage(this, 20, , , nullptr);

// NotifyOverlapBeginOverlap
if(bStartedSelfDestruction)
{
    return;
}
ASCharacter PlayerPawn = Cast<ASCharacter>(OtherActor);
if(PlayerPawn)
{
    GetWorldTimerManage().SetTimer(TimerHandle_SelfDamage, this ,&ASTrackerBot::DamageSelft, 0.5f, true, 0.0f);
    bStartedSelfDestruction  = true;
}
```
### 添加声效
+ 新建TrackerBot，将相关文件移动进去
``` cpp
UPROPERTY()
USoundCue* SelfDestructSound;
UPROPERTY()
USoundCue* ExplodeSound;

UPROPERTY()
float SelfDamageInterval; // 用以定时器时间
```
``` cpp
#include "Sound/SoundCue.h"

// SelfDestruct
UGamePlayStatics::PlaySoundAtLocation(this, ExplodeSound, GetActorlocation());

// NotifyActorBeginOverlap
UGameplayStatics::SpawnSoundAttached(SelfDestructSound, RootComponent);
```
> 设置Sound cue并通过Sounds/SoundAttenuatio 来创建音量衰减,通过蓝图创建滚动声效
### 实现多人
+ 多人模式下客户端没有Nav Mesh, 所以会崩溃
+ 将爆炸效果留在本地，其他在服务端上执行
``` cpp
UPROPERTY(..., ReplicatedUsing=OnRep_Health)
float Health;

void OnRep_Health(float oldHealth)
```
``` cpp
// SelfDestruct
MeshComp->SetVisiblility(false, true);
MeshComp->SetCollisionEnabled(...);

GetIifeSPan(2.0f);
```
# 多人模式
## 创建GameMode
+ 创建BP_GameMode
+ 设置好player pawn和Game mode
+ 修复Fire(), beginplay会在客户端和服务端都执行
## Replicated Weapon
ASChracter
```cpp
UPROEPRTY(Replicated)
ASWeapon* CurrentWeapon;
```
``` cpp
#include "Net/UnrealNetwork.h"
// Beginplay
if(Role == Role_Authority)
{
 // 武器的生成,让其在服务器上生成
}

// 通过GetLifetimeReplicatedProps 来对CurrentWeapon复制的规则进行解释 
{
    Super::...;
    // 为任何相连的客户端进行复制
    DOREPLIFETIME(ASchareacter, CurrentWeapon);
}
```
ASWeapon
``` cpp
// ASWeapon
SetReplicates(true);
```
Replicated function来使得客户端和服务端的武器能够进行同步开火
``` cpp
UFUNCTION(Server, Reliable, WithValidation)
void ServerFire();
```
``` cpp
// Fire()
if(Role < ROLE_Authority) // GetLocalRole
{
    ServerFire();
    return;
}
// ServerFire()
ServerFire_Implementaion()
{
    // 注意这里的Fire是主机在执行的
    Fire();
}
ServerFire_Validate()
{
    // 这里可以进行作弊检查, 通过返回false可以断开连接
    return true;
}
```
> 通过isLocalController来对add Viewport进行限制
 
### 客户端武器轨迹同步
客户端需要同步效果，但不需要计算伤害
``` cpp
#include "Net/UnrealNetwork.h"

// Contains infomation of a single hitscan weapon line trace
USTRCT()
struct FhitScanTrace
{
    GENERATED_BODY()

public:
    UPEORPETY()
    // FVector_NetQuantizeNormal TraceFrom;
    TEnumAsByte<EPhysicalSurface> SurfaceType; // 不可以直接传入结构，需要以字节传入才可以在网络端进行传播

    // 该类型的矢量不那么精确，但是网络传输的数据量更小
    UPROERPTY()
    FVector_NetQuantize TraceEnd;
}

    // 该数据更新时触发函数 OnRep_HitScanTrace
    UPROPERTY(ReplicatedUsing=OnRep_HitSCanTrace)
    FHitScanTrace HitScanTrace;

    UFUNCtion()
    void OnRep_HitSCanTrace();
```
``` cpp
// ASWeapon
// 因为Epic网络更新的频率和Actor相关，所以默认情况下会有延迟，可以通过以下属性进行修改
NetUpdateFrequncy = 66.0f;
MinNetUpdateFrequency = 33.0f
// Fire
{
    // ...
    if(Role == Role_Authority)
    {
        HitScanTrace.TraceTo = TracerEndPoint;
    }
}
// OnRep_HitSCanTrace()

{
    PlayFireEffect(HitScanTrace.TraceTO);
    playImpacEffect();
}

// 创建以下函数，表示属性的同步方式
GetLifetimeReplicatedProps()
{
    DOREPLIFETIME_CONDITION(ASWEAPON, HitScanTrace, COND_SkipOwner):
}
```
> 这个修改完，在服务器射击同一位置时客户端无法触发OnRep_HitScanTrace()函数
### 复制生命值组件
``` cpp
UPROPERTY(Replicated,...)
float Health;
```
``` cpp
#include "Net/UnrealNetWork/h"
// USHealthComponent
SetIsReplicated(true);
// OnHealthChanged
if(GetOwnerRole() == ...)
{
 // 声明值发生改变
}

GetLifetimeReplicatedProps()
{

}
```
> replicated bDied 来设置死亡同步
## 挑战： 让爆炸桶能够适应多人模式
1. Replicate movement
2. play visual effect

+ 物理模拟的数据量较大，存在延迟
> 设置物体的 Static Mesh Replicate Movement 为true能够来实现复制效果
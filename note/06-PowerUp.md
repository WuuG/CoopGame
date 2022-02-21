# PowerUps
## 创建文件
### 创建PickUp Class
+ 创建SPickUpActor.cpp : Actor
+ 添加SphereComp和DecalComp
+ 给DecalComp设置Rotator使其能够在蓝图中更好的显示
+ Decal Size(64,75,75), SphereRadius(75.0f);
+ delete Tick
### 创建PowerUp Class
+ 创建SPowerUpActor : AActor
+ Delete Tick
``` cpp
    UPEORPERTY(...)
    float PowerUpInterval;
    UPEORPERTY(...)
    /* Total times we  apply the powerup effect */
    int32 TotalNrOfTicks;

    int32 TicksProcessed;

    FTimerHandle TimerHandle_PowerUpTick;

    UFUNCITON()
    void OnTickPowerUup();


public:

    void ActivatePowerup();

    UFUNCITON(BlueprintImplementableEvent, Category="PowerUps")
    void OnActivated();

    UFUNCITON(BlueprintImplementableEvent, Category="PowerUps")
    void OnPowerUpTicked();

    UFUNCITON(BlueprintImplementableEvent, Category="PowerUps")
    void OnExpired();
```
``` cpp
// ACtivatePowerup
if(PowerupsInterval > 0.0f)
{
GetWorldTimerManager().SetTimer(...);
}else 
{
    //...
}
// OnTickPowerup 该函数用以判断是否过期，并对时间进行更新
OnPowerUpTicked();
OnExpired();
```
## Super Speed Power-Up
### 新建
+ 添加所需文件
+ M_PowerupDecal, Deferred Decal, Translucent, Color_rougness, 添加Texture Sample
+ 创建PowerUp_SuperSpeed : SPowerUp
+ 通过Activated事件来设定Max Walk Speed
![M_PowerupDecal - 01](index_files/06-1.png)
![M_PowerupDecal - 02](index_files/06-2.png)
### PickUpActor
``` cpp
UPROPERTY(EditDefalutOnly, Category="PickupActor")
TSubclassOf<ASPowerupActor> PowerUpClass;

ASPowerupActor* PowerUpInstance;

UPROPERTY(EditDefalutOnly, Category="PickupActor")
float CoolDownDuration;

FTimerHandl TimerHandler_Respawn;

void Respawn();
```
``` cpp
// BeginPlay
    Respawn();
// Respawn
    if(PowerUpCLass == nullptr)
    {
        UE_LOG();
        return;
    }
    FActorSpawnParameters SpawnParams;
    // ...
    PowerUpInstance = GetWorld()->SpawnActor<ASPowerupActor>(PowerUpClass, GetTransform(), SpawnParams);
// NotifyActorBeginOverlap
    ActivatePowerup();
    powerUpInstance = nullptr;
    // Set Timer to Respwan
```
+ 创建M_Powerup, 创建base color
+ 以此创建MI_PowerUpSpeed实例，进行修改
+ 添加LightPoint，关闭Cast Shadows,修改灯光颜色, 并创建LightFunction M_PowerupLightFunction
![LightFunction](index_files/06-3-PowerLightFunction.png)
> 连接到Emitter Color

+ 将M_Powerup 改为Unlit,使其不受光照影响
![M_PowerUp](index_files/06-4-Powerup.png)
## Health ReGeneration
+ 新建PowerUp_HealthRegen

HealthComp
``` cpp
UFUNCTION(BlueprintCallable, Category="HealthComp")
void Heal(float HealAmount);
```
### Polish
+ MI_PowerupHealth, 将M_Powerup的Color提升为变量，使其能够在Instance中进行改变
+ Rotating movement component 可以将道具移动起来
## 多人模式
``` cpp
UPROPERTY(ReplicatedUsing=OnRep_powerupActive)
bool bIsPowerupActive;

UFUNCTION()
void OnRep_PowerupActive();

UFUNCTION(BlueprintCallable)
void OnPowerupActiveChanged(bool bNewIsActive);
```
``` cpp
// OnRep_PowerupActive
OnPowerupActiveChanged();
// ActivatePowerup()
    bIsPowerupActive = true;
    OnRep_PowerupActive();

// GetLifetimeReplicatedProps
```
### Powerups base class
+ 创建 BP_PowerupBase
> Parent to Expired
### Powerup_HealthRegen
+ Get All Actors of Class, ForEachLoop
+ ActivatePowerup(AActor* OtherActor), 使其能够判断是哪个角色overlap了
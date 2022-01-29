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
### 添加武器
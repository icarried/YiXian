# **弈仙牌模拟器**<br>
模拟弈仙牌的战斗过程<br>
下载该代码，请在终端中或cmd中输入：
```shell
git clone https://github.com/icarried/YiXian.git
```
    
## *卡牌*<br>
完成了所有锻玄宗卡牌（机缘秘术牌除外）<br>
详见`src/cards/`目录<br>
    
## *角色*<br>
目前仅有锻玄宗角色，并且只完成了部分仙命<br>
详见`src/roles/`目录<br>
    
## *buff和debuff*<br>
囊括了基本所有门派卡牌能造成的debuff<br>
buff完成了大部分<br>
详见`src/status_effects/`目录<br>
    
## *输出示例*
```
我方角色：小布
我方仙命：[空仙命] [空仙命] [空仙命] [空仙命] [修玄不泯]
我方卡组
1级《修罗吼》 1级《罗刹扑》 1级《罗刹扑》 1级《玄心斩魄》 1级《普通攻击》 1级《普通攻击》 1级《普通攻击》 1级《普通攻击》
敌方角色：小布
敌方仙命：[空仙命] [空仙命] [空仙命] [空仙命] [修玄不泯]
敌方卡组
1级《修罗吼》 1级《罗刹扑》 1级《罗刹扑》 1级《玄心斩魄》 1级《普通攻击》 1级《普通攻击》 1级《普通攻击》 1级《普通攻击》
战斗开始…………
--------第1回合--------
我方回合
血量：60/60，灵气：0 气势上限: 6
使用了第1张牌1级《修罗吼》，获得4层内伤，获得4层内伤，增加2点灵气，剩余2点灵气，恢复2点血，剩余60/60点血
敌方回合
血量：60/60，灵气：0 气势上限: 6  内伤: 4
失去4点血，剩余56/60点血，受到{4}点伤害敌方受到内伤造成4点伤害
使用了第1张牌1级《修罗吼》，获得4层内伤，获得4层内伤，增加4点灵气，剩余4点灵气，恢复4点血，剩余60/60点血
--------第2回合--------
我方回合
血量：60/60，灵气：2 气势上限: 6  内伤: 8
失去8点血，剩余52/60点血，受到{8}点伤害我方受到内伤造成8点伤害
使用了第2张牌1级《罗刹扑》，攻{8}，对敌方造成{8}点伤害失去8点血，剩余52/60点血，增加1点灵气，剩余3点灵气，获得1层外伤
敌方回合
血量：52/60，灵气：4 气势上限: 6  内伤: 8
失去8点血，剩余44/60点血，受到{8}点伤害敌方受到内伤造成8点伤害
使用了第2张牌1级《罗刹扑》，攻{8}，对敌方造成{9}点伤害失去9点血，剩余43/60点血，增加1点灵气，剩余5点灵气，获得1层外伤
--------第3回合--------
我方回合
血量：43/60，灵气：3 气势上限: 6  外伤: 1 内伤: 8
失去8点血，剩余35/60点血，受到{8}点伤害我方受到内伤造成8点伤害
使用了第3张牌1级《罗刹扑》，攻{8}，对敌方造成{9}点伤害失去9点血，剩余35/60点血，增加1点灵气，剩余4点灵气，获得1层外伤
敌方回合
血量：35/60，灵气：5 气势上限: 6  外伤: 1 内伤: 8
失去8点血，剩余27/60点血，受到{8}点伤害敌方受到内伤造成8点伤害
使用了第3张牌1级《罗刹扑》，攻{8}，对敌方造成{10}点伤害失去10点血，剩余25/60点血，增加1点灵气，剩余6点灵气，获得1层外伤
--------第4回合--------
我方回合
血量：25/60，灵气：4 气势上限: 6  外伤: 2 内伤: 8
失去8点血，剩余17/60点血，受到{8}点伤害我方受到内伤造成8点伤害
，失去1点灵气，剩余3点灵气，使用了第4张牌1级《玄心斩魄》，获得2层外伤，获得2层内伤，获得10层气势，攻{8}，对敌方造成{24}点伤害失去24点血，剩余3/60点血，减少10层气势
敌方回合
血量：3/60，灵气：6 气势上限: 6  外伤: 4 内伤: 10
失去10点血，剩余-7/60点血，受到{10}点伤害敌方受到内伤造成10点伤害
我方胜利
我方剩余血量：17
敌方剩余血量：-7
命元伤害：15
我方胜利
战斗结束…………
```
    
## *使用方法*<br>
修改`src/game.h`文件中的`InitMyInfo()`函数和`InitEnemyInfo()`函数，按自己的需求修改角色、仙命、卡牌等信息，然后编译src内所有.cpp文件即可<br>
以修改己方信息为例：<br>
```cpp
    // 初始化己方信息
    void InitMyInfo() {
        // 更改初始化角色
        delete my_role;
        my_role = new RoleDxXiaobu(sor_my_status, sor_enemy_status); // 更改角色为小布
        my_role->realm = REALM_HSQ; // 更改境界为化神期

        // 选取仙命
        my_role->PickDestiny(new RoleDxXiaobu::ExclusiveDestinyHSQ(my_role)); // 选取化神期专属仙命

        // 更改初始化状态
        sor_my_status->health_max->setValue(60); // 最大生命值修改为60

        // 初始化卡组，未修改的卡牌为1级的“普通攻击”
        delete sor_my_deck->cards[0];
        sor_my_deck->cards[0] = new Card_dx_hsq_xiuluohou(1, 0); // 卡牌位置0处的卡牌修改为1级的“卡牌_锻玄宗_化神期_修罗吼”

        delete sor_my_deck->cards[1];
        sor_my_deck->cards[1] = new Card_dx_lqq_luochapu(1, 1); // 卡牌位置1处的卡牌修改为1级的“卡牌_锻玄宗_炼气期_罗刹扑”

        delete sor_my_deck->cards[2];
        sor_my_deck->cards[2] = new Card_dx_lqq_luochapu(1, 2); // 卡牌位置2处的卡牌修改为1级的“卡牌_锻玄宗_炼气期_罗刹扑”

        delete sor_my_deck->cards[3];
        sor_my_deck->cards[3] = new Card_dx_hsq_xuanxinzhanpo(1, 3); // 卡牌位置3处的卡牌修改为1级的“卡牌_锻玄宗_化神期_玄心斩魄”
    }|
```
*目前仅完成了锻玄宗的卡牌效果*<br>
修改卡组中的卡牌时，需要注意卡牌的构造函数参数，第一个参数为卡牌等级，第二个参数为卡牌在卡组中的位置<br>
可以以如下方式修改牌组的卡牌：<br>
```cpp
        delete sor_my_deck->cards[{卡牌在卡组中的位置0-7}];
        sor_my_deck->cards[4] = new Card_{门派或副职或机缘}_{卡牌所属境界}_{卡牌名拼音全小写}({卡牌等级1-3}, {卡牌在卡组中的位置0-7});
```
其中卡牌的命名方法为`Card_{门派或副职或机缘}_{卡牌所属境界}_{卡牌名拼音全小写}`，详解如下<br>
```
命名方法：
牌以Card_开头，后面跟牌的信息
card_{门派或副职或机缘}_{境界}_{牌名}

*门派或副职或机缘*：
云灵剑宗：yl
七星阁：qx
五行道盟：wx
锻玄宗：dx

炼丹师：lds
符箓师：fls
琴师：qs
画师：hs
阵法师：zfs
灵植师：lzs

法宝：fbjy
灵兽：lsjy
云灵剑宗机缘：yljy
七星阁机缘：qxjy
五行道盟机缘：wxjy
锻玄宗机缘：dxjy

专属仙命牌：zsxm
其他：qt

*境界*：
炼气期：lqq
筑基期：zjq
金丹期：jdq
元婴期：yyq
化神期：hsq
返虚期：fxq
其他：qtq

*特殊情况*
“·”用“_”代替，如“崩拳·惊触”为“bengquan_jingchu”，全名为“Card_dx_hsq_bengquan_jingchu”
```
    
如果需要添加DIY的卡牌，需要在`src/cards/`目录下找到对应.h文件，复制其他卡牌的写法修改类名和效果完成卡牌定义<br>
然后在`src/game.h`文件中的`InitMyInfo()`函数和`InitEnemyInfo()`函数中添加新的卡牌<br>

构建方法：
```shell
cd build
cmake ..
```
如果使用的是vscode，可以按照以下修改`.vscode/tasks.json`文件和`.vscode/launch.json`文件，然后在`src/main.cpp`处运行，选择cmake构建，确保`cmmake`和`g++`已经安装
具体文件内容：
`tasks.json`
```json
{
    "tasks": [
        {
            "type": "shell",
            "label": "C/C++: cmake build",
            "command": "cmake",
            "args": [
                "--build",
                "${workspaceFolder}/build"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "reveal": "silent"
            },
            "problemMatcher": [
                "$gcc"
            ]
        }
        
    ],
    
    "version": "2.0.0"
}
```
`launch.json`
```json
{
    "configurations": [
        {
            "name": "C/C++: g++.exe build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}\\build\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\msys64\\ucrt64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: cmake build"
        }
    ],
    "version": "2.0.0"
}
```
    
## *其他*<br>
暂未开发图形化界面<br>
代码过于繁杂请见谅<br>
若道友愿意完成卡牌效果、仙命，欢迎提交PR<br>



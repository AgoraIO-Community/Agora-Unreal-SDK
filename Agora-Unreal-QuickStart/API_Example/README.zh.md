# API-Example

这是一个关于演示 Agora Unreal SDK API 调用的 Demo 程序。

这个 Demo 项目包含多个 Level:

- VideoLevel  包含视频的 API 调用的演示 Demo。

- VoiceLevel  包含音频 API 调用的演示 Demo。

![Alt text](README_Picture/Level_List.png?raw=true "PackageProject")

每个 Level 都可以独立运行。

你可以在 Unreal Editor 的 Edit/Project Settings/Default Maps 里去切换需要运行的 Level。


## Supported Platforms

- Android
- iOS
- MAC
- Windows 64-bit

## Run Project *IMPORTANT*

### 下载并且拷贝 Agora Unreal SDK。
Agora Unreal SDK 是一个独立的 Unreal 插件 module。
[下在 Agora Unreal SDK](https://download.agora.io/sdk/release/Agora_Unreal_FULL_SDK.zip)
下载链接中 Agora Unreal SDK， 解压后将 AgoraPlugin 文件夹拷贝到 API-Example 的 Plugins 文件夹下 "API-Example/Plugins/AgoraPlugin/".

![Alt text](README_Picture/copy_plugin.png?raw=true "PackageProject")

### 编译并且运行 Demo。
用 Unreal Editor 4.25 或以上版本打开 API_Example.uproject。

打包项目：

#### Windows 打包
File->Package Project->Windows->Windows(64-bit)
![Alt text](README_Picture/package.png?raw=true "PackageProject")

#### MAC 打包
File -> Package Project -> Mac

##### 在 info.plist 文件中添加设备权限:
1. 右击上一步编译出的 xxx.app 文件 - 选择 "Show Package Contents" 
![Alt text](README_Picture/Mac_package_add_permission.png?raw=true "PackageProject")
2. 进入 "Contents->Info.plist"
3. 选择 "Information Property List" 然后添加以下两个权限:

Privacy - Camera Usage Description
Privacy - Microphone Usage Description
![Alt text](README_Picture/Mac_package_add_permission2.png?raw=true "PackageProject")

##### 将 SDK framework 添加到你编译的 app 中
将 **xxx.framework** 从 **Plugins/AgoraPlugin/Source/ThirdParty/Agora/Mac/Release** 拷贝到 ***MacNoEditor/xxx/Contents/MacOS/*** 中。
![Alt text](README_Picture/Mac_package_add_framework.png?raw=true "PackageProject")


#### iOS 打包
File -> Package Project -> iOS


##### iOS 权限
在 iOS 上也需要以下权限：

Privacy - Camera Usage Description
Privacy - Microphone Usage Description

为了将上述权限添加到 info.plist 里，你可以在 **Edit->Project Settings->Platforms: iOS** 中，将 
`<key>NSCameraUsageDescription</key><string>AgoraVideoCall</string> <key>NSMicrophoneUsageDescription</key><string>AgoraVideoCall</string>`
添加到 Additional Plist Data 里。

![Alt text](README_Picture/iOS_add_permission.png?raw=true "PackageProject")
最后你就可以打包项目。

#### Android 打包
File -> Package Project -> Android
Android 中以下权限需要动态申请，可以通过蓝图类去做。

1: android.permission.RECORD_AUDIO
2: android.permission.CAMERA
3: android.permission.READ_PHONE_STATE
4: android.permission.WRITE_EXTERNAL_STORAGE

![Alt text](README_Picture/Android_permission.png?raw=true "PackageProject")
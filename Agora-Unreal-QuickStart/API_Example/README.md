# API-Example

This is a demo program to demonstrate the API call of Agora Unreal SDK.

This demo project contains multiple levels:

- Videolevel contains demo of API call of video.

- Voicelevel contains demo of audio API call.

![Alt text](README_Picture/Level_List.png?raw=true "PackageProject")

Each level can run independently.

You can switch the level to be run in Edit/Project Settings/Default maps of Unreal Editor.

## Supported Platforms

- Android
- iOS
- MAC
- Windows 64-bit

## Run Project *IMPORTANT*

### Download and copy Agora Unreal SDK.

Agora Unreal SDK is an independent unreal plug-in module.

[Download Agora Unreal SDK](https://download.agora.io/sdk/release/Agora_Unreal_FULL_SDK.zip)

Download Agora Unreal SDK from the link, unzip and copy AgoraPlugin folder to "API_Example/ Plugins/AgoraPlugin/" in the Plugins folder of API_Example

![Alt text](README_Picture/copy_plugin.png?raw=true "PackageProject")

### Compile and run demo.

Open API_Example.uproject with Unreal Editor 4.25 or above.

Package project:

#### Windows Packaging

File->Package Project->Windows->Windows(64-bit)

![Alt text](README_Picture/package.png?raw=true "PackageProject")

#### Mac Packaging

File -> Package Project -> Mac

##### In info.plist Add device permissions to file:

1. Right click the compiled xxx.app File - select "Show Package Contents"

![Alt text](README_Picture/Mac_package_add_permission.png?raw=true "PackageProject")

2. Enter "contents ->" Info.plist "

3. Select "Information Property List" and add the following two permissions:

Privacy - Camera Usage Description
Privacy - Microphone Usage Description

![Alt text](README_Picture/Mac_package_add_permission2.png?raw=true "PackageProject")


##### Add the SDK framework to your compiled app

copy **xxx.framework** from **Plugs/AgoraPlugin/Source/ ThirdParty/Agora/MAC/Release** to ***MacNoEditor/xxx/Contents/MacOS/***.
![Alt text](README_Picture/Mac_package_add_framework.png?raw=true "PackageProject")


#### IOS packaging
File -> Package Project -> iOS


##### IOS permissions
The following permissions are also required on IOS:

Privacy - Camera Usage Description
Privacy - Microphone Usage Description


To add the above permissions to the info.plist, you can

`<key>NSCameraUsageDescription</key><string>AgoraVideoCall</string> <key>NSMicrophoneUsageDescription</key><string>AgoraVideoCall</string>`
**Edit-> Project Settings->Platforms: iOS**

Add to additional plist data.

![Alt text](README_Picture/iOS_add_permission.png?raw=true "PackageProject")

Finally, you can package the project.

#### Android package

File -> Package Project -> Android

In Android, the following permissions need to be applied dynamically, which can be done through the blueprint class.

1: android.permission.RECORD_AUDIO
2: android.permission.CAMERA
3: android.permission.READ_PHONE_STATE
4: android.permission.WRITE_EXTERNAL_STORAGE

![Alt text](README_Picture/Android_permission.png?raw=true "PackageProject")
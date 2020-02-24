# Shape and Beats
 
音に反応してグラフィックが変化するオーディオビジュアライズ作品
![preview](https://i.gyazo.com/dde56798aee68c3fc40c85dad066b8ae.png)
![preview](https://i.gyazo.com/375ef68002b6ede106d6fe778ccc0516.png)
![preview](https://i.gyazo.com/ed929c4fe41d3dd6c165ce4853e9a8e5.png)
## Dependency
### framework
openframeworks 0.11.0
### addon
 - ofxGui 
 - ofxAssimpModelLoader

## Usage
キーボードとマウスでビジュアルを調整、音声信号を入力させて利用する。
### Input
'ofApp.c'の'setup()'の中にあるsettings.setInDevice()の関数の引数のdevices[]のインデックスを書き換えて入力を切り替え。  
```
settings.setInDevice(devices['任意のデバイスを表す整数']);
```
### Mouse
- ドラッグでカメラ回転、拡大縮小
- 'lightDir'で平行光源のベクトルを操作
- 'effect'で変化の具合を調整
- 'bgColor'で背景色を操作
- 'vertColor'で表示する図形の色を操作
### Keyboard
- 数字キーで表示する図形の変更
  - '0' ウサギの3dモデル
  - '1' ofSpherePrimitive
  - '2' ofIcoSpherePrimitive
  - '3' ofCylinderPrimitive
  - '4' ofBoxPrimitive
- アルファベットのキーでシェーディングの変更
  - 'a' グーローシェーディング
  - 'b' フォンシェーディング
  - 'c' フラットシェーディング
  - 'd' オリジナルのシェーディング1　<-推奨
  - 'e' オリジナルのシェーディング2　<-推奨かつデフォルト
## Video
https://www.youtube.com/watch?v=mVSkSAn9soE
https://www.youtube.com/watch?v=Y_CtwJTsUFc
https://www.youtube.com/watch?v=WimpGQmt3lU

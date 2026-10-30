# NuPhy Nude75 JIS などの分割スペースバー用 NICOLA-F配列キーマップ
キーボード側で親指シフトをローマ字(※英字キー入力から仮名への変換方式)出力するためのキーマップです。  
「」や『』・などは直接出力できませんから、MS-IMEなどの変換機能で確定します。

* 左親指キー : 単押し → 無変換キー 、長押し → TAB(変換候補)
* 右親指キー : 単押し → Spaceキー 、長押し → 変換キー

## 配列
![](nuphy_nude75_jis.png)

## Nicolaモードの制御
本キーボードはhoboNicolaで使用している"observe_ime"を使うことを想定しています。 
Windowsのアプリ毎のIME状態がキーボードに反映されるので、いわゆるモードずれを気にする必要がありません。   

(1) 無変換キーでMS-IME側"IME on"、CAPSLOCKで"IME off"に切り替える。  
(2) "observe_ime"はIMEの状態からキーボードにNum Lockで通知する。  
(3) キーボードではNum Lockの状態に従ってNicolaモードをon/offする。  

## 制限事項
* NuPhy Nude75 JIS ではPCの電源投入時にキーボードを認識しない場合がありました。ケースのリセットボタンを押してセットすると認識します。
* NuPhy Nude75 JIS ではWindowsスタートメニューからスリープ状態にしようとするとすぐに起き上がりました。
* Nicolaモードのとき、キーのリピートは効きません。

## 情報元
* https://github.com/okiraku-camera/observe_ime hoboNicolaで使用しているobserve_imeの情報です。

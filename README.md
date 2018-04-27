# report2_git
アルゴリズム特論課題2  
C++版です
## 各種ファイル
### [report2_git.cpp](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/report2_git.cpp "report2_git.cpp")
`main()`とかが入ってるやつ
### [GA.h](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/GA.h "GA.h")
`GA`クラスの定義とか
### [GA.cpp](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/GA.cpp "GA.cpp")
`GA`クラスの関数とか
### [stdafx.h](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/stdafx.h "stdafx.h")
インクルードしたヘッダの記述  
いるのは16行目から  
(正直[report2_git.cpp](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/report2_git.cpp "report2_git.cpp")に統合していいかな感)
## コピーの仕方
上の4つのファイルを中身を含めて作る→新しいプロジェクトを作ってVisualStudioの右側にある「ソリューション エクスプローラー」にD&D
## 関数と評価値について
`functionValue`には与えられた関数の値が入ってます  
`result`には`functionValue`の最大値を引いたものを2乗して入れてます
## その他
α=0.5、突然変異率0.1です。  
3000ステップいかないくらいで収束します。

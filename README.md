# FF12RNGControl

# 作成動機
FF12IJZSのアイテムコンプ/ステータス吟味プレイを「効率よく」行う方法を知ってしまったため、それを遂行するための簡易ツールを作成してみた。
# 原理
参考URLに一通り書いてある。http://www.fftogether.com/forum/index.php?topic=2778.0
大雑把にいうと次の通り:
- FFXII において、攻撃のダメージや回復の量の計算など, プレイヤーの目に見える多くの事象の計算に使用される生成器Rは共通している。
- Rに実装されている擬似乱数生成アルゴリズムはメルセンヌ=ツイスタ(1998年版)という、初期値のみに依存するアルゴリズム。(ちなみにPS4版は2002年版らしい)
- seed(初期値)は4537で固定である。
- 初期値が固定されていることから, Rの内部状態はゲーム開始地点では一定である.
- これらの事実から,以下のことが言える:「Rがゲーム開始地点から生成した乱数をその順に並べると,必ず固定の値を持った乱数表となる.」
- 従って,Rの内部状態を知る,あるいは今後の乱数を予測したい場合,ゲーム上での事象をもとに「現在までにRが出力した乱数の個数」を算出すれば良い.
- 手軽な乱数位置同定法はCureを使用すること。計算式が単純かつ使用する乱数が1で固定であるため。
# 大まかな使い方
CUIベース。XCodeのプロジェクトとして作ってしまったが、cppファイルとhppファイルを取り出して、適当なmakefileを作れば別にXCodeは不要なはず。
1. main.cppを起動
2. 4.configメニューに入り、ゲームのステータスに合わせてパラメータをいじる(最低でも、ケアル詠唱者のレベルと魔力、補正倍率は必要)
3. 1.でキャリブレーション。ケアルを複数回唱えて結果を入力する
4. 乱数位置が同定できたら、「次に行いたいこと」を2.決定メニューから選択し、ゲーム中で所望の事象を起こす。
5. 3.に戻る。

「次に行いたいこと」として現状用意しているのは、トレジャー出現、トレジャー取得、HPMP最大化。

**トレジャー出現** 欲しいトレジャーの出現するゾーンに入る直前に乱数を調整してからゾーンに入る。あらかじめゾーンに入ってから何番目の乱数がトレジャー出現判定に使われるかを調べてパラメータとして入力する
必要あり.

**トレジャー取得** トレジャーを入手する直前に乱数を調整する。あらかじめ欲しいトレジャーがレア枠かそうでないか、ダイヤの腕輪が必要か、トレジャーからギルが出る確率をアルティマニア(攻略本)で調べてパラメータとして入力する必要あり。

**HPMP最大化** レベルアップ直前に乱数を調整する。残り経験値を、一撃で倒せるモンスターから取得できる経験値以下にしておき、レベルアップさせたいキャラクターがそのモンスターを一撃で仕留める。利用する攻撃手法が幾つ乱数を消費するかを事前に調べる必要があり。

他の処理は現状未実装(需要のある他の可能性としては、「盗む」「密漁」コマンドを利用した際のアイテムレア枠取得、赤チョコボLv99出現、天候の調整)。需要の高い処理は基本的に乱数のmod値を計算するものなので、暫定的に、`x%RN > threshold`となるような乱数を検索する汎用コマンドを用意している。
# 今後の改良余地(自分メモ、時間が余ったら手を付けるかも)
- バグfix。 現在は打撃は乱数を固定10消費という扱いになってしまっている。連撃判定を加味して計算するように改良する
- **乱数そのものを直接見なくても必要なパラメータを入力するだけで所望の動作を実現する**
- Readmeの補充(これ)
- アクセスを容易にする。GUI作成、パッケージ化(処理は重くないので、Python3やWebアプリとして移植する方が良いか)
- さらなる自動化(e.g. ゲーム画面をOpenCV等で処理、Arduino等でコントローラを動かす)

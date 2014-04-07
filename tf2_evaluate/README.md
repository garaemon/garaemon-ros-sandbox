# tf2の評価
## tf2について
[tf](http://wiki.ros.org/tf)はsubscribeしていると、
`tf::TransformListener`がツリーを作る。
これがCPUを消費してしまうので、ROSで大きなシステムを作っていくと問題になりやすい。

そこで[tf2](http://wiki.ros.org/tf2)が開発された。
tf2は中央集権的なしくみで、ツリーを作るのは中央の`tf2_buffer_server`
と呼ばれるnodeのみになっている。
tf2は`/tf`と`/tf_static`(これはtf2で導入された静的な値を入れる特殊なトピック)の二つをsubscribe
して、actionlibのインターフェイスで外部にtfの値を提供する。

## 負荷実験環境
まずは負荷実験について述べる。計算機はmensaであり、16CPU coreの計算機である。
また、全てのプロセスは同一マシンで実行している。

### 多数のtfプロセスによる高負荷環境 [tf.launch](launch/tf.launch)
tfパッケージに含まれる`tf_static_publisher`と`tf_echo`を100プロセスずつ実行した。
このときの通信は`100 * 100 / 2 = 5000`コネクションで行われている。

この環境ではCPU Loadは平均で150以上の値を示すことが実験から得られた。

### 多数のtf2プロセスによる高負荷環境 [tf2.launch](launch/tf2.launch)
この実験では`tf2_static_publisher`と本パッケージに含まれる`tf2_echo`を100プロセスずつ実行した。
また、tf2を利用するために`tf2_buffer_server`も立ち上げている。

本実験での通信は`100 * 1 + 100 * 1 = 200`コネクションであった。

この環境ではCPU Loadは平均で4程度の非常に優良な結果を残している。

しかしながら留意しておかなくてはいけないのは、`tf2_static_publisher`は`/tf_static`に対し
固定値をpublishするものであり、実際のロボットシステムでの環境とは大きく異る。
つまり、この環境では`tf2_buffer_server`は積極的に座標系のツリーを作成はしない。

### 多数のtfとtf2プロセスによる高負荷環境 [tf\_with\_tf2.launch](launch/tf_with_tf2.launch)
より実際のロボットシステムと環境を知覚するために、`tf_static_publisher`と`tf2_echo`を100プロセスずつ立ち上げて
実験環境を構築した。

この環境では先の実験と異なり、`tf2_buffer_server`は積極的に座標系のツリーを作成・更新する。

この環境ではCPU Loadは平均で6程度の結果になった。

このときに`tf2_buffer_server`はCPUを100%使いきっており、それによって計算機全体の負荷が頭打ちになっていることが
この評価からわかった。

また、この実験においては1.0秒の期間で`lookupTransformation`を実行すると、平均で10回に1回程度失敗した。
通常のtfをもちいた動揺の環境ではLoad値が非常に高くなっていたことから、tfと比べると良好な結果であるといえる。

## 速度実験
tfおよびtf2の`lookupTransformation`に必要となる時間の軽鎖奥を行った。
環境は[tf\_with\_tf2.launch](launch/tf_with_tf2.launch)によって作成し、それぞれ
`tf_lookup_bench.cpp`, `tf2_lookup_bench.cpp`によって測定した。

* tf 0.001msec程度
* tf2 0.01sec~0.0005sec程度

tf2の`lookupTransform`では大きな時間がかかることがわかった。
これはactionlibによって最低でも2回topicによって通信が行われることが原因と推定できる。
この周期は`tf2_ros::BufferClient`の第二引数で指定できる。

## 結論
tf2によって計算負荷を大きく下げることができるが、`lookupTransform`に掛かる時間は1000倍程度大きくなる。
0.1秒程度の時間が許容できるノードに関しては、積極的にtf2を利用していくことが良いと言える。


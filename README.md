# Arduino 開発（VS Code / Linux）

Arduino Uno（`arduino:avr:uno`）用の開発環境です。
Arduino CLI 1.5.1 と Arduino AVR Boards 1.8.8 をプロジェクト内に導入済みです。
VS Code でこのフォルダー全体を開いてください。

## 使い方

1. `Ctrl+Shift+B` で `control`、`HC_test`、`md_test` のいずれかを選んでビルドします。
2. USB で Uno を接続し、「ターミナル → タスクの実行 → Arduino: Boards」でポートを確認します。
3. `Arduino: Upload` を実行し、スケッチとポート（例 `/dev/ttyACM0`）を指定します。ビルド成功後に書き込みます。
4. `Arduino: Monitor (9600 baud)` でシリアル出力を確認します。`Ctrl+C` で終了してください。書き込み前にモニターを終了します。

コード補完には導入済みの Microsoft C/C++ 拡張機能を使用します。
`.vscode/arduino.json` は既存設定との互換用です。上記タスクのボード設定は `.vscode/tasks.json` と `scripts/arduino-upload` にあります。

## control のシリアル操作

9600 baud で、整数 `0`～`255` に改行（LF、CR、CRLF のいずれか）を付けて送信します。
例：`128\n` を送ると両モータを PWM 128 で前進方向に駆動し、`0\n` で停止します。
数値は PWM 出力であり、回転数や移動距離の指定ではありません。起動時は停止し、受信した出力を次の指令まで維持します。
範囲外の数値や数字以外を含む行は、改行受信時にエラーを表示して停止します。空行は無視します。
距離は約100 ms間隔で出力します（障害物による自動停止は行いません）。
モータAは4・5・6番、モータBは7・8・9番ピンを使用します。
車輪が前進方向に回らない場合は、`control/control.ino` の該当する `MOTOR_A_FORWARD` または `MOTOR_B_FORWARD` を `LOW` から `HIGH` に変更してください。

## USB 通信権限（初回のみ）

ユーザー `okabe` はまだ `dialout` に所属していません。管理者パスワードが必要なため、この設定は未実施です。
通常の Linux 端末で次を実行し、PC を再起動してください。

```bash
sudo usermod -aG dialout okabe
```

再起動後に `id -nG` で `dialout` が含まれることを確認します。
USB シリアルポート `/dev/ttyUSB0`、`/dev/ttyUSB1`、`/dev/ttyUSB2` は検出されましたが、ボード種別は Unknown でした。Uno のポートは抜き差し時の変化で確認してください。書き込みとシリアル通信は未検証です。

## ターミナルでの操作

プロジェクトのルートで実行します。

```bash
bash scripts/arduino board list
bash scripts/arduino compile --fqbn arduino:avr:uno control
bash scripts/arduino-upload control /dev/ttyACM0
bash scripts/arduino monitor --port /dev/ttyACM0 --config baudrate=9600
```

`.tools/`（CLI）、`.arduino/`（ボード・ライブラリー）、`.build/`（生成物）は Git 管理対象外です。
別の PC に clone した場合は、Linux x86_64 用 Arduino CLI 1.5.1 の `arduino-cli` を `.tools/arduino/` に配置し、以下を実行します。

```bash
bash scripts/arduino core update-index
bash scripts/arduino core install arduino:avr@1.8.8
```

ボードコアやコンパイラーを更新した場合、`.vscode/c_cpp_properties.json` のバージョン付きパスも更新してください。

公式資料: [CLI のインストール](https://docs.arduino.cc/arduino-cli/installation/)、[Linux のポート権限](https://support.arduino.cc/hc/en-us/articles/360016495679-Fix-port-access-on-Linux)

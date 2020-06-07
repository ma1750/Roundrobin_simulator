# Roundrobin_simulator

ラウンドロビンアルゴリズムでプロセスを処理していくデモ  
プロセスの個数、それぞれのプロセスの到着時刻、処理時間、タイムスライスを入力して実行できます  

# Example

次のプロセス集合に対してラウンドロビンを適用して平均応答時間を求めます  
|プロセス|到着時刻|処理時間|
|---|---|---|
|A|0|2|
|B|1|10|
|C|3|7|
|D|5|3|

実行方法  
1. プロセスの数を入力する  
1. 次にプロセス名、到着時刻、処理時間をスペース区切りで入力する  
1. プロセスごとに改行が必要  
1. 最後にタイムスライス(何秒ごとに切り替えるか)を入力することで実行  

左の数字は時刻を表し右の `Task: X` は現在実行中のプロセスの名前を表示する  
最後に終了時刻、応答時間、平均応答時間を出力する  
```
$./run
input : Task_Number
4
input : Task_Name Arrival_Time Cost
A 0 2
B 1 10
C 3 7
D 5 3
input : Step_Number
2

start
 1 Task:A
 2 Task:A is finish
 3 Task:B
 4 Task:B
 5 Task:C
 6 Task:C
 7 Task:B
 8 Task:B
 9 Task:D
10 Task:D
11 Task:C
12 Task:C
13 Task:B
14 Task:B
15 Task:D is finish
16 Task:C
17 Task:C
18 Task:B
19 Task:B
20 Task:C is finish
21 Task:B
22 Task:B is finish
end

Task_Name|Arrival_Time|Finish_Time|Response_time|
        A|           0|          2|            2|
        B|           1|         22|           21|
        C|           3|         20|           17|
        D|           5|         15|           10|

Average_Process_Time = 12.50
```
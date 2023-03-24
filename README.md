# Page-Replacement
模擬FIFO、LRU、Additional Reference Bits、Second Chance 、Least Frequently Used、Most Frequently Used等Page Replacement

輸入Page Frame個數及各個Page Reference的次序，依照不同的Page Replacement方法，計算各自Page Fault及Page Replace的次數
- FIFO:將存在於實體記憶體頁框中最久的分頁給取代掉。
- LRU:將存在於實體記憶體頁框中最久沒用到的分頁給取代掉。
- Additional Reference Bits:保留幾個bit，來表示頁面的使用歷史。每個bit對應一個時間間隔，最左邊的比特表示最近的時間間隔，最右邊的比特表示最早的時間間隔在每個時間間隔結束時將位右移一位。
- Second Chance:基於FIFO，但是會重新給予被使用到的分頁第二次機會，使其可以跳過一次頁框被別的分頁選擇取代的命運。
- Least Frequently Used:在給定時間段內訪問次數最少的頁面被刪除,取代了最不常用的頁面
- Most Frequently Used:定義和LFU有點相像，但卻是將次數最少的page認為是剛被帶入不久、很快就需要用到的類型

#!/bin/bash

# awk '{[pattern] action}' {filenames}

echo "每行按空格或TAB分割，输出文本中的1、4项"
awk '{print $1,$4}' ./awk_text.txt
echo -e "\\n"

echo "格式化输出"
awk '{printf "%-8s %-10s\n", $1, $2}' ./awk_text.txt
echo -e "\\n"

echo "-F相当于内置变量FS, 指定分割字符"
awk -F , '{print $1,$2}' ./awk_text.txt
echo -e "\\n"

echo "使用内建变量"
awk 'BEGIN{FS=","} {print $1,$2}' ./awk_text.txt 
echo -e "\\n"
awk 'BEGIN{FS=" "} {print $1,$2}' ./awk_text.txt 
echo -e "\\n"

echo "-v  # 设置变量"
awk -va=1 -vb=2 '{print $1, $1+a, $1+b}' ./awk_text.txt
echo -e "\\n"

echo "awk -f {awk脚本} {文件名}"
awk -f cal.awk awk_text.txt
echo -e "\\n"

echo "过滤第一列大于2的行"
awk '$1>2'  ./awk_text.txt
awk '$1>2 {print $1}'  ./awk_text.txt
echo -e "\\n"

echo "输出第二列包含 th，并打印第二列与第四列"
awk '$2 ~ /th/ {print $2, $4}' ./awk_text.txt
echo -e "\\n"
awk '$2 !~ /th/ {print $2, $4}' ./awk_text.txt
# ~ 表示模式开始。// 中是模式，!表示取反
echo -e "\\n"

echo "忽略大小写"
awk 'BEGIN{IGNORECASE=1} /this/' ./awk_text.txt
echo -e "\\n"

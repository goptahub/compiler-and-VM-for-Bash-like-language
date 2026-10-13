# test_while_1.sh
i=1
sum=0

while [ $i -le 4 ]; do
    sum=$((sum + i))
    i=$((i + 1))
done
echo $sum
echo $i # Вывод в терминал
# Итерации: 
# 1) sum=0+1=1, i=2
# 2) sum=1+2=3, i=3
# 3) sum=3+3=6, i=4
# 4) sum=6+4=10, i=5 -> выход
# ОТВЕТ: sum = 10, i = 5
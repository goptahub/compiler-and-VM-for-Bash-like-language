# test_while_2.sh
val=4
result=1

while [ $val -gt 1 ]; do
    result=$((result * val))
    val=$((val - 1))
done
echo $result
echo $val # Вывод в терминал

# Итерации (факториал числа 4):
# 1) result=1*4=4, val=3
# 2) result=4*3=12, val=2
# 3) result=12*2=24, val=1 -> выход

# ОТВЕТ: result = 24, val = 1
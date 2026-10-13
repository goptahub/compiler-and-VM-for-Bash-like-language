# test_while_3.sh
left=1
right=10
steps=0

while (( left < right )); do
    (( left = left + 2 ))
    (( right = right - 1 ))
    (( steps = steps + 1 ))
done

echo $left
echo $right
echo $steps

# Итерация 1: left = 3, right = 9, steps = 1
# Итерация 2: left = 5, right = 8, steps = 2
# Итерация 3: left = 7, right = 7, steps = 3
# Итерация 4: Условие (( 7 < 7 )) ложно. Выход.

# steps = 3, left = 7, right = 7
# nested_test_3.sh
target=10
count=0
num=2
last_prime=0

while (( count < target )); do
    is_prime=1
    divisor=2

    # Внутренний цикл: проверяем делимость
    while (( divisor * divisor <= num )); do
        (( rem = num % divisor ))
        
        if (( rem == 0 )); then
            is_prime=0
            (( divisor = num ))
        fi
        
        (( divisor = divisor + 1 ))
    done

    # Проверяем флаг
    if (( is_prime == 1 )); then
        (( count = count + 1 ))
        (( last_prime = num ))
    fi

    (( num = num + 1 ))
done

echo $last_prime

# Выражение: Алгоритм поиска 10-го простого числа.
# Шаги: Простые числа: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29.

# ОТВЕТ: last_prime = 29
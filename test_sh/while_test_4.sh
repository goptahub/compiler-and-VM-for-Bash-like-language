# test_while_4.sh
n=1
evens=0
odds=0

while (( n <= 5 )); do
    (( rem = n % 2 ))

    if (( rem > 0 )); then
        (( odds = odds + 1 ))
    else
        (( evens = evens + 1 ))
    fi
    
    (( n = n + 1 ))
done

echo $evens
echo $odds
echo $n

# ОТВЕТ: evens = 2, odds = 3, n = 6.
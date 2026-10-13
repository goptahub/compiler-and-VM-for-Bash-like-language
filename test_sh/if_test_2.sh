# test_if_2.sh
x=5
status=0

if [ $x -eq 5 ]; then
    status=1
elif [ $x -eq 10 ]; then
    status=2
else
    status=3
fi

echo $status # Вывод в терминал

# ОТВЕТ status: 2
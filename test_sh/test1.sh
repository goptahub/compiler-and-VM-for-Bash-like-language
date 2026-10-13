#!/bin/bash


echo $((1++2))
echo $((1+ +2))
echo $((1 ++2))
echo $((1++ 2))



a=2
echo $((1+ +a))



a=2
echo $((1+ ++a))
a=2
echo $((1+ ++a))
a=2
echo $((1++ +a))
a=2
echo $((1+ + +a))
a=2
echo $((1+++ a))
a=2
echo $((1+ ++ a))
a=2
echo $((1 ++ + a))



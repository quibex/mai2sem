quibex@STARK:~/labs/kp7$ ./kp7.out << end
> 5 5 
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
> end

-1
Matrix:
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
Array M: | -1 | -1 | -1 | -1 | -1 | 
Array A: 
quibex@STARK:~/labs/kp7$ ./kp7.out << end
5 5 
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 1
end

-1
Matrix:
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 1.000000 
Array M: | -1 | -1 | -1 | -1 | 0 | 
Array A: [ 4 | 1.000000 | 0 ] 
quibex@STARK:~/labs/kp7$ ./kp7.out << end
5 5 
0 0 0 0 0
0 0 0 14 0
0 12 0 0 0
0 0 0 0 0
0 0 0 10 -15
end

-1
Matrix:
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 14.000000 0.000000 
0.000000 12.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 10.000000 1.000000 
Array M: | -1 | 0 | 1 | -1 | 2 | 
Array A: [ 3 | 14.000000 | 0 ] [ 1 | 12.000000 | 0 ] [ 3 | 10.000000 | 3 ] [ 4 | 1.000000 | 0 ] 
quibex@STARK:~/labs/kp7$ ./kp7.out << end
5 5
0 0 0 0 0
0 0 0 14 0
0 12 0 0 0
0 0 0 0 0
0 0 0 15 -15
end
biba - 4

3
Matrix:
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 -0.933333 0.000000 
0.000000 12.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 -1.000000 -15.000000 
Array M: | -1 | 0 | 1 | -1 | 2 | 
Array A: [ 3 | -0.933333 | 0 ] [ 1 | 12.000000 | 0 ] [ 3 | -1.000000 | 3 ] [ 4 | -15.000000 | 0 ] 
quibex@STARK:~/labs/kp7$ ./kp7.out << end
5 5
0 0 0 0 0
0 0 0 14 0
0 12 0 0 0
0 0 0 0 0
0 0 -15 15 -15
end
biba - 3
biba - 4

3
Matrix:
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 -0.933333 0.000000 
0.000000 12.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 -15.000000 -1.000000 -15.000000 
Array M: | -1 | 0 | 1 | -1 | 2 | 
Array A: [ 3 | -0.933333 | 0 ] [ 1 | 12.000000 | 0 ] [ 2 | -15.000000 | 3 ] [ 3 | -1.000000 | 4 ] [ 4 | -15.000000 | 0 ] 
quibex@STARK:~/labs/kp7$ ./kp7.out << end
5 5
0 0 0 0 0
0 0 0 14 0
0 12 0 0 0
0 0 0 0 0
0 0 -15 13 -15
end
biba - 4

2
Matrix:
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 14.000000 0.000000 
0.000000 12.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 0.000000 0.000000 
0.000000 0.000000 1.000000 13.000000 -15.000000 
Array M: | -1 | 0 | 1 | -1 | 2 | 
Array A: [ 3 | 14.000000 | 0 ] [ 1 | 12.000000 | 0 ] [ 2 | 1.000000 | 3 ] [ 3 | 13.000000 | 4 ] [ 4 | -15.000000 | 0 ] 
quibex@STARK:~/labs/kp7$ ./kp7.out << end
5 3  
0 0 0    
0 0 0 
0 0 0 
0 0 4 
0 0 12
end

-1
Matrix:
0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 
0.000000 0.000000 0.000000 
0.000000 0.000000 0.333333 
0.000000 0.000000 1.000000 
Array M: | -1 | -1 | -1 | 0 | 1 | 
Array A: [ 2 | 0.333333 | 0 ] [ 2 | 1.000000 | 0 ] 
quibex@STARK:~/labs/kp7$ ./kp7.out << end
5 3  
0 0 0 
0 5 0
0 0 0
3 0 4
0 0 12
end

-1
Matrix:
0.000000 0.000000 0.000000 
0.000000 5.000000 0.000000 
0.000000 0.000000 0.000000 
3.000000 0.000000 0.333333 
0.000000 0.000000 1.000000 
Array M: | -1 | 0 | -1 | 1 | 3 | 
Array A: [ 1 | 5.000000 | 0 ] [ 0 | 3.000000 | 2 ] [ 2 | 0.333333 | 0 ] [ 2 | 1.000000 | 0 ] 
quibex@STARK:~/labs/kp7$ ./kp7.out << end
3 5  
0 0 0 3 4
3 0 4 14 17
0 0 12 -18 1
end

-1
Matrix:
0.000000 0.000000 0.000000 -0.166667 4.000000 
3.000000 0.000000 4.000000 -0.777778 17.000000 
0.000000 0.000000 12.000000 1.000000 1.000000 
Array M: | 0 | 2 | 6 | 
Array A: [ 3 | -0.166667 | 1 ] [ 4 | 4.000000 | 0 ] [ 0 | 3.000000 | 3 ] [ 2 | 4.000000 | 4 ] [ 3 | -0.777778 | 5 ] [ 4 | 17.000000 | 0 ] [ 2 | 12.000000 | 7 ] [ 3 | 1.000000 | 8 ] [ 4 | 1.000000 | 0 ] 
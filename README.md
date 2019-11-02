```bash
g++ ./0060.serialize_btree.cpp -std=c++11 -o btree
./btree
3 1 2 3
```

g++ with TEST=0, clang++ with TEST=0 or 1
```
3 1 2 3
RETN0|1
RETN1|2
LEFT 1
1 1
RETN1|2
RETN2|3
LEFT 2
2 2
RETN2|3
3 -1
1 2 3
```

g++ with TEST=1
```
3 1 2 3
RETN0|1
RETN1|2
LEFT -1
1 -1
RETN1|2
RETN2|3
LEFT -1
2 -1
RETN2|3
3 -1
1
```

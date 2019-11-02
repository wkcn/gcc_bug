# Reason
In GCC Compiler, it computes the address of `vs[si].left` firstly, then calls the function `get_snode`, which expands the vector `vs` and makes the address of `vs[si].left` invalid. In contrast, Clang calls `get_snode` firstly, then computes the address of `vs[si].left`. 

GCC:
1. Compute the address of `vs[si].left`, and move it into register
2. Call the function `get_snode`
3. Move value into the memory address

Clang:
1. Call the function `get_snode`
2. Compute the address of `vs[si].left`, and move it into register
3. Move value into the memory address

# Reproduce Procedure
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

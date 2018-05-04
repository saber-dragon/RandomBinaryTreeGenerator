# Simple Random Binary Tree Generator

This repo implements a very simple random binary tree generator. The major purpose of this repo is to produce some test cases for binary-tree related problems on leetcode.


## Usage 

see ["example.cpp"](./example.cpp)

## Sample Output

> By `SimplePrint`:
```text
{val : 6724, left : 9480, right : 223}
{val : 9480, left : 3885, right : 300}
{val : 3885, left : 8074, right : 9900}
{val : 8074, left : 9191, right : NULL}
{val : 9191, left : NULL, right : NULL}
{val : 9900, left : NULL, right : NULL}
{val : 300, left : 7552, right : NULL}
{val : 7552, left : NULL, right : 3938}
{val : 3938, left : NULL, right : NULL}
{val : 223, left : NULL, right : NULL}
```

> By `TreeToDot`:

```dot
digraph BinaryTree {
node [shape = record,height=.1];
 node0[label = "<f0> |<f1> 6724|<f2> "];
 node1[label = "<f0> |<f1> 9480|<f2> "];
 node2[label = "<f0> |<f1> 3885|<f2> "];
 node3[label = "<f0> |<f1> 8074|<f2> "];
 node4[label = "<f0> |<f1> 9191|<f2> "];
 node5[label = "<f0> |<f1> 9900|<f2> "];
 node6[label = "<f0> |<f1> 300|<f2> "];
 node7[label = "<f0> |<f1> 7552|<f2> "];
 node8[label = "<f0> |<f1> 3938|<f2> "];
 node9[label = "<f0> |<f1> 223|<f2> "];
"node0":f0 -> "node1":f1;
"node1":f0 -> "node2":f1;
"node2":f0 -> "node3":f1;
"node3":f0 -> "node4":f1;
"node2":f2 -> "node5":f1;
"node1":f2 -> "node6":f1;
"node6":f0 -> "node7":f1;
"node7":f2 -> "node8":f1;
"node0":f2 -> "node9":f1;
}
```
Note that the dot file can be viewed visualized with `xdot` or you can use `graphviz` to get the PNG by simple running `dot -Tpng -o example.png bt.dot`.
The resulted PNG is shown below.
    
![](./example.png)
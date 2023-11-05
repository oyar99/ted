# Tree Edit Distance

Given two node-labeled rooted trees $T$ and $T'$ each of size at most $n$, what is
the minimum number of elementary operations needed to transform $T$ into $T'$?.

This program implements different solutions for the above problem in C++.

Please see the next guides on how to set up GCC on different platforms.

    - Windows: https://code.visualstudio.com/docs/cpp/config-mingw.
    - Linux: https://code.visualstudio.com/docs/cpp/config-linux
    - Mac: https://code.visualstudio.com/docs/cpp/config-clang-mac

## How to compile this program?

```sh
g++ -o ted.exe -I ./src/models -I ./src/procedures *.cpp src/models/*.cpp src/procedures/*.cpp
```

## How to run this program?

The program receives two trees $T$ and $T'$ and returns a number $d$ that indicates the number of elementary
operations required to transform $T$ into $T'$.

The input contains two trees T1 and T2 represented as strings that correspond
to the pre-order traversal of T such that when we visit node u, we append
label(u) followed by a matching parenthesis that encloses the subtree rooted at u.

The first line of the input is a string of size 3n where n corresponds to the number 
of nodes in T1. This string is the pre-order traversal of T1 as explained above.

The second line of the input is a string of size 3m where m corresponds to the number
of nodes in T2. This string is the pre-order traversal of T2 as explained above.

n and m are both at least 1.

For instance:

$\begin{tikzpicture}[
        baseline=(current bounding box.center),
        level distance=1.2cm,
        level 1/.style={sibling distance=1.5cm},
        level 2/.style={sibling distance=1.5cm}]

        \node[circle,draw] 
        {1} 
            child {node[circle,draw] 
                {\phantom{2}} child {node[circle,draw] 
                    {\phantom{3}}
                }
            }
            child {node[circle,draw] 
                {4}
            }
            child {node[circle, draw]
                {5}
            };
\end{tikzpicture}$

Note each integer represents a labeled node. As such, there might be duplicated integers
in the string representation of the tree that actually correspond to different nodes.

The program requires the following parameters in the specified order

- The algorithm to use to compute tree edit distance. Either of these values: `ZhangShasha`, `Approx` or `TED`.

The first option `ZhangShasha` is an implementation of the algorithm described by ZhangShasha in 1989 in the paper
[Simple Fast Algorithms for the Editing Distance between Trees and Related Problems](https://www.proquest.com/docview/919771926) which
runs in $O(n^4)$ time.

```sh
ted.exe < data/sample_5_8.in > output/sample_5_8.out ZhangShasha
```

The second option is an approximation algorithm described in the paper [1+ε approximation of tree edit distance in quadratic time](https://dl.acm.org/doi/10.1145/3313276.3316388).

```sh
ted.exe < data/sample_5_8.in > output/sample_5_8.out Approx
```

The third option is an algorithm devised by Santiago Ramirez and Jhon Rayo inspired in some of the ideas of previos work in the area.

```sh
ted.exe < data/sample_5_8.in > output/sample_5_8.out TED
```

- The approximation factor $\varepsilon$ for the approximation scheme. Should be a positive integer value and is only required if the algorithm specified is `Approx`.


```sh
ted.exe < data/sample_5_8.in > output/sample_5_8.out Approx 2
```

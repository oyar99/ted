# Tree Edit Distance

Given two node-labeled rooted trees $T$ and $T'$ each of size at most n, what is
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
operations required to transform $T$ into $T'$. The program requires the following parameters in the specified order

- The algorithm to use to compute tree edit distance. Either of these values: `ZhangShasha`, `Approx` or `TED`.

The first option `ZhangShasha` is an implementation of the algorithm described by ZhangShasha in 1989 in the paper
[Simple Fast Algorithms for the Editing Distance between Trees and Related Problems](https://www.proquest.com/docview/919771926) which
runs in $O(n^4) time.

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

- The approximation factor $\eps$ for the approximation scheme. Should be a positive integer value and is only required if the algorithm specified is `Approx`.


```sh
ted.exe < data/sample_5_8.in > output/sample_5_8.out Approx 2
```

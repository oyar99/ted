# Tree Edit Distance

Given two node-labeled rooted trees $T$ and $T'$ each of size at most $n$, what is
the minimum number of elementary operations needed to transform $T$ into $T'$?.

This program implements different solutions for the above problem in C++.

Please see the next guides on how to set up GCC on different platforms.

    - Windows: https://code.visualstudio.com/docs/cpp/config-mingw.
    - Linux: https://code.visualstudio.com/docs/cpp/config-linux
    - Mac: https://code.visualstudio.com/docs/cpp/config-clang-mac

## Summary

The following table summarizes the time complexities for different algorithms.

|   Algorithm           | Time Complexity                               | Type
|   ------------------- | --------------------------------------------- | --------------------------------------
|   ZhangShasha         | $O(n^4)$                                      | Exact
|   Saeed               | $O(n^8)$                                      | Exact
|   Approx Saeed        | $O(n^2)$                                      | 2-approximation

## Dataset

The `data` folder contains sample inputs for trees of different sizes. It follows the below convention

`sample_x_y.in` where $x$ corresponds to the number of nodes in $T$ and y to the number of nodes in $T'$.

## Results

The `output` folder contains the result of running each algorithm with the sample data.
Each file contains a single number $d$ that indicates the number of operations to transform $T$ into $T'$.

## Scripts

The `scripts` folder contains utilities to generate random samples and test the correctness of the algorithms.

|Script                            |Description
|----------------------------------|-----------------------------------------------------------------------------
| `test.sh`                        | Builds and tests the implementations for `ZhangShasha` and `Saeed` algorithm.
| `random_sample.py`               | Generates a random tree using its pre-order traversal.

## How to compile this program?

```sh
g++ -o ted.exe -I./src/models -I./src/procedures *.cpp src/models/*.cpp src/procedures/*.cpp
```

## How to run this program?

The program receives two trees $T$ and $T'$ and returns a number $d$ that indicates the number of elementary
operations required to transform $T$ into $T'$.

Given a rooted tree $T$, we can represent the pre-order traversal of $T$ in such a way that when we visit node $u$, we append
$label(u)$ followed by a matching parenthesis that encloses the subtree rooted at $u$. This representation is unique for all possible
trees.

The first line of the input is a string of the pre-order traversal of $T$.
The second line of the input is a string of the pre-order traversal of $T'$.
The program requires the following parameters in the specified order

|Command                           |Description
|----------------------------------|----------------------------------------------------
| `ZhangShasha`, `Saeed`, `Approx` | The algorithm to use to compute tree edit distance


The first option `ZhangShasha` is an implementation of the algorithm described by ZhangShasha in 1989 in the paper
[Simple Fast Algorithms for the Editing Distance between Trees and Related Problems](https://www.proquest.com/docview/919771926) which
runs in $O(n^4)$ time.

```sh
ted.exe < data/sample_5_8.in > output/sample_5_8.out ZhangShasha
```

The second option `Saeed` is an exact algorithm adapted from the paper [1+ε approximation of tree edit distance in quadratic time](https://dl.acm.org/doi/10.1145/3313276.3316388) that runs in $O(n^8)$ time. It clearly performs way worse than `ZhangShasha`, but it demonstrates the key ideas to make a quadratic approximation possible.

```sh
ted.exe < data/sample_5_8.in > output/sample_5_8.out Saeed
```

The third option `Approx` is an implementation of the approximation scheme described in the paper [1+ε approximation of tree edit distance in quadratic time](https://dl.acm.org/doi/10.1145/3313276.3316388).

```sh
ted.exe < data/sample_5_8.in > output/sample_5_8.out Approx
```

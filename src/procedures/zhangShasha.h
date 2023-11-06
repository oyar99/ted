#ifndef ZHANGSHASHA_H
#define ZHANGSHASHA_H

#include <tree.h>

namespace ZhangShasha {
    /**
     * Computes the Tree Edit Distance (TED) between T1 and T2 using the dynamic 
     * programming algorithm described by ZhangShasha in 1989 in the paper 
     * Simple Fast Algorithms for the Editing Distance between Trees and Related Problems. 
     * 
     * It requires O(n^4) time.
     * 
     * @param t1 An ordered labeled rooted tree
     * @param t2 An ordered labeled rooted tree
     * 
     * @returns An integer that represents the number of operations needed to transform t1 into t2.
     * Each operation has unit cost.
    */
    int ted(const Tree& t1, const Tree& t2);

    /**
     * Computes the Tree Edit Distance (TED) between T1 and T2 using the dynamic 
     * programming algorithm described by ZhangShasha in 1989 in the paper 
     * Simple Fast Algorithms for the Editing Distance between Trees and Related Problems. 
     * 
     * It requires O(n^4) time.
     * 
     * @param t1 An ordered labeled rooted tree
     * @param t2 An ordered labeled rooted tree
     * 
     * @returns A matrix where each tree edit distance between subtrees of T1 and T2 can be found.
    */
    std::vector<std::vector<int>> ted_complete(const Tree& t1, const Tree& t2);

    /**
     * Computes the Forest Edit Distance (FED) between F1 and F2 using the dynamic
     * programming algorithm described by ZhangShasha in 1989 in the paper
     * Simple Fast Algorithms for the Editing Distance between Trees and Related Problems.
     * 
     * It requires O(n^2) time.
     * 
     * @param t1 An ordered labeled rooted tree
     * @param il The index of the left node for partitioning T1 into F1
     * @param ir The index of the right node for partitioning T1 into F1
     * @param t2 An ordered labeled rooted tree
     * @param jl The index of the left node for partitioning T2 into F2
     * @param jr The index of the right node for partitioning T2 into F2
     * @param ted The tree edit distances between nodes of T1 and T2
     * 
    */
    std::vector<std::vector<int>> fed(const Tree& t1, int il, int ir, const Tree& t2, int jl, int jr, const std::vector<std::vector<int>>& td);
}

#endif
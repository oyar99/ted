#ifndef SAEEDSCHEME_H
#define SAEEDSCHEME_H

#include <tree.h>

namespace SaeedScheme {
    /**
     * Computes the Tree Edit Distance (TED) between T1 and T2 using the approximation scheme algorithm 
     * described by Saeed Seddighin and others in 2019 in the paper 1+ϵ Approximation of Tree Edit
     * Distance in Quadratic Time

     * @param t1 An ordered labeled rooted tree
     * @param t2 An ordered labeled rooted tree
     * @param e The approximation factor. Should be greater than zero
     * 
     * @returns An integer that represents an approximation for the number of operations needed to transform t1 into t2.
     * Each operation has unit cost.
    */
    int ted(const Tree& t1, const Tree& t2, int e);

    /**
     * Computes the Spine Edit Distance (SED) between a spine S1 from T1 and a spine S2 from T2.
     * 
     * A spine is a path that moves upwards in the tree.
     * 
     * 
     * @param t1 An ordered labeled rooted tree
     * @param t2 An ordered labeled rooted tree
     * @param s1 A spine from T1
     * @param s2 A spine from T2
     * @param td Tree edit distances needed to compute the edit distance for the two spines
    */
    int sed(const Tree& t1, const Tree& t2, const std::vector<int>& s1, const std::vector<int>& s2, const std::vector<std::vector<int>>& td);
}

#endif
#ifndef SAEEDSCHEME_H
#define SAEEDSCHEME_H

#include <tree.h>

namespace SaeedScheme {
    /**
     * Computes the Tree Edit Distance (TED) between T1 and T2 using a variant of the approximation scheme algorithm 
     * described by Saeed Seddighin and others in 2019 in the paper 1+ϵ Approximation of Tree Edit
     * Distance in Quadratic Time.
     * 
     * It required O(n^8) time. Though it can be improved with some of the ideas in the paper.

     * @param t1 An ordered labeled rooted tree
     * @param t2 An ordered labeled rooted tree
     * 
     * @returns An integer that represents the number of operations needed to transform t1 into t2.
     * Each operation has unit cost.
    */
    int ted(const Tree& t1, const Tree& t2);

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
     * @param rl1 A map to get the outermost right leaf for any node in T1
     * @param rl2 A map to get the outermost right leaf for any node in T2
     * @param d2 A map to get the depth for any node in T2
     * @param td Tree edit distances needed to compute the edit distance for the two spines. This table will
     * be updated with new computed values of ted.
    */
    void sed(
        const Tree& t1, 
        const Tree& t2, 
        const std::vector<int>& s1, 
        const std::vector<int>& s2,
        const std::vector<int>& rl1,
        const std::vector<int>& rl2,
        const std::vector<int>& d2,
        std::vector<std::vector<int>>& td
    );
}

#endif
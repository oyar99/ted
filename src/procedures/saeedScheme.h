#ifndef SAEEDSCHEME_H
#define SAEEDSCHEME_H

#include <tree.h>
#include <unordered_map>

namespace SaeedScheme {
    /**
     * A data structure that given two forests F1 and F2, computes the forest edit distance 
     * between any pair of subforests of F1 and F2 in O(1) after O(n^2) preprocessing
    */
    struct FEDDS {
        // Forest F definition
        Tree t1;
        int il;
        int ir;

        // Forest F' definition
        Tree t2;
        int jl;
        int jr;

        // collection of feddsk data structures
        std::unordered_map<int, FEDDSK> feds;

        // Approximation factor E
        int E;
        /**
         * Constructs FEDDS given two subforests F and F' in time O(n^2)
        */
        FEDDS(const Tree& t1, int il, int ir, const Tree& t2, int jl, int jr);

        /**
         * Answer queries of the form:
         * 
         * what is the FED between two subforests F(il, ir) and F'(jl, jr)?
         * 
         * It returns an approximate answer or returns -1 if it detects that FED is 
         * larger than K
        */
        int query(int il, int ir, int jl, int jr);
    };

    struct  FEDDSK {
        // Forest F definition
        Tree t1;
        int il;
        int ir;

        // Forest F' definition
        Tree t2;
        int jl;
        int jr;

        int k;

        // Additive error E
        int E;

        /**
         * Constructs FEDDSK given two subforests F and F' in time O(n^2)
        */
        FEDDSK(const Tree& t1, int il, int ir, const Tree& t2, int jl, int jr, int k, double E);

        /**
         * Answers queries of the form:
         * 
         * what is the FED between two subforests F(il, ir) and F'(jl, jr)?
         * 
         * It returns an approximate answer or returns -1 if it detects that FED is 
         * larger than K
        */
        int query(int il, int ir, int jl, int jr);
    };

    /**
     * Computes the Tree Edit Distance (TED) between T1 and T2 using the approximation scheme algorithm 
     * described by Saeed Seddighin and others in 2019 in the paper 1+ϵ Approximation of Tree Edit
     * Distance in Quadratic Time

     * @param t1 An ordered labeled rooted tree
     * @param t2 An ordered labeled rooted tree
     * 
     * @returns An integer that represents an approximation for the number of operations needed to transform t1 into t2.
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
     * @param td Tree edit distances needed to compute the edit distance for the two spines
    */
    int sed(const Tree& t1, const Tree& t2, const std::vector<int>& s1, const std::vector<int>& s2, const std::vector<std::vector<int>>& td);
}

#endif
#ifndef APPROXSCHEME_H
#define APPROXSCHEME_H

#include <tree.h>
#include <unordered_map>

namespace ApproxScheme {
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

        // collection of fed distances for subforests of F and F'
        // key is of the form ij
        std::unordered_map<std::string, std::vector<std::vector<int>>> feds;

        /**
         * Constructs FEDDSK given two subforests F and F' in time O(n^2)
        */
        FEDDSK(const Tree& t1, int il, int ir, const Tree& t2, int jl, int jr, int k, const std::vector<std::vector<int>>& td);

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

        /**
         * Constructs FEDDS given two subforests F and F' in time O(n^2)
        */
        FEDDS(const Tree& t1, int il, int ir, const Tree& t2, int jl, int jr, const std::vector<std::vector<int>>& td);

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
}

#endif
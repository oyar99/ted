#ifndef OURALGORITHM_H
#define OURALGORITHM_H

#include <tree.h>

namespace OurAlgorithm {
    /**
     * Computes the Tree Edit Distance (TED) between T1 and T2 using our own approximation scheme algorithm 

     * @param t1 An ordered labeled rooted tree
     * @param t2 An ordered labeled rooted tree
     * 
     * @returns An integer that represents the number of operations needed to transform t1 into t2.
     * Each operation has unit cost.
    */
    int ted(const Tree& t1, const Tree& t2);
}

#endif
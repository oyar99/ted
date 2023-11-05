#include <tree.h>
#include <ZhangShasha.h>
#include <saeedScheme.h>
#include <iostream>

int compute_ZhangShasha(const Tree& t1, const Tree& t2) {
    return ZhangShasha::ted(t1, t2);
}

int compute_SaeedScheme(const Tree& t1, const Tree& t2, int e) {
    return SaeedScheme::ted(t1, t2, e);
}

std::pair<std::string, std::string> get_input_trees() {
    std::string t1_preorder;
    std::string t2_preorder;

    std::getline(std::cin, t1_preorder);
    std::getline(std::cin, t2_preorder);

    return {t1_preorder, t2_preorder};
}

/**
 * 
 * Tree Edit Distance. Given two node-labeled rooted trees T and T' each of size at most n, what
 * is the minimum number of elementary operations needed to transform T into T'?
 * 
 * Theorem. 
 * Tree Edit Distance accepts a (1+ε)-approximation scheme that runs in O(n^2/ε^3) time.
*/
int main(int argc, char *argv[]) {
    /**
     * Input: 
     * 
     * The program receives two Trees T1 and T2 and returns a 
     * number d that indicates the number of elementary operations required to transform 
     * T1 into T2.
     * 
     * The program accepts the following arguments
     * 
     * -A indicates which algorithm should be used. Available options are:
     *      "Approx"
     * 
     *          This will run the default approximation scheme which implements the algorithm
     *          described in the paper 1+ϵ Approximation of Tree Edit Distance in Quadratic Time.
     *          By default, it will set ϵ to 1. That is, the answer will be at most 2 times the
     *          optimal.
     * 
     *          Time complexity: O(n^2/ε^3)
     * 
     *      "ZhangShasha"
     * 
     *          This will run an exact algorithm that uses dynamic programming to find a solution.
     *          This algorithm is one of the building blocks for the approximation scheme.
     *          If this option is used, the ε parameter is ignored.
     * 
     *          Time complexity: O(n^4)
     * 
     *      "TED"
     * 
     *          // TODO: Our version of TED
     * 
     * -E indicates the approximation factor to use for the approximation scheme. It should be a value
     * greater than zero.
     * 
     * The input should follow these rules.
     * 
     *      The input contains two trees T1 and T2 represented as strings that correspond
     *      to the pre-order traversal of T such that when we visit node u, we append 
     *      label(u) followed by a matching parenthesis that encloses the subtree rooted at u.
     * 
     *      The first line of the input is a string of size 3n where n corresponds to the number 
     *      of nodes in T1. This string is the pre-order traversal of T1 as explained above.
     * 
     *      The second line of the input is a string of size 3m where m corresponds to the number
     *      of nodes in T2. This string is the pre-order traversal of T2 as explained above.
     * 
     *      n and m are both at least 1.
     *      
     *      For instance:
     * 
     *      1(2(4())3(5())) is the pre-order traversal for the tree.
     * 
     *                        1
     *                       / \
     *                      /   \
     *                     2     3
     *                    /     /
     *                   4     5
     * 
     *      Note each integer represents a labeled node. As such, there might be duplicated integers
     *      in the string representation of the tree that actually correspond to different nodes.
     * 
    */

    const auto& input_trees = get_input_trees();

    Tree t1(input_trees.first);
    Tree t2(input_trees.second);

    if (argc <= 1) {
        throw std::invalid_argument("The algorithm procedure was not specified. Please read the documentation");
    }

    std::string algorithm(argv[1]);

    int d = -1;

    if (algorithm == "ZhangShasha") {
        d = compute_ZhangShasha(t1, t2);
    } else if (algorithm == "Approx") {
        int e = 1;
        if (argc >= 2) {
            std::string approx_factor(argv[2]);
            e = std::stoi(approx_factor);
        }

        d = compute_SaeedScheme(t1, t2, e);
    } else if (algorithm == "TED") {
        // no-op
    }

    std::cout << d << std::endl;
}
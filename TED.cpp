#include <tree.h>
#include <zhangShasha.h>
#include <saeedScheme.h>
#include <saeedSchemeOpt.h>
#include <iostream>

int compute_ZhangShasha(const Tree& t1, const Tree& t2) {
    return ZhangShasha::ted(t1, t2);
}

int compute_SaeedScheme(const Tree& t1, const Tree& t2) {
    return SaeedScheme::ted(t1, t2);
}

int compute_SaeedSchemeOpt(const Tree& t1, const Tree&t2) {
    return SaeedSchemeOpt::ted(t1, t2);
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
     *      "ZhangShasha"
     * 
     *          This will run an exact algorithm that uses dynamic programming to find a solution.
     *          This algorithm is one of the building blocks for the approximation scheme.
     * 
     *          Time complexity: O(n^4)
     * 
     *      "Saeed"
     * 
     *          This will run an exact algorithm that uses a variant of the algorithm described in the paper
     *          1+ϵ Approximation of Tree Edit Distance in Quadratic Time.
     * 
     *          Time complexity: O(n^6)
     * 
     * The input should follow these rules.
     * 
     *      The input contains two trees T1 and T2 represented as strings that correspond
     *      to the pre-order traversal of T such that when we visit node u, we append 
     *      label(u) followed by a matching parenthesis that encloses the subtree rooted at u.
     * 
     *      The first line of the input is the pre-order traversal of T1 as explained above.
     * 
     *      The second line of the input is the pre-order traversal of T2 as explained above.
     * 
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

    std::string algorithm(argc <= 1 ? "SaeedOpt" : argv[1]);

    int d = -1;

    if (algorithm == "ZhangShasha") {
        d = compute_ZhangShasha(t1, t2);
    } else if (algorithm == "Saeed") {
        d = compute_SaeedScheme(t1, t2);
    } else if (algorithm == "SaeedOpt") {
        d = compute_SaeedSchemeOpt(t1, t2);
    }

    std::cout << d << std::endl;
}
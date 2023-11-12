#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <unordered_set>

/**
 * Represents a node-labeled rooted tree data structure referred to as T.
 * 
 * Nodes have a unique id from 1 to n where n is the number of nodes in T.
 * Labels are not necessarily unique and are drawn from the alphabet of all integers.
 * 
 * This structure provides elementary operations on the tree T used as sub-routines by 
 * a variety of algorithms.
 * 
 * Other specific algorithms may be implemented in separate packages.
*/
struct Tree {
    // Adjacency list for T.
    // adj[u] corresponds to the children of u
    std::vector<std::vector<int>> adj;
    // Maps a node to its label.
    std::vector<int> labels;
    // Maps a node to its parent.
    std::vector<int> parent;

    // Id of the root node.
    int root;
    // Number of nodes in T.
    int n;

    /**
     * Constructs an empty tree
    */
    Tree();


    /**
     * Constructs T from the pre-order traversal string representation.
     * 
     * The pre-order traversal has additional parenthesis that enclose the sub-tree rooted at u
     * for all u.
     * 
     * The running time complexity is of the order O(n) where n corresponds to the number of nodes in T.
     * 
     * @param pre_order The string representation of the preorder traversal of T
     * 
     * @returns An ordered labeled rooted tree constructed from the given pre-order traversal
    */
    Tree(const std::string& pre_order);

    /**
     * Gets a preorder string unique representation of T in linear time.
     * For instance, the tree
     *          
     *                        2
     *                       / \
     *                      /   \
     *                     1     3
     *                    / \   / \
     *                   0   7 9   1
     *                      /
     *                     2 
     * 
     * has the following pre-order sequence:
     * 
     * 2(1(0()7(2()))3(9()1()))
     * 
     * @returns The preorder traversal of T
    */
    std::string pre_order() const;

    /**
     * Gets a preorder string unique representation of the tree rooted at node l up to node r
     * excluding nodes in the exclude set.
    */
    std::string pre_order(int l, int r, const std::unordered_set<int>& exclude) const;

    /**
     * Uses Heavy-light decomposition to return a set of vertex disjoint paths
     * from the tree T. It is guaranteed that any path from a leaf to the root
     * will go through at most O(lgn) paths from this set.
     * 
     * Returns ordered vectors with the paths. 
     * 
     * This decomposition takes linear time in the number of nodes in T.
     * 
     * @returns A collection of paths
    */
    std::vector<std::vector<int>> decompose() const;

    /**
     * Computes the leftmost leaf of each node u.
     * 
     * @returns A map where the leftmost leaf of each node can be retrieved
    */
    std::vector<int> leftmost() const;

    /**
     * Computes the keyroots_l of T.
     * 
     * The keyroots are the set of nodes with lowest id in the preorder traversal
     * among all other nodes that share the same leftmost leaf.
     * 
     *                        5
     *                       / \
     *                      /   \
     *                     1     3
     *                    / \   / \
     *                   0   7 9   4
     *                      /
     *                     6 
     * 
     * The keyroots of the above tree are {3, 4, 5, 7}.
     * 
     * These can be computed in linear time by a simple traversal of T.
     * 
     * @returns The keyroots of T for the leftmost leaves
    */
    std::vector<int> keyroots_l() const;

    /**
     * Computes the rightmost leaf of each node u.
     * 
     * @returns A map where the rightmost leaf of each node can be retrieved
    */
    std::vector<int> rightmost() const;

    /**
     * Computes the keyroots_r of T.
     * 
     * The keyroots are the set of nodes with lowest id in the preorder traversal
     * among all other nodes that share the same rightmost leaf.
     * 
     *                        5
     *                       / \
     *                      /   \
     *                     1     3
     *                    / \   / \
     *                   0   7 9   4
     *                      /
     *                     6 
     * 
     * The keyroots of the above tree are {0, 1, 5, 9}.
     * 
     * These can be computed in linear time by a simple traversal of T.
     * 
     * @returns The keyroots of T for the rightmost leaves
    */
    std::vector<int> keyroots_r() const;

    /**
     * Computes the depth of all nodes in the tree.
     * 
     * By definition the depth of the root node is 1.
    */
    std::vector<int> depth() const;

    /**
     * Gets the path upwards from node u to node v.
     *
     * If it is not possible to reach node v moving upwards, then returns an empty set.
    */
    std::vector<int> get_upwards_path(int u, int v) const;
};

#endif
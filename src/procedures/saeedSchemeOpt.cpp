#include <saeedSchemeOpt.h>
#include <zhangShasha.h>
#include <cmath>
#include <limits>
#include <cstdint>
#include <algorithm>
#include <assert.h>

SaeedSchemeOpt::FEDDS::FEDDS(
    const Tree& f1,
    const Tree& f2,
    const std::vector<std::vector<int>>& td
) : f1(f1), f2(f2) {
    std::vector<std::vector<int>> t = ZhangShasha::ted_complete(f1, f2);

    for (int i = 1; i <= f1.n; ++i) {
        for (int j = 1; j <= f2.n; ++j) {
            std::vector<std::vector<int>> fedij = ZhangShasha::fed_complete(f1, 1, i, f2, 1, j, t);
            feds.insert({ std::to_string(i) + std::to_string(j), fedij});
        }
    }
}

int SaeedSchemeOpt::FEDDS::query(
    int il,
    int ir,
    int jl,
    int jr
) {
    if (il > ir && jl > jr) {
        return 0;
    }

    if (il > ir) {
        return jr - jl + 1;
    }

    if (jl > jr) {
        return ir - il + 1;
    }

    std::string key = std::to_string(ir) + std::to_string(jr);

    return feds[key][il][jl];
}


int SaeedSchemeOpt::ted(const Tree& t1_or, const Tree& t2_or) {
    // Let us first add a dummy root on top each tree by enclosing its preorder traversal in a zero-labeled node
    Tree t1("0(" + t1_or.pre_order() + ")");
    Tree t2("0(" + t2_or.pre_order() + ")");

    int n = t1.n;
    int m = t2.n;

    std::vector<std::vector<int>> td(n + 1, std::vector<int>(m + 1, std::numeric_limits<std::int32_t>::max()));

    // We first decompose T1 and T2 into spines - paths that move upward in the tree
    std::vector<std::vector<int>> t1_spines = t1.decompose();
    std::vector<std::vector<int>> t2_spines = t2.decompose();

    std::vector<int> d1 = t1.depth();
    std::vector<int> d2 = t2.depth();

    std::vector<int> size_st1 = t1.size_subtrees();

    // Sort paths so we can iterate in bottom-up manner
    auto spine_comp = [&](const std::vector<int>& s1, const std::vector<int>& s2) {
        return s1[s1.size() - 1] > s2[s2.size() - 1];
    };

    std::sort(t1_spines.begin(), t1_spines.end(), spine_comp);
    std::sort(t2_spines.begin(), t2_spines.end(), spine_comp);

    std::vector<int> t1_rightmost = t1.rightmost();
    std::vector<int> t2_rightmost = t2.rightmost();

    for (auto const& s1: t1_spines) {
        for (auto const& s2: t2_spines) {
            SaeedSchemeOpt::sed(t1, t2, s1, s2, t1_rightmost, t2_rightmost, d1, d2, size_st1, td);
        }
    }

    return td[1][1];
}

void SaeedSchemeOpt::sed(
    const Tree& t1, 
    const Tree& t2, 
    const std::vector<int>& s1, 
    const std::vector<int>& s2,
    const std::vector<int>& rl1,
    const std::vector<int>& rl2,
    const std::vector<int>& d1,
    const std::vector<int>& d2,
    const std::vector<int>& size_st1,
    std::vector<std::vector<int>>& td
) {
    /**
     * Let us compute ted for two fixed nodes u and v in s1 and s2 respectively as follows.
     * 
     * First, we will assume the optimal answer is obtained by mapping u to v.
     * 
     * We will iterate over all uk in s1, and all vl in the subtree rooted at v and add these 4 parts
     * 
     * 1. Compute ted between nodes uk and vl
     * 2. Delete nodes in the path ul to uk and insert nodes in the path vj to vl
     * 3. Compute fed for remaining nodes in T1 and T2
     * 4. Compute the cost to transform u to v
    */

    auto cost = [&](int i, int j) {
        return t1.labels[i] == t2.labels[j] ? 0 : 1;
    };

    // Computes a new entire forest. The index of this forest may differ from indices in the original tree representation
    auto get_forest = [&](int i, int j, const std::vector<int>& s, const Tree& t) {
        // we want to generate a forest t[i, j] that doesn't include nodes in the path s
        std::unordered_set<int> exclude(s.begin(), s.end());

        return Tree(t.pre_order(i, j, exclude));
    };

    auto update_leaf = [&](int i, int j) {
        int L = cost(s1[i], s2[j]);

        if (rl1[s1[i]] == s1[i]) {
            // node ui is a leaf, so ted is simply the cost of relabeling ui and the size of
            // subtree rooted at vj
            td[s1[i]][s2[j]] = L + (rl2[s2[j]] - s2[j]);
        } else if (rl2[s2[j]] == s2[j]) {
            // node vj is a leaf, so ted is simply the cost of relabeling ui and the size of
            // subtree rooted at ui
            td[s1[i]][s2[j]] = L + (rl1[s1[i]] - s1[i]);
        }
    };

    if (s1.size() == 1 || s2.size() == 1) {
        for (int i = 0; i < s1.size(); ++i) {
            for (int j = 0; j < s2.size(); ++j) {
                update_leaf(i, j);
            }
        }

        return;
    }

    // Let us create a forest data structure to quickly return fed for any two proper subforests
    // One of these structures represent the forest on the left hand side of the spine, and the other one
    // the forest on the right hand side.
    Tree f1_l = get_forest(s1[s1.size() - 1], s1[0], s1, t1);
    Tree f1_r = get_forest(s1[0] + 1, t1.n, s1, t1);
    FEDDS fedds_r = FEDDS(f1_r, t2, td);

    for (int i = 0; i < s1.size(); ++i) {
        for (int j = 0; j < s2.size(); ++j) {
            int L = cost(s1[i], s2[j]);

            update_leaf(i, j);

            for (int k = 0; k < i; ++k) {
                Tree f1_l = get_forest(s1[i], s1[k] - 1, s1, t1);

                for (int l = s2[j] + 1; l < rl2[s2[j]] + 1; ++l) {
                    int R = (i - k - 1) + (d2[l] - d2[s2[j]] - 1);

                    Tree f2_l = get_forest(s2[j], l - 1, t2.get_upwards_path(l, s2[j]) /* l does not necessarily belong in s2 */, t2);

                    int z = (f1_l.n - size_st1[s1[k]]) + (d1[s1[k]] - d1[s1[0]] + 1) + (rl1[s1[k]] - s1[0]);
                    //assert(z >= 0);
                    int cl = ZhangShasha::fed(f1_l, 1, f1_l.n, f2_l, 1, f2_l.n, ZhangShasha::ted_complete(f1_l, f2_l));
                    int cr = fedds_r.query(rl1[s1[k]] - s1[0] + 1, rl1[s1[i]] - s1[0], rl2[l] + 1, rl2[s2[j]]);

                    int C = cl + cr;

                    td[s1[i]][s2[j]] = std::min(
                        td[s1[i]][s2[j]],
                        td[s1[k]][l] + R + C +  L
                    );
                }
            }
        }
    }
}
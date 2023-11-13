#include <saeedScheme.h>
#include <zhangShasha.h>
#include <cmath>
#include <limits>
#include <cstdint>
#include <algorithm>
#include <assert.h>

int SaeedScheme::ted(const Tree& t1_or, const Tree& t2_or) {
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
            SaeedScheme::sed(t1, t2, s1, s2, t1_rightmost, t2_rightmost, d2, td);
        }
    }

    return td[1][1];
}

void SaeedScheme::sed(
    const Tree& t1, 
    const Tree& t2, 
    const std::vector<int>& s1, 
    const std::vector<int>& s2,
    const std::vector<int>& rl1,
    const std::vector<int>& rl2,
    const std::vector<int>& d2,
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

    for (int i = 0; i < s1.size(); ++i) {
        for (int j = 0; j < s2.size(); ++j) {
            int L = cost(s1[i], s2[j]);

            if (rl1[s1[i]] == s1[i]) {
                // node ui is a leaf, so ted is simply the cost of relabeling ui and the size of
                // subtree rooted at vj
                td[s1[i]][s2[j]] = L + (rl2[s2[j]] - s2[j]);
                continue;
            }

            if (rl2[s2[j]] == s2[j]) {
                // node vj is a leaf, so ted is simply the cost of relabeling ui and the size of
                // subtree rooted at ui
                td[s1[i]][s2[j]] = L + (rl1[s1[i]] - s1[i]);
                continue;
            }

            for (int k = 0; k < i; ++k) {
                for (int l = s2[j] + 1; l < rl2[s2[j]] + 1; ++l) {
                    // At this point td[s1[k]][l] should already be solved
                    assert(td[s1[k]][l] != std::numeric_limits<std::int32_t>::max());

                    int R = (i - k - 1) + (d2[l] - d2[s2[j]] - 1);

                    Tree f1_l = get_forest(s1[i], s1[k] - 1, s1, t1);
                    Tree f1_r = get_forest(rl1[s1[k]] + 1, rl1[s1[i]], s1, t1);
                    Tree f2_l = get_forest(s2[j], l - 1, t2.get_upwards_path(l, s2[j]) /* l does not necessarily belong in s2 */, t2);
                    Tree f2_r = get_forest(rl2[l] + 1, rl2[s2[j]], t2.get_upwards_path(l, s2[j]) /* l does not necessarily belong in s2 */, t2);

                    int C = ZhangShasha::fed(f1_l, 1, f1_l.n, f2_l, 1, f2_l.n, ZhangShasha::ted_complete(f1_l, f2_l))
                                + ZhangShasha::fed(f1_r, 1, f1_r.n, f2_r, 1, f2_r.n, ZhangShasha::ted_complete(f1_r, f2_r));
                    td[s1[i]][s2[j]] = std::min(
                        td[s1[i]][s2[j]],
                        td[s1[k]][l] + R + C +  L
                    );
                }
            }
        }
    }
}
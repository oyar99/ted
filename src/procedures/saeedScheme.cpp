#include <saeedScheme.h>
#include <zhangShasha.h>
#include <cmath>
#include <limits>
#include <cstdint>

SaeedScheme::FEDDS::FEDDS(
    const Tree& t1,
    int il,
    int ir,
    const Tree& t2,
    int jl,
    int jr,
    const std::vector<std::vector<int>>& td
) : t1(t1), il(il), ir(ir), t2(t2), jl(jl), jr(jr) {
    int n = (ir-il+1)+(jr-jl+1);

    for (int k = 1; k <= n; k *= 2) {
        feds.insert({ k, FEDDSK(t1, il, ir, t2, jl, jr, k, td)});
    }
}

int SaeedScheme::FEDDS::query(
    int il,
    int ir,
    int jl,
    int jr
) {
    int n = (ir-il+1)+(jr-jl+1);

    for (int k = 1; k <= n; k *= 2) {
        int d = feds.at(k).query(il, ir, jl, jr);

        if (d >= 0) {
            return d;
        }
    }

    return -1;
}

SaeedScheme::FEDDSK::FEDDSK(
    const Tree& t1,
    int il,
    int ir,
    const Tree& t2,
    int jl,
    int jr,
    int k,
    const std::vector<std::vector<int>>& td
) : t1(t1), il(il), ir(ir), t2(t2), jl(jl), jr(jr), k(k) {
    if (k < 4) {
        return;
    }

    for (int i = 1; i <= ir-il+1; i += (k/4)) {
        for (int j = 1; j <= jr-jl+1; j += (k/4)) {
            std::vector<std::vector<int>> fedij = ZhangShasha::fed_complete(t1, il+i-1, ir, t2, jl+j-1, jr, td);
            feds.insert({ std::to_string(i) + std::to_string(j), fedij});
        }
    }
}

int SaeedScheme::FEDDSK::query(
    int il,
    int ir,
    int jl,
    int jr
) {
    // Find the index of the largest marked point in F less than or equal to il
    int i = ((4 * il)/ k) * k/4;
    // Find the index of the largest marked point in F' less than or equal to jl
    int j = ((4 * jl)/ k) * k/4;

    std::string key = std::to_string(i) + std::to_string(j); 

    if (feds.count(key) > 0) {
        int d = feds.at(key)[ir][jr];

        if (d >= 0) {
            return d;
        }
    }

    return -1;
}

int SaeedScheme::ted(const Tree& t1_or, const Tree& t2_or) {
    // Let us first add a dummy root on top each tree by enclosing its preorder traversal in a zero-labeled node
    Tree t1("0(" + t1_or.pre_order() + ")");
    Tree t2("0(" + t2_or.pre_order() + ")");

    int n = t1.n;
    int m = t2.n;

    std::vector<std::vector<int>> td(n + 1, std::vector<int>(m + 1, std::numeric_limits<std::int32_t>::max()));

    td[n][m] = 0;
    for (int i = n - 1; i >= 1; --i) {
        // deletions
        td[i][m] = td[i+1][m] + 1;
    }
    for (int j = m - 1; j >= 1; --j) {
        // insertions
        td[n][j] = td[n][j+1] + 1;
    }

    // We first decompose T1 and T2 into spines - paths that move upward in the tree
    std::vector<std::vector<int>> t1_spines = t1.decompose();
    std::vector<std::vector<int>> t2_spines = t2.decompose();

    std::vector<int> t1_rightmost = t1.rightmost();
    std::vector<int> t2_rightmost = t2.rightmost();

    std::vector<int> d2 = t2.depth();

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
    // Use wisely
    auto get_forest = [&](int i, int j, const std::vector<int>& s, const Tree& t) {
        // i and k are the indices of two nodes in T

        // we want to generate a forest that doesn't include nodes in the path s 
        // nor in the subtree rooted at s[j]
        return Tree(t.pre_order(i, j, std::unordered_set(s.begin(), s.end())));
    };

    for (int i = 0; i < s1.size(); ++i) {
        for (int j = 0; j < s2.size(); ++j) {
            for (int k = 0; k < i; ++k) {
                for (int l = s2[j] + 1; l < s2[rl2[j]] + 1; ++l) {
                    Tree f1l = get_forest(s1[i] + 1, s1[k] - 1, s1, t1);
                    Tree f1r = get_forest(rl1[s1[k]] + 1, rl1[s1[i]], s1, t1);
                    Tree f2l = get_forest(s2[j] + 1, l - 1, s2, t2);
                    Tree f2r = get_forest(rl2[l] + 1, rl2[s2[j]], s2, t2);

                    int R = (i - k - 1) + (d2[l] - j - 1);
                    int C = ZhangShasha::fed(f1l, 1, f1l.n, f2l, 1, f2l.n, td) + ZhangShasha::fed(f1r, 1, f1r.n, f2r, 1, f2r.n, td);
                    int L = cost(s1[i], s2[j]);
                    td[s1[i]][s2[j]] = std::min(
                        td[s1[i]][s2[j]],
                        td[s1[k]][l] + R + C +  L
                    );
                }
            }
        }
    }
}
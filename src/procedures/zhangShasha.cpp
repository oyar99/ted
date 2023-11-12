#include <zhangShasha.h>
#include <algorithm>

int min(int a, int b, int c);

int ZhangShasha::ted(const Tree& t1, const Tree& t2) {
    std::vector<std::vector<int>> ted = ZhangShasha::ted_complete(t1, t2);

    return ted[1][1];
}

std::vector<std::vector<int>> ZhangShasha::ted_complete(const Tree& t1, const Tree& t2) {
    int n = t1.n;
    int m = t2.n;

    std::vector<int> t1_keyroots = t1.keyroots_r();
    std::reverse(t1_keyroots.begin(), t1_keyroots.end());
    std::vector<int> t2_keyroots = t2.keyroots_r();
    std::reverse(t2_keyroots.begin(), t2_keyroots.end());

    std::vector<int> t1_rightmost = t1.rightmost();
    std::vector<int> t2_rightmost = t2.rightmost();

    // use tabulation for computing tree edit distance - TED
    // td[i][j] corresponds to the TED between the subtrees T1 rooted at i and T2 rooted at j
    //
    // td[i][j] = min(
    //      fd[i+1][j] + 1,
    //      fd[i][j+1] + 1,
    //      fd[i+1][j+1] + cost of relabeling T1[i] to T2[j],
    // );
    std::vector<std::vector<int>> td(n + 1, std::vector<int>(m + 1, -1));

    // use tabulation for computing forest edit distance - FED
    // fd[i][j] corresponds to the FED between the sub-forests T1(i, rightmost(k)) and T2(j, rightmost(l)) for fixed
    // values of k and l.
    //
    // fd[i][j] = td[i][j] for trees, Otherwise it follows that:
    //
    // fd[i][j] = min(
    //      fd[i+1][j] + 1,
    //      fd[i][j+1] + 1,
    //      fd[rightmost(i) + 1][rightmost(j) + 1] + td[i][j]             
    // );
    std::vector<std::vector<int>> fd(n + 2, std::vector<int>(m + 2));

    auto cost = [&](int i, int j) {
        return t1.labels[i] == t2.labels[j] ? 0 : 1;
    };

    for (int k: t1_keyroots) {
        for (int l: t2_keyroots) {
            fd[t1_rightmost[k] + 1][t2_rightmost[l] + 1] = 0;
            for (int i = t1_rightmost[k]; i >= k; --i) {
                // deletions
                fd[i][t2_rightmost[l]+1] = fd[i+1][t2_rightmost[l]+1] + 1;
            }
            for (int j = t2_rightmost[l]; j >= l; --j) {
                // insertions
                fd[t1_rightmost[k]+1][j] = fd[t1_rightmost[k]+1][j+1] + 1;
            }
            for (int i = t1_rightmost[k]; i >= k; --i) {
                for (int j = t2_rightmost[l]; j >= l; --j) {
                    if (t1_rightmost[i] == t1_rightmost[k] && t2_rightmost[j] == t2_rightmost[l]) {
                        fd[i][j] = min(
                            fd[i+1][j] + 1, // insert
                            fd[i][j+1] + 1, // delete
                            fd[i+1][j+1] + cost(i, j) // relabel
                        );
                        td[i][j] = fd[i][j];
                    } else {
                        fd[i][j] = min(
                            fd[i+1][j] + 1, // insert
                            fd[i][j+1] + 1, // delete
                            fd[t1_rightmost[i] + 1][t2_rightmost[j]+1] + td[i][j] // relabel
                        );
                    }
                }
            }
        }
    }

    return td;
}

int ZhangShasha::fed(const Tree& t1, int il, int ir, const Tree& t2, int jl, int jr, const std::vector<std::vector<int>>& td) {
    std::vector<std::vector<int>> ted = ZhangShasha::fed_complete(t1, il, ir, t2, jl, jr, td);

    return ted[il][jl];
}

std::vector<std::vector<int>> ZhangShasha::fed_complete(const Tree& t1, int il, int ir, const Tree& t2, int jl, int jr, const std::vector<std::vector<int>>& td) {
    int n = t1.n;
    int m = t2.n;

    // use tabulation for computing forest edit distance - FED
    // fd[i][j] corresponds to the FED between the sub-forests T1(i, rightmost(k)) and T2(j, rightmost(l)) for fixed
    // values of k and l.
    //
    // fd[i][j] = td[i][j] for trees, Otherwise it follows that:
    //
    // fd[i][j] = min(
    //      fd[i+1][j] + 1,
    //      fd[i][j+1] + 1,
    //      fd[rightmost(i) + 1][rightmost(j) + 1] + td[i][j]             
    // );
    std::vector<int> t1_rightmost = t1.rightmost();
    std::vector<int> t2_rightmost = t2.rightmost();

    // Recompute rightmost leaf for nodes based on the intervals
    for (int i = il; i <= ir; ++i) {
        t1_rightmost[i] = std::min(t1_rightmost[i], ir);
    }

    for (int j = jl; j <= jr; ++j) {
        t1_rightmost[j] = std::min(t1_rightmost[j], jr);
    }

    std::vector<std::vector<int>> fd(n + 2, std::vector<int>(m + 2, -1));
    fd[ir+1][jr+1] = 0;

    auto cost = [&](int i, int j) {
        return t1.labels[i] == t2.labels[j] ? 0 : 1;
    };

    for (int i = ir; i >= il; --i) {
        // deletions
        fd[i][jr+1] = fd[i+1][jr+1] + 1;
    }
    for (int j = jr; j >= jl; --j) {
        // insertions
        fd[ir+1][j] = fd[ir+1][j+1] + 1;
    }
    for (int i = ir; i >= il; --i) {
        for (int j = jr; j >= jl; --j) {
            fd[i][j] = min(
                fd[i+1][j] + 1, // insert
                fd[i][j+1] + 1, // delete
                fd[t1_rightmost[i]+1][t2_rightmost[j]+1] + td[i][j] // relabel
            );
        }
    }

    return fd;
}

int min(int a, int b, int c) {
    return std::min(std::min(a, b), c);
}
#include <zhangShasha.h>
#include <algorithm>

int min(int a, int b, int c);

int ZhangShasha::ted(const Tree& t1, const Tree& t2) {
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
    std::vector<std::vector<int>> td(n + 1, std::vector<int>(m + 1));

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
                fd[i][t2_rightmost[l] + 1] = fd[i+1][t2_rightmost[l] + 1] + 1;
            }
            for (int j = t2_rightmost[l]; j >= l; --j) {
                // insertions
                fd[t1_rightmost[k] + 1][j] = fd[t1_rightmost[k] + 1][j+1] + 1;
            }
            for (int i = t1_rightmost[k]; i >= k; --i) {
                for (int j = t2_rightmost[l]; j >= l; --j) {
                    if (t1_rightmost[i] == t1_rightmost[k] && t2_rightmost[j] == t2_rightmost[l]) {
                        fd[i][j] = min(
                            fd[i+1][j] + 1, // delete
                            fd[i][j+1] + 1, // insert
                            fd[i+1][j+1] + cost(i, j) // relabel
                        );
                        td[i][j] = fd[i][j];
                    } else {
                        fd[i][j] = min(
                            fd[i+1][j] + 1, // delete
                            fd[i][j+1] + 1, // insert
                            fd[t1_rightmost[i] + 1][t2_rightmost[j] + 1] + td[i][j] // relabel
                        );
                    }
                }
            }
        }
    }

    return td[1][1];
}

int ZhangShasha::fed(const Tree& t1, const Tree& t2, const std::vector<std::vector<int>>& ted, int i, int j) {
    return 0;
}

int min(int a, int b, int c) {
    return std::min(std::min(a, b), c);
}
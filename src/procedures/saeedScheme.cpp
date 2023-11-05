#include <saeedScheme.h>

int SaeedScheme::ted(const Tree& t1, const Tree& t2, int e) {
    int n = t1.n;
    int m = t2.n;

    std::vector<std::vector<int>> td(n + 1, std::vector<int>(m + 1));

    // We first decompose T1 and T2 into spines - paths that move upward in the tree
    std::vector<std::vector<int>> t1_spines = t1.decompose();
    std::vector<std::vector<int>> t2_spines = t2.decompose();

    for (auto const& s1: t1_spines) {
        for (auto const& s2: t2_spines) {
            SaeedScheme::sed(t1, t2, s1, s2, td);
        }
    }

    return td[1][1];
}

int SaeedScheme::sed(
    const Tree& t1, 
    const Tree& t2, 
    const std::vector<int>& s1, 
    const std::vector<int>& s2, 
    const std::vector<std::vector<int>>& td
) {
    return 0;
}
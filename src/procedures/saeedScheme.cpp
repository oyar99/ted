#include <saeedScheme.h>
#include <cmath>

SaeedScheme::FEDDS::FEDDS(
    const Tree& t1,
    int il,
    int ir,
    const Tree& t2,
    int jl,
    int jr
) : t1(t1), il(il), ir(ir), t2(t2), jl(jl), jr(jr) {
    double er = .25f;

    int n = t1.n + t2.n;

    for (int k = 1; k <= n; k *= 2) {
        feds[k] = FEDDSK(t1, il, ir, t2, jl, jr, k, er);
    }
}

int SaeedScheme::FEDDS::query(
    int il,
    int ir,
    int jl,
    int jr
) {
    int n = t1.n + t2.n;

    for (int k = 1; k <= n; k *= 2) {
        int d = feds[k].query(il, ir, jl, jr);

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
    double E
) : t1(t1), il(il), ir(ir), t2(t2), jl(jl), jr(jr), k(k), E(E) {
    int n = t1.n;
    int m = t2.n;

    for (int i = 1; i <= n; i += (i + std::floor(k * E))) {
        for (int j = 1; j <= m; j += (j + std::floor(k * E))) {
            
        }
    }
}

int SaeedScheme::FEDDSK::query(
    int il,
    int ir,
    int jl,
    int jr
) {
    return 0;
}

int SaeedScheme::ted(const Tree& t1, const Tree& t2) {
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
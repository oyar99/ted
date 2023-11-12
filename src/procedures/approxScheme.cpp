#include <approxScheme.h>
#include <zhangShasha.h>

ApproxScheme::FEDDS::FEDDS(
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

int ApproxScheme::FEDDS::query(
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

ApproxScheme::FEDDSK::FEDDSK(
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

int ApproxScheme::FEDDSK::query(
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

int ApproxScheme::ted(const Tree& t1_or, const Tree& t2_or) {
    return 0;
}

void ApproxScheme::sed(
    const Tree& t1, 
    const Tree& t2, 
    const std::vector<int>& s1, 
    const std::vector<int>& s2,
    const std::vector<int>& rl1,
    const std::vector<int>& rl2,
    const std::vector<int>& d2,
    std::vector<std::vector<int>>& td
) {
}
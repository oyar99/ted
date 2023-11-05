#include <tree.h>
#include <functional>
#include <unordered_set>

Tree::Tree(const std::string& pre_order) {
    if (pre_order.size() == 0) {
        root = -1;
        return;
    }

    // This is an upper bound on the expected number of nodes in T
    // Since we do not know the actual number
    n = pre_order.size() / 3;

    // node ids are one-indexed
    // adj[0] is a dummy root - not actually present in the tree
    adj = std::vector<std::vector<int>>(n + 1);
    parent = std::vector<int>(n + 1);
    labels = std::vector<int>(n + 1);
    root = 1; // There's at least one node which will be the root

    int u = 0, i = 0;
    int idx = 1;

    auto is_parenthesis = [](const char& c) {
        return c == '(' || c == ')';
    };

    while (i < pre_order.size()) {
        if (!is_parenthesis(pre_order[i])) {
            // We are seeing a new node
            std::string label;

            while (!is_parenthesis(pre_order[i])) {
                label += pre_order[i++];
            }

            adj[u].push_back(idx);
            parent[idx] = u; // current pointer is the parent of u
            u = idx; // move pointer to this node

            labels[idx++] = std::stoi(label); // map node to its label
        } else if (pre_order[i++] == ')') {
            // We will go up in the tree
            u = parent[u];
        }
    }

    // shrunk vectors to fit actual number of nodes in T
    n = idx - 1;

    adj = std::vector<std::vector<int>>(adj.begin(), adj.begin() + idx);
    parent = std::vector<int>(parent.begin(), parent.begin() + idx);
    labels = std::vector<int>(labels.begin(), labels.begin() + idx);
}

std::string Tree::pre_order() const {
    if (root < 0) {
        return std::string();
    }

    std::string pre_order;

    std::function<void(int)> pre_order_inner = [&](int u) {
        pre_order += std::to_string(labels[u]);
        pre_order += "(";

        for (int v: adj[u]) {
            pre_order_inner(v);
        }

        pre_order += ")";
    };

    pre_order_inner(root);

    return pre_order;
}

std::vector<std::vector<int>> Tree::decompose() const {
    // Let us first do a depth first traversal of the tree where
    // we compute size(u) for all u. Size(u) is defined as the number
    // of nodes in the sub-tree rooted at u plus u itself.

    std::vector<int> size(n + 1);

    std::function<void(int)> dfs = [&](int u) {
        size[u] = 1;
        
        for (int v: adj[u]) {
            dfs(v);
            size[u] += size[v];
        }
    };

    dfs(root);

    std::vector<std::vector<int>> paths;
    std::unordered_set<int> covered;

    // For each node u such that size(u) < size(v)/2 for all children u of v
    // we will start a path moving upwards until we either go through a light edge or reach the root node.
    for (int i = 1; i <= n; ++i) {
        int u = i;
        if (covered.count(u) > 0) {
            continue;
        }

        bool should_pick = true;

        for (int v: adj[u]) {
            if (size[v] >= (size[u] + 1) / 2) {
                should_pick = false;
                break;
            }
        }

        if (should_pick) {
            // start a path upwards from u
            std::vector<int> path;

            // We will continue our path as long as we haven't reached the root node or the edge between parent[u]->u is heavy
            while (u != 0) {
                path.push_back(u);
                covered.insert(u);

                if (size[u] < (size[parent[u]] + 1) / 2) {
                    break;
                }

                u = parent[u];
            }

            paths.push_back(path);
        }
    }

    return paths;
}

std::vector<int> Tree::leftmost() const {
    // We will first compute the leftmost node for each node u
    std::vector<int> ll(n + 1);

    std::function<void(int)> dfs = [&](int u) {
        ll[u] = u;

        for (int i = adj[u].size() - 1; i >= 0; --i) {
            int v = adj[u][i];
            dfs(v);
            ll[u] = ll[v];
        }
    };

    dfs(root);

    return ll;
}

std::vector<int> Tree::keyroots_l() const {
    std::vector<int> ll = leftmost();

    std::unordered_set<int> r;
    std::vector<int> keyroots;

    for (int u = 1; u <= n; ++u) {
        int l = ll[u];

        if (r.count(l) <= 0) {
            r.insert(l);
            keyroots.push_back(u);
        }
    }

    return keyroots;
}

std::vector<int> Tree::rightmost() const {
    // We will first compute the rightmost node for each node u
    std::vector<int> rl(n + 1);

    std::function<void(int)> dfs = [&](int u) {
        rl[u] = u;

        for (int v: adj[u]) {
            dfs(v);
            rl[u] = rl[v];
        }
    };

    dfs(root);

    return rl;
}

std::vector<int> Tree::keyroots_r() const {
    std::vector<int> rl = rightmost();

    std::unordered_set<int> r;
    std::vector<int> keyroots;

    for (int u = 1; u <= n; ++u) {
        int l = rl[u];

        if (r.count(l) <= 0) {
            r.insert(l);
            keyroots.push_back(u);
        }
    }

    return keyroots;
}
#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"

typedef unsigned uint;

template <typename T>
class TrieNode {
public:
    T item;

    TrieNode() = default;

    TrieNode(const T &item) : item(item) {
    }

    TrieNode<T> *create_child(const T &child_item) {
        auto *child = new TrieNode<T>(child_item);
        m_children[child->item] = child;
        return child;
    }

    bool has_child(const T &child_item) {
        return m_children.contains(child_item);
    }

    TrieNode<T> *get_child(const T &child_item) {
        if (not has_child(child_item))
            return nullptr;
        return m_children[child_item];
    }

    TrieNode<T> *get_or_create_child(const T &child_item) {
        if (has_child(child_item))
            return get_child(child_item);
        return create_child(child_item);
    }

    size_t get_number_of_children() {
        return m_children.size();
    }

    TrieNode<T> *erase_child(const T &child_item) {
        auto child = get_child(child_item);
        m_children.erase(child_item);
        return child;
    }

    void delete_child(const T &child_item) {
        auto child = erase_child(child_item);
        delete child;
    }

    ~TrieNode() {
        for (auto& [key, child] : m_children)
            delete child;
    }

private:
    map<T, TrieNode *> m_children;
};

template <typename Container, typename Element>
class Trie {
protected:
    TrieNode<char> *root;

public:
    Trie() {
        root = new TrieNode<Element>();
    }

    void add(Container &elements) {
        TrieNode<Element> *node = root;
        for (Element &el : elements)
            node = node->get_or_create_child(el);
    }

    bool contains(Container &elements) {
        TrieNode<Element> *node = root;
        for (Element &el : elements) {
            if (not node->has_child(el))
                return false;
            node = node->get_child(el);
        }
        return true;
    }

    void erase(Container &elements) {
        TrieNode<Element> *node = root;
        vector<TrieNode<Element> *> nodes;

        for (Element &el : elements) {
            node = node->get_child(el);
            nodes.push_back(node);
        }

        auto it = nodes.rbegin() + 1;
        for ( ; it != nodes.rend(); it++)
            if ((*it)->get_number_of_children() == 2)
                break;
        (*it)->delete_child((*(it - 1))->item);
    }
};

int main() { _
    Trie<string, char> trie;
    string bingos = "bingos", bindo = "bindo";
    trie.add(bingos);
    dbg(trie.contains(bingos));
    trie.add(bindo);
    dbg(trie.contains(bingos));
    dbg(trie.contains(bindo));
    trie.erase(bindo);
    dbg(trie.contains(bingos));
    dbg(trie.contains(bindo));
    
    return 0;
}

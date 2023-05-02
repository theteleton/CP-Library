#include <iostream>
#include <vector>

template<typename T>
class node {
public:
    node *left;
    node *right;
    T value;

    node() {
        this->value = 0;
        this->left = NULL;
        this->right = NULL;
    }

    node(T value, node* left, node* right) {
        this->value = value;
        this->left = left;
        this->right = right;
    }
};

template<typename T>
class persistentTree {
public:
    std::vector<T> v;
    std::vector<node<T> *> roots;

    persistentTree(node<T> *root, std::vector<T> *numbers) {
        std::vector<node<T> *> vec;
        vec.push_back(root);
        this->roots = vec;
        this->v = *numbers;
    }

    void build(node<T> *current_node, int left_index, int right_index) {
        if (left_index == right_index) {
            current_node->value = this->v[left_index];
            return;
        }


        current_node->left = new node<T>();
        current_node->right = new node<T>();
        build(current_node->left, left_index, (left_index + right_index) / 2);
        build(current_node->right, (left_index + right_index) / 2 + 1, right_index);
        current_node->value = current_node->left->value + current_node->right->value;
        return;
    }

    void update(node<T>* current_node, T value, int position, int left_index, int right_index) {
        if (left_index > position || right_index < position) {
            return;
        }

        if (left_index == right_index) {
            current_node->value = value;
            return;
        }

        if (position <=  (left_index + right_index) / 2) {
            current_node->left = new node<T>(current_node->left->value, current_node->left->left, current_node->left->right);
            update(current_node->left, value, position, left_index, (left_index + right_index) / 2);
        } else {
            current_node->right = new node<T>(current_node->right->value, current_node->right->left, current_node->right->right);
            update(current_node->right, value, position, (left_index + right_index) / 2 + 1, right_index);
        }

        current_node->value = current_node->left->value + current_node->right->value;
    }

    T query(node<T> *current_node, int range_left, int range_right, int left_index, int right_index) {
        if ((left_index > range_right) || (right_index < range_left)) {
            return 0;
        }

        if ((left_index >= range_left) && (right_index <= range_right)) {
            return current_node->value;
        }

        return query(current_node->left, range_left, range_right, left_index, (left_index + right_index) / 2) + query(current_node->right, range_left, range_right, (left_index + right_index) / 2 + 1, right_index);
    }

    void addTree(int k) {
        this->roots.push_back(new node<T>(this->roots[k]->value, this->roots[k]->left, this->roots[k]->right));
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    int n, q;
    std::cin >> n >> q;

    std::vector<long long> v;
    v.resize(n);

    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }

    node<long long> *root = new node<long long>();
    persistentTree<long long> *obj = new persistentTree<long long>(root, &v);
    obj->build(obj->roots[0], 0, n - 1);
    for (int i = 0; i < q; i++) {
        int t;
        std::cin >> t;

        if (t == 1) {
            int k, a, x;
            std::cin >> k >> a >> x;
            a--;
            k--;
            obj->update(obj->roots[k], x, a, 0, n - 1);
        } else if (t == 2) {
            int k, a, b;
            std::cin >> k >> a >> b;
            k--;
            a--;
            b--;
            std::cout << obj->query(obj->roots[k], a, b, 0, n - 1) << "\n";
        } else {
            int k;
            std::cin >> k;
            k--;
            obj->addTree(k);
        }
    }
    return 0;
}
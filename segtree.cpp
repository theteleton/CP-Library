#include <iostream>
#include <vector>

template<typename T>
class node {
public:
    T value;
    node* left;
    node* right;

    node() {
        this->value = 0;
        this->left = NULL;
        this->right = NULL;
    }
};

template<typename T>
class segmentTree {
public:

    node<T>* root;
    std::vector<T> numbers;

    segmentTree(node<T> &root, std::vector<T> &numbers) {
        this->root = root;
        this->numbers = numbers;
    };

    void build(node<T>*, int, int) {};
    void update(node<T>*, int, int, int, int) {};
    T query(node<T>*, int, int, int, int) {};
};

template<typename T>
void segmentTree<T>::build(node<T>* current_node, int left_index, int right_index) {
    if (left_index == right_index) {
        current_node->value = this->numbers[left_index];
        return;
    }

    current_node->left = new node<T>();
    current_node->right = new node<T>();
    segmentTree<T>::build(current_node->left, left_index, (left_index + right_index) / 2);
    segmentTree<T>::build(current_node->right, (left_index + right_index) / 2 + 1, right_index);
    current_node->value = current_node->left.value + current_node->right.value;
    return;
}

template<typename T>
void segmentTree<T>::update(node<T>* current_node, int value, int position, int left_index, int right_index) {
    if (left_index == right_index) {
        current_node->value = value;
        return;
    }

    if ((position > right_index) || (position < left_index)) {
        return;
    }

    segmentTree<T>::update(current_node->left, value, position, left_index, (left_index + right_index) / 2);
    segmentTree<T>::update(current_node->right, value, position, (left_index + right_index) / 2 + 1, right_index);
    current_node->value = current_node->left.value + current_node->right.value;
    return;
}

template<typename T>
T segmentTree<T>::query(node<T> * current_node, int range_left, int range_right, int left_index, int right_index) {
    if ((left_index > range_right) || (right_index < left_index)) {
        return 0;
    }

    return segmentTree<T>::query(current_node->left, range_left, range_right, left_index, (left_index + right_index) / 2) + segmentTree<T>::query(current_node->left, range_left, range_right, (left_index + right_index) / 2 + 1, right_index);
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
 
    segmentTree<long long>* obj = new segmentTree<long long>(*(new node<long long>()), v);
    obj->build(obj->root, 0, n - 1);

    for (int i = 0; i < q; i++) {
        int t;
        std::cin >> t;
        if (t == 1) {
            int a, b;
            std::cin >> a >> b;
            a--;
 
            obj->update(obj->root, b, a, 0, n -1);
        } else {
            int a, b;
            std::cin >> a >> b;
            a--;
            b--;
            std::cout << obj->query(obj->root, a, b, 0, n - 1) << '\n';
        }
        
    }
    return 0;
}
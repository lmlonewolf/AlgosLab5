#include "Header.h"


void print_vector(const std::vector<int>& vec) {
    for (const auto& el : vec)
        std::cout << el << ' ';
}
void print_matrix(const std::vector<std::vector<int>>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << "Level " << i + 1 << ": ";
        for (const auto& el : vec[i])
            std::cout << el << ' ';
        std::cout << std::endl;
    }
}



Node::Node(int val) {
    value = val;
    sub_tree_min = val;
    sub_tree_max = val;
    sub_tree_sum = val;
}

void Node::update_node() {
    sub_tree_min = value;
    sub_tree_max = value;
    sub_tree_sum = value;
    int left_height = 0;
    int right_height = 0;

    if (left) {
        sub_tree_min = std::min(sub_tree_min, left->sub_tree_min);
        sub_tree_max = std::max(sub_tree_max, left->sub_tree_max);
        sub_tree_sum += left->sub_tree_sum;
        left_height = left->height;
    }
    if (right) {
        sub_tree_min = std::min(sub_tree_min, right->sub_tree_min);
        sub_tree_max = std::max(sub_tree_max, right->sub_tree_max);
        sub_tree_sum += right->sub_tree_sum;
        right_height = right->height;
    }
    height = 1 + std::max(left_height, right_height);
}



BinaryTree::BinaryTree() : root(nullptr) {}
BinaryTree::~BinaryTree() {
    clear(root);
}
void BinaryTree::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}


void BinaryTree::update_metrics(Node* node) {
    if (!node)
        return;

    update_metrics(node->left);
    update_metrics(node->right);

    node->update_node();
}
void BinaryTree::insert(int val) {
    if (!root) {
        root = new Node(val);
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (!curr->left) {
            curr->left = new Node(val);
            break;
        }
        else
            q.push(curr->left);

        if (!curr->right) {
            curr->right = new Node(val);
            break;
        }
        else
            q.push(curr->right);
    }
    update_metrics(root);
}

void BinaryTree::print(Node* node, int space) const {
	if (!node)
		return;
	space++;
	print(node->right, space);
	std::cout << std::endl;
	for (int i = 0; i < space; ++i)
		std::cout << '\t';
	std::cout << node->value << std::endl;
	print(node->left, space);
}
void BinaryTree::print() const {
    print(root, 0);
    std::cout << std::endl;
}


void BinaryTree::preorder(Node* node, std::vector<int>& vec) const {
    if (!node)
        return;
    vec.push_back(node->value);
    preorder(node->left, vec);
    preorder(node->right, vec);
}
std::vector<int> BinaryTree::preorder() const {
    std::vector<int> vec;
    preorder(root, vec);
    return vec;
}

void BinaryTree::inorder(Node* node, std::vector<int>& vec) const {
    if (!node)
        return;
    inorder(node->left, vec);
    vec.push_back(node->value);
    inorder(node->right, vec);
}
std::vector<int> BinaryTree::inorder() const {
    std::vector<int> vec;
    inorder(root, vec);
    return vec;
}

void BinaryTree::postorder(Node* node, std::vector<int>& vec) const {
    if (!node)
        return;
    postorder(node->left, vec);
    postorder(node->right, vec);
    vec.push_back(node->value);
}
std::vector<int> BinaryTree::postorder() const {
    std::vector<int> vec;
    postorder(root, vec);
    return vec;
}

void BinaryTree::level_order(Node* node, std::vector<std::vector<int>>& vec, int level) const {
    if (!node)
        return;
    if (level == vec.size())
        vec.push_back(std::vector<int>());

    vec[level].push_back(node->value);
    level_order(node->left, vec, level + 1);
    level_order(node->right, vec, level + 1);
}
std::vector<std::vector<int>> BinaryTree::level_order() const {
    std::vector<std::vector<int>> vec;
    level_order(root, vec, 0);
    return vec;
}


std::vector<int> BinaryTree::get_count_nodes_on_levels() const {
    std::vector<int> vec;
    for (const auto& el : level_order())
        vec.push_back(el.size());
    return vec;
}

int BinaryTree::get_min() const {
    if (root)
        return root->sub_tree_min;
    return 0;
}
int BinaryTree::get_max() const {
    if (root)
        return root->sub_tree_max;
    return 0;
}

void BinaryTree::get_count_leaves(Node* node, int& count) const {
    if (!node)
        return;
    if (node->left == nullptr && node->right == nullptr) {
        count++;
        return;
    }
    get_count_leaves(node->left, count);
    get_count_leaves(node->right, count);
}
int BinaryTree::get_count_leaves() const {
    int count = 0;
    get_count_leaves(root, count);
    return count;
}

int BinaryTree::get_sum() const {
    if (root)
        return root->sub_tree_sum;
    return 0;
}

void BinaryTree::get_sum_ways(Node* node, int current_sum, int& res) const {
    if (!node)
        return;

    current_sum += node->value;
    if (node->left == nullptr && node->right == nullptr) {
        res += current_sum;
        return;
    }

    get_sum_ways(node->left, current_sum, res);
    get_sum_ways(node->right, current_sum, res);
}
int BinaryTree::get_sum_ways() const {
    int res = 0;
    get_sum_ways(root, 0, res);
    return res;
}

int BinaryTree::get_height() const {
    if (root)
        return root->height;
    return 0;
}

std::vector<int> BinaryTree::longest_way(Node* node) const {
    if (!node)
        return std::vector<int>();

    std::vector<int> vec;
    int left_h = node->left ? node->left->height : 0;
    int right_h = node->right ? node->right->height : 0;

    if (left_h > right_h)
        vec = longest_way(node->left);
    else
        vec = longest_way(node->right);

    vec.insert(vec.begin(), node->value);
    return vec;

}
std::vector<int> BinaryTree::longest_way() const {
    return longest_way(root);
}

std::vector<int> BinaryTree::left_view() const {
    std::vector<int> res;
    auto vec = level_order();

    for (const auto& el : vec)
        res.push_back(el.back());

    return res;
}
std::vector<int> BinaryTree::right_view() const {
    std::vector<int> res;
    auto vec = level_order();

    for (const auto& el : vec)
        res.push_back(el[0]);

    return res;
}

std::vector<int> BinaryTree::sum_on_levels() const {
    std::vector<int> res;
    auto vec = level_order();
    for (int i = 0; i < vec.size(); i++) {
        res.push_back(0);
        for (const auto& el : vec[i])
            res[i] += el;
    }

    return res;
}
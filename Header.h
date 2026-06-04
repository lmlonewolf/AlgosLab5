#include <queue> 
#include <vector> 
#include <iostream>
#include <algorithm>


struct Node {
    int value;
    Node* left = nullptr;
    Node* right = nullptr;

    int sub_tree_min;
    int sub_tree_max;
    int sub_tree_sum;
    int height = 1;

    Node(int val);
    void update_node();
};



class BinaryTree {
    Node* root = nullptr;

    void clear(Node* node);
    void update_metrics(Node* node);
	void print(Node* node, int space) const;

    void preorder(Node* node, std::vector<int>& vec) const;
    void inorder(Node* node, std::vector<int>& vec) const;
    void postorder(Node* node, std::vector<int>& vec) const;
    void level_order(Node* node, std::vector<std::vector<int>>& vec, int level) const;

    void get_count_leaves(Node* node, int& count) const;
    void get_sum_ways(Node* node, int current_sum, int& res) const;
    std::vector<int> longest_way(Node* node) const;


public:
    BinaryTree();
    ~BinaryTree();

    void print() const;
    void insert(int val);

    // Обязательная часть
    std::vector<int> preorder() const;
    std::vector<int> inorder() const;
    std::vector<int> postorder() const;
    std::vector<std::vector<int>> level_order() const;

    // Вариативная часть
    std::vector<int> get_count_nodes_on_levels() const;
    int get_min() const;
    int get_max() const;
    int get_count_leaves() const;
    int get_sum() const;
    int get_sum_ways() const;
    int get_height() const;
    std::vector<int> longest_way() const;
    std::vector<int> left_view() const;
    std::vector<int> right_view() const;
    std::vector<int> sum_on_levels() const;

};


void print_vector(const std::vector<int>& vec);
void print_matrix(const std::vector<std::vector<int>>& vec);
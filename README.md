# Лабораторная работа 5

# Обход бинарного дерева

## В ходе работы был реализован следующий функционал

### Обязательная часть
- `preorder(root)`, `inorder(root)`, `postorder(root)`: прямой, симметричный и обратный обходы, возвращающие список значений.
- `level_order(root)`: обход в ширину (BFS), выводящий элементы по уровням.
- Создать несколько тестовых деревьев для проверки работы функций.

### Вариативная часть
1. Посчитать количество узлов на каждом уровне и вернуть список чисел.
2. Найти максимальное и минимальное значения в дереве.
3. Посчитать количество путей от корня до листьев.
4. Вычислить сумму значений по всем путям от корня до листьев.
5. Найти самый длинный путь от корня до листа (возвращать список значений).
6. Вывести «левый вид» дерева (первый узел на каждом уровне).
7. Вывести правый вид» дерева (последний узел на каждом уровне).
8. Для каждого уровня посчитать сумму значений узлов и вернуть список сумм.

---

## Реализация

### Структура `Node`
```cpp
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
```
### Класс `BinaryTree`

**Структура**
```cpp
class BinaryTree {
private:
    Node* root = nullptr;

// Внутрение методы
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

// Базовый функционал
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
```

**Конструктор узла, деструктор и управление памятью**
```cpp
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
```

**Основные методы (Вставка и обязательные обходы)**
```cpp
// Вставка узла
void BinaryTree::update_metrics(Node* node) { // Обновление метрик всех узлов
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

// Прямой обход в глубину (`preorder`), возвращающий список значений
void BinaryTree::preorder(Node* node, std::vector<int>& vec) const {
    if (!node) return;
    vec.push_back(node->value);
    preorder(node->left, vec);
    preorder(node->right, vec);
}
std::vector<int> BinaryTree::preorder() const {
    std::vector<int> vec;
    preorder(root, vec);
    return vec;
}

// Симметричный обход в глубину (`inorder`), возвращающий список значений
void BinaryTree::inorder(Node* node, std::vector<int>& vec) const {
    if (!node) return;
    inorder(node->left, vec);
    vec.push_back(node->value);
    inorder(node->right, vec);
}
std::vector<int> BinaryTree::inorder() const {
    std::vector<int> vec;
    inorder(root, vec);
    return vec;
}

// Обратный обход в глубину (`postorder`), возвращающий список значений
void BinaryTree::postorder(Node* node, std::vector<int>& vec) const {
    if (!node) return;
    postorder(node->left, vec);
    postorder(node->right, vec);
    vec.push_back(node->value);
}
std::vector<int> BinaryTree::postorder() const {
    std::vector<int> vec;
    postorder(root, vec);
    return vec;
}

// Обход в ширину по уровням (`level_order`), возвращающий матрицу значений
void BinaryTree::level_order(Node* node, std::vector<std::vector<int>>& vec, int level) const {
    if (!node) return;
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
```

**Вариативная часть**
```cpp
// Посчитать количество узлов на каждом уровне и вернуть список чисел.
std::vector<int> BinaryTree::get_count_nodes_on_levels() const {
    std::vector<int> vec;
    for (const auto& el : level_order())
        vec.push_back(el.size());
    return vec;
}

// Найти максимальное и минимальное значения в дереве.
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

// Посчитать количество путей от корня до листьев.
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

// Вычислить сумму значений по всем путям от корня до листьев.
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

// Найти самый длинный путь от корня до листа (возвращать список значений).
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

// Вывести «левый вид» дерева (первый узел на каждом уровне).
std::vector<int> BinaryTree::left_view() const {
    std::vector<int> res;
    auto vec = level_order();

    for (const auto& el : vec)
        res.push_back(el.back());

    return res;
}
// Вывести правый вид» дерева (последний узел на каждом уровне).
std::vector<int> BinaryTree::right_view() const {
    std::vector<int> res;
    auto vec = level_order();

    for (const auto& el : vec)
        res.push_back(el[0]);

    return res;
}

// Для каждого уровня посчитать сумму значений узлов и вернуть список сумм.
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
```

---

## Тестирование работоспособности
```cpp
void test_tree(BinaryTree& tree) {
    static int counter = 1;
    std::cout << std::endl << std::endl << "Tree "  << counter++ << std::endl;
    tree.print();


    std::cout << std::endl << "Preorder: ";
    print_vector(tree.preorder());
    std::cout << std::endl;

    std::cout << std::endl << "Inorder: ";
    print_vector(tree.inorder());
    std::cout << std::endl;

    std::cout << std::endl << "Postorder: ";
    print_vector(tree.postorder());
    std::cout << std::endl;


    std::cout << std::endl << "Level order:" << std::endl;
    print_matrix(tree.level_order());


    std::cout << std::endl << "Count nodes on levels: ";
    print_vector(tree.get_count_nodes_on_levels());
    std::cout << std::endl;


    std::cout << std::endl << "Min value: " << tree.get_min();
    std::cout << std::endl << "Max value: " << tree.get_max() << std::endl;

    std::cout << std::endl << "Count ways from root to leaves: " << tree.get_count_leaves() << std::endl;

    std::cout << std::endl << "Sum tree: ";
    std::cout << tree.get_sum();
    std::cout << std::endl << "Sum by all ways: ";
    std::cout << tree.get_sum_ways() << std::endl;

    std::cout << std::endl << "Longest way " << "(" << tree.get_height() << " levels): ";
    print_vector(tree.longest_way());
    std::cout << std::endl;

    std::cout << std::endl << "Left view: ";
    print_vector(tree.left_view());

    std::cout << std::endl << "Right view: ";
    print_vector(tree.right_view());
    std::cout << std::endl;

    std::cout << std::endl << "Sum on levels: ";
    print_vector(tree.sum_on_levels());
    std::cout << std::endl;
}
```

## `main`
``` cpp
int main() {
    BinaryTree tree1;
    tree1.insert(70);
    tree1.insert(50);
    tree1.insert(30);
    tree1.insert(60);
    tree1.insert(40);
    tree1.insert(20);
    tree1.insert(80);
    tree1.insert(150);
    test_tree(tree1);

    BinaryTree tree2;
    tree2.insert(70);
    tree2.insert(50);
    tree2.insert(50);
    tree2.insert(70);
    tree2.insert(40);
    tree2.insert(20);
    test_tree(tree2);

    BinaryTree tree3;
    tree3.insert(25);
    tree3.insert(25);
    tree3.insert(25);
    tree3.insert(25);
    tree3.insert(25);
    tree3.insert(25);
    test_tree(tree3);

    BinaryTree tree4;
    tree4.insert(25);
    test_tree(tree4);

    BinaryTree tree5;
    test_tree(tree5);

    return 0;
}
```

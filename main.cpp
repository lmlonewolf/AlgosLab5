#include "Header.h"

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

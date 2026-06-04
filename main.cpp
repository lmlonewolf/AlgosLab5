#include "Header.h"



int main() {
    BinaryTree tree;

    tree.insert(70);
    tree.insert(50);
    tree.insert(30);
    tree.insert(60);
    tree.insert(40);
    tree.insert(20);
    tree.insert(80);
    tree.insert(150);

    std::cout << "Tree" << std::endl;
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


    return 0;
}

#ifndef BST_H
#define BST_H

#include <vector>
#include <string>

template <class T>
class BST
{
private:
	class Node
	{
	public:
		T element;
		Node* left;
		Node* right;
		Node(T element);
		~Node();
		int height;
	};
	
	Node* root = nullptr;
	void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);
public:
	BST();
	~BST();
	void insert(T element);
	void remove(T element);
	bool find(T element);
	auto recursionRemove(T element, Node* current)->Node*;
	void  inorder(Node* current, std::vector<T> &vektor);
	void  preorder(Node* current, std::vector<T>& vektor);
	void  postorder(Node* current, std::vector<T>& vektor);
	int height_helper(Node* current);
	std::vector<T> inOrderWalk();
	std::vector<T> preOrderWalk();
	std::vector<T> postOrderWalk();
	int getTreeHeight();
	T getMin();
	T getMax();
	std::string ToGraphviz();
};

template<class T>
BST<T>::Node::Node(T element) : element(element), left(nullptr), right(nullptr), height(-1)
{
}
template<class T>
BST<T>::Node::~Node()
{
	
	delete left;
	left = nullptr;
	delete right;
	right = nullptr;
	
}
template<class T>
inline BST<T>::BST()
{
}

template<class T>
inline BST<T>::~BST()
{
	delete root;
	root = nullptr;
	
}

template<class T>
inline void BST<T>::insert(T element) //Insert an element by searching
{
	if (root == nullptr)
	{
		root = new Node(element);
	}
	else
	{
		Node* current = root;
		Node* parent = nullptr;
		while (current != nullptr)
		{
			parent = current;
			if (element < current->element)
			{
				current = current->left;
			}
			else if (element == current->element) {
				return;
			}
			else
			{
				current = current->right;
			}
		}
		if (element < parent->element)
		{
			parent->left = new Node(element);
		}
		else
		{
			parent->right = new Node(element);
		}
	}
}

template<class T>
inline void BST<T>::remove(T element) //Removes an element with iteration and searching
{
	this->root = recursionRemove(element, root);
	//if (root == nullptr)
	//{
	//	return;
	//}
	//else
	//{
	//	Node* current = root;
	//	Node* parent = root;
	//	if (root->element == element) {
	//		delete root;
	//		root = nullptr;
	//		return;
	//	}
	//	while (current != nullptr && element != current->element) //Find the element
	//	{
	//		parent = current;
	//		if (element < current->element)
	//		{
	//			current = current->left;
	//		}
	//		else
	//		{
	//			current = current->right;
	//		}
	//	}
	//	if (current == nullptr) {
	//		return;
	//	}
	//	Node* to_delete = current; //A placeholder for the node
	//	if (current->right == nullptr && current->left == nullptr) //no childs, leaf
	//	{
	//		if (parent->right == current) {
	//			delete parent->right;
	//			parent->right = nullptr;
	//			return;
	//		}
	//		if (parent->left == current) {
	//			delete parent->left;
	//			parent->left = nullptr;
	//			return;
	//		}
	//	}
	//	else if (current->right != nullptr && current->left != nullptr) //two childs
	//	{
	//		current = current->left;
	//		while (current->right != nullptr) //find max of left child
	//		{
	//			current = current->right;
	//		}
	//		element = current->element; //Saves memory
	//		remove(current->element);
	//		to_delete->element = element;
	//		return;

	//	}
	//	else if (current->right != nullptr && current->left == nullptr) { //only right child
	//		//The pointer to be deleted points to the right child instead
	//		if (parent->right == current) {
	//			parent->right = current->right;
	//			free(current->right);
	//			return;
	//		}
	//		if (parent->left == current) {
	//			parent->left = current->right;
	//			free(current->right);
	//			return;
	//		}
	//	}
	//	else if (current->left != nullptr && current->right == nullptr) { //only left child
	//		//The pointer to be deleted points to the left child instead
	//		if (parent->right == current) {
	//			parent->right = current->left;
	//			free(current->left);
	//			return;
	//		}
	//		if (parent->left == current) {
	//			parent->left = current->left;
	//			free(current->left);
	//			return;
	//		}
	//	}
	//}
}
template<class T>
inline auto BST<T>::recursionRemove(T element, Node* current) -> Node*
{

	if (root == nullptr)
	{
		return root;
	}
	if (element < current->element) {
		current->left = recursionRemove(element, current->left);
	}
	else if (element > current->element) {
		current->right = recursionRemove(element, current->right);
	}
	else {

		if (current->right == nullptr && current->left == nullptr) {
			//no childs, leaf
			delete current;
			current = nullptr;
			return current;
		}
		else if (current->right != nullptr && current->left != nullptr) //two childs
		{
			Node* to_delete = current;
			current = current->left;
			while (current->right != nullptr) //find max of left child
			{
				current = current->right;
				
			}
			T temp_element = current->element;
			current = recursionRemove(current->element, root);
			to_delete->element = temp_element;

			return to_delete;
		}
		else if (current->right != nullptr && current->left == nullptr) { //only right child
			//The pointer to be deleted points to the right child instead
			Node* temp = current->right;
			free(current);
			return temp;
		}
		else if (current->left != nullptr && current->right == nullptr) { //only left child
			//The pointer to be deleted points to the left child instead
			Node* temp = current->left;
			free(current);
			return temp;
		}
		return current;
	}
	return current;
}
template<class T>
inline bool BST<T>::find(T element) //Find the node, returns true if found
{ //Works as searchfunction for delete, but it returns a bool instead
	if (root == nullptr)
	{
		return false;
	}
	else
	{
		Node* current = root;
		Node* parent = nullptr;
		parent = current;
		while (current != nullptr && element != current->element)
		{
			parent = current;
			if (element < current->element)
			{
				current = current->left;
			}
			else if(element > current->element)
			{
				current = current->right;
			}
			
		}
		if (current != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
}
template<class T>
inline void BST<T>::inorder(Node* current, std::vector<T>& inordertemp)  { //helper
	if (current == nullptr) return;
	inorder(current->left, inordertemp);
	inordertemp.push_back(current->element);
	inorder(current->right, inordertemp);
}
template<class T>
inline void BST<T>::preorder(Node* current, std::vector<T>& preordertemp) { //helper
	if (current == nullptr) return;
	
	preordertemp.push_back(current->element);
	preorder(current->left, preordertemp);
	preorder(current->right, preordertemp);
}
template<class T>
inline void BST<T>::postorder(Node* current, std::vector<T>& postordertemp) { //helper
	if (current == nullptr) return;
	postorder(current->left, postordertemp);
	postorder(current->right, postordertemp);
	postordertemp.push_back(current->element);
}
template<class T>
inline std::vector<T> BST<T>::inOrderWalk()
{
	std::vector<T> inorderlist;
	Node* current = root;
	inorder(current, inorderlist);
	
	return inorderlist;
}

template<class T>
inline std::vector<T> BST<T>::preOrderWalk()
{
	std::vector<T> preorderlist;
	Node* current = root;
	preorder(current, preorderlist);

	return preorderlist;
}

template<class T>
inline std::vector<T> BST<T>::postOrderWalk()
{
	std::vector<T> postorderlist;
	Node* current = root;
	postorder(current, postorderlist);

	return postorderlist;
}
template<class T>
inline int BST<T>::height_helper(Node* current)
{ //Källa https://www.journaldev.com/34979/height-of-a-binary-tree-in-c-plus-plus (2022)
	
	if (current == nullptr) {
		return -1;
	}
	else {
		int left_height = height_helper(current->left);
		int right_height = height_helper(current->right);

		if (left_height > right_height) {
			return left_height + 1;
		}
		else if (right_height >= left_height) {
			return right_height + 1;
		}
	}
	return -1;
}


template<class T>
inline int BST<T>::getTreeHeight()
{
	Node* current = root;
	int height = height_helper(current);
	return height;
}

template<class T>
inline T BST<T>::getMin() //Walk to the leftmost node
{
	Node* current = root;
	while (current->left != nullptr) {
		current = current->left;
	}
	return current->element;
}

template<class T>
inline T BST<T>::getMax() //Walk to the rightmost node
{
	Node* current = root;
	while (current->right != nullptr) {
		current = current->right;
	}
	return current->element;
}
///------------------------------------------------Graphviz Graphviz
///------------------O--------------O-----------------Graphviz Graphviz
///-------------------------/----------------------------Graphviz Graphviz
///-----------XX----------./.----------------XX-------------Graphviz Graphviz
///-------------XXX-----------------------XXX------------Graphviz Graphviz
///---------------XXXXXXXXXXXXXXXXXXXXXXXX------------Graphviz Graphviz
///-----------------------------------------------Graphviz Graphviz
template <class T>
std::string BST<T>::ToGraphviz() // Member function of the AVLTree class
{
	std::string toReturn = "";
	if (this->root) // root is a pointer to the root node of the tree
	{
		std::string listOfNodes;
		std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
		toReturn += std::string("digraph {\n");
		size_t id = 0;
		ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
		toReturn += listOfNodes;
		toReturn += listOfConnections;
		toReturn += std::string("}");
	}
	return toReturn;
}

template <class T>
void BST<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
{
	size_t myID = uniqueID;
	listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
	if (toWorkWith->left)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->left, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}

	if (toWorkWith->right)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->right, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
}

#endif //BST_H


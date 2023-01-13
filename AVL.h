#ifndef AVL_H
#define AVL_H

#include <vector>
#include <string>
#include "BST.h"

template <class T>
class AVL
{
private:
	class Node
	{
	public:
		T element;
		Node* left;
		Node* right;
		int height;
		int balance;
		Node(T element);
		~Node();	

	
	};
	void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);
	
	Node* root = nullptr;
public:
	AVL();
	~AVL();
	//Helpers
	auto left_rotate(Node* current);
	auto right_rotate(Node* current);
	auto leftright_rotate(Node* current);
	auto rightleft_rotate(Node* current);
	auto balanceHelperInsert(Node* current) -> Node*;
	auto recursionInsert(T element, Node* current) -> Node*;
	int max(int a, int b);
	int returnBalance(Node* current);
	int getheight(Node* current);
	//--
	void insert(T element);
	auto checkElement(T element, Node* current)->Node*;
	auto recursionDelete(T element, Node* current)->Node*;
	void remove(T element);
	bool find(T element);
	void inorder(Node* current, std::vector<T>& inordertemp);
	void preorder(Node* current, std::vector<T>& preordertemp);
	void postorder(Node* current, std::vector<T>& postordertemp);
	std::vector<T> inOrderWalk();
	std::vector<T> preOrderWalk();
	std::vector<T> postOrderWalk();
	int getTreeHeight();
	T getMin();
	T getMax();
	std::string ToGraphviz();
	
};
template<class T>
AVL<T>::Node::Node(T element) : element(element), left(nullptr), right(nullptr), height(0), balance(0)
{

}
template<class T>
AVL<T>::Node::~Node()
{
	delete left;
	left = nullptr;
	delete right;
	right = nullptr;
	
}
template<class T>
inline AVL<T>::AVL()
{
}
template<class T>
inline AVL<T>::~AVL()
{
	delete root;
	root = nullptr;
}

template<class T>
auto AVL<T>::left_rotate(Node* current) { //Helper, rotates left
	Node* temp;
	temp = current->left;
	
	current->left = temp->right;

	temp->right = current;
	
	temp->right->height = max(getheight(temp->right->left), getheight(temp->right->right)) + 1; //Update height
	temp->height = max(getheight(temp->left), getheight(temp->right)) + 1; //Update Height

	return temp;
}
template<class T>
auto AVL<T>::right_rotate(Node* current) { //Helper, rotates right
	Node* temp;
	temp = current->right;
	current->right = temp->left;

	temp->left = current;
	temp->left->height = max(getheight(temp->left->left), getheight(temp->left->right)) + 1; //Update height
	temp->height = max(getheight(temp->left), getheight(temp->right)) + 1; //Update height
	return temp;
}
template<class T>
auto AVL<T>::leftright_rotate(Node* current) { //Helper rotates left and right
	Node* temp;
	temp = current->left;
	current->left = right_rotate(temp);
	return left_rotate(current);
}
template<class T>
auto AVL<T>::rightleft_rotate(Node* current) { //Helper, rotatets right and left
	Node* temp;
	temp = current->right;
	current->right = left_rotate(temp);
	return right_rotate(current);
}
template<class T>
inline int AVL<T>::max(int a, int b) { //Helper
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}
template<class T>
int AVL<T>::returnBalance(Node* current) { //O(1), just returns a balance with IF and ELSE
	if (current->left && current->right) {
		return current->left->height - current->right->height;
	}
	else if (current->left && current->right == nullptr) {
		return current->left->height;
	}
	else if (current->left == nullptr && current->right) {
		return -current->right->height;
	}
	return 1;
}
template<class T>
int AVL<T>::getheight(Node* current) { //returns height
	if (current == nullptr) {
		return 0;
	}
	else {
		return current->height;
	}
}

template<class T>
auto AVL<T>::recursionInsert(T element, Node* current) -> Node* //Rekursion simplifierar problemet
{

	if (current == nullptr)
	{
		current = new Node(element);
		current->height = 1;
		return current;
	}
	else if (element < current->element) {
		current->left = recursionInsert(element, current->left);
		
	}
	else if (element > current->element) {
		current->right = recursionInsert(element, current->right);
	}
	else if (element == current->element) {
		return current;
	}
	current->height = max(getheight(current->right), getheight(current->left)) +1; //O(1) to get height
	
	int balance = returnBalance(current); //O(1)

	if (balance > 1) {

		if (returnBalance(current->left) >= 0) {
			current = left_rotate(current);
			
		}
		else {
			current = leftright_rotate(current);
			
		}
	}
	else if (balance < -1) {
		if (returnBalance(current->right) > 0) {

			current = rightleft_rotate(current);
			
		}
		else {

			current = right_rotate(current);
			
		}
	}
	
	
	return current;
}
template<class T>
inline void AVL<T>::insert(T element)
{
	this->root = recursionInsert(element, root);
}

template<class T>
auto AVL<T>::balanceHelperInsert(Node* current) -> Node* //Used for remove also, checks balance and performs rotations
{

	int balance = returnBalance(current); //O(1) (check function)

	if (balance > 1) {

		if (returnBalance(current->left) >= 0) {
			current = left_rotate(current);
		}
		else {
			current = leftright_rotate(current);
		}
	}
	else if (balance < -1) {
		if (returnBalance(current->right) > 0) {

			current = rightleft_rotate(current);
		}
		else {

			current = right_rotate(current);
		}
	}
	return current;
}

template<class T>
auto AVL<T>::checkElement(T element, Node* current)->Node* {
	if (element == current->element) {
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
				current = balanceHelperInsert(current);
			}
			T temp_element = current->element;
			current = recursionDelete(current->element, root);
			to_delete->element = temp_element;
			to_delete = balanceHelperInsert(to_delete);
			return to_delete;
		}
		else if (current->right != nullptr && current->left == nullptr) { //only right child
			//The pointer to be deleted points to the right child instead
			current = current->right;
			current = balanceHelperInsert(current);
			return current;
		}
		else if (current->left != nullptr && current->right == nullptr) { //only left child
			//The pointer to be deleted points to the left child instead
			current = current->left;
			current = balanceHelperInsert(current);
			return current;
		}
		return current;
	}
	return current;
}

template<class T>
auto AVL<T>::recursionDelete(T element, Node* current) -> Node* //Rekursion simplifierar problemet
{
	if (current == nullptr)
	{
		return nullptr;
	}
	else if (element < current->element) {

		current->left = recursionDelete(element, current->left);
		current = balanceHelperInsert(current);

	}
	else if (element > current->element) {

		current->right = recursionDelete(element, current->right);
		current = balanceHelperInsert(current);
	}
	else if (element == current->element) {
		current = checkElement(element, current);
		if (current != nullptr) {
			current = balanceHelperInsert(current);
		}
	}
	return current;
}

template<class T>
inline void AVL<T>::remove(T element)
{
	this->root = recursionDelete(element, root);
}
template<class T>
inline bool AVL<T>::find(T element) //Samma som BST
{
	if (root == nullptr)
	{
		return false;
	}
	else
	{
		Node* current = root;
		Node* temp_parent = nullptr;
		temp_parent = current;
		while (current != nullptr && element != current->element)
		{
			temp_parent = current;
			if (element < current->element)
			{
				current = current->left;
			}
			else if (element > current->element)
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
inline void AVL<T>::inorder(Node* current, std::vector<T>& inordertemp) { //helper, samma som BST
	if (current == nullptr) return;
	inorder(current->left, inordertemp);
	inordertemp.push_back(current->element);
	inorder(current->right, inordertemp);
}
template<class T>
inline void AVL<T>::preorder(Node* current, std::vector<T>& preordertemp) { //helper, samma som BST
	if (current == nullptr) return;
	preordertemp.push_back(current->element);
	preorder(current->left, preordertemp);
	preorder(current->right, preordertemp);
}
template<class T>
inline void AVL<T>::postorder(Node* current, std::vector<T>& postordertemp) { //helper, samma som BST
	if (current == nullptr) return;
	postorder(current->left, postordertemp);
	postorder(current->right, postordertemp);
	postordertemp.push_back(current->element);
}
template<class T>
inline std::vector<T> AVL<T>::inOrderWalk()
{
	std::vector<T> inorderlist;
	Node* current = root;
	inorder(current, inorderlist);
	return inorderlist;
}
template<class T>
inline std::vector<T> AVL<T>::preOrderWalk()
{
	std::vector<T> preorderlist;
	Node* current = root;
	preorder(current, preorderlist);
	return preorderlist;
}
template<class T>
inline std::vector<T> AVL<T>::postOrderWalk()
{
	std::vector<T> postorderlist;
	Node* current = root;
	postorder(current, postorderlist);
	return postorderlist;
}
template<class T>
inline int AVL<T>::getTreeHeight() //
{
	if (root == nullptr) {
		return -1;
	}
	Node* current = root;
	return current->height -1;
}
template<class T>
inline T AVL<T>::getMin() //samma som BST
{
	Node* current = root;
	while (current->left != nullptr) {
		current = current->left;
	}
	return current->element;
}
template<class T>
inline T AVL<T>::getMax() //samma som BST
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
std::string AVL<T>::ToGraphviz() // Member function of the AVLTree class
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
void AVL<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
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

#endif //AVL_H

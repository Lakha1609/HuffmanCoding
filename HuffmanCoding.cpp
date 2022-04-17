/*Huffman Coding Implementation
Written By : Lakha Rahman 
On : 11/02/2022
Program to demonstrate Huffman coding algorithm which used for lossless compress data compression 
*/

#include <iostream>
#include <cstdlib>
using namespace std;


// constant can be avoided by explicitly calculating height of the tree
#define MAX_TREE_HT 100
 
//structure of huffman tree
class Node {
public:
    char data;
    unsigned freq;
    Node *left, *right;
};
 
// Structure for Queue 
class Queue {
public:
    int front, rear;
    int size;
    Node** array;
};
 
// creating the Node
Node* newNode(char data, unsigned freq)
{
    Node* temp = new Node[(sizeof(Node))];
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
 
//creating Queue of capacity size
Queue* createQueue(int size)
{
    Queue* queue = new Queue[(sizeof(Queue))];
    queue->front = queue->rear = -1;
    queue->size = size;
    queue->array = new Node*[(queue->size * sizeof(Node*))];
    return queue;
}
 
//Checking if there is only one element present in Queue
int isSizeOne(Queue* queue)
{
    return queue->front == queue->rear && queue->front != -1;
}
 
int isEmpty(Queue* queue) { 
    
     return queue->front == -1; 
}
 
int isFull(Queue* queue)
{ 
    return queue->rear == queue->size - 1;
}
 
//Insert operation on Queue
void enQueue(Queue* queue, Node* item)
{
    if (isFull(queue))
        return;
    queue->array[++queue->rear] = item;
    if (queue->front == -1)
        ++queue->front;
}
 
//Delete operation on Queue
Node* deQueue(Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    Node* temp = queue->array[queue->front];
    if (queue->front == queue->rear) // If there is only one item in queue
        queue->front = queue->rear = -1;
    else
        ++queue->front;
    return temp;
}
 
//getting value from queue
Node* getFront(Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    return queue->array[queue->front];
}
 
// returns the minmium item from the queue 
Node* findMin(Queue* firstQueue, Queue* secondQueue)
{
    //  If first queue is empty, dequeue from second queue
    if (isEmpty(firstQueue))
        return deQueue(secondQueue);
 
    // If second queue is empty, dequeue from first queue
    if (isEmpty(secondQueue))
        return deQueue(firstQueue);
 
    //Else, compare the front of two queues and dequeue minimum
    if (getFront(firstQueue)->freq
        < getFront(secondQueue)->freq)
        return deQueue(firstQueue);
 
    return deQueue(secondQueue);
}
 
//checking if this node is leaf
int isLeaf(Node* root)
{
    return !(root->left) && !(root->right);
}
 

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n;i++) cout << arr[i];
    cout << endl;
}
 
// Building Huffman Tree
Node* buildHuffmanTree(char data[], int freq[],int size)
{
    Node *left, *right, *top;
 
    //Creating two empty queues
    Queue* firstQueue = createQueue(size);
    Queue* secondQueue = createQueue(size);
 
    // Create a leaf node for each unique character and Enqueue it to the first queue in non-decreasing order of frequency. 
    for (int i = 0; i < size; ++i)
        enQueue(firstQueue, newNode(data[i], freq[i]));
 
    // Loop till Queue contain more than one node
    while (
        !(isEmpty(firstQueue) && isSizeOne(secondQueue))) {
        //Dequeuing two nodes with the minimum  frequency 
        left = findMin(firstQueue, secondQueue);
        right = findMin(firstQueue, secondQueue);
 
        //Creating a new internal node with frequency equal to the sum of the two nodes frequencies.
        // Enqueue this node to second queue.
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        enQueue(secondQueue, top);
    }
 
    return deQueue(secondQueue);
}
 //Dissplaying the Huffman tree codes starting from root
void printCodes(Node* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
    // If this is a leaf node, then it contains one of the
    // input characters, print the character and its code
    if (isLeaf(root)) {
        cout << root->data << ": ";
        printArr(arr, top);
    }
}
 
// function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
    // Construct Huffman Tree
    Node* root = buildHuffmanTree(data, freq, size);
 
    // Print Huffman codes using the Huffman tree built
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}
 

int main()
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
    return 0;
}
 
 

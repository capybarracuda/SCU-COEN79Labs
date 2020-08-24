//NODE CLASS:
template <class T>
class Node
{
    public:
    T data;
    Node* next;

};

//LINKED LIST
template <class T>
class LinkedList
{
    Node<T> *head, *tail;
    public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }
}
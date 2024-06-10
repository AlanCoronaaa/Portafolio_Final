/*
  Integrantes:
    Moisés Abel Díaz Nava. A01799628
    Luis Enrique Gutierrez Mendioroz. A00837481
  Compilar:
  Compilación para ejecutar:
  g++ -O3 -Wall -o main main.cpp
  ejecutar:
  ./main
*/

#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include "DLLNode.h"
#include "data.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <vector>

template <class T> void swap(T *a, T *b) {
  T t = *a;
  *a = *b;
  *b = t;
}

template <class T> class DLinkedList {
private:
  DLLNode<T> *head;
  DLLNode<T> *tail;
  int numElements;

public:
  DLinkedList();
  ~DLinkedList();
  int getNumElements();
  void printList();
  void printReverseList();
  void addFirst(T value);
  void addLast(T value);
  bool deleteData(T value);
  bool deleteAt(int position);
  T getData(int position);
  void updateData(T value, T newValue);
  // TO-DO act 2.2
  void updateAt(int position, T newValue);
  void findData(T value);
  void invert();
  // https://www.geeksforgeeks.org/quicksort-for-linked-list/
  void quicksort(DLLNode<T> *start, DLLNode<T> *end);
  DLLNode<T> *partition(DLLNode<T> *start, DLLNode<T> *end);
  void qSort();
  DLLNode<T> *merge(DLLNode<T> *left, DLLNode<T> *right);
  DLLNode<T> *mergeSort(DLLNode<T> *start);
  void mergeSort();
  DLLNode<T> *getMiddle(DLLNode<T> *start);
  int getProductSublist(int ini, int fin);
  DLLNode<T> *lowerLim(string target);
  DLLNode<T> *upperLim(string target);
  void printInterval(DLLNode<T> *lower, DLLNode<T> *upper);

  std::string getMes(int index);
  int getDia(int index);
  std::string getErrMessage(int index);
  std::string getHoraMinSec(int index);
  std::string getIpAd(int index);
  std::string getFechaHora(int index);
  std::string getFechaHoraString(int index);
  int getTimeInt(int index);
  std::chrono::system_clock::time_point getEpochSecond(int index);
};

int comparaciones = 0;
int swaps = 0;
// Complejidad O(1)
template <class T> DLinkedList<T>::DLinkedList() {
  std::cout << "--> Creando una lista doblemente ligada vacia: " << this
            << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T> DLinkedList<T>::~DLinkedList() {
  std::cout << "--> Liberando memoria de la lista doblemente ligada: " << this
            << std::endl;
  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(1)
template <class T> int DLinkedList<T>::getNumElements() { return numElements; }

// Complejidad O(n)
template <class T> void DLinkedList<T>::printList() {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido de la lista es: " << std::endl;
    DLLNode<T> *p = head;
    while (p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }
}

// Complejidad O(n)
template <class T> void DLinkedList<T>::printReverseList() {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido inverso de la lista es: " << std::endl;
    DLLNode<T> *p = tail;
    while (p != nullptr) {
      std::cout << p->data << " ";
      p = p->prev;
    }
    std::cout << std::endl;
  }
}

// Complejidad O(1)
template <class T> void DLinkedList<T>::addFirst(T value) {
  // 1. crear nuevo nodo
  DLLNode<T> *newNode = new DLLNode<T>(value);
  // si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    head = newNode;
    tail = newNode;
  } else {
    // 2. apuntar newNode->next al nodo apuntado por head
    newNode->next = head;
    // 3. apuntar head->prev a newNode
    head->prev = newNode;
    // 4. actualizar head para apuntar a newNode
    head = newNode;
  }
  numElements++;
}

// Complejidad O(1)
template <class T> void DLinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else {
    // 1. crear nuevo nodo
    DLLNode<T> *newNode = new DLLNode<T>(value);
    // 2. apuntar tail->next a newNode
    tail->next = newNode;
    // 3. apuntar newNode->prev a tail
    newNode->prev = tail;
    // 4. actualizar tail para apuntar a newNode
    tail = newNode;
    numElements++;
  }
}

// Complejidad O(n)
template <class T> bool DLinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    std::cout << "La lista esta vacia" << std::endl;
    return false;
  } else {
    // Buscar value en la lista
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    while (p != nullptr && p->data != value) {
      previous = p;
      p = p->next;
    }
    // si value no esta en la lista
    if (p == nullptr) {
      std::cout << "El valor no existe en la lista" << std::endl;
      return false;
    }
    // si debo borrar el primer nodo de la lista
    if (p != nullptr && p == head) {
      head = p->next;
      if (head == nullptr) // habia solo un nodo en la lista
        tail = nullptr;
      else
        head->prev = nullptr;
    } else if (p->next == nullptr) { // borrar el ultimo nodo
      previous->next = nullptr;
      tail = previous;
    } else { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    // borrar el nodo apuntado por p
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T> bool DLinkedList<T>::deleteAt(int position) {
  // La lista esta vacia
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) { // primer nodo
    DLLNode<T> *p = head;
    // si la lista contiene un solo nodo
    if (p != nullptr && p->next == nullptr) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = p->next;
      head->prev = nullptr;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  } else {
    // Buscar position en la lista
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    int index = 0;
    while (index != position) {
      previous = p;
      p = p->next;
      index++;
    }
    // debo borrar el ultimo nodo
    if (p->next == nullptr) {
      previous->next = nullptr;
      tail = previous;
    } else { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T> T DLinkedList<T>::getData(int position) {
  // Validar position
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) { // primer nodo
    return head->data;
  } else { // si es cualquier otra posicion
    // Buscar position en la lista
    DLLNode<T> *p = head;
    int index = 0;
    while (index != position) {
      p = p->next;
      index++;
    }
    if (p != nullptr)
      return p->data;
    else
      return {};
  }
}

// Complejidad O(n)
template <class T> void DLinkedList<T>::updateData(T value, T newValue) {
  // Buscar value en la lista
  DLLNode<T> *p = head;
  while (p != nullptr && p->data != value) {
    p = p->next;
  }
  if (p != nullptr)
    p->data = newValue;
  else
    throw std::out_of_range("El elemento a actualizar no existe en la lista");
}

//Metodo quicksort
//Complejidad O(n log n)
template <class T>
void DLinkedList<T>::quicksort(DLLNode<T> *start, DLLNode<T> *end) {
  if (start == nullptr || start == end || start == end->next)
    return;
  DLLNode<T> *pivot = partition(start, end);
  if (pivot != nullptr) { // Verificar si el pivot no es nulo
    if (pivot->prev != nullptr)
      quicksort(start, pivot->prev); // Llamada recursiva con 'pivot->prev'
    if (pivot->next != nullptr)
      quicksort(pivot->next, end); // Llamada recursiva con 'pivot->next'
  }
}

template <class T>
//Complejidad O(n)
DLLNode<T> *DLinkedList<T>::partition(DLLNode<T> *start, DLLNode<T> *end) {
  int pivot = start->data.getTimeInt(); // Usamos el tiempo como pivote
  DLLNode<T> *i = start;

  for (DLLNode<T> *j = start->next; j != end->next; j = j->next) {
    if (j->data.getTimeInt() < pivot) {
      i = (i == nullptr) ? start : i->next;
      swap(&(i->data), &(j->data));
    }
  }
  swap(&(i->data), &(start->data));
  return i;
}
// Metodo  para llamar quicksort
// Ordena la lista de forma ascendente
//https://www.geeksforgeeks.org/quicksort-for-linked-list/
// Complejidad O(n log n)
template <class T> void DLinkedList<T>::qSort() { quicksort(head, tail); }

//Metodo mergeSort
//https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
//https://www.javatpoint.com/merge-sort-on-doubly-linked-list
//complejidad O(n)
template <class T>
DLLNode<T> *DLinkedList<T>::merge(DLLNode<T> *left, DLLNode<T> *right) {
  DLLNode<T> *result = nullptr;

  // Caso base: si alguna de las sublistas es nula, devolvemos la otra sublista
  if (left == nullptr)
    return right;
  if (right == nullptr)
    return left;

  // Comparar los elementos de las sublistas y elegir el menor para ser el
  // siguiente en la lista ordenada
  if (left->data.getTimeInt() <= right->data.getTimeInt()) {
    result = left;
    result->next = merge(left->next, right);
    result->next->prev = result;
  } else {
    result = right;
    result->next = merge(left, right->next);
    result->next->prev = result;
  }

  return result;
}

// Complejidad O(n log n)
template <class T> DLLNode<T> *DLinkedList<T>::mergeSort(DLLNode<T> *start) {
  // Casos base: si la lista está vacía o tiene solo un elemento, ya está
  // ordenada
  if (start == nullptr || start->next == nullptr)
    return start;

  // Dividir la lista en dos sublistas
  DLLNode<T> *middle = getMiddle(start);
  DLLNode<T> *nextToMiddle = middle->next;

  // Separar las sublistas
  middle->next = nullptr;
  nextToMiddle->prev = nullptr;

  // Ordenar recursivamente ambas sublistas
  DLLNode<T> *left = mergeSort(start);
  DLLNode<T> *right = mergeSort(nextToMiddle);

  // Combinar las sublistas ordenadas
  return merge(left, right);
}

// Metodo  para llamar mergeSort
// Complejidad O(n log n)
template <class T> void DLinkedList<T>::mergeSort() {
  head = mergeSort(head);
  // Actualizar la cola de la lista
  tail = head;
  while (tail->next != nullptr) {
    tail = tail->next;
  }
}
//Complejidad O(n)
template <class T> DLLNode<T> *DLinkedList<T>::getMiddle(DLLNode<T> *start) {
  if (start == nullptr)
    return start;
  DLLNode<T> *slow = start;
  DLLNode<T> *fast = start->next;

  while (fast != nullptr) {
    fast = fast->next;
    if (fast != nullptr) {
      slow = slow->next;
      fast = fast->next;
    }
  }
  return slow;
}

// Complejidad O(n)
template <class T> int DLinkedList<T>::getProductSublist(int ini, int fin) {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    DLLNode<T> *p = head;
    int product = 1;
    int index = 0;
    while (p != nullptr) {
      p = p->next;
      index++;
      if (index == ini) {
        while (p != nullptr && index != fin) {
          product *= p->data;
          p = p->next;
          index++;
        }
        product *= p->data;
        p = p->next;
        return product;
      }
    }
  }
  return 0;
}


// Metodo invert
// Invierte la lista encadenada doble
// Complejidad O(n)
template <class T> void DLinkedList<T>::invert() {
  if (head == nullptr || head == tail) // Si la lista está vacía o tiene solo un
                                       // elemento, no es necesario invertirla
    std::cout << "La lista no puede ser invertida/Esta vacia" << std::endl;

  DLLNode<T> *current = head;
  DLLNode<T> *temp = nullptr;

  // Intercambiar los punteros prev y next de cada nodo en la lista
  while (current != nullptr) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev; // Mover al siguiente nodo (ahora prev) en la lista
  }

  // Actualizar los punteros head y tail
  temp = head;
  head = tail;
  tail = temp;
}

template <class T> void DLinkedList<T>::updateAt(int ini, T fin) {
  // Validar posicion
  if (ini < 0 || fin < 0 || fin >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }

  DLLNode<T> *p = head;
  int index = 0;
  for (int i = index; i < ini; i++) {
    p = p->next;
  }

  int producto = 1;
  for (int i = ini; i < fin; i++) {
    producto *= p->data;
    p = p->next;
  }
}

//Conmplejidad O(n)
template <class T> DLLNode<T> *DLinkedList<T>::lowerLim(string target) {
  DLLNode<T> *current = head;
  DLLNode<T> *result = nullptr;
  while (current != nullptr) {
    if (current->data.getFechaHoraString() == target) {
      result = current;
      break;
    }
    current = current->next;
  }

  return result;
}

//Conmplejidad O(n)
template <class T> DLLNode<T> *DLinkedList<T>::upperLim(string target) {
  DLLNode<T> *current = head;
  DLLNode<T> *result = nullptr;
  while (current != nullptr) {
    if (current->data.getFechaHoraString() == target) {
      result = current;
      break;
    }
    current = current->next;
  }

  return result;
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::printInterval(DLLNode<T> *lower, DLLNode<T> *upper) {
  if (lower == nullptr || upper == nullptr) {
    cout << "No se encontraron valores en el intervalo" << endl;
    return;
  }
  cout << "Valores en el intervalo: {" << lower->data.getFechaHoraString()
       << "} a {" << upper->data.getFechaHoraString() << "} " <<endl;
  DLLNode<T> *current = lower;
  while (current != nullptr && current != upper->next) {
    cout << current->data.getFechaHoraString() << " " << current->data.getIpAd() << " " << current->data.getErrMessage() << endl;
    current = current->next;
  }
}

// Complejidad O(n)
template <class T> std::string DLinkedList<T>::getMes(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getMes();
}

// Complejidad O(n)
template <class T> int DLinkedList<T>::getDia(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getDia();
}

// Complejidad O(n)
template <class T> std::string DLinkedList<T>::getErrMessage(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getErrMessage();
}

// Complejidad O(n)
template <class T> std::string DLinkedList<T>::getHoraMinSec(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getHoraMinSec();
}

// Complejidad O(n)
template <class T> std::string DLinkedList<T>::getIpAd(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getIpAd();
}

// Complejidad O(n)
template <class T> std::string DLinkedList<T>::getFechaHora(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getHoraMinSec();
}

// Complejidad O(n)
template <class T> int DLinkedList<T>::getTimeInt(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getTimeInt();
}

// Complejidad O(n)
template <class T> std::string DLinkedList<T>::getFechaHoraString(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getFechaHoraString();
}

// Complejidad O(n)
template <class T>
std::chrono::system_clock::time_point
DLinkedList<T>::getEpochSecond(int index) {
  if (index < 0 || index >= numElements || head == nullptr) {
    // Manejar caso de índice fuera de rango o lista vacía
    throw std::out_of_range("Índice fuera de rango o lista vacía");
  }
  DLLNode<T> *current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data.getEpochSecond();
}

#endif // _LINKEDLIST_H_
#ifndef BILIST_HPP
#define BILIST_HPP

#include "iostream"

namespace khasnulin
{
  template < class T > struct BiList
  {
    T val;
    BiList< T > *next;
    BiList< T > *prev;
  };

  // Создает пустой двухсвязный список, который ссылается сам на себя в next и prev
  template < class T > BiList< T > *create(const T &val)
  {
    BiList< T > *elem = new BiList< T >{val, nullptr, nullptr};
    elem->next = elem;
    elem->prev = elem;
    return elem;
  }

  // Создать новый элемент перед текущим
  template < class T > BiList< T > *insertBefore(BiList< T > *h, const T &val)
  {
    return nullptr;
  }

  // Создать новый элемент после текущего
  template < class T > BiList< T > *insertAfter(BiList< T > *h, const T &val)
  {
    return nullptr;
  }

  // Удалить текущий элемент списка, вернуть указатель на следующий
  template < class T > BiList< T > *remove(BiList< T > *h)
  {
    return nullptr;
  }

  // Удалить следующий элемент списка, вернуть указатель новый следующий
  template < class T > BiList< T > *eraseNext(BiList< T > *h)
  {
    return nullptr;
  }

  // Удалить предыдущий элемент списка, вернуть указатель новый предыдущий
  template < class T > BiList< T > *erasePrev(BiList< T > *h)
  {
    return nullptr;
  }

  // Удалить все элементы списка
  template < class T > BiList< T > *clear(BiList< T > *h)
  {
    return nullptr;
  }

  // Обойти элементы списка от текущего двигаясь влево, пока снова не встретим end. Для каждого
  // элемента вызывать F(val)
  template < class T, class F > F leftTraverse(F f, BiList< T > *h, BiList< T > *e)
  {
    return f;
  }

  // Обойти элементы списка от текущего двигаясь вправо, пока снова не встретим end. Для каждого
  // элемента вызывать F(val)
  template < class T, class F > F rightTraverse(F f, BiList< T > *h, BiList< T > *e)
  {
    return f;
  }

  // Обойти все элементы списка от текущего двигаясь влево, пока не вернемся в начальный элемент. Для каждого
  // элемента вызывать F(val)
  template < class T, class F > F leftTraverse(F f, BiList< T > *h)
  {
    return f;
  }

  // Обойти все элементы списка от текущего двигаясь вправо, пока не вернемся в начальный элемент Для каждого
  // элемента вызывать F(val)
  template < class T, class F > F rightTraverse(F f, BiList< T > *h)
  {
    return f;
  }

  // Обойти все элементы по кругу и вернуть их количество.
  template < class T > size_t size(BiList< T > *h)
  {
    return 0;
  }
}

#endif
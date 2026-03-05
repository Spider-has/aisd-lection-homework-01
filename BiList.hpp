#ifndef BILIST_HPP
#define BILIST_HPP

#include <cstddef>
#include <utility>

namespace khasnulin
{
  template < class T > struct BiList
  {
    T val;
    BiList< T > *next;
    BiList< T > *prev;
  };

  // Получившийся неявный интерфейс:
  // 1) Наличие конструктора копирования
  // 2) Наличие деструктора
  // 3) В traverse наличие перегруженного оператора круглые скобки у объекта F, принимающего в качестве аргумента T
  // 4) В traverse наличие конструктора копирования у объекта F

  // Создает пустой двухсвязный список, который ссылается сам на себя в next и prev
  template < class T, class... Args > BiList< T > *create(Args &&...args)
  {
    BiList< T > *elem = new BiList< T >{T(std::forward< Args >(args)...), nullptr, nullptr}; // T::T(const T& v)
    elem->next = elem;
    elem->prev = elem;
    return elem;
  }

  // Создать новый элемент перед текущим
  template < class T, class... Args > BiList< T > *insertBefore(BiList< T > *h, Args &&...args)
  {
    BiList< T > *elem = create< T >(std::forward< Args >(args)...);
    if (!h)
    {
      return elem;
    }
    h->prev->next = elem;
    elem->next = h;
    elem->prev = h->prev;
    return h->prev = h->prev->next;
  }

  // Создать новый элемент после текущего
  template < class T, class... Args > BiList< T > *insertAfter(BiList< T > *h, Args &&...args)
  {
    if (!h)
    {
      return create< T >(std::forward< Args >(args)...);
    }
    return insertBefore< T >(h->next, std::forward< Args >(args)...);
  }

  // Удалить текущий элемент списка, вернуть указатель на следующий
  template < class T > BiList< T > *remove(BiList< T > *h)
  {
    if (!h)
    {
      return nullptr;
    }
    if (h->next == h)
    {
      delete h; // ~T::T()
      return nullptr;
    }
    BiList< T > *next = h->next;
    h->prev->next = next;
    next->prev = h->prev;
    delete h; // ~T::T()
    return next;
  }

  // Удалить следующий элемент списка, вернуть указатель новый следующий
  template < class T > BiList< T > *eraseNext(BiList< T > *h)
  {
    return remove(h->next);
  }

  // Удалить предыдущий элемент списка, вернуть указатель новый предыдущий
  template < class T > BiList< T > *erasePrev(BiList< T > *h)
  {
    return remove(h->prev);
  }

  // Удалить все элементы списка
  template < class T > BiList< T > *clear(BiList< T > *h)
  {
    while (h)
    {
      h = remove(h);
    }
    return h;
  }

  // Обойти элементы списка от текущего двигаясь влево, пока снова не встретим end. Для каждого
  // элемента вызывать F(val)
  template < class T, class F > F leftTraverse(F f, BiList< T > *h, BiList< T > *e) // F::F(const &F)
  {
    if (!h)
    {
      return f;
    }
    do
    {
      f(h->val); // F::operator()(T). T::T(const T& val)
      h = h->prev;
    } while (h != e);
    return f;
  }

  // Обойти элементы списка от текущего двигаясь вправо, пока снова не встретим end. Для каждого
  // элемента вызывать F(val)
  template < class T, class F > F rightTraverse(F f, BiList< T > *h, BiList< T > *e)
  {
    if (!h)
    {
      return f;
    }
    do
    {
      f(h->val); // F::operator()(T). T::T(const T& val)
      h = h->next;
    } while (h != e);
    return f;
  }

  // Обойти все элементы списка от текущего двигаясь влево, пока не вернемся в начальный элемент. Для каждого
  // элемента вызывать F(val)
  template < class T, class F > F leftTraverse(F f, BiList< T > *h)
  {
    return leftTraverse(f, h, h);
  }

  // Обойти все элементы списка от текущего двигаясь вправо, пока не вернемся в начальный элемент Для каждого
  // элемента вызывать F(val)
  template < class T, class F > F rightTraverse(F f, BiList< T > *h)
  {
    return rightTraverse(f, h, h);
  }

  // Обойти все элементы по кругу и вернуть их количество.
  template < class T > size_t size(BiList< T > *h)
  {
    size_t count = 0;
    rightTraverse([&count](const T &) { count++; }, h);
    return count;
  }

  // Конвертирует массив элементов типа T в кольцевой двусвязный список.
  // Возвращает указатель на первый элемент.
  // Если size == 0, возвращает nullptr.
  template < class T > BiList< T > *convert(const T *a, size_t k)
  {
    if (!k || !a)
    {
      return nullptr;
    }
    BiList< T > *head = create< T >(a[0]);
    BiList< T > *tail = head;
    try
    {
      for (size_t i = 1; i < k; ++i)
      {
        tail = insertAfter(tail, a[i]);
      }
    }
    catch (...)
    {
      clear(head);
      throw;
    }
    return head;
  }
}

#endif

### Получившийся неявный интерфейс:
 1) Наличие конструктора копирования
 2) Наличие деструктора
 3) В traverse наличие перегруженного оператора круглые скобки, принимающего в качестве аргумента T
 4) В traverse наличие конструктора копирования у объекта F

---

Создает пустой двухсвязный список, который ссылается сам на себя в next и prev
```cpp
template < class T > BiList< T > *create(const T &val);
```

Создать новый элемент перед текущим
```cpp
template < class T > BiList< T > *insertBefore(BiList< T > *h, const T &val);
```

Создать новый элемент после текущего
```cpp
template < class T > BiList< T > *insertAfter(BiList< T > *h, const T &val);
```

Удалить текущий элемент списка, вернуть указатель на следующий
```cpp
template < class T > BiList< T > *remove(BiList< T > *h);
```

Удалить следующий элемент списка, вернуть указатель новый следующий
```cpp
template < class T > BiList< T > *eraseNext(BiList< T > *h);
```

Удалить предыдущий элемент списка, вернуть указатель новый предыдущий
```cpp
template < class T > BiList< T > *erasePrev(BiList< T > *h);
```

Удалить все элементы списка
```cpp
template < class T > BiList< T > *clear(BiList< T > *h);
```

Обойти элементы списка от текущего двигаясь влево, пока снова не встретим end. Для каждого элемента вызывать F(val)
```cpp
template < class T, class F > F leftTraverse(F f, BiList< T > *h, BiList< T > *e);
```

Обойти элементы списка от текущего двигаясь вправо, пока снова не встретим end. Для каждого элемента вызывать F(val)
```cpp
template < class T, class F > F rightTraverse(F f, BiList< T > *h, BiList< T > *e);
```

Обойти все элементы списка от текущего двигаясь влево, пока не вернемся в начальный элемент. Для каждого элемента вызывать F(val)
```cpp
template < class T, class F > F leftTraverse(F f, BiList< T > *h);
```

Обойти все элементы списка от текущего двигаясь вправо, пока не вернемся в начальный элемент Для каждого элемента вызывать F(val)
```cpp
template < class T, class F > F rightTraverse(F f, BiList< T > *h);
```

Обойти все элементы по кругу и вернуть их количество.
```cpp
template < class T > size_t size(BiList< T > *h);
```

Конвертирует массив элементов типа T в кольцевой двусвязный список. Возвращает указатель на первый элемент. Если size == 0, возвращает nullptr.
```cpp
template < class T > BiList< T > *convert(const T *a, size_t k);
```
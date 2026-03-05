#include "BiList.hpp"
#include "boost_test.hpp"
#include <boost/test/tools/old/interface.hpp>

BOOST_AUTO_TEST_SUITE(BiListBasicTests)

using namespace khasnulin;

BOOST_AUTO_TEST_CASE(test_create_and_loop)
{
  BiList< int > *node = create< int >(42);

  BOOST_REQUIRE(node != nullptr);
  BOOST_CHECK_EQUAL(node->val, 42);
  BOOST_CHECK(node->next == node);
  BOOST_CHECK(node->prev == node);
}

BOOST_AUTO_TEST_CASE(test_insertion_logic)
{
  BiList< int > *h = create< int >(10);
  insertAfter(h, 20);

  BOOST_CHECK_EQUAL(size(h), 2);
  BOOST_CHECK(h->next != h);
  BOOST_CHECK_EQUAL(h->next->val, 20);
  BOOST_CHECK_EQUAL(h->next->next->val, 10);
  BOOST_CHECK_EQUAL(h->prev->val, 20);

  clear(h);
}

struct Person
{
  std::string n_;
  int a_;

  Person(std::string n, int a):
      n_(std::move(n)),
      a_(a)
  {
  }
  Person(std::string n):
      n_(std::move(n)),
      a_(0)
  {
  }
  bool operator==(const Person &c) const
  {
    return n_ == c.n_ && a_ == c.a_;
  }
};

BOOST_AUTO_TEST_CASE(test_perfect_forwarding_struct)
{
  BiList< Person > *list = create< Person >("Vasiliy", 29);
  insertAfter(list, "Dmitriy", 19);
  insertBefore(list, "Ignat");

  BOOST_CHECK_EQUAL(list->val.n_, "Vasiliy");
  BOOST_CHECK_EQUAL(list->val.a_, 29);
  BOOST_CHECK_EQUAL(list->next->val.n_, "Dmitriy");
  BOOST_CHECK_EQUAL(list->prev->val.a_, 0);

  clear(list);
}

BOOST_AUTO_TEST_CASE(test_remove_logic)
{
  BiList< int > *h = create< int >(1);
  h = insertAfter(h, 2);
  h = insertAfter(h, 3);

  BiList< int > *next_node = remove(h);

  BOOST_REQUIRE(next_node != nullptr);
  BOOST_CHECK_EQUAL(next_node->val, 1);
  BOOST_CHECK_EQUAL(size(next_node), 2);
  clear(h);
}

BOOST_AUTO_TEST_CASE(test_remove_empty_logic)
{
  BiList< int > *h = create< int >(1);
  h = insertBefore< int >(h, 2);
  h = insertAfter< int >(h, 3);

  h = remove(h);
  h = remove(h);
  BOOST_REQUIRE(h != nullptr);
  BOOST_CHECK_EQUAL(h->val, 2);
  BOOST_CHECK_EQUAL(size(h), 1);

  h = remove(h);
  h = remove(h);
  BOOST_REQUIRE(h == nullptr);
  clear(h);
}

BOOST_AUTO_TEST_CASE(test_clear_list)
{
  BiList< int > *h = create< int >(1);
  h = insertBefore(h, 2);
  h = insertAfter(h, 3);
  h = insertAfter(h, 4);
  h = insertAfter(h, 5);

  BOOST_CHECK_EQUAL(size(h), 5);
  h = clear(h);
  BOOST_CHECK_EQUAL(size(h), 0);
  BOOST_REQUIRE(h == nullptr);
  clear(h);
}

BOOST_AUTO_TEST_CASE(test_right_traverse_sum)
{
  BiList< int > *h = create< int >(1);
  insertAfter(h, 2);
  insertAfter(h, 3);

  int sum = 0;
  rightTraverse([&sum](int v) { sum += v; }, h);

  BOOST_CHECK_EQUAL(sum, 6);
  clear(h);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ConversionTests)

using namespace khasnulin;

BOOST_AUTO_TEST_CASE(test_for_empty_array)
{
  int *arr = nullptr;
  BiList< int > *list = convert(arr, 0);
  BOOST_REQUIRE(list == nullptr);
}

BOOST_AUTO_TEST_CASE(test_for_single_element_array)
{
  int arr[1] = {1};
  BiList< int > *list = convert(arr, 1);

  BOOST_REQUIRE(list != nullptr);
  BOOST_CHECK_EQUAL(size(list), 1);
  BOOST_CHECK(list->next == list);

  list = clear(list);
  BOOST_REQUIRE(list == nullptr);
}

BOOST_AUTO_TEST_CASE(test_from_regular_array)
{
  int arr[] = {10, 20, 30};
  BiList< int > *list = convert(arr, 3);

  BOOST_REQUIRE(list != nullptr);
  BOOST_CHECK_EQUAL(size(list), 3);
  BOOST_CHECK_EQUAL(list->val, 10);
  BOOST_CHECK_EQUAL(list->next->val, 20);
  BOOST_CHECK_EQUAL(list->next->next->val, 30);
  BOOST_CHECK_EQUAL(list->next->next->next, list);

  BOOST_CHECK_EQUAL(list->prev->val, 30);

  clear(list);
}

BOOST_AUTO_TEST_SUITE_END()
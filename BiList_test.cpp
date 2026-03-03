#include "boost_test.hpp"

BOOST_AUTO_TEST_SUITE(BiListBasicTests)

using namespace khasnulin;

BOOST_AUTO_TEST_CASE(test_create_and_loop)
{
  BiList< int > *node = create(42);

  BOOST_REQUIRE(node != nullptr);
  BOOST_CHECK_EQUAL(node->val, 42);
  BOOST_CHECK(node->next == node);
  BOOST_CHECK(node->prev == node);
}

BOOST_AUTO_TEST_CASE(test_insertion_logic)
{
  BiList< int > *h = create(10);
  insertAfter(h, 20);

  BOOST_CHECK_EQUAL(size(h), 2);
  BOOST_CHECK(h->next != h);
  BOOST_CHECK_EQUAL(h->next->val, 20);
  BOOST_CHECK_EQUAL(h->next->next->val, 10);
  BOOST_CHECK_EQUAL(h->prev->val, 20);
}

BOOST_AUTO_TEST_CASE(test_remove_logic)
{
  BiList< int > *h = create(1);
  h = insertAfter(h, 2);
  h = insertAfter(h, 3);

  BiList< int > *next_node = remove(h);

  BOOST_REQUIRE(next_node != nullptr);
  BOOST_CHECK_EQUAL(next_node->val, 1);
  BOOST_CHECK_EQUAL(size(next_node), 2);
}

BOOST_AUTO_TEST_CASE(test_remove_empty_logic)
{
  BiList< int > *h = create(1);
  h = insertBefore(h, 2);
  h = insertAfter(h, 3);

  h = remove(h);
  h = remove(h);
  BOOST_REQUIRE(h != nullptr);
  BOOST_CHECK_EQUAL(h->val, 2);
  BOOST_CHECK_EQUAL(size(h), 1);

  h = remove(h);
  h = remove(h);
  BOOST_REQUIRE(h == nullptr);
}

BOOST_AUTO_TEST_CASE(test_clear_list)
{
  BiList< int > *h = create(1);
  h = insertBefore(h, 2);
  h = insertAfter(h, 3);
  h = insertAfter(h, 4);
  h = insertAfter(h, 5);

  BOOST_CHECK_EQUAL(size(h), 5);
  h = clear(h);
  BOOST_CHECK_EQUAL(size(h), 0);
  BOOST_REQUIRE(h == nullptr);
}

BOOST_AUTO_TEST_CASE(test_right_traverse_sum)
{
  BiList< int > *h = create(1);
  insertAfter(h, 2);
  insertAfter(h, 3);

  int sum = 0;
  rightTraverse([&sum](int v) { sum += v; }, h);

  BOOST_CHECK_EQUAL(sum, 1);
}

BOOST_AUTO_TEST_SUITE_END()
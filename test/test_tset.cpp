#include "tset.h"
#include <gtest.h>

class TestTSet : public ::testing::Test
{
protected:
	TSet *s;
public:
	void SetUp()
	{
		s = new TSet(5);
	}
	void TearDown()
	{
		delete s;
	}
};

class TestTSets : public ::testing::Test
{
protected:
	TSet *s1, *s2, *s3, *s4, *s5, *sres, *sres_6;
public:
	void SetUp()
	{
		s1 = new TSet(5);
		// s1 = {1, 3}
		s1->InsElem(1);
		s1->InsElem(3);
		s2 = new TSet(5);
		// s2 = {1, 3}
		s2->InsElem(1);
		s2->InsElem(3);
		s3 = new TSet(6);
		// s3 = {1, 2, 3}
		s3->InsElem(1);
		s3->InsElem(2);
		s3->InsElem(3);
		s4 = new TSet(5);
		// s4 = {0, 2, 4}
		s4->InsElem(0);
		s4->InsElem(2);
		s4->InsElem(4);
		s5 = new TSet(5);
		// s5 = {1, 2}
		s5->InsElem(1);
		s5->InsElem(2);
		sres = new TSet(5);
		// sres = {1, 2, 3}
		sres->InsElem(1);
		sres->InsElem(2);
		sres->InsElem(3);
		sres_6 = new TSet(6);
		// sres = {1, 3}
		sres_6->InsElem(1);
		sres_6->InsElem(3);
	}
	void TearDown()
	{
		delete s1;
		delete s2;
		delete s3;
		delete s4;
		delete s5;
		delete sres;
		delete sres_6;
	}
};


TEST_F(TestTSet, can_get_max_power_set)
{
  EXPECT_EQ(5, s->GetMaxPower());
}

TEST_F(TestTSet, can_insert_non_existing_element)
{
  s->InsElem(3);

  EXPECT_NE(s->IsMember(3), 0);
}

TEST_F(TestTSet, can_insert_existing_element)
{
  s->InsElem(3);
  s->InsElem(3);

  EXPECT_NE(s->IsMember(3), 0);
}

TEST_F(TestTSet, can_delete_non_existing_element)
{
  s->DelElem(3);

  EXPECT_EQ(s->IsMember(3), 0);
}

TEST_F(TestTSet, can_delete_existing_element)
{
  s->InsElem(3);
  EXPECT_GT(s->IsMember(3), 0);

  s->DelElem(3);
  EXPECT_EQ(s->IsMember(3), 0);
}

TEST_F(TestTSets, compare_two_sets_of_non_equal_sizes)
{
  EXPECT_NE(*s1, *s3);
}

TEST_F(TestTSets, compare_two_equal_sets)
{
  EXPECT_EQ(*s1, *s2);
}

TEST_F(TestTSets, compare_two_non_equal_sets)
{
  EXPECT_NE(*s1, *s5);
}

TEST_F(TestTSets, can_assign_set_of_equal_size)
{
  *s1 = *s5;

  EXPECT_EQ(*s1, *s5);
}

TEST_F(TestTSets, can_assign_set_of_greater_size)
{
  *s1 = *s3;

  EXPECT_EQ(*s1, *s3);
}

TEST_F(TestTSets, can_assign_set_of_less_size)
{

  *s3 = *s1;

  EXPECT_EQ(*s3, *s1);
}

TEST_F(TestTSets, can_insert_non_existing_element_using_plus_operator)
{
  *s1 = *s1 + 2;

  EXPECT_EQ(1, s1->IsMember(3));
}

TEST_F(TestTSets, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
  ASSERT_ANY_THROW(*s1 = *s1 + 8);
}

TEST_F(TestTSets, can_insert_existing_element_using_plus_operator)
{
  *s1 = *s1 + 3;

  EXPECT_EQ(1, s1->IsMember(3));
}

TEST_F(TestTSets, check_size_of_the_combination_of_two_sets_of_equal_size)
{
  *sres = *s1 + *s2;

  EXPECT_EQ(5, sres->GetMaxPower());
}

TEST_F(TestTSets, can_combine_two_sets_of_equal_size)
{
  *s1 = *s1 + *s5;

  EXPECT_EQ(*sres, *s1);
}

TEST_F(TestTSets, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
  *sres = *s1 + *s3;

  EXPECT_EQ(6, sres->GetMaxPower());
}

TEST_F(TestTSets, can_combine_two_sets_of_non_equal_size)
{
  *sres = *s1 + *s3;

  EXPECT_EQ(*sres, *s3);
}

TEST_F(TestTSets, can_intersect_two_sets_of_equal_size)
{
  *sres = *s1 * *s2;

  EXPECT_EQ(*sres, *s1);
}

TEST_F(TestTSets, can_intersect_two_sets_of_non_equal_size)
{
  *s1 = *s1 * *s3;

  EXPECT_EQ(*sres_6, *s1);
}

TEST_F(TestTSets, check_negation_operator)
{
  *sres = ~(*s1);

  EXPECT_EQ(*sres, *s4);
}

TEST_F(TestTSets, throws_when_insert_negative_elem)
{
  ASSERT_ANY_THROW(s1->InsElem(-3));
}

TEST_F(TestTSets, throws_when_delete_negative_elem)
{
  ASSERT_ANY_THROW(s1->DelElem(-3));
}

TEST_F(TestTSets, can_combine_three_sets_of_equal_size)
{
  *s1 = *s1 + *s2 + *s5;

  EXPECT_EQ(*sres, *s1);
}
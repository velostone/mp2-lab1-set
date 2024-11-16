#include "tset.h"
#include <gtest.h>

class TestTSet : public ::testing::Test
{
protected:
	TSet *s;
public:
	void SetUp()
	{
		this->s = new TSet(5);
	}
	void TearDown()
	{
		delete this->s;
	}
};

class TestTSets : public ::testing::Test
{
protected:
	TSet *s1, *s2, *s3, *s4, *s5, *sres, *sres_6;
public:
	void SetUp()
	{
		this->s1 = new TSet(5);
		// s1 = {1, 3}
		this->s1->InsElem(1);
		this->s1->InsElem(3);
		this->s2 = new TSet(5);
		// s2 = {1, 3}
		this->s2->InsElem(1);
		this->s2->InsElem(3);
		this->s3 = new TSet(6);
		// s3 = {1, 2, 3}
		this->s3->InsElem(1);
		this->s3->InsElem(2);
		this->s3->InsElem(3);
		this->s4 = new TSet(5);
		// s4 = {0, 2, 4}
		this->s4->InsElem(0);
		this->s4->InsElem(2);
		this->s4->InsElem(4);
		this->s5 = new TSet(5);
		// s5 = {1, 2}
		this->s5->InsElem(1);
		this->s5->InsElem(2);
		this->sres = new TSet(5);
		// sres = {1, 2, 3}
		this->sres->InsElem(1);
		this->sres->InsElem(2);
		this->sres->InsElem(3);
		this->sres_6 = new TSet(6);
		// sres = {1, 3}
		this->sres_6->InsElem(1);
		this->sres_6->InsElem(3);
	}
	void TearDown()
	{
		delete this->s1;
		delete this->s2;
		delete this->s3;
		delete this->s4;
		delete this->s5;
		delete this->sres;
		delete this->sres_6;
	}
};


TEST_F(TestTSet, can_get_max_power_set)
{
  EXPECT_EQ(5, this->s->GetMaxPower());
}

TEST_F(TestTSet, can_insert_non_existing_element)
{
	this->s->InsElem(3);

  EXPECT_NE(this->s->IsMember(3), 0);
}

TEST_F(TestTSet, can_insert_existing_element)
{
	this->s->InsElem(3);
	this->s->InsElem(3);

  EXPECT_NE(this->s->IsMember(3), 0);
}

TEST_F(TestTSet, can_delete_non_existing_element)
{
	this->s->DelElem(3);

  EXPECT_EQ(this->s->IsMember(3), 0);
}

TEST_F(TestTSet, can_delete_existing_element)
{
	this->s->InsElem(3);
  EXPECT_GT(this->s->IsMember(3), 0);

  this->s->DelElem(3);
  EXPECT_EQ(this->s->IsMember(3), 0);
}

TEST_F(TestTSets, compare_two_sets_of_non_equal_sizes)
{
  EXPECT_NE(*this->s1, *this->s3);
}

TEST_F(TestTSets, compare_two_equal_sets)
{
  EXPECT_EQ(*this->s1, *this->s2);
}

TEST_F(TestTSets, compare_two_non_equal_sets)
{
  EXPECT_NE(*this->s1, *this->s5);
}

TEST_F(TestTSets, can_assign_set_of_equal_size)
{
  *this->s1 = *this->s5;

  EXPECT_EQ(*this->s1, *this->s5);
}

TEST_F(TestTSets, can_assign_set_of_greater_size)
{
  *this->s1 = *this->s3;

  EXPECT_EQ(*this->s1, *this->s3);
}

TEST_F(TestTSets, can_assign_set_of_less_size)
{

  *this->s3 = *this->s1;

  EXPECT_EQ(*this->s3, *this->s1);
}

TEST_F(TestTSets, can_insert_non_existing_element_using_plus_operator)
{
  *this->s1 = *this->s1 + 2;

  EXPECT_EQ(1, this->s1->IsMember(3));
}

TEST_F(TestTSets, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
  ASSERT_ANY_THROW(*this->s1 = *this->s1 + 8);
}

TEST_F(TestTSets, can_insert_existing_element_using_plus_operator)
{
  *this->s1 = *this->s1 + 3;

  EXPECT_EQ(1, this->s1->IsMember(3));
}

TEST_F(TestTSets, check_size_of_the_combination_of_two_sets_of_equal_size)
{
  *this->sres = *this->s1 + *this->s2;

  EXPECT_EQ(5, this->sres->GetMaxPower());
}

TEST_F(TestTSets, can_combine_two_sets_of_equal_size)
{
  *this->s1 = *this->s1 + *this->s5;

  EXPECT_EQ(*this->sres, *this->s1);
}

TEST_F(TestTSets, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
  *this->sres = *this->s1 + *this->s3;

  EXPECT_EQ(6, this->sres->GetMaxPower());
}

TEST_F(TestTSets, can_combine_two_sets_of_non_equal_size)
{
  *this->sres = *this->s1 + *this->s3;

  EXPECT_EQ(*this->sres, *this->s3);
}

TEST_F(TestTSets, can_intersect_two_sets_of_equal_size)
{
  *this->sres = *this->s1 * *this->s2;

  EXPECT_EQ(*this->sres, *this->s1);
}

TEST_F(TestTSets, can_intersect_two_sets_of_non_equal_size)
{
  *this->s1 = *this->s1 * *this->s3;

  EXPECT_EQ(*this->sres_6, *this->s1);
}

TEST_F(TestTSets, check_negation_operator)
{
  *this->sres = ~(*this->s1);

  EXPECT_EQ(*this->sres, *this->s4);
}

TEST_F(TestTSets, throws_when_insert_negative_elem)
{
  ASSERT_ANY_THROW(this->s1->InsElem(-3));
}

TEST_F(TestTSets, throws_when_delete_negative_elem)
{
  ASSERT_ANY_THROW(this->s1->DelElem(-3));
}

TEST_F(TestTSets, can_combine_three_sets_of_equal_size)
{
  *this->s1 = *this->s1 + *this->s2 + *this->s5;

  EXPECT_EQ(*this->sres, *this->s1);
}
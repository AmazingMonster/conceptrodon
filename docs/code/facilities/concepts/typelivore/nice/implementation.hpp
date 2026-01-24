/**********************/
/**** Dependencies ****/
/**********************/

template<typename...>
struct Yes
{
    static constexpr bool value {true};
};

/************************/
/**** Implementation ****/
/************************/

template<typename...Args>
concept Nice = Yes<Args...>::value;

/***********************/
/**** First Example ****/
/***********************/

#include <type_traits>

/**** Tester ****/
template<typename...>
struct Tester
{ static constexpr int value {0}; };

template<typename I, typename J>
requires Nice<typename I::type>
struct Tester<I, J>
{ static constexpr int value {1}; };

template<typename I, typename J>
requires Nice<typename I::type> && Nice<typename J::type>
struct Tester<I, J>
{ static constexpr int value {2}; };

/**** Test ****/
static_assert(Tester<int, std::type_identity<int>>::value == 0);
static_assert(Tester<std::type_identity<int>, int>::value == 1);
static_assert(Tester<std::type_identity<int>, std::type_identity<int>>::value == 2);


/************************/
/**** Second Example ****/
/************************/

/**** Good ****/
template<typename...>
concept Good = true;

/**** Tester ****/
template<typename...>
struct AnotherTester
{ static constexpr int value {0}; };

template<typename I, typename J>
requires Good<typename I::type>
struct AnotherTester<I, J>
{ static constexpr int value {1}; };

template<typename I, typename J>
requires Good<typename I::type> && Good<typename J::type>
struct AnotherTester<I, J>
{ static constexpr int value {2}; };

/**** Test ****/
static_assert(AnotherTester<int, std::type_identity<int>>::value == 0);
static_assert(AnotherTester<std::type_identity<int>, int>::value == 1);
static_assert(AnotherTester<std::type_identity<int>, std::type_identity<int>>::value == 2);
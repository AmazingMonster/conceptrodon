/**********************/
/**** Dependencies ****/
/**********************/

template<auto...>
struct Yes
{
    static constexpr bool value {true};
};

/************************/
/**** Implementation ****/
/************************/

template<auto...Args>
concept Nice = Yes<Args...>::value;

/***********************/
/**** First Example ****/
/***********************/

#include <type_traits>

/**** Tester ****/
template<auto...>
struct Tester
{ static constexpr int value {0}; };

template<auto I, auto J>
requires Nice<I.value>
struct Tester<I, J>
{ static constexpr int value {1}; };

template<auto I, auto J>
requires Nice<I.value> && Nice<J.value>
struct Tester<I, J>
{ static constexpr int value {2}; };

/**** Tests ****/
static_assert(Tester<0>::value == 0);
static_assert(Tester<std::integral_constant<int, 0>{}, 0>::value == 1);
static_assert(Tester<std::integral_constant<int, 0>{}, std::integral_constant<int, 0>{}>::value == 2);


/************************/
/**** Second Example ****/
/************************/

/**** Good ****/
template<auto...>
concept Good = true;

/**** Tester ****/
template<auto...>
struct AnotherTester
{ static constexpr int value {0}; };

template<auto I, auto J>
requires Good<I.value>
struct AnotherTester<I, J>
{ static constexpr int value {1}; };

template<auto I, auto J>
requires Good<I.value> && Good<J.value>
struct AnotherTester<I, J>
{ static constexpr int value {2}; };

/**** Test ****/
static_assert(AnotherTester<0>::value == 0);
static_assert(AnotherTester<std::integral_constant<int, 0>{}, 0>::value == 1);
static_assert(AnotherTester<std::integral_constant<int, 0>{}, std::integral_constant<int, 0>{}>::value == 2);
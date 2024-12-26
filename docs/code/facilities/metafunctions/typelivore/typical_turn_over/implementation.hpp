/**********************/
/**** Dependencies ****/
/**********************/

/**** ExtendBack ****/
template<typename...>
struct ExtendBack {};

template<
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct TypicalTurnOver {};

template<typename First>
struct TypicalTurnOver<First>
{
    using type = Capsule<First>;
};

template<typename First, typename Second>
struct TypicalTurnOver<First, Second>
{
    using type = Capsule<Second, First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type 
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Mold<Second, First>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int**, int**, int*, int>;

/**** Result ****/
using Result = TypicalTurnOver<int, int*, int**, int**>
::type;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
/**********************/
/**** Dependencies ****/
/**********************/

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** ExtendBack ****/
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};

/************************/
/**** Implementation ****/
/************************/

template<auto...>
struct TypicalTurnOver {};

template<auto First>
struct TypicalTurnOver<First>
{
    using type = Shuttle<First>;
};

template<auto First, auto Second>
struct TypicalTurnOver<First, Second>
{
    using type = Shuttle<Second, First>;
};

template<auto First, auto Second, auto...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Page<Second, First>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<2, 2, 1, 0>;

/**** Result ****/
using Result = TypicalTurnOver<0, 1, 2, 2>::type;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
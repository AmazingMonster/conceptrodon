/**********************/
/**** Dependencies ****/
/**********************/

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** ExtendBack ****/
// We will use this function to concatenate two parts.
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

/**** Send ****/
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** Varybivore::TypicalTurnOver ****/
namespace Varybivore {

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

}

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct CognateReverse
{
    template<auto...Variables>
    using Page = Send
    <
        typename Varybivore::TypicalTurnOver<Variables...>
        ::type
    >
    ::template Rail<Operation>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2, 1, 0>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateReverse<Operation>::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

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

/**** Varybivore::TypicalReiterate ****/
namespace Varybivore {

template<auto...Variables>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Shuttle<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Shuttle<Variables...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Page<Variables..., Variables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Varybivore::TypicalReiterate<Variables...>
            ::template ProtoPage<Amount>::type
        >
        ::template Rail<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

/**** Result ****/
using Result = CognateRepeat<Operation>
::Page<4>
::Page<0, 1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
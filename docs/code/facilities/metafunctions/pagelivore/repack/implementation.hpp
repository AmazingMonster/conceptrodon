/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct Repack
{

    template<typename...>
    struct Detail {};

// Base Case:

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    {
        using type = Operation<Variables...>;
    };

    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    {
        using type = Operation<Variables...>;
    };

// Recursive Case:

    template
    <
        template<auto...> class SequenceA,
        template<auto...> class SequenceB,
        auto...VariableAs, 
        auto...VariableBs,
        typename...Others
    >
    struct Detail<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
    {
        using type = Detail
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::type;
    };

    template
    <
        template<typename, auto...> class SequenceA,
        template<typename, auto...> class SequenceB,
        typename TA,
        typename TB,
        auto...VariableAs, 
        auto...VariableBs,
        typename...Others
    >
    struct Detail<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
    {
        using type = Detail
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::type;
    };

    template<typename...PackedSequences>
    using Mold = Detail<PackedSequences...>::type;
};

/*****************/
/**** Example ****/
/*****************/

/**** NewVessel ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<0, 1, 2, 3>;

/**** Result ****/
using Result = Repack<NewVessel>
::Mold
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>
#include <utility>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/************************/
/**** Implementation ****/
/************************/

/**** KindredRepack ****/
template<typename...>
struct KindredRepack {};

// Base Case:

template<template<auto...> class Sequence, auto...Variables>
struct KindredRepack<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct KindredRepack<Sequence<Type, Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation
        <static_cast<std::make_signed_t<size_t>>(Variables)...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
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
struct KindredRepack<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
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
struct KindredRepack<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
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
using Result = KindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


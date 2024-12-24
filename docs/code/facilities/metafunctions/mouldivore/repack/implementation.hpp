/**********************/
/**** Dependencies ****/
/**********************/

template<typename...>
struct Capsule;

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct Repack
{
    template<typename...>
    struct Detail {};

// Base Case:

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    {
        using type = Operation<Elements...>;
    };

// Recursive Case:

    template
    <
        template<typename...> class ContainerA,
        template<typename...> class ContainerB,
        typename...ElementAs, 
        typename...ElementBs,
        typename...Others
    >
    struct Detail<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
    {
        using type = Detail
        <
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::type;
    };

    template<typename...PackedContainers>
    using Mold = Detail<PackedContainers...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <tuple>
#include <concepts>

/**** Container ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct Container;

/**** SupposedResult ****/
using SupposedResult = Container<int, int*, int**, int***>;

/**** Result ****/
using Result = Repack<Container>
::Mold
<
    std::tuple<int>,
    std::tuple<int*, int**>,
    std::tuple<int***>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/**********************/
/**** Dependencies ****/
/**********************/

template<typename...>
struct Capsule;

/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<typename...> class Container, typename...Elements>
struct KindredRepack<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
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
struct KindredRepack<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            // Put ElementAs... and ElementBs into the `Capsule`
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <tuple>

/**** NewVessel ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<int, float, float*, double>;

/**** Result ****/
using Result = KindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
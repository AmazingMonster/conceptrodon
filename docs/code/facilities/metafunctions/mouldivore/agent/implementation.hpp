/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    { using type = Operation<Elements...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = Metafunction<Capsule<int, int*, int**>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
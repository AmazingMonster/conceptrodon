/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    { using type = Operation<Variables...>; };
    
    // This specialization handles `std::integer_sequence`.
    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    { using type = Operation<Variables...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result = Metafunction<Shuttle<0, 1, 2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

#include <utility>

/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    static_cast<size_t>(0),
    static_cast<size_t>(1),
    static_cast<size_t>(2)
>;

/**** Result ****/
using Result_1 = Metafunction<std::index_sequence<0, 1, 2>>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);


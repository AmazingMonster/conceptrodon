/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class Operation>
struct Reveal
{
    template<template<auto...> class...Sequences>
    using Rail = Operation<Sequences...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Dummy Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Operation ****/
template<template<auto...> class...Args>
struct Operation
{ using type = Carrier<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Carrier<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = Reveal<Operation>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

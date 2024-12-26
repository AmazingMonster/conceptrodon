/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class Operation>
struct Conceal
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    { using type = Operation<Sequences...>; };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;
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

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = Conceal<Operation>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3, Seq_0, Seq_1>::type;

/**** Result ****/
static_assert(std::same_as<Result, SupposedResult>);

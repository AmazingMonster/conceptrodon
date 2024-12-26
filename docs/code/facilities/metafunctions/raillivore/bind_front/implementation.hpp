/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class Operation>
struct BindFront
{
    template<template<auto...> class...Beginnings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Beginnings..., Sequences...>;
    };

    template<template<auto...> class...Beginnings>
    using Rail = ProtoRail<Beginnings...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Arguments ****/
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
using SupposedResult = Operation<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = BindFront<Operation>
::Rail<Seq_0, Seq_1>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


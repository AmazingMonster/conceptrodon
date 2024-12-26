/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class Operation>
struct BindBack
{
    template<template<auto...> class...Endings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Sequences..., Endings...>;
    };

    template<template<auto...> class...Endings>
    using Rail = ProtoRail<Endings...>;
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
using SupposedResult = Operation<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = BindBack<Operation>
::Rail<Seq_0, Seq_1>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


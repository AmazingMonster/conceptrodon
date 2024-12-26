/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<auto...> class...Agreements>
        using Rail = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>
#include <utility>

/**** Operation ****/
template<template<auto...> class...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<std::index_sequence>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Rail<std::index_sequence>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

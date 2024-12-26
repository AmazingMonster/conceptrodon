/************************/
/**** Implementation ****/
/************************/

template<template<template<typename...> class...> class Operation>
struct Flip
{
    template<typename...Elements>
    struct ProtoMold 
    {
        template<template<typename...> class...Agreements>
        using Road = Operation<Agreements...>
        ::template Mold<Elements...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <tuple>

/**** Operation ****/
template<template<typename...> class...>
struct Operation
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<std::tuple>
::Mold<int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Flip<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*>::Road<std::tuple>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


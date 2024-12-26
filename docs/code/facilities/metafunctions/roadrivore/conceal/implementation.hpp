/************************/
/**** Implementation ****/
/************************/

template<template<template<typename...> class...> class Operation>
struct Conceal
{
    template<template<typename...> class...Sequences>
    struct ProtoRoad
    { using type = Operation<Sequences...>; };

    template<template<typename...> class...Sequences>
    using Road = ProtoRoad<Sequences...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Con_2, Con_3, Con_0, Con_1>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = Conceal<Operation>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3, Con_0, Con_1>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


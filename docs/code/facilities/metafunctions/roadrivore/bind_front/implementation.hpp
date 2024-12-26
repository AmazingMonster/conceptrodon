/************************/
/**** Implementation ****/
/************************/

template<template<template<typename...> class...> class Operation>
struct BindFront
{
    template<template<typename...> class...Beginnings>
    struct ProtoRoad
    {
        template<template<typename...> class...Containers>
        using Road = Operation<Beginnings..., Containers...>;
    };

    template<template<typename...> class...Beginnings>
    using Road = ProtoRoad<Beginnings...>;
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
using SupposedResult = Operation<Con_0, Con_1, Con_2, Con_3>;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = BindFront<Operation>
::Road<Con_0, Con_1>
::Road<Args...>;

/**** Result ****/
using Result = Metafunction<Con_2, Con_3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


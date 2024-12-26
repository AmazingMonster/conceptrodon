/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
    struct Detail<Stockroom<Sequences...>>
    { using type = Operation<Sequences...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Seq_0, Seq_1, Seq_2>;

/**** Result ****/
using Result = Metafunction<Carrier<Seq_0, Seq_1, Seq_2>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


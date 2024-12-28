/**********************/
/**** Dependencies ****/
/**********************/

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/************************/
/**** Implementation ****/
/************************/

/**** KindredRepack ****/
template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct KindredRepack<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Sequences...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<auto...> class...> class StockroomA,
    template<template<auto...> class...> class StockroomB,
    template<auto...> class...SequenceAs, 
    template<auto...> class...SequenceBs,
    typename...Others
>
struct KindredRepack<StockroomA<SequenceAs...>, StockroomB<SequenceBs...>, Others...>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Carrier<SequenceAs..., SequenceBs...>,
            Others...
        >::template Sail<Operation>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** NewVessel ****/
template<template<auto...> class...>
struct NewVessel;

/**** Vessels ****/
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

/**** Items ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult = NewVessel<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result = KindredRepack
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::Sail<NewVessel>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


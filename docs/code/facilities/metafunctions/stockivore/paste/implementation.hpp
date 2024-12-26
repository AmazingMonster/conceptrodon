/**********************/
/**** Dependencies ****/
/**********************/

template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedStockroom>
struct TypicalPaste<PackedStockroom>
{
    using type = PackedStockroom;
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
struct TypicalPaste<StockroomA<SequenceAs...>, StockroomB<SequenceBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        StockroomA<SequenceAs..., SequenceBs...>,
        Others...
    >::type;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...Args>
using Paste = TypicalPaste<Args...>::type;

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

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
using SupposedResult = Stockroom_0<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result = Paste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);


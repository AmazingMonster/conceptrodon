/**********************/
/**** Dependencies ****/
/**********************/

/**** Sequnivore::TypicalPaste ****/
namespace Sequnivore {

template<typename...>
struct TypicalPaste {};

// Base Case:
template<typename PackedSequence>
struct TypicalPaste<PackedSequence>
{
    using type = PackedSequence;
};

// Recursive Case:
template
<
    template<auto...> class SequenceA,
    template<auto...> class SequenceB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct TypicalPaste<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    using type = TypicalPaste
    <
        SequenceA<VariableAs..., VariableBs...>,
        Others...
    >::type;
};

template
<
    template<typename, auto...> class SequenceA,
    template<typename, auto...> class SequenceB,
    typename TA,
    typename TB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct TypicalPaste<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    using type = TypicalPaste
    <
        SequenceA<TA, static_cast<TA>(VariableAs)..., static_cast<TA>(VariableBs)...>,
        Others...
    >::type;
};

}

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Sieve ****/
template<template<auto...> class...Predicates>
struct Sieve
{
    template<auto Variable>
    struct Detail 
    { using type = Shuttle<>; };

    template<auto Variable>
    requires (not (...&&Predicates<Variable>::value))
    struct Detail<Variable>
    { using type = Shuttle<Variable>; };

    template<auto...Variables>
    using Page = Sequnivore::TypicalPaste
    <typename Detail<Variables>::type...>::type;
};

/**** Send ****/
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct CognateFilter
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Send
        <
            typename Sieve<Predicates...>
            ::template Page<Variables...>
        >
        ::template Rail<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** DivisibleByTwo ****/
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

/**** DivisibleByThree ****/
template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateFilter<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<1, 2, 15>;

/**** Result ****/
using Result = Metafunction<1, 12, 2, 6, 15>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
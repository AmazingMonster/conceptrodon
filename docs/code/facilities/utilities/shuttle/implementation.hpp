/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>
#include <utility>

/************************/
/**** Implementation ****/
/************************/

/**** Payload ****/
template<auto...Variables>
struct Payload
{
    static constexpr size_t size() { return sizeof...(Variables); }

    template<template<auto...> class Sequence>
    struct Detail { using type = Sequence<Variables...>; };

    template<template<auto...> class...Sequences>
    using Rail = Detail<Sequences...>::type;
};

/**** Payroll ****/
template<auto...>
struct Payroll {};

template<auto First, auto...Others>
struct Payroll<First, Others...>
{
    static constexpr auto first() { return First; }
};

template<auto First, auto Second, auto...Others>
struct Payroll<First, Second, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
};

template<auto First, auto Second, auto Third, auto...Others>
struct Payroll<First, Second, Third, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
};

template<auto First, auto Second, auto Third, auto Fourth, auto...Others>
struct Payroll<First, Second, Third, Fourth, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
    static constexpr auto fourth() { return Fourth; }
};

/**** Shuttle ****/
template<auto...Variables>
struct Shuttle
: public Payload<Variables...>
, public Payroll<Variables...> {};

template<size_t...Indices>
struct Shuttle<Indices...>
: public std::index_sequence<Indices...>
, public Payload<Indices...>
, public Payroll<Indices...> {};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Operation ****/
template<auto...>
struct Operation;

/**** Packed Vessel ****/
using PackedShuttle = Shuttle<nullptr, 1, 2, 2>;

/**** SupposedResult ****/
using SupposedResult = Operation<nullptr, 1, 2, 2>;
using Result = PackedShuttle::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedShuttle::size() == 4);

/***********************/
/**** Third Example ****/
/***********************/

static_assert(PackedShuttle::first() == nullptr);
static_assert(PackedShuttle::second() == 1);
static_assert(PackedShuttle::third() == 2);
static_assert(PackedShuttle::fourth() == 2);

/************************/
/**** Fourth Example ****/
/************************/

/**** Packed Vessel ****/
using PackedIndexShuttle = Shuttle
<
    static_cast<size_t>(0),
    static_cast<size_t>(1),
    static_cast<size_t>(2),
    static_cast<size_t>(2)
>;

/**** fun ****/
template<size_t...I>
constexpr bool fun(std::index_sequence<I...>)
{return true;}

/**** Test ****/
static_assert(fun(PackedIndexShuttle{}));
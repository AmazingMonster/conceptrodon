/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Gauge
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Device>
    struct ProtoRail<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};

template<auto Variable>
struct Gauge<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variable>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Transformations ****/
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

template<auto I>
struct AddTwo
{ 
    static constexpr auto value
    {I + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= Gauge<0>
::Rail<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = Gauge<0, 1, 2>
::Rail<AddOne>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = Gauge<0, 1, 2>
::Rail<AddZero, AddOne, AddTwo>
::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
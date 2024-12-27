/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct SensibleGauge
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<auto...> class...Devices>
        struct Detail
        {
            using type = Operation
            <Devices<Variables>::value...>;
        };
        
        template<template<auto...> class Device>
        struct Detail<Device>
        {
            using type = Operation
            <Device<Variables>::value...>;
        };

        template<template<auto...> class...Devices>
        using Rail = Detail<Devices...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto Variable>
struct SensibleGauge<Variable>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        template<template<auto...> class...Devices>
        using Rail = Operation
        <Devices<Variable>::value...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
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
using Result = SensibleGauge<0>
::Rail<Operation>
::Rail<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = SensibleGauge<0, 1, 2>
::Rail<Operation>
::Rail<AddOne>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = SensibleGauge<0, 1, 2>
::Rail<Operation>
::Rail<AddZero, AddOne, AddTwo>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
/************************/
/**** Implementation ****/
/************************/

template<typename IfTrue, typename IfFalse>
struct AnyConditional
{
    template<auto>
    struct Detail {};

    template<auto I>
    requires I
    struct Detail<I>
    { using type = IfTrue; };

    template<auto I>
    requires (!I)
    struct Detail<I>
    { using type = IfFalse; };

    /**** Page ****/
    template<auto...Agreements>
    using Page = Detail<(...||static_cast<bool>(Agreements))>::type;

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...||static_cast<bool>(Elements::value))>::type;

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Detail<(...||static_cast<bool>(Predicates<Elements...>::value))>::type;
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...||static_cast<bool>(Predicates<Variables...>::value))>::type;
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Choices ****/
struct IfTrue;
struct IfFalse;

/**** Select ****/
using Select = AnyConditional<IfTrue, IfFalse>;

/**** Tests ****/
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 0>, IfFalse>);

/************************/
/**** Second Example ****/
/************************/

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 0>
    >, 
    IfFalse
>);

/***********************/
/**** Third Example ****/
/***********************/

/**** VoidInt ****/
struct VoidInt;

/**** Void Tester ****/
template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

/**** IntTester ****/
template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

/**** Tests ****/
static_assert(std::same_as<Metafunction<int>, IfTrue>);
static_assert(std::same_as<Metafunction<void>, IfTrue>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Metafunction<double>, IfFalse>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfFalse>);

/************************/
/**** Fourth Example ****/
/************************/

/**** NonpositiveTester ****/
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

/**** Tests ****/
static_assert(std::same_as<Metafunction_1<1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<-1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<0>, IfTrue>);
static_assert(std::same_as<Metafunction_1<nullptr>, IfFalse>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfFalse>);
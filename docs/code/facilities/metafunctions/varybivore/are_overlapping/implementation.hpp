/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/************************/
/**** Implementation ****/
/************************/

template<auto...InspectedVariables>
struct AreOverlapping
: public Vay<InspectedVariables>...
{
    struct Detail
    {
        template<auto...>
        struct ProtoPage
        { using type = void; };
    };

// Recursive Case:
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        // `Detail` will stop recursion, achieving short-circuit.
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>,AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

// Base Case:
    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, AreOverlapping>::value, 
            void,
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
        
        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction = AreOverlapping<1, -1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<0, 1, 2>::value);

/************************/
/**** Second Example ****/
/************************/

static_assert(Metafunction<0, 2, 2>::value);

/***********************/
/**** Third Example ****/
/***********************/

static_assert(! Metafunction<0, 3, 2>::value);
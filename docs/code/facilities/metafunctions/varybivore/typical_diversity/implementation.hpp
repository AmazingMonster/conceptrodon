/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/************************/
/**** Implementation ****/
/************************/

template<auto...InspectedVariables>
struct TypicalDiversity: public Vay<InspectedVariables>...
{
// Recursive Case:
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;
    };

// Base Case:
    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            Shuttle<InspectedVariables...>, 
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TypicalDiversity<1, -1>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<1, -1, 0, 2>;

/**** Result ****/
using Result = Metafunction<0, 1, 2>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
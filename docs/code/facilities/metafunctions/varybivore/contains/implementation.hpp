/**********************/
/**** Dependencies ****/
/**********************/

/**** SolitaryIsSame ****/
template<auto, auto>
struct SolitaryIsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct SolitaryIsSame<Variable, Variable>
{ static constexpr bool value {true}; };

/**** IsSame ****/
template<auto Target, auto...Variables>
struct IsSame
{
    static constexpr bool value
    {(...&&SolitaryIsSame<Variables, Target>::value)};
};

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Contains
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {(...||(IsSame<Variables, Inspecting>::value))};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Contains<0, 1, 2, 2>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1>::value);
static_assert(! Metafunction<-1>::value);
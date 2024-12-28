/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct SetContains
: public Vay<Variables>...
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                Vay<Inspecting>,
                SetContains
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction = SetContains<0, 1, 2>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1>::value);
static_assert(! Metafunction<-1>::value);
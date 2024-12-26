/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct SetContains
: public std::type_identity<Elements>...
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                std::type_identity<Inspecting>,
                SetContains
            >::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafuntion ****/
template<typename...Args>
using Metafunction = SetContains<int, int*, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
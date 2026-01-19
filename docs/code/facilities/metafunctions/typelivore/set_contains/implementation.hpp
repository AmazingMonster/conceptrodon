/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/**** Tyy ****/
template<typename Element>
struct Tyy
{
    using type = Element;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct SetContains
: public Tyy<Elements>...
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                Tyy<Inspecting>,
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
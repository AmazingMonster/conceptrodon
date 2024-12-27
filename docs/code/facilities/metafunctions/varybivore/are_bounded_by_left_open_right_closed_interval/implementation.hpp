/************************/
/**** Implementation ****/
/************************/

template<auto Lower, auto Upper>
struct AreBoundedByLeftOpenRightClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr bool value
        { (...&&(Lower < Variables && not (Upper < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Lower < Variables && not (Upper < Variables))) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
// Create a left-open-right-closed interval (1, 4].
template<auto...Args>
using Metafunction
= AreBoundedByLeftOpenRightClosedInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<-1, 1, 2, 3, 4>::value);
/**********************/
/**** Dependencies ****/
/**********************/

#include <iostream>

/************************/
/**** Implementation ****/
/************************/

template<typename Target>
constexpr std::remove_cvref_t<Target> forward_if_rvalue(std::remove_cvref_t<Target> const & arg)
{
    return static_cast<std::remove_cvref_t<Target>>(arg);
}

template<typename Target>
constexpr Target&& forward_if_rvalue(std::remove_reference_t<Target>&& arg)
{
    return static_cast<Target&&>(arg);
}

/*****************/
/**** Example ****/
/*****************/

/**** Argument ****/
struct Argument
{
    Argument() = default;

    Argument(Argument const & argument)
    {
        std::cout << "Argument copy constructed" << std::endl;
    }
    
    Argument(Argument && argument)
    {
        std::cout << "Argument move constructed" << std::endl;
    }
};

/**** check****/
inline void check(Argument){}


/**** Tests ****/
inline void test()
{
    Argument arg{};

    {
        std::cout << "/**** Passing LValue ****/" << std::endl;
        check(forward_if_rvalue<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Passing XValue ****/" << std::endl;
        check(forward_if_rvalue<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Passing PRValue ****/" << std::endl;
        check(forward_if_rvalue<Argument>(Argument{}));
    }
}
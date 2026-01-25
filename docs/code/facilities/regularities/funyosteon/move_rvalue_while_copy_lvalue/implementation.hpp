/**********************/
/**** Dependencies ****/
/**********************/

#include <iostream>

/************************/
/**** Implementation ****/
/************************/

template<typename Arg>
requires std::is_lvalue_reference_v<Arg>
constexpr std::remove_cvref_t<Arg> move_rvalue_while_copy_lvalue(Arg&& arg)
{
    return static_cast<std::remove_cvref_t<Arg>>(arg);
}

template<typename Arg>
constexpr Arg&& move_rvalue_while_copy_lvalue(Arg&& arg)
{
    return static_cast<Arg&&>(arg);
}

/***********************/
/**** First Example ****/
/***********************/

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


/**** Test ****/
inline void test_move_rvalue_while_copy_lvalue()
{
    Argument arg{};

    {
        std::cout << "/**** Passing LValue ****/" << std::endl;
        check(move_rvalue_while_copy_lvalue(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Passing XValue ****/" << std::endl;
        check(move_rvalue_while_copy_lvalue(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** Passing PRValue ****/" << std::endl;
        check(move_rvalue_while_copy_lvalue(Argument{}));
    }
}

/************************/
/**** Second Example ****/
/************************/

/**** Test ****/
inline void test_std_forword()
{
    Argument arg{};

    {
        std::cout << "/**** std::forward: Passing LValue ****/" << std::endl;
        check(std::forward<Argument>(arg));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward: Passing XValue ****/" << std::endl;
        check(std::forward<Argument>(std::move(arg)));
    }

    std::cout << std::endl;

    {
        std::cout << "/**** std::forward: Passing PRValue ****/" << std::endl;
        check(std::forward<Argument>(Argument{}));
    }
}
<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Funyosteon::forward_if_rvalue`

<p style='text-align: right;'><a href="">To Index</a></p>

## Description

`Funyosteon::forward_if_rvalue` is a regular function.

When invoked by a lvalue, the function returns a copy of the argument. Otherwise, it forwards the argument similar to `std::forward`.

## Type Signature

## Structure

## Examples

We will forward values of `Argument` of different value categories to the function `check` and inspect how the argument is constructed. 

```C++
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
```

## Implementation

The implementation of `Funyosteon::forward_if_rvalue` is similar to that of `std::forward`.

The difference is that when provided by an lvalue, instead of forwarding it based on the target type, `Funyosteon::forward_if_rvalue` always returns a copy.

```C++
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
```

## Links

- [Example](../../../code/facilities/regularities/funyosteon/forward_if_rvalue/implementation.hpp)
- [Source code](../../../../conceptrodon/regularities/funyosteon/forward_if_rvalue.hpp)
- [Unit test](../../../../tests/unit/regularities/funyosteon/forward_if_rvalue.test.hpp)

<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalPop`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-pop">To Index</a></p>

## Description

`Typelivore::Pop` accepts a list of elements and pops the last one. The result is stored in `Capsule`.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n-1</sub>, E<sub>n</sub>
-> Capsule&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalPop
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPop
{
    using type = RESULT;
};
```

## Examples

We will pop the last element from `int, int*, int**, int**`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = TypicalPop<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPop` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**

  1. Preserve several elements from the beginning of the list.
  2. Invoke `TypicalPop` with the rest.
  3. Extend the front of the resulting list by the preserved elements.

Here is a simplified version of the implementation:

```C++
// We will use this function to
// concatenate the preserved and recursed parts.
template<typename>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...Beginnings>
    using Mold = Container<Beginnings..., Elements...>;
};

template<typename...>
struct Capsule;

template<typename...>
struct TypicalPop {};

template<typename First>
struct TypicalPop<First>
{
    using type = Capsule<>;
};

template<typename First, typename Second>
struct TypicalPop<First, Second>
{
    using type = Capsule<First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalPop<First, Second, Others...>
{
    using type
    = ExtendFront<typename TypicalPop<Others...>::type>
    ::template Mold<First, Second>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsSaQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOt2wqgIrgAYsRZF9DkCdjtbgB1TC3ADudFoty8SluBAQeE%2BVC8DAcOUJqBByNuaApTChzChhIQGLSxA%2BCQAbph0LdDAKucgNkoBWkBgoAHQgqEsNIGKEmQJuAgAT2ezDYKuwIImxC8DnBkJhcMEtxMAHYrFb7iqrFc5ZgFUrMCq1S7FUz3aqNVrWJhpcHdfSDApPh5BEwIglSITNYxA8Hpdh6GxBApdfqCIbjRDmehYbIPVGWrHiB60y7GAQZSHAnrGyDrY7LrcO4SvW6Pf6k2wUxZMMAIgwIsAs82rp28VkjLcALKeAUq%2B63MsxyKV1VDkcMMdGevS%2BPVjN1lPZwJt632q8t35gtxMNIKLz0BEHIHy73Kv2J7VBg2epXAaRoEOuz6vvQDr3qCALwd8tJggAkq6NbRo0H5nEhCG4UCzquj6vb/smQE5nm4EACqangoi0MoqBpJaNo3jBTpXN%2BPZ/gGbC3NCeDEBM2YgbmYG3NRaS0WIDFpB6/GCQQwnAix06dvi44Js8lqBGuT4vm%2BvpuJe152mxwIcd2RHcf2GLyRM8Z9gBtxCJgDLoEpoHGhJUn0YxckCfZzmuQI7lTspbYzup859tpumQQZ/kKcZLamXe7GXJxVlqiRvF2QQDk5RiLluQVPGAdKADyRIJJOwGXJ5VE0XRMmJYFxUhfGVXsoJF5ha2IKRXOwCae6qkdquJqFsWgjEWV4lNdJfmql1NW9dgIAgH2SkzhtmWskutChW4eXxu1DChU2Jm3teD64Yht0HCarCKhi91wXdn6weYgQRMg3hYNpbgMlsaR1kpOGPXpUGvYiBE/oZjmkbKYUNRB%2BnQWl5nvXszleGkxT8gASh8b7gW9UXDUIeME%2BgxNQeBE1QwlqoRPltys3s8Yc3syXpX8ON06TWFAhTtyC7QDM6fNknNUtbis1zgic%2BzSvK9zuq7YmZkQzjlEfGTsMiUytEAPpMBGCQEBAEzoBtCiBmbk5uOLbNU/jmREyTEu6ssDocKstCcP4vB%2BBwWikKgnBGZY1i3Ao6ybBi308KQBCaP7qwANYBJI0oaAAHGYZgAJzF1w/gF/nXBWla0iBxwki8CwEgaBopCh%2BHkccLwCggG3adh/7pBwLAMCICA6wEGkXj5RQEBoAqdAJFEgacKo%2BdJAAtEkki3MAyDILcUjSmYvD8oQJB4LbXAyIIIhiOwUi3/IShqOnpC6DfmLEM%2BnA8AHQcQ7vy7hVGe09wKoCoLcdeW8d57wPkfXOZhbgQA8IvegxBLRmECFwZYvAB5aFWBAJAC9JIYPIJQUhS9EjACkGYPgdAoSCUoLEd%2BsQIitHVH/Xg7DmDEHVBVWI2hXIDxTgvM8FUGC0C4YPUgWBYheGAE%2BWgtBe7cF4FgFghhgDiFkfgEUjg%2BRqPDpgVQrkZ7bBTqzeo79aB4FiD/fhHgsDv1zHgZu6jSB8mILED2jwtFGDsUYdOqwqAGAnAANXeJiCqWpuHP3vuIJ%2B/BBCKBUOoWRn99DaJQNYaw%2Bh7G90gKsRijQ1GbxtquUwMdLBmE7t44gV8PjwFWHYEROQXDnWmH4G%2BYRYyLFGDfYo2QBDdL0MMxoCwRiJBvm0ykAh%2BhTE8J0PQczGiLMGP06ZqzJjtGWQUWZuyplVEGa0hOWwJAAI4MHduwDODQI3tvXe%2B9D7H2QRAXAF9MHJzwanEJqx2RMCwIkCAWcQCSECNKYugRa4aEkGYSQSRW7%2BCSMXfQnBG6kGbjg6USQuBJHzsXKuSR/CSHLtC1IHdeBdx7n3P5g8iFj2IRPMBM8KHz1QOg5eq8OCtBYDyK0m8mBhm0UfYu0ouB5zPvgIgjTr4JLoo/aQKSX7pPfroeh39f7qKuTcqlEdOCgKnjPW4kCHmwN3n9UVXBxWSo0CgtBZCEhYMCGYX5BCh7MqoeQue3rRhWqMDargbcaASxqiwthHD%2BHxN4ZwwRwiHDxPEbWSR0j37yMUco1R8TNHaN0eHfR7SjHv1MeYqE8TrH13DnYhxnDnHbHDm4jxKdvG%2BKUP4vN44Ql8HCQoKJmAYlxM8SqxJSrn5pLfpkkA9CDDBOqVYSwBTYhFNBRHUGORymVJ0vO6wdTqUNKaSu1p9R2nOAgK4MZvTzrHKWEMzIIzcj7J6eke9kytknJmT0U9TRdmXq/fMn98x323tsL%2Bp9OygMVG2bgtYGwLkwfrnqu5HBzVPJFfOG1Eq84oM%2BbKl1uD8H/NIIC4FlArmYuxeKuFVp/DFxroEeFiKyW3NkTS2wdKPWMvgMyye4D2V%2BuICvNgnA%2BVwJYAoHkh8eSYbdBMaVXyr56BHYqiQyrZAToyeHXQwQtVpG4bqoBrHDWsogVA1QYmJNSZkz6CYDrOVOu%2BdgwI7ru1evs9Q/j7mMEgEk/jE20ni4m1kwQE25nlWMPDRAVhsjY3Rs8bFgRQiRFJs5RIqRMiC2YAUUosQ2bPG5sCQ2jRAki3NNkaW0U5bPGVtsfYxx6p62uMac23gra/Euk7cEhlPamCROibExg8TlMP1U%2BO1%2BmmdAgGCLO4weTF01qPWuspnAdg21yTUiwe6I4HqwIttZHTz1dPA1e9AN7BkvpKDkP9Eychnc/fthZYH8jPoe4Btod2INLOe59zZUGP2XNg4nAHiHDOd3uWF244nJO3AC9KYLOGZUkHwy5hlALMBAtGKu%2BuFHp3isCIEfwFcyWt3x1aAlLGwfd3Y/3Ij2dJD%2BChdXK0rd86SDLlwQuZhUj10CKD6lnBCOo/RRwU%2BFP%2BdU846sbxWRnCSCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_pop/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/pop.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_pop.test.hpp)

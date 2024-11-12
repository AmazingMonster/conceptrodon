<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SensiblePlume`

## Description

`Typelivore::SensiblePlume` accepts a list of elements.
Its first layer accepts an operation and returns a function.
When invoked by containers, the function places the elements into the containers via a process similar to pack expansion;
then, it collects every packed container and instantiates the operation with the collection.

Check out **Example** for more information.

<pre><code>   Element
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> Container
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Operation
-> ...Container<sub><i>i</i></sub>...
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>

## Type Signature

```Haskell
SensiblePlume ::   typename... 
                -> template<typename...> class...
                -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<typename...>
struct SensiblePlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::SensiblePlume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will instantiate `Operation` with the results.

```C++
template<typename Element>
using ZeroStar  = Element;

template<typename Element>
using OneStar = Element*;

template<typename Element>
using TwoStars = Element**;

template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = SensiblePlume<int>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<int*, float*, double*>;

using Result_1 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<OneStar>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<int, float*, double**>;

using Result_2 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::SensiblePlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

[*Check out this test to see how it works.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyaBbgQAnumMrJgAdPfY9GyCCifYJhoAgpPEXg4A1EJGNlYvRlAVMB9PiYUlYvv8Ef89gcjpDTsjDkxjujLtc2Pdbm9/sgDAoFP8APJXYhY3JvKGI/4/P4Ef7KYioIgAJVQTHQ/wZiJhcM%2BjMZGNRJzO%2B0x2LOuOY%2BPuRJJTDJBI8CjYjmQr0C73hYoRzIBABFMK06IKjcLrUbEV5skYkbiBYFTZTqbSBFLNdq8LqpY99owCHrsAT6YERfaBSlTScRXbxTLJejU1i0fKroq7sr9cTSeS/RaA/TDUaTazzZbaL6sv7TPrk0LYS2jY6IsAXVc3R6qQlvQx61rS023MHnmG3pHm9H23GE/OvguJZmpWu5RcczdZ9hC2qFBqG2PwwvO86eXy%2B/8a0wracSzqj/nsCAQNu0THW0ukxWkRmW6AVmn65nuB7qvcnzAMQmAhi85aig6Trdle/InB67KcqgaFStBsHwWGe6JlCMK/qRXybiBCo3P8k6hohVaAsCeCgioEJBk8DHNiubb/lRG7ARuNFKoSBaqmSnqDk0iGMkxWHcry6H/ra/4pii67phpW4iXmYn7hJL63E%2BAZnmpyFdv8aE3gONIyY%2BJ7PpxhEzq%2BJEqfG7nQvxQlabK1E7qJKpFgS%2BFwVOZlIQiF6oUpN4KThSl4TB4WhkZUZJp5y7eZ8AD0ABUhVFcVuVQgVhUACrYEIFVFaVXzlcVJUUdCZiBBEJJeFgbpuGgDDbOk048TlAk4oFmB0VxgiITF/wAFoJKgAzEAiGGTS52VQqN2Z4hN9HTcNs0UpEy03vtBD5V5W2%2BTtubrVOM0of8FUAO5LVM5JredhVXZRN2gbublfExtlDr9eW5c9mCTP8GgtbNQheOkJSYOgXLQ14tCsmtoP2W4EQEKQ/wE/lRMk5dc5/p8s3owomPY%2B6zEMCCYIcacBOIe%2BuGnLjdLDVzSWnAtHLLUTx2YKLz1vctZ6bcDrQ6gA%2BoeCQEBAkzoO%2BCg3MrepuLT9NE4jyNZKjBtY28Kzg7lkMVdDrJcPDT3GyjaMY1jitcDZXp4yTRNULQvIXUT6AbGxFPvHL1NPebBCezeQLM6xrM%2BFmBP%2B4HWIh2H9CcyA3NuLzPr8/nguFydUwZS18xKyr7TqwQmsgNrbC61KsdG0jrux5b1u2/b/xmE7lku6bbt0x7Zje9JfP44IGdB6T/yh144cR%2BDNPu3HU9rYnLPsanUrp/8AdB9nq%2B5yXBdF8OV9l8L71tGLFdP1Lj/ELLVM1wGutKPXGtax1mqduW9O4myUOPemvdowcDWLQTg/heB%2BG4LwVAnA3DWGsEyDYWwJrmECDwUgBBNCwLWAAawCJIW4GhJBcBSIEDQ/gNBmAAGwsLMEkJI%2BhOCSF4CwCQGgNCkGQVoUgaCOC8AUCAIRxCOBaDWHAWAMBEAgA2AQdIXhCYUAgGgA4dAEhRBuJwVQSQWEAFoWGSH%2BMAZAyB/hSFuGYXgqNCAkDwJrLgMhBAiDEOwKQXj5BKDUCQ0guhPEvRpOkTgPA4EIKQSE8RFJNEaNZKgKg/wTHmMsdY2x9iqFTwgB4PR9AVr4K4CsXgsj5GkAgEgXR6R9FkG0fUxpIBgBSDMHwOgewP6UFiCE2IEQ2jnGibwQZzBiDnApLEbQmAHCjNILoqcx1aAjLkbwLAsQvDADcGIWgUiUGkCwCwQwwBxDrKOXgWCDg8AADdoYhMwKoOZmidiEIJg0EJtBWI0kmR4LAISCDEDwPww59ziCxFNuaE5RhvlGBIWsAOTBgAKAAGp4EwC9AcyDCH8G8aIcQ/i8WBJUOoC5YT9CnJQJgyw%2BhWJSMgGsVAg1cgHLMRrDCphLDWDMKI1A4LgVYAZRANYdg5lNBcAwdwnguh6DCBEEY1QxieJKDkAQMw/AqqyGqhgixRiJE8WKm5AhlodBlYUQ1DRxX9CmEMBVSxlW2FtRqvQ8x2h6qVQa0VODtgSFiRwRBwiEmcAyaYixVibF2IcQU3ArjSltXKZUhFawECYD5GMEVpAKGSECLcAAnIEFIkgaFmEkCwwR/gWF5u4RwXhpB%2BEENuCwrgLCkh5qSC2/wtD/AFpYUGi54jJHSKIQimpyjamqOSZo8glAWklMMWwTgbQWC3JSGYpgB5nRcDzbcLg1DnH4CIIKvQxKfGEukMSxQpKQm6E6REpgUSUH%2BsDSI1BnAknqM0f8NJ/xl2rvXZu7s27d3UP%2BIU1AxSEgCjamYCpI71kKLqRBhpJSZ06OQ60v9a7VRGG3VwIRNAsYJCkRAfpFzxnDIWRRyZ0zZnzMOUs0MKy1miM2ds3ZtB9kLOOac85rGrnWvuQc0RTyXl7AWR8%2BBFzvmxF%2Becf5OxRFApBQs8FkKlDQt412UdSKUXosxdihZp6CV%2BIvbIK9wTyUgE6QYeFXKrC0pk8KplLKBBso5e6ezPK%2BUCvcQ8xlvRrXOAgK4F1nj5WVH1XoVVTQwsZG1U0D1yxLV9BNc681mrAvGuaLapLjq3VmoKJlgreWvXrE2L68pNaX3Bo4L%2B4gK610bpw0Bnde6NBgdjUe6DBC4NVNIaQVN6bEiZqk3WhtO6aEpB7SkehkhS2WM8a%2BsRnAh0yNHYolRaiUlobnQYoxHBl3ZJYAoW5djbnAdRJMA9cb3EntkGe0zASLNktEboYI97H0xOq/Egd76p2pPSUdqxJ2zv/Auzuq7rJwOQfjYEQIfWNtIdh7tjDJSQBneRorCHisofKwa5YrpRHemkYGUMyZVHydTJmeKhZjHBDMZCWxnZeyDmEJ47CxTGyBM3KE4855yBXkScEJ86TPzhkKcBcC0FhC1NQv2Fp%2BFCG%2BAGD0xirFOYjMPZMxIMzggXs3pAMEWzxgaU2Cc/AFzTQDm5QAV5ywvLUG%2BaFZbrLEqQtSrixFxVyX4ulFyHFmLuRSuuqtdl01cWjVNFNSHw16Wiuuty/aqLVWFA%2Br8c%2B37fKQ3A/%2BKD87l3MwwwgF1kgPXE3wfkSmtNWARv%2BvG9Znd8P/BMNoYI%2BHKRW39uzxI2ww7%2BsrHISASQ/h83%2BCSKwvNkg830MLVwY3nBAhZ7fb3gf/qnHd5X0mhDaxwXZGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/sensible_plume.hpp)
- [unit test](../../../../tests/unit/typelivore/sensible_plume.test.hpp)

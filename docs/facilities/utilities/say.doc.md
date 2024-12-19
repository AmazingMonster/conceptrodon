<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Say`

<p style='text-align: right;'><a href="../../index.md#identities">To Index</a></p>

## Description

`Say` accepts a `Sail` and returns the `Sail` via member `Sail`.

<pre><code>Sail -> Sail</code></pre>

## Type Signature

```Haskell
Say ::   template<template<template<auto...> class...> class...> class...
           -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<template<template<auto...> class...> class...> class>
struct Say
{
    template<template<template<auto...> class...> class...>
    alias Sail = RESULT;
};
```

## Examples

This function injectively maps a `Sail` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<auto...> class...> class...>
struct Op_0 {};

template<template<template<auto...> class...> class...>
struct Op_1 {};

constexpr auto fun(Say<Op_0>) { return false; }

constexpr auto fun(Say<Op_1>) { return true; }

static_assert(not fun(Say<Op_0>{}));

static_assert(fun(Say<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Say<Op_0>) -> std::false_type;

constexpr auto gun(Say<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Say<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Say<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<auto...> class...> class...> class Operation>
struct Say
{
    template<template<template<auto...> class...> class...Args>
    using Sail = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMQgAKykAA6oCoRODB7evv5BaRmOAmER0SxxCcl2mA5ZQgRMxAQ5Pn6Btpj2xQwNTQSlUbHxSbaNza15HQrjA%2BFDFSOJAJS2qF7EyOwcBJgsKQa7JgDMbrv7h5gnZ3sHTEen53cPZwCeKYysmAB0vyfYAGpkAYFApft9/kCQWC/sdAcCmKCAQB5D7Ee5Zf4mDQAQRmxC8DgBADFaCQ8KIGNicSYAlZcQDGQCnpdriz7ldHrdWY93p82ODIQjQYK4VDETDvjjiMAFFiGUyvBkjCSyQB3AEnAAiKLRGIE12lstF2BO9JpAS1Zup1IA9AAqR1O50u21250AgAq2CEnqEAOdbtxDpdoadQZpuPZL2jnJuFw5bL5zAFsPh0JN4pFaep%2BMJBF1AH0NJq6bSrcdzdTY2zuYmuQmY8mvpnhZKhRmc7i80TUYWuKWrJbrbj3U6SXhiDMvZhp4Gbbi0AwZphVCliACmF4iACqF4GBBSeTKdc%2Bxp/stBwDiJgCBsGLuxEozaWraPFwIV2uN1ud3uD0exAUoYp4pP2F5Xjed7EA%2BBAEpyFivgueKNI4yCFhK8QEBADCoAW/6HmSQEnqcZ5YmWlrLMsI6RihGLoZhzTUPuhHHiBpFgVw5FDlqVE0WOjoAkItQCOgM5zuGyHmMc4TAl4WCaqc250IQrzyrRS5fuum7bqgALACxgHAVSHHFhBAC0kIzOgIAgFQT6YIWBB8vxH7Lrs346TuBkAURxmgeBcKXpZYrWbZcFeI5zkfK5dFoRhoJYTheEAlgwLRZg0AsWFIBpbQABuYjXEZJFuGRcL/BAVHLLZhXeJg1GVshMz0QlShMXlGVZQeOV5XVxV%2BaVfZcRVcJVVRtViJFjUWBwqy0JwiS8H4HBaKQqCcG41jWACCjrJsmCamYxw8KQBCaHNqwANZJJI3waJIXABMcGiJBoZgAGwfWYAAcP36Jwki8CwEgaBopArWtG0cLwCggOD52rXNpBwLAMCICA6wECk27kJQaD7HQ8SRF8nCqD9H3mR9kj6cgyAAlI3xmLwmD4EQQE2VwMiCCIYjsFI3PyEoagXaQuhc2q6IpJwPDzYty2i9DyLbjjBaoFQALk5T1O0/TjNmACEAeIT9AbtJXDLLwiNaKsEBIATKRE2QFAQA7TsgMAUhmHwdC7FOlAxKLMThE0rwy7wwfMMQrzIjE2i1Ijp0E2wgjIgwtBh0jpBYDEXjAG4Yi0HD3C8FgLCGMA4hZ/gN51Pls6i6utTbtsp3hLsC1Z7QeAxOi0ceFgotwXgIMl6Q9fEDE6SYFqewV93RgXasVAGLKABqeCYGqqKMOHgu8%2BIAv8IIigqOoWfi/oFcoNtlj6D3cOQKsqApD0xfmdZ2qmJY1hmFDE8cwbk/To3QsguAYO4TwbQ9ChHmOUSoehCiZAEJMPwXMkE9EGPAkYXMah1AEH0CYUC8i4K6AneoswsHDASLg2YqC9AtWaFQxYNDVh7Q2FsCQcsOBLQhorTgmsKZUxpsAOmDM7oGwgLgQgJAjonUtmdJeqwECYCYFgBIVVSA3UkMcb4ABOY4ARJAPTMJID6YNEgfT0QDDgQNSAgxOt8D6XAPo/T0T9FxiRHqJAMR9PhWdoaw3hoopGtt0Z20xirXGLs3amxJmwTgTQWD5QCOZJg4oVRcD0d8Lg90WZs3JJzfeohD7SGPkLM%2BotdDe0lkwaWJduG8MhrwJWUS1YaySSktJGTgAM2ybkksRtUAm3iHIswCjrbIwibE%2BIeNXbDMdqbEAnTUkIiMFkrg4MaC0D9nDCAgcs6R1DnvI50dY7xwcHvZOjACBpwzqLHOecC60CLnvMu89thrRruQ%2Buxc1pN2QC3Pe7cuii27r3UOA9PlWyAqPU6E8p5KFnuXIwC9QChL4KvBQG8t47xWqdcpB9%2BZlNkKfEWF9/BX0Xt/Kwd9wWP00S/N%2BnAP4EHQF/W%2BFg/4tIAXgLADK2FkPwX4CArh6Fc1gWUahiD0jIOyMQtBqRZWYLgdK0hoCCF0IVQwoVPRCFzClSwhhWrciKsYQahYCCLZrA4fzRpCsAkCJWd0tZvSsk5PuobaR7M5EWytko0gKi1EjE0Z3OxDjskPQCD4gIz1JCmOplzZp61OBBIRkvFG4SkBY1VnMmZxB4nbCSTrFgCh8r03yu6y4Mx8kyI5noQlJTiWCzJefNauhjikFqfU2WNimn8I4MrbG24ATq03MQFgJay0VqrRyacQyRlm2OscCZGbpkLKdnmjdSzy0pDApWvRhZq0EAwhO6mPsdnxD2QctapzM6nTvechOVzhkp1uenTOXzMC53zoXYup13mouhdnScPyG5ZwBUCseILO5rXBX3V4UKh6wr3gi6eyL57hHRTbTFTB16b23h8fFvBG18wkCSk%2Bws206BAJ2gw1LOX3xiAK9ar8sjF1tGFGlv9/7xEASxvBPRwGQNNTAiBzCrVKqKFkcVUm5USZwSA8hmr%2BiycExQ/oCmaFjFU9q2hmnVVGutewg6XC%2B0Oqhk6s9NNS3loBAe74x6vUFKXfI/1oTlGqPUZQbh4b/DZOOMcRIb1Hpg0CwEVx/jLMw1sMEyZVEtEgEkIkfRiQfqfT0ZIPRz1DFcDo5wY4FmWmppCTbbhzMovFZi/F1YE8MjOEkEAA%3D%3D)

## Links

- [source code](../../../conceptrodon/say.hpp)

<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalReiterate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-reiterate">To Index</a></p>

## Description

`Varybivore::TypicalReiterate` accepts a list of variables and returns a function. When invoked by the times of repetitions, the function repeats the list the given number of times and stores the result inside `Shuttle`.

<pre><code>   Vs...
-> N
-> Shuttle&lt;Vs...<sub>1</sub>, Vs...<sub>2</sub>, ..., Vs...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
TypicalReiterate ::   auto...
                   -> auto...
                   -> typename
```

## Structure

```C++
template<auto...>
struct TypicalReiterate
{
    template<auto>
    alias Page
    {
        using type = RESULT;
    };

    template<auto>
    using Page_t = RESULT;
};
```

## Examples

We will repeat `0, 1` four times:

```C++
template<auto...>
struct Shuttle;

using SupposedResult = Shuttle<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

using Result = TypicalReiterate<0, 1>
::Page<4>
::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalReiterate` using recursion over the times of iterations.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};
```

Here is a simplified version of the implementation:

```C++
template<auto...>
struct Shuttle;

template<auto...Variables>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Shuttle<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Shuttle<Variables...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Page<Variables..., Variables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADs/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ6n2CYaAIK7%2B4eYJ2fIE%2BhYVHcPzyeBEwLDSBmBpzcTAuqAAdPD/k8JsQvA4jkIEBcCPRTlYngCAPQEo4AdXeAHc6LQjl4lEcCAg8AojlQvAwHDl6agjmh2UxgcxgfTydy0gMFLCAcDQeDMJCCNc0oxWJh4ZLAvckQQUWjsKoBegLExkABrE5JKxJAAiuIBUpBYP5crOAKObvpDtlkOhRDVdx5BgUzKEmAAjl5GFtSK73T64fCAGqtPBMWL0BR2jUA5GoghHPUGo2myEh8OR51uJPEFNpzAShFZrP4i0xt3Sx0Qs5xtWPYDETAgxgEDNNx7umlZIxHZRMYDvU5W9FhiPsitVmvptWkI69/uDwT19X3QJ457W234oGep3emFq9ep9OIx45tEAFUVeFEtAASphCAkN7Nqe47tl6XZ3g2mpju6r55soxCoEQM5zualo2iedpPESRxGnSUJKCArYejKN4QUQRwAJLPuO/bhng/bMhAlEfBhi4aMsxFwdOiHIbOFbUaO44mC2TzjuOtIRMA9KKvOgSLhiWI4i6jYge6IkYaexFgWRUIwlRNHunRXgMXWRzMaxC5HFwnFibB2q5jxSGoChAmGW6IlqeJE5STJSqseimIENia7Jo%2BdZ%2BqpxEaRegKPDhf7IBsWQAG7vAR7DadenZ6RRgnQbRy6mUxZgfG4VmUbZMFutxCHOa5kL5dFonVeJklTgq/lWQWrhFia8qycwbBOXxc6NUcAC0RxmHcIAgJ1zoFd5RxzTpQoNWcD61oe25bZuUGxcJ56YZerVrRW3bwruA5sAe7k%2BVOrkBXVo0Vtd%2B7DpFx5acdWnYQAVIDQPAwShJA2%2B2BCG%2BQOgwDwPw7DcUvOybxlRcdA3M%2B9qkTll1HtmDloopwXKX9jztdJQheGkxSYOgf4KF4tB5lZxMhZCxEaNuXDRnZbpc9ZvOtQLPOc9zmbfVh5OTtJDNMyz8lHB%2BaRfmIf4AcQuki8%2Bc0bW4kg6/NsmxQT/JfgA%2BkwQYJAQEDfHNCgqpbI5uHLzPblTNOZHTbsEHcnEnhwqy0Jw/i8H4HBaKQqCcOVljWEcCjrJs85mIEPCkAQmhB6sJoBGYsJJGYkgABwl/4GgAJz%2BGYGgAGwl8EIccJIvAsBIGhcxHUcxxwvAKCAXNZ5HQekHAsAwIgIDrAQaQXOQlBoKCdAJFEKqcKoJd1xNdeSEcwDIMg1mSLCZi8HThAkHg6B6PwggiGI7BSDIgiKCo6gj6Qug8%2BSmtpJwPBg6h3DtnaOnAADyFw555lQFQI4m9t6733ofY%2Bp9zIeGXvQYgJw042V4MPLQqwIBICXirLBC8ICkJXokYAUgzB8DoMCYgA8ICxFAbECIrRrgAN4Bw5gxBrjgNiNoTADgeGkCXrdAg4CGC0G4Z/LAsQvDAChLQWgA9uC8CwCwQwwBxAKNMhyNKGio6YFUKIi42wM4RGBM3KOVxYiawER4LAoDtR4Hbpo0gaViCxG9laEEuirhGGzqsKgBhgAKATHgTA5JwFKgjhnO%2BwhvxP2kMkt%2BahQHf30LolA1hrD6DwLEAekBVioDSI0DRE1vgLlMPHSwtdeCoB8dWLApSICrDsKIxoLgGDuE8J0PQYQIjDCqKMHmxRsgCGmH4SZmRpkMAWCMRIPNukcgEP0KYgyChrPqD0vokxBijMWBM2wRzZl6DmG0ZZ4zVldOTlsCQQCOBh1IN3ZpnB4Fbx3nvA%2BR8pBoIgLgS%2B2Ddh4MzqE1YCBMBMCwIkTppA86SECLCSugQkiSA0JIYuddO7%2BDrpXfQnBW6kHbunWEdcuAN0riXal/hJBcH8Oiuu7zQG937oPSFI8iGT2IdPKB88KCUNQJg1e68OCtBYClJIE0mABl0dZSusIuCwlMfgIgbTb6yAfuIZ%2BGSlBZM/roehv8mD/00S8t5HywEcEgbPC4RxYFHClTKuVCqpxcGVaqjQ6DRVkISDgwIZhlj4NCWPEh/rqEUKoVgkArrZUHF0V6rgXMaDMwSCwthn8%2BFcPEbmgRQiRFiK8ZIocMi5GgMUco1R6jxHaKCdsKO%2BB%2BxGLrKAsxFjgTiJsfUUBDinHXBcU2/B1ZPEZx8X4pQASdFGGCaAHlfAIlRJiXEhJ4jkm6rSS/eQhqP5RxNbkkJ9SrCWCKSU%2BA5TKk5GqbU%2BSJ7rBNOjq06%2B7ayk9AOc4CArhLk8xGRUFZegpmNF/ekBZjRblLD2b0TZFydlzI/RspoRzINnOue0eDVyUMnMAzZNYGwnl4ebta9lXyE3uqTZ671arzIgs1UGiFBCc6kBhXC0YiLm6kvJcq7FKRK5JCSIEHFkhd48xtRy2wXKmO8vgPyme0CY1RqwWvNgnApVIJYAoFKR8UpethLKCY58NVXxvjzTdqSJDpNkJk/dOgQDBDNRawBxLXkgM/r3e10CnVwPU3vTT2mji6eVQZvMEAMEBrBWnQIobuWEIjSgJTCRFNisSNpmm5sgvmxC5bYgLBd4MIzcwyg2ao4FvkRnMrRaeniLLYICt8jm2YCUSosQdavENrnSO0gLaDnGI7eYpK3avG9rsbwAdXDh1uLHeIyd/jAlzqkuG8Js4V2xPiYwDdOqLP6us3u7J9mj3GAKWehxHSr1VM4ASe2D7Gk9xfe0y9iHenfv6aB/9YyoNgZKDkUDwGciodWU9w5AxQPrMaFs45AG7lYZB5htZ2GodQYeQRp%2BVq3M9zI7ljTWmdN6ZC7R4zkX04xek9C2F8LKAvK4yAMwyrAiBH8BXRlnd6dJAbmy9znBOVDyhUikAkgkinxSFwKQldePoq4EkFzgR0efL7rF5jzcz4c4x/L0n3jM05H50AA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/reiterate.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/typical_reiterate.test.hpp)

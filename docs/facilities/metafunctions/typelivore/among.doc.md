<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-among">To Index</a></p>

## Description

`Typelivore::Among` accepts a list of elements and returns a function.
When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
Among
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Among
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = Among<int, int*, int**, int***>::Page<3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Among<*>::Page` is implemented as a shortcut to `TypicalAmong<*>::Page<*>::type`:

```C++
template<typename...Elements>
struct Among
{
    template<auto...Agreements>
    using Page = TypicalAmong<Elements...>
    ::template Page<Agreements...>
    ::type;
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAA7NIADqgKhE4MHt6%2BekkpjgJBIeEsUTHxtpj2eQxCBEzEBBk%2BflzllWk1dQQFYZHRcdIKtfWNWS2Dnd1FJf0AlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKYCa6MyHiYCmfbB8enex87r0eHP2YAzMFkN4sGcTP83MhBugsFRwdhfr93uszgAVACeCTwoloRxYAmAzy23wImBYCQMpPBbgImMYrEwADpmdh6GxBAp4b9BsQvA40ZjsWI8QSwbErLELuCrMdfqTyZTMNTaTdmGwzgAxPDEQZc448vkEAVYnEiozUrU6gh6n7i35nB1neUUphUiEpABemAA%2BkaAJI2x1nA385TEVBEZRMYCYMUSqX/GU/Y5B52K6men3%2BwOO4iYACOXm1jzOEAD/wTFw0M3tjpDRrDEdQUZj1PLCJTjpM4rOXhSRiddLBFc12t1ibFCaTtYdaddSohTC8RGZjKOwDzZMYBE5/w7RyDfeChJbsfBFzOjcj0YXbnXm/ZO9X8JAIBVC%2BnkuliOOc7dNLpNVY0tQZSEHVUGTOIRMDQBh0DA98gNXAB5AgEGiXd93rY0hVxfFzQhECCDA6DYPgs5UPQnVnz3RE7U7WcyRdf9M19M52xnYMCF5UNw2vGMwQYuNe37Ql32HC8MRNYV8OAalKIwmjsFfP9YyvZsbzbM4AFozjMF83zpaVJ2/WUhNUjM8C9NiOKEvNC2LJ4y3Pc9q047D1NPNscwdbsLBE49wLPEciOM7spx/A9HQs90rKzdifLOeyizzJzy0rLgayEjy%2BI01sIVsqLfJ7I8B3E88oJggR0DCr9E0i1MmPTRdl1QVd70wLcOUS0qTxvCTL1yryIQ6rqn2ZLl6tlOrpzeT55q%2BJFtnYhUxtdNIiU2b5kQWz5vjlJr52VQCGVXVkxsw7luMNM4zTk6ak0ahUjpaldmVGx9LqE3rL36iqpNwu7qXOz6lM4lTDtJX78rvDdOtBibaKElSjKm20IrMk5dsWubzmwVRWApWMXiW7HiUi8xAQYYEvFBalYOWBIdxtUnNigrwEhyTB0AAJUeLxaCNEnjh%2BoQOa53n%2BcFgbggILZTOTLHzj5hQBaF8mRdEs4VbVgagYhWWwNl9YjcETZTblzYDOGtx/km2albZ1FHnVrarvW5BvSYBQlHqCBoVfBQGS93c3B1wWSPF5JufD609xrNGODmWhOAAVl4PwOC0UhUE4NxrGsYMFiWM8AR4UgCE0JO5gAaxAVPJEZDQAA4zDMABOduuFTlvm64WIyhTjhJF4FgJA0DRSEz7Pc44XgFBASfK6zpPSDgWAYEQEAFgIBJl3ISg0HJOholCBlOFUZuADZtKvyQzmAZBkDOKRGTMXhucIEg8HQPR%2BEEEQYh2BSBkIIRQKh1Ar1ILoFoAB3YgTAEicB4MnNOGcq4504MhZce8jSoCoGcS%2BN874Pyfi/RuZhSweGPvQYgYIy4zF4MvLQcwIBICPliWhB8IAcJPjEYAUgzB8DoKSHUlAIgYIiMEOo6JkG8CkcwYg6JkIRG0DBZe5cj6PmQgwWgsioFYAiF4YAbgxC0AXtwXgWAWCGGAOIAxxYHB4AAG6PAwZgVQMFlwrHLrLCoGDaB4AiAgpRHgsAYO4ngMeljSCuOIBEaOVwbFGECUYKucwqAGGAAoAAag8WByFVRyNAcIHEwDpD/3kEoNQGCYH6FsSgAulh9BBIXpAOYqAmZpAsdpaE55TCWGsGYGecTiA/zce01o6i0guDgiMZopBAjBB6MUPoLQcipAEPM7IyRNkMEmL0GIYwKjTIEB0YYngmh6DsKc6oQwujLKmGs2w9ztljHuQc1ZRy5gKGLssCQqCODpynhg2ehDr633vo/Z%2Br9KEQFwF/OhlNMpMPSXMdCTAsAxAgLXEAkh/iMnbv8eIGhJBmEkFfCeqcr7t30JwEepAx7/C4IyK%2BXAr7N3bn3K%2BDdu5EqviCqBs956Lwruktem82HbxwfvCgPDUA0NPufDgdQWDONiNpJgZxgS2Jfu3RkLLs6fyIGM3%2BLRKmAPECAyp4CalQN0EI%2BBiC5GAuBdPXgs9sG72XGcfB4LiH3x1QOLg%2BrDVUIVZw6I9D/hmEYWKlerD2ERr4dw3htCUAGCMCGrgk8aCCwwuIyR0ilHFIUTIlRaiHDFK0duHReiMGGOMaY2g5jinWNsfY7O%2BA8xONcRYo1njkDeOKX4oe2dAnBJkWElY2dInRPLnEhJSgkkduPOKzJ0Zcn5MKYwYpFqykSAqbIW1kDs4OvqWkgZVhmkTraTinOXSBA9L6RWK9QyRnRFNRM%2B9NynHOAgK4N5iy4KfOmOs3ZVQgMbKqKB55v6qjnIaJc0YUy/13ImI8w51zXnIYWeMeosHvnzEWP8zKdKgXoKFZwf1kLtWZsJCGg1TdSwIpNdGlF8aWHoswJivo96h4MqZfq0lsRU7twHv8MlFLJAtHdZguethRXMNXuvLeO9cGpuTbQs%2BbBOCqpISwBQzjn7OMY4qQYH98Amp/n/WQlryklJPbUkA/xSBOqQZY11lGZ5YJlXgghqgDNGZM2Z%2Bcgxw2KqRQCf4cblOJpQFp6ImnIsgGM5zb0pn27enMwQb0gWKkiILRACRUCy0lpiWV5Rqj1HVoVdo3R%2Biu2YCMSYsxFjy7tpSTOqxjjHB9vcYO4dMTR0BKCSE9E06IljPnbwRdiSySrrSQmvgWSt2YAKUUmJ%2B6gGHsc9U09OgXMXuME0mwt74AdMfQwCxqwA5vssMMj1ozxl3p%2BSctDsz3C4f8CBzDXydm5DSFBiDaRCPXPewhnDmQ8MQ/aB8v7YGXmdCA/hh5hQsNkd%2BSR4BXnBU%2BY4IQoLxmziZcZDlljVmSDsdi2i0gGKsWUEBYJkAHdGT/H%2BKnHuMmJ7s9iByvHHrOAiqXrTuukhU6Ev7rECezdJBdy4K3MwAqh7/G84LhTcXAXvwF/J1FCa5hxJSM4SQQA)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/among.test.hpp)

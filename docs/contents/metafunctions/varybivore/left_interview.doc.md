<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::LeftInterview`

## Description

`Varybivore::LeftInterview` accepts a list of variables.
Its first layer accepts another list of variables and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first variable that satisfies all newly formed predicates, or `-1` if it cannot find the variable.

<pre><code>   Arguments...
-> LeftSides...
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
LeftInterview ::   auto...
                -> auto...
                -> template<auto...> class...
                -> auto
```

## Structure

```C++
template<auto...>
struct LeftInterview
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;

        template<template<auto...> class...>
        static constexpr std::make_signed_t<size_t>
        Rail_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = LeftInterview<0, 1, 2, 2>
::Page<Args...>;

static_assert
(Metafunction<2>::Rail<Equal>::value == 2);
static_assert
(Metafunction<-1>::Rail<Equal>::value == -1);
```

## Implementation

We will implement `LeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct LeftInterview
{
    template<auto...>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        { static constexpr auto value {-1}; };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First>
struct LeftInterview<First>
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};

template<auto First, auto Second, auto...Others>
struct LeftInterview<First, Second, Others...>
{
    template<auto...LeftSides>
    struct ProtoPage
    {
        template<template<auto...> class...Predicates>
        struct ProtoRail
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<LeftSides..., Second>::value))
                    { return 1; }

                    else if constexpr
                    (
                        LeftInterview<Others...>
                        ::template Page<LeftSides...>
                        ::template Rail<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + LeftInterview<Others...>
                        ::template Page<LeftSides...>
                        ::template Rail<Predicates...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Args>
    using Page = ProtoPage<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQSZhqkAA6oCoRODB7evnppGY4CYRHRLHEJXBpBdpgOWUIETMQEOT5%2BgbaY9kUMjc0EJVGx8YnJCk0tbXlctpOD4cPlo1UBAJS2qF7EyOwc5gDM4cjeWADUJgduBACeKZgA%2BgTETIQKl9gmGgCCh8enmAuV2QE3QWCoHy%2Bvx%2BBEwLBSBlhlzcTC8RAAdJjIT8JsQvA4ziFMFQCABJQTxABueEwAHcoSYAOxWH5nNlnWHwxGYZGojFYg6fVns3H4ghnZTEVBEZRMYA84Vspks77stUcuEIphIq6crU6lFo1CY9EfM4nJgKBQmyWYfCiWHvQVQ9Ui55iiVSogAJVetBdrouzLOE21eGQ5oEE0wqhSxDOfNQZ0pYi8gOVAFouEyACKXCxBvMHFUB1167nI8vanlXRMms0Wq0m77AYiYOGMAhOoWqwNeDJGM6%2BuhAnOe6WoYf%2Bq4ttsdwTWgWfYulwv5hmKjVc6u8o3N4jAbur/vhYASuXpg5jyUT2Xy5HfA%2BL03Olc/XPr98wzUV2tGs4AGJ4MQEzYt8ooEkSJLkrCxDUnSyJASBBBgcqq5VgadaYlBwh4FgR6bhB4o3jKF6rmhm5qhhNbXD%2BO5/vyL7YOaBhNpitr2tWBG9q6RHjj6fqrmqyrskJgaho4EZoAw0axvGibJqm6aUYGFE8YGromAArFYWk5hAaxnBmZqgiAIAsEwADWjwZMAEToE8yIZAAXo8KHOipGlKsyYleeqeBUJGMmwnJFyeX57JQPWZgBOYAQceGXHIjhQh4Zgz6kIBwGgYKZkpt4mBrGsvkRd5BZtgQ2wMGcGj5muX7qaVardEoJWlSJFVVUZ2bFvVjURbmBltaJjJFiqGkfm%2B0L9Wy1GVnRmF7kuLGWs%2Bs7tmwC5gRpJ6DlOo78ZOgkzq2G2ds%2BkJTcJo2ftNVELTRWHoo%2Bh7beyu1nnel7Xl6qBfQ%2BT71q%2BJY3VNUJzQxSZIRMmUKUIdQCOgsNLeiADyBAIPE3F8ThMFUjS9JXNDBCZfD0lI2c6OYyBQM9mp93botjEpWl3FqnxJF/WRm704GEO0Yzj0ow2rHPglDrpW9vHugSnNTiVIlKuF7NNJJQWyXGCb/vlaZhTN6q801Fw6dp%2BmGcZgohgQ6BmRZ1kPLZ9mOVcLluVLTWG0b7IBerIWa8NflRViMVxeLSVXCz%2BEmplxMfHlSlFQHXkdZglXENVtW9R%2BDVe%2BqLWAj70ka/GScaUHpohzFYeOslxK4VHmKkwjDDoHHIA64VxXKwNwadenZw9QW2d3bn7L52chdRn7xCl4GECz35uMUnBBPIlTWO0wvXlmdR573hHdepQ3TFbxpO8PUOx1uNX6Wb93RvxwVZxgGAlxjlmp/sl3%2BvtcGn%2Bun3aqZgLiWEJHXPGK8EJXHXjTJc/91Tn0FnvGikdb5wPvk1RB%2BpATyyuDfC6Hkf5e0fmmOq8Dh7wPzuQ3uqcuofyzjdDB10zZJ0muNVSoMSzhX5vzJ6ItVrNlOvOLs7s1QfUviON%2Bh1cFuHWsIghy52HeTGhudSvCUYvTZu9Acn0LwHU5v9GcgM4Fg04aogA9AAKmsTY2x5ioRWOsQAFWwEIJxNj7E/EcbYuxqj1FEDOKSZGASABSYE%2BLYAAI5eDEAyHyhFVbhl9jGTWMRUCeEUgVcizJSSjikWEsx75CnTX8caTEmiwLiIALKpyYFQLwDB6gCAOkvWC8FCZuGSAPTKZgelgTMoY2RxiT5gxxIk5ADxVrxBQj8CANSmj1Mab0ZEZg24yKiTE6c2ASHfSkWYYqU0JLhkmVaaZUI5m1MWU0hgyJ6HbJAOs6JsTcrtyUnkq83UDkWA4BsWgnAtK8D8BwLQpBUCcDcNYawIYtg7HTGYA4PBSAEE0D8jYlkQBaUkOiDQkguCMgOBoLSGgYoBDMAADjJfoTgkheAsAkBoZIQKQVgo4LwBQIBkjIuBT80gcBYAwEQCALYBAUhonIJQNA8I6DxEiKwPYqgyUBAzAESQZxgDIAjFIdEZheB2kICQPCeh%2BCCBEGIdgUgZCCEUCodQ3LSC6FmLSF4KROA8F%2Bf8wFKLQWcFRmiUV4pUCBQVUqlVaqNUDyxcAiAHgpX0BLvCrgaxeBcq0BsCASBJUpGlWQCgEBM3ZpAMAKQvSaC0FguyiAMQvUxHCM0G4rreA1uYMQG4qMYjaDqFyxFkrNoEFRgwWg9a7VYBiF4YAKJaC0HZdwXgWALJGHEMO4Cna8CUnSl6mMdQ0R7EReEWEfy7W0DwDEF4LaPBYC9c8PAdKZ2kDXcQNJSgcxwkMMAI9RgUUbCoAYQ8AA1AmqN7hAsRca4QohxAWtA9atQXqHX6FfSgSFlh9DHvZZADYqAUi9GnRmUEb9TCWGsEkXgqB73EFZvADYtRrkuBbtMPwsxQiLDKBUfI6RMgCHo2xwoWQhgsZWF0HoDR5hcdmNR3o/QWh8ZGJUOYAxRNyak8xmTEgqMwt2KpqlHAAWkCZSRzgZxg3KtVeqzVkazgQFwPq%2BNCKk1Is/RsTGTAsAJAMqQdFkgDjogAJwHEZJIHFZhAgMq0gEbzWmaWkDpQi9EAQuABDJd5sl8XMVcC0r5oIenvWstsBy%2Bz3K00CvTUKv1Yrc35rjbKtgnBmgsEpIyDMTAVqDi4N59EXBsW6vwEQcjNtZigdNRB6QUGlAwbtboXpTqmAupne67Tnq7Ust9SKtEZxA0JmIHVhrTWLQtbax1jQFmY1ZrjSAg4%2Bzk2ft5Rm1Asb4jirzbdk7oxav1YzLtot3mqh8DoOWygVa7VNrrQ20gQOW1to7Q4EHPbOz9sHV6kdY6J1TpB3O19i6QX4DbPUNd06QWbuQNukHe7uheqPSeut569ggqvTexF97H2YGffOt9p4rvfrlAof9dJAOMBBwN8D5rhuyGg7akFE34MfoI1YZD5O0Nucw9hzguHrb4aQxYYjoKyMUfQ4JldzgICuAU0x0oKnZgFA49kTw7RuOW%2Bk8sWT4nhPyetzMPX1zJMLFNw7vQoYpiu4Y4pr3SxWOJs2NsDTYeD06ayyyjbW3GvNbPK19r2KLNWZ62dxNl2CuOcwM50YbmD2Rei21nFjJ0uMnxZIILKrZix84GyvLKaeV8sFcK/1D2KsyrlTVzboaWAKEpBGSkKfuQTC69Zw1/XZCDaF5a%2BQo2xc6BAAcUgU2Ztuq0zHr1S3SsBsCrVgfQ%2BR9j64uKaNT3s1nYOHZlvaabt3ZzRKq/cb27IBSCkB4o/vMPHHwQSZfvYbX7LGf7atWtFtEHMHVtdtTtaHW7XtOHIdTHTAUdcdMQFHW9NHBdanWdZdHHddO1AnInW9EnA9EFcnU9G4KnS9cjOnXgBndIJnF9BdNnArPgH9LnADIDfnWfQXCQYXK1JfWDVfSXYwdXFDGIeXDDLDLIadcxUyaXIjZlbXfCSjd3XoWjdwAPPQE3EPATC3XoBTQw3jZTH3MTbofXPoETHQiwoTAQT3e3UPIPBTP3YPfjSoNTCPc1ObHfRbAzI/VVQfYfZMM/R0C/DPEgLPO/BzUgJzFzSgObEvEAMwNrA4A4LSIlXFBldIxkBLXTXfRvXLTlWIjzLSHzLSMlGKbzSQbzfFPzLgNfA9A4BbZlIo%2B/ObHVAo/wnLDou9LGLIfwIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/left_interview.test.hpp)

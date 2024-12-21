<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicRecur`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-recur">To Index</a></p>

## Description

`Mouldivore::ClassicRecur` accepts an operation.
Its first layer accepts a list of predicates and returns a function.
When invoked, the function instantiates the operation with its arguments and uses the type result to call the operation repeatedly until the type result satisfies all the predicates.

<pre><code>   Oper
-> Preds...
-> Args...
-> (...&&Preds&lt;Oper&lt;Args...&gt;::type&gt;::value) ? Oper&lt;Args...&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt;::value) ? Oper&lt;Oper&lt;Args...&gt;::type&gt; : (
   (...&&Preds&lt;Oper&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt;::type&gt;::value) ? Oper&lt;Oper&lt;Oper&lt;Args...&gt;::type&gt;::type&gt; : (
            &vellip;
   )))</code></pre>

## Type Signature

```Haskell
ClassicRecur ::   template<typename...> class...
               -> template<typename...> class...
               -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicRecur
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will increment `0` and `-1` until they are greater than `9`.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename Vay>
struct AddOne
{
    using type = Vay<Vay::value + 1>;
};

template<typename Vay>
struct IsGreaterThanNine
{
    static constexpr auto value
    {Vay::value > 9};
};

template<typename...Args>
using Metafunction = ClassicRecur<AddOne>
::Road<IsGreaterThanNine>
::Mold<Args...>;

using SupposedResult = Vay<10>;

using Result_0 = Metafunction<Vay<0>>::type;
using Result_1 = Metafunction<Vay<-1>>::type;

static_assert(std::same_as<Result_0, SupposedResult>);
static_assert(std::same_as<Result_1, SupposedResult>);
```

## Implementation

We will implement `ClassicRecur` using a helper regular function, which utilizes `constexpr if` statements to decide whether the recursion should continue.

```C++
// `Sacrifices` are the arguments that will initiate `Operation`.
template<typename...Sacrifices>
static consteval auto idyl()
{
    if constexpr 
    (
        // `LessonsLearned...` are the predicates.
        (...&&LessonsLearned<
            // `History` is the operation that will recur.
            typename History<
                Sacrifices...
            >::type
        >::value)
    )
    {
        return std::type_identity<History<
                Sacrifices...
        >>{};
    }
    
    else if constexpr 
    (
        (...&&LessonsLearned<
            typename History<
            typename History<
                Sacrifices...
            >::type
            >::type
        >::value)
    )
    {
        return std::type_identity<History<
            typename History<
                Sacrifices...
            >::type
        >>{};
    }

    else
    {
        return idyl<
            typename History<
            typename History<
                Sacrifices...
            >::type
            >::type
        >();
    }
}
```

Note that we wrap around each result inside a `std::type_identity`.
This is to avoid creating an object of an instantiation of the operation, as it might be impossible.

We return the final operation itself instead of its type result.
This is because the type result that we are testing might be an indicator to signal the end of the recursion, and the actual output could be a different member of the final operation.

Here is the entire implementation.

```C++
template<template<typename...> class History>
struct ClassicRecur
{
    template<template<typename...> class...LessonsLearned>
    struct ProtoRoad
    {
        // `Sacrifices` are the arguments that will initiate `Operation`.
        template<typename...Sacrifices>
        static consteval auto idyl()
        {
            if constexpr 
            (
                // `LessonsLearned...` are the predicates.
                (...&&LessonsLearned<
                    // `History` is the operation that will recur.
                    typename History<
                        Sacrifices...
                    >::type
                >::value)
            )
            {
                return std::type_identity<History<
                        Sacrifices...
                >>{};
            }
            
            else if constexpr 
            (
                (...&&LessonsLearned<
                    typename History<
                    typename History<
                        Sacrifices...
                    >::type
                    >::type
                >::value)
            )
            {
                return std::type_identity<History<
                    typename History<
                        Sacrifices...
                    >::type
                >>{};
            }

            else
            {
                return idyl<
                    typename History<
                    typename History<
                        Sacrifices...
                    >::type
                    >::type
                >();
            }
        }

        template<typename...Sacrifices>
        using Mold = decltype(idyl<Sacrifices...>())::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAnGakAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwc5gDMwcjeWADUJutuXo60hACeB9gmGgCC1zcEmCyJBo8Hbo/Pr5jvBGeJjFYmAAdKDLrttkwFApdgAJPBDEgXdZXW5DYheBy7NwGaF4ZAAJUwyCW9xMAHYrLddjTdp8Xkw3od6d9fv9AWxQcDwZDoVyAphoQIFAL6iF0Jd7rTdujMQRdspiKgiATUEwJdTaRSqTdpdKAPT6/YANg0QiYyGIeBoKwUJlNu3qmDpCGd9WAPkYBBhBAQjN2AHc6LRdsE0oznfaNAB5AHERnpKPczV6ulPBlMj7s5ic0Hmy3W/GCyUpvUTRzICHCx4ANzEjuOqFD6DOtAgsylqf2lM7Xdp1qrDCGmFUiWI%2B1LfYgvb7esNJo0AqFQ9FxHFXKjjuIzt9zrHmHwokeCmTutnqYgG7MxvMxqXCmFq/F7xn59T86j8MRxAuDoRLudVA4wTAQXX9INaBDbcSWIU831nP4ARzZ0vyIH8X0neCu3zK0bUFDdMKw/YURAEBEJ%2BQjZ0uUi628TAO0o6UGLPc9tVfN9twIJYGBlAh0FI8iAH08CwQRzneVCkQwliiOwi1cKLE8wUYrtJRRNjyQAEQOHV4IpbSVJpdjU0qJRQyoQdh1HcdjL1adDLsq8b2ve9H0wMUD2k2S9XI5C4QRNDkTcWz4N8oF/O/IKQtknDC1tAiZO86iyPZaLWJIlKATSvVktorx6Oy5i9J7BzpU47jeP4zLMGE0THD%2BCSAqkw5sr7MK2AiwKvO8uSCzwpS4J6oyMvI1qtXU9Sey0nTsv0skHNMijEtUkrlvPcq12bVtuqG9qUKa9CWtKrs9s65rguO89Yv6hKhuG7ABNSy6cpGp61qolF2xmhy5so367kolkIzZJCgS5a7FJLd6vFSIxdgAWU8dBiM03YsG2ciIBE7bDgh%2BKwU%2B2ZZkerL1l0rVprJ%2BaZKBzNaZ%2BZlszBgnsAhXEBpuYBtyeL07XU0sYeCYBdlVdUUYVJUVTVCVDk57m2EEAa1J1Oaqdue59QAKm1nXdb1/UNd13YABVBW9XZdYN24tb122datgG7jMTYGG2Lw9neY46HE/nHZt7WEYEZUBDOC37fuen3iYRtdgASSh2UsURhhg4YC51cpXiE0rNAh0eayGyIXY8sjSl48pixu20tW/aNm50HQaMQjD7WHcjxnQY6gA1MQE4IDEsXrxuQjJVbpUFuHyPF5PU6CnvaBosR8v2Sxdi4ZXR%2BrlXraN2OFAAcW3CNiGNv0GFCYJnUtiP01ZDuOWdee%2B4H%2BU98P9zHhPs%2BL5HjPyZpcs%2BJLL5zHIXJsJcZzannovOixFWaxFVirCu1N25Zk7iCUENxiDAD5qiG4E9hbw0wHUKgXhXbVHFjiKEqRCTElJLLBuTcGZ4NIqLGWbg35H0/qfQwP9mH3FIojWg7CsE4I3BNbe%2BDYbCyEF4RIuQDxEgUF4Wg8oDioxnkQNO7wuAaA3urW4BCRaChUQQQSGhp7EKYKQ8hiZDiaJDu8PRE0HrVW%2BlIoWxjlGqMElwSxJCyEODsW4Bx2jDgAFp14uJJgzSRgDkCCWodEAgEAhhVQUECRJfM3BKNMeY0guxZHyJSIokxqjLgdhrvErJSgGipL4qRDJbAsnvFyT41ohS5EKPQG0ggFSdIcHmAvDgABWXgfgOBaFIKgTgwVLDWBlIsZYkZnY8FIAQTQgz5gAGsQAjLMMCckZhJAAA4TkjI0LEfZGhjQnPWPoTgkheAsAkBoDQpAJlTJmRwXgCgQDvI2ZMwZpA4CwBgIgEAiwCCJGOOQSgaBnh0GiKEIEnBVAnONOE40khdjAGQJWKQwIzC8APIQEgIk9D8EECIMQ7ApAyEEIoFQ6ggWkF0K0AM8ZEicB4EMzgYyPmbOmZwaMxwYXylQBZdFmLsW4vxWvSQRLdgQA8Ii%2BgNlVmzF4ICrQ8wIBIARYkJFZAKAQENcakAwApAJBoKo6IfyIARCFREYI9Qzg8t4C65gP5owRG0MSQFayEUKwIE3Wg7rWVYAiF4YAbgxC0D%2BdwXgWAWCGGAOISNeBoKOBrIKIVI46GPA9eQQQlQhWnAiPGH8HgsBCv7ngF5SbSC5uIBEEpmknhptOEYTZ8wqAGBwV3PAmAAyxkYMWqlwhRDiHpZOplaghXsv0GmlA1hrD6DwBEP5kB5hAWqIm8JaT1GmHmZYMwXyW1WiwNu9sbQA3pBcAwdwnhmj%2BCfVMPoMRWi5DSAIUYLQkgpF/QwD9JR%2BjjEqPegQnQRgvrGHeoJ0HhjdEvtMcDthkP/r0BMBooGZhcHmA%2BJYKwJB8tGeMoV3zdjSqxTivFBLFVmGVbgMlGr1gEe1b2%2BYrp1T9FvbsyQ6xgSxHWOSSQGhJDHNNBoEZxpYgPI4E80gLz2PAmNFwW5sQTkaZGZILgIyRPGkFay75vz/nrN7SC8F%2BrIVithaa816qUVsE4PUFgNZyThKYGzNNa9YjAi4MCKZpK0IUtaJOmlM7pBzqUAu1lugEicqYNypNZGBWfN4N80V0Lji7ElVudznnvOQjhlwfzgWLEqtQGq6IK91hmC1RZoFeqDXVaNequFZq2sWrcx58JJWrWxF0XwOgn8HVOtZV6t1xaps%2Br9QG4twavRhojVMqNMa42QUTWslNXbVhrazfe3NibguqELasNZwRHjDKmRWqtZwa37e1VaRtayW1tqUB21NRhu2gGa3wAdCgh0jrHRMtZEXp10ui7IedLKpkJeXT2k9VhLAbq3fAXdiR92cEPXxY9a6z0XuiFevNO6EPVEfc%2BrIAHAioc/TkID1QsPfsZ%2BkPD6G7BQZqJhuDAHOeIe55MOnYGv0Ya6MzsXuHhf4cI0skjBGFPpco5wArfXisGFK%2BVoLzH8BoTqxxpruruPuSwDEW9wylMqf8xJ8kBnyTknWJJyQ2LWgZeFT82w5mdXAtBRCqF4rOuOeRaijgbnZUsAUDWSsNYyvAm%2BEMEluvyX8XC7ISLUOGXyFi3DnQIB7lJZS7yxXFGTMirsxKiyYecUR6j8XWP8f5RVZq2x9YjXvctZQN1jrDmu/9Cj/IwSMfYiCQb4k4gLBsUjbtcQcbzrXU/hm/Ps4vr/UOEW9VkNK2hXrdjfG7bybO0/ae6QfA2a8DHfzWdkkRam1XbLayu7brHt1pe8W977bD/pqFpZ/tTBB3DtHSQgnTT0hwkGh0ZWz0XTz0R2MAJxsArRvUx2xw4H1DSVXVPQsHPUy0vRElJ1vX5wpwgFcAl1pyKHpxZzyHSAlx/WqHZ1FwII6B52p2w0gwFxgxQzIJF2wyYNfXGGQzoNIwWGIzpTSxLy%2BRVyr12Br2j3rwjCGB11Y31zby41IB41N0oDI0txADMH83WHWBGQuT0zeT0PJFuWM3EI9z%2BQBRUIE3JCJVty4CkFiBtxEy4HJAU3WDEMy04E42azI2JXMO8I93b3mBbVSGcEkCAA)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/classic_recur.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/classic_recur.test.hpp)

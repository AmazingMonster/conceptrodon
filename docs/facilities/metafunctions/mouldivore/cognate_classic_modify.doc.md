<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateClassicModify`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-classic-modify">To Index</a></p>

## Description

`Mouldivore::CognateClassicModify` accepts an operation.
Its first layer accepts a transformation.
Its second layer accepts a list of indices in ascending order, which indicates positions in a list, and returns a function.
When invoked, the function transforms its arguments at positions indicated by the index list using the transformation. Then, The function instantiates the operation with the modified argument list.

<pre><code>   Oper
-> Transf
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Oper
   <
                    Arg<sub>0</sub>,
                    Arg<sub>1</sub>,
                     &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;::type, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;::type, Arg<sub>I<sub>1</sub>+1</sub>,
                     &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;::type, Arg<sub>I<sub>n</sub>+1</sub>,
                     &vellip;
                    Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateClassicRemove
 :: template<typename...> class...
 -> template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateClassicRemove
{
    template<template<typename...> class>
    alias Road
    {
        template<auto...>
        alias Page
        {
            template<typename...>
            alias Mold = RESULT;
        };
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>` and invoke `Operation` with the result.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinus
{
    using type = Vay<-Val::value>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateClassicModify<Operation>
::Road<UnaryMinus>
::Page<1, 3, 5>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateClassicModify` by combining `Pagelivore::CognateSegment` and `Omennivore::ModifyTypes`.

When provided with a list of ascending indices, `Pagelivore::CognateSegment` will find the differences between the adjacent indices.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub></code></pre>

Then, we will make `std::index_sequence` of each difference by passing the following helper class template to `Pagelivore::CognateSegment` as the operation.

```C++
template<size_t I, size_t...J>
using Detail_t = Capsule
<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;
```

We will keep the first index, <code>I<sub>0</sub></code>, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>
-> Capsule
   <
       std::index_sequence&lt;0, 1, ..., I<sub>0</sub>&gt;,
       std::index_sequence&lt;0, 1, ..., I<sub>1</sub>-I<sub>0</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>i</sub>-I<sub>i-1</sub>&gt;,
                    &vellip;
       std::index_sequence&lt;0, 1, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;
   ></code></pre>

`Capsule` is a vessel holding the results. It can be declared as follows:

```C++
template<typename...>
struct Capsule;
```

Finally, we will transfer the `std::index_sequence`s and relevant arguments to `Pagelivore::CognateSegment`.

We will use `Send` to connect operations.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation.

```C++
template<template<typename...> class Operation>
struct CognateClassicModify
{
    template<template<typename...> class Hormone>
    struct ProtoRoad
    {
        template<size_t I, size_t...J>
        using Detail_t = Capsule<std::make_index_sequence<I>, std::make_index_sequence<J-1>...>;

        template<size_t...I>
        struct ProtoPage
        {
            template<typename...Elements>
            using Mold = Send
            <
                typename Send
                <
                    typename Pagelivore::CognateSegment<Detail_t>
                    ::template Page<I...>
                >::template Road<Omennivore::ClassicModifyTypes>
                ::template Road<Hormone>
                ::template Mold<Elements...>
            >
            ::template Road<Operation>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[Run this snippet on Godbolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIFmABykAA6oCoRODB7evgHBmdmOAuGRMSzxiclpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5fHhyYaAIInZwDUACKY6a6MyHiYCk/nN3ujyuIIugLutwhZkCEWQ3iwTxMgTcXkctEIAE8kdhIeYYQw4V4EUi3MhFugsFRsbigecnspiJgaKp/mdwQRMCx0gYOSSCBiPsw2KQntkAF6YAD6BGp9zQBPeBHpjOZiMCLyeBGIXkwSKs90hwOOTzcTHSCi89FZp3ZnO5TF5yP5gtYmAAdB7ZXdFtqHCazRb6HqaQ86dhVByGOgAGLEWTW66Qjlcnm6p0Cxiur0%2Brx%2B8ORmNxwSIgDsVhLL2DBvuyftjrctdTfIzQvdnsC2CecKYCj%2BHkETBWZE1LddHrd2HobEECmzWtzSvzrljshJ/daQ5Jk85jAICnH1I7uLLkKeZ81dqb6ZdbHHFkwwAiDAiwFnR/u56eXmyRieAFlPHQNUNXXQdImIEl70fBhnyMfcPRFbdpz3A8j0CfUIQrKsIRrS8HTTBs8PrJhUVQVDO27XsniETAAEcdQVEUSKIccADU2jwJhYnoN8cXuHM8wjZcixlZEaPor4CPY4hOO435yK9EwTw/c9G3wklmLIj0oKfF9eNPc9vxfekmGATBgOouiGP2SCH10uDxxFaTZJ4hT0OPSt3OrUNngAeWnZ8ADcSHYEA3AMXs8GQAD8CoDEABUMz%2BAFIVbBR0iYfYnn8xggpC0sMKTIiCOdTNb3bPjvXnP1wp7bJoowPA4sSj4/iU8tPMK2lngsHtzNNJQE1tFN1ORTTxwASTnX0lVqyKGtihKkpJckQBACIsFUSUlAkhUSQmtzKvagyzzU%2BszpK0dyrdbEuwiv5fI%2BYgHVyL1PwEpUGVQIgACVUCYdAToKoHPwukHzxJcHPzPQ5DieAB1czv3MkwADYNAZJk8FUfbsQPdHNVQJ5GB8BJ8MRdGV0EeK2jMvc0Y0G6VOh6HMeZXGO3HKmCBp4g6YUUgoeh2GEfMgB3OhaE1Z6GAUfhiBYTUEHMyIIyeWnScEJm7hZlnStbJ5ebpwXmd106rrbN1euQABrI3MHp03Pze3XFhe5AuwERZMECsR1dIp48HQDFaAgDYhYAWlu01zUtXUnYh5Ehc/bn7ZQhDk9Ui3sqel6BBJNPsTW0qTZ1s3z2tu3aYd%2BDtbNw8urLvXiubG9LbuYBGR3GcXZZozfwA2ggKRDUsDhUqICDkOSQ7rvkNr7Ew/Drym9LTqQ1BlunS3hsLfIu66vHWfMG7%2Bn31X/vgCeP6AYsr7fv%2BwHkWP0%2BF7QwqsJXoqRuI0jJqYv%2BHoABS00FwmnulFGKTUlqtRWgQdAa0NqYC2jtayBEDoVRFKtdaUZkHbSspJEkQDDrHgwpvH%2BJUd76zHBVA%2BVFHpkwGL3UU1VPpxgfgDIGx0E6nRbjwtUbhM4wzhojL8g0GZs2xhzbA%2BMNCE2JgwUmz0OQUw0Knau9N0Z13LmeSRONkRTU5h6dRfMa6lx0cI0WTwJa0CllqQwcsSCKwIMrJ4qslQa2QtonR1C2BPGjHgYgiw07mIsSLURyNVF6KIXjT0BMiBPGAETTKcYqIuPMvgN2e1%2BGfhFvEAgYsT4ME1GLImMx%2BbePLtE5EICjFuj/EHdA9A04CyEU8cJ4tJbSwcfLZxrj3Hqz5prAglSza%2BPMjReU6AQltPGXeTKVdTGO1Xs7c%2BZs3aOA9vKb2vspaaUDsHUO4d%2BFRw7P6WOQZ%2BGQxyeeExFSM43PNm3HOjDXrIgCUEnmGii4gBLm0hpFJmkaNrqEnx2cGHKLeW4SZAhpnfI7MXDMoLy6VxaQeK578N66zBteMq7dO4n3nswz8l9/yAQsmPWgE8p60BngS1%2B5El7YWdp/Ru5C6yUIoa3PF%2B9KK1xfkStZhkfxXxvsPdUypvqoDFXSueu4344i/qykMRpr6NF2NkQK/U%2BpDW/hyjSgC3QTQASxYBIo5kel8uk4g4k0H6X4qw8BdVIGNWastZE2CkEoIIXtAx5EsHwMQbg71u0bI1P9dla1trJIKtIUDHFhEuW4tbLy%2B6LzIX5yFWeD6kqOGA1NtwlZqk%2BFFrPNc0twsRFI3EejapbhDEyLiXIhJJM2DKJRpTESLSGajN1nWhtXMu3AuRWbDp1iun2Nlr0pWKtkEeKGV42Z2cPnBI0SO3WY7IkSJVFImpsSbrxKJkk9WyBUl/HSU8TJrRskVtyXDfJhTGAlLKcC3tLM621MbfUxpQKlmtMee0qt47bHdKnU4mdbi52DOAMMt90NxmWSmTMgDFqrYLO7Riyq6zWibM9rLDkuz/YJJpWHSOt0lxRm5kLctFiRzPLmvVKBbrYHIitcrG1Pr9ixoA8XYq19H4kghXnBgxLda8YoWSoekF0OvoqtRrN0NxMcsk/mitNGLF3Jro5JdzyhNMPeYE1dSyfl/IAwCppmA0UPNvVnXTud9PQsaLCwuCLfkZnk4qtl2KqF7w9AK%2BVomzyksHuK0ejQqUZknoc2VhL5WMo2MvMhENlXeXZVeRN%2Brk00JumcvlR96WCqw8K4yYq77sOlQJ5%2BBW4tyaVevbySlKzeVVUIBAqICBWhSrhJNppDWgL9K19rQYv7dVOE8aSGJYh4GCoyNaLUopiGUKgdIur7hpQyllCbU2Zso2UjhO4CbxpyYdTNQ2AoFu0CWyt46KX9uHYDiu0SlUc3zdEJd5bJJHuKT2ySkVdGUYSsGwQDrBEG4eWwnq9L%2BzHsmqJjCqM/WlSvcWx9gznyRTw6fkdH7xXfylQskDkHn3DNPYh7dyHo1esJJh0RuHTmoyw/HGxhI9qqqneR%2B99IxP0eIdhSKZnQSFIGhx0Fv7pUuESoo4WVcWW/Ec6u4J61CrEUfGYUp1MJkzLc8WBj%2BnWOyf1f241lVdIaJRlWwdnzbchds7AWb4eJ5yfdcyxlqHfXctpujYxWnbEOJcR4ojyyCOxKcakn7uSsbz6FrS5T%2B7pqcsUTTXpt5RXs2OreBuWlBaRfQ1Jfjke6bhMkmcv7%2BStWktlqd6vBNcetIJ7ofy6rPcFOkp%2BoOKWBeM/t5iwyiqKu0wf0NxT86VueW0L5SaWQYEEjmt8xOKcAXz45vt2uKfm5kRIRqwn77FeLw9Zr3P26E/k%2BZtTyw07Xe6BcJz794y%2BeJUn5ExvhfM43K7%2BNyN6vVDR8pvH/dfLcqzeZ%2Brej8Fkl%2BtKVWgB6cCe/eBuEOo2xoygpkfQ02IUa0HgwAzAHINEwAyEFu62mU5kSBZk6IO2wM3kNeO8R29ex%2B9mKekIOaGBWBmAOByEcapsCa4oUoSoxqooeAEo0o44n6QMOa4B1%2Bu%2BMe9YXBghHoAA0oFk8IyPRIEr8E8BAAeGYKjOYKjBALIQIk8EAglkLKSgABKNKMDSgWSP77QihAIRyyFv7X5D4cFUGGr%2BZAFAykrEEA4agr6y7mRbaoGzYgDy6o5uDuHQEmbuYKbq7kxt5X7IhiGQGxav596/J8ZmEUgWGk6f4iwTRRhRSqGiDFJiAKBEzxBPAZS9iYBASkoMyerBr4Khq6haLxo/5ZgKY5qZFYDFI3bOFf49bSE8FYL8HcFCHMJdHmFP5uANGbRNFoI2EGEkLZ4SHFqDGjEyFujyEKafhKFeAqF/DqGeiaHaG6H6GGHHIVqkrgGWEF7WEGK2H2GOGpa6x54ZgE6uDcoGyBE7ZzbnZvYK4PFLFpHi47HnixEqLxEQFuA3E5Hv5V6SGXTW5%2BZN5nzAF/YhYWTdGMA97zzkSwF1bwGYRNb7ZGigjkmJgIFPATQpinzCYW5kkUkgjgjD6cou6oZH5J50Gn4MGOpMH4QMYuqLTsEDHsntHXScl1RPAmFOICBphn45r3wVacIrFCycEbHDF8ECEjLAIKHXEOzt63ESoxyBgETYIsBMA2xSherzGEIGLYgBoIIgAWlWmSg2moJ2luB2FcD7pg4vHNzrHamTQKGKnlbeHUY37eb75z6b4eEAbBbkoF4r4Abqa0ZPJ4pB6qZpmJyCIAZjLZzeGkFoFhSoCYH4SsG7gkiwkKG0YQlEHIH7Q27ZllquYXT8acKsYBRBGhSCkLTQItS/A1libpESYyrIgykKxylDksx1kqZbgv6RFgkszTlPCzljluD3GeYRn9FjKuHx4RGs5mxeHIFlZSrhnJG97b4rwso7lrFinRnIk0H/4olQGHm46iqgEF5KnrkHnPHElEmMkUngiqrhisDcjmRdY%2BRMlsghh4iwjwgA6kgCD7DpBokm7PDsQYgW617UmB6YWkIsLux4beyqDpDEC05PC7I6gFRTSsprwAV0hyDMDEAYgNKKLJQwXO7pYIbsQQHPaOpMVtCsURDfgim3547vEF74XIgRy8VrRUXylwG5F0iP7YXimWyB73GNyqp/gGlUBeAEgDBqUPlj5uh3B8ys7BZ6UGVNACAWT8kci9lMZYisbclP6VRrTrmCUsVsWiXnxrTnluBcAijBBPD%2BBehrQhYzwWV/mGim5eDpAlA1E/S/CWhKiQWkpCAJVJXoApWBhKh3FuXF5MAuVuAaAOnjYlUkgRw%2BkdhORVXIhmAVXSVuARyBDNUNVuCSAdWlURzhVoRbnNZ0h5VpUW6t6pVUoWS6WtD6WGVQotXlV1WVWlW1XYD1WlVNVLUtXtVbWdXdW7WlX9WKqDWkl0jxS/DpWcVVTuySh1QJAEAQDYIKCui3VvhuAjVUoY7ZVZDJUTVPaJYcBbC0CcD%2BC8B%2BAcBaCkCoCcCCKWDWCig7B7AozQg8CkAECaCA1bA2wBCSBugaApBmBmAACcRNXA/g%2BNKQXAJYJY0gwNHAkgvALAEgGgGgpA4NkN0NHAvACgIArN6NENgNpAcAsAMAiAIAOwBA6QqI5AlAaAXIdACQUQronAqgKQqMEcqMkgiSyAHsUgboZgvANRhAJAQceg/AggIgYg7AUgMgggigKg6gAtpAugwVYsz06QnAPAQNINYNGNUNnAvkqIUtSoqAVATwqt6tmt2tutuNZgahHg8t9A5FeIXAGwvA/NWgWwEASAct6QCtZAFAEAud%2BdIAwAUgZgfAdAHIQSlAsQftU2zFGIntvADdQlvksQ2gjQ/NqNctyEvkDAtATdTtWAsQXgwApotiPN3AvAWAFpRg4gw9KhTQWqU9kNyC6qHIzd5AggfQft6IsQz0LFHgWAftWoeATN09pAWqxAsQP1bwc9wA6IRgGNWwVABgr4rEPwYsDC4NqN5twgb21t0g/99tagftLt%2Bghgxg1g1g%2BgeAsQPNkAWwy2AwU9Ec5II8pgcNlgZgHN19MkWAiDYcvQ/QuQLgUYcwfgwVYQKwVQNQegJQOQAglDDDWQTDDAowdDEwwVDQtlgwSwLDPDfQXdzQSwnD4wiQPDAjngXQegbs7Q4jawkjWwZRuw%2BwEg3tHAoNbNftnN4datGtWtwAOtTwetcdEAuAxtydKNadaNL9WwysAMEwxD2NkggQboRNgQNNGgkgZgkg6MGg/gqMRN%2BgnADNpATNgQXAboqMXAqMKQRNlNqM/gkgZNnjqMOjTtnN3NvNdjAtWdot2d4tQd0thdxdSdStbAnAbQLAgUJYEcTAB8v4XARNbo0Ta9%2BARABDZtsglt4gNtIDSgYDTtugFdbtZozdmj2j7NvAnNgdktqITwod%2BjkdWt3YzTrT7T8dqAidCQiI0IZgtjGdgtRT5TM%2BZTOzedSdKABgRgLTXArNNAVKLOtd9dEQQlW9rdLF7dndDgW9vdu4/dg9ftI9Y9E9tAU9qNs9UDC9kN%2BAjIy9vwft69yAqIBwqNEQHIdNkN%2B9h9GIx9BwkNZ9F9qN19t9Sg99MLL4L9fA79Cgn9mA39goW9/9fTQDtt8gQzjtkNozkDz9WDVglgcDCD8AyDqFuQaDGD6oAr1guDsz%2BDQcSLSDJDIjzgEArggjIQUYij9DwVjDAwmr%2BruQOr3DKrfDQwswMjhQQjpDAgFrywlQEjcj0jBQVD0wwwJryj2waj1tUzvtWTnAKzhjTTV8LTbTeNahljXT%2BzUTRz9jpAjjWAiQxDdN4TkTrTPjJY/gRN1NgQvj/jqTmTHNnAOTfNNLwtYtEtwdMtRdlz%2BdlTBwNTUdLACggUHsgUYbqYiwhtnTJtCCwVrLgDEgwDsgoD3LOgSQpA4zHt09frRbszAdJTIdYdqgzbrb7bnb%2BEiw2zuz1jgQgQcb%2BTQtOddbSdNbZziQbbiVkoHbRNkoXbBAkoq7wDVdLzEAddTtXzQ9qNX7PzXd/zOzfdA9Q9cLmAo949YgELW90L89hLM9S9jgK9yLqgG96LvAmLu9TtuLQlBLp9MkJLvAZLd9nIVLz9R7b9pk9LX9P9LLvTQ7Azo7XL4Dk7tz0D2DNg%2B9RDYrqDnAhwq0MrODeDCQBDSrxDvDAw5D7gVrbrNDjrSjrDpQuQhrbDAwnrcjwj5rLrsjNrqr/DHrtDTrUjwwmr8jDrqwurKjiN6jqdoTWj/rxbHA4da7bblFm7HI27Fjvbe7qd6d8bibzjmjabIAxNbo%2B7/g5NqTLN%2B7JY8T87/tXNtguTxzCWpArj/gHjVNJYLNKQkgpNXABNmhtngQ9nC7CXyXmjBtcX2TeTmdWw192QzgkgQAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/cognate_classic_modify/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_classic_modify.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_classic_modify.test.hpp)

<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::TypicalGetTypeSignature`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typical_get_type_signature">To Index</a></p>

## Description

`Functivore::TypicalGetTypeSignature` accepts a function-like type and returns its type signature via the alias member `type`.

## Type Signature

```Haskell
TypicalGetTypeSignature
 :: template<typename...>
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalGetTypeSignature
{
    using type = RESULT;
};
```

## Examples

We will extract the type signature from several function-like type.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** SupposedTypeSignature ****/
using SupposedTypeSignature = int(int, int*);

/**** Tests ****/
static_assert(std::same_as<TypicalGetTypeSignature<decltype(fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<AbominableFun>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<decltype(FunAddr)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<decltype(&Tester::fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<FO>::type, SupposedTypeSignature>);
```

## Implementation

The implementation of `TypicalGetTypeSignature` relies on dissecting the structure of the function-like type into parameter types and return type using the metafunction `Analyzer`.

```C++
template<typename Fn>
struct TypicalGetTypeSignature
{ using type = Analyzer<Fn>::type_signature; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAHFykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn4JdpgO6bX1BIVhkdFxrXUNTdlD3b3FpYMAlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKYia6MyHiYCmfbB8enex87r0eHJ9tnR2YtAAngAvaLPLbfAiYFiJAwws4mADMbgIwJuzDYKOwvwUBGIXgcAKBYOiymIqCI6JuSIA7FY6RcUVZjr8YXCEZgkaiaYxWNyAEqYAikM58rGYAB0MqOxGAChxeIJRIIJLEZOIFKpVIxmBRbmFBAgcoVMqlMyVbIZvzOdrOXlSRnFeoA%2BqlgMwCItuSiLmcjSb5QpzZbkayfkyWb92bD4UxEQaJQKAyKxcm2ObTYrkbjjvjCcTARrwVrKdS9QbA9nQ2c0Ax8VbIxH7Q6ncAXTd3XhPQmfTz/dXg6Ho9bmeGY8cOfGYUm9ZKzgAxBhNguq9Ug0sgM6JLwRWh4ZAbzXais3A3LnH0xnjiOxzkJ/W8%2Bcpy%2B55WFtXFzfRC8MdZNtuu77oex6lqeurnqib7YNeJhRhObJTnGXJzpiKYALKwsu6YvmwZy1J%2BPqriqRakqWBpYSwy4EaR3rEOwIAAe%2BxxAXuB5Ht%2BJ7lpBT5uFRMFwQhd7IQ%2Bs7Puh%2BGLgA8k2DEAI5eHgDFPApSkqXBZgAGwySAICoDcxAJiQEBhjeH7rlxFHQbJLFHGxIGceRv6olgyC0HyEDmDp0l6QZ0TGcQplhrB8HmYhPxvJ80VfL87zrGcACSnKwowdTVJCmzfPFMWfN894znxGbcjBFnEgAKhih5iAA4iKlU3EIPZesR1oWG2wQdnyA5gS5bgwXpfLdr29FPuFIl/LlLxxf82CqKw8LctNUVTVCk4/GYyLBO5XhYDybj1ssiQEDmeaRZNmxnFQXgMB0AhPMtRzBAeIRnMEarXQwEDvWK73rJaDJnAx9EMGcGgsvSzJIRdCVMBEqAsMEcP0FdN13Q2mX7L8jqdQC8OI8w%2B6YIuN09e932CL9gj/XW90EKO53xajt0Zck73RA9a3HM9wTckwXhEEuN1HOg6DENeSLaZ9kMMzN5xs4IEKC2wJQQp96Oc1lZVquVjwwsQMY2scrY86973MxTopvdTMy0w2aphUDIqLKD4PhjLY6yytl3qxlqARNo7QnZj3xrsSMmGy29rm/5RlEEFMyW1TBA0/W%2BIS8DLtgxD8FQ5Gt7rUzQheIkuSYOgDWYE1I39o9OPOsXpcpOXlfVy1DFk4ISfWynZmF/8uv4prWP5ulh6ukwChKA0ED4ugekKAKE85m4DXVbQdUEK3zV9gxBpuR5erUDdIWDXqYqN2XFd6m3u9Ptgfejwm4%2BT9PxpzwvS%2BTwaa%2BiBv9U3x3qNA0Rx8ZIyJiTFcuYz43AviXK%2B28a571zI/I4%2BJn7IGXm/WeBB54gEXmwZeP8qp/03og9ufED6eUgSLMWp8QB8jgU3JQ19GpAOIighm6DHCYNftEd%2BuDP6EO/qiX%2BtUAFsKQZQ9oh8bheW0oPfWelPr0MYQReBzdWFV3Ycgh%2BXCx68KnvwnBeCCGYCIaIkh4it6AKkReWy2AYGYCYQg2xFCcSoI4HMWgnAACsvA/AcC0KQVAnA3DWGsGcBQCwli%2Bk2jwUgBBNBeLmAAaxAL45EUo6S%2BN8XSLgvizBcFiPELgZhpA%2BI4JIXgLAJAaA0KQQJwTQkcF4AoEADSklBK8aQOAsAYCIH0gLXcooKAQDQHCOg0RQgCk4KoWIWkAC0WlJBnGAMgI8UgpRmF4OXQgJA8DzwSPwQQIgxDsCkDIQQigVDqG6aQXQCQADuRlEicB4N4vxATkkhM4NJYZAszioCoGceZSyVlrI2WcLZZgzgQA8JM%2Bg4tzDIi4DMXgXStBzAgEgCZiQplkDGXiglIBgBSDMHwOg%2Bt2kQAiD8iISNiDAnebwBlzAmXSQDkHFlpAJlsEENJBgIIflYAiF4YAbgxC0HadwXgWAWCGGAOIe5%2BAGIdAAG6PB%2BZgVQ7QBYrASezSpwSDwRCMkyjwWAfkEjwLU2VpBNXEHhkoK4CqjAvVAN0uYVADAKgAGoPCedJTEPKTnCD/hc6QYablqB%2BY8/QiqUARMsPoPAER2mQDmAZaoMrFlzz9KYSw1gzDNMdcQQ5WrM0VCqOkFwDB3CeGaP4etkx%2BgxASLkNIAhRgtCSCkLtDBW2q3bdWoOnRhiNEbWMUd6MugNCHdMcYIwp29vQfO3mUwBhovmIsZYEhPkcH8Y0n5LTQULOWas9ZmzJDbLhbgfZyL4nosSckmYcwECYCYFgGIplSDpMkFkgAnMiOkkgNCSHKVpepvitKAf0JwappBamoqlFpLgWlYiAfiFpXxkgCnAa0se%2B5LS2kdJfV63pAycVDIICM8glBiVIpmWwTg9QWDqrpIspgdYDDOi4IBqUXApTBL2fHQ5egw1nPEJc6NShY33N0BSl5TA3myoPUeppvAWn/No4C4FZ7wWrPcoq6FAmhMaDhQi/FSLJbIjMM%2BzFPTqOMeiPR8ZCNrMDGM0YfjXAGk0A8hzSgdL7lsvqMy%2B1YWOVcocDyvlaVBXCpVZgMVEqpUyoSfKxVyrgmqrHZqmVIndXIH1Tyo1PzTXmuBJalYwSbV2oSY651mBXXZc6q%2BvgvqFABswEGkN9rJMRokFG2QMa7nBMUwmowSai0ptNRm392b0i5vzciC4harCWBLVpstFaFtzDaOjOtDasi9sCButtOR%2B3VB7VdvI6QF1bpndUOdk7Tt6EOy9idj2R1rre02pdPQLvDv3Tu2JoPKkaZPZwAzF6eMmf44J4Td78Dx1s2ijFr732fu/ZQA9iHkMCfAzkwDdI6TIgg5IFZCRNO/NabYMjjnsVUaQAsXToyGMeYJcxlYbGIUsAUOqo86rEdcnxLs1HByjlXPDec4bMuxtxpAMiUgynVMfPg4e75xG/kArVPp1Q/PBfC9F4%2BdO8Kuc2ZRciBzHXnOW9c0Sh3MQhel1dCLwDroxcEFdIbqNVKgu0vpYyiLCSovAk5YHWL9r4sCqFRF3LKXxWStoNKnlWX3W1blcpfLWr7k6r1TCMritjW8Eq%2BFmr1ry0Nd4E15urX3XtYoz6pg/rA3BsYKG2QUnI0K7k%2BNnQyupvGGTTYeb8As3HWW5wVYH8NvFtLdEctWB9vPdrRAVwt2EjnaKJdjt130hb77fdgowPF1r4EK9o/n3x0TDP09v71/vv3/bQdmJe7t2Q%2B180mHfuzgC6FzOA9ylG9xRwfXR1ty9Wxy/QGF/UqQJxADMAE2RGRFyXAz8w0BQLpAwyIx/3p3aU6Sxz/RACp22UkAg1iEkDpFKRKWwM12RG/y004ExygM1x2VwKYPpyZzmEdVSGcEkCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/typical_get_type_signature/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_type_signature.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/typical_get_type_signature.test.hpp)

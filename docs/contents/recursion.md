<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Recursion

## Confusion

Why hasn't recursion created a time loop paradox, destroying this beautiful yet cruel world?
I often reflect on how I should think about this problem, reaching for an answer.
Before I figure it out, let's look at some code:

```C++
template<int I>
struct History
{
    static constexpr auto value
    {History<I-1>::value};
};

template<>
struct History<42>
{ static constexpr auto value {42}; };

static_assert(History<200>::value == 42);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxBIAzKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXEl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwcBJgsyQa7JgluYQQA1ACSx9gmGgCCM8ReDucAEngzJACed/cmAHYLOc/ucwecZkxHMhzmgGDNMKpksRzmdzgA3MReTAgoEfL7EX4nS4AWi4NxAIEx3kwgIAIsdgX96YzmQ9dvtDrSTjc/k8Xhd8URCcc3AFeQ9AUyHuCIY1obCBAikSi0dTsbiLOKAQyEtL/jrWZKHpDoQB9JgKJTNCBCn6iswaDQUqlYnHHXV084BZaMjirWicACsvD83F4qE4bms1gh6027rMCR4pAImn9qwQmCYWHiEFWAGsQEGAQA6AFcIMaBIANi4XDMAE4EkH9JxJKH06RIxxeAoQBpU%2BnVnBYDBECB1gRkl4CORKGh9nQ4hFWNtVAAOGskmuSc7AZAwqSlsy8TD4YV4dB6fiCERidhSGSCRQqdQcLSkXRJADuxCYyScDwAbBp2H4RpwADys4zhcqBUOcm7bru%2B6Hucx5mOcEAeEu9AouYCQJMsvBpuBI5IFOsHzhAi7JMuxCrmwnBITue4HkekgnmeF4kFeN6yPe4hPre8hKGoXa6FwpB/gBQH%2Bm2HAhqQYafj20HTrO5zwYhW6sahHEnlhOF0XhIJJlwxFDmRpAQEgtH0dR9l4SAwBSIENC0LsxD9hA0RdtEYRNN8cmkAFzCEpB0TaLUpEpoubCCJBDC0MF4GkFg0ReMAbhiLQ/bhuleyGMA4hpfgxAxXg6KYPln6IrUs7bCmZxdF2tB4NE/6Eh4WBdgQxB4CwIXVcQ0RpJgdJFUY7VGMOfAGMACgAGp4JgP6QckjAhSJgmPtIImvuJaXfvoxUoDGlj6B1/aQKsqDJD0%2BV9vGWwSCBilgapnA6chbFoRhWG4IQJBmcmlmkVo5EoKguFxI5MMmSMrkdB5Xk%2BX5aVhUFIVYxFUUxSF8WMAQSUpV2GVZTltB5SFWAsMVpWfuVlXVbVZ6qA1uwhS1gZpe1nVBT12yfv1g3DXEY1KJN9PTWEoDWVQC3Lat62bWGKY7aIQn7bIh3vp%2BkmnbNpiWNYV3RDd%2Bbdg9mRPd2I0DVglurDUdTOBAriTH4UkhPMZQVHoBQZAIXuB2kwcMIM/tLJ03T1LModSa7PR9M0UfDJUYz9InWdp37GdvWsGyvRZClKSpEEcD9ensehnGYRAQPCqDFkkcOmbZrmlCFiAyalo2ZgbmY9ZbmYQZBlwjYbkkvMdqQQ0JGWNYJFuG4AhujaT5IkgaJIrYV92nB9gOVmQzZ462ZOMGzvDsMMWunBNCw6IAiSTCwgYRjoY2pZcKWdU8UdvxO8Ws9rPlEm%2BCSIBAgyUAuGd65cuxqWvnBBCT8X5vw/sVb%2Bv9/5GQRvRUGZhwZzUvk5OGFAaIEOcug1%2ByBP6uU3oOVGcR0b%2BUCoSHGHDviRWig4QmMMEok2SqlJmmBMrZVyvlFMdMGbC14MzOorMuz1WQI1bmghWp8w6l1b4Qs%2BoDSGgVEaksJpTRKnLOaismCLRWmtDaW0CqawfBIHWL4xL6x0NAo2xgLo2H5s7a2j0j72ziI7Gq8AXZdEqu7T2ng2h6F9qUAuUkg49BzmkzI6dFiZ2TvHbO8TchJ2iW7XosxskByTgnQp3tc5zGSTkwuCgXqPgQZ9Su5xaGYPodgyeuCNCA0AS3EhZEO45hGFbWevAF5/y4BuDQNYgw1g0EGHeZgASNnXspJBIT%2ByDghvJUcE5KI30oeQ%2B%2BTEOBPxQiwBQ6IYToj6VyGY3FgZAKks47W4C9ZQOkLAuSbTtlpWQRpVBnTiAsBuXch5TyoQ1QuNhahcRQaSBGWfMhSKyBnMxVSZAyRkhmkeY2M0zyCAWghbuPgdA0aUAxp%2BXGqUUwMt4QTAqRNEoiPJuIymUjabmMZgovAFUlERLSqo9RBUeZtR0YLDA8jUyGPFqNca0sGaWIVkrOxqtHEawEqA1x3yPG/J8edU2l0AmRKCbbEJqAHZXgibdWOMS/AewYO4GpiS3UVJjpkkOHrUnhx6N63JJSU7VJyLUvJAhU71IWJUupOdIR5waZUl2LTC680QcC761y9y3PuRiWFuwZiDLecMtuozSBZnGXmd6c8Zm/3mYs5ZqyNDrM2RuIFX1ey2BPgc5YPcAgng3JIRsy8NxrwWVWKSvMEjtMPj2/t71TxdsrhWyGqwRrpGcJIIAA%3D)

In this example, `History` calls the previous version of itself in the quest of answering everything until reaching 42.
Then, it rolls back to the present, revealing the truth of the long-lost past.
But, if `History` is needed in the making of `History`, how are we supposed to grasp the `History` while producing `History`?

How is a question for a being possible if the answer is part of the being's definition, the very definition that decides its existence?

To demonstrate my confusion, I will prove that `History` will exist only if the initialization of its class member `value` succeeds:

```C++
template<int I>
class D
{ public: static constexpr bool value {I}; };
```

Only two values will keep `D` alive. Namely:

```C++
static_assert(! D<0>::value);
static_assert(D<1>::value);
```

All other inputs will result in narrowing, which kills `D` instantly:

```C++
static_assert(D<2>::value); /* will fail */
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMT%2BpAAOqAqETgwe3r7%2BQSlpjgJhEdEscQnSdpgOGUIETMQEWT5%2BgbaY9oUMdQ0ExVGx8YkK9Y3NOW0jvf2l5f4AlLaoXsTI7BwEmCxJBpsmAMxu4QQA1ACSB9gmGgCCyAYKCicAItc3JgDsFidvJ38nSS8MVoeGQIBOU0cyBOaAYI0wqiSxBOMVQnhOADcxF5MD8vhcPq99t83p8iVZbm9IaCAPpMR7xAgQMBgF4HNwaS4gEBY7yYeYHCk3anIOkMxoQIluLhcnnY/mCqn1KFipQSqVmWW8nEC4knAD0ACpzgQwBwnlgmOgTob9RxFrROABWXh%2Bbi8VCcNzWawQ5arXHmfY8UgETT2xYAaxAAQ0ADouPt9k6NAAOSRmALJrgp6SOjiSXgsCQaDSkN1aUieji8BQgMthjhaRZwWAwRAgZYEQEEciUNDbOjxSKsdaqVMBAC0AUkJ2AyGhUjjZl4mHwRGIeHQen4ghEYnYUhkgkUKnUTZ0egA7sQmElODwHc7XeGq5wAPJebtfk6oKgnccpxnOcFxOJczBOCAPEHehkSDLh5l4Rtm1ICAkAHJIhzICgIAwrCQGAKQzD4OhNmIOsIBiV8YnCBoAE8H14GjmGIOj3xibRqkbEMBzYQR3wYWgGIvUgsBiLxgDcMRaDrd1RK2QxgHEET8GILi8AxTBZMrBFqi/dYQ2ODpXxBGJb1YjwsFfAhN2LOTNOIVElGeBSjBBIxw0WKgDGABQADU8EwK93ySRhGOPYRRHEI9d3kJQ1FfXQuH0RSUB9Sx9DwGI60gRZUCSLpZI9BzNywHKIEWKoamcCBXHGPxktCcIBjKIZkvydIBHqvQOq6GZBgSZKqq6Hoxk8Fo9GG2pRj6ZrZja2wZu6oaZv61rBsq/01gkJ8OBdctX2rACJ2nWd50XSRl0g3BCBIH4zGDRDQ08xYEEwK0hgq0ho0kfY4wATn2D5JA0DNAlLJ0An%2B/ROELUhi0CBNJHTDR/tjRMzA%2Bf7UwOkTq1retnovFt2zQzsvx7PtcNQGDh1HTgGhYDEPknJgYQMIwwP%2BhM4x09cSC3HdZH3aLpFi08EpE3RiJvO9GN2/aKw9D8KZ/P8TkZ5nWfZxSuZ5jRIOgzDYPu/YzCe5D7VQ9CaeN%2BIqbw2CQE1ln7kUrh/q4MsaFoMiKKokTmPo8Kg9Y9jOIccLeMYAgBKE18xIkqTaBk8KsBYRTlMrVT1M07TV1UPTNnCoz80rUzzLoyz1krGy8DskMHKczAXIztzwlAYm%2BB8/zAuC0K3RDWKRcPMXZAl89K2llKPNMSxrEy7L4DygqMiKqsSq3LTl/aToMhcBh3HGnJGsPta5na1JOsyY%2BGuSK%2B%2BrmgbJo6dSBFGppb5fvf39Wp/1smktL%2BK1pj/wvptFY20EIwz2i%2BPGnANbECZizNmbtOYe31tdfmcEHoISQi9Ugb0PoJC%2BvmOGxZMwAzME6LGToPaA32LGNMuNKz41sITS2JN4Bk0dvbHCvCEgYmQEkJINIMQexpLsLSBA6RIJnCRX28R/bUVoqxEOqi2IcS4lHGmfFY6CWEtnTA4lJLSVkiGdOmca68BzjUPOr5dLIH0iXQQxkRIV3otXaytlwpN1SC3VySkO6eW7kwXyAUgohTCnJYeUVR4RQnolEA%2BwZ7GHSjYUy5UV6FU4MVeIpVt65V3m/PwtVD7LWCGfMBC1eoZAqbUoo1TBrFOqt0IB2Q75TV/qAkoz8QFjQ6YAnpLVwFLEgYeBWcDWEIMZsBFgCghGYgwVIkYWDbo4MevgruZMuyU34bbLCI42AMzkbOeZizxHcxWQQVc2DBbJViQeCQY8TzxUnpeFJst7zukmSw5WHBPzflOOrWZZyFnQkuXGa5hsDkmyDPsC2BCiFYBIbtchIBKH/WobQ%2BhSYmE4yVm%2BGs7CGwEOjPsbmE4ZyexoYw5GToYH7Cmf8rZzZdorj%2BUS1lEZSAOTSM4SQQA)

For `History` to exist, `value` must be valid, which requires `History` to exist.
Fortunately, `History` indeed exists,
but only if the `value` is valid,
which isn't true unless `History` exists,
which will happen if the value is valid,
but why would it be if the `History` that it valued so much was forgotten by it very self in the endless emptiness of perpetual recursion?
Doesn't this feel like a time loop paradox?

Before I confuse myself even more, let's take a look at another example:

```C++
struct Past
{
    static constexpr int value
    {Past::value};
};
```

Here's the error from GCC:

```C++
error: incomplete type 'Past' used in nested name specifier
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQBspK4AMngMmAByPgBGmMQgAMykAA6oCoRODB7evv5BaRmOAmER0SxxCcl2mA5ZQgRMxAQ5Pn6Btpj2xQwNTQSlUbHxSbaNza15HQrjA%2BFDFSOJAJS2qF7EyOwcM8ReDgDUykwzJhoAgiYA7FYXB/cHM0yOyAdoDDOYqinEB%2BEEBwAbmIvJgDtcLMcZiAQMDvJhrgAREyJW6XK7I1EcVa0TgAVl4fm4vFQnDc1msj3WmzB5kSPFIBE02NWAGsQHjJAA6DSSLhXRIaPEaMwBAJmAAcEv0nEkvBYEg0GlIRK0pFJHF4ChAyqZHC0qzgsBgiBA6wIKS8BHIlDQLBSdHikVY21UEoCAFoApIDsBkK8pFyzLxMPgiMQ8Og9PxBCIxOwpDJBIoVOp9To9AB3YhMFKcHg4/GE5nqzgAeStloBqCoBzdnu9vv9B0DZgOEA89sdvzpXGWvD1BtIECQdod9DIFAgY%2B7IGAUjMfDoBHi2ogMRLMXCTQAnvneFvmMQd2WYtpanqGXa2IIywxaHv06QsDEvMA3GJaNric/MCxDMA4hPvgxAXnggKYN%2BapfLUVrbAy/xdCWtB4DEObHh4WAlgQEYKj%2BEHEDE6SYIif4AShRjMqsVAGMACgAGp4JgmZlikjD7kmwiiOIiYxvIShqCWuhcPoAEoBSlj6Kh2qQKsqApD034kgREZYDJECrDUdTOBAriTH4ImhPM5SVHohSZAI%2BlmekFkMIMJkjCJWk9H0EyeG0ejOfUsz2cMCRObMVkBf0vmLP5mnUlsEiFhwBIqiWGp1u6Xo%2Bn6Abcm2EC4IQJDgmY9L9oyVGrAgmBMFgCQaaQ7KSIkXIAJyJFcki8mYgRKniAT1TKHByqQCr0lyARcAEEr1RKI2clweKNUEqokpwWo6kV6aGiaI5mpWVo2tOqBdhOzpsJwTQsICVwekwbwGEYLb1VyXA8iGYYkJG0ayHGPHSHxKaCU%2BuiLtmub7jFcXzaWHAVhaVoHDWBwnWdF1XQBt33Ty7aduO8R5YkZiFYO2LDqOe2Y5OtrE7O8Pncg13zvVXDKjQtArsQa4bk%2Bh67hxHPHqe54OBx16MAQd4PiWL5vh%2BtBfhxWD/kYQFqiBYEQVBIaqLBK4cYhuJPihaG7ph2xqjheB4QyBFEUopFy4B4SgKtfC0QxTEsWxRIMnxH0Jl9sg/Wmar/aJlGmJY1hSTE6lyQpWRKeqKmRpB8CaV0YE6Xp7l5IZDDoKFpkieZPRBakNk9LnjmdN03n9EXXkCK5cxlH5nmBRnBljCFxlN32awbFF3c66DCWcHDxCnedl3U8jXB3Q9Gjttl4bY32A7FaQpXlSMVU631A13byVwzVcAqSG13oiWDGpLbqVHDutSDmlWO0zgdLrHaPjYsAogKvIC09cgYK4ZhPRyqpN6sZuLe04n7ISoxAZ5mJCDYsT4NSQyrDDWsJ0P5fx/n/ABkEAQdnJhObGKwV4Ow2s/eIT8iEjG/ikFIAB9X%2B9UGF4JmAwzBX1lyrkoGzNU3NHwMgEbzC8As9o3mFveR8itMCvnfJ%2Bb8DJZbkSNrwJWdQVYlhgsgOCWtBBIV1qhdCO5DbYVwhxC2xFrbkTtjfGiTA6KMWYqxdiP5PYQIkD7ZMAl/YZmSDTcSodJJ60juqaOAhY6oHjmpJOFdU5%2BF0tnIuRlG5hWskULIRcC5ZDLv5OJ2legt1yG3WuhSO6pLzu3NyxTm7lIWHnCKvcEyIPisg4enCDif2/kCXBzx8Hz2ej2fKy8VoGhKmVCqlAYo7xAGYO6iREh4mFHyJUCyrijVaWqS%2Bthlr42WGyfweIGp4glKKeqkh6oCialwfxnBEhIK2YtUZLIerBk2QtTUzz9mkAIhkZwkggA%3D%3D%3D)

Finally, GCC spits out some truth: `Past` is an incomplete type.
It cannot be used to initialize its own `value`.

An incomplete type, it says.
A type instead of a template or anything. Each time we instantiate a `D`, it becomes a type that lives or dies depending on its static constexpr value.
But `History` is a template.
When I claimed that the experiment we did on `D` proves `History` needs its `value` to exist, I was wrong.
The conclusion should be rephrased as follows:

> For every `int I`, the instantiation of `History` by `History<I>` fails if the process cannot produce a valid `value`.

But how do we know which integer gives us a valid value and which does not?

That's where mathematical induction comes into play.
We can prove that every integer no less than 42 will give us a sound `History.`

> Proof:
>
> - Base step: `History<42 + 0>::value` is valid;
> - Inductive step: Let `I` &isin; Natural Numbers. If `History<42 + I>::value` is valid, then `History<42 + (I+1)>::value {History<42 + I>::value}` is valid.  
>
> Hence, `History<42 + N>::value` is valid for every Natural Number `N`.

Since `value` is the only member of `History` that can go wrong, as long as we instantiate `History` with an `int` argument, the validity of `value` is equivalent to the success of the instantiation.

That's it!
I almost figured it out, although I am not so sure what 'it' refers to anymore.
There are two things I couldn't wrap my head around.

First, while mathematical induction tells us integers no less than 42 are good int, it says nothing about integers below it.
Will there be a negative integer that makes `History` perfect?
How do we know?

Second, why are we talking about types and instances all of a sudden?
There is a `History` inside the `History`.
`History` being a template doesn't change the fact that it is used to define itself.

What is recursion anyway?
In the mathematical sense, `History` is only defined on integers no less than 42. The definition starts from the base case `42 + 0`, walking through every natural number guided by mathematical induction. Its very existence is the manifestation of recursion.

In programming, this is not good enough, as we don't need a base case to do recursion.
Let us remove 42 from `History` and see what will happen:

```C++
template<int I>
struct History
{ 
    static constexpr int value
    {History<I-1>::value};
};

static_assert(History<200>::value == 42);
```

Here's the error message from Clang:

```C++
fatal error: recursive template instantiation exceeded maximum depth of 1024
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxCAA7KQADqgKhE4MHt6%2BeqnpjgKh4VEssfFctpj2hQxCBEzEBNk%2BfgFVNZn1jQTFkTFxibYNTS25lQojvWH9ZYNcAJS2qF7EyOwcBJgsyQZbJgDMbmEEANQAkofYJhoAgpPEXg6nABJ4kyQAnje3JgkWpx%2Bp2Bp0mTEcyFOaAYk0wqmSxFOJ1OADcxF5MID/m8PsRvkdzgBaLhXEAgNHeTB/AAihwBPxpdIZdzBEIA%2BkwFEomhAcUQ8Yc3GYNBpSeT0ZjDrSDtTTgEFnSOEtaJwAKy8PzcXioThuazWUErNaSswHHikAiaJVLBCYJhYeIQJYAaxAqoSADoElxVRoDgA2LhcMwATgOqv0nEkGqtpB1HF4ChAGgtVqWcFgMEQIBWBGSXgI5EoaB2dDiEVYG1UAA5/YT/ZJTsBkJCpB6zLxMPh%2BXh0Hp%2BIIRGJ2FIZIJFCp1BwtKRdAdSAB3YhMZKcHjKtUx6fazgAeQL%2BbOqCopxrdYbTZbpzbZlOEA8pfoiPMBwOC14lu36aQucPRYgJbJGWxAVmwnBnvWjbNq2kjtp23YkL2/ayEO4ijgO8hKGosa6JUS4rmuSqRhw6qkJqM7xvueYFqcx6nrWkGXjB7Z3g%2BQFPoCpqLB%2BaakBASCAcB/6CU%2BIDAFIgQ0LQWzEEmEDRLG0RhI0nyEaQSnMHiu7RNomAOGpJZsIIu4MLQqnbqQWDRF4wBuGItBJlqlnbIYwDiBZ%2BDEHpjgopgjkznCekFhs5onNUsa0Hg0TLniHhYLGBDEHgLBqb5xDRGkmDUi5RiRUYvFUAYwAKAAangmALruySMGpGGoSO0gYRO2EWXO%2BiuSg%2BqWPoUVJpASyoMktSOdqaVJVgfVOh03mZC4DDuJ4rR6CEMylOUeRpBkAhjH4lT5FtDB9Gt8zTQ4XRTDteh2DNAjdE0R0DBUww9JdExTA9cwVEsChGusEgbiRW4UZw9HnlBV43neuCECQnFmu%2BqZfnxAmoI%2BcTCaj7GDOJ7RSTJckKRZGkqWpxNaTp3kGajRkECZZmxlZNl2bQDlqVgLCue5M6eTNvn%2BZ2qhBVsalhSqFmRdFKlxRsM6JclqVxBlSjZRzuVhKASOFUwxVlRVVU1U5dWiGhjWyM1U4zrh7X5aYljWD10STQNQ2ZCNcZjb2fnwN91Q3X4ECuK9QTzR9617ZttRB/ttShyd11nbdF2LeMp21Hd0wlI9V1Jzku3Pfdq1Z4syyrH9xdi6R5E7hwoOMdB16wbeEDQ/ycPcYjWgLDadoOpQLogGaHohmY1ZmEGtZmKqqpcCG1bzmL0akClByev6By1tWCTViGM%2BSJIGiSBGVdxpwibJh3REZtmv4FhjaMgZWnCNCwKIJISTBQgYRjXiGHpcB6AUELjWQoOY2DUxyYUnDhEAgR8Kri1ADSusZKIHhonRZ%2Br936f1cj/P%2BADWKY2AnDMwCNPyd2RigQhT475Y3iBgt%2ByAv7iR3imPGcQCaKWUniUmXDPjaV0vpJyhlGC01MuZbmmBrK2Xso5c07NOYy14DzM6fNYyBWQMFEWghwriyijFT40sEpJRSk5NKSsso5TcurAqRVSrlUqtVTU5ojbDgkKbccWELY6BgdbYwXUbASydnGF2Ag3aoA9hNb2qdZoB3mkHFamdPobQKJkKOEdMixyevHNOOcloTF9gnOo71C5JLei9ZOecwQF0SWHb6v0RyIKBtXU49CsGMJwTPPBGgoZALbqQtM3d7SDCmgvXgy9/5cGrBof0qp/QaFVPvMwCQQxbzIsg0%2Bthz5kMvlmfiOZUGFgoABKh5ZH4cGfheFgCgUSQhRJ0vYfkCDwRhsAyoLiTYQPNtA6QcDCKNLWRZFB1EjwnguY2K5NzUT3PBI8gh984aSH6UjPZIl0ZHNRfEG5yRkhsjuSGNkDzJgcmICwBsfA6D40oITGcZNzLmlpfwymQjqYiLpuIpRkimYyLZpYrmSi8BeRUV7Cy6jNFOVFhFPRUsMCKItMYhW6VMoq05tYzWtjdYOINs4lCYC3GfM8d83xnU7bdUCVEwaw0NnhLiONL2/VonOFiQtXOy0Q4lLDikdJ20KnJIOpkq6BScnlJdfkzoicej%2BrKaMH1UaM6zFqSXY0/1iJIMBSDMFpwIW3OhVsSYPSXl9J4l%2BQZvcRlRjGQPCZUyZlzIWRoJZKzqwAuBgmTZKZtld1IK6AI7ZqySBDGvasm9pm%2BkqGLA4TST6to7QDDszbq5Fs7ksNK6RnCSCAA)

Seems like Clang didn't immediately freak out just because it couldn't find a base case.
Instead, Clang recursed for quite a while and said, 'That's not happening, lol,' then fired up an error like a real gentleman.

Let us look at another example with a base case for comparison. This time, we want Clang to recurse more than 1024 times before it reaches the base case:

```C++
template<int I>
struct History
{
    static constexpr int value
    {History<I-1>::value};
};

template<>
struct History<42>
{ static constexpr auto value {42}; };

static_assert(History<2000>::value == 42);
```

Clang hates it, even though this is a valid recursion in the mathematical sense:

```C++
fatal error: recursive template instantiation exceeded maximum depth of 1024
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAHKQADqgKhE4MHt6%2BekkpjgJBIeEsUTHxdpgOaUIETMQEGT5%2BXLaY9nkM1bUEBWGR0XG2NXUNWc0KQ93BvcX9sQCUtqhexMjsHASYLAkGGyYAzG7BBADUAJL72CYaAILjxF4OxwASeOMkAJ5X1yYA7BbH4yYjmQxzQDHGmFUCWIxyOxwAbmIvJhjr8LC83sRPgdTgBaLgXEAgRHeTC/AAi%2B3%2BFKpXy%2BGy2OzJBwuXzuDxOGKIWP2bkkZlZNzRAJqwNBAghUJhTC8RARSJRaP5NL21J%2BlNVdJugOBAH0mAolHUIFyPryzBpLYTiQrUXsNeTjvy5lSOAtaJwAKy8PzcXioThuazWAFLFaKsx7HikAiaN0LBCYJhYGIQBYAaxAnp%2BADoflxPRo9gA2LhcMwATj2nv0nEkPrjpADHF4ChAGhjcYWcFgMEQICWBASsvIlDQWzo0VCrDWqlixdxxckx2AyBBUhzZl4mHw3Lw6D0/EEIjE7CkMkEihU6g4WlIuj2pAA7sQmAlODx3V6G7f/ZwAPKysOJyoFQxxzguS4rmuxwbmYxwQB4E70DC5h7Hscy8LGv7dkgg7AaOEDjgkk7ENObCcBBi7Lqu66SJu267iQ%2B6HrIJ7iOeR7yEoaiNrozQvm%2BH5urWHDeqQvp3s2gFDrKxygeB87UdBdGbghSEkShqKRlwmGdjhpAQEgxGkYRJkoSAwBSGYfB0BsxBthAESNhEwS1O8wmkK5zBYv%2BETaBU2HRuObCCP%2BDC0B5v6kFgEReMAbhiLQbZ%2BjFmyGMA4jRfgxCBXg8KYCld6QhUsprNGRytI2tB4BEr5Yh4WCNgQxB4CwnkFcQETJJg5LpUYNVGF2fAGMACgAGp4JgT7/gkjCeVx7FntIXFXrx0UPvoGUoMGlj6LVbaQAsqAJO0KX%2Bp1rVYIdaYtG0aQuAw7ieI0/hPT0RQlNkySpAIIxNIkP3tB9fQxGMrR5QInTDC9ox3ZDHQTCDMxg4MXT/XogJ1MjX26YsyyrBIX5iT%2BUmcIpkE0TBcEIbghAkNpUZ6dhWi4SgqDIdEZkc5p/RWfytm0PZjnOdF3nuZ54u%2Bf5gWeSFjAEOFkWNrF8WJbQyWeVgLAZVld45XlBVFduqilRsnmVR60U1XV7mNWsd4tW1HXRN1Sh9TrA3BKABlUKNE1TTNc2%2BtGi2iBxK2yGtN53vxW1DaYljWPtEQ3cdp1pOdTaXfuhXwAs5SVM4ECuBjzSBFMn39M0OS/eksMA7XwOV6DmMQ0XiPow3bf3VDSMtyjmMTGXaPYwPuMF2GhN41b4mSX%2BHAU8ptGwfR8EQHT3KM7pWFdgmSYppQGYgFGOYVmYsRmGW85mJ6npcBWsSPlb9akO1ey5sWezzrEPyxBWD9JCSA0JIGs88mycFbO2fSrNDJ9iMgOICI4KBER5qRciaxagsHhD8XETBQQGCMLBCsOYuA5mKkxK6rFjzh2Whebi14%2BIgBsoJd8fpiZz0bNJJBIEwJYJwXgghGViGkPIepNBWk0JmGZsNBB5kuYoPkTEfhuDkCEKsgAjsNAhbRBFi5NyWJJYGPeH5AKDg5Yc1CorCKUV9aYDiglJKKVoza11g7XgBtKhG0bCVZAZULaCCqtbWq9V3j22aq1dqqVOpu16v1TK3thp%2ByYGNSa01ZrzVSmHU8EhI6Xh4jHHQzD47GF2jYG2acmwZwlJA7O0Qrp5yOvDDuj1nqZABhXQorca5AzSCPJuaQcbV2ae0aG9Ru7g17p3MeXTB5jGHhM0ekxZkT3xuGImolOHRWbMcFRgi1HCIfqIjQtNKHbxkThfeyZ%2Bi3Rfrwd%2BZCuCxA0MWT0xYNCemAWYH4FY/4SS4bUtsHYWYiR7P2fCyCxwSKnDOTgWCoIsAUPCEE8IjlMnGIxemVDmjZIjvQ6OTDpCsOEhw0mC8ZLAXknw4gLAEVIpRWioEhUTiIWhahSMkgLmwLkWy7mnMYjIoSAkXUqKKy6nRQQfUNKlyC2FpQUWd4pZRWjEq0xstUryzCjYlW9i1ZOK1vEvWHi8C5S8XnaKvj/GpUttVEJdsMDuJjJEl2XUeoe11ok32/s0lB0yaHNitDcn4oKYSkpO0k57QqfnKpZ1amoBztdaNhd2itJHp06YuNAa5D6YsgZ%2BRx7DOTVUBZ7Se4IzGUM1GWNxmlvmV0StGyFBTzPKS/52zybwuXIi5FCJGUbHGKcrF5zd6XNIIma5qZiavweaQ55rz3mfI0N8358RwHNigcCvepBMz8k3LESQFYv6xF/i8wszQrZ7DJRAlsMD4yiS3G2smN6QVzAWJ1FIzhJBAA)

Having a base case or not doesn't change compilers' recursive behavior during recursion.
The process of going from one step to the next doesn't involve a base case.

So why don't compilers get confused like I do?
What have I understood after this train of thought?
How can a being be produced by itself without existing in the first place?

## Metaphor

Two analogies are often used to demonstrate recursion: domino toppling and Russian dolls.

```C++
   ___
  /- -\
  \ - /
  /   \
 /     \
 \_____/ /* A Russian doll made of dominoes. */
```

But aren't they the opposite of recursion?
Each domino is established manually.
Each doll is made by hand figuratively.
What is there to recurse?
Isn't recursion more like a domino tile inscribed with four words: 'The World Shall Fall,' or a doll sealing a blood letter saying: 'There Shall be More'?

Then what is this recursive turmoil I feel whenever dominoes fall?
What is this recursive sensation in my heart whenever a doll splits in half, only to reveal another doll?
Recursion, hiding inside its own making, manifesting perfection through incompletion.
When will it stop smirking at a world confined by finitude, declaring the arrival of infinity, claiming its rightful throne of confusion?

## Declaration

Let us examine `History` again:

<table>
  <thead>
    <tr>
      <th>Line</th>
      <th>Part</th>
      <th>Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align: center">1</td>
      <td><code>template&lt;int&nbsp;I&gt;</code></td>
      <td>The template-head. Declaring parameter <code>I</code></td>
    </tr>
    <tr>
      <td style="text-align: center">2</td>
      <td><code>struct History</code></td>
      <td>Declare the template's name</td>
    </tr>
    <tr>
      <td style="text-align: center">3</td>
      <td><code>&#123</code></td>
      <td>Start of the template's body</td>
    </tr>
    <tr>
      <td style="text-align: center">4</td>
      <td><code>static constexpr int value</code></td>
      <td>Declare a member called <code>value</code></td>
    </tr>
    <tr>
      <td style="text-align: center">5</td>
      <td><code>{History&lt;I&gt;::value}</code></td>
      <td>Initialize <code>value</code></td>
    </tr>
    <tr>
    <tr>
      <td style="text-align: center">6</td>
      <td><code>&#125</code></td>
      <td>End of the template's body</td>
    </tr>
  </tbody>
</table>

My confusion comes from the fifth line: why won't compilers fail when they see `History` being used for its member without a complete definition?
To demonstrate this peculiar phenomenon, let us accidentally make a typo:

```C++
template<int I>
struct History
{ 
    static constexpr int value 
    {History<I-1>::/**/net_worth/**/}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAbKQADqgKhE4MHt6%2BASlpGQKh4VEssfFJdpgOmUIETMQE2T5%2BgVU1AnUNBMWRMXGJtvWNzbltwz1hfWUDCQCUtqhexMjsHASYLMkGGyb%2BbmEEANQAknvYJhoAggoExF4ORwASeLckAJ6XVyYA7FbXR0BR1uTEcyCOaAYt0wqmSxCOhyOADcxF5MEcvkCMX8Xm9iJ99icALRcc4gEAAegAVFSKRFMAQAOokAgIam034AET2Fgx1y5PI4C1onAArLw/NxeKhOG5rNZgUsVujzP4eKQCJohQsANYgUWSAB0GkkXB%2B/g0oo0ZgSCTMAA57fpOJJeCwJBoNKRJVpSDKOLwFCAvZqOFoFnBYDBECAlgRkl4CORKGgtnQ4hFWGtVPaEkSEpIjsBkOCpIazLxMPgiMQ8Og9PxBCIxOwpDJBIoVOowzo9AB3YhMZKcHjCsUSrV%2BzgAeUTCeOqCoRxzeYLRZLRzLZiOEA8afo8NVXDmvFD4dIECQqeS6bIFAg19vIGAUjMfDoG2IQYg0Un0TCDTvCOvD/sw%2BLTtE2jVKG6qpmwgjTgwtBAT2pBYNEXjAG4Yi0EGUpoZshjAOIqH4MQ0F4EimB4b6MLVImazqocmAiqhtB4NEg74h4WCTnceDuvhVHENEaSYJyhFGOxRhagsVAGMACgAGp4JgfbTskjDAe2wiiOIbaNvIShqJOuhcPoREoPKlj6BxQaQAsqDJI4Ah4dKwm1lg9kQAs7QuX4ECuKMfjmSEUylOUeipOk/nBVFBT%2Bb0EUDOZfm1BMcWpSxFGdBMSX9PEqUZZ4LR6CCjT5TMhW%2BUqqwSGOHDit6k7%2Bsuub5oWxalka24QLghAkBiZhqieGqyQsCCYEwWDxD5pB6pI/iGgAnP4PySCaZiSAknqigky3OhwrqkO6aqGgkXAJPay32pdBpcKKq1JD60qcIGwZjT2EbRpesZzomyYPqg%2B4ZlmnANCwSI/ESTAQgYRibsthpcMalbViQdYNrIzb6dIhmdiZqG6G%2BA5DsBDVNS9U4cLO8aJkci5HBDUMw3DRGI8jxo7nuN4HkN/hmKNZ5CheV7A7zcSA4%2BB4gMz0PIPDL7LVwXo0LQn7fr%2BqGgYB2k6%2BBkHQdpcGMAQiHIZO6GYdhtC4dpWAsERJG%2BmRFFUTRlaqPRGzacxrG%2BuxnGATxay%2BvxgnqsJolKBJjtSWEoBfXwCnKap6maZK6qGTjrZ47IBPdr6xMWTJpiWNYtnRN5jnOZkbl%2Bh5dbUfAvnZR0AVBSVuShQw6CVZF5nRYUWRdyF%2BQxZk/cpbYbf%2BV0Iyj2Vs/pd0U%2BFUM3SZRvFXhQV9WLMsdXHodlMtZwTPEJD0Owwr7NcEjKMaDu/U1vzx6nuNpCTdNAxzaxx2nSRiaH4j0fjmkkFtAs5kqb%2BneiGWSF4fpIDjPOKW4tbyZjYODS%2Ba4WAKCROCJE99DQ7GogQNGA1PJYybHpXOOkC6mTyKTYcUoKYTlQv6Wm84GZLghrg/BhDiGkNuNzdBfNVT%2BCFgg360tJb3lkfEAhyRkgAH0iHLRUcIggKi%2BF4w/HETWf4AL4j1sY94EEoIOGNsDeCZskIoRdpgDCWEcJ4XVA7J2odeCuxqO7ScdFkAMV9oIFik5A5cXeCHPitYI68CjmJWOTsE4IPkkwRSKk1IaS0vhbOtCJB5w7MZQuvZAiKysuXGygdq5%2Blrq5N6Dc4ieWbg5Ge9h/IuF7lvMKJQ96DwSpkLeQ9Eq7yqkvNpK8F45DHmlXKq8RkD23k0ReRU5k9NGcfBQtVWxsOahw8%2Buijh4IIciIRoIyHP3RoeYa79PrhgmlNGalAGoAJAGYJG/h/CiitKaT0HyfhXV2b6WBtgPrCzmLqEAkhRQrVFPaG0y1JDLXNGtLgpTOD%2BHYUC%2BpYKGoVkBa9AMtztSkGEukZwkggA%3D%3D)

It compiles even though `History` doesn't have a member called `net_worth`.
That's suspicious.
Let's go one step further.

```C++
template<int>
struct ELDorado;

template<int I>
struct History
{
    static constexpr int value 
    {/**/ELDorado<I-1>/**/::net_worth}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGE6a4AMngMmAByPgBGmMQgABykAA6oCoRODB7evv5JKWkCwaERLNGxCXaYDulCBEzEBJk%2BflK2mPaOAjV1BIXhUTHxtrX1jdktCsM9IX0lA3EAlLaoXsTI7BwEmCyJBpsmAMxuIQQH2CYaAIITxF4OANTYgQAiJEzoqAdWl%2BcXm9u7mAOR0EdwAkqcftdbgQ7gAJPATEgATx%2BJgA7F8LndsXcJkxHMg7mgGBNMKpEsQ7sc7gA3MReTB3H44pkYx4vYhvD6HUEAWi4pxAIAA9AAqUXC0IEAD6AHcSAQEGKJeinp8md80Wr9hYOItaJwAKy8PzcXioThuazWXHLVaM8z7HikAiaPWLADWIENkgAdBpJFw0fsNIaNGYAGwRsxxBIGjiSXgsCQaDSkU1aUgWji8BQgNOujhaRZwWAwRAgZYERJeAjkShobZ0GJhVjrVRxCO8iOSO7AZCEqS%2Bsy8TD4IjEPDoPT8QQiMTsFqz%2BRKNRu0i6LikWWcxKcHj6o0m9fZgDytZrMNQVDuHa7Pb7A7uQ7MdwgHib9Epjq4814heLUgICQRtEmbMgKAgUDwJAYApDMPg6E2Yg8wgSJ10iEI6iRfdeEw5hiCRU9Im0SpC2dRs2EEU8GFoHCi14LBIi8YA3DEWg8zNUgsBYQxgHEBjuLwYgyLwGlME4zMyUqWt1mdY42nXWg8EiTlCI8LB1wISdky48TiEiFJMCeLY%2BOUow3UWKgDGABQADU8EwWVT0SRhcJkOdRHEJdZEUFR1EEzd9D4lBrUsfQVLzSBFlQRIOhJThzX0ycsCiiBFgqKpnAgVxRmaUggmmYpSj0ZJUnivLSryeLemKgYt0y%2BKuhGTwmj0RrqkmWr%2BliBrJkqvrum62Zeoyu01gkQ8OGNdMT04W9O27Xt%2B0HP1XwgXBCBIJkzCdP8XUsxYEEwN4BnS0gvUkfZfQATn2NFJADMxJAjVNDQjG79E4RNSGTJ1fQjLgIziG64iBn0uENO6I1mwTs1zfMDoYkty2AysL1resoNQT8WzbTg6hYGk0V5JgiQMIxnxu30uH9UdxxIKcZ1kedvOkZc/LXQKQAQncmD3M0ppmjNzU4c9q1rO5rzuQnidJ8m%2BKpmn/TfD8wK/Hb9jMfaAL1ICQJx9WYix6CvxAWWSeQCm4Jurg0xoWhkNQ9DBPw7D3LdwjiNIhx3MoxgCBouj1yYli2NoDj3J4sz1kzfARKqcTJNHVQZM2dyFPjTNlNU7CNNj/8dPc/TDKUEzeKMczQGRvgbPsxznNc01nWXVnF3Z3zVwCzNdAQ63QssawIsiNKYri9JOKSmIUok%2BAMraUTsty1qxgKhh0GGkqtzK/IMhX/Kd5qoqevahesoYZqGn30/2k6obj5G9r%2Buvwb6k3%2BqxpWCbfy%2B6bjzh%2BaFt5ZW0VlwamtMNBvk2hOTWv5/yHVIMdU6sRzrxh%2Bn9amAY0RQzRMGSQz0exbhFlmRKthEa6xRvANGVZLwm0NuBVsbACbEBYA%2BFgCgaSEhpGA30AIJj0y2ilZmnkFw5A5l3dcuh9jbl3LhIW/9MxngxleG8hM2EcK4TwvhMJ3z0I1o6fYOtLL6xQHo42kFTYDE4YkRI0puE3WlNo6Uaj2ZIRiM7DCWFCIey8UREiZE/Y4yooHWi9E46YGYqxdinFnTR0rgXISCdHBJ3XNJZAskM6CEUoJHOakkT5y0kXPSMRS7GVMpXEI1dALWSYLZByTkXJuS4q3Ly7cPIrn8pIkA0j%2B6mEHuFHOo8szjwEJPLMyUpyz2iq0W%2BS914DTXhvB%2BW9cjlXSAsw%2B6R369RmYvC%2Bz8sj5Q6p0Lqyz6pDG6AsvEb8zmjSWF/Rc8jYaKMASw9RnDaRaPxBJHR0Dto/iMcjI6J0sAoKmugnm1N9j7ENGGQMqZoVomBs80WOYyEFgQZdQ0t1DRxEjDdSQN1gz3S4D0zg%2BwFGovgUC3%2BI4UUkLRRQxY%2BlUjOEkEAA%3D%3D)

It compiles again, and `ELDorado` isn't even real.

Finally, it becomes clear:
Compilers don't need a concrete definition to transcribe the `value` of `History`.
A dubious declaration is good enough for compilers to make `History` happen.

What is a declaration, then?

In math proofs, we often see sentences started like this:

> Let $x \in S$, ...

Here, we declare a variable called `x`, which has the property of belonging to the set `S`.
From this point forward, whenever `x` appears in the current context, we know `x` represents a generic member from `S`. If we see a phrase like `y = x + x`, we can verify the validity of such phrase by asking whether `S` supports operation `+`.

In C++, we use the following syntax to declare `x`:

```C++
S x; /* Declare x, which is from set S */

auto y = x + x; /* Compiler will help us check its validity */
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgGykrgAyeAyYAHI%2BAEaYxCCBAA6oCoRODB7evgGkyamOAqHhUSyx8YF2mA7pQgRMxASZPn5cFZj2BQy19QRFkTFxCbZ1DU3ZrcM9fSVlCQCUtqhexMjsHOYAzFg04QDUAIIA%2BgAqAJrK2LthBCYa%2B16pRrtCuyYbACIHJ%2BfYb1Z3t32L1Uf0BgKYXiIuwAnq8PrtVK9LAi/hwFrROABWXh%2Bbi8VCcNzWay7BRLFaYJEbHikAiaNELADWIExkgAdBpJFwAOwbDSYjRmfz%2BMwADlF%2Bk4kl4LAkGg0pFxWlIBI4vAUIAVdI4WgWcFgMEQICWBESkPIlDQLESdDiEVYa1Uov8AFp/JJdsBkMhdlI2WZeJh8ERiHh0Hp%2BIIRGJ2FIZIJFCp1DqdHoAO7EJiJTg8dFYnH0lWcADykLNBF2qCoCOdbo9Xp9frMuwgHmttuIVK4c142t1pAgSCtNvoZAoEGHHZAwCkZj4dAIcQ1EGiheiYXq0JzvHXzGI0OL0W0VW1NKtbEExYYtC3KdIWGiXmAbjEtA1ePvmBYhmA4jv%2BGIE88AAN0wd9lUwVQqkhNYaWudpC1oPBokzfcPCwQsCFDWUP1A4hohSTB3i/H8kKMekFioAxgAUAA1PBMDTYtEkYbd42EURxDjSN5CUNRC10Lh9B/FBiUsfRkI1SAFlQRJOnffE8NDLApIgBZKmqZwIFcMYWiCBh0GmAZ4iEvI0gEXS9DMzojNKQYhI0zpulGTxmj0RyahGXown6OyTMmFysj0hQvNs2Zu0WZZVgkPMOGxRVC1VGtXXdT1vV9dlmwgXBCBILse1pCiFgQTAmCweI1NIZlJA2NkAE4Nm5SROTMSR/HlTF/DqyUOGlUhZWpNl/FaUU6tFVpWS4TEGsCJV8U4dVNUKlM9UNQdjTLc1x0nUd7TYTh6hYYDuRdJhdmQAwni4Oq2S4DlA2DEgwwjWRoy46QeMTfi710OcMyzbdYviuaiw4UtTUhStq0O47TvOy7gF9G67o0Fs2xHOIqTMAq%2BzRAch1QdtRwtCdCYx%2BIYZOi6f2urgFRoWhF2IZdVzvXdNzY9n90PY8HDY89GAIK8b0LB8nxfWg3zYrBvyMP9lQAoDQPAwMoOQGC2PgjE7yQlDN3QtZlSwvAcJpPCCKUYjZd/MJQBWvhqLohimJY3EaR4t7Yw%2B2QvuTZVfuE8jTEsawJOiVSZLk9IFJVJSwzA%2BB1PaICtJ01zxn0wyfJmezchScyMnTvTrPSMLc48gRnMaIv3OTzSulC7PjPcrzLIcxvimbiKySi2MgYLO8kspuHqau5GORbHKQ3y3sitIEqysGSrtb6gabs5blpu5XlJFa90hJB1VFq1CiBzWpATXLEmdrtB0DuIFhUpYBRgJ9YDrrZAxFxCh7cuUl6oycS9uxX2AkQAbFIP9bMeJ%2B4JUHiWTaFYqy7EOk/F%2Bb8P5fzAhWVsZMOxUg2DjU%2B60b5jktHg0cIBX6JESIcd%2BdVDhYJCocVBH0FxLkoKzZUXNbw0h4TzE8/NCYXiFteW8CtMCPmfK%2Bd8NIZakUNrwRW1RlaFkgtBRcmtBAIR1shVC0IDaYWwmxc2hErakVtqfKiTAaL0UYsxViH4PZAIkN7BMfE/apggQjUSIdxK6wjiqKOAgY6oDjipROtg66dBcAZNumcy7%2BRLhZGupl842Sbn5WuHRPI9HiRXBuUxMnhQCtXIKLcimdyyd3ck0UIra2BolTgKCH5oNfrsehn8mDfxwVPPKmxuyzxWsVUq5VKCxVXiAMwN0NgbExAKLk8pZncn8BKQ%2BC1bBLVxnMJkIBJCYnqpiUUQo6qSDqryRqXBvGcA2APZUR9lq6ligGOB9yNnbIWHhVIzhJBAA)

If `S` doesn't support `+`, an error will occur during compile time:

```C++
using S = int*;

S x;

auto y = x + x;
```

Error from MSVC:

```C++
error C2110: '+': cannot add two pointers
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxHoADqgKhE4MHt6%2BcQlJAkEh4SxRMVy2mPaOAkIETMQEqT5%2BRXaYDskVVQQ5YZHRegqV1bXpDX3twZ353VwAlLaoXsTI7BxeiUYA1EKrJgDMACKrwQQAVNtWGgCCJucbqieXF%2BdMXkSrAJ6bu6uqm5afJxzTtE4AFZeH5uLxUJw3NZrKsFLN5phvlseKQCJp/tMANYgIGSAB0GkkXAA7FsNECNGYAGzUswADnp%2Bk4kl4LAkGg0pDBWlIkI4vAUIC56I4WmmcFgMEQIFmBFiT3IlDQLFidGioVYi1U9OpAFpqZJVsBkMhVlJ8WZeJh8ERiHh0Hp%2BIIRGJ2FIZIJFCp1GKdHoAO7EJixTg8AHA0EYvmcADyTwVBFWqCon11BqNJrNFrMqwgHlV6uIyKmvFF4tIECQKrV9DIFAgNaLIGAUjMfDoBGiQogEWjEWCVReYd4A%2BYxBesYi2iaotRKrYgljDFow79pCwES8wDcYloQvBG8wLEMwHE6/wxFneAAbpgD7zMKomk9FqiDiVo7Q8BFgxOPFg0YEPa7KHnexARAkmA7Mep7fkYGLTFQBjAAoABqeCYAGsaxIwI6esIojiB6zryEoajRroRQGAhpiWNY%2Bg/kKkDTKgsRlAwB4QuB9pYMxEDTI0zTOBArgDPUpCBKMeQFBkiQceJclZAwHQyRMxSlC0wyKQ0JTXuUwyqV0hS2Npnh1D0hnScZEiCQiCy2cyHAgty0b8mm%2BqGsaprmgSuYQLghAkCWkxloh0wIJgTBYDEAmkDikhbPiACcWwkpIRJmJI1KckC1LJU5rKkOyKL4tSXDUvSyX0hVeJcECqXUq5678oKwpoohlbSlWsoJoqDZNnWmpsJwVQsDeJJ6kwqzIDRwDmsl%2BJcIS1q2iQDpOrIrrEdIpHehR666O2QYhiOEbOVGLVxn1SYpqsY0TVNM1zQtS2EnmBa1tEyJmKFHV%2BhK1aoIWdZKo2wNfTED2TbNp5cMlXBcjQtBdsQPZ9uuY5DvhWMTlOM4OPhC6MAQy6rtGm7brutD7vhWAnkY568pe153g%2B1rPsgr74R%2BgLrt%2Bv5DgBiy8sBeCgai4GQUoMEM2ewSgADfAoehmHYbhYKoqR23urtsj7b6vJHfop4oDCliMRE/GsexyRcXyPEOve8CCXpwl%2BKJDDuOZgySV7RnjCZ8TyckOmkMHykB7JumaQZbRh0JHGtNUUfqb08c%2BxJ6cp9ZgeOfCcwOVMTkuTyEKcPdxDjZN02w2s8NvRoeaBXaIVhQDEVRTFlDnUVJWLUSJINSSZKSFlhpFGXMYCrY7Xlv8XXwD1cqJmDg0alqo1V15LAKDeZo3g3Bhdr0q1Bbxm0ukRusEQblEgFspAnaG4LnaXbnXfKTzJqmY073vB8j5MBPkmfMEMizIi2H9eegMUDgNBgNeB3R96xFiAAfUPslNBx97wEDQX/XanZuyUAxryXGa5UTkPxrOImwNFykxXGuZmmAtw7j3AeVE9M4Ii14CzZobNoxPhfF2HmghPz8x/H%2BF4wsgIgXwlLKCss4IK06shJgqEMJYRwnhQ82tr4SD1l6ciht/SPzmmbeiFsBbWz5LbAQ9tUCOz4i7DS%2BkPZiUzv4f2udo7h0yApTxRQI4cVTiZROWkM5pCzm7JOVlcg2SGJEiyiSc7xLzsXAuiJHJ83fldDglcWD/33qsTB%2BIcG9GbmtYs5gUTQPCqQSK0VuhxT5n3EAZhFpbC2ECSkxJORdJJJVZqvJWqzxFPUhKQIUpAnpDSZKkhkpkjSlwMxnAtiXRGZwdu4pzpWmGeXGeMDpjgUSM4SQQA%3D)

The idea of declaration is intuitive.
We need to name something first before referring to it by the name.
We call this naming process 'declaration.'
However, in C++, no simplicity is left untainted by the darkness of complication.
Declarations in C++ are so complex that not only do they get their own chapter in the standard, but that chapter is also horrifyingly long.

There are some justifications for this monstrosity:

First, the complexity of declarations is the product of a highly saturated language.
Every time a new entity or specifier is introduced to C++, a new declaration syntax or rule must be created to match the change.
Under the hood, declarations are still intuitive.

Second, interestingly, definitions in C++ form a subset of declarations.
It is probably a good thing to step away from the word 'definition' since:

> Is a definition truly defined if it results in an undefined behavior? <p style='text-align: right;'> &mdash; <i>Man In Shower</i></p>

Let us review `History` again:

<table>
  <thead>
    <tr>
      <th>Line</th>
      <th>Part</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align: center">1</td>
      <td><code>template&lt;int&nbsp;I&gt;</code></td>
    </tr>
  </tbody>
</table>

`I` is declared right after its name is completed, meaning we can refer to `I`  even inside the template head:

```C++
// By the way,
// 'decltype' stands for 'declared type.'
template<int I, typename Type = decltype(I)>
struct History;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgGykrgAyeAyYAHI%2BAEaYxCBmpAAOqAqETgwe3r4ByanpAqHhUSyx8Yl2mA4ZQgRMxARZPn5cgZXVArX1BEWRMXEJtnUNTTmtQ929JWUJAJS2qF7EyOwcBJgsSQbrJgDMbmEEANQAkqRHBACeSYysmEcAKtf3ewAiR1jItFc3ECeze2wJg0AEEFARiF4HEcABJ4cEkS57Cwcea0TgAVl4fm4vFQnDc1msRwUi2WLzMux4pAImlR8wA1iAMZIAHQaSRcADsuw0GI0Zn8/jMAA4RfpOJJeCwJBoNKQcVpSPiOLwFCB5bSOFp5nBYDBECBFgQkl4CORKGhNnQ4hE7pxVCL/ABafySI7AZDII5SVlmXiYfBEYh4dB6fiCERidhSGSCRQqdTanR6ADuxCYSU4PDRmOxdOVnAA8mbTcdUFQjo6XW6PV6fWyzEcIB5rfRiEdzFTZrwtTrSBAkFakjayBQIMPRyBgFJEjRvnF1RBogXomF6pds7w18xiJci9FtFUtdSrWxBEWGLRN8nSFhol5gG4xLR1bi7xtDMBxLf8MRj3gABumBvkqmCqFUZqrNShyYOit60Hg0QZnuHhYAWEJ4DK77AcQ0SpJgryfkYiFGHS8xUAYwAKAAangmCpkWNw4tSEbCKI4ixmxCZqAWuhcPoX4oESlj6Eh6qQPMqBJI4AhvniuEhlgEkQPM7SyX4ECuKMLRBAw6BTP08QCSkaQaTpeimQUDCGaUAwCepNTDI0njNHojmdM5tkzA5zkWb5kxhH0dnGWpZIrBIuYcFiCoFiqVZOq67qet6vpNhAuCECQnaUlwPY0uR8wIJgTBYPEqmkEyki7KyACcuxcpIHJmJI/hyhi/i1RKHBSqQMpUqy/itCKtUiq0LJcBi9WBIqeKcGqGoFcmuoGoORqlmaFoTqgba2vaHD1CwgFcs6TBHF8X4%2BrVrJcOyAZBiQobhrIUacdI3FKLxt66Ik6aZluUUxbNhYcCWJpmkcFZHIdx2nedBhGFdN3ss2rYju2OW7GY%2BV9qiA5Djt6NxFtk7tiAMMnRdRhcLVXDyvO6zEEuK63juG5bqQbN7geR4OBzZ6MAQl7XgW96Ps%2BtCvhzWAsF%2BP5Kn%2BAHAaBAYQcgUEc7B8FKohyEbmhqxKph2HUrh%2BFKERsskWEoDLXwVG0fRjHMRzbGvTG72yDxSZKj9glkaYljWGJ0QqVJMkZPJyqKaGIHwGpcEAc4Wn6f5ekGUF0z2XkZkZGnVkad52ceQwXQjK5Yy2InHSl15mdGe5fkV7p4KBcUDd5QsSwRZ38FA3FnDQ8QR0nWdVPAEjt0aM2mXBpjeW9oVpDFaVAwVfBvX9ddHJclNXI8pILVugJwMqgtmrkQOq1IMaZYk4To52mwnCHbWLAKIB3qATTrLbCBBD3SykpZ6kYOIezjPIT6PsUy7FIH9LMuJAb5lvCqMGZZIaVlfu6d%2Bn8jjf2un/cEqMH4Yy7LsHGl81qk2JuOah8RP5JCSAAfXwUwwhBAmFYL4HQRmzNVzrj3BzLm%2B5DzHn5jtc8Qsrw3gVpgB8T4XxvmpDLOWhteCK2qMrAs4FILrE1oIOCBZdYoUuAbDCIYTa8DNgRS2csbaX0okwaidEGJMUYK7F6YCJCe3jFAviIBYEI2MCJGwusw7KgjnJea0c4hKTjpJKu9gNIuFTs3PQIR64hUsvkcyaSTI5IyEXYyiSk6126GnEuZceiZJ8hMcu2QW513blkzupJu4xiQbFFBg8sFHBwV/H%2B7CZ4PQ7F2BeS0dRFRKmVSgUVN4JGursXYGJ%2BScjlEsrk/hxSn2ieqC%2By1GQgEkBiOqGIRSClqpIWqPIGpcECZwXYyClRnwmfSbq/ounPOibjWY8xcJpGcJIIAA%3D%3D%3D)

As a comparison, using `I` before its declaration will cause an error:

```C++
template<typename Type = decltype(I), int I = 0>
struct History;
```

Error from GCC:

```C++
error: 'I' was not declared in this scope
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMR6AA6oCoRODB7evv5ByamOAmER0SxxCVy2mPYFDEIETMQEmT5%2BgZXV6XUNBEVRsfF6CvWNzdltQ929JWUSAJS2qF7EyOwcBJgsiQbrJgDMbgQAnomMrJgA1AAqxxd7ACLnWMi0RycQAJLz5%2BEE5%2B/n93OGj22BMGgAgkNiF4HOcABJ4IYkQ57Cwcea0TgAVl4fm4vFQnDc1ms5wUi2WtzMux4pAImnR8wA1iAsZIAHQaSRcAK7DRYjRmABsQrMAA4xfpOJJeCwJBoNKQ8VpSISOLwFCBFfSOFp5nBYDBECBFgREl4CORKGhNnR4pEzpxVGKhQBaIWSc7AZDIc5SdlmXiYfBEYh4dB6fiCERidhSGSCRQqdS6nR6ADuxCYiU4PAx2NxDNVnAA8hbzb9UFRzs63R6vT6/RyzOcIB5bfRiADqVxZrwdXrSBAkDbEnayBQIKPxyBgFIzHw6OtiJqIDEizFwg1DrneJvmMRDiWYtpMA5d6QbWxBCWGLQd6nSFgYl5gG4xLRNfinxtDMBxI%2B%2BDEGejgAG6YF%2BKqYKoZ4WqstI/FURa0HgMRZoeHhYEWBBhnK37gcQMQpJgdy/kYKFGAy8xUAYwAKAAangmDpiWJx4rSUbCKI4jxpxSZqEWugVAYlGmJY1j6KhmqQPMqCJDUX4EgRYZYNJEDzHYIHpC4DDuJ4LR6KE4R9KUAwVHkaQCKMfjmSklkMFM/TlO0WkCF0Iz6dkFSaQ4nTDD0xnTGZtj%2BdZgz%2BY5pnlBpFIrHMUocDiSpFmqNYuu6nrer6/othAuCECQ3Y0n2dJUfMCCYEwWAJOppAspIuzsgAnLsASSFyZiSEKCpYkKTUJTKpByjS7JClwQpik1YrjWyXBYi1QrJY%2BaoalqpWpvqRrDia5YWlaU6oB29qOhwDQsKBASukw5zPH%2BfpNeyXCckGIYkOGkayDGPHSHxSgCY%2BugLpm2a7vmiWFstpa7ZW1ZnRdV03SJwD3Y9nKtu2Y6dkVZglQO6JDiOh2Y/E%2B3Tp2IBw5dt1GFwTVcIqNAvPEq7ro%2B%2B7bhe7OHsep7nt%2BV6MAQt73kWz6vu%2BtCfheWAsH%2BAEqkBWngZBQYwcgcEXohmKPihaHbphqwqjheB4bSBFEUopGy%2BR4SgBtfC0QxTEsWxF6cV9cY/bI/EpiqgP6H%2BKAkpYkkxGpsnyekimqsp4YQfAGlVK5fgQK4YUVEZxROUkdk1OnpAWTUkUzN5Se%2BW5oWeTZLnl7UEWBdn3mV1k1cTI0xdmTFSxxb2CVJcqBKcOclMI9TyO06jGitvloZFb2/ZlaQFVVQMtXa4Nw0PVyATzQEvKSJ1HoVAPxbqrYa145t8DbaaFak0T44OmwnBnfWLAKKBvqgRP2wQQQL0FRUh9aM3FPYJnkH9X2aZdikGBjmfEYN%2B4pShmaC05wqzD2ICwN%2BH8v4/yYOsIY6MH5Y3MLsXYuMqIExQCQkmk4yYDE/okRIAB9b%2BTUWG/yGCw1%2BP0lzM0oKzFUXMHy0hETzECF4BY3jvA%2BBWmAXxvg/F%2BWkMs5aG14IrXyysizQVgusTWggkI61QuhQ4BtsK4QvObYiVs5a2yoTRJgdFGLMVYowN2n1QESC9omSBgkQAwKRkHcSIddbh1VJHAQ0dUCx1UgnGuNQdJ6RboZXSHdnKF3SPnLJhQG5RUGGXGo7kmhV0KR0Cukx8klxCt0fObcApZwKb3ck3c4yIIhiqVKvDzjv0/ucdh7IuG/Dyq9LsZD57rT1OVSq1VKBgw3iAMwD1yFYgFNyBU5CAgTSWl0zgq1tSL3qliZqWIxTCiapIJqvJWpcCCZwXYnTB5n0vmDQMuznkLw2vMAiqRnCSCAA%3D%3D%3D)

Next, we introduce the name of our template:

<table>
  <thead>
    <tr>
      <th>Line</th>
      <th>Part</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align: center">2</td>
      <td><code>struct History</code></td>
    </tr>
  </tbody>
</table>

`History` is declared once its name is completed, meaning we can refer to it in the fifth line:

<table>
  <thead>
    <tr>
      <th>Line</th>
      <th>Part</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align: center">3</td>
      <td><code>&#123</code></td>
    </tr>
    <tr>
      <td style="text-align: center">4</td>
      <td><code>static constexpr int value</code></td>
    </tr>
    <tr>
      <td style="text-align: center">5</td>
      <td><code>{History&lt;I&gt;::value}</code></td>
    </tr>
    <tr>
    <tr>
      <td style="text-align: center">6</td>
      <td><code>&#125</code></td>
    </tr>
  </tbody>
</table>

Now, let us address the elephant in the room.
How does recursion in regular functions work?

```C++
int fun (int i)
{
    if (i == 42)
    { return 42; }

    return fun (i - 1); 
}
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM6SuADJ4DJgAcj4ARpjEIACcpAAOqAqETgwe3r7%2ByanpAiFhkSwxcYl2mA4ZQgRMxARZPn4BldUCtfUERRHRsQm2dQ1NOa1D3aG9pf3xAJS2qF7EyOwcoQQA1FReDBsQ6xt4syYaAIImAOxWZxu3h1R7eBsmAMwAIq9vG5Jmxzd3lwsz3%2BdzuxEwBCWux%2BryBJ1OoMuHzO8NB4MhxF2212%2Bw2AFoNlxji84SiLm8OPNaJwAKy8PzcXioThuazWDYKRbLTDPMwvHikAiaSnzADWIBpkgAdBpJFwLi8NDSNGYAGyqswADk1%2Bk4kl4LAkGg0pAZWlIzI4vAUIBNQo4WnmcFgMEQIEWBCSXgI5EoaBYSTosXCrFWqk1qrxqskG2AyGQhOlZl4mHwRGIeHQen4ghEYnYUhkgkUKnUDp0egA7sQmElODwqbT6cKLZwAPLer2bVAPcOR6Ox%2BOJqVmPYeANB4i8/mzXj2x2kCBIf2B%2BhkCgQFeTkDAKQBGi0AixG0QKItqKheoAT3rvAvzGIV7bUW0VXtAv9bEEbYYtBv5dILAoi8YA3DEWgbUZQDMBYQxgHEAD8HBaoADdMEg81MFUKpvVWAV1kwakANoPAohrR8PCwFsCAzQ0oLQ4golSTA3hguCSKMYV5ioAxgAUAA1PBMErNskkYW8i2EURxELHN5CUNQW10Lh9DglA2UsfRSJtSB5lQJJHAESCmQYjMsB0iB5jaQy/AgVwRj8FTgkmEoyj0FI0hshz3PyGyelc/oVOsmpxm8oLCLfEKun8vo4iC0LPGaPQFHGGLpjiqyuRWCRGw4OlTRbS0Nj7KMYzjBMpBHPZcEIEhpyJOcuPmBBMCYLA4ks0hxUkF4pXiF4LkkWUzEkVVjRpVVEiI/VSENfkpVVLhVU1eJNSWyUuBpfrVQKgDLWtW1BS4xdXSXd1O29X1N1QCc1xDNhOHqFgUIuPEmA2ZADCMQl4ilLgZRTNMSEzbNZDzGTpDkktFIA3QAmrWtb1y/KzSZdsLu7B4npet6Pq%2B4Afr%2BmUxxu1dYmnX5GvLJ1l1Jycrq3NcQGx17Prgrh4i4E0DyPYgTzPAD72vCShcfZ9XwcCTP0YAgfz/FsgJAsDaAgiSsFgowEPNJDIrQjCU2w5BcIkgiiPNEiyOvSjVnNGi8DogUGKYpRWI1%2BDQlAam%2BF4gShJEsSGQFOTwYLSHZGhstzTh1TONMSxrC0qILL0gyMmMi1TMzdD4CsiL2ls%2BzEpyJyGHQNK3JUjyCkyIvHLyTyMnLwLbDzmzOmGWvktbqKGibuLBi6MKB97lzYpyhYlmyoldTy5s9s4DYWdxtnvo5omNGqoGp3MGcqcdZrWvayhcpmubftlC4touBUflGuVdvNfbbEO%2BdKRO%2BAzo9LsGbpu7Q0e4gLABwsAUChBMKE14GCPClQGtUzKg1zNJUOkkI5KRAC8UgCM6yMmRnPR%2B6NPTeg2D2RegDgGgPAZApg0DNgQHHGTbefIXiziOl7M6jNYg/1uv0MBSQkgAH0IHxH4VA9CBB%2BFPWjHwOgvN%2BbnkvI%2BEWCinwvjfFLG6X5Za/n/NrTAwFQLgUggKdW7Eba8B1qhbOAEsI4SPCbQQhEWwW3Ilea21FaISSdsxV27EPbHR4kwPiglhKiXElBYOSCJBh2LApSOFYMH43UvHTSFtk4WlTkZTgJlYhmWzrpFu9gbIuFLkPZyxQx6V18hkIeVc/Kj3Sl3QpPdGid3Ck0joqV6kV2Hi07IdcUrRS6YFTKk8Cy4IfmjDgpCgExhAWAjYQipSiJSpvOB9UWGv1mAfNq/ROrTQNP4X6LwXg0mVHKY0xyLjLQma2K0z87RNS6iASQNI%2Bo0k1GqeIkh4gKgGlwBJnAXh4MmXvEUM9kw3Kfps%2BYDE0jOEkEAA%3D)

Based on the discussions above, we expect the following code compiles:

```C++
int bun(int i);

int fun (int i)
{ return bun(i); }
```

And it does! [*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxCDSAA6oCoRODB7evnrJqY4CoeFRLLHxXLaY9vkMQgRMxASZPn5cgXaYDum19QSFkTFxCbZ1DU3Z5QojvWH9JYNcAJS2qF7EyOwcYQQA1NFeDBBb23gLJgDMVhoAgibXR1T724eCx6fXJgDsFtvEmASrDF2%2B0Opwu20%2BABEOEtaJwAKy8PzcXioThuazWbYKFZrTDgsxnHikAiaaFLADWIDhkgAdBpJFwPmcNHCNGYAGzsswADm5%2Bk4kl4LAkGg0pCRWlIqI4vAUIDFJI4WiWcFgMEQIBWBESXgI5EoaBYiTocQirA2qm57IAtOzJNtgMhkNspDSzLxMPgiMQ8Og9PxBCIxOwpDJBIoVOolTo9AB3YhMRKcHgw%2BGI0lSzgAeV1Op2qCo20tNrtDqdLtpZieHiNJuI%2BMJC14iuVpAgSENxvoZAoEE7dZAwCkZj4dAIcTlEGiGeiYXqAE9k7xZ8xiPOs9FtB1FUTDWxBFmGLRF9HSFg9sA3GJaHLkWfMCxDMBxKf8L9OgA3TC3yWYVQdXUNiJLZKgzWg8GiBM1w8LAMwIH1hTvL9iGiFJMAhB8n3AoxSSWKgDGABQADU8EwWMs0SRglzDYRRHEUMA3kJQ1AzXRygMHDTEsax9AguVICWVBEmqW8UWQn0sH4iAlnaTpnAgVwxhaIIGHQPpilKHIUjSAQlK0vJ0nUgYygqKouimPSJkqbdzJ6Iy5hMyYeks4Y7JmDT5hknF1gkVMOARcUM2lIsrVte1HWdV0qwgXBCBIBtFmbXClgQTAmCweJpNISlJDOGl/DOD5JHpMxJHZUU4XZQJYQ4QVSGFQkaXZLh2W5fxuRa6kuDhAr2UC09pVleViVwtt1XbTVc11fU%2B1QWtuzNNhOHqFgPw%2Ba0mG2ZAOOAF1/BpLg6Q9L0SF9f1ZCDejpEYiMWNPXQR3jRMlz8gKJRRbMpvzQsVrWjatp2vaDrpas5q7OIGzMJsRujFUOzBusZv7bsQF%2B9btqfVouDFGhaHHYhJ2nU8VwXaiSbXDctwcai90YAhD2PDNzy8S9r1vIksEfIwX0lN8bK/H8PX/ZBAOokCaslcDIIXGCNkleC8EQolkNQpQMK558wlAWG%2BAI4jSPIyikSJRjLpDa7ZFuqNJQe/QnxQDFLF46IpME4T0lEqVxN9b94Bk6y5L8BTVJckJ3OM/SdIyTxmkj6p7M0qyzIEbpRhj8ZTJslOpgT%2BZXLTrJlKchpc7KLzVh8xZ%2BX89MBs4bY0f%2BjGjCBw6NCeWLvQS6GWzJUhUvSwYspquqGv2%2BkPh6j4mUkUq7XKd7MxlWxht7lVxqQLU8yRhGFvNZbiBYUsWAUD9nQ/VoaQMcdJmOuKJPOwM6PNmirdYkAzlIJ6k2RV7a8laUOZtS6m2AWBuh9j6n3Ppfa%2B34dgQBrODes5gzhnB7qNCayM4g73moMM%2BiREgAH0L7%2BEIbAyYhCVp2lHHjCclAiaSnJieIkTDKbbhpnNfc9Mjwnl5pgC8V5aA3mopzLCcteB80/L7U8f4ALjjFoIUCp4pZQXnLLOCCFqIqzQurLCWtRr4SYIREiZEKJUTvKbZ%2BEgLbhmYtbGMn8doO24k7KWrspTuwEJ7VA3tJJ%2B0zoHFwId07KTDkUCO5RchRxclE%2BO4cHJ6FktUVOjQQmJIDsknO8TE751SYXRJWTwkJKrtiCuIY/79QAfXKh9oT5n22CQq%2BTAb7wM7vFFBiUYbKhSmlDKlA/KjxAGYfaqC4SsgZKKVBHxWqVI%2BsvOUCpkrZQSHCfKcJuQcn8JIfwTJCpcEcZwM4/85lJVhn5d0syl6nO6aQZCqRnCSCAA%3D%3D)

A function is declared once we specify its name and type.
The following code won't compile since `gun` is not declared until the trailing return is completed.

```C++
auto gun () -> decltype(gun)*;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxHoADqgKhE4MHt6%2BcQlJAkEh4SxRMVy2mPaOAkIETMQEqT5%2BRXaYDskVVQQ5YZHRegqV1bXpDX3twZ353VwAlLaoXsTI7BxMXkQA1MBeDKsQk6sAtCYAzNirWMi0BACesZjQm5MAVEcWHNO0nACsvH7cvKicbms1lWClm80wq3Mhx4pAImle0wA1iAPpIAHQaSRcADshw0Hw0ZgAbESzAAOMn6TiSXgsCQaDSkH5aUj/Di8BQgRlwjhaaZwWAwRAgWYEWIrciUNAsWJ0aKhViLVRkol7ImSdbIZCrKRosy8TD4IjEPDoPT8QQiMTsKQyQSKFTqXk6PQAd2ITFinB4b0%2B33hrM4AHkVuKCKtUFRVsrVerNdrdWZth4ZXLiJCzNDJrweXzSBAkNLZfQyBQIEW0yBgFIzHw6ARopyIBEAxFglVLt7eG3mMRLkGItomjyYdK2IIgwxaJ3naQsBEvMA3GJaJzfnPMCxDMBxLP8MRh3gAG6YNcszCqJorRYw4IN96z2h4CIevseLABggmunrk/ECIJJgAAim7bk%2BRjwtMVAGMACgAGp4JgrpBjcPwwhawiiOItoYQ6agBroRQGBBpiWNY%2BjPpykDTKgsRlAwa5/H%2BJpYFROzFKUyQuAw7ieHU/g8R0eQFBkiT0QM9SkPEYnJEJXSFBxh7lMMEk9CUSkMK01RyeMCm9G0qlDG0OkiVMMxzAsEi%2BhwXxMgGbLRiqaoasAWo6uiSYQLghAkBmWY5pB0wIJgTBYDE7HIpIhxogAnIc2KSJiZiSESDIfESMVUhwNKkHS0JokSXBEmSMVkkVqJcB8cVEnZs5shyXKwpB%2BZCgWIqhhKZYViWCpsJwVQsEe2J7EwqznNuOoxWiXAYgaRokKa5qyFa2HSLhSj4bOui1u6npdtZtnMn8wYdeGkarANQ0jWNxHAJN00YsmqCpiWflmNmTXOvyhbPcW0SSuWv2Vpdw3jUYXAxVwjI0BcjaUC2s49h2XakEjfYDkODgo2OjAEJO04BvOi7LrQq4o1gW5GLuLL7oeJ5ngal7INeKN3iUAZPi%2BHbvosLJfngP4wn%2BAFKCBlM7sEoBfXwMHwYhyGoSjGErTaa2yHhTostt%2BjbigQKWBRERsTRdHJIxrLMaap7wNMjTNM4ECuIZpCBKMwkTFJmTiXxgyezJ2Ru/JamccpBk%2B5Jdv0VpIy5EHRn9OHPTDCZEy22CllmQ%2Bh32ZwF3EINw2jWDd0Qw9GjbN5xp%2BVMAVfUFIVhZQ1k5XlU2YtiVXYrikjJeqRRHYG7K2I1uavC18BtaKYYA918qKv1%2BdxiwChHtqR6lwYDa9HNPksUtlpYardryBtmsuocpC7V6vwHf6dUnWKKwRlGA1Lyva8b0wW/hhAKZ/emUJDgfVHt9FAQMSwz3Ad0VesRYgAH114xTgZvU8BA4GvzWvWOGzZWztj7CjNG/ZBzDmxs9cceMpwzhppgBcS4VxrhhBTMCvNeC02aPTAMF4rwNlZoIdmj5nyvkuDzT834UbC0AmLMCktmrQSYLBBCSEUKMCVstQ%2BEg1b2lPgREAF9bp6zIgbTmxtWSmwEGuAA9L0M0pErCWDMCyVAltWI20UvbPwjseLO1drHXSoksgpETkUaSASU56XUu46OztI4tGToHPx8cahBNsHE3xpk04WRtLfWqjjc4YNWMvVeqxEFohQb0Cu80AGZhrp9Pk9dQrdHYg%2BFuIAzBTUOIcD4BIsQMg6diYqOTjpD05NyQKpBIofFih8MkxIYqSBirieKXA9GcEOHfXJQ8QHWX1IMwetc6mkD/IkZwkggA%3D)

Error from Clang:

```C++
error: use of undeclared identifier 'gun'
```

As a comparison, the following code will compile:

```C++
int bun(int i);

auto gun () -> decltype(bun)*;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwAcpK4AMngMmAByPgBGmMT%2BpAAOqAqETgwe3r7%2BQSlpjgJhEdEscQlmtpj2hQxCBEzEBFk%2BfoFVNRn1jQTFUbHxiQoNTS057cM9faXl/gCUtqhexMjsHOEEANQxXgwQcyYAzFYaAIJMXkSbwLub%2B5sAtEfYm1jItAQAnkmYEDsMcwAVEcLBwFrROABWXh%2Bbi8VCcNzWaybBRLFaYTbmQ48UgETRghYAaxAkMkADoNJIuAB2Q4aSEaMwANmZgSCEI4kl4LAkGg0pFhWlICI4vAUIAF%2BI4WgWcFgMEQICWBCSl3IlDQLCSdHikVYa1UAWZD2ZkmuyGQmyk5LMvEw%2BCIxDw6D0/EEIjE7CkMkEihU6hlOj0AHdiEwkpweOCoTCCSLOAB5S5qraoKibI0ms0Wq02sx3Dza3XELFmHFzXjS2WkCBILU6%2BhkCgQBslkDAKSVGgfeISv7xmLhRqfKO8IfMYifRMxbSYBxj0hatiCRMMWijoOkLA7YBuMS0CVw7eYFiGYDiLf4YjzxwAN0wR%2BFmFU88ua1xG2q8doeBi4anDwsHjAhnV5Y8H2IGJUkwAARU9z1/IwCQWKgDGABQADU8EwENEx%2BWFcXdYRRHEH1iP9NR410Lh9HPFBkUsfQ/wlSAFlQJJaiPeFIOdLBWP2DpbwyFwGHcTxWj0UJwn6MpBlo/J0gEMY/AU1IlIYaYBgSWi7GEgRulGCScl06p9LqEZehkmZ5NsSyVL0SYmi0uSdIWNFllWCQYw4aFBXjUVM2NU1zWAS1rQpAsIFwQgSDLCsqxQhYEEwJgsASQSSUkQ5yQATkOGlJCpMxJGZflIWZXL9E4blSF5HFyWZLhmQCXKAmaskuEhfLmX8rdRXFSU8RQ2tFTrZUU3VFs2ybfU2E4RoWDvGkHiYTZ3nPa1cvJLhKXtR0SBdN1ZE9MjpAopQqK3XRKjDCMxx8vyhXhJNJrTDNFuW1b1oMIwtp2ylC1QYsm3isxK2GoM5XrYHG3iDVW1h9tPpWjajC4XKuAFHsCD7SgYkHYcp0XCcRxnOcF2PZdGAINcN3jHcvD3A8j1xLAzyMS9hWvYSHyfe1X2Qd9Fy/TlhV/f8RyAtZhVAvBwNxSDoKUeCOYvcJQChvh0KwnC8IIxdiNO71ztkSjA2FG66OQ0xLGsZiYgE9jOIybiRV4l1H3gdyzIcESIFcBzaOkkptL0RTaiD5J1NqFzZlMzoDPs4zVKEv2k6mayw905PslTpyrND1zvMWTzvUeuN%2Bs4TYUe%2BtHgH%2B3aNDuGKnXirgIerQlSBStLBkEzlavq7aqRpbqaTpSQSrNWjnoTMVbCGru5TGpAVVTBGZr1A0FuIFgcxYBQ7ytO8MfJAxceGfbYr446PVIk3fXkS6LeDQ5SDuyM4QrvrhVFZNVSXE2OmGue8D5HxPmfC%2Bj4tgQCLHDUs2JDidxGuNLezZNRIybCAY%2BSQkgAH1T65XwdA4Y%2BDFpmj4HQXGxB%2BwEy3KTYmx5GHTlnLeRc1NVzrk3NzTAu59y0EPIudmiEZa8B5n7Pm8YXxvlxiLQQ34twSwAp8aWIEwKLiVjBVWiENYjTQkwDC2FcL4UYIbE6D8JCmz9C/aiIB36/WMIxGwEsnYihdgII8AB6YYrpbZWEsGYP%2BHt%2BLezTrUUS4k85STEnHWyEcMhRwSUULOxcE7mUMs0FOjlfa1EyXEnSdkehRwLgUkuHkMQl05E9AK1cKHmkPsfTYRDz5MEvrA1ucVsQd0SlDZKqV0qUB8kPfw21DiHEhIyak/Jxk0har/F6C8JRSiSqQLKkI8qQgCCyXKkhcp0gKlwBxnBDiVz/pwXpsofJ2gWfPS53dIJpGcJIIAA%3D)

Similarly, if our understanding is indeed correct, then the following code shouldn't compile:

```C++
auto pun (int i)
{ return pun(i - 1); }
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDMpK4AMngMmAByPgBGmMT%2BpAAOqAqETgwe3r7%2BQSlpjgJhEdEscQlmtpj2hQxCBEzEBFk%2BfoFVNRn1jQTFUbHxiQoNTS057cM9faXl/gCUtqhexMjsHExeRADUSV4MWxDhBFt4cyYaAIImAOwWW8SYBMv7uwyHWwC0W1xnAXc3ABEOAtaJwAKy8PzcXioThuazWLYKJYrTBbcwBHikAiaYELADWIDBkgAdBpJFxrgENGCNGYAGz0swADmZ%2Bk4kl4LAkGg0pChWlIsI4vAUID5OI4WgWcFgMEQICWBF2BHIlDQLCSdHikVYa1UzPpH3pki2wGQyG%2BpLMvEw%2BCIxDw6D0/EEIjE7CkMkEihU6ilOj0AHdiEwkpweCDwZDcULOAB5TYqraoKhbA1Gk1mi1WklmA4eTXa4jowI/XiS6WkCBIDVa%2BhkCgQOvFkDAKSVGi0AjxMUQGKxmLhRoATwjvCHzGII/jMW0mAc49IGrYgnjDFoY4DpCwMS8wDcYloYuhO8wLEMwHE2/wDwceAAbpgT4LMKoF5s1lijtVY7Q8DEobTh4WCxgQjrcqeT7EDEqSYAC56Xv%2BRi4gsVAGMACgAGp4JgQbxkkjBLq6wiiOIXokb6aixroXD6JeKAIpY%2BgAWKkALKgSS1CeMLQY6WBsRACx2AutQuAw7ieK0eihOE/RlIMdH5OkAhjH4SmpCpDDTAMCR0SJ94CN0oxSTk%2BnVKJXQjL0ckzIptjWWpeiTE0OkKXpwkoqsEhRhwEL8rGwrpoaxqmualpSHmBy4IQJClpicwVqhCwIJgTBYAkQmkISkgBCSACcATXJI5JmJI9K8mC9L5eyHCcqQ3KYiS9JcPSzL5cyrXElwYKFfSAXbsKoritiqHVvKNaKkmmxqs2qBFg2upsJwjQsA%2B1wfEwWzIAYRjfPlJJcGStr2iQTourI7rkdIlFKNR266JUIZhuOvn%2BQKMIJtNxyplsq3rZt227cA%2B2HWSBbzfW8TxWYiWjQGMq1pDxazS2DYgP9G07ZeXD5VwfJdj2xB9gO26TqOS7k9Os7zoup4rowBDrpusa7vuh60MeS5YBeRjXoKt6WU%2BL62u%2ByCfkuP6gtu/6AaOIFrIK4F4JBWLQbBSgIbzV7hKACN8Bh2G4fhhFQliJFXZ6N2yFR/qCo99EoaYljWCxMSCRxXEZDxQp8U6z7wMJFmGX4ECuE5dGySUul6MptQR8kmm1G5szmZ0RmOaZ6kdJZGdTLZMf6Zn2TZy5NnR%2B5PmLMs3k/LV72BZwf3EGtG1bdje242DGjRadJYYuW8PSilaUZZQvn1Y1B3ktcvXXFSkhlSadEfXGIq2CNlbAuN8CTUqKqo8ji16itLdZiwCgPpaD5dwYPbDCdsX8RdbpkVb3ryHdduBkEz3htCb0YyDS%2BsqTYKY0yrXPpfa%2Bt8mD32OBAQsUN%2B6BACHDLeiMUBH3iIfBagwr5JCSAAfRvvlIhd9nwECIZAm6dAiYk0HMOaclMmEzjnKJJcDM1wbi3ALTAe4DxHhPFiHmSFFa8EFveYWsY3wfh7JLQQv4ZYASAiOBWYEIJLnVnBLWSFdZjXQkwTCOE8IESIqeC2b8JDWx9F/GiIAgjA0Yi7ZissPZCi9gIE8AB6YYzpnZWEsGYQUqA/YCUDjnEO4lJIlxkhJFO9k44ZATkkooBdK5p1znUYu0lMkh2MuXeSqcHI9ATmXBJHlq6oirtLBuwCODNxYFAq%2BWxSEkgocMXuT94qDwwSPdKgwsrS0nv4A6AQAhglpBSXk4zrhtQGiEzgw0JTJWyiASQYICpgmZAyfKkh8pUiKlwRxnAAhAMWevPptUbQLM%2Bpc1Z0E0jOEkEAA%3D)

Here's the error from GCC:

```C++
error: use of 'auto pun(int)' before deduction of 'auto'
```

A function's type includes its return type, meaning `pun` is not declared until the return type is deduced, which also means the following code will compile:

```C++
auto pun (int i)
{ 
    if (0)
    /* Return type will be deduce here */
    { return 0; } 

    return pun(i - 1);
}
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM9KuADJ4DJgAcj4ARpjEIAAcpAAOqAqETgwe3r7%2B0ilpjgIhYZEsMXGJdpgOGUIETMQEWT5%2BAbaY9oUMdQ0ExRHRsQm29Y3NOW0Ko32hA2VD8QCUtqhexMjsHExeRADUSV4MuxChBLt4iyYaAIImAOwWu1fXu6/nVMcalzdvTw/Pv1%2BxEwBDWRw0JgAzFYfm97gARAFw2GvYGg4hHA4ME67AC0uy4l2hTxuCI4y1onAArLw/NxeKhOG5rNZdgpVutME8zJCeKQCJpycsANYgKmSAB0GkkXDukI0VI0ZgAbMqzPFEpSOJJeCwJBoNKQ6VpSIyOLwFCBDQKOFplnBYDBECBVgQDgRyJQ0CwknRYuFWJtVPFlbjlZJdsBkMgCZKzLxMPgiMQ8Og9PxBCIxOwpDJBIoVOpbTo9AB3YhMJKcHgU6m0wWmzgAeR27t2qA%2BwdD4cj0djErMxw8Pr9xG5vMWvBtdtIECQ3t99DIFAgC9HIGAUjMfDoBFilogUQbUVCDQAntXeCfmMQz02otpqja%2Bd62IImwxaBfi6QsFEvMAbhiLQlr0r%2BmAsIYwDiD%2B%2BDAjUABumCgSamCqNUOybHypwdA2tB4FEFa3h4WANgQKZ6mBSHEFEqSYPCEFQfhRiCssVAGMACgAGp4JgpZNkkjCXnmwiiOIuYZvIShqA2uhcPoUEoCylj6ARlqQMsqBJF0oEMtRKZYOpEDLFUNTOBArjjH48nBLMpTlHo%2BTpAIVmOakzkMP09lDPJpldD0YyeC0eh%2BbU0xeYMcS%2BdMrnRb0EXzFFJkchsEi1hwNJGg2Zq7F2YYRlGMZSAOxy4IQJDjoSU6scsCCYEwWBxMZpCipIkISgAnJCdySNKATKgaVLKh1%2BicDqpB6ryErKlwyrxB18SzeKXBUl1ypZT%2BZoWla/KsbOTpzi6rY7J6q6oCOS4BmwnANCwCF3LiTC7MgBhGASHUSlwUoJkmJCpumshZuJ0iSQWMk/ro27lpWl7pZlxoMs2x1nB2uy3fdj3Pa9wDvZ9UpDudi6xOOZiTrtxb2vOhOjqda5LiA6MPS9UFcB1XCGjQtB7sQB5Hj%2B17nsJAu3vej4OMJr6MAQH5fg2f4AUBtAgcJWCQUYMEmnBT54EhKEJuhyCYcJOFaia%2BGEeeJGbCa5F4JRfLUbRSgMWr0GhKAFN8Bx3G8fxgl0nyklAzmIOyGDRYmpDCksaYljWKpURGZp2kZLppr6amyHwCZHTa%2BZllBTkNkMOgCUOfJTldLFyTuV0Zc%2Be0nRhb01ehQIAUzCUkUhTFhfWSM8V2d3hIrGsqUj1q8PZZwaPEHdD1Pczb2s3jGilb9Y7mBO1UU7V9WNZQ6XjZNH3Sncq13HKkj9TKG0mlttg7dO5L7fAh2uu6tPU5dgY3XPPYsAUAhGMCEV4GD3FMH65UDIA0zGJEOIlw6yRAJCUg0Mqz0jhvWTaSM3Q7HbB8W6ACgEgLAUwCBZwIDDiJpvHkkIybP0pigb%2BsQv4XSGMApISQAD6oCOrcPAchAg3CiEg13PuSgfMTTC2/HyGRosnwS3Om%2BaWn5vya0wP%2BQCwFQJ8lVkxa2vAtaISzj%2BNCGE9zG0ELhH85siJnitmRCiwlHZ0Rdkxd2e12JME4jxPiAkhJgSDvAiQod8zSQjiWVB2MlJxxUubJOpoU4CFAgAeimGmWOVhLBmHvhnQy2dG55z8BZEu1dbJd0Sm5AoGRq6VwyPXKKRSzLdF7tkfubdWmD0qeXAegV2k926XMcuyUx45iwXfRGHBZ4sGIcA3YfCJSCKmOvaBlUGE1VIHVBqQxmpamPv4D6kJIRUkVDKA0xy7hzUmY2c0j9rSbNalSTqVJ4gqg6pIDqcpupcGiZwSE2D76cB3nadK8YbkP0YcsaiaRnCSCAA)

Finally, I figured it out.
Turns out all a compiler wants is a declaration, something it can rely on, a bit of sincerity, a promise from the programmer it trusts.
Me, in this case.
I might be lying, but I am convincing:

```C++
struct Truth;

template<int I>
struct History
{
    static constexpr int value 
    {Truth::value}; 
};
```

Error from GCC, the truth hurts:

```C++
error: incomplete type 'Truth' used in nested name specifier
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMxqkrgAyeAyYAHI%2BAEaYxCAA7KQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSXaYDplCBEzEBNk%2BfgG2mPZFDPWNBCWRMXGJtg1NLbntCmP9YYPlwwkAlLaoXsTI7BzTxF4OANQAKrsECCYAzFYaAIImNwSYLMkGDxduYQT7AJIX2HfXOz2nwAEnhpiQAJ7/EwJK7XfYI/bTJiOZD7NAMaaYVTJYj7D77ABuYi8mH2/0R5Nhxy8pxAIGJ3kwMIAIhc4az2RwVrROABWXh%2Bbi8VCcNzWaxItYbMnmc48UgETTclYAaxAfMkADoNJIuAlzho%2BRozAA2U1mAAclv0nEkvBYEg0gSFWlIoo4vAUIECSo4WhWcFgMEQIDWBGStPIlDQTzocQirC2qktpoAtKbJPtgMg0VItWZeJh8ERiHh0Hp%2BIIRGJ2FIZIJFCp1P6dHoAO7EJjJTg8Hn8wXK92cADytMjn1QVH2KfTmezuf2%2BbM%2BwgHjj9Dxcq4S14foDpAgSFjyXjZAoEBPZ5AwCkZj4dAexG9EGiQ%2BiYUaEN7vA/zGIEIjtE2g1H6CqxmwggjgwtDfq2pBYNEXjAG4Yi0N6woIY8hjAOI8H4MQoF4ISmAYW62I1LSWwKh8nRDrQeDRF2AEeFgQ4EGWjqYSRxDRGkmAsthRgMUYyorFQBjAAoABqeCYO2I7JIwP4NsIojiPWVbyEoahDroXD6DhKASpY%2BiMd6kArKgyTdBhIo8WWWAWRAKzVLUzgQK4Ex%2BAZIRzGUFR6AUGQCN5QVpCFDADAFwwGW53S9OMnitHo8V1DM0VDPEcUzGFOV9JlCzZa50qbBI/YcAKpCuiKnAzqmGZZjmebaiuEC4IQJDkmY8q7oqYkrAgmBMFg8QuaQ6qSOcWoAJznAkki6mYkims6fKmjNtocPapCOvKWqmlwpqWjNlpHZqXB8nNprVUOHpej6/WtoGIZHmG45RheV6bombCcI0LCEgkaZMOiBhGEuM1alwOpFiWJDlpWsg1hp0haU2unwbo96dt2P4VVVNXDhwY4RrS%2BxTvsANAyDYM4ZD0M6qu66npu3XnGYfX7tyh7HqgG5xNGl786zwzU8DyDg7eM1cIENC0E%2BL5vvBf5fipqsAUBIEOCpEGMAQ0GwUOiHIahtDoSpWAsDheFugRREkWRRaqJRDwqbRvLwQxTFfqxWxuhxeBcQqPF8UognW8JYSgM9fCSTJckKUpQoKlpKN1mjsgYy2brY4ZommJY1hmdEzlWTZmR2e6DnlqR8CuZ0REeV5yW5L5DDoIVgUGcF3R5SkEXdF3sUdF06V9P3aUCIlsylFlqW5a3PmjAV/nzzuqzrGVG%2Be4Td11eLtOS/TXBQzDGirh1pbszue4DaQQ0jcM42ezte1Q7qCRXQkBqSMtmYGSJvdWwj1uYvXgG9cME4hbfQTEmf6xAWDzhYAoQkaJCSny1C8UiBA4adUckjas6kM6qWznpEA5xSC4x7MKAmg54IelJhOCm04AbINQegzB2DpjMxFmedm5wuZiV5igPhm4YFiOGGg5IyQAD6GCZqyO4QQWRbC0aPjiErd8n4ALqx0YBYCoFdb80ggbGCcE7aYCQihNCGEFRWxtv7Xg9taiOyHBRZAVF3aCDol7RizEIR%2B3YpxFSod%2BIRxttHYREkmBSVkvJRSylMJp2IRITOjYdI5zbJQqWxki6mW9mXd0FcBAYQAPTTArIXKwlgAj2TiI5OullR5Nz8J5Du/c/JzyKuFQomR%2B690yMPbKLT3I9EXjkZeU9xmr26d3FeSVJkL1mfMbuJUt51jobdBhB9EHsLQUSLhKIcGX3hluHqt8noBkGsNUalAKpv38FDc45w%2BTGj1M6F5CRjrbLdMA70vp76TT5LNPklozQzUkDNA080uA5M4OcehfzOB32ehVQsvzaqeiuSqUgPF0jOEkEAA%3D)

`Truth` was declared in the first line.
Why wouldn't compilers trust us?
Let's change things up.
This time, `Truth` is a template, and `History` is a `struct`:

```C++
template<auto>
struct Truth;

struct History
{
    static constexpr int value 
    {Truth<42>::value};
};
```

Error from GCC:

```C++
error: incomplete type 'Truth<42>' used in nested name specifier
```

[*Run this snippet on Gogbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAHKQADqgKhE4MHt6%2BASlpGQKh4VEssfFJdpgOmUIETMQE2T5%2BgVU1AnUNBMWRMXGJtvWNzbltwz1hfWUDCQCUtqhexMjsHASYLMkGGyb%2BbkxeRHvYJhoAggoExF4OANQAKjcECHtWF2eX17cEdwASeCuJAAnp8TAB2d7nO4wu5XJiOZB3NAMK6YVTJYh3MK/ABuYi8mDun1hxMhTyOr32kjMJxAIHx3kwEIAIm8weC2f4LBwFrROABWXh%2Bbi8VCcNzWaxwpYrInmfw8UgETS8hYAaxAAskADoNJIuOD/BoBRozAA2c1mBJJfkcSS8FgSDQaUgirSkcUcXgKECulUcLQLOCwGCIEBLAjJI7kShoLZ0OIRVhrVQJc0AWnNkjuwGQSKkOrMvEw%2BCIxDw6D0/EEIjE7CkMkEihU6kDOj0AHdiExkpweHzBcLVZ7OAB5I7R36oKh3NOZ7O5/N3QtmO4QDwJ%2BhYhVcOa8ANB0gQJDx5KJsgUCBni8gYBSMx8OgbYi%2BiDREfRMINYH93hf5hiGBMdom0aoAyVeM2EEMcGFoX921ILBoi8YADloWhfVFJDNkMYBxEQ/BiHAvBcUwLCPXRaojjWJUcUwO0PVoPBoh7ICPCwEdrjwJ1sLI4hojSTAWVwoxmKMVUFioAxgAUAA1PBME7MdkkYP8m2EURxEbGt5CUNQR10Lh9DwlApUsfQWN9SAFlQZJHAELCxX4issGsiAFnaBy/AgVxRj8YyQimUpyj0VJ0m8/ywoKbzehCgZjK82oJiixKGJIzoJji/p4kSlLPBaPR4UabKZlyzzZVWCRBw4IU3RHL053TLMczzAtdTXCBcEIEhiTMRV92VSSFgQTAmCweIPNITVJH8HUAE5/HBSR9TMSRzRdAVzXm/ROAdUgnUVHVzS4c0EnmhJTu1LgBUW816sQr0fT9Ib22DMMTwjScYyvG9t2TNhOAaFhcXBDMmGRAwjBXeadS4PUSzLEhK2rWQ6206RdJbAzEN0R9u17P8arq90xXHb7p1nYHQfByG8JhuG9XXTdz23Pr/DMQbD15Y9T1QLc4lja9%2BdZgZqbB5AofveauFdGhaBfN8P0QgCf3U1WgJAsCHHUqDGAIWD4JHZDUPQzD1KwFg8IIj0iJIsiKJLVRqI2dT6MY3hmNYn8OLWD1uN4pV%2BMEpQRKtsSwlAN6%2BBk%2BTFOU1SRSVXT0YbTHZGxtsPTxkyJNMSxrEs6J3Ns%2BzMicz0XMrcj4E89KOh8vyCtyQKGHQUrQuM8LCiyZuAvyCLMg7hLbHr7yuhGPuirH5LumH3Khm6VLF5K4KcuqxZliqvddtq4dHs4O5xdpyX6a4WH4Y0dduvLdm9wPYbSFG8aBimu19sO2H9XBW7wSNGl1oGgeh6J6tgXrc3evAT6kYpxCz%2BkmFMQNiAsEXCwBQuIkS4nPjqHY5ECCIx6q5VGtYtJpw0pnQyeQCZ9lFMTfeIDyZRiOHcGcR9kGoPQZg7BuCrjMxFhedm/guaSV5igfh244HiIGBg5IyQAD6WD5pyJ4QQORwNsxPgVnEJWn5vxAXVno4CoFwK635tBA2cEEK20wChNCYhzbYUttbP2vA7Y1AdiOKiyAaJu0EAxEcXs2LAl9lxCsgdeDByEmHa2kcRHSSYLJBSSkVJqWwinUhEh07Nn0lnDsgQpZmQLhZL2JdPRl0cpwAA9FcKs%2BcrCWDMCAqubla6j3sN5Fwbdl5BRKOvLuMVMjL27rFNeZVp7tNnpPHI/ckqZTnqMzuK8mhTzyvM3pYyd4KEqg2OhwCyYcDYSgnMaCMF3EUTghEeDr5Ix3P1e%2Br0gwjTGhNSgNUP4gDMLDfw/gBSmgNC6b54Izp7NHN6MB/pH4zQFAtAUCQLTzUkPNI0S0uD5M4P4eh%2ByH5vRqsWEFoCIELH4ukZwkggA%3D%3D)

Seems familiar. Remember the `Past` we had early on?

```C++
struct Past
{
    static constexpr int value
    {Past::value};
};
```

Why wouldn't it work?
Shouldn't `Past` be declared once its name is completed?
Then, why couldn't we refer to it inside the curly braces?
What does `History` have but `Past` doesn't?

It is this `template` thing, isn't it?

What is a template, then?

## Template

First, let us address the second elephant in the room:
How does a recursion actually recurse after the initiation?
Assume we are the `fun` coded by our earlier form:

```C++
int fun (int i)
{
    if (i == 42)
    { return 42; }

    return fun (i - 1); 
}
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM6SuADJ4DJgAcj4ARpjEIACcpAAOqAqETgwe3r7%2ByanpAiFhkSwxcYl2mA4ZQgRMxARZPn4BldUCtfUERRHRsQm2dQ1NOa1D3aG9pf3xAJS2qF7EyOwcoQQA1FReDBsQ6xt4syYaAIImAOxWZxu3h1R7eBsmAMwAIq9vG5Jmxzd3lwsz3%2BdzuxEwBCWux%2BryBJ1OoMuHzO8NB4MhxF2212%2Bw2AFoNlxji84SiLm8OPNaJwAKy8PzcXioThuazWDYKRbLTDPMwvHikAiaSnzADWIBpkgAdBpJFwLi8NDSNGYAGyqswADk1%2Bk4kl4LAkGg0pAZWlIzI4vAUIBNQo4WnmcFgMEQIEWBCSXgI5EoaBYSTosXCrFWqk1qrxqskG2AyGQhOlZl4mHwRGIeHQen4ghEYnYUhkgkUKnUDp0egA7sQmElODwqbT6cKLZwAPLer2bVAPcOR6Ox%2BOJqVmPYeANB4i8/mzXj2x2kCBIf2B%2BhkCgQFeTkDAKQBGi0AixG0QKItqKheoAT3rvAvzGIV7bUW0VXtAv9bEEbYYtBv5dILAoi8YA3DEWgbUZQDMBYQxgHEAD8HBaoADdMEg81MFUKpvVWAV1kwakANoPAohrR8PCwFsCAzQ0oLQ4golSTA3hguCSKMYV5ioAxgAUAA1PBMErNskkYW8i2EURxELHN5CUNQW10Lh9DglA2UsfRSJtSB5lQJJHAESCmQYjMsB0iB5jaQy/AgVwRj8FTgkmEoyj0FI0hshz3PyGyelc/oVOsmpxm8oLCLfEKun8vo4iC0LPGaPQFHGGLpjiqyuRWCRGw4OlTRbS0Nj7KMYzjBMpBHPZcEIEhpyJOcuPmBBMCYLA4ks0hxUkF4pXiF4LkkWUzEkVVjRpVVEiI/VSENfkpVVLhVU1eJNSWyUuBpfrVQKgDLWtW1BS4xdXSXd1O29X1N1QCc1xDNhOHqFgUIuPEmA2ZADCMQl4ilLgZRTNMSEzbNZDzGTpDkktFIA3QAmrWtb1y/KzSZdsLu7B4npet6Pq%2B4Afr%2BmUxxu1dYmnX5GvLJ1l1Jycrq3NcQGx17Prgrh4i4E0DyPYgTzPAD72vCShcfZ9XwcCTP0YAgfz/FsgJAsDaAgiSsFgowEPNJDIrQjCU2w5BcIkgiiPNEiyOvSjVnNGi8DogUGKYpRWI1%2BDQlAam%2BF4gShJEsSGQFOTwYLSHZGhstzTh1TONMSxrC0qILL0gyMmMi1TMzdD4CsiL2ls%2BzEpyJyGHQNK3JUjyCkyIvHLyTyMnLwLbDzmzOmGWvktbqKGibuLBi6MKB97lzYpyhYlmyoldTy5s9s4DYWdxtnvo5omNGqoGp3MGcqcdZrWvayhcpmubftlC4touBUflGuVdvNfbbEO%2BdKRO%2BAzo9LsGbpu7Q0e4gLABwsAUChBMKE14GCPClQGtUzKg1zNJUOkkI5KRAC8UgCM6yMmRnPR%2B6NPTeg2D2RegDgGgPAZApg0DNgQHHGTbefIXiziOl7M6jNYg/1uv0MBSQkgAH0IHxH4VA9CBB%2BFPWjHwOgvN%2BbnkvI%2BEWCinwvjfFLG6X5Za/n/NrTAwFQLgUggKdW7Eba8B1qhbOAEsI4SPCbQQhEWwW3Ilea21FaISSdsxV27EPbHR4kwPiglhKiXElBYOSCJBh2LApSOFYMH43UvHTSFtk4WlTkZTgJlYhmWzrpFu9gbIuFLkPZyxQx6V18hkIeVc/Kj3Sl3QpPdGid3Ck0joqV6kV2Hi07IdcUrRS6YFTKk8Cy4IfmjDgpCgExhAWAjYQipSiJSpvOB9UWGv1mAfNq/ROrTQNP4X6LwXg0mVHKY0xyLjLQma2K0z87RNS6iASQNI%2Bo0k1GqeIkh4gKgGlwBJnAXh4MmXvEUM9kw3Kfps%2BYDE0jOEkEAA%3D)

Let's compile ourselves into instructions by reading GCC-generated Assembly code:

<table>
<caption><b>fun(int)</b></caption>
  <thead>
    <tr>
      <th style="text-align: center">Assembly</th>
      <th style="text-align: center">Instruction</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>push&nbsp;&nbsp;&nbsp;&nbsp;rbp</code></td>
      <td rowspan="3">Prepare the stack frame for the function</td>
    </tr>
    <tr>
      <td><code>mov&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rbp,&nbsp;rsp</code></td>
    </tr>
    <tr>
      <td><code>sub&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;rsp,&nbsp;16</code></td>
    </tr>
    <tr>
      <td><code>mov&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;DWORD&nbsp;PTR&nbsp;[rbp-4],&nbsp;edi</code></td>
      <td>Initialize <code>i</code> with the value in <b>EDI</b></td>
    </tr>
    <tr>
      <td><code>cmp&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;DWORD&nbsp;PTR&nbsp;[rbp-4],&nbsp;42</code></td>
      <td>Compare <code>i</code> against <code>42</code></td>
    </tr>
    <tr>
    <tr>
      <td><code>jne&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.L2</code></td>
      <td>Jump to <b>.L2</b> if <code>i</code> is not equal to <code>42</code></td>
    </tr>
    <tr>
      <td><code>mov&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;eax,&nbsp;42</code></td>
      <td>Place <code>42</code> into <b>EAX</b></td>
    </tr>
    <tr>
      <td><code>jmp&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.L3</code></td>
      <td>Jump to <b>.L3</b></td>
    </tr>
  </tbody>
</table>

<table>
<caption><b>.L2</b></caption>
  <thead>
    <tr>
      <th style="text-align: center">Assembly</th>
      <th style="text-align: center">Instruction</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>mov&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;eax,&nbsp;DWORD&nbsp;PTR&nbsp;[rbp-4]</code></td>
      <td rowspan="3">Subtract <code>i</code> by <code>1</code> and place the result into <b>EDI</b></td>
    </tr>
    <tr>
      <td><code>sub&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;eax,&nbsp;1</code></td>
    </tr>
    <tr>
      <td><code>mov&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;edi,&nbsp;eax</code></td>
    </tr>
    <tr>
      <td><code>call&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fun(int)</code></td>
      <td>Excute instructions for <b>fun(int)</b></td>
    </tr>
    <tr>
      <td><code>nop</code></td>
      <td>No operation. *Burp*</td>
    </tr>
  </tbody>
</table>

<table>
<caption><b>.L3</b></caption>
  <thead>
    <tr>
      <th style="text-align: center">Assembly</th>
      <th style="text-align: center">Instruction</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>leave</code></td>
      <td>Clean up the stack frame</td>
    </tr>
    <tr>
      <td><code>ret</code></td>
      <td>Return to the call site</td>
    </tr>
  </tbody>
</table>

[*Check out this article for more information about Assembly.*](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html)

Now, let's invoke ourselves with 43 by placing 43 into **EDI**. We will place the result into **EAX**:

<table>
<caption><b>Routine</b></caption>
  <thead>
    <tr>
      <th style="text-align: center">Step</th>
      <th style="text-align: center">Instruction</th>
      <th style="text-align: center"><code>i</code></th>
      <th style="text-align: center">EDI</th>
      <th style="text-align: center">EAX</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align: center">1</td>
      <td>Prepare the stack frame for the function</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">43</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">2</td>
      <td>Initialize <code>i</code> with the value in <b>EDI</b></td>
      <td style="text-align: center">43</td>
      <td style="text-align: center">43</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">3</td>
      <td>Compare <code>i</code> against <code>42</code></td>
      <td style="text-align: center">43</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">4</td>
      <td>Jump to <b>.L2</b> since <code>i</code> is not equal to <code>42</code></td>
      <td style="text-align: center">43</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">5</td>
      <td>Subtract <code>i</code> by <code>1</code> and place the result into <b>EDI</b></td>
      <td style="text-align: center">43</td>
      <td style="text-align: center">42</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">6</td>
      <td>Excute instructions for <b>fun(int)</b></td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">42</td>
      <td style="text-align: center">Ignore</td>
    </tr>
  </tbody>
</table>

<table>
<caption><b>Subroutine</b></caption>
  <thead>
    <tr>
      <th style="text-align: center">Step</th>
      <th style="text-align: center">Instruction</th>
      <th style="text-align: center"><code>i</code></th>
      <th style="text-align: center">EDI</th>
      <th style="text-align: center">EAX</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align: center">7</td>
      <td>Prepare the stack frame for the function</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">42</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">8</td>
      <td>Initialize <code>i</code> with the value in <b>EDI</b></td>
      <td style="text-align: center">42</td>
      <td style="text-align: center">42</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">9</td>
      <td>Compare <code>i</code> against <code>42</code></td>
      <td style="text-align: center">42</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">10</td>
      <td>Not jump to <b>.L2</b> since <code>i</code> is equal to <code>42</code></td>
      <td style="text-align: center">42</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">Ignore</td>
    </tr>
    <tr>
      <td style="text-align: center">11</td>
      <td>Place <code>42</code> into <b>EAX</b></td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">42</td>
    </tr>
    <tr>
      <td style="text-align: center">12</td>
      <td>Jump to <b>.L3</b></td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">42</td>
    </tr>
    <tr>
      <td style="text-align: center">13</td>
      <td>Clean up the stack frame</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">42</td>
    </tr>
    <tr>
      <td style="text-align: center">14</td>
      <td>Return to the call site</b></td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">Ignore</td>
      <td style="text-align: center">42</td>
    </tr>
  </tbody>
</table>

<table>
  <caption><b>Routine</b></caption>
  <thead>
    <tr>
      <th style="text-align: center">Step</th>
      <th style="text-align: center">Instruction</th>
      <th style="text-align: center"><code>i</code></th>
      <th style="text-align: center">EDI</th>
      <th style="text-align: center">EAX</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>15</td>
      <td>Clean up the stack frame</td>
      <td>Ignore</td>
      <td>Ignore</td>
      <td>42</td>
    </tr>
    <tr>
      <td>16</td>
      <td>Return to the call site</td>
      <td>Ignore</td>
      <td>Ignore</td>
      <td>42</td>
    </tr>
  </tbody>
</table>

Hyper links

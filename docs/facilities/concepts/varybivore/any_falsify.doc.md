<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AnyFalsify`

<p style='text-align: right;'><a href="../../concepts.md#varybivore-any-falsify">To Index</a></p>

## Description

`Varybivore::AnyFalsify` accepts a callable predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `false` and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...||(not Pred(Vs)))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AnyFalsify = REQUIREMENT;
```

## Examples

`AnyFalsify` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

Since `(...||(not Pred_0(***)))` and `(...||(not Pred_0(***))) && (...||(not Pred_1(***)))` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
constexpr auto Pred_0 = [](auto...){return false;};

/**** Pred_1 ****/
constexpr auto Pred_1 = [](auto...){return false;};

/**** fun ****/
template<auto...Args>
requires (...||(not Pred_0(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||(not Pred_0(Args))) && (...||(not Pred_1(Args)))
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCaAyzmKopxMdMXkSn5yuNxMAGYACLHEwBKwBMEQX5EAB0yJWJgA7BZzgRNgxjlQxEpQVY0WCiY8nuSDkcARdLlxbkcHs9Xu9Pt8EagaVd6aCIVCYXCOcjEaiMVicXiCZgySSyc9KXc8V5cXcmU8CJgWCkDBrQW4hcinsRgApQdhyecAI5ePDnBTHCDC9FuZ0QBioAhc64QI0mlb%2B8ksjVs44xVCeJUMCCizGYbHEXH42iEkHE0ny54arU66Ug/V/VDC32mkHm55Wm12h1OtEu2tuj1ejQ%2B40Kf0rSFmABs5i71eRztd7s9Z1pXBbfoDzIErK%2BofDtEj0fRsfjuIIxC8ubT5IV1IAKphZgzDmrdrtjthiMQSOTZkxHMhLkwFEoWtRlXquGbo6jUxw1loTgAl4PwOC0UhUE4F1LGsY4FA2LZME7EEeFIAhNAAtYAGsQACLtEUSLspACNEu0kABOEEyLMEF9E4SReBYCQNA0UgwIgqCOF4BQQDYjDwIA0g4FgGBEBADYCBSP5yEoNAtToeJIlYHZVCIgBacjjmAZBkGOKRETMXgLkIEg8HQPR%2BEEEQxHYKQZEERQVHUQTSF0LhSAAd2IJgUk4HhAOA0DMMgzgAHk/mkz1UCoY41K7TTJG03T9MkQyHQ8BT6G%2BcxUJWXgBK0NYICQeSUkUsgKAgMqKpAYApDMPg6A1YheIgGIQpicJmgAT383guuYYgerCmJtDqAS0PkthBDChhaD61ysBiLxgH1Whk360gsBYQxgHEJbbQmvAADcjxCj46j%2BHY0PCDUgNc2g8BiHzho8LAQo3PBmO4XgzuIMMlDBTU9qeoxMLWKgDBNAA1PBME8sKUkYLarOEURxHstGnLUEL3P0PaUGsax9Ge3jIDWVAUl6XiOHU2Z0F5UxYMsMxOP%2B4hzPOimuh6LIXAYdxPHaPRQgWcpKj0QpMgEKY/A86XeiGCXll546BH6SZhbyDzanqDW5mVkYqnGAY5b0e8WiNpYqjWBDNm2CRAo4ED2JCri4o0rSdL0gyzAdXBTJy2iuHy9CIbWBBMCYLAEmjUhcMkEFESotFJA0SQzEkLtWPwij6I4RjSGYkEzEREEuzRRIQUSAIAi4aiKOSDjeC4ni%2BPDwTirEkqJMimSqpq7LlLYTh4sS45kAMIx9IoxEuERCCTKITmLI8tGbMx6RsaUXHXN0RrvN8/rnddlvQo4CKpL%2BY4Ys9hKtKnvbZ/nxeMtQLL4hQsww8KoTe6HvEWS1UP7lWyigae9UKJcDYjQWgLU2odVcoNXqW0UHDVGuNBwW1pqMAIHNBaIVlqrXWptX620QZGAOhBfA5x6hnVpkvVQV0NRbTut0EKT0Xq9XejsCCX0fpoX%2BoDTAwNdpUPCKALufBoYKDhgjJGKNyEbwxnZbesgcYuQggfAm4NmZWEsKTGI5N45UxppwemBBGbgn0dYNmrcOZcxMXbbo6s/AQFcObDyYsyjGylukGW2Rtby1SAEpW4s/G61cfrPocwvFqxiZreYvibYWzicEtJAxraS1DusB2dlT7BVch7cej9IEvwXjcCAgcV4oVDgVCOpAo4x1GPHXCMC2IPSLiXAIiJKIBAomYQZ3ZEgN3Im7YpnB278QhsJHuSBJJRWAYA4gI8djNBYFpFgCgTp6ROlwOeOZZjGXwCvcyllZCbzUQ5eQu8tE6BAHRI%2BflfqFImZxcK/doqxVUFsnZeyDmIiOZ6CAmUwFf1yiCX%2BsyAGgIqssuF4DdkpBSJcfZFFLjAsuL87ezV4iIM6t1YaaCiUjTGhNHBH8Zr4PmotGhmAVprTEGQtCO1QZ8N4LQ46DCLrMOQNdNhggOGPWeq9HqvDPqc0EX9eIIixGg0kbMqGTBYbw0RsjMCaEVG2QkOoxydy8aPN0cYYmhiuHOMgtTLItNdgMyJizCw9jIKOKwBavWvQBZC1yCEnxiwcmhKKFkeJissjZNVu6ho6TvUW2ib0JJYaTaW1aBk3WhsImpNyfbJCTsC5n3dpwOKfzdnHHRUCh8R4QU1JIHU6FXdI7R1jpQZ23THllzGbRMwnbqgaC7AM95rcpm2A7n/f0CcQBJ3njXAImcQQBB7bRMiBcQRFI%2BdxTuRVnZGX7RfBpdbSD/QyM4SQQA)

By turning `(...||(not Pred_0(***)))` and `(...||(not Pred_1(***)))` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AnyFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyFalsify<Pred_0, Args...> && AnyFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept AnyFalsify = (...||(not Predicate(Variables)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iHdlMRMPhRGDSHd4UQAHR4gBqzTwTBi9AUMOwILQDG2KQIdyuDAAngAxMQZKhMu4wgAidwgeJxJgA7G4RW4IAxUPTkai8OjMBBCcRiaTMAoVpqYVZriC/gDznrjncACrqggKL6G34Gk5Ao33WXoAD6GithyB1NmmFUKWIWIRqCRKJdbt53ICVgCPIg2NQgpWIosKIImwYdyo7Mw2pFPJzuptjpDzq47v2noE3t9/rjwdRJe50L5JkjLZjcYTSZTaYzWZzwrz0J1wMLhwzXnT3xBYIhH2zsI7eKuxGA5OhlOuKIAjl48CjLYzWey8JyYW4na7McvV4KKVTK2Dq3cYqhPOOGBBE8Lk5hU8R05mtBKP2eYFqC4IvHOZ6Lji15rhuy6YDue7qgyzJskBJ5MmeF4aFeK4KLe67cmYABs5ikWhR6YaesIXlw%2BE3nid7XF6j5%2Bs%2Br60O%2Bn5dr%2BPYEMQXjzlYA4gg6Y5mrMZZArMHzys6TAKEoLTUBOZ5cBSn6JkOHBrLQnABLwfgcFopCoJwYqWNYdwKBsWyYCR0I8KQBCaHpawANYgAEpE4okpFSAEwqkZIACc0IhWY0L6Jwki8CwEgaHhJlmRZHC8AoIB4W5pl6aQcCwDAiAgBsBApAi5CUGgzx0PEkSsDsqgBQAtKFdzAMgyB3FIOJmLwcpECq6B6PwggiGI7BSDIgiKCo6h5aQugMQA7sQTApJwPD6YZxnueZnAAPIIhV9KoFQdzNaRbWSB1XU9ZIfX8h4tX0P65jOSsvC5VoawQEgNUpHVZAUBAgPAyAwBSGYfB0GCxBZRAMT7TE4TNEyW28KjzDEEyh0xNodS5S5NVvAQh0MLQGOLVgMReMAcK0EBmOkFgLCGMA4g0yh9QAG7qvtPp1AiOwueEYIGYttB4DE624x4WD7YJeCJdwvD88QL5KDy4Ic9LRjuWsVAGKu%2BJ4JgK2HSkjAs2NwiiOI0123Naj7ct%2Bgcyg1jWPoMtZZAayoHSWRZRwLWzOgvKmNZlhmGlGvDQLAddD0WQuAw7ieO0eihAs5SVHohSZAIUx%2BAxRe9EM%2BejAxtT1AI/STFneS190RMNHMVcjAktdzKXehyS0XdLD3ax2Zs2wSDtHBGaQqW8Oll2te1nXdb1Zj8rghAkE5XBfa5htrAgmBMFgCSfqQ3mSNCOIRcKkgaJIZiSKRyW%2BWFsUcPFpCJdCZg4tCUiwpEjQkSAEAIXBIphWSPPA6GVbDZQPnlP6xV/qlROpVUG4M3oNTYJwK6N07jIAMEYHqYUcRcBxGZQaJA8AjQYnbCajtpDOyUK7RaugYZrQ2pjaes9YHpWOuVBEdxzpL2uu1YhHMyEUKoc9VAr14hOTMPvH6%2BU0HYPiFVMGCigZvRQCQqGYUuB4RoLQeGiNkaLWxujFmNjcb40Jg4FmpNGDk0ptTMytN6aM2ZmrVmusjBcy8TzRw/NQ7UNUMLMELNxbdH2tLWW6MFY7DMsrVWLkNZa0wDrdmQTwigGQXwE2CgzYWytjbfxjCHZTRYbIF2C0zKcI9gbaOVhLC%2BxiP7C%2BQdeih3DgQSOTY2nWDjgvBOdCk4Xzrr0dOmdchl2CBnYeBdy7pGLtkZuiyK5ZBWTXFO7cG59y2QPNu9c%2Bidzzt3AexyFk3IGHs0e6wJ5TT4XtRai8CGSMMTIyhboIBbyGrvVRh9SDH1PqMC%2B3kTF4Ult/X%2BAQcThQCGFMwqKyKJEgaFOe%2B10qZUQWolB8A0FlVOtozRxBcE7GaCwdqLAFC826rzLg5DITmgGvgIadDRqyCYbUma8g2GNJ0CAGK3DNpqzeTij5R0MFnQuqoOlDKmUspxGy6SEAXp6KUR9aEIKikaN0cDclRr9GMpSCkZ0zKwrOnVQQZ0iqWFw3iJYlGaNcZ2PdXjAmRMXEKLJhTKm%2B1vEMzEH4lybM9apN4PgFEfMBaLSFsgEWsTBDxKljLOWTIUlKxVBk9W8Rsm5L1gUw2xSmCm3Npba2JkXLVMmhIOps0hVu1FS04w3sOmJO6YHYOlZOC7Ajl7GOFgxnmQmVgHtBzzlzP7gxXOZRrlrKKFkOdqR1mVyuSPU5qcjkDDXTMjuDyt2rPGPuk5vdj2Lu3XvZ5Dkp6f34bizgl0lWMruNatVc4NWAp3h9Pe31QXgrPpQae8LRX/yxdFMwMGuCJA0KRFF0q0qcHxTlUFV8b6QLAU/aEAQEPRRCp/aE7yUPwMJdPfqyGF6oaQb9NYGsMjOEkEAA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/varybivore/concepts/any_falsify.hpp)
- [Unit test](../../../../tests/unit/concepts/varybivore/any_falsify.test.hpp)
- [Example](../../../code/facilities/concepts/varybivore/any_falsify/implementation.hpp)

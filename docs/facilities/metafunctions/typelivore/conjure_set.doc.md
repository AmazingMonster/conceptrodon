<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ConjureSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-conjure-set">To Index</a></p>

## Description

`Typelivore::ConjureSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

The result will be stored in a `Capsule`.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
ConjureSet
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias ConjureSet = Result;
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = ConjureSet<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`ConjureSet` is implemented as a shortcut to `TypicalConjureSet<*>::type`:

```C++
template<typename...Elements>
using ConjureSet = TypicalConjureSet<Elements...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElwAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCw0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bDAg87gRiF5MHCrNdQf99nc3Ew0govPRGYdmaz2UxOfDubzWJgAHQO0VXSbKhw6vUG%2Bhqik3KkeVoMPAANxI7BAABUeXhRLRlExJphjedQXzPmkmNsdagA8HQ7CAOzqkHXFlsjmqq08xi2h12p0urxuyNpaNiOMJgtWfMPb0av67O4WeOJ3VKEA%2B0vmy1ua3VtjUjMAa0w7lkTAiCXrSsbUubrdj8enceQy9XgnXkWITpMhdBd3vdy8WSMiqrcoVx9PHnPG6vgSLN49v%2BPq7AOABKmDIJsWRBiOw7jn2VyTuWmLwneD7IRaFYzlWqa1uidxQvGXzfq0v5XKQ6H3ph06znhjqBNghEGAoJFrr%2BNhUa%2BNpsLW2D0GwgjOgKXF0TWDr8ayjAEBYCiUdcD7cXO9oOgA8gQCAJAoqEYtcDZNlGMbttOpEXgkILwpJgkEM6%2BGMQKpkcQSVnSbJdnYAK6macQCjuZit4KQ%2BT4RMASnvnce5GYeqqBfeBJcYpjmXhZbguUJvkOgKaUyRldb2QlD5eVp%2BGxXK2AgCAs69iC3bVf5PaIVqEWGWI37aJsmBCJgUo/KCNHYWJvESQJ0naYxoL6buLW0G1HVdQQ/lFop/VcrhtpOopk2PN1660J2gF1aVK3wlkABemAAPoELWACSG0PltTxkbQBLEhVERYKoF1KAAjiqEoEjdfnjaVN5LYpGFmihlY8YmN0MAoLwOCFAqDSpdpDieVzEMAY26VcEMPa0jjIIRAgJkGYiCsKdx4OgKIvaVikQAVhM0nSeCqIDBFCkQtbyQThMQ/DiOQY4RgC0LEOY4u2O4yVguEysrN3AAtARb0oAI%2BBNGIV0q/FTNCxA%2BH5m4N5uJreAKN9toXUGgMI0j4vAAKMty3jawq4lHqGth6KS1LD66vqfurbDdwi87IUVVVIOKxD5LAaDtXJ8WCfHThsP3feW0ABJ01gDD7anAFHVDWGvXg51XbdOd3PnheMK9BDoO9DCfd9mB/W82FAwxGLx4pYMq8FL6zuF/qGLmtIVZFbbRQbaFG4TWBQlVK8Qyzm9S09u0t23IAsEwy4XR9mBfb9/3bNz41D0HhPvfTtAQJrs5n0Xjjcs5I2CHjI/dlrMrHeD4VgKyluiWOVZqrD1Lj6RSY9QoTzhAqAuJJm4nVbhVY%2Bp9z6X27tfbCZ1MCoCoLWCA2UFDKzvuVSq0C04HQYZSQELDerMMOJHMsUlzxNCTMCLUrDATAj6hXWia0hp2koU6RBWYGDtVpPNcK88ZoCHkZ1bqP9uEEFypAuhLxDq%2BkEWwwxHDsCqFYOyRMxiBGCOERqcEkJoSJgJOKbYaRtHXnYdqEOnorFMhEWWSuMNlJ%2BT0tuN0Piw5MJMdqIQXg0jFBXBBT0PV/HXBkXEhJmQkmfENFKFB7pQ5enhBEAgApSn7HKYIQ4Scy4xLuMkvJfDQQyMabQfJ8pZFqPmgSUpVSCCVNptUwZFT9i1JAlScMnxUkmgmsTaMF1iIJAIK/LBIAFB23jASNpZS7iZMSegHZ6JqEWA4GsWgnB/C8D8BwLQpBUCcHNpYawDcNhbGceCHgpACCaDOWsRcARJB2g0AADjMGYZIyQuD%2BFBSCrg%2BZ8zSAuRwSQvAWASA0BoUgNy7kPI4LwBQIAsU/NuWc0gcBYAwEQCADYBA0iInIJQNAbI6AJCiLaTgqgQUADZVbcskHcYAyBSZSDtGYXgK5CAkDpnofgggRBiHYFIGQghFAqHUKS0guguCkAAO7ED1JwHg5zLnXN%2BfczgqlET0qlKQu4XLeX8sFcKu4oqzB3AgB4Fl9BiCwk%2BSsXgJKtBrAgEgZlLYfWMogOG1liRgBSDMHwOgLIfKUFiOa2IEQ2goiNbwTNzBiAolUrEbQYtc2kGZdZVSDBaA5s1VgWIXhgC6loLQQl3BeBYGPkYcQ9a8C0mRrBdtdyL6QURDsL5pSGjmuRLEA1haPBYHNUqPA6KO2kFgsQWI2SnjduAMiIwvy1hUAMLjAAah8XVqleTlrlcIGMSrpB3rVWoc12r9CGGMNYaw%2Bg8CxEJZANYqB3E5HbarYkKDTDPMsGYXFm7iB00%2BPANYdgxY5BcB3GYfgdVhA3EsMYOrijZAEFhvQRGmiLFGDUXoaGBADGmJ4LoehUPIzo1MIYeGqPMfY6RnV8x2iUaqARlDbztgSBNRwK52LzV4vtTyvlAqhUiqBe6ihOsSB%2BsCFwAN3yj1rE0kwLAiQID/JAJIQIdpkiBERRoSQZhJDcsxf4blqRkWotIOirTdpuVcG5SC5IcLuX%2BEkNCqz3LpOarxQSolunSUhqpaGml1qGUUGjagb1bKOUcDaCwIM%2BZVZMGYp%2B11yQ7RcGBRK9TCG246rvQq8Qyrn1KFfZq3Qib9WGo7RJqTOLeB4qtXSxEdw7UOoU0Vl8KQyvAo9V6iNCRNNmB00GsliWY2RtS2tsYREjApC4Fimg7StJpozVmwt5b83ZuLaWhw5bK3SWrbW81Dam0trbeWrtn7e13PwAOxwQ7zWjqgiyctU7kV3NnfOlEi6dh3JXWur5m7t1KF3Z9mOcW%2BCnoUBezAV6b3rrqw%2BiQT7ZAvo1XctrH7D1QasJYX9/7kP3JA%2BTTg4HW6Qe/TBuDCRqtIcAzR1jfgICuF4yEDugnliEcyMR3IjGCiS5KDkcXBH%2BdNHox0WX2GVf9HY0r6j/H1f5E1/r3X4n1ibDE9p/QpqIu4s4HJx1ArtuhUm%2BVjQHrcBSt9VibTga9OkAM0ZygEn3OedK7Z/M/hkgIsCHZhzIWbd9c4NF4lR7yUJaQLSm1UbNvEHZWwTgOWnUsAUEGUmQZJvlkmJVz3MrauyHq4%2BlV8hmtk50CAYIHW0i5u62ayLlrku2qoPaovJey8V6wpMGb6W5te/BIEJbqfVvT9jdn5fPqQCl4SfbFIF1K8EAuqoflSbDupogOmzVF2zvrsv0WktZb113cEA9ut33MCNubWIN766Ps9ph52/taG/2mqgO46IOgg06mqEO2a0Oy6CG8OvAiOO6rIqOh66OJ6TA56l616jAt69ehOjWJOLeb67elOX60GNgs6AGJmjOTQ7auwb01O1gsGfW8GiGVBKGDQtGguwuGueguGFQXG8u0uIu5GiunGQmeunBAuauIuLGquOu4hEutgPGvBfGChAhEhpuCgomSqPeCeFqHAw%2BAqxepedw5epWe%2B7uVWmmPusWwa%2BmmAhmYw1BbmaKIAEKdogQgQ/gMKIWmKXh%2BYfm%2BhUWtgMWy2Kwpmkg/glm8K%2BYmKIKkgUKXAYKZg4WyKgQvetu%2BKdhfyVuHA4qwRSeORERG6Wk6GkgQAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/conjure_set/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/conjure_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/conjure_set.test.hpp)

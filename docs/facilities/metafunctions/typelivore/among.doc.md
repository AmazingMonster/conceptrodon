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
using SupposedResult = int***;

using Result = Among<int, int*, int**, int***>::Page<3>;

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

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5oERyN5YANQmgW7IE%2BhYVKfYJhoAgvcPBJgsaQavp24EAJ5pjFYmAAdKDsPQ2IIFLdnhNiF4HEcACr/PCiWgPFgCYAnADsVlxABFTlZHs9Xu9Pphvn8Acw2EcAGJ4YgTGGPOEIgjI1HozHY77M1kEdlPfHPI6So4Uj5ML5nLIAL0wAH1uQBJUVSo6cxHKYioIjKJjATB4gnEwKkp6PbUyqnfJWqjVaqXETAARy8LMwCiOEE1gUthI0ywlUt13P1htQxtN30Dd1tUpM%2BKOXiyRml/zNp0JTJZbKteMt1vDkvtcupZyYXiIoOBD2A7rejAI0MCSYe2ozERxcdzQaO0aNJurbibLch7YbtxAIFp1bLRJJz3Jb1l8p%2BOfpZqFE1I2bpQKOQkwaAY6EPi93DYA8gQEAkO13Izy0mixPyjILCwRD2eF5XkcD5Pqys6dmu4rJhWG4OgqeDKmqRyJuWOoEPCeoGqOponDB5rppmOKLicQ4oh%2BfJYj%2BZygc%2BEHYPOlavMO2GxmOCZHAAtEcZhzguOYkiWq5kvhTHjk6yGofh7pej6foBnmeahmhb4jmx8ZnFJ3YpmmvZZiReYFsKgmpqWa6iXBVaOohzooa6koyd67ryYGwZcGG%2BGqaxA4JvZBF6cROakfmgECOgJkrla5nabBlJWTWdaoA2k6YK2UJ%2BQFw5jsFLExj5ZwpWlM6gjCUVkpFZaPGJNI7kCDbgkVL6whhXJHN%2BwBQdadqWVutb1qChXTk1%2BGZQOOXkZ%2BGJUR1ZwNUN9FoYxPVmvlE7Nql80lZB%2BGMQJZVimZIkPAA9AAVOdF2XVdx3PGdF3Ir67ZHJdN2PHdV0fedr02k8Zh7AwBxeMc3wXlsaTtqKzyZUIXhpMUmDoAASr6Xi0NyhkRAQF3CT9mXIwoqPo0O7XfJjh6Y6d5OCOdVNY%2BdfGrYEpWVQ8cyOMgKpMAoShtBAlzzgoQKcx2bj44TAGw/DSMo2jtxhvtHCrLQnD%2BLwfgcFopCoJwbjWNYOrrJsuZ/TwpAEJoiurAA1gEkjAhokhcLigQaP4GhmEkSRmAAHN7%2BicJIvAsBIGgaKQ6ua9rHC8AoIBh%2BbGuK6QcCwDAiAgOsBBpHW5CUGg7x0AkURApwqje0knFJJIRzAMgyBHFIwJmLwCOECQeDoHo/CCCIYjsFIMiCIoKjqInpC6KkADuxBMGknA8ErKtqxbWucHedbZ9yqBUEcZcV1XNd1w3dtmP6HgF/QxAnCbyy8AnWirBASD5x%2Bl%2B5xAL%2BF4kwBSGYfB0K8VklBYgr1iBEVovx568DAcwYgvw7yxG0OeBOpt87TjvAwWgkCx5YFiF4YAbgxC0FjtwXgWAWCGGAOIHBPoHB4AAG6%2BhXpgVQ546zbFNpjeoK9aB4FiDPOBHgsArwwngYOpDSCMOILETImBCRvEobwowFtVhUAMMABQAA1PAmBJ53jpFAwewh0T92kN3eQSg1ArwnvoShKA9aWH0Hw2OkBVioHBjkEhnFLh5lMJYawZhI5SOIB3JhriejIJyC4S80w/CpDCBEYYVRRipGKNkAQsS9BpMaAsEYiRxj1EiQIfoUxPCdD0HYIpTRJiDESYsFJtgamZPGDU3JyT8mrAUIbLYEhF4cFVuHFeUdd7l0rtXWu9dG6nwgLgNuV9djuTvio1YT4mBYESBAa2IBJCBGBAATkCLiSQDszCSCSKHfwSQ9n%2Bw4IHUgwdAhcGBCkJI3s9ney4Ekfwjt/AHKSIMseUcY5xzNio5Oacn4Zw3jnCgH9UAXyLiXDgrQWD0NxJxJgRwDiUIbns4ETzNatyICEzuqRzG93EAPcxw8rFj10H/aes8oF9IGRHXgUd15ZzrEcbeRwUVooxVigwWYuB4oJWfeFr8EjX0CGYW%2BoLE6P2fpKr%2B79P6XxAPy9F2KjCiq4GHGgaNnzANAeAuBhiYEQIQUghwhi0FtgwVgleuD8GENoMQwx5DFHbE1vgd0dDGEkMJaw5A7DDFcOVmPXh/CIFCJ9XfEJ4jTZSJkUoeRFCjBKNAIqvg6itE6L0QYiR5KTESDMbIGlo9Nb0tscovxVhHHRpcZsrWHiBBeJ8UGetASgkJBJWEltlS6HOAgK4ZpIRLxtKWKkzI6TchlIKDOkoOQp0NKHY0Ep7QF1xIicO6p8w6l5IqU07dx6D0VCPe5NYGwelXsjayoZnA%2BXEFReizFOqcSivxfbf0sziUysWQqh%2BKzMBrNGC2yNdyHl4odriX5uJnaSFOVXVIbLV7R1sCC%2B%2BScU7p0zpvNVKrL7FzYJwFFB8WAKHofXehX6qQTBbvgYlHcu6yApaYoxlbrEgGCIyuepCWXL0BWvaFW8d7kerpR6jRxaN4vo9yCA58pXzL%2BoEeV2GlUoCIwkQjCLEjUbhiqWTKp5OcxfVXf%2BRqgEQBAWPS15qJH2fgYg5Bdr4XoMwdg31mA8EEKISQ02XrM3xtIH6yJgbmEhrDRIiNPC%2BECN%2BHGkRibDEptkemxRfYwVqJNPm3R%2BjGCGJLX3MtnHLFVp0Dx2txgHE2CbfANxbaGAkOOvzbtlhAnsuCaE5tnTCl7uie4U98TJ2HvaVk2djRx3ZJXWN6du6N0nvyDu9dfRWlzbXUt8pLTz1JOnZ07p/dBMAsjk%2BiTRwpM0bo1WCYv6mMkAA%2Bp5ZpBVnrMoH0qDIAzB4sCIEfwbtHah1%2B7iV5J32WcGBfHZ7NtJD%2BH2f4b2Hs9mSD2c7Q5XBgiRsCEJ07GGNN9ObmD9DSzFWrCkVkZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/among.test.hpp)

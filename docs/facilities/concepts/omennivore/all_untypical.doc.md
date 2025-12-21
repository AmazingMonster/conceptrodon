<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::AllUntypical`

<p style='text-align: right;'><a href="../../concepts.md#omennivore-all-untypical">To Index</a></p>

## Description

`Omennivore::AllUntypical` accepts a list of classes.
It returns true if none of the classes contains a type alias member `type` and returns false if otherwise.

<pre><code>   Classes...
-> (... && (not requires {typename Classes::type;}))</code></pre>

## Structure

```C++
template<typename...>
concept AllUntypical = REQUIREMENT;
```

## Implementation

```C++
template<typename...Structures>
concept AllUntypical = (... && Untypical<Structures>);
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/omennivore/concepts/all_untypical.hpp)
- [Unit test](../../../../tests/unit/concepts/omennivore/all_untypical.test.hpp)

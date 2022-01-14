# RangeQuery
To query the sum of a range. It only supports `int` value.
The idea is to recursively divide the range into smaller ranges.

![](visualize.svg)

## API
```cpp
template <typename ValueType>
class RangeQuery {
public:
    /**
     * @N the biggest possible value is 2^N.
     * @E the number of sub-blocks is 2^E.
     */
    RangeQuery(int N, int E, std::function<ValueType(int)> func);
    /**
     * @return if successfully update.
     */ 
    bool update(int x, ValueType diff);
    ValueType query(int l, int r) const; // Not including r
}
```

## Example
```cpp
std::unordered_map<int, double> values{
        {32, 40.2},
        {27, 24.4},
        {100, 1.1}
};
RangeQuery<double> rangeQuery(10, 3, [&](int x) -> double {
    if (values.find(x) != values.end()) return values[x];
    return 0;
});

for (auto [x, value] : values) {
    rangeQuery.update(x, value);
}

rangeQuery.update(800, 800.1);

assert(rangeQuery.query(700, 900) == 800.1);
assert(rangeQuery.query(1, 10) == 0);
assert(rangeQuery.query(1, 32) == 24.4);
assert(rangeQuery.query(1, 33) == 64.6);
assert(rangeQuery.query(100, 101) == 1.1);
assert(rangeQuery.query(1, 1000) == 865.8);

rangeQuery.update(800, -200);
assert(rangeQuery.query(10, 1024) == 665.8);

```

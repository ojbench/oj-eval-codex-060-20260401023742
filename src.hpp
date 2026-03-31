// Only <vector> is allowed per problem statement
#include <vector>

template <typename T>
struct Expect {
    T value;
    bool invert;
    bool ok;

    explicit Expect(const T& v) : value(v), invert(false), ok(true) {}

    // Logical negation toggle for all subsequent conditions
    Expect& Not() {
        invert = !invert;
        return *this;
    }

    // x == y
    Expect& toBe(const T& y) {
        bool match = (value == y);
        apply(match);
        return *this;
    }

    // y is std::vector<T>; any z in y such that x == z
    Expect& toBeOneOf(const std::vector<T>& ys) {
        bool found = false;
        for (const T& z : ys) {
            if (value == z) { found = true; break; }
        }
        apply(found);
        return *this;
    }

    // x <= y
    Expect& le(const T& y) {
        bool match = (value < y) || (value == y);
        apply(match);
        return *this;
    }

    // x >= y
    Expect& ge(const T& y) {
        bool match = (y < value) || (value == y);
        apply(match);
        return *this;
    }

    // x < y
    Expect& lt(const T& y) {
        bool match = (value < y);
        apply(match);
        return *this;
    }

    // x > y
    Expect& gt(const T& y) {
        bool match = (y < value);
        apply(match);
        return *this;
    }

    // Allow implicit conversion to bool for conditions like: if (expect(x).ge(...))
    operator bool() const {
        return ok;
    }

private:
    void apply(bool condition) {
        bool eval = invert ? (!condition) : condition;
        ok = ok && eval;
    }
};

template <typename T>
Expect<T> expect(const T& v) {
    return Expect<T>(v);
}


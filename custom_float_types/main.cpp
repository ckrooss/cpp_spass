#include <cstdint>
#include <type_traits>

//#define DEBUG
#ifdef DEBUG
#include <fmt/format.h>
#define println(...) fmt::println(__VA_ARGS__)
#else
#define println(...)
#endif

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

static constexpr u8 BASE = 2;
static constexpr u8 HIDDEN_BIT = 1;

template <typename T>
/// Keep only the n lowest bits of val
static constexpr T keep_bits(T val, int n) {
    T mask = (T{1U} << n) - 1;
    return val & mask;
}

template <typename T>
/// Integer-only power function
static constexpr T ipow(std::type_identity_t<T> base, std::type_identity_t<T> exp, T result = 1) {
    static_assert(std::is_integral_v<T>, "ipow requires integral type T");
    return exp < 1 ? result : ipow(base * base, exp / 2, (exp % 2) ? result * base : result);
}

static_assert(ipow<u8>(2, 0) == 1);
static_assert(ipow<u8>(2, 1) == 2);
static_assert(ipow<u8>(2, 2) == 4);
static_assert(ipow<u8>(2, 3) == 8);
static_assert(ipow<u8>(2, 4) == 16);;
static_assert(ipow<u8>(2, 5) == 32);
static_assert(ipow<u8>(2, 6) == 64);
static_assert(ipow<u64>(2, 32) == 4294967296);

struct FP8 {
    using storage = u8;
    static constexpr u8 SIGN = 1;
    static constexpr u8 EXP = 5;
    static constexpr u8 MANT = 2;
    static constexpr storage BIAS = (ipow<storage>(BASE, EXP - 1) - 1);
};

struct FP16 {
    using storage = u16;
    static constexpr u8 SIGN = 1;
    static constexpr u8 EXP = 5;
    static constexpr u8 MANT = 11;
    static constexpr storage BIAS = (ipow<storage>(BASE, EXP - 1) - 1);
};

struct FP32 {
    using storage = u32;
    static constexpr u8 SIGN = 1;
    static constexpr u8 EXP = 8;
    static constexpr u8 MANT = 23;
    static constexpr storage BIAS = (ipow<storage>(BASE, EXP - 1) - 1);
};

struct FP64 {
    using storage = u64;
    static constexpr u8 SIGN = 1;
    static constexpr u8 EXP = 11;
    static constexpr u8 MANT = 52;
    static constexpr storage BIAS = (ipow<storage>(BASE, EXP - 1) - 1);
};

template <typename F>
class minifloat {
  public:
    using storage = typename F::storage;

    constexpr explicit minifloat(float f) {
        println("-> {}(f={})", __PRETTY_FUNCTION__, f);
        storage s;
        if (f < 0) {
            f *= -1;
            s = 1;
        } else {
            s = 0;
        }

        println("-> s = {}", s);

        storage e{0};
        while (f >= BASE) {
            f /= BASE;
            e++;
        }
        println("-> e = {}", e);
        println("-> f = {}", f);

        e += F::BIAS;
        f -= HIDDEN_BIT;
        storage m = static_cast<storage>(ipow<storage>(BASE, F::MANT) * f);
        println("-> m = {}", m);

        data = 0;
        data |= (s << (F::MANT + F::EXP));
        data |= (e << F::MANT);
        data |= (m);
        println("-> data = {}\n", data);
    }

    constexpr float to_float() const {
        println("<- {}", __PRETTY_FUNCTION__);
        println("<- data = {}", data);
        storage s = (data >> (F::MANT + F::EXP));
        println("<- s = {}", s);
        storage e = keep_bits(data >> F::MANT, F::EXP) - F::BIAS;
        println("<- e = {}", e);
        storage m = keep_bits(data, F::MANT);
        float f = static_cast<float>(m);
        f /= ipow<storage>(BASE, F::MANT);
        f += HIDDEN_BIT;
        println("<- f = {}", f);
        println("<- m = {}", m);

        if (s) {
            f *= -1;
        }

        return f * ipow<storage>(BASE, e);
    }

  private:
    storage data;
};

int main() {
    constexpr float val{3.145};
    constexpr minifloat<FP8> mf{val};
    constexpr float val2 = mf.to_float();
#ifdef DEBUG
    fmt::print("{} => {}\n\n", val, val2);
#endif

    return val2 > 2.0;
}

static_assert(minifloat<FP8>(1.0).to_float() == 1.0);
static_assert(minifloat<FP16>(1.0).to_float() == 1.0);
static_assert(minifloat<FP32>(1.0).to_float() == 1.0);
static_assert(minifloat<FP64>(1.0).to_float() == 1.0);

static_assert(minifloat<FP8>(3.145f).to_float() == 3.0f);
static_assert(minifloat<FP16>(3.145f).to_float() == 3.14453125f);
static_assert(minifloat<FP32>(3.145f).to_float() == 3.14499998f);
static_assert(minifloat<FP64>(3.145f).to_float() == 3.14499998f);


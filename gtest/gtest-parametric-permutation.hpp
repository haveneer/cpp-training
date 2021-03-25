#pragma once

#include "gtest-parametric-sequence.hpp"
#include "gtest/gtest.h"
#include <array>
#include <tuple>

template <typename T> struct InternalPermutation {};

template <typename... Ts>
struct InternalPermutation<std::tuple<Ts...>>
    : testing::internal::ParamGeneratorInterface<std::tuple<Ts...>> {
  using Tuple = std::tuple<Ts...>;
  using Type = std::decay_t<std::tuple_element_t<0, std::decay_t<Tuple>>>;
  static constexpr std::size_t Size = std::tuple_size_v<Tuple>;
  using Data = std::array<Type, Size>;
  using ParamGenerator = testing::internal::ParamGenerator<Tuple>;
  using ParamIteratorInterface = testing::internal::ParamIteratorInterface<Tuple>;

  InternalPermutation(ParamGenerator l) : m_l(std::move(l)) {}

  struct Iterator : ParamIteratorInterface {
    Iterator(const InternalPermutation *base,
             const typename ParamGenerator::iterator iter1, Data data)
        : m_base(base), m_iter1(iter1), m_data(data) {}

    const typename InternalPermutation::ParamGeneratorInterface *
    BaseGenerator() const override {
      return m_base;
    }
    void Advance() override {
      if (!std::next_permutation(m_data.begin(), m_data.end())) {
        ++m_iter1;
        if (m_iter1 != m_base->m_l.end()) {
          m_data = to_data(*m_iter1);
        } else {
          m_data = Data{};
        }
      }
    }
    ParamIteratorInterface *Clone() const override {
      return new Iterator{m_base, m_iter1, m_data};
    }
    const Tuple *Current() const override {
      m_tuple = to_tuple(m_data, std::make_index_sequence<Size>{});
      return &m_tuple;
    }
    bool Equals(const ParamIteratorInterface &other) const override {
      assert(this->m_base == other.BaseGenerator());
      const Iterator *that = reinterpret_cast<const Iterator *>(&other);
      return this->m_iter1 == that->m_iter1 && this->m_data == that->m_data;
    }

    const InternalPermutation *m_base;
    typename ParamGenerator::iterator m_iter1;
    Data m_data;
    mutable Tuple m_tuple;
  };

  ParamIteratorInterface *Begin() const override {
    return new Iterator{this, m_l.begin(), to_data(*m_l.begin())};
  }
  ParamIteratorInterface *End() const override {
    return new Iterator{this, m_l.end(), Data{}};
  }

  ParamGenerator m_l;

private:
  static Data to_data(const Tuple &tuple) {
    Data data = std::apply(
        [](auto &&...elems) {
          return Data{std::forward<decltype(elems)>(elems)...};
        },
        tuple);
    std::sort(data.begin(), data.end());
    return data;
  }
  template <size_t... Is>
  static Tuple to_tuple(const Data &data, std::index_sequence<Is...> _) {
    return std::make_tuple(data[Is]...);
  }
};

template <typename T>
testing::internal::ParamGenerator<T>
Permutation(testing::internal::ParamGenerator<T> l) {
  return testing::internal::ParamGenerator<T>(new InternalPermutation<T>(l));
}

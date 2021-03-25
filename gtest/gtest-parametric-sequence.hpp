#pragma once

#include "gtest/gtest.h"

template <typename T>
struct InternalSequence : testing::internal::ParamGeneratorInterface<T> {
  using ParamGenerator = testing::internal::ParamGenerator<T>;
  using ParamIteratorInterface = testing::internal::ParamIteratorInterface<T>;

  InternalSequence(std::initializer_list<ParamGenerator> l) : m_l(std::move(l)) {
    assert(m_l.size() > 0);
  }

  struct Iterator : ParamIteratorInterface {
    Iterator(const InternalSequence *base,
             const typename std::vector<ParamGenerator>::const_iterator iter1,
             const typename ParamGenerator::iterator iter2)
        : m_base(base), m_iter1(iter1), m_iter2(iter2) {}

    const typename InternalSequence::ParamGeneratorInterface *
    BaseGenerator() const override {
      return m_base;
    }

    void Advance() override {
      ++m_iter2;
      if (m_iter2 == m_iter1->end()) {
        ++m_iter1;
        if (m_iter1 != m_base->m_l.end()) {
          m_iter2 = m_iter1->begin();
        }
      }
    }

    ParamIteratorInterface *Clone() const override {
      return new Iterator{m_base, m_iter1, m_iter2};
    }

    const T *Current() const override { return &*m_iter2; }

    bool Equals(const ParamIteratorInterface &other) const override {
      assert(this->m_base == other.BaseGenerator());
      const Iterator *that = reinterpret_cast<const Iterator *>(&other);
      return this->m_iter1 == that->m_iter1 && this->m_iter2 == that->m_iter2;
    }

    const InternalSequence *m_base;
    typename std::vector<ParamGenerator>::const_iterator m_iter1;
    typename ParamGenerator::iterator m_iter2;
  };

  ParamIteratorInterface *Begin() const override {
    return new Iterator{this, m_l.begin(), m_l[0].begin()};
  }
  ParamIteratorInterface *End() const override {
    return new Iterator{this, m_l.end(), m_l[m_l.size() - 1].end()};
  }

  std::vector<testing::internal::ParamGenerator<T>> m_l;
};

template <typename T>
testing::internal::ParamGenerator<T>
Sequence(std::initializer_list<testing::internal::ParamGenerator<T>> l) {
  return testing::internal::ParamGenerator<T>(new InternalSequence<T>(std::move(l)));
}
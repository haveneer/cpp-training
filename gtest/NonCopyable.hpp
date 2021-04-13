#pragma once

class Noncopyable {
public:
  Noncopyable() = default;
  virtual ~Noncopyable() = default;

  Noncopyable(const Noncopyable &) = delete;
  Noncopyable(Noncopyable &&) = delete;
  Noncopyable &operator=(const Noncopyable &) = delete;
  Noncopyable &operator=(Noncopyable &&) = delete;
};
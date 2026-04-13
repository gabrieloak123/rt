#include "paramset.hpp"

namespace rt {

template <typename T> T ParamSet::retrieve(const string &key, const T &def) const {
  const auto search = m_ps.find(key);

  if (search == m_ps.end()) {
    return def;
  }

  try {
    auto test = dynamic_cast<Value<T>>(search->second);
  } catch (const bad_cast &e) {
    std::cout << "Cast failed: [" << e.what() << "]" << std::endl;
  }

  return dynamic_cast<Value<T>>(search->second).m_value;
}

template <typename T> void ParamSet::assign(const string key, const T &value) {
  m_ps[key] = make_shared<Value<T>>(value);
}

template <typename T> bool ParamSet::contains(const string key) {
	return m_ps.count(key) == 1;
}

} // namespace rt

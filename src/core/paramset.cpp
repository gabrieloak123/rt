#include "paramset.hpp"

template <typename T> T ParamSet::retrieve(const string &key, const T &def) {
  const auto search = m_render_opts.find(key);

  if (search == m_render_opts.end()) {
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
  m_render_opts[key] = make_shared<Value<T>>(value);
}

template <typename T> bool ParamSet::contains(const string key) {
	return m_render_opts.count(key) == 1;
}
